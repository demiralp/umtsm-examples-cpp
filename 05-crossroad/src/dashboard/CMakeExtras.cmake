#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-06-08 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# Dashboard
#
# LIBDashboard_SOURCE_EXTRA
#set(LIBDashboard_SOURCE_EXTRA )
# LIBDashboard_HEADER_EXTRA
#set(LIBDashboard_HEADER_EXTRA )
# LIBDashboard_LIB_EXTRA
set(LIBDashboard_LIB_EXTRA -lncurses)
# LIBDashboard_INCLUDES_EXTRA
set(LIBDashboard_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/src/crossroad
    ${CMAKE_SOURCE_DIR}/generated/src/execution-director
    ${CMAKE_SOURCE_DIR}/generated/src/lane
    ${CMAKE_SOURCE_DIR}/generated/src/monitor
    ${CMAKE_SOURCE_DIR}/generated/src/pedestrian-light
    ${CMAKE_SOURCE_DIR}/generated/src/trafficlight
)
# TESTDashboard_INCLUDES_EXTRA
set(TESTDashboard_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/test/crossroad
    ${CMAKE_SOURCE_DIR}/generated/test/execution-director
    ${CMAKE_SOURCE_DIR}/generated/test/monitor
)
# TESTDashboard_LIB_EXTRA
set(TESTDashboard_LIB_EXTRA
    LIBRCrossroad_Static
    LIBRExecutionDirector_Static
    LIBRLane_Static
    LIBRMonitor_Static
    LIBRTrafficLight_Static
    LIBRPedestrianLights_Static
    -lncurses
)
