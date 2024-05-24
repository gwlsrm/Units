cmake_minimum_required(VERSION 3.5)

project(iniparser)

add_library(${PROJECT_NAME} STATIC iniparser.cpp iniparser.h)

target_link_libraries(${PROJECT_NAME} str_utils)

# set library properties
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# tests
if (USE_TEST)
    set(TEST_NAME test_iniparser)
    add_executable(${TEST_NAME} tests/test_iniparser.cpp)

   set_target_properties(${TEST_NAME} PROPERTIES
           CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
           #COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
           )
    target_include_directories(${TEST_NAME}
            PRIVATE ${Boost_INCLUDE_DIR} .
            )

    # link to tests
    target_link_libraries(${TEST_NAME}
            ${PROJECT_NAME}
            ${Boost_LIBRARIES}
            str_utils
            )

    # tests
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

endif()
