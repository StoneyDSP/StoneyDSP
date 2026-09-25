cmake_minimum_required(VERSION 3.23...3.31)
project(stoneydsp_consumer_fixture LANGUAGES CXX)

find_package(StoneyDSP CONFIG REQUIRED COMPONENTS Core DSP)

add_executable(stoneydsp-consumer main.cpp)
target_link_libraries(stoneydsp-consumer PRIVATE StoneyDSP::DSP)
target_compile_features(stoneydsp-consumer PRIVATE cxx_std_11)
