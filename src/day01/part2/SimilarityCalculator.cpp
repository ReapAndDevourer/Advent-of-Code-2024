/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 01.12.2024
 *
 ******************************************************************************/

#include "SimilarityCalculator.h"
#include <stdexcept>
#include <algorithm>
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
long calculateSimilarity(std::vector<int>& place1, std::vector<int>& place2) {
    long similarity = 0;
    if(place1.size() != place2.size())
        throw std::out_of_range {"Input-Lists have different sizes!"};
    std::sort(std::execution::unseq, place1.begin(), place1.end());
    std::sort(std::execution::unseq, place2.begin(), place2.end());
    // Now one has to get the amount of numbers for the given element of the
    // first dataset
    std::unordered_map<int, size_t> alreadyChecked { };
    std::for_each(place1.begin(), place1.end(),
    [&place2, &alreadyChecked, &similarity](const int& valueToLookup) {
        // Check if value has already been counted, if not, add to the map
        if(alreadyChecked.find(valueToLookup) == alreadyChecked.end()) {
            const size_t countedOccurences (
                std::count(place2.begin(),place2.end(), valueToLookup)
            );
            alreadyChecked.emplace(valueToLookup, countedOccurences);
        }
        // Calculate the value to add to similarit with value and occurences
        const size_t occurrences { alreadyChecked.find(valueToLookup)->second };
        similarity += static_cast<long>(valueToLookup * occurrences);
    });
    return similarity;
}