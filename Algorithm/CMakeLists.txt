cmake_minimum_required(VERSION 3.10)

project(algo_lib)

set(HEADER_ALGO_UNITS algo_lib.h dictionary.h double_counter_map.h iterator_range.h
    lazy_value.h object_pool.h stack_vector.h
)

add_library(algo_lib INTERFACE)

target_include_directories(algo_lib INTERFACE
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

add_library(GwUnits::algo_lib ALIAS algo_lib)

# tests
if(UNITS_BUILD_TESTS)
    set(TEST_NAME test_algo_lib)
    add_executable(${TEST_NAME} tests/test_algo_lib.cpp)

    target_include_directories(${TEST_NAME}
        PRIVATE ${Boost_INCLUDE_DIR}
        PRIVATE ..
    )

    target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES})

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
