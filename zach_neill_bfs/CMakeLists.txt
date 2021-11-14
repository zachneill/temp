cmake_minimum_required(VERSION 3.0.0)
project(zach_neill_bfs VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(zach_neill_bfs zach_neill_bfs.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
