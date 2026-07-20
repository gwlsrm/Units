cmake_minimum_required(VERSION 3.10)

project(gwdate)

add_library(gwdate STATIC date.cpp date.h)

set_target_properties(gwdate PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

target_include_directories(gwdate PUBLIC
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

add_library(GwUnits::gwdate ALIAS gwdate)
