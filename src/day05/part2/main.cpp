/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 05.12.24
 *
 ******************************************************************************/

#include <part2/PrinterFixingSW.h>
#include <part2/PrinterRulesetWithCorrection.h>
#include <iostream>

int main() {
    constexpr std::string_view inputFileName {
        "./../../../src/day05/part1/InputData.txt"
    };
    const PrinterRulesetWithCorrection ruleset { inputFileName.data() };
    PrinterFixingSW printer { inputFileName.data() };
    std::cout << "The sum of middle elements of correct instructions is: " <<
        printer.getSumOfCorrectedInstructions(ruleset) << std::endl;
    return 0;
}