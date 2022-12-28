cmake_minimum_required(VERSION 2.8)
project(IC_G07_Proj3)

SET (BASE_DIR ${CMAKE_SOURCE_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR} /../Part_II/test_programs)

add_executable(langTest ./test_programs/langTest.cpp)
#add_executable(findlangTest ./test_programs/findlangTest.cpp)
#add_executable(locatelangTest ./test_programs/locatelangTest.cpp)