#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-06-08 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# Monitor
#
# LIBMonitor_SOURCE_EXTRA
#set(LIBMonitor_SOURCE_EXTRA )
# LIBMonitor_HEADER_EXTRA
#set(LIBMonitor_HEADER_EXTRA )
# LIBMonitor_LIB_EXTRA
set(LIBMonitor_LIB_EXTRA -lncurses)
# LIBMonitor_INCLUDES_EXTRA
set(LIBMonitor_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/src/crossroad
    ${CMAKE_SOURCE_DIR}/generated/src/execution-director
    ${CMAKE_SOURCE_DIR}/generated/src/lane
    ${CMAKE_SOURCE_DIR}/generated/src/pedestrian-light
    ${CMAKE_SOURCE_DIR}/generated/src/trafficlight
)
# TESTMonitor_INCLUDES_EXTRA
set(TESTMonitor_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/test/crossroad
    ${CMAKE_SOURCE_DIR}/generated/test/execution-director
    ${CMAKE_SOURCE_DIR}/generated/test/lane
    ${CMAKE_SOURCE_DIR}/generated/test/pedestrian-light
    ${CMAKE_SOURCE_DIR}/generated/test/trafficlight
)
# TESTMonitor_LIB_EXTRA
set(TESTMonitor_LIB_EXTRA 
    LIBRCrossroad_Static
    LIBRDashboard_Static
    LIBRExecutionDirector_Static
    LIBRLane_Static
    LIBRTrafficLight_Static
    LIBRPedestrianLights_Static
    -lncurses
)
