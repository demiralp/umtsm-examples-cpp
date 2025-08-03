/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-06 GMT
 *  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
 *
 *  Released under the MIT License
 *  ==============================================================================
 */

/*  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include "Command.hh"

#include "Timewatch.hh"

#include <ncurses.h>
#include <unistd.h>

// The implementation of the guards
bool Command::isKeyHPressed( ) const
{
  bool const result = ( instanceData.key == 'h' || instanceData.key == 'H' );
  return result;
}  // End of guard function: isKeyHPressed

bool Command::isKeyPPressed( ) const
{
  bool const result = ( instanceData.key == 'p' || instanceData.key == 'P' );
  return result;
}  // End of guard function: isKeyPPressed

bool Command::isKeyQPressed( ) const
{
  bool const result = ( instanceData.key == 'q' || instanceData.key == 'Q' );
  return result;
}  // End of guard function: isKeyQPressed

bool Command::isKeyRPressed( ) const
{
  bool const result = ( instanceData.key == 'r' || instanceData.key == 'R' );
  return result;
}  // End of guard function: isKeyRPressed

bool Command::isKeySPressed( ) const
{
  bool const result = ( instanceData.key == 's' || instanceData.key == 'S' );
  return result;
}  // End of guard function: isKeySPressed

bool Command::isKeyXPressed( ) const
{
  bool const result = ( instanceData.key == 'x' || instanceData.key == 'X' );
  return result;
}  // End of guard function: isKeyXPressed

bool Command::isKeyZPressed( ) const
{
  bool const result = ( instanceData.key == 'z' || instanceData.key == 'Z' );
  return result;
}  // End of guard function: isKeyZPressed

bool Command::isSpacePressed( ) const
{
  bool const result = ( instanceData.key == ' ' );
  return result;
}  // End of guard function: isSpacePressed

// The implementation of the actions
void Command::ReadKey( [[maybe_unused]] Command_DataType const& input )
{
  instanceData.key = wgetch( stdscr );
}  // End of action function: ReadKey

void Command::SendAbortEvent( [[maybe_unused]] Command_DataType const& input )
{
  instanceData.timer->trigger_abort( );
}  // End of action function: SendAbortEvent

void Command::SendHelpEvent( [[maybe_unused]] Command_DataType const& input )
{
  instanceData.timer->trigger_help( );
}  // End of action function: SendHelpEvent

void Command::SendPauseEvent( [[maybe_unused]] Command_DataType const& input )
{
  instanceData.timer->trigger_pause( );
}  // End of action function: SendPauseEvent

void Command::SendPrintLapsEvent( [[maybe_unused]] Command_DataType const& input )
{
  instanceData.timer->trigger_print( );
}  // End of action function: SendPrintLapsEvent

void Command::SendRestartEvent( [[maybe_unused]] Command_DataType const& input )
{
  instanceData.timer->trigger_restart( );
}  // End of action function: SendRestartEvent

void Command::SendResumeEvent( [[maybe_unused]] Command_DataType const& input )
{
  instanceData.timer->trigger_resume( );
}  // End of action function: SendResumeEvent

void Command::SendStartEvent( [[maybe_unused]] Command_DataType const& input )
{
  instanceData.timer->trigger_start( );
}  // End of action function: SendStartEvent

void Command::SendStopEvent( [[maybe_unused]] Command_DataType const& input )
{
  instanceData.timer->trigger_stop( );
}  // End of action function: SendStopEvent

// End of Command_Auxilary.cpp
