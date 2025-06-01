cmake_minimum_required(VERSION 3.10)
project(banking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(banking STATIC
    src/Account.cpp
    src/Transaction.cpp
)
target_include_directories(banking PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Настройка покрытия кода
if(CMAKE_BUILD_TYPE MATCHES Coverage)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

# Настройка тестов с Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(tests
    tests/test_account.cpp
    tests/test_transaction.cpp
)
target_link_libraries(tests banking gtest gtest_main gmock)

include(GoogleTest)
gtest_discover_tests(tests)

# Цель для запуска тестов
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS tests
)
