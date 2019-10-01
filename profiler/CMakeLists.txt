cmake_minimum_required(VERSION 3.5)

project(Profile) 

add_library(profile_advanced STATIC profile_advanced.cpp profile_advanced.h)   # can be SHARED (dll)
    
set_target_properties(profile_advanced PROPERTIES      
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      )


