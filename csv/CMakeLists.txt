cmake_minimum_required(VERSION 3.5)

project(csvlib)

set(HEADER_CSV_UNITS csv_writer.h)

add_library(csvlib INTERFACE ${HEADER_CSV_UNITS})

# set library properties
set_target_properties(csvlib PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# tests
if (USE_TEST)
    set(TEST_NAME test_csv_lib)
    add_executable(${TEST_NAME} tests/test_csv_lib.cpp)

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
        ${Boost_LIBRARIES}
    )

    # tests
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

# example
if (BUILD_EXAMPLE)
    add_executable(ex_csv_writer example/main_writer.cpp)
    set_target_properties(ex_csv_writer PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
endif()