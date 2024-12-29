/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/
#include <boost/test/unit_test.hpp>
#include <part1/Guard.h>
#include <part1/GuardMap.h>

BOOST_AUTO_TEST_SUITE(Day06);
BOOST_AUTO_TEST_SUITE(Part1);

namespace {
    struct SutMap : GuardMap {
        using GuardMap::GuardMap;
        using GuardMap::getMap;
    };
}

/*******************************************************************************
* @brief String-View to the file that contains the test input data.
*******************************************************************************/
constexpr std::string_view testData {
    "./../../test/day06/part1/TestInput.txt"
};

/*******************************************************************************
* @brief Check that the map is equal to the expected one after simulation of the
* movement.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(CheckMapAfterMovement) {
    SutMap testInput { testData.data() };
    const SutMap controlInput { "./../../test/day06/part1/ControlInput.txt" };
    testInput.simulateMovement();
    const auto& testMap = testInput.getMap();
    const auto& controlMap= controlInput.getMap();
    for(auto i { 0 }; i < controlMap.size(); ++i) {
        BOOST_CHECK(
            std::equal(controlMap.at(i).begin(),controlMap.at(i).end(),
            testMap.at(i).begin())
            );
    }
}

/*******************************************************************************
* @brief Check that the amount of checked field of the movement simulation
* equals the expected amount.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestCheckedSpaces) {
    constexpr auto EXPTECTED_CHECKED_FIELDS { 41 };
    GuardMap map { testData.data() };
    const auto foundFields = map.simulateMovement();
    BOOST_CHECK_EQUAL(EXPTECTED_CHECKED_FIELDS, foundFields);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();