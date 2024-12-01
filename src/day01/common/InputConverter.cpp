/*******************************************************************************
 *
 * Author: Enrique Rodriguez
 * Datum: 01.12.2024
 *
 ******************************************************************************/

#include <fstream>
#include <sstream>
#include <vector>

/*******************************************************************************
 * @brief With this function one is able to extract input Data out of a given
 * file if the data is provided as 2 coloumn dataset in which the first set is
 * the location1-vector while the second is the location2-vector.
 *
 * @param inputDataFile Name of the file that is used for data-extraction
 * @return Vectors that contain the dataset.
 ******************************************************************************/
std::pair<std::vector<int>, std::vector<int>>
    convertInputData(const std::string_view inputDataFile) {
    std::fstream dataFile;
    dataFile.open(inputDataFile.data(), std::ios::in);
    if(not dataFile.is_open())
        throw std::invalid_argument{ "No Data-Set was provided under the given name!" };
    std::string lineString;
    std::vector<int> locations1 { };
    std::vector<int> locations2 { };
    while(std::getline(dataFile, lineString)) {
        std::istringstream lineData { lineString };
        // The string now contains "x y" --> With the >> Operator one can
        // extract the numbers
        int location1, location2;
        lineData >> location1 >> location2;
        locations1.push_back(location1);
        locations2.push_back(location2);
    }
    dataFile.close();
    return std::make_pair(std::move(locations1),std::move(locations2));
}