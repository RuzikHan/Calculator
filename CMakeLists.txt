cmake_minimum_required(VERSION 3.6)
project(Calculator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp printer.h)
add_executable(Calculator ${SOURCE_FILES})