cmake_minimum_required(VERSION 3.10)

project(BinFStream)

add_library(bintext_fstream STATIC bintext_fstream.cpp bintext_fstream.h)

set_target_properties(bintext_fstream PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(bintext_fstream PUBLIC
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

add_library(GwUnits::bintext_fstream ALIAS bintext_fstream)
