cmake_minimum_required(VERSION 3.5)

project(algo_lib)

set(HEADER_ALGO_UNITS algo_lib.h double_counter_map.h, iterator_range.h,
        lazy_value.h object_pool.h stack_vector.h
)

# tests
if (USE_TEST)
    set(TEST_NAME test_algo_lib)
    add_executable(${TEST_NAME} tests/test_algo_lib.cpp)

    # set tests properties
#    set_target_properties(${TEST_NAME} PROPERTIES
#            CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
#            COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#            )
    target_include_directories(${TEST_NAME}
            PRIVATE ${Boost_INCLUDE_DIR}
            PRIVATE ..
            )

    # link to tests
    target_link_libraries(${TEST_NAME}
            ${Boost_LIBRARIES}
            )

    # tests
    add_test(algo_tests ${TEST_NAME})
endif()