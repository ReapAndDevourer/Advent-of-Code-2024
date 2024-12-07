/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/

#include <boost/test/unit_test.hpp>
#include <part2/PrinterRulesetWithCorrection.h>
#include <part2/PrinterFixingSW.h>

BOOST_AUTO_TEST_SUITE(Day05);
BOOST_AUTO_TEST_SUITE(Part2);

/*******************************************************************************
* @brief String-View to the file that contains the test input data.
*******************************************************************************/
constexpr std::string_view inputFileName {
        "./../../test/day05/part1/TestInput.txt"
};

/*******************************************************************************
* @brief The following test shall check if a faulty given print instruction
* is transformed correctly into a legal instruction.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestFaultyInstructionCorrection) {
    const PrinterRulesetWithCorrection sut { inputFileName.data() };
    std::vector<uint16_t> testSequence {
        97, 13, 75, 29, 47
    };
    const std::vector<uint16_t> correctedSequence {
        97, 75, 47, 29, 13
    };
    sut.fixInstructionIfNeeded(testSequence);
    BOOST_TEST(
        std::equal(correctedSequence.begin(), correctedSequence.end(),
            testSequence.begin()), "Instruction was not adjusted as needed!");
}

/*******************************************************************************
* @brief In this test the sum of the middle elements of all instructions
* (correct from start + corrected through function) is checked against the
* expected value.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestSumOfAllInstructions) {
    constexpr auto EXPECTED_SUM { 123 };
    const PrinterRulesetWithCorrection rules { inputFileName.data() };
    PrinterFixingSW printerSW { inputFileName.data() };
    const auto calculatedSum = printerSW.getSumOfCorrectedInstructions(rules);
    BOOST_CHECK_EQUAL(EXPECTED_SUM, calculatedSum);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();