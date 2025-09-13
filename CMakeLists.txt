cmake_minimum_required(VERSION 3.14)
project(RPN_Calculator)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
FetchContent_MakeAvailable(googletest)

# Main app
add_executable(rpn_calculator src/main.cpp src/rpn.cpp)
target_include_directories(rpn_calculator PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Tests
add_executable(rpn_tests tests/test_rpn.cpp src/rpn.cpp)
target_include_directories(rpn_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(rpn_tests PRIVATE GTest::gtest_main)

enable_testing()
add_test(NAME rpn_tests COMMAND rpn_tests)
