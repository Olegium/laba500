cmake_minimum_required(VERSION 3.4)
project(tests)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(tests test_transaction.cpp)
add_executable(tests test_account.cpp)

target_link_libraries(tests Transaction Account gtest gmock)

add_test(test tests)
