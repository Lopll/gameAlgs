cmake_minimum_required(VERSION 3.14)
project(Lab2)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 ")

# GoogleTest requires at least C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

enable_testing()

add_executable(
  gTest
  gTest.cpp
)
target_link_libraries(
  gTest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(gTest)