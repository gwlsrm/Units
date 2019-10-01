cmake_minimum_required(VERSION 3.5)

project(DllLoader) 

add_library(dll_loader STATIC dll_loader.cpp dll_loader.h)   # can be SHARED (dll)
    
set_target_properties(dll_loader PROPERTIES      
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      )


