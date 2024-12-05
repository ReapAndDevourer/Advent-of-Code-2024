/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 03.12.2024
 *
 ******************************************************************************/

#include <boost/test/unit_test.hpp>
#include "part2/X_MasSearch.h"

BOOST_AUTO_TEST_SUITE(Day04);
BOOST_AUTO_TEST_SUITE(Part2);

/*******************************************************************************
* @brief Testclass to get access to internal calculation function.
*******************************************************************************/
struct SUT : X_MasSearch {
    using X_MasSearch::findOccurences;
    using X_MasSearch::getStartCoordinates;
    explicit SUT(const std::string_view dataInputFile) :
        X_MasSearch{dataInputFile} { }
};

/*******************************************************************************
* @brief String-View to the file that contains the test input data.
*******************************************************************************/
constexpr std::string_view inputFileName {
        "./../../test/day04/part1/TestDataRaw.txt"
};

/*******************************************************************************
* @brief Checks if the amount of found crosses is correct.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestCrossesFound) {
    X_MasSearch sut { inputFileName.data() };
    constexpr uint16_t EXPECTED_OCCURENCES { 9 };
    BOOST_CHECK_EQUAL(EXPECTED_OCCURENCES, sut.findAmountOfMatchCrosses());
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();