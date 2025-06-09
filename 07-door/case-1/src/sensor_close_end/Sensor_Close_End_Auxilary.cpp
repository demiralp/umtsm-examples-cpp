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

#include "Sensor_Close_End.hh"

#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <optional>
#include <thread>
#include <unistd.h>

#include <Door.hh>

#define SIMULATION_DOOR_CLOSE_DURATION ( 3U )

// The implementation of the actions
void Sensor_Close_End::checkDoorClosed( [[maybe_unused]] Sensor_Close_End_DataType const& input )
{
  time_t end;
  time( &end );
  end += SIMULATION_DOOR_CLOSE_DURATION;

  do
  {
    time_t now;
    time( &now );
    if( now >= end )
    {
      break;
    }

    usleep( 20000 );
  } while( true );
}  // End of action function: checkDoorClosed

void Sensor_Close_End::notifyDoorClosed( [[maybe_unused]] Sensor_Close_End_DataType const& input )
{
    instanceData.pDoor->trigger_DoorClosed();
}  // End of action function: notifyDoorClosed

void Sensor_Close_End::waitUntilDoorStartClosing( [[maybe_unused]] Sensor_Close_End_DataType const& input )
{
  do
  {
    bool const closing = instanceData.pDoor->isIn_Closing_State();
    if( closing )
    {
      break;
    }
    usleep( 20000U );
  } while( true );
}  // End of action function: waitUntilDoorStartClosing

// End of Sensor_Close_End_Auxilary.cpp
