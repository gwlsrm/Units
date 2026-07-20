cmake_minimum_required(VERSION 3.10)

project(dll_loader)

add_library(dll_loader STATIC dll_loader.cpp dll_loader.h)

set_target_properties(dll_loader PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(dll_loader PUBLIC
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

add_library(GwUnits::dll_loader ALIAS dll_loader)
