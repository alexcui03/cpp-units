cmake_minimum_required(VERSION 3.5)

project(cpp-units VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cpp-units INTERFACE)
target_include_directories(cpp-units INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/cpp-units)

enable_testing()
add_subdirectory(test)
