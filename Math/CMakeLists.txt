cmake_minimum_required(VERSION 3.10)

project(math_lib)

set(SRC_MATH_UNITS
        geom_lib.cpp gw_algorithm.cpp interpol.cpp leastsquares.cpp
        math_lib.cpp nonlinearsolver.cpp numeric_integration.cpp
        sle.cpp
        )
set(HEADER_MATH_UNITS
        array_view.h gwmatrix.h gw_matrix_view.h geom_lib.h gw_algorithm.h
        interpol.h leastsquares.h
        math_lib.h nonlinearsolver.h numeric_integration.h sle.h
        )

add_library(math_lib STATIC ${SRC_MATH_UNITS} ${HEADER_MATH_UNITS})

# set library properties
set_target_properties(math_lib PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# tests
if (USE_TEST)
    set(TEST_MATH_LIB test_math_lib)
    set(TEST_MATRIX test_matrix)
    add_executable(${TEST_MATH_LIB} tests/test_math_lib.cpp)
    add_executable(${TEST_MATRIX} tests/test_matrix_array.cpp)

    # set tests properties
   set_target_properties(${TEST_MATH_LIB} PROPERTIES
           CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
           #COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
           )
    target_include_directories(${TEST_MATH_LIB}
            PRIVATE ${Boost_INCLUDE_DIR} .
            )
    target_include_directories(${TEST_MATRIX}
            PRIVATE ${Boost_INCLUDE_DIR} .
            )

    # link to tests
    target_link_libraries(${TEST_MATH_LIB}
            math_lib
            ${Boost_LIBRARIES}
            )
    target_link_libraries(${TEST_MATRIX}
            math_lib
            ${Boost_LIBRARIES}
            )

    # tests
    add_test(NAME ${TEST_MATH_LIB} COMMAND ${TEST_MATH_LIB} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    add_test(NAME ${TEST_MATRIX} COMMAND ${TEST_MATRIX} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
