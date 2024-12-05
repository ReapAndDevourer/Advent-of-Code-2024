/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 04.12.24
 *
 ******************************************************************************/

#include "X_MasSearch.h"
#include <fstream>
#include <algorithm>
#include <sys/types.h>

namespace {
    /***************************************************************************
    * @brief Helper-Method to extract the input data out of the input-file into
    * the const class attribute.
    * @param inputFileName Name of the file, from whom the data shall be
    * extracted.
    ***************************************************************************/
    std::vector<std::vector<char>>convertFileToInputData(
        const std::string_view inputFileName) {
        std::fstream inputFile;
        inputFile.open(inputFileName.data(), std::ios::in);

        if(not inputFile.is_open())
            throw std::invalid_argument {
                "No Input-File was found under the provided path!"};
        std::vector<std::vector<char>> inputData { std::vector<char>{ } };
        // While one can read char by char
        char charToSet { };
        while(inputFile.get(charToSet), not inputFile.eof()) {
            if(charToSet == '\n') {
                inputData.emplace_back( );
                continue;
            }
            inputData.back().push_back(charToSet);
        }
        inputFile.close();
        if(inputData.size() == 1 and inputData.at(0).empty())
            throw std::invalid_argument {
                "Test-Input is either empty or not in a correct format!" };
        std::for_each(inputData.begin(), inputData.end(),
            [](std::vector<char>& vec) { vec.shrink_to_fit(); });
        inputData.shrink_to_fit();
        return std::move(inputData);
    }
}

/*******************************************************************************
* @brief Construct an instance, that reads all the characters from a file whichs
* path is provided by @ref inputFileName. After that various directions can be
* checked to find all occurunces of the provided keyword of the class.
* @param inputFileName Path to the file name
******************************************************************************/
X_MasSearch::X_MasSearch(const std::string_view inputFileName) :
    inputData { std::move(convertFileToInputData(inputFileName)) } {
    this->findStartCoordinates();
}

/*******************************************************************************
* @brief By calling this method all the locations that contain the first
* character of the keyword, will be pushed back into the class startCoordinate
* Container
*******************************************************************************/
void X_MasSearch::findStartCoordinates() {
    size_t rowIndex { 0 };
    for(const auto& row : this->inputData) {
        size_t columnIndex { 0 };
        for(const auto sign : row) {
            if(sign == X_MasSearch::KEYWORD.front())
                this->startCoordinates.emplace_back(rowIndex, columnIndex);
            columnIndex++;
        }
        rowIndex++;
    }
    this->startCoordinates.shrink_to_fit();
}

/*******************************************************************************
* @brief With this method all occurences of the keyword are searched and the
* center position of them are safed inside the attributes of this class.
*
* @return Amount of found occurences
*******************************************************************************/
void X_MasSearch::findAllOccurences() {
    uint16_t occurencesFound { 0 };
    this->matchCenters.clear();
    // In this part 2 we only check the diagonal ones
    for(uint8_t modeNr { static_cast<uint8_t>(CheckDirection::DIAGONAL_LEFT) };
        modeNr <= static_cast<uint8_t>(CheckDirection::DIAGONAL_RIGHT_REVERSE);
        modeNr++) {
        const auto currentMode { static_cast<CheckDirection>(modeNr) };
        findOccurences(currentMode);
    };
}

/*******************************************************************************
* @brief By calling this function all the Matches and their centers (position
* of their 'A' character) will be used to determine the amount of X-MAS-Crosses
* that are located inside the input data.
*******************************************************************************/
uint16_t X_MasSearch::findAmountOfMatchCrosses() {
    uint16_t crossesDetected { 0 };
    this->findAllOccurences();
    std::for_each(this->matchCenters.begin(), this->matchCenters.end(),
        [&crossesDetected](const std::pair<Coordinates, uint8_t>& centerInfos) {
            const auto matchesInCenter { centerInfos.second };
            if(matchesInCenter > 2)
                throw std::overflow_error {
                    "Too many matches have been found for one center coordinate!" };
            if(matchesInCenter == 2)
                crossesDetected++;
        });
    return crossesDetected;
}


