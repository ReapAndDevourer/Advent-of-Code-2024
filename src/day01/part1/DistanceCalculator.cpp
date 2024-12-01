/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 01.12.2024
 *
 ******************************************************************************/

#include <algorithm>
#include "DistanceCalculator.h"
#include <stdexcept>
#include <execution>

/*******************************************************************************
 * @brief With the call of this function we can calculate the distance of
 * all places given in list 1 vs list 2. The distance is calculated by adding
 * the difference between the smallest element of both lists, the 2nd smallest
 * elements of the lists ...(repeat for all index).
 *
 *
 * @param place1 List with the first set of location-ids
 * @param place2 List with the second set of location-ids
 * @return Distance between the list-locations
 ******************************************************************************/
long calculateDistance(std::vector<int>& place1, std::vector<int>& place2) {
    long distance = 0;
    if(place1.size() != place2.size())
        throw std::out_of_range {"Input-Lists have different sizes!"};
    std::sort(std::execution::unseq, place1.begin(), place1.end());
    std::sort(std::execution::unseq, place2.begin(), place2.end());
    for(size_t i = 0; i < place1.size(); i++) {
        distance += std::abs(place1[i] - place2[i]);
    }
    return distance;
}
