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

#Day3
set(Day03-Part1-Src day03/part1/TestComputerPart1.cpp)
set(Day03-Part2-Src day03/part2/TestComputerPart2.cpp)
add_executable(Day03-Tests TestMain.cpp ${Day03-Part1-Src} ${Day03-Part2-Src})
target_link_libraries(Day03-Tests
        Boost::unit_test_framework
        Day03-Part1 Day03-Part2
)

#Day4
set(Day04-Part1-Src day04/part1/TestXMasSearch.cpp)
set(Day04-Part2-Src day04/part2/TestX_MasSearch.cpp)
add_executable(Day04-Tests TestMain.cpp ${Day04-Part1-Src} ${Day04-Part2-Src})
target_link_libraries(Day04-Tests
        Boost::unit_test_framework
        Day04-Part1 Day04-Part2
)

#Day5
set(Day05-Part1-Src day05/part1/TestPrinter.cpp)
set(Day05-Part2-Src day05/part2/TestPrinterFixing.cpp)
add_executable(Day05-Tests TestMain.cpp ${Day05-Part1-Src} ${Day05-Part2-Src})
target_link_libraries(Day05-Tests
        Boost::unit_test_framework
        Day05-Part1 Day05-Part2
)

#All Days
add_executable(All-Tests
        TestMain.cpp
        ${Day01-Part1-Src} ${Day01-Part2-Src}
        ${Day02-Part1-Src} ${Day02-Part2-Src}
        ${Day03-Part1-Src} ${Day03-Part2-Src}
        ${Day04-Part1-Src} ${Day04-Part2-Src}
        ${Day05-Part1-Src} ${Day05-Part2-Src}
)
target_link_libraries(All-Tests PRIVATE
        Boost::unit_test_framework
        Day01-Part1 Day01-Part2
        Day02-Part1 Day02-Part2
        Day03-Part1 Day03-Part2
        Day04-Part1 Day04-Part2
        Day05-Part1 Day05-Part2
)
