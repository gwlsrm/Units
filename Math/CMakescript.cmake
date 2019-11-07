# src for math
set(SRC_MATH_UNITS ${MATH_UNITS}sle.cpp ${MATH_UNITS}numeric_integration.cpp
    ${MATH_UNITS}math_lib.cpp ${MATH_UNITS}leastsquares.cpp ${MATH_UNITS}interpol.cpp
    ${MATH_UNITS}gwmatrix.cpp
)

# library
set(LIB_NAME math_lib)
add_library(${LIB_NAME} STATIC ${SRC_MATH_UNITS})

# tests
set(TEST_NAME test_math_lib)
add_executable(${TEST_NAME} ${MATH_UNITS}/tests/test_math_lib.cpp)

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
    PRIVATE ${MATH_UNITS}
)

# link to tests
target_link_libraries(${TEST_NAME} 
    ${LIB_NAME}
    ${Boost_LIBRARIES}
)

# tests
enable_testing()
add_test(math_tests ${TEST_NAME})
