cmake_minimum_required(VERSION 3.10)

project(gw_contract)

add_library(gw_contract INTERFACE)

target_include_directories(gw_contract INTERFACE
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/GwUnits>
)

add_library(GwUnits::gw_contract ALIAS gw_contract)
