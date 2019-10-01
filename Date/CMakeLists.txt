cmake_minimum_required(VERSION 3.5)

project(Date) 

add_library(gwDate STATIC date.cpp date.h)   # can be SHARED (dll)
    
set_target_properties(gwDate PROPERTIES      
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      )


