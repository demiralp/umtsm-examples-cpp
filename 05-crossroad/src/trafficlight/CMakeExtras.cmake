#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-06-08 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# TrafficLight
#
#set(LIBTrafficLight_SOURCE_EXTRA )
#set(LIBTrafficLight_HEADER_EXTRA )
#set(LIBTrafficLight_LIB_EXTRA )
set(LIBTrafficLight_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/src/crossroad
    ${CMAKE_SOURCE_DIR}/generated/src/dashboard
    ${CMAKE_SOURCE_DIR}/generated/src/execution-director
    ${CMAKE_SOURCE_DIR}/generated/src/monitor
    ${CMAKE_SOURCE_DIR}/generated/src/lane
    ${CMAKE_SOURCE_DIR}/generated/src/pedestrian-light
    ${CMAKE_SOURCE_DIR}/generated/src/trafficlight
)
set(TESTTrafficLight_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/test/execution-director
    ${CMAKE_SOURCE_DIR}/generated/test/monitor
    ${CMAKE_SOURCE_DIR}/generated/test/lane
)
set(TESTTrafficLight_LIB_EXTRA 
    LIBRDashboard_Static
    LIBRExecutionDirector_Static
    LIBRCrossroad_Static
    LIBRLane_Static
    LIBRMonitor_Static
    LIBRPedestrianLights_Static
    -lncurses
)