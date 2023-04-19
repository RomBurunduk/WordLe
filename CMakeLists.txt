cmake_minimum_required(VERSION 3.24)
project(TestAlgorithm)
find_library(CARBON_LIBRARY Carbon)
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(TestAlgorithm main.cpp header.h)
target_link_libraries(TestAlgorithm ${CARBON_LIBRARY})
target_link_libraries(TestAlgorithm ${OpenCV_LIBS})
