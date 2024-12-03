/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 03.12.2024
 *
 ******************************************************************************/

#include <boost/test/unit_test.hpp>
#include "part2/ComputerCalculatorWithToggle.h"

BOOST_AUTO_TEST_SUITE(Day03);
BOOST_AUTO_TEST_SUITE(Part2);

BOOST_AUTO_TEST_CASE(TestComputerCalculationWithToggle) {
    const std::string testString {
        "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"
    };
    std::map<
        uint32_t, ComputerCalculatorWithToggle::Mode> activationMarkers { };
    ComputerCalculatorWithToggle::findNewLineMarkers(testString, activationMarkers);
    const auto lineValue =
        ComputerCalculatorWithToggle::calculateLineValue(testString, activationMarkers);
    constexpr size_t expectedResult { 48 };
    BOOST_CHECK_EQUAL(expectedResult, lineValue);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();