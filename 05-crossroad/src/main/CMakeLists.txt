cmake_minimum_required( VERSION 3.20 )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/generated/src/crossroad)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/dashboard)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/execution-director)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/lane)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/monitor)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/trafficlight)
include_directories(${CMAKE_SOURCE_DIR}/generated/src/pedestrian-light)

# The project
set(MAIN_SOURCE
    main.cpp
)

set(MAIN_HEADER
)

add_executable(crossroad ${MAIN_SOURCE} ${MAIN_HEADER})
target_link_libraries(crossroad PUBLIC
    LIBRCrossroad_Static
    LIBRDashboard_Static
    LIBRExecutionDirector_Static
    LIBRLane_Static
    LIBRMonitor_Static
    LIBRTrafficLight_Static
    LIBRPedestrianLights_Static
    -lncurses
)
