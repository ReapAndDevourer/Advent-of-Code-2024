/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/

#include <part2/GuardMapSolver.h>
#include <iostream>

int main() {
    constexpr std::string_view inputFileName {
        "./../../../src/day06/part1/InputData.txt"
    };
    GuardMapSolver solver { inputFileName };
    const auto loopsFound = solver.findAllLoops();
    std::cout << "Following amounts of endless loops can be created: " <<
        loopsFound << std::endl;
    return 0;
}