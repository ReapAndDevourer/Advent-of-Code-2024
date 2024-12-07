/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 05.12.24
 *
 ******************************************************************************/

#include <boost/test/unit_test.hpp>
#include <part1/PrinterRuleset.h>
#include <part1/PrinterSW.h>

BOOST_AUTO_TEST_SUITE(Day05);
BOOST_AUTO_TEST_SUITE(Part1);

struct PrinterSWExtend : PrinterSW {
    using PrinterSW::getInstructions;
    using PrinterSW::PrinterSW;
};

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
    const PrinterRuleset sut { inputFileName.data() };
    const std::vector<uint16_t> legalCheckSequence {
        75, 47, 61, 53, 29 };
    const auto correctSequence = sut.checkCorrectness(legalCheckSequence);
    BOOST_CHECK(correctSequence);
}

/*******************************************************************************
* @brief Test @ref TestCorrectInstruction will be repeated buth with a false
* instruction.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestFaultyInstruction) {
    const PrinterRuleset sut { inputFileName.data() };
    const std::vector<uint16_t> illegalCheckSequence {
        97, 13, 75, 29, 47
    };
    const auto isCorrect = sut.checkCorrectness(illegalCheckSequence);
    BOOST_CHECK(not isCorrect);
}

/*******************************************************************************
* @brief In the following test it shall be checked if the instructions of
* the test input are correctly converted to the wanted containers of the
* PrinterSW
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestInstructionInput) {
    PrinterSWExtend sut { inputFileName.data() };
    std::array<std::vector<uint16_t>,6> instructions {{
            { 75, 47, 61, 53, 29 },
            { 97, 61, 53, 29, 13 },
            { 75, 29, 13 },
            { 75, 97, 47, 61, 53 },
            { 61, 13, 29 },
            { 97, 13, 75, 29, 47 }
        }};
    const auto& readInstructions = sut.getInstructions();
    BOOST_REQUIRE_EQUAL(instructions.size(), readInstructions.size());
    for(auto i { 0 }; i < instructions.size(); ++i) {
        BOOST_REQUIRE_EQUAL(instructions.at(i).size(), readInstructions.at(i).size());
        BOOST_CHECK(std::equal(instructions.at(i).begin(),
            instructions.at(i).end(),
            readInstructions.at(i).begin()));
    }
}

/*******************************************************************************
* @brief Check that the sum of instructions will be calculated to the expected
* amount.
*******************************************************************************/
BOOST_AUTO_TEST_CASE(TestSumCalculationForTestData) {
    constexpr uint32_t EXPECTED_SUM { 143 };
    const PrinterRuleset ruleset { inputFileName.data() };
    const PrinterSW software { inputFileName.data() };
    const auto calculatedSum = software.getSumOfCorrectInstuction(ruleset);
    BOOST_CHECK_EQUAL(EXPECTED_SUM, calculatedSum);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();