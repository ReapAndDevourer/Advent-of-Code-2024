/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 01.12.2024
 *
 ******************************************************************************/

#include <boost/test/unit_test.hpp>
#include <common/InputConverter.h>
#include "part1/DistanceCalculator.h"

BOOST_AUTO_TEST_SUITE(Day01)
BOOST_AUTO_TEST_SUITE(Part1)

/*******************************************************************************
 * With this test and the data we will check if the created algorithm
 * calculates the distance as expected.
 ******************************************************************************/
BOOST_AUTO_TEST_CASE(DistanceCalculation) {
    std::vector<int> set1 { 3, 4, 2, 1, 3, 3 };
    std::vector<int> set2 { 4, 3, 5, 3, 9, 3 };
    constexpr long expectedDistance { 11 };
    const auto distance = calculateDistance(set1, set2);
    BOOST_CHECK_EQUAL(distance, expectedDistance);
}

/*******************************************************************************
 * In this test it should be tested that the input-Data that is provided via
 * .txt-file is converted correctly into the target format of the vectors.
 ******************************************************************************/
BOOST_AUTO_TEST_CASE(InputCreation) {
    constexpr std::string_view testDateLoc {
        R"(./../../test/day01/part1/TestData.txt)" };
    std::vector<int> dataset1 { 412341, 32423, 920948, 4, 203459 };
    std::vector<int> dataset2 { 12341234, 120294, 204958, 234, 200035};
    auto [convert1 , convert2] = convertInputData(testDateLoc.data());
    BOOST_CHECK(std::equal(dataset1.begin(), dataset1.end(), convert1.begin()));
    BOOST_CHECK(std::equal(dataset2.begin(), dataset2.end(), convert2.begin()));
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();