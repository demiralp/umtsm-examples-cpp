#
#  ==============================================================================
#  Created by Fehmi Demiralp(Fedem) on 2025-04-10 GMT
#  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
#
#  Released under the MIT License
#  ============================================================================
#

#
# Calculator
#
set(LIBCalculator_SOURCE_EXTRA Calculator_Utilities.cpp)
set(LIBCalculator_HEADER_EXTRA Calculator_Utilities.hh)
#set(LIBCalculator_LIB_EXTRA )
#set(LIBCalculator_INCLUDES_EXTRA "${CMAKE_CURRRENT_SOURCE_DIR}")
set(TESTCalculator_LIB_EXTRA LIBRKeypad_Shared LIBRDisplay_Shared -lncurses)

#
# Keypad
#
#set(LIBKeypad_SOURCE_EXTRA )
#set(LIBKeypad_HEADER_EXTRA )
#set(LIBKeypad_LIB_EXTRA )
#set(LIBKeypad_INCLUDES_EXTRA "${CMAKE_CURRRENT_SOURCE_DIR}")
set(TESTKeypad_LIB_EXTRA LIBRCalculator_Static LIBRDisplay_Static -lncurses)

#
# Display
#
set(LIBDisplay_SOURCE_EXTRA Display_Utilities.cpp)
set(LIBDisplay_HEADER_EXTRA Display_Utilities.hh)
#set(LIBDisplay_LIB_EXTRA )
#set(LIBDisplay_INCLUDES_EXTRA "${CMAKE_CURRRENT_SOURCE_DIR}")
set(TESTDisplay_LIB_EXTRA -lncurses)
