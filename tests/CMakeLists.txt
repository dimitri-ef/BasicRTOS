cmake_minimum_required(VERSION 3.13)
project(tests C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER /usr/bin/gcc)

enable_testing()

# add_subdirectory(heap)
add_subdirectory(list)