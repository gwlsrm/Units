cmake_minimum_required(VERSION 3.5)

project(CnfReader) 

message("text")
if (WIN64)
	message("windows")
	set(SOURCE serial_port_winapi.cpp serial_port_winapi.h)
else()
	message("linux")
	set(SOURCE serial_port_linapi.cpp serial_port_linapi.h)
endif()

add_library(serial_port STATIC ${SOURCE})   # can be SHARED (dll)
    
set_target_properties(serial_port PROPERTIES      
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      )
                      
target_include_directories( # include library dir
        serial_port
        PRIVATE         
        ${CMAKE_CURRENT_SOURCE_DIR}/../ContainerOutput
)


