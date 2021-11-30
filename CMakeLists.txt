cmake_minimum_required(VERSION 3.19)
project(lab_sistemi)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_sistemi
        matrix.cpp
        matrix.h
        matrixFactory.h
        )
