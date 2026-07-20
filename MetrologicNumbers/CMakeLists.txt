cmake_minimum_required(VERSION 3.10)

project(metr_number)

add_library(metr_number STATIC metr_number.cpp metr_number.h)

set_target_properties(metr_number PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

target_include_directories(metr_number PUBLIC
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

add_library(GwUnits::metr_number ALIAS metr_number)
