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

#include "TrafficLight.hh"

#include "Crossroad.hh"
#include "ExecutionDirector.hh"
#include "Lane.hh"
#include "Monitor.hh"

#include <unistd.h>

namespace
{
  constexpr unsigned int RUN_FLASHING_US = 500000U;
}

// The implementation of the guards
bool TrafficLight::IsCheckAndGo( ) const
{
  bool const result = instanceData.pLane->isIn_CheckAndGo_State( )
    && instanceData.pLane->isIn_Uncontrolled_State( )
    && instanceData.pLane->isIn_Available_State( );
  return result;
}  // End of guard function: IsCheckAndGo

bool TrafficLight::IsLaneAvailable( ) const
{
  bool const result = instanceData.pLane->isIn_Available_State( );
  return result;
}  // End of guard function: IsLaneAvailable

bool TrafficLight::IsLaneClose( ) const
{
  bool const result = instanceData.pLane->isIn_Close_State( )
    && instanceData.pLane->isIn_Controlled_State( )
    && instanceData.pLane->isIn_Available_State( );
  return result;
}  // End of guard function: IsLaneClose

bool TrafficLight::IsLaneOnClosing( ) const
{
  bool const result = instanceData.pLane->isIn_PrepareToStop_State( )
    && instanceData.pLane->isIn_Controlled_State( )
    && instanceData.pLane->isIn_Available_State( );
  return result;
}  // End of guard function: IsLaneOnClosing

bool TrafficLight::IsLaneOnOpening( ) const
{
  bool const result = instanceData.pLane->isIn_Ready_State( )
    && instanceData.pLane->isIn_Controlled_State( )
    && instanceData.pLane->isIn_Available_State( );
  return result;
}  // End of guard function: IsLaneOnOpening

bool TrafficLight::IsLaneOpen( ) const
{
  bool const result = instanceData.pLane->isIn_Open_State( )
    && instanceData.pLane->isIn_Controlled_State( )
    && instanceData.pLane->isIn_Available_State( );
  return result;
}  // End of guard function: IsLaneOpen

bool TrafficLight::IsStopCheckAndGo( ) const
{
  bool const result = instanceData.pLane->isIn_StopAndCheck_State( )
    && instanceData.pLane->isIn_Uncontrolled_State( )
    && instanceData.pLane->isIn_Available_State( );
  return result;
}  // End of guard function: IsStopCheckAndGo

bool TrafficLight::IsSystemOperational( ) const
{
  bool const result = instanceData.pExecutionDirector->isIn_Operational_State( );
  return result;
}  // End of guard function: IsSystemOperational

bool TrafficLight::IsSystemSwitching( ) const
{
  bool const result = instanceData.pExecutionDirector->isIn_SwitchSystem_State( );
  return result;
}  // End of guard function: IsSystemSwitching

// The implementation of the actions
void TrafficLight::CountForFlashing( [[maybe_unused]] TrafficLight_DataType const& input )
{
  usleep( RUN_FLASHING_US );
}  // End of action function: CountForFlashing

void TrafficLight::SwitchAmberLightOff( [[maybe_unused]] TrafficLight_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchAmberLightOff

void TrafficLight::SwitchAmberLightOn( [[maybe_unused]] TrafficLight_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchAmberLightOn

void TrafficLight::SwitchGreenLightOff( [[maybe_unused]] TrafficLight_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchGreenLightOff

void TrafficLight::SwitchGreenLightOn( [[maybe_unused]] TrafficLight_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchGreenLightOn

void TrafficLight::SwitchRedLightOff( [[maybe_unused]] TrafficLight_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchRedLightOff

void TrafficLight::SwitchRedLightOn( [[maybe_unused]] TrafficLight_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchRedLightOn

// End of TrafficLight_Auxilary.cpp
