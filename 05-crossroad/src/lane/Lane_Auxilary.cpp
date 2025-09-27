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

#include "Lane.hh"

#include <fstream>
#include <sstream>
#include <vector>

namespace
{
  constexpr std::string_view regfile      = "cpp-crossroad-lane";
  constexpr std::string_view tmpDirEnvVar = "TMPDIR";
}  // namespace

// The implementation of the guards
bool Lane::IsCheckAndGo( ) const
{
  bool const result = instanceData.UncontrolledMode == UncontrolledModeType::E_CHECK;
  return result;
}  // End of guard function: IsCheckAndGo

// The implementation of the Persistency Functions
void Lane::store_Shallow_Availability( [[maybe_unused]] Availability_States state, [[maybe_unused]] Lane_DataType const& instance, [[maybe_unused]] bool finalWrite ) const
try
{
  if( finalWrite )
  {
    std::ostringstream path;
    char* folder = getenv( tmpDirEnvVar.data( ) );

    path << ( folder ? folder : "/tmp" ) << '/' << regfile << instance.Id << ".bin";

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
}  // End of action function: store_Shallow_Availability

Lane::Availability_States Lane::load_Shallow_Availability( [[maybe_unused]] Lane_DataType const& instance ) const
try
{
  Availability_States result = Availability_States::E_init;

  static std::vector< Availability_States > const availStates {
    Availability_States::E_init,
    Availability_States::E_Available,
    Availability_States::E_Unavailable,
    Availability_States::E_final
  };

  std::ostringstream path;

  char* folder = getenv( tmpDirEnvVar.data( ) );

  path << ( folder ? folder : "/tmp" ) << '/' << regfile << instance.Id << ".bin";

  std::ifstream stream;

  stream.open( path.str( ), std::ios::in | std::ios::binary );

  if( stream.is_open( ) )
  {
    uint16_t sdata;
    stream >> sdata;
    stream.close( );

    if( sdata < availStates.size( ) )
    {
      result = availStates[ sdata ];
    }
  }

  return result;
}
catch( ... )
{
  Availability_States const result = Availability_States::E_init;
  return result;
}  // End of loader function: load_Shallow_Availability

// End of Lane_Auxilary.cpp
