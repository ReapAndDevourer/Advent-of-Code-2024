/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 03.12.2024
 *
 ******************************************************************************/

#include "ComputerCalculator.h"
#include <iostream>

int main() {
    constexpr std::string_view inputFileName {
        R"(D:\Programming\Advent-of-Code-2024\src\day03\part1\InputData.txt)"
    };
    const auto programmResult {
        ComputerCalculator::calculateProgrammValue(inputFileName) };
    std::cout << "Programm result: " << programmResult << std::endl;
    return 0;
}