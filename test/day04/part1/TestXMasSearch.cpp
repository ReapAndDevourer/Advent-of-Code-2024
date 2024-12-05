/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 03.12.2024
 *
 ******************************************************************************/

#include <boost/test/unit_test.hpp>
#include "part1/XMasSearch.h"

BOOST_AUTO_TEST_SUITE(Day04);
BOOST_AUTO_TEST_SUITE(Part1);

/*******************************************************************************
* @brief Testclass to get access to internal calculation function.
*******************************************************************************/
struct SUT : XMasSearch {
    using XMasSearch::findOccurences;
    using XMasSearch::getStartCoordinates;
    explicit SUT(const std::string_view dataInputFile) :
        XMasSearch{dataInputFile} { }
};

/*******************************************************************************
* @brief String-View to the file that contains the test input data.
*******************************************************************************/
constexpr std::string_view inputFileName {
        "./../../test/day04/part1/TestDataRaw.txt"
};

/*******************************************************************************
* @brief Inside the following test case it will be checked that all the
* startpoints have been loacted from inside the simulated test input.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestStartPositions) {
    constexpr std::array<XMasSearch::Coordinates, 19> expectedPositions {
        {
            { 0, 4 },
            { 0, 5 },
            { 1, 4 },
            { 2, 2 },
            { 2, 4 },
            { 3, 9 },
            { 4, 0 },
            { 4, 6 },
            { 5, 0 },
            { 5, 1 },
            { 5, 5 },
            { 5, 6 },
            { 6, 7 },
            { 7, 2 },
            { 8, 5 },
            { 9, 1 },
            { 9, 3 },
            { 9, 5 },
            { 9, 9 }
        }};
    const SUT sut { inputFileName.data() };
    const auto& startCoordinates = sut.getStartCoordinates();
    BOOST_CHECK(std::equal(
        expectedPositions.begin(), expectedPositions.end(),
        startCoordinates.begin(), startCoordinates.end()));
}

/*******************************************************************************
* @brief In the following it will be checked that for all the different
* search directions the correct amount of occurences have been found.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestOrientationOccurences) {
    constexpr uint16_t NORMAL_OCCURENCES { 3 };
    constexpr uint16_t REVERSE_OCCURENCES { 2 };
    constexpr uint16_t TOP_DOWN_OCCURECES { 1 };
    constexpr uint16_t BOTTOM_UP_OCCURENCES { 2 };
    constexpr uint16_t DIAGONAL_LEFT_OCCURENCES { 4 };
    constexpr uint16_t DIAGONAL_LEFT_REVERSE_OCCURENCES { 1 };
    constexpr uint16_t DIAGONAL_RIGHT_OCCURENCES { 4 };
    constexpr uint16_t DIAGONAL_RIGHT_REVERSE_OCCURENCES { 1 };

    const SUT sut { inputFileName.data() };
    BOOST_CHECK_EQUAL(NORMAL_OCCURENCES, sut.findOccurences(XMasSearch::CheckDirection::NORMAL));
    BOOST_CHECK_EQUAL(REVERSE_OCCURENCES, sut.findOccurences(XMasSearch::CheckDirection::REVERSE));
    BOOST_CHECK_EQUAL(TOP_DOWN_OCCURECES, sut.findOccurences(XMasSearch::CheckDirection::TOP_DOWN));
    BOOST_CHECK_EQUAL(BOTTOM_UP_OCCURENCES, sut.findOccurences(XMasSearch::CheckDirection::BOTTOM_UP));
    BOOST_CHECK_EQUAL(DIAGONAL_LEFT_OCCURENCES, sut.findOccurences(XMasSearch::CheckDirection::DIAGONAL_LEFT));
    BOOST_CHECK_EQUAL(DIAGONAL_LEFT_REVERSE_OCCURENCES, sut.findOccurences(XMasSearch::CheckDirection::DIAGONAL_LEFT_REVERSE));
    BOOST_CHECK_EQUAL(DIAGONAL_RIGHT_OCCURENCES, sut.findOccurences(XMasSearch::CheckDirection::DIAGONAL_RIGHT));
    BOOST_CHECK_EQUAL(DIAGONAL_RIGHT_REVERSE_OCCURENCES, sut.findOccurences(XMasSearch::CheckDirection::DIAGONAL_RIGHT_REVERSE));
}

/*******************************************************************************
* @brief Check that the sum of all occurences is equal to the expected amount.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestOccurences) {
    const XMasSearch sut { inputFileName.data() };
    constexpr uint16_t EXPECTED_OCCURENCES { 18 };
    BOOST_CHECK_EQUAL(EXPECTED_OCCURENCES, sut.findAllOccurences());
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();