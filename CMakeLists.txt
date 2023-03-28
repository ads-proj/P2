cmake_minimum_required(VERSION 3.23)
project(P2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(P2
        LeftistHeap.h
        main.cpp
        SkewHeap.h
        NormalHeap.h
        Node.h)