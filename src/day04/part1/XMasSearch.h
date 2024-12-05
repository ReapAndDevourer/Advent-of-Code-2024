/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 04.12.24
 *
 ******************************************************************************/
 
#ifndef XMASSEARCH_H_E47E8711_6D00_45B6_A3DD_F63F0DA62005
#define XMASSEARCH_H_E47E8711_6D00_45B6_A3DD_F63F0DA62005

#include <array>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <string_view>
#include <atomic>

/*******************************************************************************
* @class XMasSearch
* @brief This class can be used to determine the amount of occurunces of
* a provided Keyword. All directions listed inside
* @ref XMasSearch::CheckDirection will be checked for the mathing keyword.
*******************************************************************************/
class XMasSearch {

public:

    using Coordinates = std::pair<uint16_t, uint16_t>;

private:

    /***************************************************************************
    * @brief This container contains all the start positions from whom the
    * search for the matches will be started from. The position will be set if
    * the first character of the keyword is found inside the data input.
    ***************************************************************************/
    std::vector<Coordinates> startCoordinates { };

public:

    /***************************************************************************
    * @brief Keyword that has to be found as char-array
    ***************************************************************************/
    static constexpr std::array<char, 4> KEYWORD { 'X', 'M', 'A', 'S' };

    static_assert(not KEYWORD.empty(), "Keyword can't be empty!");

    /***************************************************************************
    * @brief Contains the input data.
    ***************************************************************************/
    const std::vector<std::vector<char>> inputData { };

    /***************************************************************************
    * @class CheckDirection
    * @brief All the different variants for which the Check-Word can exist.
    ***************************************************************************/
    enum class CheckDirection {
        /// From left to right
        NORMAL,
        /// From right to left
        REVERSE,
        /// Top to bottom
        TOP_DOWN,
        /// Bottom to top
        BOTTOM_UP,
        /// Bottom right to top left
        DIAGONAL_LEFT,
        /// Top left to bottom rigth
        DIAGONAL_LEFT_REVERSE,
        /// Bottom left to top right
        DIAGONAL_RIGHT,
        /// Top right to bottom left
        DIAGONAL_RIGHT_REVERSE,
    };

    /***************************************************************************
    * @brief Map with the changes of X and Y position that have to be made from
    * one character to the next if the used CheckDirection has to be checked.
    *
    * First Parameter: Mode to use
    * Second Parameter: first: Row-Adjustment second: Column-Adjustment
    ***************************************************************************/
    static inline const std::unordered_map<
        CheckDirection, std::pair<int8_t, int8_t>> stepInstructions {
            {CheckDirection::NORMAL, { 1, 0 }},
            {CheckDirection::REVERSE, { -1, 0 }},
            {CheckDirection::TOP_DOWN, { 0, 1 }},
            {CheckDirection::BOTTOM_UP, { 0, -1 }},
            {CheckDirection::DIAGONAL_LEFT, { -1, -1 }},
            {CheckDirection::DIAGONAL_LEFT_REVERSE, { 1, 1 }},
            {CheckDirection::DIAGONAL_RIGHT, { 1, -1 }},
            {CheckDirection::DIAGONAL_RIGHT_REVERSE, { -1, 1 }}
    };

    explicit XMasSearch(std::string_view inputFileName);

    [[nodiscard]] uint16_t findAllOccurences() const;


protected:


    /***************************************************************************
    * @brief Getter-methode to retreive the found start coordinates.s
    ***************************************************************************/
    [[nodiscard]] const std::vector<Coordinates>& getStartCoordinates() const {
        return this->startCoordinates;
    }

    [[nodiscard]] uint16_t findOccurences(CheckDirection mode) const;

private:
    void findStartCoordinates();
    [[nodiscard]] bool doesFieldExist(Coordinates coord) const;
    [[nodiscard]] bool checkForMatch(const Coordinates& startCoordinates,
        int8_t xDeriv, int8_t yDeriv) const;
};

#endif //XMASSEARCH_H_E47E8711_6D00_45B6_A3DD_F63F0DA62005
