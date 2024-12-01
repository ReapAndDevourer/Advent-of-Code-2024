/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 01.12.2024
 *
 ******************************************************************************/
#include <iostream>
#include <part2/SimilarityCalculator.h>
#include <common/InputConverter.h>

int main() {
    constexpr std::string_view dataLocation{
        R"(D:\Programming\Advent-of-Code-2024\src\day01\part1\Data.txt)" };
    auto [dataset1, dataset2] =  convertInputData(dataLocation.data());
    const auto distance = calculateSimilarity(dataset1, dataset2);
    std::cout << "Calculated distance for the given data: " << distance << std::endl;
    return 0;
}
