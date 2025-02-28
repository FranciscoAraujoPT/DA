cmake_minimum_required(VERSION 3.20)
project(DA)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA ../main.cpp
        ../MutablePriorityQueue.h
        ../Graph.h
        ../Location.cpp
        ../Location.h
        ../CSVReader.cpp
        ../CSVReader.h)

file(GLOB_RECURSE data ./data/*)

file(COPY ${data} DESTINATION data)
