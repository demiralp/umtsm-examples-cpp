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

#include "ExecutionDirector.hh"
#include "ExecutionDirector_DataType.hh"

#include "Crossroad.hh"
#include "Monitor.hh"

#include <cassert>
#include <cmath>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <optional>
#include <thread>
#include <unistd.h>

namespace
{
  constexpr unsigned int MS_IN_US                  = 1000000U;
  constexpr unsigned int RUN_LANE_MS               = 10U * MS_IN_US;
  constexpr unsigned int RUN_LANE1_MS              = RUN_LANE_MS;
  constexpr unsigned int RUN_LANE2_MS              = RUN_LANE_MS;
  constexpr unsigned int RUN_LANE3_MS              = RUN_LANE_MS;
  constexpr unsigned int RUN_LANE4_MS              = RUN_LANE_MS;
  constexpr unsigned int RUN_PEDESTRIANLANES_MS    = 8U * MS_IN_US;
  constexpr unsigned int RUN_PREPARING_MS          = 4U * MS_IN_US;
  constexpr unsigned int RUN_STOPING_TRAFFIC_MS    = RUN_LANE_MS;
  constexpr unsigned int RUN_SWITCHING_TIME_MS     = 7U * MS_IN_US;
  constexpr unsigned int RUN_MIN_SWITCHING_TIME_MS = 5U * MS_IN_US;
  constexpr unsigned int RUN_INTERVAL_TIME_US      = 3U * MS_IN_US;

  // internal functions
  void TellLaneAvailability(
    ExecutionDirector* const smInfo,
    ExecutionDirector_DataType const* const pInputData,
    ExecutionDirector_DataType* const pOutputData )
  {
    auto crossroad = smInfo->instanceData.pCrossroad;

    if( pInputData->LaneCmd1 == Lane_Command::E_CMD_DISABLE_LANE )
    {
      crossroad->subSMTrigger_Disallowed( Crossroad::SubstateMachines::E_SubSM_Lane1 );
    }
    else if( pInputData->LaneCmd1 == Lane_Command::E_CMD_ENABLE_LANE )
    {
      crossroad->subSMTrigger_Allowed( Crossroad::SubstateMachines::E_SubSM_Lane1 );
    }
    else
    {
      // Nope
    }

    if( pInputData->LaneCmd2 == Lane_Command::E_CMD_DISABLE_LANE )
    {
      crossroad->subSMTrigger_Disallowed( Crossroad::SubstateMachines::E_SubSM_Lane2 );
    }
    else if( pInputData->LaneCmd2 == Lane_Command::E_CMD_ENABLE_LANE )
    {
      crossroad->subSMTrigger_Allowed( Crossroad::SubstateMachines::E_SubSM_Lane2 );
    }
    else
    {
      // Nope
    }

    if( pInputData->LaneCmd3 == Lane_Command::E_CMD_DISABLE_LANE )
    {
      crossroad->subSMTrigger_Disallowed( Crossroad::SubstateMachines::E_SubSM_Lane3 );
    }
    else if( pInputData->LaneCmd3 == Lane_Command::E_CMD_ENABLE_LANE )
    {
      crossroad->subSMTrigger_Allowed( Crossroad::SubstateMachines::E_SubSM_Lane3 );
    }
    else
    {
      // Nope
    }

    if( pInputData->LaneCmd4 == Lane_Command::E_CMD_DISABLE_LANE )
    {
      crossroad->subSMTrigger_Disallowed( Crossroad::SubstateMachines::E_SubSM_Lane4 );
    }
    else if( pInputData->LaneCmd4 == Lane_Command::E_CMD_ENABLE_LANE )
    {
      crossroad->subSMTrigger_Allowed( Crossroad::SubstateMachines::E_SubSM_Lane4 );
    }
    else
    {
      // Nope
    }

    smInfo->instanceData.LaneCmd1 = Lane_Command::E_CMD_NOPE;
    smInfo->instanceData.LaneCmd2 = Lane_Command::E_CMD_NOPE;
    smInfo->instanceData.LaneCmd3 = Lane_Command::E_CMD_NOPE;
    smInfo->instanceData.LaneCmd4 = Lane_Command::E_CMD_NOPE;

    crossroad->trigger_Check( );
  }
}  // namespace

