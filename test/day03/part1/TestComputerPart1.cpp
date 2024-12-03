/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 03.12.2024
 *
 ******************************************************************************/

#include <boost/test/unit_test.hpp>
#include "part1/ComputerCalculator.h"

BOOST_AUTO_TEST_SUITE(Day03);
BOOST_AUTO_TEST_SUITE(Part1);

BOOST_AUTO_TEST_CASE(TestComputerCalculation) {
    const std::string testString {
        "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"
    };
    const auto lineValue = ComputerCalculator::calculateLineValue(testString);
    constexpr size_t expectedResult { 161 };
    BOOST_CHECK_EQUAL(expectedResult, lineValue);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();