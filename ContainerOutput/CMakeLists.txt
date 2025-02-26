cmake_minimum_required(VERSION 3.10)

project(gw_logger)

add_library(gw_logger STATIC gwLogger.cpp gwLogger.h)

# tests
#if (USE_TEST)
#    set(TEST_NAME test_gw_logger)
#    add_executable(${TEST_NAME} tests/test_gw_logger.cpp)
#
##    set_target_properties(${TEST_NAME} PROPERTIES
##            CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
##            COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
##            )
#    target_include_directories(${TEST_NAME}
#            PRIVATE ${Boost_INCLUDE_DIR}
#            PRIVATE ${LOGGER_UNITS}
#            )
#
#    # link to tests
#    target_link_libraries(${TEST_NAME}
#            gw_logger
#            ${Boost_LIBRARIES}
#            )
#
#    # tests
#    add_test(gw_logger_tests ${TEST_NAME})
#endif()
