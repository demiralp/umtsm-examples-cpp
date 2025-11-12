#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-05-31 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ==============================================================================
#

#
# Command
#
#set(LIBCommand_SOURCE_EXTRA )
#set(LIBCommand_HEADER_EXTRA )
set(LIBCommand_LIB_EXTRA -lncurses)
set(LIBCommand_INCLUDES_EXTRA
    ${CMAKE_SOURCE_DIR}/generated/src/command
    ${CMAKE_SOURCE_DIR}/generated/src/timewatch
)
set(TESTCommand_INCLUDES_EXTRA ${CMAKE_SOURCE_DIR}/generated/test/timewatch/unittest)
set(TESTCommand_LIB_EXTRA 
    LIBRTimewatch_Static
    -lncurses)
