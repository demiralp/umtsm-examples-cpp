/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-04-11 GMT
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

#include "Timewatch.hh"

#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstring>
#include <mutex>
#include <optional>
#include <thread>

#include <csignal>
#include <ctime>
#include <ncurses.h>

// The implementation of the actions
void Timewatch::Exit( [[maybe_unused]] Timewatch_DataType const& input )
{
  std::raise( SIGINT );
}  // End of action function: Exit

void Timewatch::InitPauseTime( [[maybe_unused]] Timewatch_DataType const& input )
{
  std::time( &instanceData.Run.Pause.start_pause_time );
}  // End of action function: InitPauseTime

void Timewatch::InitWatchProperties( [[maybe_unused]] Timewatch_DataType const& input )
{
  std::time( &instanceData.Run.start_time );
  instanceData.Run.suspended_duration= 0.0;
}  // End of action function: InitWatchProperties

void Timewatch::PrintElapsedTime( [[maybe_unused]] Timewatch_DataType const& input )
{
  std::time_t now;
  std::time( &now );
  double totalTime= totalTime = std::difftime(now, input.Run.start_time) - input.Run.suspended_duration;
  if ( isIn_Pause_State())
  {
    totalTime -= std::difftime(now, input.Run.Pause.start_pause_time);
  }

  printw( "%1.0fs\n", totalTime);
  refresh( );
}  // End of action function: PrintElapsedTime

void Timewatch::PrintHelp( [[maybe_unused]] Timewatch_DataType const& input )
{
  printw( "H - Print help menu\n");
  refresh( );
  printw( "S - Start timer\n");
  refresh( );
  printw( "Z - Stop timer\n");
  refresh( );
  printw( "P - Pause timer\n");
  refresh( );
  printw( "R - Resume timer\n");
  refresh( );
  printw( "X - Restart timer\n");
  refresh( );
  printw( "Q - Exit\n");
  refresh( );
  printw( "SPACE - Print counter\n");
  refresh( );
}  // End of action function: PrintHelp

void Timewatch::PrintStatusIdle( [[maybe_unused]] Timewatch_DataType const& input )
{
  printw( "<IDLE>\n");
  refresh( );
}  // End of action function: PrintStatusIdle

void Timewatch::PrintStatusPause( [[maybe_unused]] Timewatch_DataType const& input )
{
  printw( "<PAUSE>\n");
  refresh( );
}  // End of action function: PrintStatusPause

void Timewatch::PrintStatusReset( [[maybe_unused]] Timewatch_DataType const& input )
{
  printw( "<RESTART>\n");
  refresh( );
}  // End of action function: PrintStatusReset

void Timewatch::PrintStatusResume( [[maybe_unused]] Timewatch_DataType const& input )
{
  printw( "<RESUME>\n");
}  // End of action function: PrintStatusResume

void Timewatch::PrintStatusRun( [[maybe_unused]] Timewatch_DataType const& input )
{
  printw( "<RUN>\n");
  refresh( );
}  // End of action function: PrintStatusRun

void Timewatch::ReportTotalTime( [[maybe_unused]] Timewatch_DataType const& input )
{
  time_t now;
  time( &now );
  double totalTime = difftime(now, input.Run.start_time) - input.Run.suspended_duration;

  printw( "total time : %1.0fs\n", totalTime);
  refresh( );
}  // End of action function: ReportTotalTime

void Timewatch::UpdateSuspendentDuration( [[maybe_unused]] Timewatch_DataType const& input )
{
  time_t now;
  time( &now );
  instanceData.Run.suspended_duration+= difftime( now, input.Run.Pause.start_pause_time );
  instanceData.Run.Pause.start_pause_time= now;
}  // End of action function: UpdateSuspendentDuration

// End of Timewatch_Auxilary.cpp
