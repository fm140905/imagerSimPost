cmake_minimum_required(VERSION 3.16.3)

project(Postprocessing CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Header)

enable_testing()
add_subdirectory(googletest)
add_subdirectory(Sources)
add_subdirectory(Test)