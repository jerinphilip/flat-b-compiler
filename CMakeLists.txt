cmake_minimum_required(VERSION 3.24)

project(flatb CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(LLVM REQUIRED CONFIG)

add_subdirectory(src)
