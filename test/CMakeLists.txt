#Day1
set(Day01-Part1-Src day01/part1/TestDistanceCalculator.cpp)
set(Day01-Part2-Src day01/part2/TestSimilarityCalculator.cpp)
add_executable(Day01-Tests TestMain.cpp ${Day01-Part1-Src} ${Day01-Part2-Src})
target_link_libraries(Day01-Tests
        Boost::unit_test_framework
        Day01-Part1 Day01-Part2
)

#Day2
set(Day02-Part1-Src day02/part1/TestLevelChecker.cpp)
set(Day02-Part2-Src day02/part2/TestLevelCheckerWithDampener.cpp)
add_executable(Day02-Tests TestMain.cpp ${Day02-Part1-Src} ${Day02-Part2-Src})
target_link_libraries(Day02-Tests
        Boost::unit_test_framework
        Day02-Part1 Day02-Part2
)

#All Days
add_executable(All-Tests
        TestMain.cpp
        ${Day01-Part1-Src} ${Day01-Part2-Src}
        ${Day02-Part1-Src} ${Day02-Part2-Src}
)
target_link_libraries(All-Tests PRIVATE
        Boost::unit_test_framework
        Day01-Part1 Day01-Part2
        Day02-Part1 Day02-Part2
)
