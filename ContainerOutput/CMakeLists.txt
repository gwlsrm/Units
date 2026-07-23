cmake_minimum_required(VERSION 3.10)

project(gw_logger)

add_library(gw_logger STATIC gwLogger.cpp gwLogger.h)

set_target_properties(gw_logger PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(gw_logger PUBLIC
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

add_library(GwUnits::gw_logger ALIAS gw_logger)

# tests
if (UNITS_BUILD_TESTS)
    set(TEST_NAME test_gw_logger)
    add_executable(${TEST_NAME} tests/test_gw_logger.cpp)

    set_target_properties(${TEST_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
    target_link_libraries(${TEST_NAME} PRIVATE gw_logger doctest)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
