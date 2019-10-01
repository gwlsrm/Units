cmake_minimum_required(VERSION 3.5)

project(GwUnits) 

add_subdirectory(BinaryFStream)   # cmake will search cmake lists in these dirs
add_subdirectory(CnfReader)
add_subdirectory(ComPortReader)
add_subdirectory(ContainerOutput)
add_subdirectory(Date)
add_subdirectory(dll_loader)
add_subdirectory(Math)
add_subdirectory(MetrologicNumbers)
add_subdirectory(profiler)
add_subdirectory(StringUnits)



