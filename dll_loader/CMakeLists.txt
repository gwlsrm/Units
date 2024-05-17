cmake_minimum_required(VERSION 3.5)

project(dll_loader)

add_library(dll_loader STATIC dll_loader.cpp dll_loader.h)
    
set_target_properties(dll_loader PROPERTIES      
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON
                      )


