/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-06-15 GMT
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

#include "Door.hh"
#include <Engine.hh>

#include <cassert>
#include <cstddef>
#include <cstring>
#include <csignal>
#include <cstdlib>
#include <mutex>
#include <optional>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>

namespace
{
  constexpr std::chrono::seconds KEEP_DOOR_OPEN( 5U );
  constexpr std::string_view regfile      = "cpp-door";
  constexpr std::string_view tmpDirEnvVar = "TMPDIR";
}  // namespace

// The implementation of the actions
void Door::engineRunACCW( [[maybe_unused]] Door_DataType const& input )
{
  instanceData.doorActionTimeStart = std::chrono::system_clock::now( );
  instanceData.pEngine->trigger_runACCW();
}  // End of action function: engineRunACCW

void Door::engineRunCCW( [[maybe_unused]] Door_DataType const& input )
{
  instanceData.doorActionTimeStart = std::chrono::system_clock::now( );
  instanceData.pEngine->trigger_runCCW();
}  // End of action function: engineRunCCW

void Door::engineStop( [[maybe_unused]] Door_DataType const& input )
{
  instanceData.pEngine->trigger_stop();
}  // End of action function: engineStop

void Door::resetWaitingTime( [[maybe_unused]] Door_DataType const& input )
{
  instanceData.waitUntil = std::chrono::system_clock::now( ) + KEEP_DOOR_OPEN;
}  // End of action function: resetWaitingTime

void Door::wait( [[maybe_unused]] Door_DataType const& input )
{
  std::this_thread::sleep_until( input.waitUntil );
}  // End of action function: wait

// The implementation of the Persistency Functions
void Door::store_Deep_Main( [[maybe_unused]] Main_States state, [[maybe_unused]] Door_DataType const& instance ) const
try
{
  std::ostringstream path;
  char* folder = getenv( tmpDirEnvVar.data( ) );

  path << ( folder ? folder : "/tmp" ) << '/' << regfile << instance.id << ".bin";

  std::ofstream stream( path.str( ), std::ios::out | std::ios::binary );

  if( stream.is_open( ) )
  {
    uint16_t sdata = (uint16_t)state;
    stream << sdata;
  }

  stream.close( );
}
catch( ... )
{
}  // End of action function: store_Deep_Main

Door::Main_States Door::load_Deep_Main( [[maybe_unused]] Door_DataType const& instance ) const
try
{
  Main_States result = Main_States::E_init;

  static std::vector< Main_States > const doorStates {
      Main_States::E_init,
      Main_States::E_Main,
      Main_States::E_AutomaticMode,
      Main_States::E_AutomaticMode_Open,
      Main_States::E_AutomaticMode_Closing,
      Main_States::E_AutomaticMode_Close,
      Main_States::E_AutomaticMode_Opening,
      Main_States::E_ManualMode,
      Main_States::E_ManualMode_Open,
      Main_States::E_ManualMode_Closing,
      Main_States::E_ManualMode_Close,
      Main_States::E_ManualMode_Opening,
      Main_States::E_final
  };

  std::ostringstream path;

  char* folder = getenv( tmpDirEnvVar.data( ) );

  path << ( folder ? folder : "/tmp" ) << '/' << regfile << instance.id << ".bin";

  std::ifstream stream;

  stream.open( path.str( ), std::ios::in | std::ios::binary );

  if( stream.is_open( ) )
  {
    uint16_t sdata;
    stream >> sdata;
    stream.close( );

    if( sdata < doorStates.size( ) )
    {
      result = doorStates[ sdata ];
    }
  }

  return result;
}
catch( ... )
{
  Main_States result = Main_States::E_init;
  return result;
}  // End of loader function: load_Deep_Main

// End of Door_Auxilary.cpp
