/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/
 
#ifndef GUARDMODIFIED_H_5987AE9B_85ED_4877_8F45_30407EB343B3
#define GUARDMODIFIED_H_5987AE9B_85ED_4877_8F45_30407EB343B3

#include <map>
#include <cstdint>
#include <utility>

class GuardMapModified;

/*******************************************************************************
* @class Guard
* @brief This class represent a guard and his movement on a map.
*******************************************************************************/
class GuardModified {

public:

    using Coordinates = std::pair<int32_t, int32_t>;

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

private:

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

    explicit GuardModified(Coordinates startPosition);
    void move(GuardMapModified& mapToCheck);
    bool insertObstacle(GuardMapModified& mapToModify) const;
    [[nodiscard]] bool isGuardActive() const;

private:
    void rotateDirection();

};

#endif //GUARDMODIFIED_H_5987AE9B_85ED_4877_8F45_30407EB343B3
