cmake_minimum_required(VERSION 3.4)
project(testing)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(testing test_transaction.cpp)
add_executable(testing test_account.cpp)

target_link_libraries(testing Transaction Account gtest gmock)

add_test(test testing)
