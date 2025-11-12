#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-06-08 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# PedestrianLights
#
# LIBPedestrianLights_SOURCE_EXTRA
#set(LIBPedestrianLights_SOURCE_EXTRA )
# LIBPedestrianLights_HEADER_EXTRA
#set(LIBPedestrianLights_HEADER_EXTRA )
# LIBPedestrianLights_LIB_EXTRA
#set(LIBPedestrianLights_LIB_EXTRA )
# LIBPedestrianLights_INCLUDES_EXTRA
set(LIBPedestrianLights_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/src/crossroad
    ${CMAKE_SOURCE_DIR}/generated/src/dashboard
    ${CMAKE_SOURCE_DIR}/generated/src/execution-director
    ${CMAKE_SOURCE_DIR}/generated/src/lane
    ${CMAKE_SOURCE_DIR}/generated/src/monitor
    ${CMAKE_SOURCE_DIR}/generated/src/pedestrian-light
    ${CMAKE_SOURCE_DIR}/generated/src/trafficlight
)
# TESTPedestrianLights_INCLUDES_EXTRA
set(TESTPedestrianLights_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/test/crossroad/unittest
    ${CMAKE_SOURCE_DIR}/generated/test/execution-director/unittest
    ${CMAKE_SOURCE_DIR}/generated/test/monitor/unittest
)
# TESTPedestrianLights_LIB_EXTRA
set(TESTPedestrianLights_LIB_EXTRA 
    LIBRDashboard_Static
    LIBRMonitor_Static
    LIBRTrafficLight_Static
    LIBRCrossroad_Static
    LIBRLane_Static
    LIBRExecutionDirector_Static
    -lncurses
)
