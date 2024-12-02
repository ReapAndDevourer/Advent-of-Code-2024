/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 02.12.2024
 *
 ******************************************************************************/

#include <iostream>
#include "LevelChecker.h"

int main() {
    constexpr std::string_view inputFileName {
        R"(D:\Programming\Advent-of-Code-2024\src\day02\part1\InputData.txt)"
    };
    LevelChecker::calculateLevelSafety(inputFileName.data());
    std::cout << "Amount of safe lines: " <<
        static_cast<int>(LevelChecker::getAmountOfSafeLevels()) << std::endl;
    return 0;
}