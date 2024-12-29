/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/

#include "GuardMapModified.h"
#include "GuardModified.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <iostream>

/*******************************************************************************
* @brief Create a guard map out of the data of the input file.
*
* @param inputFileName Path to the file with input data.
*******************************************************************************/
GuardMapModified::GuardMapModified(std::string_view inputFileName) {
    std::ifstream inputFile { inputFileName.data() };
    if(not inputFile.is_open())
        throw std::invalid_argument { "No input data in given file path!" };
    std::string inputLine;
    while(std::getline(inputFile, inputLine)) {
        this->mapLayout.emplace_back();
        for(auto& fieldInfo : inputLine) {
            if(fieldInfo == '^') {
                fieldInfo = 'X';
                this->guard.emplace(
                    Coordinates {
                        this->mapLayout.size() -1,
                        this->mapLayout.back().size()});
                this->startPosition = std::make_pair(
                        this->mapLayout.size() - 1,
                        this->mapLayout.back().size());
            }
            this->mapLayout.back().emplace_back(fieldInfo);
        }
    }
}

/*******************************************************************************
* @brief Get the status of the provided coordinates.
*
* @param coord Coordiantes from which the status on the map is asked.
*******************************************************************************/
GuardMapModified::FieldStatus GuardMapModified::getFieldStatus(
    const Coordinates& coord) const {
    if(coord.first >= this->mapLayout.size())
        return FieldStatus::DOESNT_EXIST;
    if(coord.second >= this->mapLayout.at(0).size())
        return FieldStatus::DOESNT_EXIST;
    switch(this->mapLayout.at(coord.first).at(coord.second)) {
        case 'O': [[fallthrough]];
        case '#': return FieldStatus::OBSTACLE;
        default: return FieldStatus::USEABLE;
    }
}

/*******************************************************************************
* @brief With this methode one can artificially insert an obstacle into the
* map.
*******************************************************************************/
void GuardMapModified::insertObstacle(const Coordinates& coords) {
    // Check that the obstacle would be neither on the start position nor the
    // first step of the soldier.
    if( (coords.first == this->startPosition.first or
        coords.first == this->startPosition.first -1) and
        coords.second == this->startPosition.second) return;
    this->mapLayout.at(coords.first).at(coords.second) = 'O';
}

/*******************************************************************************
* @brief Mark the given coordinate on the map with direction.
*
* @param coords Coordinates to mark.
* @param dir Direction which the guard is using at this position.
*******************************************************************************/
void GuardMapModified::markFieldAsChecked(
    const Coordinates &coords, const GuardModified::Direction dir) {
    char dirToSet = 0;
    switch(dir) {
        case GuardModified::Direction::LEFT: dirToSet = 'L'; break;
        case GuardModified::Direction::RIGHT: dirToSet = 'R'; break;
        case GuardModified::Direction::UPWARDS: dirToSet = 'U'; break;
        case GuardModified::Direction::DOWNWARDS: dirToSet = 'D';
    }
    this->checkedPositions.emplace_back(coords, dir);
    this->mapLayout.at(coords.first).at(coords.second) = dirToSet;
}

/*******************************************************************************
* @brief Simulate another step of the guard on the map
*******************************************************************************/
void GuardMapModified::simulateNextStep() {
    guard->move(*this);
}

/*******************************************************************************
* @brief Check if the last step of the simulated guard path equals one of the
* steps already made --> If yes, a loop has been created.
*
* @return true Loop has been created
* @return false Loop hasn't been created
*******************************************************************************/
bool GuardMapModified::wasLoopCreated() {
    const auto& lastElement = this->checkedPositions.back();
    return std::any_of(
        this->checkedPositions.begin(),
        this->checkedPositions.end() - 1,
        [&lastElement](const FieldInformation& element) {
            return element == lastElement;
        });
}

