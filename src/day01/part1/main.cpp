#include <iostream>
#include <part1/DistanceCalculator.h>
#include <common/InputConverter.h>

int main() {
    constexpr std::string_view dataLocation{
        R"(D:\Programming\Advent-of-Code-2024\src\day01\part1\Data.txt)" };
    auto [dataset1, dataset2] =  convertInputData(dataLocation.data());
    const auto distance = calculateDistance(dataset1, dataset2);
    std::cout << "Calculated distance for the given data: " << distance << std::endl;
    return 0;
}