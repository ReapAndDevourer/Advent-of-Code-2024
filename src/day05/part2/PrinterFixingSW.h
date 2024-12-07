/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 05.12.24
 *
 ******************************************************************************/

#ifndef PRINTERSW_H_1EDF2738_0DF6_4E0B_9263_73EE4A7CAD46
#define PRINTERSW_H_1EDF2738_0DF6_4E0B_9263_73EE4A7CAD46

#include <string_view>
#include <vector>
#include <cstdint>
#include "part2/PrinterRulesetWithCorrection.h"

/*******************************************************************************
* @class PrinterFixingSW
* @brief Abstraction of a printer SW that reads instructions from an input file
* and checks if the contained print instructions are correct or not.
*******************************************************************************/
class PrinterFixingSW {

    /***************************************************************************
    * @brief Print-instructions that should be checked for correctness.
    ***************************************************************************/
    std::vector<std::vector<uint16_t>> printInstructions { };

public:

    explicit PrinterFixingSW(std::string_view inputFileName);
    [[nodiscard]] uint32_t getSumOfCorrectedInstructions(
        const PrinterRulesetWithCorrection& rulesetToApply);

protected:
    /***************************************************************************
    * @brief Gibt die eingelesen Instructions zurück.
    ***************************************************************************/
    [[nodiscard]] const std::vector<std::vector<uint16_t>>& getInstructions() const {
        return this->printInstructions;
    }
};

#endif //PRINTERSW_H_1EDF2738_0DF6_4E0B_9263_73EE4A7CAD46