// The implementation of the guards
bool ExecutionDirector::IsControlledModeRequested( ) const
{
  bool const result = instanceData.ControlModeStatus == ControlMode::CONTROLLED;
  return result;
}  // End of guard function: IsControlledModeRequested

bool ExecutionDirector::IsNextLane1( ) const
{
  bool const result = instanceData.NextLane == 1;
  return result;
}  // End of guard function: IsNextLane1

bool ExecutionDirector::IsNextLane2( ) const
{
  bool const result = instanceData.NextLane == 2;
  return result;
}  // End of guard function: IsNextLane2

bool ExecutionDirector::IsNextLane3( ) const
{
  bool const result = instanceData.NextLane == 3;
  return result;
}  // End of guard function: IsNextLane3

bool ExecutionDirector::IsNextLane4( ) const
{
  bool const result = instanceData.NextLane == 4;
  return result;
}  // End of guard function: IsNextLane4

bool ExecutionDirector::IsNextLanePedestrianLanes( ) const
{
  bool const result = instanceData.NextLane == 0;
  return result;
}  // End of guard function: IsNextLanePedestrianLanes

bool ExecutionDirector::IsUncontrolledModeRequested( ) const
{
  bool const result = instanceData.ControlModeStatus == ControlMode::UNCONTROLLED;
  return result;
}  // End of guard function: IsUncontrolledModeRequested

// The implementation of the actions
void ExecutionDirector::CheckRouteRequest( ExecutionDirector_DataType const& input )
{
  instanceData.NextLane      = input.LaneRequested;
  instanceData.LaneRequested = -1;

  TellLaneAvailability( this, &input, &instanceData );
}  // End of action function: CheckRouteRequest

void ExecutionDirector::ClearControlMode( ExecutionDirector_DataType const& input )
{
  instanceData.ControlModeStatus = ControlMode::PERSISTENT_CONTROL_MODE;
}  // End of action function: ClearControlMode

void ExecutionDirector::DisableSystem( ExecutionDirector_DataType const& input )
{
  instanceData.pCrossroad->trigger_SystemDisabled( );
}  // End of action function: DisableSystem

void ExecutionDirector::EnableSystem( ExecutionDirector_DataType const& input )
{
  instanceData.pCrossroad->trigger_SystemEnabled( );
}  // End of action function: EnableSystem

void ExecutionDirector::NotifyCrossroad( ExecutionDirector_DataType const& input )
{
  instanceData.pCrossroad->trigger_Check( );
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: NotifyCrossroad

void ExecutionDirector::OrderOpenLane1( ExecutionDirector_DataType const& input )
{
  auto crossroad = instanceData.pCrossroad;

  if( instanceData.NextLane == 1 )
  {
    instanceData.NextLane = -1;
  }
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane2 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane3 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane4 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_PedestrianLanes );

  if( crossroad->getSubSM_Lane1( )->isIn_Available_State( ) )
  {
    crossroad->subSMTrigger_Open( Crossroad::SubstateMachines::E_SubSM_Lane1 );
  }
  else
  {
    crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane1 );
  }
}  // End of action function: OrderOpenLane1

void ExecutionDirector::OrderOpenLane2( ExecutionDirector_DataType const& input )
{
  auto crossroad = instanceData.pCrossroad;

  if( instanceData.NextLane == 2 )
  {
    instanceData.NextLane = -1;
  }
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane1 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane3 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane4 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_PedestrianLanes );

  if( crossroad->getSubSM_Lane2( )->isIn_Available_State( ) )
  {
    crossroad->subSMTrigger_Open( Crossroad::SubstateMachines::E_SubSM_Lane2 );
  }
  else
  {
    crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane2 );
  }
}  // End of action function: OrderOpenLane2

void ExecutionDirector::OrderOpenLane3( ExecutionDirector_DataType const& input )
{
  auto crossroad = instanceData.pCrossroad;

  if( instanceData.NextLane == 3 )
  {
    instanceData.NextLane = -1;
  }
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane1 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane2 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane4 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_PedestrianLanes );

  if( crossroad->getSubSM_Lane3( )->isIn_Available_State( ) )
  {
    crossroad->subSMTrigger_Open( Crossroad::SubstateMachines::E_SubSM_Lane3 );
  }
  else
  {
    crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane3 );
  }
}  // End of action function: OrderOpenLane3

