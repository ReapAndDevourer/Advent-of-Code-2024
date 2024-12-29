/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/

#include "Guard.h"
#include "GuardMap.h"
#include <stdexcept>
#include <utility>

/*******************************************************************************
* @brief Create a guard at the current position.
*******************************************************************************/
Guard::Guard(Coordinates startPosition) :
    currentPosition {std::move( startPosition )} { }

/*******************************************************************************
* @brief Simulate one movement of the guard
*
* @param mapToCheck Map on which the guard is moving on.
*******************************************************************************/
void Guard::move(GuardMap &mapToCheck) {
    auto [xPos, yPos] = movement.at(this->currentDirection);
    const auto newPosition = Coordinates {
        this->currentPosition.first + yPos,
        this->currentPosition.second + xPos };
    switch(mapToCheck.getFieldStatus(newPosition)) {
        case GuardMap::FieldStatus::DOESNT_EXIST:
            this->activeDuty = false;
            this->currentPosition = newPosition;
            break;
        case GuardMap::FieldStatus::FREE:
            [[fallthrough]];
        case GuardMap::FieldStatus::CHECKED:
            this->currentPosition = newPosition;
            mapToCheck.markFieldAsChecked(newPosition);
            break;
        case GuardMap::FieldStatus::OBSTACLE:
            this->rotateDirection();
            this->move(mapToCheck);
            break;
        default:
            throw std::invalid_argument { "Unknown Field-State was given to guard!" };
    }
}

/*******************************************************************************
* @brief Update the guard direction after running into an obstacle.
*******************************************************************************/
void Guard::rotateDirection() {
    switch(this->currentDirection) {
        case Direction::UPWARDS: this->currentDirection = Direction::RIGHT; return;
        case Direction::RIGHT: this->currentDirection = Direction::DOWNWARDS; return;
        case Direction::DOWNWARDS: this->currentDirection = Direction::LEFT; return;
        case Direction::LEFT: this->currentDirection = Direction::UPWARDS;
    }
}

/*******************************************************************************
* @brief Check if a guard is still active or not.
*
* @return true Guard is active
* @return false Guard is non-active
*******************************************************************************/
bool Guard::isGuardActive() const {
    return this->activeDuty;
}



