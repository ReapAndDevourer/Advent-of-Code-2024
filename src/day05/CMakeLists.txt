#Part 1
add_library(Day05-Part1 STATIC
        part1/PrinterRuleset.h
        part1/PrinterRuleset.cpp
        part1/PrinterSW.h
        part1/PrinterSW.cpp
)

target_include_directories(Day05-Part1 PUBLIC
        .
)

add_executable(Day05-Part1-Exe
        part1/main.cpp
)

target_link_libraries(Day05-Part1-Exe Day05-Part1)

# Part2
#add_library(Day05-Part2 STATIC
#        part2/X_MasSearch.cpp
#)
#
#target_include_directories(Day05-Part2 PUBLIC
#        .
#)
#
#add_executable(Day05-Part2-Exe
#        part2/main.cpp
#)
#
#target_link_libraries(Day05-Part2-Exe Day05-Part2)