void ExecutionDirector::OrderOpenLane4( ExecutionDirector_DataType const& input )
{
  auto crossroad = instanceData.pCrossroad;

  if( instanceData.NextLane == 4 )
  {
    instanceData.NextLane = -1;
  }
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane1 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane2 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane3 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_PedestrianLanes );

  if( crossroad->getSubSM_Lane4( )->isIn_Available_State( ) )
  {
    crossroad->subSMTrigger_Open( Crossroad::SubstateMachines::E_SubSM_Lane4 );
  }
  else
  {
    crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane4 );
  }
}  // End of action function: OrderOpenLane4

void ExecutionDirector::OrderOpenPedestrianLanes( ExecutionDirector_DataType const& input )
{
  auto crossroad = instanceData.pCrossroad;

  if( instanceData.NextLane == 0 )
  {
    instanceData.NextLane = -1;
  }
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane1 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane2 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane3 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane4 );
  crossroad->subSMTrigger_Open( Crossroad::SubstateMachines::E_SubSM_PedestrianLanes );
}  // End of action function: OrderOpenPedestrianLanes

void ExecutionDirector::PrepareForNextLane( ExecutionDirector_DataType const& input )
{
  auto crossroad = instanceData.pCrossroad;

  auto pLane1           = crossroad->getSubSM_Lane1( );
  auto pLane2           = crossroad->getSubSM_Lane2( );
  auto pLane3           = crossroad->getSubSM_Lane3( );
  auto pLane4           = crossroad->getSubSM_Lane4( );
  auto pPedestrianLanes = crossroad->getSubSM_PedestrianLanes( );

  instanceData.NextLane      = instanceData.LaneRequested;
  instanceData.LaneRequested = -1;

  TellLaneAvailability( this, &input, &instanceData );

  bool posiablyLane1 = pLane1->isIn_Available_State( ) && ( instanceData.NextLane == -1 || instanceData.NextLane == 1 );
  bool posiablyLane2 = pLane2->isIn_Available_State( ) && ( instanceData.NextLane == -1 || instanceData.NextLane == 2 );
  bool posiablyLane3 = pLane3->isIn_Available_State( ) && ( instanceData.NextLane == -1 || instanceData.NextLane == 3 );
  bool posiablyLane4 = pLane4->isIn_Available_State( ) && ( instanceData.NextLane == -1 || instanceData.NextLane == 4 );
  bool posiablyLaneP = pPedestrianLanes->isIn_Available_State( ) && ( instanceData.NextLane == -1 || instanceData.NextLane == 0 );

  if( pLane1->isIn_Open_State( ) )
  {
    pLane1->trigger_Prepare( );

    if( posiablyLane2 )
    {
      pLane2->trigger_Prepare( );
    }
    else if( posiablyLane3 )
    {
      pLane3->trigger_Prepare( );
    }
    else if( posiablyLane4 )
    {
      pLane4->trigger_Prepare( );
    }
    else
    {
      // not other availabe lanes
    }
  }
  else if( pLane2->isIn_Open_State( ) )
  {
    pLane2->trigger_Prepare( );

    if( posiablyLane3 )
    {
      pLane3->trigger_Prepare( );
    }
    else if( posiablyLane4 )
    {
      pLane4->trigger_Prepare( );
    }
    else if( posiablyLaneP )
    {
      // no Nothing
    }
    else if( posiablyLane1 )
    {
      pLane1->trigger_Prepare( );
    }
    else
    {
      // not other availabe lanes
    }
  }
  else if( pLane3->isIn_Open_State( ) )
  {
    pLane3->trigger_Prepare( );

    if( posiablyLane4 )
    {
      pLane4->trigger_Prepare( );
    }
    else if( posiablyLaneP )
    {
      // no Nothing
    }
    else if( posiablyLane1 )
    {
      pLane1->trigger_Prepare( );
    }
    else if( posiablyLane2 )
    {
      pLane2->trigger_Prepare( );
    }
    else
    {
      // not other availabe lanes
    }
  }
  else if( pLane4->isIn_Open_State( ) )
  {
    pLane4->trigger_Prepare( );

    if( posiablyLane4 )
    {
      pLane4->trigger_Prepare( );
    }
    else if( posiablyLaneP )
    {
      // no Nothing
    }
    else if( posiablyLane1 )
    {
      pLane1->trigger_Prepare( );
    }
    else if( posiablyLane2 )
    {
      pLane2->trigger_Prepare( );
    }
    else if( posiablyLane3 )
    {
      pLane3->trigger_Prepare( );
    }
    else
    {
      // not other availabe lanes
    }
  }
  else if( pPedestrianLanes->isIn_Open_State( ) )
  {
    pPedestrianLanes->trigger_Prepare( );

    if( posiablyLane1 )
    {
      pLane1->trigger_Prepare( );
    }
    else if( posiablyLane2 )
    {
      pLane2->trigger_Prepare( );
    }
    else if( posiablyLane3 )
    {
      pLane3->trigger_Prepare( );
    }
    else if( posiablyLane4 )
    {
      pLane4->trigger_Prepare( );
    }
    else
    {
      // not other availabe lanes
    }
  }
  else if( posiablyLane1 )
  {
    pLane1->trigger_Prepare( );
  }
  else if( posiablyLane2 )
  {
    pLane2->trigger_Prepare( );
  }
  else if( posiablyLane3 )
  {
    pLane3->trigger_Prepare( );
  }
  else if( posiablyLane4 )
  {
    pLane4->trigger_Prepare( );
  }
  else if( posiablyLaneP )
  {
    pPedestrianLanes->trigger_Prepare( );
  }

}  // End of action function: PrepareForNextLane

