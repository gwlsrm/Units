cmake_minimum_required(VERSION 3.10)

project(cnfreader)

add_library(${PROJECT_NAME} STATIC cnfreader.cpp cnfreader.h)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

target_link_libraries(${PROJECT_NAME} PUBLIC str_utils)

add_library(GwUnits::cnfreader ALIAS cnfreader)

# tests
if (UNITS_BUILD_TESTS)
    set(TEST_NAME test_cnf_reader)
    add_executable(${TEST_NAME} tests/test_cnf_reader.cpp)

    set_target_properties(${TEST_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
    target_link_libraries(${TEST_NAME} PRIVATE ${PROJECT_NAME} doctest)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
