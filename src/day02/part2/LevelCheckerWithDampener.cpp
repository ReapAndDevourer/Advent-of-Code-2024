/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 02.12.2024
 *
 ******************************************************************************/

#include "LevelCheckerWithDampener.h"
#include <fstream>
#include <sstream>

/*******************************************************************************
 * @brief Retreive the amount of levels that are safe from the report input
 * @return Amount of safe levels
 ******************************************************************************/
uint32_t LevelCheckerWithDampener::getAmountOfSafeLevels() {
    return LevelCheckerWithDampener::amountOfSaveLevels;
}

/*******************************************************************************
 * @brief Determine the amount of safe levels from the test data whichs name
 * is provided by the string view @ref dataFile.
 * Also check if alternatives would be safe, if one element of the vector would
 * be removed. If so, this counts as safe level aswell.
 * @param dataFile Name of input data file
 ******************************************************************************/
void LevelCheckerWithDampener::calculateLevelSafety(const std::string_view dataFile) {
    std::fstream inputFile;
    inputFile.open(dataFile.data(), std::ios::in);
    if(not inputFile.is_open())
        throw std::invalid_argument {
            "No Data-Set was provided under the given name!" };
    std::string lineString;
    // Extract Line-Elements out of input data
    while(std::getline(inputFile, lineString)) {
        // Variable which will signal that line doesn't need to be checked
        // anymore after a safe variant has been found
        bool safeVariantFound { false };
        // Extract uint8_t values out of line-string
        std::istringstream lineData { lineString };
        std::vector<uint8_t> rowData { };
        int elementValue;
        while (lineData >> elementValue)
            rowData.push_back(static_cast<uint8_t>(elementValue));
        // Do the normal check of the line
        // Stop further checks if line is safe
        if(LevelCheckerWithDampener::isLineSafe(rowData)) {
            amountOfSaveLevels++;
            safeVariantFound = true;
        }
        // Check alternatives variants
        // Stop further checks if one alternative is safe
        const size_t ALTERNATIVES_TO_CHECK { rowData.size() };
        for(size_t i = 0;
            i < ALTERNATIVES_TO_CHECK and not safeVariantFound;
            ++i) {
            std::vector<uint8_t> alternativeRow { rowData };
            alternativeRow.erase(std::next(alternativeRow.begin(), i));
            if(LevelCheckerWithDampener::isLineSafe(alternativeRow)) {
                amountOfSaveLevels++;
                safeVariantFound = true;
            }
        }
    }
}

/*******************************************************************************
 * @brief Control if the line is "safe" by checking
 * 1) That all the elements are either ascending or descending
 * 2) The difference between two adjecent elements is smaller 3
 * @param lineData Element of the line to check
 * @return true Line is considered "safe"
 * @return false Line is considered "not safe"
 ******************************************************************************/
bool LevelCheckerWithDampener::isLineSafe(const std::vector<uint8_t>& lineData) {
    enum class Rule { ASCENDING, DESCENDING };
    // Set ascend or descend rule depending on 1st and 2nd element
    const Rule ruleToCheck { lineData.at(1) > lineData.at(0) ?
            Rule::ASCENDING : Rule::DESCENDING };
    const size_t RUNS_TO_DO { lineData.size() - 1 };
    // Do the checks for the elements for the first time
    for(size_t i = 0; i < RUNS_TO_DO; ++i) {
        const uint8_t firstElement { lineData.at(i) };
        const uint8_t secondElement { lineData.at(i + 1) };
        // Check Rule
        const Rule availableRule { secondElement > firstElement ?
            Rule::ASCENDING : Rule::DESCENDING };
        if(availableRule != ruleToCheck) return false;
        // Check adjacent dif between values
        const uint8_t absDiff = std::abs(secondElement-firstElement);
        if(absDiff < 1 or absDiff > 3 ) return false;
    }
    return true;
}