void ExecutionDirector::SetControlledMode( ExecutionDirector_DataType const& input )
{
  instanceData.ControlModeStatus = ControlMode::CONTROLLED;
}  // End of action function: SetControlledMode

void ExecutionDirector::SetDisableLane1( ExecutionDirector_DataType const& input )
{
  instanceData.LaneCmd1 = Lane_Command::E_CMD_DISABLE_LANE;
  if( ! isIn_Operational_State( ) )
  {
    TellLaneAvailability( this, &input, &instanceData );
    instanceData.pMonitor->trigger_Update( );
    ;
  }
}  // End of action function: SetDisableLane1

void ExecutionDirector::SetDisableLane2( ExecutionDirector_DataType const& input )
{
  instanceData.LaneCmd2 = Lane_Command::E_CMD_DISABLE_LANE;
  if( ! isIn_Operational_State( ) )
  {
    TellLaneAvailability( this, &input, &instanceData );
    instanceData.pMonitor->trigger_Update( );
  }
}  // End of action function: SetDisableLane2

void ExecutionDirector::SetDisableLane3( ExecutionDirector_DataType const& input )
{
  instanceData.LaneCmd3 = Lane_Command::E_CMD_DISABLE_LANE;
  if( ! isIn_Operational_State( ) )
  {
    TellLaneAvailability( this, &input, &instanceData );
    instanceData.pMonitor->trigger_Update( );
  }
}  // End of action function: SetDisableLane3

void ExecutionDirector::SetDisableLane4( ExecutionDirector_DataType const& input )
{
  instanceData.LaneCmd4 = Lane_Command::E_CMD_DISABLE_LANE;
  if( ! isIn_Operational_State( ) )
  {
    TellLaneAvailability( this, &input, &instanceData );
    instanceData.pMonitor->trigger_Update( );
  }
}  // End of action function: SetDisableLane4

void ExecutionDirector::SetEnableLane1( ExecutionDirector_DataType const& input )
{
  instanceData.LaneCmd1 = Lane_Command::E_CMD_ENABLE_LANE;
  if( ! isIn_Operational_State( ) )
  {
    TellLaneAvailability( this, &input, &instanceData );
    instanceData.pMonitor->trigger_Update( );
  }
}  // End of action function: SetEnableLane1

void ExecutionDirector::SetEnableLane2( ExecutionDirector_DataType const& input )
{
  instanceData.LaneCmd2 = Lane_Command::E_CMD_ENABLE_LANE;
  if( ! isIn_Operational_State( ) )
  {
    TellLaneAvailability( this, &input, &instanceData );
    instanceData.pMonitor->trigger_Update( );
  }
}  // End of action function: SetEnableLane2

void ExecutionDirector::SetEnableLane3( ExecutionDirector_DataType const& input )
{
  instanceData.LaneCmd3 = Lane_Command::E_CMD_ENABLE_LANE;
  if( ! isIn_Operational_State( ) )
  {
    TellLaneAvailability( this, &input, &instanceData );
    instanceData.pMonitor->trigger_Update( );
  }
}  // End of action function: SetEnableLane3

