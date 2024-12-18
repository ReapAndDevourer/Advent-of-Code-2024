/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 05.12.24
 *
 ******************************************************************************/

#include "PrinterRuleset.h"

#include <algorithm>
#include <fstream>
#include <sstream>

/*******************************************************************************
* @brief Constructor to create a ruleset from an input file.
* @param inputFileName Name of the file that provides the input data.
*******************************************************************************/
PrinterRuleset::PrinterRuleset(std::string_view inputFileName) {
    std::ifstream inputData { inputFileName.data() };
    if(not inputData.is_open())
        throw std::invalid_argument {
            "No input-Data-File has been found under given location!" };
    std::string inputLine;
    // Read the lines until the end of the decleration of the ruleset
    while(std::getline(inputData, inputLine), not inputLine.empty()) {
        std::istringstream numberStream { inputLine };
        std::string numberAsString;
        // Two numbers are provided per line
        uint16_t highPrioPage { 0 };
        uint16_t lowPrioPage { 0 };
        std::getline(numberStream, numberAsString, '|');
        highPrioPage = std::stoi(numberAsString);
        std::getline(numberStream, numberAsString);
        lowPrioPage = std::stoi(numberAsString);
        // Insert or use element with Lower Prio element as key and a vector
        // of higher prio pages as element
        auto itToMatch =
            this->rules.try_emplace(lowPrioPage, std::vector<uint16_t>{ }).first;
        itToMatch->second.push_back(highPrioPage);
    }
}

/*******************************************************************************
* @brief By calling this method one can check if the given print instruction
* is adhering to the currently loaded ruleset or not.
*
* The checker works the following. We take the first element and check that
* no rule exists that one of the other elements has prio over our current.
* If that is the case, we can move one to the next and repeat this until we have
* reached the last element. On reaching the last element, we can confirm that
* the sequence is correct. If we find a rule on they way, we can instantly
* quit the check and return that the sequence is illegal.
*
* @param printInstruction print instruction to check
* @return true The instruction is correct.
* @return false The instruction is faulty.
*******************************************************************************/
bool PrinterRuleset::checkCorrectness(
    const std::vector<uint16_t>& printInstruction) const {
    for(auto i { 0 }; i < (printInstruction.size() - 1); ++i) {
        // For every element the check with all following numbers has to be done
        const uint16_t printNumber { printInstruction.at(i) };
        const auto itToRuleset = this->rules.find(printNumber);
        if(itToRuleset == this->rules.end() or printInstruction.size() <= 1)
            continue; // Used number doesn't need to follow any rules
        const auto& numbersWithHigherPrio = itToRuleset->second;
        // Check all the following numbers with the given ruleset
        auto itToSearchResult =
            std::find_if(std::next(printInstruction.begin(), i + 1),
            printInstruction.end(),
            [&numbersWithHigherPrio](const auto followedNumber) {
                // Check all the rulesets on the current number to check
                const bool illegalOrder =
                    std::any_of(numbersWithHigherPrio.begin(),
                        numbersWithHigherPrio.end(),
                        [followedNumber](const auto higherPrioNum) {
                        return higherPrioNum == followedNumber;
                    });
                // If illegal order has been found, stop std::find_if so it
                // will return an iterator to the illegal element
                if(illegalOrder) return true;
                // If order is okay, return true to keep on searching for
                // illegal orders with the numbers following after
                return false;
        });
        // If an illegal order has been located, return false
        if(itToSearchResult != printInstruction.end()) return false;
    }
    return true;
}
