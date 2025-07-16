#!/bin/bash

show_help() {
  echo "Usage: $0 [OPTIONS]"
  echo ""
  echo "Options:"
  echo "  -a, --all                         Run everything (build lib, build tests, build for board, run tests)"
  echo "  -t, --build-tests                 Build tests only"
  echo "  -r, --run-tests                   Run tests only (assumes tests are built)"
  echo "  -f|--build-basicfreertos-lib      Build the core RTOS library"
  echo "  -b, --board                       Build and flash for STM32 board"
  echo "  -h, --help                        Show this help message"
}

FALSE=0
TRUE=1

ALL=$FALSE
BUILD_TEST=$FALSE
RUN_TESTS=$FALSE
BUILD_BASICFREERTOS_LIB=$FALSE
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
        -f|--build-basicfreertos-lib)
            BUILD_BASICFREERTOS_LIB=$TRUE
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
    mkdir -p builds/test
    cmake -DCMAKE_C_COMPILER=/usr/bin/gcc -S tests/ -B builds/test
    cd builds/test; make; cd -
fi

if [ $RUN_TESTS -eq $TRUE ]; then
    cd builds/test; ctest --output-on-failure --output-junit test_results.xml; cd -
fi

if [ $BUILD_BASICFREERTOS_LIB -eq $TRUE ]; then
    mkdir -p builds/basicFreeRTOS
    cmake -S . -B builds/basicFreeRTOS -DCMAKE_TOOLCHAIN_FILE=${PWD}/stmf411re/cmake/gcc-arm-none-eabi.cmake
    cd builds/basicFreeRTOS; make; cd -
fi

if [ $BUILD_BOARD -eq $TRUE ]; then
    cp -rf basicFreeRTOS stmf411re/Middleware
    mkdir -p builds/stmf411re
    cmake -S stmf411re/ -B builds/stmf411re -DCMAKE_TOOLCHAIN_FILE=${PWD}/stmf411re/cmake/gcc-arm-none-eabi.cmake
    cd builds/stmf411re; make flash; cd -
fi