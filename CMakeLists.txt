cmake_minimum_required(VERSION 4.2)
project(rsa)

set(CMAKE_CXX_STANDARD 20)

add_executable(rsa main.cpp
        BigInt.cpp
        BigInt.h)
