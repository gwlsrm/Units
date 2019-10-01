cmake_minimum_required(VERSION 3.5)

project(CnfReader) 

add_library(cnfreader STATIC cnfreader.cpp cnfreader.h)   # can be SHARED (dll)
    
set_target_properties(cnfreader PROPERTIES      
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON
                      )
                      
target_include_directories( # include library dir
        cnfreader
        PRIVATE         
        ${CMAKE_CURRENT_SOURCE_DIR}/../StringUnits
)

target_link_libraries(cnfreader str_utils) # link library from lib dir


