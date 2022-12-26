cmake_minimum_required(VERSION 2.8)
project(IC_G07_Proj3)

SET (BASE_DIR ${CMAKE_SOURCE_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR} /../Part_I/test_programs)

add_executable(fcmTest ./test_programs/fcmTest.cpp)