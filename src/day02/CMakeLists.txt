#Part 1

add_library(Day02-Part1 STATIC
        part1/LevelChecker.cpp
)

target_include_directories(Day02-Part1 PUBLIC
        .
)

add_executable(Day02-Part1-Exe
        part1/main.cpp
)

target_link_libraries(Day02-Part1-Exe Day02-Part1)

# Part2

add_library(Day02-Part2 STATIC
    part2/Empty.cpp
)

target_include_directories(Day02-Part2 PUBLIC
        .
)

add_executable(Day02-Part2-Exe
        part2/main.cpp
)

target_link_libraries(Day02-Part2-Exe Day02-Part2)