/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 29.12.24
 *
 ******************************************************************************/

#include "boost/test/unit_test.hpp"
#include "part2/GuardMapSolver.h"

BOOST_AUTO_TEST_SUITE(Day06);
BOOST_AUTO_TEST_SUITE(Part2);

namespace {
    struct Sut : GuardMapSolver {
        using GuardMapSolver::GuardMapSolver;
    };
}

/*******************************************************************************
* @brief String-View to the file that contains the test input data.
*******************************************************************************/
constexpr std::string_view testData {
    "./../../test/day06/part1/TestInput.txt"
};

/*******************************************************************************
* @brief Check that the correct amount of endless loops are found.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(CheckPossibleEndlessLoops) {
    constexpr size_t EXPECTED_AMOUNT_OF_LOOPS { 6 };
    Sut solver { testData.data() };
    const auto foundLoops = solver.findAllLoops();
    BOOST_CHECK_EQUAL(EXPECTED_AMOUNT_OF_LOOPS, foundLoops);
}

BOOST_AUTO_TEST_CASE(TestAlternativeInput) {
    constexpr size_t EXPECTED_AMOUNT_OF_LOOPS { 1 };
    Sut solver { "./../../test/day06/part2/AlternativeInput.txt" };
    const auto foundLoops = solver.findAllLoops();
    BOOST_CHECK_EQUAL(EXPECTED_AMOUNT_OF_LOOPS, foundLoops);
}

BOOST_AUTO_TEST_CASE(TestAlternativeInput2) {
    constexpr size_t EXPECTED_AMOUNT_OF_LOOPS { 3 };
    Sut solver { "./../../test/day06/part2/AlternativeInput2.txt" };
    const auto foundLoops = solver.findAllLoops();
    BOOST_CHECK_EQUAL(EXPECTED_AMOUNT_OF_LOOPS, foundLoops);
}

BOOST_AUTO_TEST_CASE(TestAlternativeInput3) {
    constexpr size_t EXPECTED_AMOUNT_OF_LOOPS { 1 };
    Sut solver { "./../../test/day06/part2/AlternativeInput3.txt" };
    const auto foundLoops = solver.findAllLoops();
    BOOST_CHECK_EQUAL(EXPECTED_AMOUNT_OF_LOOPS, foundLoops);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();