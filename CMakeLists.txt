cmake_minimum_required(VERSION 3.20.0)

project("Advent Of Code 2024" LANGUAGES CXX VERSION 1.0.0)

cmake_policy(SET CMP0167 OLD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Connect the build version of Boost.Test for unit-testing
set(Boost_ROOT "/Users/enriquerodriguez/Entwicklungstools/boost_1_86_0")
find_package(Boost 1.85 COMPONENTS unit_test_framework REQUIRED)

add_subdirectory(src)
add_subdirectory(test)