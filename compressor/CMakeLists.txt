cmake_minimum_required(VERSION 3.22)

set(CXX_STANDARD 20)

project(COMPRESSOR)

aux_source_directory(${CMAKE_SOURCE_DIR}/src src)

include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(compressor main.cpp ${src})