/*******************************************************************************
* @brief Counts the amount of occurences of the keyword for the provided
* check direction and add center position to the internal class attribute.
*
* @param mode Mode in which orientation inside the data input the keyword
* shall be found and counted.
*******************************************************************************/
void X_MasSearch::findOccurences(const CheckDirection mode) {
    // Check which moves have to be done to check via the given mode
    const auto colDeriv = X_MasSearch::stepInstructions.find(mode)->second.first;
    const auto rowDeriv = X_MasSearch::stepInstructions.find(mode)->second.second;
    uint16_t occurencesFound { 0 };
    // Now check for correct matches from every start point found until now
    std::for_each(this->startCoordinates.begin(), this->startCoordinates.end(),
        [this, rowDeriv, colDeriv] (const Coordinates& startPoint) {
            const bool matchFound =
                this->checkForMatch(startPoint, colDeriv, rowDeriv);
            // If a match of the keyword has been found, we need to check if
            // there is already another match found at this center-coordinate or
            // if the coordinate has to "registered" in the vector. --> This
            // will be done to know for further matches that a match has
            // already been found at this location.
            if(matchFound) {
                const auto centerRowIndex = startPoint.first + rowDeriv;
                const auto centerColIndex = startPoint.second + colDeriv;
                const auto itToExistingCoordinate =
                    std::find_if(this->matchCenters.begin(),
                        this->matchCenters.end(),
                        [centerRowIndex, centerColIndex] (std::pair<Coordinates,
                        uint8_t>& centerPair) {
                            auto& [coord, CenterCount] = centerPair;
                        return coord.first == centerRowIndex and
                            coord.second == centerColIndex;
                    });
                if(itToExistingCoordinate == this->matchCenters.end())
                    this->matchCenters.emplace_back(
                        Coordinates {centerRowIndex, centerColIndex}, 1);
                else
                    itToExistingCoordinate->second++;
            }
        });
}

/*******************************************************************************
* @brief Methode that checks if the given Coordinated are part of the input
* data or not. If not, access to the element would result in undefined
* behaviour!
* @param coord Coordinates that will be checked, if they are part of the data
* input.
* @return true Coordinates exist in the input.
* @return false Coordinates are not part of the input data.
*******************************************************************************/
bool X_MasSearch::doesFieldExist(const Coordinates coord) const {
    if(coord.first < 0 or coord.second < 0) return false;
    if(coord.first >= this->inputData.size()) return false;
    if(coord.second >= this->inputData.at(coord.first).size()) return false;
        return true;
}

/*******************************************************************************
* @brief Check if the keyword can be located from moving with the given
* coordinate-derivatives from the startCoordinate.
*
* @param coordinates point to start the search from inside the input data
* @param xDeriv Change in the column from current point to the next (x-Direction)
* @param yDeriv Change in the row from current point to the next (y-Direction)
*******************************************************************************/
bool X_MasSearch::checkForMatch(
    const Coordinates& coordinates,
    const int8_t xDeriv, const int8_t yDeriv) const {
    // Defining the needed ressources
    bool matchFound { false };
    uint16_t rowIndex { coordinates.first };
    uint16_t colIndex { coordinates.second };
    constexpr auto MATCHES_NEEDED { KEYWORD.size() };
    // Start the pattern-matching algorithm
    for(size_t completedChecks { 1 };; completedChecks++) {
        if(completedChecks == MATCHES_NEEDED)
            return true;
        colIndex+= xDeriv;
        rowIndex += yDeriv;
        if(not X_MasSearch::doesFieldExist({ rowIndex, colIndex})) return false;
        if(this->inputData.at(rowIndex).at(colIndex) != KEYWORD.at(completedChecks)) return false;
    }
}


