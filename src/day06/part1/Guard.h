/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/
 
#ifndef GUARD_H_05B7366C_5F46_4AB9_B675_CB79A7C01B24
#define GUARD_H_05B7366C_5F46_4AB9_B675_CB79A7C01B24

#include <map>
#include <cstdint>
#include <utility>

class GuardMap;

/*******************************************************************************
* @class Guard
* @brief This class represent a guard and his movement on a map.
*******************************************************************************/
class Guard {

public:

    using Coordinates = std::pair<int32_t, int32_t>;

private:

    /***************************************************************************
    * @brief Helper-class that defines in which way the guard can move on the
    * provided map.
    ***************************************************************************/
    enum class Direction {
        UPWARDS,
        RIGHT,
        DOWNWARDS,
        LEFT
    };

    /***************************************************************************
    * @brief Lookup-Table in which directions the guard will make its movements
    * depending on the current direction he is heading to.
    ***************************************************************************/
    const static inline std::map<Direction, Coordinates> movement {
        {Direction::UPWARDS, {0, -1}},
        {Direction::RIGHT, {1, 0}},
        {Direction::DOWNWARDS, {0, 1}},
        {Direction::LEFT, {-1, 0}}
    };

    /***************************************************************************
    * @brief Current position of the guard on the map
    ***************************************************************************/
    Coordinates currentPosition;

    /***************************************************************************
    * @brief current direction of the guard
    ***************************************************************************/
    Direction currentDirection { Direction::UPWARDS };

    /***************************************************************************
    * @brief flag if the guard is still active or not
    ***************************************************************************/
    bool activeDuty { true };

public:

    explicit Guard(Coordinates startPosition);
    void move(GuardMap& mapToCheck);
    [[nodiscard]] bool isGuardActive() const;

private:
    void rotateDirection();

};

#endif //GUARD_H_05B7366C_5F46_4AB9_B675_CB79A7C01B24
