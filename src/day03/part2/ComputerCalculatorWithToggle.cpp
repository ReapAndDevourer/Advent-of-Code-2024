/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 03.12.2024
 *
 ******************************************************************************/

#include "ComputerCalculatorWithToggle.h"

#include <fstream>
#include <regex>
#include <vector>
#include <part1/ComputerCalculator.h>

using Comp = ComputerCalculatorWithToggle;

/*******************************************************************************
 * @brief Calculate the sum of the products that are provided by the corrupted
 * programm input.
 * @param inputFileName The file name of the input-data.
 * @return Sum of the legal multiply-operands.
 ******************************************************************************/
uint64_t Comp::calculateProgrammValue(
    const std::string_view inputFileName) {
    std::fstream inputFile;
    inputFile.open(inputFileName.data(), std::ios::in);
    if(not inputFile.is_open())
        throw std::invalid_argument(
            "No Input-Data provided under given name of test-file");
    std::string lineString;
    uint64_t sumOfMultiplications { 0 };
    ActivationMarkers activationMarkers {
        { 0, Mode::ACTIVATED }
    };
    while(std::getline(inputFile, lineString)) {
        // Find the activation markers for the line
        findNewLineMarkers(lineString, activationMarkers);
        // Calculate the multiplications if Mode is Mode::ACTIVATED
        sumOfMultiplications +=
            calculateLineValue(lineString, activationMarkers);
    }
    return sumOfMultiplications;
}

/*******************************************************************************
 * @brief With this function you can get the sum of the multiply-instructions
 * that are specified in a string-line of the corrupted programm.
 * The calculation of the products is also dependent on the last activation
 * mode that has been found inside the line.
 *
 * @param programmLine string with the corrupted instructions
 * @param activationMarkers positions of the keywords that toggle if the
 * calculations have to be done or not.
 * @return Sum of calculated multiply-instructions
 ******************************************************************************/
uint32_t Comp::calculateLineValue(
    const std::string& programmLine, const ActivationMarkers& activationMarkers) {
    // Step 1: Find part with "mul(" until ")" via regex
    auto mulInstructions = findMulInstructions(programmLine);
    // Step 2: Remove operands that are not fulfilling the wrong format
    removeIllegalOperands(mulInstructions);
    // Step 3: Remove all the operations, that are after a don't() keyword
    removeDeactivatedOperands(mulInstructions, activationMarkers);
    // Extract the operand of the remaining multiplication instructions
    uint32_t sumOfProducts { 0 };
    for(const auto& [ _,mulString] : mulInstructions) {
        const size_t commaPosition { mulString.find(',') };
        // Get the first and second operand of the multiplication
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
 * @brief Convert the input line into strings that contain possible operands
 * for the found mutiplication instruction
 * @param lineString String that containes the whole instruction line
 * @return Vector with all the instruction contents and their positions.
 ******************************************************************************/
Comp::InstructionsContent Comp::findMulInstructions(
    const std::string& lineString) {
    /*
     * mul\( --> Start with mul(
     * ([^)]*) --> Capture everything until )
     *      --> ( ) is the capturing group, [^)] --> match every char except )
     *      * --> Capture until closing, which is the next step
     * \) --> close with )
     */
    const std::regex pattern(R"(mul\(([^)]*)\))");
    std::smatch match { }; //Here all the matches will be set
    auto startPosition (lineString.cbegin());
    InstructionsContent mulInstructions {  };
    //Search the occurunces
    while(std::regex_search(
        startPosition, lineString.cend(), match, pattern)) {
        // Access first capute group of regex --> Is the part inside mul( )
        const auto absolutePosition {
            match.position() + std::distance(
                lineString.cbegin(), startPosition) };
        mulInstructions.emplace_back(absolutePosition, match[1].str());
        //Search from after mul( --> 4 signs after the mul(
        startPosition = std::next(match.prefix().second,4);
        }
    return mulInstructions;
}

/*******************************************************************************
 * @brief Find the "do()" and "don't()" markers inside the data
 * @param lineString String of the current line to check
 * @param markers map in which the markers are safed
 ******************************************************************************/
void Comp::findNewLineMarkers(
    const std::string& lineString, ActivationMarkers& markers) {
    const std::regex doPattern {"do\\(\\)"};
    const std::regex dontPattern {R"(don't\(\))"};

    if(markers.empty())
        markers.insert(std::make_pair(0, Mode::ACTIVATED));
    else {
        const auto [position, lastMode] = *markers.rbegin();
        markers.clear();
        markers.insert({ 0, lastMode });
    }
    std::smatch match;
    auto startPosition { lineString.cbegin() };
    while(std::regex_search(startPosition, lineString.cend(), match, doPattern)) {
        const auto absolutePosition {
            match.position() + std::distance(
                lineString.cbegin(), startPosition) };
        markers.insert(std::make_pair(absolutePosition, Mode::ACTIVATED));
        startPosition = match.suffix().first;
    }
    startPosition = lineString.cbegin();
    while(std::regex_search(startPosition, lineString.cend(), match, dontPattern)) {
        const auto absolutePosition {
            match.position() + std::distance(
                lineString.cbegin(), startPosition) };
        markers.insert(std::make_pair(absolutePosition, Mode::DEACTIVATED));
        startPosition = match.suffix().first;
    }
}

/*******************************************************************************
 * @brief Illegal operands will be filtered out of the vector, so they won't
 * be calculated in the next steps.
 * @param mulInstructions vector with the operands that have to be checked and
 * removed if necessary.
 ******************************************************************************/
void Comp::removeIllegalOperands(InstructionsContent& mulInstructions) {
    mulInstructions.erase(
        std::remove_if(mulInstructions.begin(), mulInstructions.end(),
        [](const auto& contentPair) {
            const auto& [_, contentString] = contentPair;
            // If size > 7 or any signs in the string is neither a number
            // nor a comma, remove the string out of the legal operands vector
            // Also remove the string if the operands are not between 1-3 digits
            if(contentString.size() > 7) return true;
            if(std::any_of(contentString.begin(), contentString.end(),
                [](const char c) { return not std::isdigit(c) and c != ','; }))
                return true;
            if(not correctDigitFormat(contentString)) return true;
            return false;
        }), mulInstructions.end());
}

/*******************************************************************************
 * @brief We use the position of the mul instructions and the positions of the
 * activationMarkers to remove all operations that are between don't() and do()
 * @param mulInstructions All instructions with their corresponding positions
 * @param activationMarkers All markers and their corresponding positions
 ******************************************************************************/
void Comp::removeDeactivatedOperands(
    InstructionsContent& mulInstructions,
    const ActivationMarkers& activationMarkers) {
    mulInstructions.erase(
        std::remove_if(mulInstructions.begin(), mulInstructions.end(),
        [&activationMarkers]
            (const std::pair<unsigned, std::string>& instructionPair) {
            const auto& [pos, _] = instructionPair;
            // Get the valid activation marker
            auto itToCheckMode = activationMarkers.upper_bound(pos);
            if(itToCheckMode != activationMarkers.begin())
                --itToCheckMode;
            return itToCheckMode->second == Mode::DEACTIVATED;
        }),
        mulInstructions.end());
}

/*******************************************************************************
 * @brief Check if the operands are the right amount of digits (1-3)
 * @param mulInstructions string with the operands, while operands are
 * separated by a comma.
 * @return true --> Operands are in range
 * @return false --> Illegal Operands
 ******************************************************************************/
bool Comp::correctDigitFormat(const std::string& mulInstructions) {
    std::istringstream dataStream { mulInstructions };
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



