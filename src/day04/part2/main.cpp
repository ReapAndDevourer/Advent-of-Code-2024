/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 04.12.24
 *
 ******************************************************************************/

#include "part2/X_MasSearch.h"
#include <iostream>

int main() {
    constexpr std::string_view inputFileName {
        "./../../../src/day04/part1/InputData.txt"
    };
    X_MasSearch searcherUnit { inputFileName };
    const uint16_t foundCrosses = searcherUnit.findAmountOfMatchCrosses();
    std::cout << static_cast<int>(foundCrosses) <<
        " crosses were found!" << std::endl;
    return 0;
}