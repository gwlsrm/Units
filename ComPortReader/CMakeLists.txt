cmake_minimum_required(VERSION 3.5)

project(serial_reader)

if (WIN32)
	set(SOURCE serial_port_winapi.cpp serial_port_winapi.h)
else()
	set(SOURCE serial_port_linapi.cpp serial_port_linapi.h)
endif()

add_library(serial_reader STATIC ${SOURCE})

