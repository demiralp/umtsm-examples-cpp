/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-08 GMT
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

#include "Monitor.hh"
#include "Monitor_DataType.hh"

#include "Crossroad.hh"
#include "ExecutionDirector.hh"
#include "Lane.hh"
#include "PedestrianLights.hh"
#include "TrafficLight.hh"

#include "ExecutionDirector.hh"

#include <ncurses.h>
#include <unistd.h>

namespace
{
  /* internal functions */
  char const* LaneNumberToName( int number )
  {
    static char const* const name[] = {
      "Pedestrian Lanes",
      "Lane1",
      "Lane2",
      "Lane3",
      "Lane4",
      "N/A"
    };

    return name[ ( number < 0 || number > 4 ) ? 5 : number ];
  }

  void PrintHelpLine( char const* const key, char const* const summary )
  {
    attron( COLOR_PAIR( 7 ) );
    printw( "%-6s :", key );
    attroff( COLOR_PAIR( 7 ) );

    attron( COLOR_PAIR( 8 ) );
    printw( " %s\n", summary );
    attroff( COLOR_PAIR( 8 ) );
  }

  static void PrintHelp( Monitor* const smInfo,
                         Monitor_DataType const* const pInstanceData )
  {
    Lane* pLane[ 4 ];

    auto crossroad = pInstanceData->pCrossroad;
    auto executor  = pInstanceData->pExecutionDirector;

    pLane[ 0 ] = crossroad->getSubSM_Lane1( );
    pLane[ 1 ] = crossroad->getSubSM_Lane2( );
    pLane[ 2 ] = crossroad->getSubSM_Lane3( );
    pLane[ 3 ] = crossroad->getSubSM_Lane4( );

    printw( "\n" );
    printw( "Keys for controlling the lanes\n" );

    if( executor->isIn_StandBy_State( ) )
    {
      PrintHelpLine( "R", "Start running the system" );
      PrintHelpLine( "C", "Start running the system in CONTROLLED mode" );
      PrintHelpLine( "U", "Start running the system in UNCONTROLLED mode" );
    }
    else
    {
      if( executor->isIn_Controlled_State( ) )
      {
        PrintHelpLine( "U", "Switching to UNCONTROLLED mode" );
      }
      else if( executor->isIn_Uncontrolled_State( ) )
      {
        PrintHelpLine( "C", "Switching to CONTROLLED mode" );
      }
      else
      {
        PrintHelpLine( "C", "Switching to CONTROLLED mode" );
        PrintHelpLine( "U", "Switching to UNCONTROLLED mode" );
      }
      PrintHelpLine( "S", "Switching to STANDBY mode" );
    }

    for( int lane = 0; lane < 4; ++lane )
    {
      char key[ 8 ];
      char summary[ 128 ];

      bool const available = pLane[ lane ]->isIn_Available_State( );

      if( available )
      {
        sprintf( key, "D-%d", lane + 1 );
        sprintf( summary, "Disable lane %d", lane + 1 );
      }
      else
      {
        sprintf( key, "E-%d", lane + 1 );
        sprintf( summary, "Enable lane %d", lane + 1 );
      }
      PrintHelpLine( key, summary );
    }

    if( executor->isIn_Controlled_State( ) )
    {
      for( int lane = 0; lane < 4; ++lane )
      {
        char key[ 8 ];
        char summary[ 128 ];

        bool const available = pLane[ lane ]->isIn_Available_State( );

        if( available )
        {
          sprintf( key, "%d", lane + 1 );
          sprintf( summary, "Open the lane %d", lane + 1 );
          PrintHelpLine( key, summary );
        }
      }
    }

    PrintHelpLine( "P", "Open the pedestrian lanes" );
    PrintHelpLine( "Q", "Quit" );
    PrintHelpLine( "Ctrl+C", "Terminate immediately" );
    PrintHelpLine( "SPACE", "Update this screen" );
  }
}  // namespace

