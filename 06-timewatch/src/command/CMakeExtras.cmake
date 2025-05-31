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
set(TESTCommand_LIB_EXTRA -lncurses)
