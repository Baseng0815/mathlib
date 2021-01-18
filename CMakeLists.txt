cmake_minimum_required(VERSION 3.10)

project(mathlib
    LANGUAGES CXX
    VERSION 1.0.0
    DESCRIPTION "a custom mathematics library")

add_library(mathlib SHARED)

target_sources(mathlib PUBLIC
    include/Constants.h
    include/Convert.h
    include/EquationSolving.h
    include/Matrix.h
    include/MatrixTransform.h
    include/Vector.h PRIVATE
    src/Convert.cpp
    src/EquationSolving.cpp
    src/MatrixTransform.cpp)

set(INSTALL_HEADERS
    include/Constants.h
    include/Convert.h
    include/EquationSolving.h
    include/Matrix.h
    include/MatrixTransform.h
    include/Vector.h)

install(TARGETS mathlib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)
install(FILES ${INSTALL_HEADERS} DESTINATION include/mathlib)
