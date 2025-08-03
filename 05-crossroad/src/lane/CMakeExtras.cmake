#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-06-08 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# Lane
#
#set(LIBLane_SOURCE_EXTRA )
#set(LIBLane_HEADER_EXTRA )
#set(LIBLane_LIB_EXTRA )
set(LIBLane_INCLUDES_EXTRA ${CMAKE_SOURCE_DIR}/generated/src/crossroad)
set(TESTLane_INCLUDES_EXTRA ${CMAKE_SOURCE_DIR}/generated/src/crossroad)
set(TESTLane_LIB_EXTRA 
    LIBRCrossroad_Static
    LIBRDashboard_Static
    LIBRExecutionDirector_Static
    LIBRMonitor_Static
    LIBRTrafficLight_Static
    LIBRPedestrianLights_Static
    -lncurses
)
