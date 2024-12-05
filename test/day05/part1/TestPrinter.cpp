/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 05.12.24
 *
 ******************************************************************************/

#include <boost/test/unit_test.hpp>
#include <part1/PrinterRuleset.h>

BOOST_AUTO_TEST_SUITE(Day05);
BOOST_AUTO_TEST_SUITE(Part1);

/*******************************************************************************
* @brief String-View to the file that contains the test input data.
*******************************************************************************/
constexpr std::string_view inputFileName {
        "./../../test/day05/part1/TestInput.txt"
};

/*******************************************************************************
* @brief Inside the following test case it will be checked that all the
* startpoints have been located from inside the simulated test input.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestCorrectInstruction) {
    PrinterRuleset sut { inputFileName.data() };
    const std::vector<uint16_t> legalCheckSequence {
        75, 47, 61, 53, 29}
    ;
    const auto correctSequence = sut.checkCorrectness(legalCheckSequence);
    BOOST_CHECK(correctSequence);
}

/*******************************************************************************
* @brief Test @ref TestCorrectInstruction will be repeated buth with a false
* instruction.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestFaultyInstruction) {
    PrinterRuleset sut { inputFileName.data() };
    const std::vector<uint16_t> illegalCheckSequence {
        97, 13, 75, 29, 47
    };
    const auto correctSequence = sut.checkCorrectness(illegalCheckSequence);
    BOOST_CHECK(correctSequence);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();