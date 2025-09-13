include(FetchContent)
FetchContent_Declare(
 googletest
 GIT_REPOSITORY https://github.com/google/googletest.git
 GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
add_executable(rpn_test test_rpn.cpp ../src/rpn.cpp)
target_link_libraries(rpn_test PRIVATE gtest_main)
target_include_directories(rpn_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_test(NAME rpn_test COMMAND rpn_test)
