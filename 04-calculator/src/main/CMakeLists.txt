cmake_minimum_required( VERSION 3.20 )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/generated/src/calculator)

# The project
set(MAIN_SOURCE
    main.cpp
)

set(MAIN_HEADER
)

add_executable(calculator ${MAIN_SOURCE} ${MAIN_HEADER})
target_link_libraries(calculator PUBLIC LIBRCalculator_Static)
target_link_libraries(calculator PUBLIC LIBRKeypad_Static)
target_link_libraries(calculator PUBLIC LIBRDisplay_Static)
target_link_libraries(calculator PUBLIC -lncurses)
