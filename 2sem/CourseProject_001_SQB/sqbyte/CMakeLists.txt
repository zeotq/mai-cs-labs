cmake_minimum_required(VERSION 3.10)
project(SQByte C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(SQByte SQByte.c)
target_include_directories(SQByte PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})