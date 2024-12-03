#Part 1
add_library(Day03-Part1 STATIC
        part1/ComputerCalculator.cpp
)

target_include_directories(Day03-Part1 PUBLIC
        .
)

add_executable(Day03-Part1-Exe
        part1/main.cpp
)

target_link_libraries(Day03-Part1-Exe Day03-Part1)

# Part2
add_library(Day03-Part2 STATIC
        part2/ComputerCalculatorWithToggle.cpp
)

target_include_directories(Day03-Part2 PUBLIC
        .
)

add_executable(Day03-Part2-Exe
        part2/main.cpp
)

target_link_libraries(Day03-Part2-Exe Day03-Part2)