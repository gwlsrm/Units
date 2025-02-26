cmake_minimum_required(VERSION 3.10)

project(gwdate)

add_library(gwdate STATIC date.cpp date.h)

set_target_properties(gwdate PROPERTIES
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      )
