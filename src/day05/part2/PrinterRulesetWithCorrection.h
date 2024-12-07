/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 05.12.24
 *
 ******************************************************************************/
 
#ifndef PRINTERRULESET_H_0F694FFA_EA9F_4A52_8EA0_A6B9D71FD51C
#define PRINTERRULESET_H_0F694FFA_EA9F_4A52_8EA0_A6B9D71FD51C

#include <unordered_map>
#include <cstdint>
#include <vector>
#include <string_view>

/*******************************************************************************
* @class PrinterRuleset
* @brief This class converts input data into a ruleset that can be applied to
* the printer software of the superior application.
*******************************************************************************/
class PrinterRulesetWithCorrection {

public:

    using Ruleset = std::unordered_map<uint16_t, std::vector<uint16_t>>;

protected:

    /***************************************************************************
    * @brief Combined containers whoms elements represents the ruleset that
    * was provided from the file input.
    ***************************************************************************/
    Ruleset rules { };

public:

    explicit PrinterRulesetWithCorrection(std::string_view inputFileName);
    bool fixInstructionIfNeeded(std::vector<uint16_t>& printInstruction,
        bool wasChanged = false) const;
};

#endif //PRINTERRULESET_H_0F694FFA_EA9F_4A52_8EA0_A6B9D71FD51C

