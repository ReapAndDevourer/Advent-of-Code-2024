/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/

#include "GuardModified.h"
#include "GuardMapModified.h"
#include <stdexcept>
#include <utility>

/*******************************************************************************
* @brief Create a guard at the current position.
*******************************************************************************/
GuardModified::GuardModified(Coordinates startPosition) :
    currentPosition {std::move( startPosition )} { }

/*******************************************************************************
* @brief Simulate one movement of the guard
*
* @param mapToCheck Map on which the guard is moving on.
*******************************************************************************/
void GuardModified::move(GuardMapModified &mapToCheck) {
    auto [xPos, yPos] = movement.at(this->currentDirection);
    const auto newPosition = Coordinates {
        this->currentPosition.first + yPos,
        this->currentPosition.second + xPos };
    switch(mapToCheck.getFieldStatus(newPosition)) {
        case GuardMapModified::FieldStatus::DOESNT_EXIST:
            this->activeDuty = false;
            this->currentPosition = newPosition;
            break;
        case GuardMapModified::FieldStatus::USEABLE:
            this->currentPosition = newPosition;
            mapToCheck.markFieldAsChecked(newPosition, this->currentDirection);
            break;
        case GuardMapModified::FieldStatus::OBSTACLE:
            this->rotateDirection();
            break;
        default:
            throw std::invalid_argument { "Unknown Field-State was given to guard!" };
    }
}

/*******************************************************************************
* @brief Calling this function will try to insert an obstacle directly infront
* of the next step of the guard.
*
* @return true Obstacle has been inserted
* @return false Obstacle couldn't be inserted
*******************************************************************************/
bool GuardModified::insertObstacle(GuardMapModified &mapToModify) const {
    auto [xPos, yPos] = movement.at(this->currentDirection);
    const auto obstaclePos = Coordinates {
        this->currentPosition.first + yPos,
        this->currentPosition.second + xPos };
    switch(mapToModify.getFieldStatus(obstaclePos)) {
        case GuardMapModified::FieldStatus::OBSTACLE: [[fallthrough]];
        case GuardMapModified::FieldStatus::DOESNT_EXIST:
            return false;
        case GuardMapModified::FieldStatus::USEABLE:
            mapToModify.insertObstacle(obstaclePos);
            return true;
        default:
            throw std::invalid_argument { "Unknown Field-State was given to guard!" };
    }
}


/*******************************************************************************
* @brief Update the guard direction after running into an obstacle.
*******************************************************************************/
void GuardModified::rotateDirection() {
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
bool GuardModified::isGuardActive() const {
    return this->activeDuty;
}