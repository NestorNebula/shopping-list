cmake_minimum_required(VERSION 3.15...4.00)

project(shopping-list
        VERSION 0.0
        DESCRIPTION "A program that prints a shopping list"
        LANGUAGES C)

file(GLOB src src/*.c)

add_executable(shopping-list ${src})
target_include_directories(shopping-list PRIVATE include)
