# src for math
set(SRC_METR_UNITS ${METR_UNITS}metr_number.cpp)

# library
set(LIB_NAME metr_number_lib)
add_library(${LIB_NAME} STATIC ${SRC_METR_UNITS})

# tests
if (USE_TEST)
    set(TEST_NAME test_metr_number_lib)
    add_executable(${TEST_NAME} ${METR_UNITS}/tests/test_metr_number_lib.cpp)

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
    PRIVATE ${METR_UNITS}
)

# link to tests
target_link_libraries(${TEST_NAME} 
    ${LIB_NAME}
    ${Boost_LIBRARIES}
)

# tests
enable_testing()
add_test(metr_number_tests ${TEST_NAME})
endif()