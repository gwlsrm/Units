cmake_minimum_required(VERSION 3.5)

project(GwUnits)

if (USE_TEST AND NOT Boost_FOUND)
    if(WIN32)
        #set(Boost_DEBUG 1)
        #set(Boost_COMPILER -mgw93)
        set(Boost_ARCHITECTURE -x32)
        set(Boost_USE_STATIC_LIBS ON)
    endif()
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    enable_testing()
endif() 

include_directories(SYSTEM ${CMAKE_SOURCE_DIR})

add_subdirectory(Algorithm)
add_subdirectory(BinaryFStream)
add_subdirectory(CnfReader)
add_subdirectory(ComPortReader)
add_subdirectory(ContainerOutput)
add_subdirectory(csv)
add_subdirectory(Date)
add_subdirectory(dll_loader)
add_subdirectory(Math)
add_subdirectory(MetrologicNumbers)
add_subdirectory(profiler)
add_subdirectory(StringUnits)



