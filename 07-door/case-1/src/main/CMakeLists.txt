cmake_minimum_required( VERSION 3.20 )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/generated/src/door)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/button)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/engine)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/sensor_close_end)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/sensor_open_end)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/dashboard)

# The project
set(MAIN_SOURCE
    main.cpp
)

set(MAIN_HEADER
)

add_executable(door ${MAIN_SOURCE} ${MAIN_HEADER})
target_link_libraries(door PRIVATE LIBRDoor_Static)
target_link_libraries(door PRIVATE LIBRButton_Static)
target_link_libraries(door PRIVATE LIBREngine_Static)
target_link_libraries(door PRIVATE LIBRSensor_Close_End_Static)
target_link_libraries(door PRIVATE LIBRSensor_Open_End_Static)
target_link_libraries(door PRIVATE LIBRDashboard_Static)
target_link_libraries(door PRIVATE -lncurses)
