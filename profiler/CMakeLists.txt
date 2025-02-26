cmake_minimum_required(VERSION 3.10)

project(profile_advanced)

add_library(profile_advanced STATIC profile_advanced.cpp profile_advanced.h)

set_target_properties(profile_advanced PROPERTIES
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      )
