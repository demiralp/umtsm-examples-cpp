cmake_minimum_required( VERSION 3.20 )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/generated/src/paroot)

# The project
set(MAIN_SOURCE
    main.cpp
)

set(MAIN_HEADER
)

add_executable(paroot ${MAIN_SOURCE} ${MAIN_HEADER})
target_link_libraries(paroot PUBLIC LIBRParoot_Static)
