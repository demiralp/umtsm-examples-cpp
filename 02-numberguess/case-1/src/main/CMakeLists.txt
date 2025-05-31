cmake_minimum_required( VERSION 3.20 )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/generated/src/numberguess)

# The project
set(MAIN_SOURCE
    main.cpp
)

set(MAIN_HEADER
)

add_executable(guess ${MAIN_SOURCE} ${MAIN_HEADER})
target_link_libraries(guess PRIVATE LIBRNumberGuess_Static)
