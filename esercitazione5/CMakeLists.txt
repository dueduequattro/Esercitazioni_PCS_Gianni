cmake_minimum_required(VERSION 3.20)
project(esercitazione2) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla -Wno-sign-compare")


add_executable(test_bubblesort test_bubblesort.cpp timecounter.cpp)
add_test(NAME bubblesort COMMAND test_bubblesort)

add_executable(test_insertionsort test_insertionsort.cpp timecounter.cpp)
add_test(NAME insertionsort COMMAND test_insertionsort)

add_executable(test_selectionsort test_selectionsort.cpp timecounter.cpp)
add_test(NAME selectionsort COMMAND test_selectionsort)

add_executable(test_mergesort test_mergesort.cpp timecounter.cpp)
add_test(NAME mergesort COMMAND test_mergesort)

add_executable(test_quicksort test_quicksort.cpp timecounter.cpp)
add_test(NAME quicksort COMMAND test_quicksort)

add_executable(test_strings test_strings.cpp)
add_test(NAME strings COMMAND test_strings)

add_executable(test_mysort test_mysort.cpp timecounter.cpp)
add_test(NAME mysort COMMAND test_mysort)

add_executable(delta_times delta_times.cpp timecounter.cpp)
add_executable(confronto_tempi confronto_tempi.cpp timecounter.cpp)

enable_testing()

