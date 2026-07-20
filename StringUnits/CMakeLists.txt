cmake_minimum_required(VERSION 3.10)

project(str_utils)

set(SRC_STR_UTILS str_utils.cpp param_str_utils.cpp fileutils.cpp)
set(HEADER_STR_UTILS str_utils.h param_str_utils.h fileutils.h)

add_library(${PROJECT_NAME} STATIC ${SRC_STR_UTILS} ${HEADER_STR_UTILS})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

add_library(GwUnits::str_utils ALIAS str_utils)

# tests
if (UNITS_BUILD_TESTS)
    set(TEST_NAME test_str_utils)
    add_executable(${TEST_NAME} tests/str_utils_boost_ut.cpp)

    set_target_properties(${TEST_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
    target_include_directories(${TEST_NAME} PRIVATE ${Boost_INCLUDE_DIR} .)
    target_link_libraries(${TEST_NAME} ${PROJECT_NAME} ${Boost_LIBRARIES})

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
