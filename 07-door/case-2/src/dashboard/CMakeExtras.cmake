#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-05-29 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# Dashboard
#
#set(LIBDashboard_SOURCE_EXTRA )
#set(LIBDashboard_HEADER_EXTRA )
set(LIBDashboard_LIB_EXTRA -lncurses)
set(LIBDashboard_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/src/door
    ${CMAKE_SOURCE_DIR}/generated/src/button
    ${CMAKE_SOURCE_DIR}/generated/src/engine
    ${CMAKE_SOURCE_DIR}/generated/src/sensor_close_end
    ${CMAKE_SOURCE_DIR}/generated/src/sensor_open_end
)
set(TESTDashboard_INCLUDES_EXTRA 
    ${CMAKE_SOURCE_DIR}/generated/test/door/unittest
    ${CMAKE_SOURCE_DIR}/generated/test/button/unittest
    ${CMAKE_SOURCE_DIR}/generated/test/engine/unittest
    ${CMAKE_SOURCE_DIR}/generated/test/sensor_close_end/unittest
    ${CMAKE_SOURCE_DIR}/generated/test/sensor_open_end/unittest
)
set(TESTDashboard_LIB_EXTRA
    LIBRDoor_Static
    LIBREngine_Static
    LIBRSensor_Open_End_Static
    LIBRSensor_Close_End_Static
    LIBRButton_Static
    -lncurses
)
