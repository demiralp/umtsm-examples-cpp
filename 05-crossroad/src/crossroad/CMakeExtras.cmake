#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-06-08 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# Crossroad
#
# LIBCrossroad_SOURCE_EXTRA
#set(LIBCrossroad_SOURCE_EXTRA )
# LIBCrossroad_HEADER_EXTRA
#set(LIBCrossroad_HEADER_EXTRA )
# LIBCrossroad_LIB_EXTRA
#set(LIBCrossroad_LIB_EXTRA )
# LIBCrossroad_INCLUDES_EXTRA
set(LIBCrossroad_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/src/dashboard
    ${CMAKE_SOURCE_DIR}/generated/src/execution-director
    ${CMAKE_SOURCE_DIR}/generated/src/lane
    ${CMAKE_SOURCE_DIR}/generated/src/pedestrian-light
    ${CMAKE_SOURCE_DIR}/generated/src/trafficlight
)
# TESTCrossroad_INCLUDES_EXTRA
set(TESTCrossroad_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/test/dashboard/unittest
    ${CMAKE_SOURCE_DIR}/generated/test/execution-director/unittest
    ${CMAKE_SOURCE_DIR}/generated/test/lane/unittest
    ${CMAKE_SOURCE_DIR}/generated/test/trafficlight/unittest
    ${CMAKE_SOURCE_DIR}/generated/test/pedestrian-light/unittest
    ${CMAKE_SOURCE_DIR}/generated/test/monitor/unittest
    ${CMAKE_SOURCE_DIR}/generated/src/pedestrian-light
    ${CMAKE_SOURCE_DIR}/generated/src/monitor
)
# TESTCrossroad_LIB_EXTRA
set(TESTCrossroad_LIB_EXTRA
    LIBRDashboard_Static
    LIBRLane_Static
    LIBRTrafficLight_Static
    LIBRMonitor_Static
    LIBRPedestrianLights_Static
    LIBRExecutionDirector_Static
    -lncurses
)
