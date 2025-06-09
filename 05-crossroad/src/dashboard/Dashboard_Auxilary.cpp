/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-07 GMT
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

#include "Crossroad.hh"
#include "Dashboard.hh"

#include "ExecutionDirector.hh"
#include "Lane.hh"
#include "Monitor.hh"

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

// The implementation of the guards
bool Dashboard::IsKey_1( ) const
{
  bool const result = instanceData.LastInputKey == '1';
  return result;
}  // End of guard function: IsKey_1

bool Dashboard::IsKey_2( ) const
{
  bool const result = instanceData.LastInputKey == '2';
  return result;
}  // End of guard function: IsKey_2

bool Dashboard::IsKey_3( ) const
{
  bool const result = instanceData.LastInputKey == '3';
  return result;
}  // End of guard function: IsKey_3

bool Dashboard::IsKey_4( ) const
{
  bool const result = instanceData.LastInputKey == '4';
  return result;
}  // End of guard function: IsKey_4

bool Dashboard::IsKey_C( ) const
{
  bool const result = toupper( instanceData.LastInputKey ) == 'C';
  return result;
}  // End of guard function: IsKey_C

bool Dashboard::IsKey_D( ) const
{
  bool const result = toupper( instanceData.LastInputKey ) == 'D';
  return result;
}  // End of guard function: IsKey_D

bool Dashboard::IsKey_E( ) const
{
  bool const result = toupper( instanceData.LastInputKey ) == 'E';
  return result;
}  // End of guard function: IsKey_E

bool Dashboard::IsKey_P( ) const
{
  bool const result = toupper( instanceData.LastInputKey ) == 'P';
  return result;
}  // End of guard function: IsKey_P

bool Dashboard::IsKey_Q( ) const
{
  bool const result = toupper( instanceData.LastInputKey ) == 'Q';
  return result;
}  // End of guard function: IsKey_Q

bool Dashboard::IsKey_R( ) const
{
  bool const result = toupper( instanceData.LastInputKey ) == 'R';
  return result;
}  // End of guard function: IsKey_R

bool Dashboard::IsKey_S( ) const
{
  bool const result = toupper( instanceData.LastInputKey ) == 'S';
  return result;
}  // End of guard function: IsKey_S

bool Dashboard::IsKey_Space( ) const
{
  bool const result = instanceData.LastInputKey == ' ';
  return result;
}  // End of guard function: IsKey_Space

bool Dashboard::IsKey_U( ) const
{
  bool const result = toupper( instanceData.LastInputKey ) == 'U';
  return result;
}  // End of guard function: IsKey_U

// The implementation of the actions
void Dashboard::DisableLane1( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_DisableLane1( );
}  // End of action function: DisableLane1

void Dashboard::DisableLane2( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_DisableLane2( );
}  // End of action function: DisableLane2

void Dashboard::DisableLane3( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_DisableLane3( );
}  // End of action function: DisableLane3

void Dashboard::DisableLane4( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_DisableLane4( );
}  // End of action function: DisableLane4

void Dashboard::EnableLane1( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_EnableLane1( );
}  // End of action function: EnableLane1

void Dashboard::EnableLane2( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_EnableLane2( );
}  // End of action function: EnableLane2

void Dashboard::EnableLane3( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_EnableLane3( );
}  // End of action function: EnableLane3

void Dashboard::EnableLane4( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_EnableLane4( );
}  // End of action function: EnableLane4

void Dashboard::OpenLane1( [[maybe_unused]] Dashboard_DataType const& input )
{
  if( instanceData.pCrossroad->getSubSM_Lane1( )->isIn_Available_State( ) )
  {
    instanceData.pExecutionDirector->trigger_OpenLane1( );
  }
}  // End of action function: OpenLane1

void Dashboard::OpenLane2( [[maybe_unused]] Dashboard_DataType const& input )
{
  if( instanceData.pCrossroad->getSubSM_Lane2( )->isIn_Available_State( ) )
  {
    instanceData.pExecutionDirector->trigger_OpenLane2( );
  }
}  // End of action function: OpenLane2

void Dashboard::OpenLane3( [[maybe_unused]] Dashboard_DataType const& input )
{
  if( instanceData.pCrossroad->getSubSM_Lane3( )->isIn_Available_State( ) )
  {
    instanceData.pExecutionDirector->trigger_OpenLane3( );
  }
}  // End of action function: OpenLane3

void Dashboard::OpenLane4( [[maybe_unused]] Dashboard_DataType const& input )
{
  if( instanceData.pCrossroad->getSubSM_Lane4( )->isIn_Available_State( ) )
  {
    instanceData.pExecutionDirector->trigger_OpenLane4( );
  }
}  // End of action function: OpenLane4

void Dashboard::OpenPedestrianLanes( [[maybe_unused]] Dashboard_DataType const& input )
{
  if( instanceData.pCrossroad->getSubSM_PedestrianLanes( )->isIn_Available_State( ) )
  {
    instanceData.pExecutionDirector->trigger_OpenPedestrianLanes( );
  }
}  // End of action function: OpenPedestrianLanes

void Dashboard::Quit( [[maybe_unused]] Dashboard_DataType const& input )
{
  raise( SIGINT );
}  // End of action function: Quit

void Dashboard::ReadCommand( [[maybe_unused]] Dashboard_DataType const& input )
{
  static char const* const keyChar = "CcDdEeSsPpQqRrUu1234 ";
  bool okay                        = false;
  int ch;

  do
  {
    ch   = wgetch( stdscr );
    okay = strchr( keyChar, ch ) != NULL;
  } while( ! okay );

  instanceData.LastInputKey = ch;
}  // End of action function: ReadCommand

void Dashboard::ReadLaneNumber( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.LastInputKey = wgetch( stdscr );
}  // End of action function: ReadLaneNumber

void Dashboard::RunTheSystem( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_SystemEnabled( );
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: RunTheSystem

void Dashboard::StandbyTheSystem( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_SystemDisabled( );
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: StandbyTheSystem

void Dashboard::SwitchToControlledProgram( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_TakeControl( );
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchToControlledProgram

void Dashboard::SwitchToUncontrolledProgram( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pExecutionDirector->trigger_ReleaseControl( );
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchToUncontrolledProgram

void Dashboard::UpdateScreen( [[maybe_unused]] Dashboard_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: UpdateScreen

// End of Dashboard_Auxilary.cpp
