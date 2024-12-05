/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 02.12.2024
 *
 ******************************************************************************/

#include <boost/test/unit_test.hpp>
#include <part2/LevelCheckerWithDampener.h>

BOOST_AUTO_TEST_SUITE(Day02);
BOOST_AUTO_TEST_SUITE(Part2);

/*******************************************************************************
 * In this test it will be checked if the lines are correctly categorized as
 * safe and unsafe with a given test input. --> Result will be checked against
 * expected result.
 ******************************************************************************/
BOOST_AUTO_TEST_CASE(TestLevelCalculationWithDampener) {

    constexpr uint16_t AMOUNT_OF_SAVE_LEVELS { 4 };
    constexpr std::string_view dataFileName {
        R"(./../../test/day02/part1/TestData.txt)"
    };
    LevelCheckerWithDampener::calculateLevelSafety(dataFileName.data());
    BOOST_CHECK_EQUAL(AMOUNT_OF_SAVE_LEVELS,
        LevelCheckerWithDampener::getAmountOfSafeLevels());
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();