cmake_minimum_required(VERSION 3.5)

project(MathLib) 

add_library(geom_lib STATIC geom_lib.cpp geom_lib.h)
add_library(gw_algorithm STATIC gw_algorithm.cpp gw_algorithm.h)
add_library(gwmatrix STATIC gwmatrix.cpp gwmatrix.h)
add_library(gw_solid_matrix STATIC gw_solid_matrix.cpp gw_solid_matrix.h)
add_library(gw_triangle_matrix STATIC gw_triangle_matrix.cpp gw_triangle_matrix.h)
add_library(interpol STATIC interpol.cpp interpol.h)
add_library(leastsquares STATIC leastsquares.cpp leastsquares.h)
add_library(math_lib STATIC math_lib.cpp math_lib.h)
add_library(nonlinearsolver STATIC nonlinearsolver.cpp nonlinearsolver.h)
add_library(numeric_integration STATIC numeric_integration.cpp numeric_integration.h)
add_library(sle STATIC sle.cpp sle.h)
    
set_target_properties(geom_lib PROPERTIES CXX_STANDARD 14)
set_target_properties(gw_algorithm PROPERTIES CXX_STANDARD 14)
set_target_properties(gwmatrix PROPERTIES CXX_STANDARD 14)
set_target_properties(gw_solid_matrix PROPERTIES CXX_STANDARD 14)
set_target_properties(gw_triangle_matrix PROPERTIES CXX_STANDARD 14)
set_target_properties(interpol PROPERTIES CXX_STANDARD 14)
set_target_properties(leastsquares PROPERTIES CXX_STANDARD 14)
set_target_properties(math_lib PROPERTIES CXX_STANDARD 14)
set_target_properties(nonlinearsolver PROPERTIES CXX_STANDARD 14)
set_target_properties(numeric_integration PROPERTIES CXX_STANDARD 14)
set_target_properties(sle PROPERTIES CXX_STANDARD 14)


