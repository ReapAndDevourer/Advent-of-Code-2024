#Part 1
add_executable(Day01-Part1-Test
        part1/TestDistanceCalculator.cpp
        ../TestMain.cpp
)

target_link_libraries(Day01-Part1-Test PRIVATE
    Day01-Part1
    Boost::unit_test_framework
)

#Part 2
add_executable(Day01-Part2-Test
        part2/TestSimilarityCalculator.cpp
        ../TestMain.cpp
)

target_link_libraries(Day01-Part2-Test PRIVATE
    Day01-Part2
    Boost::unit_test_framework
)

# Combine sources and include paths
set(Day01-Sources
        $<TARGET_PROPERTY:Day01-Part1-Test,SOURCES>
        $<TARGET_PROPERTY:Day01-Part2-Test,SOURCES>
)

set(Day01-Includes
        $<TARGET_PROPERTY:Day01-Part1,INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:Day01-Part2,INCLUDE_DIRECTORIES>
)

set(Day01-Libraries
        $<TARGET_PROPERTY:Day01-Part1,LINK_LIBRARIES>
        $<TARGET_PROPERTY:Day01-Part2,LINK_LIBRARIES>
)

set(Day01-Libraries)
list(APPEND Day01-Libraries
        $<TARGET_PROPERTY:Day01-Part1-Test,LINK_LIBRARIES>
        $<TARGET_PROPERTY:Day01-Part2-Test,LINK_LIBRARIES>
)
list(REMOVE_DUPLICATES Day01-Libraries)

# Create the combined target
add_executable(Day01-Tests ${Day01-Sources})

# Add the combined include directories
target_include_directories(Day01-Tests PRIVATE ${Day01-Includes})

# Link combined libraries
target_link_libraries(Day01-Tests PRIVATE ${Day01-Libraries})
