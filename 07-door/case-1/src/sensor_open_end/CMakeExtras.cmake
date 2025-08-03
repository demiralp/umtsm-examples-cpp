#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-05-29 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# Sensor_Open_End
#
#set(LIBSensor_Open_End_SOURCE_EXTRA )
#set(LIBSensor_Open_End_HEADER_EXTRA )
set(LIBSensor_Open_End_LIB_EXTRA -lncurses)
set(LIBSensor_Open_End_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/src/door
)
set(TESTSensor_Open_End_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/test/door
)
set(TESTSensor_Open_End_LIB_EXTRA
    LIBRDoor_Static
    LIBREngine_Static
    -lncurses
)
