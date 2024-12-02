/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 02.12.2024
 *
 ******************************************************************************/

#include "LevelChecker.h"
#include <fstream>
#include <sstream>

/*******************************************************************************
 * @brief Retreive the amount of levels that are safe from the report input
 * @return Amount of safe levels
 ******************************************************************************/
uint32_t LevelChecker::getAmountOfSafeLevels() {
    return LevelChecker::amountOfSaveLevels;
}

/*******************************************************************************
 * @brief Determine the amount of safe levels from the test data whichs name
 * is provided by the string view @ref dataFile.
 * @param dataFile Name of input data file
 ******************************************************************************/
void LevelChecker::calculateLevelSafety(const std::string_view dataFile) {
    std::fstream inputFile;
    inputFile.open(dataFile.data(), std::ios::in);
    if(not inputFile.is_open())
        throw std::invalid_argument {
            "No Data-Set was provided under the given name!" };
    std::string lineString;
    // Extract Line-Elements out of input data
    while(std::getline(inputFile, lineString)) {
        std::istringstream lineData { lineString };
        constexpr size_t ELEMENTS_PER_ROW { 5 };
        std::vector<uint8_t> rowData { };
        int elementValue;
        while (lineData >> elementValue)
            rowData.push_back(static_cast<uint8_t>(elementValue));
        if(LevelChecker::isLineSafe(rowData))
            LevelChecker::amountOfSaveLevels++;
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
bool LevelChecker::isLineSafe(const std::vector<uint8_t>& lineData) {
    enum class Rule { ASCENDING, DESCENDING };
    // Set ascend or descend rule depending on 1st and 2nd element
    const Rule ruleToCheck { lineData.at(1) > lineData.at(0) ?
            Rule::ASCENDING : Rule::DESCENDING };
    const size_t RUNS_TO_DO { lineData.size() - 1 };
    // Do the checks for the elements (Check 1 vs 2, 2 vs 3, ...)
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


