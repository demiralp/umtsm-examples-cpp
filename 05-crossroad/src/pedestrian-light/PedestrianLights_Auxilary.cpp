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

#include "PedestrianLights.hh"

#include <Crossroad.hh>
#include <ExecutionDirector.hh>
#include <Lane.hh>
#include <Monitor.hh>

#include <cassert>
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
  constexpr unsigned int RUN_FLASHING_US = 500000U;
}

// The implementation of the guards
bool PedestrianLights::IsCheckAndGo( ) const
{
  bool const result = instanceData.pExecutionDirector->isIn_Uncontrolled_State( );
  return result;
}  // End of guard function: IsCheckAndGo

bool PedestrianLights::IsLaneClose( ) const
{
  Lane* pPedestrianLanes = instanceData.pCrossroad->getSubSM_PedestrianLanes( );

  bool const result = pPedestrianLanes->isIn_Close_State( )
    && pPedestrianLanes->isIn_Controlled_State( )
    && pPedestrianLanes->isIn_Available_State( );

  return result;
}  // End of guard function: IsLaneClose

bool PedestrianLights::IsLaneOpen( ) const
{
  Lane* pPedestrianLanes = instanceData.pCrossroad->getSubSM_PedestrianLanes( );

  bool const result = pPedestrianLanes->isIn_Open_State( )
    && pPedestrianLanes->isIn_Controlled_State( )
    && pPedestrianLanes->isIn_Available_State( );

  return result;
}  // End of guard function: IsLaneOpen

bool PedestrianLights::IsStopCheckAndGo( ) const
{
  bool const result = instanceData.pExecutionDirector->isIn_Uncontrolled_State( );
  return result;
}  // End of guard function: IsStopCheckAndGo

bool PedestrianLights::IsSystemOperational( ) const
{
  bool const result = instanceData.pExecutionDirector->isIn_Operational_State( );
  return result;
}  // End of guard function: IsSystemOperational

bool PedestrianLights::IsSystemSwitching( ) const
{
  bool const result = instanceData.pExecutionDirector->isIn_SwitchSystem_State( );
  return result;
}  // End of guard function: IsSystemSwitching

// The implementation of the actions
void PedestrianLights::CountForFlashing( PedestrianLights_DataType const& input )
{
  usleep( RUN_FLASHING_US );
}  // End of action function: CountForFlashing

void PedestrianLights::SwitchGreenLightOff( PedestrianLights_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchGreenLightOff

void PedestrianLights::SwitchGreenLightOn( PedestrianLights_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchGreenLightOn

void PedestrianLights::SwitchRedLightOff( PedestrianLights_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchRedLightOff

void PedestrianLights::SwitchRedLightOn( PedestrianLights_DataType const& input )
{
  instanceData.pMonitor->trigger_Update( );
}  // End of action function: SwitchRedLightOn

// End of PedestrianLights_Auxilary.cpp
