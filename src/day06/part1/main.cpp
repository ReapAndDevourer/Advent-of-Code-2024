/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/

#include <part1/GuardMap.h>
#include <iostream>

int main() {
    constexpr std::string_view inputFileName {
        "./../../../src/day06/part1/InputData.txt"
    };
    GuardMap map { inputFileName.data() };
    const uint32_t fieldsCovered = map.simulateMovement();
    std::cout << "The guard covered " << static_cast<int>(fieldsCovered) <<
        " fields!" << std::endl;
    return 0;
}