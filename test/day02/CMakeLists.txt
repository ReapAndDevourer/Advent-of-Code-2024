#Part 1
add_executable(Day02-Part1-Test
        part1/TestLevelChecker.cpp
        ../TestMain.cpp
)

target_link_libraries(Day02-Part1-Test PRIVATE
        Day02-Part1
        Boost::unit_test_framework
)

#Part 2
add_executable(Day02-Part2-Test
        part2/TestLevelCheckerWithDampener.cpp
        ../TestMain.cpp
)

target_link_libraries(Day02-Part2-Test PRIVATE
        Day02-Part2
        Boost::unit_test_framework
)

# Combine sources and include paths
set(Day02-Sources
        $<TARGET_PROPERTY:Day02-Part1-Test,SOURCES>
        $<TARGET_PROPERTY:Day02-Part2-Test,SOURCES>
)

set(Day02-Includes
        $<TARGET_PROPERTY:Day02-Part1,INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:Day02-Part2,INCLUDE_DIRECTORIES>
)

set(Day02-Libraries
        $<TARGET_PROPERTY:Day02-Part1,LINK_LIBRARIES>
        $<TARGET_PROPERTY:Day02-Part2,LINK_LIBRARIES>
)

set(Day02-Libraries)
list(APPEND Day02-Libraries
        $<TARGET_PROPERTY:Day02-Part1-Test,LINK_LIBRARIES>
        $<TARGET_PROPERTY:Day02-Part2-Test,LINK_LIBRARIES>
)
list(REMOVE_DUPLICATES Day02-Libraries)

# Create the combined target
add_executable(Day02-Tests ${Day02-Sources})

# Add the combined include directories
target_include_directories(Day02-Tests PRIVATE ${Day02-Includes})

# Link combined libraries
target_link_libraries(Day02-Tests PRIVATE ${Day02-Libraries})
