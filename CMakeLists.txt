cmake_minimum_required(VERSION 3.3)
project(Markov_Chain)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Markov_Chain_SOURCE_DIR}/cmake")
set(BIN_DIR ${Markov_Chain_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
add_executable(Markov_Chain src/main.cpp)