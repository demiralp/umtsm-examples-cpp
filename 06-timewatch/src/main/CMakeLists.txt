cmake_minimum_required( VERSION 3.20 )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/generated/src/timewatch)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/command)

# The project
set(MAIN_SOURCE
    main.cpp
)

set(MAIN_HEADER
)

add_executable(timewatch ${MAIN_SOURCE} ${MAIN_HEADER})
target_link_libraries(timewatch PUBLIC
    LIBRTimewatch_Static
    LIBRCommand_Static
    -lncurses
)
