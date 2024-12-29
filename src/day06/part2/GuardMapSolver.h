/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/
 
#ifndef GUARDMAPSOLVER_H_D3B7296A_5D84_4110_9CC9_D4543A2F8F1E
#define GUARDMAPSOLVER_H_D3B7296A_5D84_4110_9CC9_D4543A2F8F1E

#include <part2/GuardMapModified.h>

/*******************************************************************************
* @class GuardMapSolver
* @brief The idea behind the GuardMapSolver starts with the starting point to
* let the guard run through his route as before. But instead of just marking the
* areas on which the guard was walking on, one also remembers the direction the
* guard was headed to. One can use this information to find places for the
* obstacles that would create "future" walking paths that would end up
* in an already "used" field with the same direction --> This would create
* the loop. Checks only have to be done on an "obstacle hit".
*
* The implementation will try to spawn an obstacle on every position of the
* path before continuing to the next step. This will happen in a copy of
* the current map. In the copied map, the whole path including the obstical
* will be simulated to check if an endless loop can be created.
* - The existing path was reached again with the needed direction
*   --> Counts as correct solution
* - The path simulation runs out of the map --> Non-correct solution
* After this step, the copied map can be deleted, while the next step in the
* original map can be calculated.
*
* @note The path during the obstacle simulation has to be tracked aswell,
* because it is also possible that a loop emerges outside the
* original path.
*******************************************************************************/
class GuardMapSolver {

    /***************************************************************************
    * @brief Original map in which the steps of the guard are simulated.
    ***************************************************************************/
    GuardMapModified originalMap;

    /***************************************************************************
    * @brief temporary copy of the map in which the path with the artificial
    * obstacle will be simulated.
    ***************************************************************************/
    std::optional<GuardMapModified> obstacleSimulation { };

public:

    explicit GuardMapSolver(std::string_view inputDataFile);
    uint32_t findAllLoops();

private:
    void createCopyWithObstacle(const GuardModified::Coordinates &coordsOfObstacle);
    bool loopWasCreated();
    bool placementLegal(const GuardModified::Coordinates& coords) const;
    static void printProgressBar(size_t current, size_t total, size_t barWidth = 50);
};


#endif //GUARDMAPSOLVER_H_D3B7296A_5D84_4110_9CC9_D4543A2F8F1E
