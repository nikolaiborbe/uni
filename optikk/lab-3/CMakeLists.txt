cmake_minimum_required(VERSION 3.20)
project(lab-3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendor/matplotplusplus)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE matplot)
