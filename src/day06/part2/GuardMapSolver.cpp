/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/

#include "GuardMapSolver.h"

#include <algorithm>
#include <iostream>

/*******************************************************************************
* @brief With the call of this constructor, the GuardMapSolver will be applied
* to the data of the provided input file.
*
* @param inputDataFile name / path to the input data
*******************************************************************************/
GuardMapSolver::GuardMapSolver(const std::string_view inputDataFile) :
    originalMap { inputDataFile } {
    // Do the original walking route to get all positions which now need
    // to be checked with the obstacles
    while(this->originalMap.guard->isGuardActive()) {
        this->originalMap.guard->move(this->originalMap);
    }
}

/*******************************************************************************
* @brief For each checked tile of the path create a copy of the map, insert
* the obstacle and check if a loop has been created.
*******************************************************************************/
uint32_t GuardMapSolver::findAllLoops() {
    // Get the list with all the tiles to check
    const auto allPositionsToCheck = this->originalMap.checkedPositions;
    std::vector<GuardMapModified::Coordinates> obstaclePositions { };
    // The first position can be ignored, because it is not legal to
    // place an object right infront of the guard
    size_t elementsCheckedTotal { 0 };
    size_t elementsDoneSinceProgressUpdate { 0 };
    std::for_each(
        std::next(allPositionsToCheck.begin(), 1),
        allPositionsToCheck.cend(),
        [this, &obstaclePositions, &allPositionsToCheck,
            &elementsDoneSinceProgressUpdate, &elementsCheckedTotal] (
            const auto& positionsToCheck) {
            if(placementLegal(positionsToCheck.coord)) {
                createCopyWithObstacle(positionsToCheck.coord);
                if(this->loopWasCreated())
                    obstaclePositions.push_back(positionsToCheck.coord);
            }
            // Do some visualisation of the current progress
            constexpr size_t PROGRESS_REFRESH_RATE { 100 };
            elementsDoneSinceProgressUpdate++;
            elementsCheckedTotal++;
            if(elementsDoneSinceProgressUpdate >= PROGRESS_REFRESH_RATE) {
                GuardMapSolver::printProgressBar(elementsCheckedTotal,
                allPositionsToCheck.size());
                elementsDoneSinceProgressUpdate = 0;
            }
        }
    );
    // Create a new line to not override the progress bar
    GuardMapSolver::printProgressBar(1,1);
    std::cout << std::endl;
    // Remove duplicate positions
    std::sort(obstaclePositions.begin(), obstaclePositions.end());
    const auto last = std::unique(obstaclePositions.begin(), obstaclePositions.end());
    obstaclePositions.erase(last, obstaclePositions.end());
    return obstaclePositions.size();
}

/*******************************************************************************
* @brief Create a copy of the original map with its path and insert an
* artifical obstacle at the provided coordinates.
*
* @param coordsOfObstacle Coordinates on which the artificial obstacle shall be
* placed.
*******************************************************************************/
void GuardMapSolver::createCopyWithObstacle(
    const GuardModified::Coordinates& coordsOfObstacle) {
    this->obstacleSimulation.emplace(this->originalMap);
    this->obstacleSimulation->insertObstacle(coordsOfObstacle);
    this->obstacleSimulation->guard.emplace(this->obstacleSimulation->startPosition);
    this->obstacleSimulation->checkedPositions.clear();
}

/*******************************************************************************
* @brief Create a copy of the current map and check if emplacement of an
* obstacle in the front would create and enless loop for the guard.
*******************************************************************************/
bool GuardMapSolver::loopWasCreated() {
    bool loopCreated { false };
    do {
        this->obstacleSimulation->simulateNextStep();
        loopCreated = this->obstacleSimulation->wasLoopCreated();
    } while(not loopCreated and
        this->obstacleSimulation->guard->isGuardActive());
    return loopCreated;
}

/*******************************************************************************
* @brief Checks if the obstacle is allowed to be placed at the given coordinates
*
* @param coords coordinates to check for the obstacle placement
* @return true Obstacle can be placed at the coordinates
* @return false Illegal position for obstacle placement
*******************************************************************************/
bool GuardMapSolver::placementLegal(const GuardModified::Coordinates& coords) const {
    const auto startPos = this->originalMap.startPosition;
    // Check for start pos
    if(coords.first == startPos.first and coords.second == startPos.second)
        return false;
    const auto coordsOfFirstMove =
        std::make_pair(startPos.first - 1, startPos.second);
    if(coords.first == coordsOfFirstMove.first and
        coords.second == coordsOfFirstMove.second)
        return false;
    return true;
}

/*******************************************************************************
* @brief Prints a small progress bar which gives a quick overview how long the
* programm will need to finish its task.
*
* @param current Current amount of elements done
* @param total Total amount of elements to do
* @param barWidth Display width of the progress bar.
*******************************************************************************/
void GuardMapSolver::printProgressBar(const size_t current,
    const size_t total, const size_t barWidth) {
    // Calculate the percentage completed
    const float progress = static_cast<float>(current) / total;
    // Calculate the number of '#' to display in the progress bar
    const auto pos =
        static_cast<size_t>(static_cast<float>(barWidth) * progress);
    // Display the progress bar
    std::cout << "[";
    for (size_t i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "#";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(progress * 100.0) << "%\r";
    std::cout.flush();
}
