#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-05-29 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# Door
#
#set(LIBDoor_SOURCE_EXTRA )
#set(LIBDoor_HEADER_EXTRA )
set(LIBDoor_LIB_EXTRA -lncurses)
set(LIBDoor_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/src/engine
)
set(TESTDoor_INCLUDES_EXTRA ${CMAKE_SOURCE_DIR}/generated/test/engine)
set(TESTDoor_LIB_EXTRA 
    LIBREngine_Static
    -lncurses
)
