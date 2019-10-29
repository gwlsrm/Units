# src for str_utils 
set(STR_UNITS ${UNITS}StringUnits/)
set(SRC_STR_UTILS ${STR_UNITS}str_utils.cpp ${STR_UNITS}param_str_utils.cpp
    ${STR_UNITS}fileutils.cpp  #${STR_UNITS}metrologic_round.cpp 
)

# library
set(LIB_NAME str_utils_lib)
add_library(${LIB_NAME} STATIC ${SRC_STR_UTILS})

# tests
set(TEST_NAME test_str_utils)
add_executable(${TEST_NAME} ${STR_UNITS}/tests/str_utils_boost_ut.cpp)

# boost dependensies
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# set library properties    
set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# set tests properties
set_target_properties(${TEST_NAME} PROPERTIES 
    CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)
target_include_directories(${TEST_NAME}
    PRIVATE ${Boost_INCLUDE_DIR}
    PRIVATE ${STR_UNITS}
)

# link to tests
target_link_libraries(${TEST_NAME} 
    ${LIB_NAME}
    ${Boost_LIBRARIES}
)

# tests
enable_testing()
add_test(str_tests ${TEST_NAME})



