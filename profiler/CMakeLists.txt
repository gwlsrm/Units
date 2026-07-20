cmake_minimum_required(VERSION 3.10)

project(profile_advanced)

add_library(profile_advanced STATIC profile_advanced.cpp profile_advanced.h)

set_target_properties(profile_advanced PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

target_include_directories(profile_advanced PUBLIC
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

add_library(GwUnits::profile_advanced ALIAS profile_advanced)
