cmake_minimum_required(VERSION 3.5)

project(BinFStream) 

add_library(bintext_fstream STATIC bintext_fstream.cpp bintext_fstream.h)   # can be SHARED (dll)
    
set_target_properties(bintext_fstream PROPERTIES      
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      )


