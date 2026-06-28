cmake_minimum_required(VERSION 3.20)
project(Progetto_Finale)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

add_executable(main main.cpp)
target_include_directories(main PRIVATE /opt/homebrew/include/eigen3)