/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-09 GMT
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

#include <Crossroad.hh>
#include <Dashboard.hh>
#include <ExecutionDirector.hh>
#include <Monitor.hh>

#include <atomic>
#include <csignal>
#include <cstdlib>
#include <iostream>

#include <ncurses.h>
#include <unistd.h>

std::atomic_flag blocker = ATOMIC_FLAG_INIT;

Crossroad crossroad;
ExecutionDirector executor;
Dashboard dashboard;
Monitor monitor;

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

  init_pair( 3, 0, COLOR_RED );
  init_pair( 4, 0, COLOR_YELLOW );
  init_pair( 5, 0, COLOR_GREEN );
  init_pair( 6, 0, 0 );

  init_pair( 7, COLOR_YELLOW, 0 );
  init_pair( 8, COLOR_GREEN, 0 );

  noecho( );
  cbreak( );
  set_escdelay( 0 );
  clear( );
  refresh( );

  // Configure Monitor
  auto pMonitorData                = monitor.getData( );
  pMonitorData->pCrossroad         = &crossroad;
  pMonitorData->pExecutionDirector = &executor;

  // Configure Dashboard
  auto pDashboardData                = dashboard.getData( );
  pDashboardData->pMonitor           = &monitor;
  pDashboardData->pExecutionDirector = &executor;
  pDashboardData->pCrossroad         = &crossroad;

  // Configure ExecutionDirector
  auto pExecutor        = executor.getData( );
  pExecutor->pCrossroad = &crossroad;
  pExecutor->pMonitor   = &monitor;

  // Configure Crossroad
  // Configure Crossroad.Lane1
  auto pLane1              = crossroad.getSMData_Lane1( );
  pLane1->Id               = "1";
  pLane1->UncontrolledMode = UncontrolledModeType::E_STOP_AND_CHECK;

  // Configure Crossroad.Lane2
  auto pLane2              = crossroad.getSMData_Lane2( );
  pLane2->Id               = "2";
  pLane2->UncontrolledMode = UncontrolledModeType::E_STOP_AND_CHECK;

  // Configure Crossroad.Lane3
  auto pLane3              = crossroad.getSMData_Lane3( );
  pLane3->Id               = "3";
  pLane3->UncontrolledMode = UncontrolledModeType::E_CHECK;

  // Configure Crossroad.Lane4
  auto pLane4              = crossroad.getSMData_Lane4( );
  pLane4->Id               = "4";
  pLane4->UncontrolledMode = UncontrolledModeType::E_CHECK;

  // Configure Crossroad.PedestrianLanes
  auto pPedestrianLanes = crossroad.getSMData_PedestrianLanes( );
  pPedestrianLanes->Id  = "P";

  // Configure Crossroad.TrafficLight1
  auto pTrafficLight1                = crossroad.getSMData_TrafficLight1( );
  pTrafficLight1->pLane              = crossroad.getSubSM_Lane1( );
  pTrafficLight1->pMonitor           = &monitor;
  pTrafficLight1->pExecutionDirector = &executor;

  // Configure Crossroad.TrafficLight2
  auto pTrafficLight2                = crossroad.getSMData_TrafficLight2( );
  pTrafficLight2->pLane              = crossroad.getSubSM_Lane2( );
  pTrafficLight2->pMonitor           = &monitor;
  pTrafficLight2->pExecutionDirector = &executor;

  // Configure Crossroad.TrafficLight3
  auto pTrafficLight3                = crossroad.getSMData_TrafficLight3( );
  pTrafficLight3->pLane              = crossroad.getSubSM_Lane3( );
  pTrafficLight3->pMonitor           = &monitor;
  pTrafficLight3->pExecutionDirector = &executor;

  // Configure Crossroad.TrafficLight4
  auto pTrafficLight4                = crossroad.getSMData_TrafficLight4( );
  pTrafficLight4->pLane              = crossroad.getSubSM_Lane4( );
  pTrafficLight4->pMonitor           = &monitor;
  pTrafficLight4->pExecutionDirector = &executor;

  // Configure Crossroad.PedestrianLights
  auto pPedestrianLights                = crossroad.getSMData_PedestrianLight( );
  pPedestrianLights->pExecutionDirector = &executor;
  pPedestrianLights->pMonitor           = &monitor;
  pPedestrianLights->pCrossroad         = &crossroad;

  // Start entire the State Machines
  monitor.start( );
  dashboard.start( );
  crossroad.start( );
  executor.start( );

  // Allow entire the state machines run for  indefinite time until CTRL-C is pressed
  signal( SIGINT, signal_handler );

  while( blocker.test_and_set( ) )
  {
    // blank
  }

  executor.halt( );
  crossroad.halt( );
  dashboard.halt( );
  monitor.halt( );

  // exit the application
  clear( );
  printw( "Exited!\n" );
  refresh( );

  endwin( );

  return EXIT_SUCCESS;
}
