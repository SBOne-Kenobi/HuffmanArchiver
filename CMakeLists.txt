cmake_minimum_required(VERSION 3.15)
project(HuffmanArchiver)
set(CMAKE_CXX_FLAGS "-std=c++14 -pedantic -Wall -Wextra -Werror")
include_directories(include)
add_executable(HuffmanArchiver src/main.cpp
        src/huffman.cpp include/huffman.h
        include/binary.h src/binary.cpp
        include/archiver.h src/archiver.cpp)