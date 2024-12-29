/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/
 
#ifndef GUARDMAPMODIFIED_H_4A2476B8_93D9_4D56_911_BD44A63D2BF92
#define GUARDMAPMODIFIED_H_4A2476B8_93D9_4D56_911_BD44A63D2BF92

#include <cstdint>
#include <utility>
#include <vector>
#include <string_view>
#include <optional>
#include "GuardModified.h"

/*******************************************************************************
* @class GuardMapModified
* @brief This class is an abstraction off a map on which a guard is doing his
* patrol.
*******************************************************************************/
class GuardMapModified {

friend class GuardMapSolver;

public:

    using Coordinates = std::pair<uint16_t, uint16_t>;

    struct FieldInformation {
        Coordinates coord;
        GuardModified::Direction direction;

        FieldInformation(const Coordinates& coord, const GuardModified::Direction dir) :
        coord { coord }, direction { dir } { }

        bool operator==(const FieldInformation& other) const {
            return coord.first == other.coord.first and
                coord.second == other.coord.second and
                direction == other.direction;
        }
    };

    /***************************************************************************
    * @brief Helper class that determines the current status of a position on
    * the map.
    ***************************************************************************/
    enum class FieldStatus {
        /// Field is available
        USEABLE,
        /// Field is available, but an obstacle is on top of it
        OBSTACLE,
        /// Field doesn't exist
        DOESNT_EXIST
    };

protected:

    /***************************************************************************
    * @brief Copy of the map that was provided by the input file
    ***************************************************************************/
    std::vector<std::vector<char>> mapLayout { };

    /***************************************************************************
    * @brief This info needs to be safed because it is not allowed that an
    * obstacle is placed directly infront or ontop of the starting position
    * of the guard. So even tho a loop would be created when placing an obstacle
    * there, it cant be counted as sucessful loop.
    ***************************************************************************/
    std::pair<uint32_t, uint32_t> startPosition;

    /***************************************************************************
    * @brief Vektor which contains all fields on which the guard was walking on
    * including the direction he was walking to when being on the field.
    ***************************************************************************/
    std::vector<FieldInformation> checkedPositions { };

    /***************************************************************************
    * @brief Guard that is walking on the map.
    ***************************************************************************/
    std::optional<GuardModified> guard { };

public:

    explicit GuardMapModified(std::string_view inputFileName);
    void simulateNextStep();
    [[nodiscard]] FieldStatus getFieldStatus(const Coordinates& coord) const;
    void markFieldAsChecked(const Coordinates& coords,
        GuardModified::Direction direction);
    bool wasLoopCreated();
    void insertObstacle(const Coordinates& coords);

protected:

    [[nodiscard]] const std::vector<std::vector<char>>& getMap() const { return mapLayout; };

};


#endif //GUARDMAPMODIFIED_H_4A2476B8_93D9_4D56_911_BD44A63D2BF92
