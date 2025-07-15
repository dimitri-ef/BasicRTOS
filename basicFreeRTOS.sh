#!/bin/bash

show_help() {
  echo "Usage: $0 [OPTIONS]"
  echo ""
  echo "Options:"
  echo "  -a, --all           Run everything (build lib, build tests, build for board, run tests)"
  echo "  -t, --build-tests   Build tests only"
  echo "  -r, --run-tests     Run tests only (assumes tests are built)"
  echo "  -l, --lib           Build the core RTOS library"
  echo "  -b, --board         Build and flash for STM32 board"
  echo "  -h, --help          Show this help message"
}

FALSE=0
TRUE=1

ALL=$FALSE
BUILD_TEST=$FALSE
RUN_TESTS=$FALSE
BUILD_LIB=$FALSE
BUILD_BOARD=$FALSE
HELP=$FALSE

while [[ $# -gt 0 ]]; do
    case "$1" in
        -a|--all)
            ALL=$TRUE
            ;;
        -t|--build-tests)
            BUILD_TEST=$TRUE
            ;;
        -r|--run-tests)
            BUILD_TEST=$TRUE
            RUN_TESTS=$TRUE
            ;;
        -l|--lib)
            BUILD_LIB=$TRUE
        ;;
        -b|--board)
            BUILD_BOARD=$TRUE
            ;;
        -h|--help)
            HELP=$TRUE
            ;;
        --)
            shift
            break
            ;;
        *)
            echo "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
    shift
done

mkdir -p builds

if [ $BUILD_TEST -eq $TRUE ]; then
    mkdir -p builds/test_build
    cmake -DCMAKE_C_COMPILER=/usr/bin/gcc -S tests/ -B builds/test_build
    cd builds/test_build; make; cd -
fi

if [ $RUN_TESTS -eq $TRUE ]; then
    cd builds/test_build; ctest; cd -
fi

if [ $BUILD_BOARD -eq $TRUE ]; then
    mkdir -p builds/stmf411re_build
    cmake -S stmf411re/ -B builds/stmf411re_build -DCMAKE_TOOLCHAIN_FILE=${PWD}/stmf411re/cmake/gcc-arm-none-eabi.cmake
    cd builds/stmf411re_build; make flash; cd -
fi