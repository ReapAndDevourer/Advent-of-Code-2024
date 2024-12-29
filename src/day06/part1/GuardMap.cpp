/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 07.12.24
 *
 ******************************************************************************/

#include "GuardMap.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <iostream>

/*******************************************************************************
* @brief Create a guard map out of the data of the input file.
*
* @param inputFileName Path to the file with input data.
*******************************************************************************/
GuardMap::GuardMap(std::string_view inputFileName) {
    std::ifstream inputFile { inputFileName.data() };
    if(not inputFile.is_open())
        throw std::invalid_argument { "No input data in given file path!" };
    std::string inputLine;
    while(std::getline(inputFile, inputLine)) {
        this->mapLayout.emplace_back();
        for(auto& fieldInfo : inputLine) {
            if(fieldInfo == '^') {
                fieldInfo = 'X';
                this->guards.emplace_back(
                    Coordinates {
                        this->mapLayout.size() -1,
                        this->mapLayout.back().size()});
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
GuardMap::FieldStatus GuardMap::getFieldStatus(const Coordinates& coord) const {
    if(coord.first >= this->mapLayout.size())
        return FieldStatus::DOESNT_EXIST;
    if(coord.second >= this->mapLayout.at(0).size())
        return FieldStatus::DOESNT_EXIST;
    switch(this->mapLayout.at(coord.first).at(coord.second)) {
        case '.': return FieldStatus::FREE;
        case 'X': return FieldStatus::CHECKED;
        case '#': return FieldStatus::OBSTACLE;
        default: throw std::invalid_argument { "Unknown field value on map!" };
    }
}

/*******************************************************************************
* @brief Simulate the movement of the guards on the map.
*******************************************************************************/
uint32_t GuardMap::simulateMovement() {
    while(std::any_of(this->guards.begin(), this->guards.end(),
        [] (const Guard& guard) { return guard.isGuardActive(); })) {
        std::for_each(this->guards.begin(), this->guards.end(),
            [this](Guard& guard) {
                if(guard.isGuardActive()) {
                    guard.move(*this);
                }
            });
    }
    uint32_t checkedFields { 0 };
    for(const auto& mapLine : this->mapLayout)
        for(const auto fieldValue : mapLine)
            if(fieldValue == 'X') checkedFields++;
    return checkedFields;
}

/*******************************************************************************
* @brief Mark the given coordinate on the map as checked
*
* @param coords Coordinates to mark.
*******************************************************************************/
void GuardMap::markFieldAsChecked(const Coordinates &coords) {
    this->mapLayout.at(coords.first).at(coords.second) = 'X';
}




