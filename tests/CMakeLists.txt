cmake_minimum_required(VERSION 3.15...4.00)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(shopping-list-tests
        LANGUAGES C CXX)


file(GLOB tests_files *.cpp)
add_executable(shopping-list-tests ${tests_files})
target_include_directories(shopping-list-tests PRIVATE ../include)

file(GLOB src_files ../src/*.c)
add_library(src ${src_files})
target_include_directories(src PRIVATE ../include)

find_package(GTest CONFIG REQUIRED)
enable_testing()
target_link_libraries(shopping-list-tests GTest::gtest_main src)
