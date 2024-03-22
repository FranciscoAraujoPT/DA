cmake_minimum_required(VERSION 3.20)
project(DA)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA main.cpp
        CSVReader.cpp
        CSVReader.h
        WaterReservoir.cpp
        WaterReservoir.h
        PumpingStation.cpp
        PumpingStation.h
        DeliverySite.cpp
        DeliverySite.h
        Pipeline.cpp
        Pipeline.h
        Graph.h
        GraphNode.h
        GraphNode.cpp)

file(GLOB_RECURSE data ./data/*)

file(COPY ${data} DESTINATION data)