void ExecutionDirector::SetEnableLane4( ExecutionDirector_DataType const& input )
{
  instanceData.LaneCmd4 = Lane_Command::E_CMD_ENABLE_LANE;
  if( ! isIn_Operational_State( ) )
  {
    TellLaneAvailability( this, &input, &instanceData );
    instanceData.pMonitor->trigger_Update( );
  }
}  // End of action function: SetEnableLane4

void ExecutionDirector::SetNextOpenLane1( ExecutionDirector_DataType const& input )
{
  instanceData.LaneRequested = 1;
}  // End of action function: SetNextOpenLane1

void ExecutionDirector::SetNextOpenLane2( ExecutionDirector_DataType const& input )
{
  instanceData.LaneRequested = 2;
}  // End of action function: SetNextOpenLane2

void ExecutionDirector::SetNextOpenLane3( ExecutionDirector_DataType const& input )
{
  instanceData.LaneRequested = 3;
}  // End of action function: SetNextOpenLane3

void ExecutionDirector::SetNextOpenLane4( ExecutionDirector_DataType const& input )
{
  instanceData.LaneRequested = 4;
}  // End of action function: SetNextOpenLane4

void ExecutionDirector::SetNextOpenLanePedestrianLanes( ExecutionDirector_DataType const& input )
{
  instanceData.LaneRequested = 0;
}  // End of action function: SetNextOpenLanePedestrianLanes

void ExecutionDirector::SetUncontrolledMode( ExecutionDirector_DataType const& input )
{
  instanceData.ControlModeStatus = ControlMode::UNCONTROLLED;
}  // End of action function: SetUncontrolledMode

void ExecutionDirector::StartControlMode( ExecutionDirector_DataType const& input )
{
  instanceData.LaneClosingCompleted = false;
  instanceData.pCrossroad->trigger_StartControlling( );
}  // End of action function: StartControlMode

void ExecutionDirector::StartSystemSwitchingTimer( ExecutionDirector_DataType const& input )
{
  time( &instanceData.StartSwitchingTime );
}  // End of action function: StartSystemSwitchingTimer

void ExecutionDirector::StartUncontrolMode( ExecutionDirector_DataType const& input )
{
  instanceData.pCrossroad->trigger_StopControlling( );
  instanceData.LaneRequested = -1;
}  // End of action function: StartUncontrolMode

void ExecutionDirector::StopTraffic( ExecutionDirector_DataType const& input )
{
  auto crossroad = instanceData.pCrossroad;

  instanceData.LaneClosingCompleted = false;

  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane1 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane2 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane3 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_Lane4 );
  crossroad->subSMTrigger_Close( Crossroad::SubstateMachines::E_SubSM_PedestrianLanes );
  crossroad->trigger_Check( );

  instanceData.pMonitor->trigger_Update( );
}  // End of action function: StopTraffic

