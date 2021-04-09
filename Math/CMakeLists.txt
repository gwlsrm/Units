cmake_minimum_required(VERSION 3.5)

project(math_lib)

set(SRC_MATH_UNITS sle.cpp numeric_integration.cpp
        math_lib.cpp leastsquares.cpp interpol.cpp
        gwmatrix.cpp geom_lib.cpp gw_algorithm.cpp
        nonlinearsolver.cpp
        )
set(HEADER_MATH_UNITS sle.h numeric_integration.h
        math_lib.h leastsquares.h interpol.h
        gwmatrix.h geom_lib.h gw_algorithm.h
        nonlinearsolver.h
        )

add_library(math_lib STATIC ${SRC_MATH_UNITS} ${HEADER_MATH_UNITS})

# set library properties
set_target_properties(math_lib PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# tests
if (USE_TEST)
    set(TEST_NAME test_math_lib)
    add_executable(${TEST_NAME} tests/test_math_lib.cpp)

    # set tests properties
   set_target_properties(${TEST_NAME} PROPERTIES
           CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
           #COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
           )
    target_include_directories(${TEST_NAME}
            PRIVATE ${Boost_INCLUDE_DIR} .
            )

    # link to tests
    target_link_libraries(${TEST_NAME}
            math_lib
            ${Boost_LIBRARIES}
            )

    # tests
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()