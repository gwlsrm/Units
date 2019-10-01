cmake_minimum_required(VERSION 3.5)

project(MetrNumbers) 

add_library(metr_number STATIC metr_number.cpp metr_number.h)   # can be SHARED (dll)
    
set_target_properties(metr_number PROPERTIES      
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      )


