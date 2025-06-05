/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-10 GMT
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

#include "KeyPress.hh"
#include "KeyPressEventGenerator.hh"

#include <cassert>
#include <chrono>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <optional>
#include <thread>

#include <unistd.h>

#include <ncurses.h>

// The implementation of the actions
void KeyPressEventGenerator::ReadKey( KeyPressEventGenerator_DataType const& input )
{
  char prev = 0;

  while( true )
  {
    int c = wgetch( stdscr );

    clrtoeol( );
    refresh( );

    switch( c )
    {
      case 'A':
        [[fallthrough]];
      case 'a':
      {
        instanceData.sm_keypress->trigger_keyA( );
        break;
      }
      case 'B':
        [[fallthrough]];
      case 'b':
      {
        instanceData.sm_keypress->trigger_keyB( );
        break;
      }
      case 'C':
        [[fallthrough]];
      case 'c':
      {
        instanceData.sm_keypress->trigger_keyC( );
        break;
      }
      case 'R':
        [[fallthrough]];
      case 'r':
      {
        instanceData.sm_keypress->trigger_space( );
        break;
      }
      case '1':
      {
        instanceData.sm_keypress->trigger_key1( );
        break;
      }
      case '2':
      {
        instanceData.sm_keypress->trigger_key2( );
        break;
      }
      case '3':
      {
        instanceData.sm_keypress->trigger_key3( );
        break;
      }
      case '4':
      {
        instanceData.sm_keypress->trigger_key4( );
        break;
      }
      case '5':
      {
        instanceData.sm_keypress->trigger_key5( );
        break;
      }
      case '6':
      {
        instanceData.sm_keypress->trigger_key6( );
        break;
      }
      case '7':
      {
        instanceData.sm_keypress->trigger_key7( );
        break;
      }
      case '8':
      {
        instanceData.sm_keypress->trigger_key8( );
        break;
      }
      case '9':
      {
        instanceData.sm_keypress->trigger_key9( );
        break;
      }
      case KEY_BACKSPACE:
        [[fallthrough]];
      case KEY_DC:
      {
        instanceData.sm_keypress->trigger_keyDelete( );
        break;
      }
      case ' ':
      {
        instanceData.sm_keypress->trigger_space( );
        break;
      }
      case KEY_F( 1 ):
      {
        instanceData.sm_keypress->trigger_keyF1( );
        break;
      }
      case KEY_F( 2 ):
      {
        instanceData.sm_keypress->trigger_keyF2( );
        break;
      }
      case KEY_F( 12 ):
      {
        printw( "   F12" );
        instanceData.sm_keypress->trigger_keyF12( );
        break;
      }
      default:
      {
        prev = 0;
        break;
      }
    }
  }
}  // End of action function: ReadKey

void KeyPressEventGenerator::TimeBaseEventGenerator( KeyPressEventGenerator_DataType const& input )
{
  clock_t start, end;
  unsigned long long duration;

  while( true )
  {
    start = clock( );
    instanceData.sm_keypress->trigger_clock4log( );
    end      = clock( );
    duration = static_cast< unsigned long long >( 1000000.0 * ( end - start ) / CLOCKS_PER_SEC );
    std::this_thread::sleep_for( std::chrono::microseconds( 20000 - duration ) );
  }
}  // End of action function: TimeBaseEventGenerator

// End of KeyPressEventGenerator_Auxilary.cpp
