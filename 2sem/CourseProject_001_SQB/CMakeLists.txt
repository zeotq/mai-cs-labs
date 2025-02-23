cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(CourseProject LANGUAGES C)
set(CMAKE_C_STANDARD 11)

add_subdirectory(sqbyte)

add_executable(searcher src/searcher.c)
add_executable(reader src/reader.c)
add_executable(generator src/generator.c)
add_executable(fillfromkeyboard src/fillfromkeyboard.c)

set(EXECUTABLES searcher reader generator fillfromkeyboard)

foreach(exec IN LISTS EXECUTABLES)
    target_include_directories(${exec} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_include_directories(${exec} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/sqbyte)
    target_link_libraries(${exec} PRIVATE SQByte)
endforeach()
