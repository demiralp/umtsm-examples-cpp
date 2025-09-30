/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-29 GMT
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

#include <Button.hh>
#include <Dashboard.hh>
#include <Door.hh>
#include <Engine.hh>
#include <Sensor_Close_End.hh>
#include <Sensor_Open_End.hh>

#include <atomic>
#include <csignal>
#include <cstdlib>
#include <iostream>

#include <ncurses.h>
#include <unistd.h>

std::atomic_flag blocker = ATOMIC_FLAG_INIT;

Door door;
Button button;
Engine engine;
Sensor_Close_End scloseend;
Sensor_Open_End sopenend;
Dashboard dashboard;

void signal_handler( int sig )
{
  switch( sig )
  {
    case SIGINT:
    {
      blocker.clear( );
      break;
    }
    default:
    {
      // blank
    }
  }
}

int main( )
{
  while( blocker.test_and_set( ) )
  {
    // blank
  }

  initscr( );

  if( has_colors( ) == FALSE )
  {
    endwin( );
    std::cerr << "Your terminal does not support color\n";
    return EXIT_FAILURE;
  }

  start_color( );
  init_pair( 1, COLOR_BLUE, 0 );
  init_pair( 2, COLOR_MAGENTA, 0 );

  init_pair( 3, COLOR_RED, 0 );
  init_pair( 4, COLOR_YELLOW, 0 );
  init_pair( 5, COLOR_GREEN, 0 );
  init_pair( 6, COLOR_WHITE, 0 );

  init_pair( 7, COLOR_YELLOW, 0 );
  init_pair( 8, COLOR_CYAN, 0 );

  noecho( );
  cbreak( );
  set_escdelay( 0 );
  clear( );
  refresh( );

  // Initialize entire the state machines
  door.instanceData.id      = "case-3";
  door.instanceData.pEngine = &engine;

  button.instanceData.pDoor = &door;

  scloseend.instanceData.pDoor = &door;
  sopenend.instanceData.pDoor  = &door;

  dashboard.instanceData.pButton   = &button;
  dashboard.instanceData.pDoor     = &door;
  dashboard.instanceData.pEngine   = &engine;
  dashboard.instanceData.pOpenEnd  = &sopenend;
  dashboard.instanceData.pCloseEnd = &scloseend;

  // Start entire the State Machines
  engine.start( );
  door.start( );
  button.start( );
  scloseend.start( );
  sopenend.start( );
  dashboard.start( );

  // Allow entire the state machines run for  indefinite time until CTRL-C is pressed
  signal( SIGINT, signal_handler );

  while( blocker.test_and_set( ) )
  {
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );
  }

  dashboard.halt( );
  sopenend.halt( );
  scloseend.halt( );
  button.halt( );
  door.halt( );
  engine.halt( );

  // exit the application
  clear( );
  printw( "Exited!\n" );
  refresh( );

  endwin( );

  return EXIT_SUCCESS;
}
