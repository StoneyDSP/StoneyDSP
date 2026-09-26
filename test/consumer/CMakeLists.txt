cmake_minimum_required(VERSION 3.23...3.31)
project(stoneydsp_consumer_fixture LANGUAGES C CXX)

enable_testing()

find_package(StoneyDSP CONFIG REQUIRED COMPONENTS Core DSP)

add_executable(stoneydsp-consumer main.cpp)
target_link_libraries(stoneydsp-consumer PRIVATE StoneyDSP::DSP)
target_compile_features(stoneydsp-consumer PRIVATE cxx_std_11)

add_executable(stoneydsp-aggregate-consumer main.cpp)
target_link_libraries(stoneydsp-aggregate-consumer PRIVATE StoneyDSP::StoneyDSP)
target_compile_features(stoneydsp-aggregate-consumer PRIVATE cxx_std_11)

add_executable(stoneydsp-c-consumer main.c)
target_link_libraries(stoneydsp-c-consumer PRIVATE StoneyDSP::Core)
target_compile_features(stoneydsp-c-consumer PRIVATE c_std_11)

add_test(NAME stoneydsp-c-consumer COMMAND stoneydsp-c-consumer)
add_test(NAME stoneydsp-consumer COMMAND stoneydsp-consumer)
add_test(NAME stoneydsp-aggregate-consumer COMMAND stoneydsp-aggregate-consumer)
