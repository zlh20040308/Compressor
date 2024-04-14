cmake_minimum_required(VERSION 3.22)

set(CXX_STANDARD 20)

project(DECOMPRESSOR)

aux_source_directory(${CMAKE_SOURCE_DIR}/src src)

include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(decompressor main.cpp ${src})