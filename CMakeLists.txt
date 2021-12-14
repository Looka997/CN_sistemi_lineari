cmake_minimum_required(VERSION 3.16.3)
project(lab_sistemi)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(.)

add_executable(lab_sistemi
        matrix.cpp
        matrix.h
        matrixFactory.h
        flags.h
        )
