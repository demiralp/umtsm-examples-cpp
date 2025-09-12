#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-06-08 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# ExecutionDirector
#
# LIBExecutionDirector_SOURCE_EXTRA
#set(LIBExecutionDirector_SOURCE_EXTRA )
# LIBExecutionDirector_HEADER_EXTRA
#set(LIBExecutionDirector_HEADER_EXTRA )
# LIBExecutionDirector_LIB_EXTRA
#set(LIBExecutionDirector_LIB_EXTRA )
# LIBExecutionDirector_INCLUDES_EXTRA
set(LIBExecutionDirector_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/src/crossroad
    ${CMAKE_SOURCE_DIR}/generated/src/dashboard
    ${CMAKE_SOURCE_DIR}/generated/src/execution-director
    ${CMAKE_SOURCE_DIR}/generated/src/lane
    ${CMAKE_SOURCE_DIR}/generated/src/monitor
    ${CMAKE_SOURCE_DIR}/generated/src/pedestrian-light
    ${CMAKE_SOURCE_DIR}/generated/src/trafficlight
)
# TESTExecutionDirector_INCLUDES_EXTRA
set(TESTExecutionDirector_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/test/crossroad
    ${CMAKE_SOURCE_DIR}/generated/test/monitor
)
# TESTExecutionDirector_LIB_EXTRA
set(TESTExecutionDirector_LIB_EXTRA 
    LIBRCrossroad_Static
    LIBRDashboard_Static
    LIBRLane_Static
    LIBRMonitor_Static
    LIBRTrafficLight_Static
    LIBRPedestrianLights_Static
    -lncurses
)
