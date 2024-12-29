/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/
 
#ifndef GUARDMAP_H_D3B7296A_5D84_4110_9CC9_D4543A2F8F1E
#define GUARDMAP_H_D3B7296A_5D84_4110_9CC9_D4543A2F8F1E

#include <cstdint>
#include <utility>
#include <vector>
#include <string_view>
#include "Guard.h"

class GuardMap {

public:

    using Coordinates = std::pair<uint16_t, uint16_t>;

    /***************************************************************************
    * @brief Helper class that determines the current status of a position on
    * the map.
    ***************************************************************************/
    enum class FieldStatus {
        /// Field is available and hasn't been checked yet
        FREE,
        /// Field is available and has been checked already
        CHECKED,
        /// Field is available, but an obstacle is on top of it
        OBSTACLE,
        /// Field doesn't exist
        DOESNT_EXIST
    };

private:

    /***************************************************************************
    * @brief Copy of the map that was provided by the input file
    ***************************************************************************/
    std::vector<std::vector<char>> mapLayout { };

    /***************************************************************************
    * @brief Guard that is walking on the map.
    ***************************************************************************/
    std::vector<Guard> guards { };

public:

    explicit GuardMap(std::string_view inputFileName);
    uint32_t simulateMovement();
    [[nodiscard]] FieldStatus getFieldStatus(const Coordinates& coord) const;
    void markFieldAsChecked(const Coordinates& coords);

protected:

    [[nodiscard]] const std::vector<std::vector<char>>& getMap() const { return mapLayout; };

};

#endif //GUARDMAP_H_D3B7296A_5D84_4110_9CC9_D4543A2F8F1E
