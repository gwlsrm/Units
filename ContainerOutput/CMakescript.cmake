# src for gwLogger
set(SRC_LOGGER_UNITS ${LOGGER_UNITS}gwLogger.cpp)

# library
set(LIB_NAME gw_logger_lib)
add_library(${LIB_NAME} STATIC ${SRC_LOGGER_UNITS})

# tests
if (USE_TEST)
    set(TEST_NAME test_gw_logger)
    add_executable(${TEST_NAME} ${LOGGER_UNITS}/tests/test_gw_logger.cpp)

    # boost dependensies
    #find_package(Boost COMPONENTS unit_test_framework REQUIRED)
endif()

# set library properties    
set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# set tests properties
if (USE_TEST)
    set_target_properties(${TEST_NAME} PROPERTIES
        CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    )
    target_include_directories(${TEST_NAME}
        PRIVATE ${Boost_INCLUDE_DIR}
        PRIVATE ${LOGGER_UNITS}
    )

    # link to tests
    target_link_libraries(${TEST_NAME}
        ${LIB_NAME}
        ${Boost_LIBRARIES}
    )

    # tests
    enable_testing()
    add_test(gw_logger_tests ${TEST_NAME})
endif()