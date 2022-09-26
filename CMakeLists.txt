cmake_minimum_required(VERSION 3.23)
project(inter)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(inter
        HermitInterpolation.c
        CubicSpline.c
        interpolation.c
        interpolation.h
        main.c
        HermitInterpolation.h TestFunctions.c TestFunctions.h CubicSpline.h Common.c Common.h)

target_link_libraries(inter PRIVATE m)