// The implementation of the actions
void Monitor::ClearMessage( [[maybe_unused]] Monitor_DataType const& input )
{
  instanceData.Message[ 0 ] = '\0';
}  // End of action function: ClearMessage

void Monitor::DisplayStatusOfLanes( [[maybe_unused]] Monitor_DataType const& input )
{
  Lane* pLane[ 4 ];
  auto crossroad = instanceData.pCrossroad;
  auto executor  = instanceData.pExecutionDirector;

  pLane[ 0 ] = crossroad->getSubSM_Lane1( );
  pLane[ 1 ] = crossroad->getSubSM_Lane2( );
  pLane[ 2 ] = crossroad->getSubSM_Lane3( );
  pLane[ 3 ] = crossroad->getSubSM_Lane4( );

  ExecutionDirector_DataType* pExecutorData = executor->getData( );

  TrafficLight* pTrafficLight[ 4 ];
  pTrafficLight[ 0 ] = crossroad->getSubSM_TrafficLight1( );
  pTrafficLight[ 1 ] = crossroad->getSubSM_TrafficLight2( );
  pTrafficLight[ 2 ] = crossroad->getSubSM_TrafficLight3( );
  pTrafficLight[ 3 ] = crossroad->getSubSM_TrafficLight4( );

  PedestrianLights* pPedestrianLights = crossroad->getSubSM_PedestrianLight( );

  while( true )
  {
    while( ! instanceData.UpdateStatus )
    {
      usleep( 10000 );
    }

    clear( );

    attron( COLOR_PAIR( 1 ) );
    printw( "System State     : " );
    attroff( COLOR_PAIR( 1 ) );

    attron( COLOR_PAIR( 2 ) );
    if( executor->isIn_OnCloseLane1_State( ) )
    {
      printw( "LANE1 IS ON CLOSING" );
    }
    else if( executor->isIn_OnCloseLane2_State( ) )
    {
      printw( "LANE2 IS ON CLOSING" );
    }
    else if( executor->isIn_OnCloseLane3_State( ) )
    {
      printw( "LANE3 IS ON CLOSING" );
    }
    else if( executor->isIn_OnCloseLane4_State( ) )
    {
      printw( "LANE4 IS ON CLOSING" );
    }
    else if( executor->isIn_ClosePedestrianLanes_State( ) )
    {
      printw( "PEDESTRIAN LANES ARE ON CLOSING" );
    }
    else if( executor->isIn_OpenLane1_State( ) )
    {
      printw( "LANE1" );
    }
    else if( executor->isIn_OpenLane2_State( ) )
    {
      printw( "LANE2" );
    }
    else if( executor->isIn_OpenLane3_State( ) )
    {
      printw( "LANE3" );
    }
    else if( executor->isIn_OpenLane4_State( ) )
    {
      printw( "LANE4" );
    }
    else if( executor->isIn_OpenPedestrianLanes_State( ) )
    {
      printw( "PEDESTRIAN LANES" );
    }
    else if( executor->isIn_Uncontrolled_State( ) )
    {
      printw( "UNCONTROLLED" );
    }
    else if( executor->isIn_SwitchControlState_State( ) )
    {
      if( executor->IsControlledModeRequested( ) )
      {
        printw( "SWITCHING TO CONTROLLED MODE" );
      }
      else if( executor->IsUncontrolledModeRequested( ) )
      {
        printw( "SWITCHING TO UNCONTROLLED MODE" );
      }
      else
      {
        printw( "RESTORING CONTROL MODE BACK" );
      }
    }
    else if( executor->isIn_GoesToOperational_State( ) )
    {
      if( executor->IsControlledModeRequested( ) )
      {
        printw( "GOES TO CONTROLLED MODE" );
      }
      else if( executor->IsUncontrolledModeRequested( ) )
      {
        printw( "GOES TO UNCONTROLLED MODE" );
      }
      else
      {
        printw( "GOES TO OPERATIONAL" );
      }
    }
    else if( executor->isIn_GoesToStandby_State( ) )
    {
      printw( "GOES TO STANDBY" );
    }
    else if( executor->isIn_StandBy_State( ) )
    {
      printw( "STANDBY" );
    }
    else
    {
      printw( "SAFETY GAP" );
    }
    attroff( COLOR_PAIR( 2 ) );

    printw( "\n" );

    for( int lane = 0; lane < 4; ++lane )
    {
      bool const available = pLane[ lane ]->isIn_Available_State( );
      bool const red       = pTrafficLight[ lane ]->isIn_Red_On_State( )
        || pTrafficLight[ lane ]->isIn_Red_On_Flashing_State( );
      bool const amber = pTrafficLight[ lane ]->isIn_Amber_On_State( )
        || pTrafficLight[ lane ]->isIn_Amber_On_Flashing_State( );
      bool const green = pTrafficLight[ lane ]->isIn_Green_On_State( )
        || pTrafficLight[ lane ]->isIn_Green_On_Flashing_State( );

      int const redColor   = red ? 3 : 6;
      int const amberColor = amber ? 4 : 6;
      int const greenColor = green ? 5 : 6;

      attron( COLOR_PAIR( 1 ) );
      printw( "LANE%d            : ", lane + 1 );
      attroff( COLOR_PAIR( 1 ) );

      attron( COLOR_PAIR( 2 ) );
      printw( "%s ", ( available ? "   " : "N/A" ) );
      attroff( COLOR_PAIR( 2 ) );

      attron( COLOR_PAIR( redColor ) );
      printw( " " );
      attroff( COLOR_PAIR( redColor ) );

      attron( COLOR_PAIR( amberColor ) );
      printw( " " );
      attroff( COLOR_PAIR( amberColor ) );

      attron( COLOR_PAIR( greenColor ) );
      printw( " " );
      attroff( COLOR_PAIR( greenColor ) );

      printw( "\n" );
    }

    // Pedestrian lane
    bool const red = pPedestrianLights->isIn_Red_On_State( )
      || pPedestrianLights->isIn_Red_On_Flashing_State( );
    bool const green = pPedestrianLights->isIn_Green_On_State( )
      || pPedestrianLights->isIn_Green_On_Flashing_State( );

    int const redColor   = red ? 3 : 6;
    int const greenColor = green ? 5 : 6;

    attron( COLOR_PAIR( 1 ) );
    printw( "PEDESTRIAN LANES :     " );
    attroff( COLOR_PAIR( 1 ) );

    attron( COLOR_PAIR( redColor ) );
    printw( " " );
    attroff( COLOR_PAIR( redColor ) );

    printw( " " );

    attron( COLOR_PAIR( greenColor ) );
    printw( " " );
    attroff( COLOR_PAIR( greenColor ) );

    printw( "\n" );

    attron( COLOR_PAIR( 1 ) );
    printw( "PLAN             : " );
    attroff( COLOR_PAIR( 1 ) );

    attron( COLOR_PAIR( 2 ) );
    printw( "Requested -> %s\n", LaneNumberToName( pExecutorData->LaneRequested ) );
    attroff( COLOR_PAIR( 2 ) );

    attron( COLOR_PAIR( 1 ) );
    printw( "MESSAGE          : " );
    attroff( COLOR_PAIR( 1 ) );

    attron( COLOR_PAIR( 2 ) );
    printw( "%s\n", input.Message );
    attroff( COLOR_PAIR( 2 ) );

    PrintHelp( this, &input );

    refresh( );
    instanceData.UpdateStatus = false;
  }
}  // End of action function: DisplayStatusOfLanes

void Monitor::RequestUpdate( [[maybe_unused]] Monitor_DataType const& input )
{
  instanceData.UpdateStatus = true;
}  // End of action function: RequestUpdate

// End of Monitor_Auxilary.cpp