void ExecutionDirector::Update( ExecutionDirector_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: Update

void ExecutionDirector::WaitForInterval( ExecutionDirector_DataType const& input )
{
  usleep( RUN_INTERVAL_TIME_US );
}  // End of action function: WaitForInterval

void ExecutionDirector::WaitForLane1( ExecutionDirector_DataType const& input )
{
  if( instanceData.pCrossroad->getSubSM_Lane1( )->isIn_Available_State( ) )
  {
    instanceData.LaneClosingCompleted = false;
    usleep( RUN_LANE1_MS );
  }
}  // End of action function: WaitForLane1

void ExecutionDirector::WaitForLane2( ExecutionDirector_DataType const& input )
{
  if( instanceData.pCrossroad->getSubSM_Lane2( )->isIn_Available_State( ) )
  {
    instanceData.LaneClosingCompleted = false;
    usleep( RUN_LANE2_MS );
  }
}  // End of action function: WaitForLane2

void ExecutionDirector::WaitForLane3( ExecutionDirector_DataType const& input )
{
  if( instanceData.pCrossroad->getSubSM_Lane3( )->isIn_Available_State( ) )
  {
    instanceData.LaneClosingCompleted = false;
    usleep( RUN_LANE3_MS );
  }
}  // End of action function: WaitForLane3

void ExecutionDirector::WaitForLane4( ExecutionDirector_DataType const& input )
{
  if( instanceData.pCrossroad->getSubSM_Lane4( )->isIn_Available_State( ) )
  {
    instanceData.LaneClosingCompleted = false;
    usleep( RUN_LANE4_MS );
  }
}  // End of action function: WaitForLane4

void ExecutionDirector::WaitForNextLaneOpen( ExecutionDirector_DataType const& input )
{
  if( ! input.LaneClosingCompleted )
  {
    usleep( RUN_PREPARING_MS );
    instanceData.LaneClosingCompleted = true;
  }
}  // End of action function: WaitForNextLaneOpen

void ExecutionDirector::WaitForPedestrians( ExecutionDirector_DataType const& input )
{
  instanceData.LaneClosingCompleted = false;
  usleep( RUN_PEDESTRIANLANES_MS );
}  // End of action function: WaitForPedestrians

void ExecutionDirector::WaitForSystemSwitchingTimer( ExecutionDirector_DataType const& input )
{
  time_t now;
  time( &now );
  double remainingtime = ceil( RUN_SWITCHING_TIME_MS - difftime( now, input.StartSwitchingTime ) );
  if( remainingtime < RUN_MIN_SWITCHING_TIME_MS )
  {
    remainingtime = RUN_MIN_SWITCHING_TIME_MS;
  }

  usleep( remainingtime );
}  // End of action function: WaitForSystemSwitchingTimer

void ExecutionDirector::WaitForTrafficStops( ExecutionDirector_DataType const& input )
{
  usleep( RUN_STOPING_TRAFFIC_MS );
}  // End of action function: WaitForTrafficStops

// The implementation of the Persistency Functions
void ExecutionDirector::store_Shallow_Operational( Main_States state, ExecutionDirector_DataType const& instance ) const
{
  static char const* const regfile = "crossroad-executor.bin";
  char const* folder               = getenv( "TMPDIR" );
  char path[ 256 ];
  if( folder == 0 )
  {
    folder = "/tmp";
  }

  strcpy( path, folder );
  strcat( path, "/" );
  strcat( path, regfile );

  FILE* fd = fopen( path, "wb" );
  if( fd != NULL )
  {
    uint16_t sdata = (uint16_t)state;
    fwrite( &sdata, sizeof( sdata ), 1, fd );
    fclose( fd );
  }
}  // End of action function: store_Shallow_Operational

ExecutionDirector::Main_States ExecutionDirector::load_Shallow_Operational( ExecutionDirector_DataType const& instance ) const
{
  static constexpr Main_States mainStates[] = {
    Main_States::E_init,
    Main_States::E_Main,
    Main_States::E_StandBy,
    Main_States::E_SwitchSystem,
    Main_States::E_GoesToOperational,
    Main_States::E_GoesToStandby,
    Main_States::E_SwitchControlState,
    Main_States::E_Operational,
    Main_States::E_Uncontrolled,
    Main_States::E_CheckRequests,
    Main_States::E_Controlled,
    Main_States::E_OpenLane1,
    Main_States::E_OnCloseLane1,
    Main_States::E_OpenLane2,
    Main_States::E_OnCloseLane2,
    Main_States::E_OpenLane3,
    Main_States::E_OnCloseLane3,
    Main_States::E_OpenLane4,
    Main_States::E_OnCloseLane4,
    Main_States::E_OpenPedestrianLanes,
    Main_States::E_OnClosePedestrianLanes,
    Main_States::E_final
  };

  static constexpr std::size_t maxState = sizeof( mainStates ) / sizeof( mainStates[ 0 ] );

  Main_States result = Main_States::E_init;

  static char const* const regfile = "crossroad-executor.bin";
  char const* folder               = getenv( "TMPDIR" );
  char path[ 256 ];
  if( folder == 0 )
  {
    folder = "/tmp";
  }

  strcpy( path, folder );
  strcat( path, "/" );
  strcat( path, regfile );

  FILE* fd = fopen( path, "rb" );
  if( fd != NULL )
  {
    uint16_t sdata;
    fread( &sdata, sizeof( sdata ), 1, fd );
    if( sdata >= 0 && sdata <= maxState )
    {
      result = mainStates[ sdata ];
    }
    fclose( fd );
  }

  return result;
}  // End of loader function: load_Shallow_Operational

// End of ExecutionDirector_Auxilary.cpp
