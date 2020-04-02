# src for str_utils 
set(CNF_READER_UNITS ${UNITS}CnfReader/)
set(SRC_CNF_READER ${CNF_READER_UNITS}cnfreader.cpp ${CNF_READER_UNITS}cnfreader.h)

# library
set(LIB_NAME cnf_reader_lib)
add_library(${LIB_NAME} STATIC ${SRC_CNF_READER})

# tests
if (USE_TEST)
    set(TEST_NAME test_cnf_reader)
    add_executable(${TEST_NAME} ${CNF_READER_UNITS}/tests/test_cnf_reader.cpp)

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
        PRIVATE ${CNF_READER_UNITS}
    )

    # link to tests
    target_link_libraries(${TEST_NAME} 
        ${LIB_NAME}
        ${Boost_LIBRARIES}
        str_utils_lib
    )

    # tests
    enable_testing()
    add_test(cnf_reader_tests ${TEST_NAME})
endif()


