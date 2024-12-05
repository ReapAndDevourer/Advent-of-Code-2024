/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 04.12.24
 *
 ******************************************************************************/

#include "XMasSearch.h"
#include <fstream>
#include <algorithm>
#include <sys/types.h>

/*******************************************************************************
* @brief Helper-Method to extract the input data out of the input-file into
* the const class attribute.
* @param inputFileName Name of the file, from whom the data shall be extracted.
*******************************************************************************/
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

/*******************************************************************************
* @brief Construct an instance, that reads all the characters from a file whichs
* path is provided by @ref inputFileName. After that various directions are
* checked to find all occurunces of the provided keyword of the class.
* @param inputFileName Path to the file name
******************************************************************************/
XMasSearch::XMasSearch(const std::string_view inputFileName) :
    inputData { std::move(convertFileToInputData(inputFileName)) } {
    this->findStartCoordinates();
}

/*******************************************************************************
* @brief By calling this method all the locations that contain the first
* character of the keyword, will be pushed back into the class startCoordinate
* Container
*******************************************************************************/
void XMasSearch::findStartCoordinates() {
    size_t rowIndex { 0 };
    for(const auto& row : this->inputData) {
        size_t columnIndex { 0 };
        for(const auto sign : row) {
            if(sign == XMasSearch::KEYWORD.front())
                this->startCoordinates.emplace_back(rowIndex, columnIndex);
            columnIndex++;
        }
        rowIndex++;
    }
    this->startCoordinates.shrink_to_fit();
}

/*******************************************************************************
* @brief With this method all occurences of the keyword are searched and counted
* inside the input data.
*
* @return Amount of found occurences
*******************************************************************************/
uint16_t XMasSearch::findAllOccurences() const {
    uint16_t occurencesFound { 0 };
    for(uint8_t modeNr { static_cast<uint8_t>(CheckDirection::NORMAL) };
        modeNr <= static_cast<uint8_t>(CheckDirection::DIAGONAL_RIGHT_REVERSE);
        modeNr++) {
        const auto currentMode { static_cast<CheckDirection>(modeNr) };
        occurencesFound += this->findOccurences(currentMode);
    }
    return occurencesFound;
}

/*******************************************************************************
* @brief Counts the amount of occurences of the keyword for the provided
* check direction and adds the amount to the internal element counter of the
* class.
*
* @param mode Mode in which orientation inside the data input the keyword
* shall be found and counted.
*******************************************************************************/
uint16_t XMasSearch::findOccurences(const CheckDirection mode) const {
    // Check which moves have to be done to check via the given mode
    const auto [colDeriv, rowDeriv] =
        XMasSearch::stepInstructions.find(mode)->second;
    uint16_t occurencesFound { 0 };
    // Now check for correct matches from every start point found until now
    std::for_each(this->startCoordinates.begin(), this->startCoordinates.end(),
        [this, rowDeriv, colDeriv, &occurencesFound] (
            const Coordinates& startPoint) {
            const bool matchFound =
                this->checkForMatch(startPoint, colDeriv, rowDeriv);
            if(matchFound) occurencesFound++;
        });
    return occurencesFound;
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
bool XMasSearch::doesFieldExist(const Coordinates coord) const {
    if(coord.first < 0 or coord.second < 0) return false;
    if(coord.first >= this->inputData.size()) return false;
    if(coord.second >= this->inputData.at(coord.first).size()) return false;
        return true;
}

/*******************************************************************************
* @brief Check if the keyword can be located from moving with the given
* coordinate-derivatives from the startCoordinate
*
* @param startCoordinates point to start the search from inside the input data
* @param xDeriv Change in the column from current point to the next (x-Direction)
* @param yDeriv Change in the row from current point to the next (y-Direction)
*******************************************************************************/
bool XMasSearch::checkForMatch(
    const Coordinates& startCoordinates,
    const int8_t xDeriv, const int8_t yDeriv) const {
    // Defining the needed ressources
    bool matchFound { false };
    uint16_t rowIndex { startCoordinates.first };
    uint16_t colIndex { startCoordinates.second };
    constexpr auto MATCHES_NEEDED { KEYWORD.size() };
    // Start the pattern-matching algorithm
    for(size_t completedChecks { 1 };; completedChecks++) {
        if(completedChecks == MATCHES_NEEDED)
            return true;
        colIndex+= xDeriv;
        rowIndex += yDeriv;
        if(not XMasSearch::doesFieldExist({ rowIndex, colIndex})) return false;
        if(this->inputData.at(rowIndex).at(colIndex) != KEYWORD.at(completedChecks)) return false;
    }
}


