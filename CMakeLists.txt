cmake_minimum_required(VERSION 3.10)

project(mathlib
    LANGUAGES CXX
    VERSION 1.0.0
    DESCRIPTION "a custom mathematics library")

set(HEADERS
    include/Constants.h
    include/Convert.h
    include/EquationSolving.h
    include/Matrix.h
    include/MatrixTransform.h
    include/Vector.h)

set(SOURCES
    src/Convert.cpp
    src/EquationSolving.cpp
    src/MatrixTransform.cpp)

add_library(mathlib SHARED
    ${SOURCES})

install(
    TARGETS mathlib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)
install(FILES ${HEADERS}
    DESTINATION include/mathlib)
