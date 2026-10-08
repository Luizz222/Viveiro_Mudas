cmake_minimum_required(VERSION 3.30)
project(Viveiro_Mudas C)

set(CMAKE_C_STANDARD 11)

add_executable(Viveiro_Mudas main.c
        resource/Structs.h
        resource/Bst.h)
