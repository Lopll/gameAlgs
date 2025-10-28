cmake_minimum_required(VERSION 3.14)
project(Lab2)

if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wextra")
endif()

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
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