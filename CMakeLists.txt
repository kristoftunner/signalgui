cmake_minimum_required(VERSION 3.16)

project(signalgui CXX)
include(cmake/defines.cmake)

# build dependecies
add_subdirectory(ext/kfr)

# build the lib
add_subdirectory(src)