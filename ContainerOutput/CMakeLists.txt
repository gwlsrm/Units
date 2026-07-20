cmake_minimum_required(VERSION 3.10)

project(gw_logger)

add_library(gw_logger STATIC gwLogger.cpp gwLogger.h)

set_target_properties(gw_logger PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(gw_logger PUBLIC
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

add_library(GwUnits::gw_logger ALIAS gw_logger)
