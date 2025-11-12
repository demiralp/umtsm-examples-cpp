#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-05-29 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# Button
#
#set(LIBButton_SOURCE_EXTRA )
#set(LIBButton_HEADER_EXTRA )
set(LIBButton_LIB_EXTRA -lncurses)
set(LIBButton_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/src/door
)
set(TESTButton_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/test/door/unittest
)
set(TESTButton_LIB_EXTRA
    LIBRDoor_Static
    LIBREngine_Static
    -lncurses
)
