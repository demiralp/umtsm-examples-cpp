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
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

namespace
{
  constexpr std::string_view regfile      = "cpp-door";
  constexpr std::string_view tmpDirEnvVar = "TMPDIR";
}  // namespace

// The implementation of the actions
void Door::engineRunACCW( [[maybe_unused]] Door_DataType const& input )
{
  instanceData.pEngine->trigger_runACCW( );
}  // End of action function: engineRunACCW

void Door::engineRunCCW( [[maybe_unused]] Door_DataType const& input )
{
  instanceData.pEngine->trigger_runCCW( );
}  // End of action function: engineRunCCW

void Door::engineStop( [[maybe_unused]] Door_DataType const& input )
{
  instanceData.pEngine->trigger_stop( );
}  // End of action function: engineStop

// The implementation of the Persistency Functions
void Door::store_Shallow_Main( [[maybe_unused]] Main_States state, [[maybe_unused]] Door_DataType const& instance, [[maybe_unused]] bool finalWrite ) const
try
{
  if( finalWrite )
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
}
catch( ... )
{
}  // End of action function: store_Shallow_Main

Door::Main_States Door::load_Shallow_Main( [[maybe_unused]] Door_DataType const& instance ) const
try
{
  Main_States result = Main_States::E_init;

  static std::vector< Main_States > const doorStates {
    Main_States::E_init,
    Main_States::E_Main,
    Main_States::E_Open,
    Main_States::E_Closing,
    Main_States::E_Close,
    Main_States::E_Opening,
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
}  // End of loader function: load_Shallow_Main

// End of Door_Auxilary.cpp
