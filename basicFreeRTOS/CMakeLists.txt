cmake_minimum_required(VERSION 3.13)
project(basicFreeRTOS LANGUAGES C)

enable_language(C ASM)

include_directories(inc)

file(GLOB SOURCES "src/*.c")

add_library(basicFreeRTOS STATIC ${SOURCES})