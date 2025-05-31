cmake_minimum_required( VERSION 3.20 )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(VERSION 1.0)
project(UMTSM-PAROOT-TEST VERSION ${VERSION} LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CPP_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

# The project
set(MAIN_SOURCE
    Paroot.cpp
)

set(MAIN_HEADER
)

add_executable(paroot ${MAIN_SOURCE} ${MAIN_HEADER})
target_link_libraries(paroot PUBLIC -lm )
