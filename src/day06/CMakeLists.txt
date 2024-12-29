#Part 1
add_library(Day06-Part1 STATIC
    part1/Guard.h
    part1/Guard.cpp
    part1/GuardMap.h
    part1/GuardMap.cpp
)

target_include_directories(Day06-Part1 PUBLIC
        .
)

add_executable(Day06-Part1-Exe
        part1/main.cpp
)

target_link_libraries(Day06-Part1-Exe Day06-Part1)

# Part2
add_library(Day06-Part2 STATIC
    part2/GuardModified.h
    part2/GuardModified.cpp
    part2/GuardMapModified.h
    part2/GuardMapModified.cpp
    part2/GuardMapSolver.h
    part2/GuardMapSolver.cpp
)

target_include_directories(Day06-Part2 PUBLIC
        .
)

add_executable(Day06-Part2-Exe
        part2/main.cpp
)

target_link_libraries(Day06-Part2-Exe Day06-Part2)