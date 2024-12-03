/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 03.12.2024
 *
 ******************************************************************************/
 
#ifndef COMPUTERCALCULATOR_H_3D3422F0_D6CF_4EB9_A32C_1788C76212F7
#define COMPUTERCALCULATOR_H_3D3422F0_D6CF_4EB9_A32C_1788C76212F7

#include <cstdint>
#include <string>
#include <vector>
#include <map>

/*******************************************************************************
 * @class ComputerCalculatorWithToggle
 * @brief With this little class you can decypher a corrupted computer programm
 * to calculate the wanted sum of multiplies.
 *
 * To remove the corrupted Parts of the programm, we have to determine which
 * parts of the programm code are correct. Following conditions have to be
 * fulfilled:
 * - The Operation needs to start with "mul("
 * - Immerdiately after, a 1-3 digit number has to follow
 * - with a "," immediately afterward - no whitespaces inbetween are allowed.
 * - anoter 1-2 digit number has to follow immediately
 * - the sequence has to be close with a ")"
 *
 * --> The programm will do the following
 * --> Extract sequence after "mul(" --> until ")"
 * --> Check if extracted part > 7 --> immediately skip
 * --> Check that only digits and , are inside the extracted part
 * --> Split into two number strings with position of ,
 * --> Check that both numbers are 1-3 digits big
 * --> Calculate the value
 *
 * In addition to the part1 variant, the last activation mode found inside the
 * list will be used aswell to determine if a multiplication instruction has
 * to be executed or not.
 ******************************************************************************/
class ComputerCalculatorWithToggle {

public:

    /***************************************************************************
     * @class Mode
     * @brieg Helping class that marks if following mul-Instructions should be
     * calculated or not.
     **************************************************************************/
    enum class Mode {
        ACTIVATED,
        DEACTIVATED
    };

private:

    using ActivationMarkers = std::map<uint32_t, Mode>;
    using InstructionsContent = std::vector<std::pair<uint32_t, std::string>>;

public:

    [[nodiscard]] static uint64_t calculateProgrammValue(
         std::string_view inputFileName);
    [[nodiscard]] static uint32_t calculateLineValue(
        const std::string& programmLine,
        const ActivationMarkers& activationMarkers);
    static void findNewLineMarkers(
        const std::string& lineString, ActivationMarkers& markers);

private:

    static InstructionsContent findMulInstructions(const std::string& lineString);
    static void removeIllegalOperands(InstructionsContent& mulInstructions);
    static void removeDeactivatedOperands(
        InstructionsContent& mulInstructions,
        const ActivationMarkers& activationMarkers);
    static bool correctDigitFormat(const std::string& mulInstructions);

};

#endif //COMPUTERCALCULATOR_H_3D3422F0_D6CF_4EB9_A32C_1788C76212F7
