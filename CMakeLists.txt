cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
add_compile_options(--coverage)
project(banking)

add_library(banking_lib STATIC  ${CMAKE_CURRENT_SOURCE_DIR}/banking/Transaction.cpp 
                                ${CMAKE_CURRENT_SOURCE_DIR}/banking/Account.cpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest gtest)
add_executable(run_test ${CMAKE_CURRENT_SOURCE_DIR}/gtests/Testfile.cpp)

target_include_directories(run_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/banking)
target_compile_options(run_test PRIVATE --coverage)
target_link_libraries(run_test PRIVATE --coverage)
target_link_libraries(run_test PUBLIC banking_lib gtest_main)
