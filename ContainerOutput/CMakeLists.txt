cmake_minimum_required(VERSION 3.5)

project(gwLogger) 

add_library(gwLogger STATIC gwLogger.cpp gwLogger.h)   # can be SHARED (dll)
    
set_target_properties(gwLogger PROPERTIES      
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      )


