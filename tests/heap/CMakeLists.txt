cmake_minimum_required(VERSION 3.10)
project(HeapAllocator C)

add_definitions(-DDEBUG)

include_directories("../../inc")
add_executable(heap_test main.c ../../src/heap.c)