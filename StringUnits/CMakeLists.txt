cmake_minimum_required(VERSION 3.5)

project(str_utils)

set(SRC_STR_UTILS str_utils.cpp param_str_utils.cpp
        fileutils.cpp  #metrologic_round.cpp
        )
set(HEADER_STR_UTILS str_utils.h param_str_utils.h
        fileutils.h  #metrologic_round.cpp
        )

# library
add_library(str_utils STATIC ${SRC_STR_UTILS} ${HEADER_STR_UTILS})

# tests
if (USE_TEST)
    set(TEST_NAME test_str_utils)
    add_executable(${TEST_NAME} tests/str_utils_boost_ut.cpp)

#    set_target_properties(${TEST_NAME} PROPERTIES
#            CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
#            COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#            )
    target_include_directories(${TEST_NAME}
            PRIVATE ${Boost_INCLUDE_DIR}
            PRIVATE ${STR_UNITS}
            )

    # link to tests
    target_link_libraries(${TEST_NAME}
            str_utils
            ${Boost_LIBRARIES}
            )

    # tests
    add_test(str_tests ${TEST_NAME})
endif()



