#Part 1
add_library(Day01-Part1 STATIC
        part1/DistanceCalculator.cpp
        part1/DistanceCalculator.h
        common/InputConverter.h
        common/InputConverter.cpp
        ../day04/part1/XMasSearch.h
)

target_include_directories(Day01-Part1 PUBLIC
    .
)

add_executable(Day01-Part1-Exe
        part1/main.cpp
)

target_link_libraries(Day01-Part1-Exe Day01-Part1)

# Part2
add_library(Day01-Part2 STATIC
    common/InputConverter.h
    common/InputConverter.cpp
    part2/SimilarityCalculator.h
    part2/SimilarityCalculator.cpp
)

target_include_directories(Day01-Part2 PUBLIC
    .
)

add_executable(Day01-Part2-Exe
    part2/main.cpp
)

target_link_libraries(Day01-Part2-Exe Day01-Part2)