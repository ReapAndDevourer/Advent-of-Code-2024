/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 05.12.24
 *
 ******************************************************************************/

#include <part1/PrinterRuleset.h>
#include <part1/PrinterSW.h>
#include <iostream>

int main() {
    constexpr std::string_view inputFileName {
        "./../../../src/day05/part1/InputData.txt"
    };
    const PrinterRuleset ruleset { inputFileName.data() };
    const PrinterSW printer { inputFileName.data() };
    std::cout << "The sum of middle elements of correct instructions is: " <<
        printer.getSumOfCorrectInstuction(ruleset) << std::endl;
    return 0;
}