cmake_minimum_required(VERSION 3.26)
project(BancoquempoupatemVF C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(BancoquempoupatemVF
        biblioteca.c
        biblioteca.h
        main.c)
