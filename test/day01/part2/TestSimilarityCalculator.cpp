/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 01.12.2024
 *
 ******************************************************************************/

#include <boost/test/unit_test.hpp>
#include "part2/SimilarityCalculator.h"

BOOST_AUTO_TEST_SUITE(Day01)
BOOST_AUTO_TEST_SUITE(Part2)

/*******************************************************************************
 * With this test and the data we will check if the created algorithm
 * calculates the distance as expected.
 ******************************************************************************/
BOOST_AUTO_TEST_CASE(SimilarityCalculation) {
    std::vector<int> set1 { 3, 4, 2, 1, 3, 3 };
    std::vector<int> set2 { 4, 3, 5, 3, 9, 3 };
    constexpr long expectedDistance { 31 };
    const auto distance = calculateSimilarity(set1, set2);
    BOOST_CHECK_EQUAL(distance, expectedDistance);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();