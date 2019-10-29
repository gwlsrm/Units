cmake_minimum_required(VERSION 3.5)

project(StringUnits) 

# library
add_library(fileutils STATIC fileutils.cpp fileutils.h)
add_library(metrologic_round STATIC metrologic_round.cpp metrologic_round.h)
add_library(param_str_utils STATIC param_str_utils.cpp param_str_utils.h)
add_library(str_utils STATIC str_utils.cpp str_utils.h)

# tests
add_executable(test_str_utils tests/str_utils_boost_ut.cpp)

# boost dependensies
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# set library properties    
set_target_properties(fileutils PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
set_target_properties(metrologic_round PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(param_str_utils PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
set_target_properties(str_utils PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# set tests properties
set_target_properties(test_str_utils PROPERTIES 
    CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    #INCLUDE_DIRECTORIES ${UNITS}StringUnits/
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

# include to lib
target_include_directories(
        metrologic_round
        PRIVATE         
        ${CMAKE_CURRENT_SOURCE_DIR}/../Math
)

# link to lib
target_link_libraries(metrologic_round math_lib) # link library from lib dir

# link to tests
target_link_libraries(test_str_utils 
    str_utils
    {Boost_LIBRARIES}
)

# tests
enable_testing()
add_test(str_tests test_str_utils)



