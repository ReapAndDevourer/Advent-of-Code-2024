/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 02.12.2024
 *
 ******************************************************************************/

#include <iostream>
#include "LevelCheckerWithDampener.h"

int main() {
    constexpr std::string_view inputFileName {
        R"(D:\Programming\Advent-of-Code-2024\src\day02\part1\InputData.txt)"
    };
    LevelCheckerWithDampener::calculateLevelSafety(inputFileName.data());
    std::cout << "Amount of safe lines with dampener: " <<
        static_cast<int>(LevelCheckerWithDampener::getAmountOfSafeLevels()) << std::endl;
    return 0;
}