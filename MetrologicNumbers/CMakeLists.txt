cmake_minimum_required(VERSION 3.5)

project(metr_number)

add_library(metr_number STATIC metr_number.cpp metr_number.h)
    
set_target_properties(metr_number PROPERTIES      
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      )

# tests
if (USE_TEST)
#    set(TEST_NAME test_metr_number_lib)
#    add_executable(${TEST_NAME} tests/test_metr_number_lib.cpp)
#
##    set_target_properties(${TEST_NAME} PROPERTIES
##            CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
##            COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
##            )
#    target_include_directories(${TEST_NAME}
#            PRIVATE ${Boost_INCLUDE_DIR}
#            PRIVATE ${METR_UNITS}
#            )
#
#    # link to tests
#    target_link_libraries(${TEST_NAME}
#            metr_number
#            ${Boost_LIBRARIES}
#            )
#
#    # tests
#    add_test(metr_number_tests ${TEST_NAME})
endif()

