cmake_minimum_required(VERSION 3.5)

project(cnfreader)

add_library(cnfreader STATIC cnfreader.cpp cnfreader.h)
    
target_link_libraries(cnfreader str_utils)

# tests
if (USE_TEST)
    set(TEST_NAME test_cnf_reader)
    add_executable(${TEST_NAME} tests/test_cnf_reader.cpp)

#    set_target_properties(${TEST_NAME} PROPERTIES
#            CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
#            COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#            )
    target_include_directories(${TEST_NAME}
            PRIVATE ${Boost_INCLUDE_DIR}
            )

    # link to tests
    target_link_libraries(${TEST_NAME}
            cnfreader
            ${Boost_LIBRARIES}
            str_utils
            )

    # tests
    add_test(cnf_reader_tests ${TEST_NAME})

endif()


