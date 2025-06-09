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

#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstring>
#include <mutex>
#include <optional>
#include <thread>

#include <cstdio>
#include <cstdlib>

// The implementation of the guards
bool Lane::IsCheckAndGo( ) const
{
  bool const result = instanceData.UncontrolMode == UncontrolModeType::E_CHECK;
  return result;
}  // End of guard function: IsCheckAndGo

// The implementation of the Persistency Functions
void Lane::store_Shallow_Availability( [[maybe_unused]] Availability_States state, [[maybe_unused]] Lane_DataType const& instance ) const
{
  static char const* const regfile = "crossroad-lane";
  char const* folder               = getenv( "TMPDIR" );
  char path[ 256 ];
  if( folder == 0 )
  {
    folder = "/tmp";
  }

  strcpy( path, folder );
  strcat( path, "/" );
  strcat( path, regfile );
  strcat( path, instance.Id.c_str( ) );
  strcat( path, ".bin" );

  FILE* fd = fopen( path, "wb" );
  if( fd != NULL )
  {
    uint16_t sdata = (uint16_t)state;
    fwrite( &sdata, sizeof( sdata ), 1, fd );
    fclose( fd );
  }
}  // End of action function: store_Shallow_Availability

Lane::Availability_States Lane::load_Shallow_Availability( [[maybe_unused]] Lane_DataType const& instance ) const
{
  static constexpr Availability_States availStates[] = {
    Availability_States::E_init,
    Availability_States::E_Available,
    Availability_States::E_Unavailable,
    Availability_States::E_final
  };

  static constexpr std::size_t maxStates = sizeof( availStates ) / sizeof( availStates[ 0 ] );

  static char const* const regfile = "crossroad-lane";
  char const* folder               = getenv( "TMPDIR" );
  char path[ 256 ];
  Availability_States result = Availability_States::E_init;

  if( folder == 0 )
  {
    folder = "/tmp";
  }

  strcpy( path, folder );
  strcat( path, "/" );
  strcat( path, regfile );
  strcat( path, instance.Id.c_str( ) );
  strcat( path, ".bin" );

  FILE* fd = fopen( path, "rb" );
  if( fd != NULL )
  {
    uint16_t sdata;
    fread( &sdata, sizeof( sdata ), 1, fd );
    fclose( fd );

    if( sdata < maxStates )
    {
      result = availStates[ sdata ];
    }
  }

  return result;
}  // End of loader function: load_Shallow_Availability

// End of Lane_Auxilary.cpp
