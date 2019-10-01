cmake_minimum_required(VERSION 3.5)

project(StringUnits) 

add_library(fileutils STATIC fileutils.cpp fileutils.h)
add_library(metrologic_round STATIC metrologic_round.cpp metrologic_round.h)
add_library(param_str_utils STATIC param_str_utils.cpp param_str_utils.h)
add_library(str_utils STATIC str_utils.cpp str_utils.h)
    
set_target_properties(fileutils PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
set_target_properties(metrologic_round PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(param_str_utils PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
set_target_properties(str_utils PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories( # include library dir
        metrologic_round
        PRIVATE         
        ${CMAKE_CURRENT_SOURCE_DIR}/../Math
)

target_link_libraries(metrologic_round math_lib) # link library from lib dir



