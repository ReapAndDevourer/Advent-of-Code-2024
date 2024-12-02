/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 02.12.2024
 *
 ******************************************************************************/
 
#ifndef LEVELCHECKER_H_086BB50A_B734_47CA_A616_EF482AB57680
#define LEVELCHECKER_H_086BB50A_B734_47CA_A616_EF482AB57680

#include <cstdint>
#include <string_view>
#include <vector>

/*******************************************************************************
 * @class LevelChecker
 * @brief Class that is used to check the levels of the provided report-data
 * if they are "safe to use".
 *
 * A Level is safe if the following two conditions are fulfilled:
 * 1) All element of the level are either increasing or decreasing
 * 2) The difference between two adjacent elements is smaller 3
 ******************************************************************************/
class LevelChecker {

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

#endif //LEVELCHECKER_H_086BB50A_B734_47CA_A616_EF482AB57680
