cmake_minimum_required(VERSION 3.10)

project(GwUnits)

# Root of the whole Units repository. Used by individual modules to expose
# their public include directories via target_include_directories(), so that
# cross-module includes like "StringUnits/str_utils.h" or
# "Algorithm/dictionary.h" keep working
set(UNITS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Whether Units is being built as the top-level project (i.e. built directly,
# not pulled in via add_subdirectory()/FetchContent() from another project).
# Used to keep tests/examples opt-in by default when Units is consumed as a
# dependency, so it never forces Boost or extra build targets onto consumers.
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(UNITS_IS_TOP_LEVEL ON)
else()
    set(UNITS_IS_TOP_LEVEL OFF)
endif()

# Namespaced options (UNITS_ prefix) to avoid clashing with identically named
# variables/options (USE_TEST, BUILD_EXAMPLE, ...) that a parent project might
# already define for its own purposes. Defaulting to UNITS_IS_TOP_LEVEL means
# tests/examples are built when you work on Units itself, but stay off when
# Units is included as a dependency of another project.
option(UNITS_BUILD_TESTS "Build Units unit tests" ${UNITS_IS_TOP_LEVEL})
option(UNITS_BUILD_EXAMPLES "Build Units examples" ${UNITS_IS_TOP_LEVEL})

if (UNITS_BUILD_TESTS AND NOT Boost_FOUND)
    if(WIN32)
        #set(Boost_DEBUG 1)
        #set(Boost_COMPILER -mgw93)
        set(Boost_ARCHITECTURE -x32)
        set(Boost_USE_STATIC_LIBS ON)
    endif()
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    enable_testing()
endif()

add_subdirectory(Algorithm)
add_subdirectory(BinaryFStream)
add_subdirectory(CnfReader)
add_subdirectory(ContainerOutput)
add_subdirectory(csv)
add_subdirectory(Date)
add_subdirectory(dll_loader)
add_subdirectory(IniParser)
add_subdirectory(Math)
add_subdirectory(MetrologicNumbers)
add_subdirectory(profiler)
add_subdirectory(StringUnits)
