cmake_minimum_required(VERSION 3.10)

add_executable(test_simple test_simple.cpp)

find_library(MATHLIB_LIBRARY mathlib HINTS /home/bastian/mathlib/build)
target_link_libraries(test_simple PUBLIC ${MATHLIB_LIBRARY})
add_test(NAME simple COMMAND test_simple)
