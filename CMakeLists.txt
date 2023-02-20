cmake_minimum_required(VERSION 3.23)
project(Sort)

set(CMAKE_CXX_STANDARD 20)

add_executable(Sort main.cpp Sort.h Sort.cpp Array.cpp Array.h CSVWriter.h)
