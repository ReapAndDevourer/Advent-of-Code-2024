/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 04.12.24
 *
 ******************************************************************************/

#include "part1/XMasSearch.h"
#include <iostream>

int main() {
    constexpr std::string_view inputFileName {
        "./../../../src/day04/part1/InputData.txt"
    };
    XMasSearch searcherUnit { inputFileName };
    const uint16_t foundElements = searcherUnit.findAllOccurences();
    std::cout << "The keyword was found " << static_cast<int>(foundElements) <<
        " times!" << std::endl;
    return 0;
}