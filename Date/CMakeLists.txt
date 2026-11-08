cmake_minimum_required(VERSION 3.10)

project(gwdate)

add_library(gwdate STATIC date.cpp date.h datetime.cpp datetime.h)

target_link_libraries(gwdate PUBLIC GwUnits::gw_contract)

set_target_properties(gwdate PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(gwdate PUBLIC
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

add_library(GwUnits::gwdate ALIAS gwdate)

# tests
if(UNITS_BUILD_TESTS)
    set(TEST_NAME test_gwdate)
    add_executable(${TEST_NAME} tests/test_datatime.cpp)

    target_link_libraries(${TEST_NAME} PRIVATE gwdate doctest)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
