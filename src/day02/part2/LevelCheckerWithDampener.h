/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 02.12.2024
 *
 ******************************************************************************/
 
#ifndef LEVELCHECKERWITHDAMPENER_H_11264A54_A709_43C8_9E5A_E817E0AEA7AA
#define LEVELCHECKERWITHDAMPENER_H_11264A54_A709_43C8_9E5A_E817E0AEA7AA

#include <cstdint>
#include <string_view>
#include <vector>

/*******************************************************************************
 * @class LevelCheckerWithDampener
 * @brief Class that is used to check the levels of the provided report-data
 * if they are "safe to use".
 *
 * A Level is safe if the following two conditions are fulfilled:
 * 1) All element of the level are either increasing or decreasing
 * 2) The difference between two adjacent elements is smaller 3
 * OR a 1) or 2) are fullfilled if one element of the vector would be removed
 ******************************************************************************/
class LevelCheckerWithDampener {

    /***************************************************************************
     * @brief static variable that counts the amount of levels that are safe
     * from the input report data.
     **************************************************************************/
    static inline uint32_t amountOfSaveLevels { 0 };

public:

    [[nodiscard]] static uint32_t getAmountOfSafeLevels();
    static void calculateLevelSafety(std::string_view dataFile);

private:

    [[nodiscard]] static bool isLineSafe(
        const std::vector<uint8_t>& lineData);

};

#endif //LEVELCHECKERWITHDAMPENER_H_11264A54_A709_43C8_9E5A_E817E0AEA7AA
