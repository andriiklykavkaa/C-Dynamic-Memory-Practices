cmake_minimum_required(VERSION 3.29)
project(Dynamic_Array C)

set(CMAKE_C_STANDARD 11)

add_executable(Dynamic_Array main.c
        Vector.c
        Vector.h
        Buffer.c
        Buffer.h)
