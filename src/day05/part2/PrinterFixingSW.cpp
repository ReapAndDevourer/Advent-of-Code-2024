/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 05.12.24
 *
 ******************************************************************************/

#include "PrinterFixingSW.h"
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>

/*******************************************************************************
* @brief Constructor to create a printer software which's instructions are
* externally read and checked for obliance to a provided ruleset
*
* @param inputFileName Name / Path of the input data file.
*******************************************************************************/
PrinterFixingSW::PrinterFixingSW(const std::string_view inputFileName) {
    std::ifstream inputData(inputFileName.data());
    if(not inputData.is_open())
        throw std::invalid_argument {
            "No input was found under given file path!" };
    std::string instructionLine { };
    // Skip reading the ruleset, we only want the instructions
    while(std::getline(inputData, instructionLine),
        not instructionLine.empty()) { }
    // Read the instruction lines
    auto lineCounter { 0 };
    do {
        std::getline(inputData,instructionLine);
        if(instructionLine.empty()) return;
        this->printInstructions.emplace_back();
        std::istringstream instructions { instructionLine };
        std::string pageAsString;
        while(std::getline(instructions, pageAsString, ','))
            this->printInstructions.at(lineCounter).push_back(std::stoi(pageAsString));
        lineCounter++;
    } while(not inputData.eof());
}

/*******************************************************************************
* @brief By calling this methode, we are able to retreive the sum of the
* middle page numbers of the instructions of the printer that did not
* obly to the provided ruleset.
*
* @param rulesetToApply Ruleset with which the instructions should be
* controlled.
*******************************************************************************/
uint32_t PrinterFixingSW::getSumOfCorrectedInstructions(
    const PrinterRulesetWithCorrection& rulesetToApply) {
    uint32_t sumsOfCorrectMiddles { 0 };
    this->printInstructions.erase(
        std::remove_if(
            this->printInstructions.begin(), this->printInstructions.end(),
            [&rulesetToApply](auto& instruction) {
                const bool wasFixed = rulesetToApply.fixInstructionIfNeeded(instruction);
                return not wasFixed;
            }), this->printInstructions.end());
    std::for_each(this->printInstructions.begin(), this->printInstructions.end(),
        [&sumsOfCorrectMiddles](
        const std::vector<uint16_t>& instructions) {
            // Check if the instruction set has a "middle element"
            if(instructions.size() % 2 == 1) {
                const size_t middleIndex =
                    std::floor(instructions.size() / 2);
                sumsOfCorrectMiddles += instructions.at(middleIndex);
            }
        });
    return sumsOfCorrectMiddles;
}

