cmake_minimum_required( VERSION 3.20 )

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(VERSION 1.0)
project(UMTSM-PAROOT-TEST VERSION ${VERSION} LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Setup gTest
find_package(PkgConfig)
find_package(GTest)

enable_testing()
include_directories(${GTEST_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(generated)
add_subdirectory(src/main)

# End CMakeList.txt
