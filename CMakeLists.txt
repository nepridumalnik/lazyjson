cmake_minimum_required(VERSION 3.25)
project(lazyjson)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(src)
