/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 03.12.2024
 *
 ******************************************************************************/

#include "ComputerCalculator.h"

#include <fstream>
#include <regex>
#include <vector>

/*******************************************************************************
 * @brief Calculate the sum of the products that are provided by the corrupted
 * programm input.
 * @param inputFileName The file name of the input-data.
 * @return Sum of the legal multiply-operands.
 ******************************************************************************/
uint64_t ComputerCalculator::calculateProgrammValue(
    const std::string_view inputFileName) {
    std::fstream inputFile;
    inputFile.open(inputFileName.data(), std::ios::in);
    if(not inputFile.is_open())
        throw std::invalid_argument(
            "No Input-Data provided under given name of test-file");
    std::string lineString;
    uint64_t sumOfMultiplications { 0 };
    while(std::getline(inputFile, lineString))
        sumOfMultiplications += ComputerCalculator::calculateLineValue(lineString);
    return sumOfMultiplications;
}


/*******************************************************************************
 * @brief With this function you can get the sum of the multiply-instructions
 * that are specified in a string-line of the corrupted programm.
 * @param programmLine string with the corrupted instructions
 * @return Sum of calculated multiply-instructions
 ******************************************************************************/
uint32_t ComputerCalculator::calculateLineValue(
    const std::string& programmLine) {

    // Part 1: Find part with "mul(" until ")" via regex
    /*
     * mul\( --> Start with mul(
     * ([^)]*) --> Capture everything until )
     *      --> ( ) is the capturing group, [^)] --> match every char except )
     *      * --> Capture until closing, which is the next step
     * \) --> close with )
     */
    const std::regex pattern(R"(mul\(([^)]*)\))");
    std::smatch match { }; //Here all the matches will be set
    auto startPosition (programmLine.cbegin());
    std::vector<std::string> mulInstructions {  };
    //Search the occurunces
    while(std::regex_search(
        startPosition, programmLine.cend(), match, pattern)) {
        // Access first capute group of regex --> Is the part inside mul( )
        mulInstructions.push_back(match[1].str());
        //Search from after mul( --> 4 signs after the mul(
        startPosition = std::next(match.prefix().second,4);
    }
    ComputerCalculator::removeIllegalOperands(mulInstructions);
    //Now one can calculate the sum
    uint32_t sumOfProducts { 0 };
    for(const std::string& mulString : mulInstructions) {
        const size_t commaPosition { mulString.find(',') };
        const uint16_t firstOperand { static_cast<uint16_t>(
            std::stoi(mulString.substr(0, commaPosition)))
        };
        const uint16_t secondOperand { static_cast<uint16_t>(
            std::stoi(mulString.substr( commaPosition + 1)))
        };
        sumOfProducts += firstOperand * secondOperand;
    }
    return sumOfProducts;
}

/*******************************************************************************
 * @brief Illegal operands will be filtered out of the vector, so they won't
 * be calculated in the next steps.
 * @param mulStrings vector with the operands that have to be checked and
 * removed if necessary.
 ******************************************************************************/
void ComputerCalculator::removeIllegalOperands(
    std::vector<std::string>& mulStrings) {
    mulStrings.erase(
        std::remove_if(mulStrings.begin(), mulStrings.end(),
        [](const std::string& contentString) {
            // If size > 7 or any signs in the string is neither a number
            // nor a comma, remove the string out of the legal operands vector
            // Also remove the string if the operands are not between 1-3 digits
            if(contentString.size() > 7) return true;
            if(std::any_of(contentString.begin(), contentString.end(),
                [](const char c) { return not std::isdigit(c) and c != ','; }))
                return true;
            if(not correctDigitFormat(contentString)) return true;
            return false;
        }), mulStrings.end());
}

/*******************************************************************************
 * @brief Check if the operands are the right amount of digits (1-3)
 * @param mulString string with the operands, while operands are seperated by ,
 * @return true --> Operands are in range
 * @return false --> Illegal Operands
 ******************************************************************************/
bool ComputerCalculator::correctDigitFormat(const std::string& mulString) {
    std::istringstream dataStream { mulString };
    std::string operand;
    size_t operandsChecked { 0 };
    while(std::getline(dataStream, operand, ',')) {
        operandsChecked++;
        // Check if format XXX,YYY is fulfilled
        if(operand.empty() or operand.size() > 3 or
            not std::all_of(operand.begin(), operand.end(), ::isdigit))
            return false;
    }
    return operandsChecked == 2;
}


