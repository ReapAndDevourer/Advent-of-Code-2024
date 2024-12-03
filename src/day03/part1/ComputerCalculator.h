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

/*******************************************************************************
 * @class ComputerCalculator
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
 ******************************************************************************/
class ComputerCalculator {

public:

    [[nodiscard]] static uint64_t calculateProgrammValue(std::string_view inputFileName);
    [[nodiscard]] static uint32_t calculateLineValue(const std::string& programmLine);

private:

    static void removeIllegalOperands(std::vector<std::string>& mulStrings);
    static bool correctDigitFormat(const std::string& mulString);
};

#endif //COMPUTERCALCULATOR_H_3D3422F0_D6CF_4EB9_A32C_1788C76212F7
