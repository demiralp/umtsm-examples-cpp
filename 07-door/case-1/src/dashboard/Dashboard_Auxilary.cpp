/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-30 GMT
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

#include "Dashboard.hh"

#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <optional>
#include <thread>
#include <unistd.h>

#include <ncurses.h>

#include <Door.hh>
#include <Button.hh>
#include <Engine.hh>
#include <Sensor_Close_End.hh>
#include <Sensor_Open_End.hh>

static void PrintHelpLine( char const* const key, char const* const summary );
static void PrintHelp(
  [[maybe_unused]] Dashboard* const smInfo,
  [[maybe_unused]] Dashboard_DataType const* const pInstanceData );

// The implementation of the guards
bool Dashboard::IsKey_B( ) const
{
  bool const result = toupper( instanceData.LastInputKey ) == 'B';
  return result;
}  // End of guard function: IsKey_B

// The implementation of the actions
void Dashboard::ButtonPress( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pButton->trigger_Pressed();
}  // End of action function: ButtonPress

void Dashboard::DisplayDoorStatus( [[maybe_unused]] Dashboard_DataType const& input )
{
  while( true )
  {
    usleep( 200000 );

    clear( );

    /* Door Working Mode */
    {
      char const* const wmode = "Manual";

      attron( COLOR_PAIR( 1 ) );
      printw( "%-19s :", "Door Working Mode" );
      attroff( COLOR_PAIR( 1 ) );

      attron( COLOR_PAIR( 2 ) );
      printw( " %s\n", wmode );
      attroff( COLOR_PAIR( 2 ) );
    }

    /* Door status */
    {
      char const* st = NULL;
      int color= 0;

      if( instanceData.pDoor->isIn_Open_State() )
      {
        st = "Open";
        color= 5; // GREEN
      }
      else if( instanceData.pDoor->isIn_Close_State() )
      {
        st = "Closed";
        color= 3; // RED
      }
      else if( instanceData.pDoor->isIn_Opening_State() )
      {
        st = "Opening ...";
        color = 6; // WHITE 
      }
      else if( instanceData.pDoor->isIn_Closing_State() )
      {
        st = "Closing ...";
        color = 4; // YELLOW
      }

      attron( COLOR_PAIR( 1 ) );
      printw( "%-19s :", "Door Status" );
      attroff( COLOR_PAIR( 1 ) );

      attron( COLOR_PAIR( color ) );
      printw( " %s\n", st );
      attroff( COLOR_PAIR( color ) );
    }

    /* Engine Mode */
    {
      char const* engmode = NULL;

      if( instanceData.pEngine->isIn_Idle_State() )
      {
        engmode = "Idle";
      }
      else if( instanceData.pEngine->isIn_CCW_State() )
      {
        engmode = "CCW";
      }
      else if( instanceData.pEngine->isIn_ACCW_State() )
      {
        engmode = "Anti CCW";
      }

      attron( COLOR_PAIR( 1 ) );
      printw( "%-19s :", "Engine Working Mode" );
      attroff( COLOR_PAIR( 1 ) );

      attron( COLOR_PAIR( 2 ) );
      printw( " %s\n", engmode );
      attroff( COLOR_PAIR( 2 ) );
    }

    /* Sensor Close End */
    {
      char const* sclose = NULL;

      if( instanceData.pCloseEnd->isIn_Idle_State() )
      {
        sclose = "Idle";
      }
      else if( instanceData.pCloseEnd->isIn_Check_State() )
      {
        sclose = "Check";
      }

      attron( COLOR_PAIR( 1 ) );
      printw( "%-19s :", "Sensor Close End" );
      attroff( COLOR_PAIR( 1 ) );

      attron( COLOR_PAIR( 2 ) );
      printw( " %s\n", sclose );
      attroff( COLOR_PAIR( 2 ) );
    }

    /* Sensor Open End */
    {
      char const* sopen = NULL;

      if( instanceData.pOpenEnd->isIn_Idle_State() )
      {
        sopen = "Idle";
      }
      else if( instanceData.pOpenEnd->isIn_Check_State() )
      {
        sopen = "Check";
      }

      attron( COLOR_PAIR( 1 ) );
      printw( "%-19s :", "Sensor Open End" );
      attroff( COLOR_PAIR( 1 ) );

      attron( COLOR_PAIR( 2 ) );
      printw( " %s\n", sopen );
      attroff( COLOR_PAIR( 2 ) );
    }

    PrintHelp( this, &instanceData );
    refresh( );
  }
}  // End of action function: DisplayDoorStatus

void Dashboard::ReadCommand( [[maybe_unused]] Dashboard_DataType const& input )
{
  static char const* const keyChar = "Bb";
  bool okay                        = false;
  int ch;

  do
  {
    ch   = wgetch( stdscr );
    okay = strchr( keyChar, ch ) != NULL;
  } while( ! okay );

  instanceData.LastInputKey = ch;
}  // End of action function: ReadCommand

static void PrintHelpLine( char const* const key, char const* const summary )
{
  attron( COLOR_PAIR( 7 ) );
  printw( "%-6s :", key );
  attroff( COLOR_PAIR( 7 ) );

  attron( COLOR_PAIR( 8 ) );
  printw( " %s\n", summary );
  attroff( COLOR_PAIR( 8 ) );
}

static void PrintHelp(
  [[maybe_unused]] Dashboard* const smInfo,
  [[maybe_unused]] Dashboard_DataType const* const pInstanceData )
{
  printw( "Keys for controlling the door\n" );

  PrintHelpLine( "B", "Button press" );

  PrintHelpLine( "Ctrl+C", "Terminate immediately" );
}

// End of Dashboard_Auxilary.cpp
