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

#define KEEP_DOOR_OPEN ( 5 )

// The implementation of the actions
void Door::engineRunACCW( [[maybe_unused]] Door_DataType const& input )
{
  instanceData.pEngine->trigger_runACCW();
}  // End of action function: engineRunACCW

void Door::engineRunCCW( [[maybe_unused]] Door_DataType const& input )
{
  instanceData.pEngine->trigger_runCCW();
}  // End of action function: engineRunCCW

void Door::engineStop( [[maybe_unused]] Door_DataType const& input )
{
  instanceData.pEngine->trigger_stop();
}  // End of action function: engineStop

// The implementation of the Persistency Functions
void Door::store_Shallow_Main( [[maybe_unused]] Main_States state, [[maybe_unused]] Door_DataType const& instance ) const
{
  static char const* const regfile = "door";
  char const* folder               = getenv( "TMPDIR" );
  char path[ 256 ];
  if( folder == 0 )
  {
    folder = "/tmp";
  }

  strcpy( path, folder );
  strcat( path, "/" );
  strcat( path, regfile );
  strcat( path, "-" );
  strcat( path, instanceData.id.c_str() );
  strcat( path, ".bin" );

  FILE* fd = fopen( path, "wb" );
  if( fd != NULL )
  {
    uint16_t sdata = (uint16_t)state;
    fwrite( &sdata, sizeof( sdata ), 1, fd );
    fclose( fd );
  }
}  // End of action function: store_Shallow_Main

Door::Main_States Door::load_Shallow_Main( [[maybe_unused]] Door_DataType const& instance ) const
{
  Main_States result = Main_States::E_init;

  static char const* const regfile = "door";
  char const* folder               = getenv( "TMPDIR" );
  char path[ 256 ];
  if( folder == 0 )
  {
    folder = "/tmp";
  }

  strcpy( path, folder );
  strcat( path, "/" );
  strcat( path, regfile );
  strcat( path, "-" );
  strcat( path, instanceData.id.c_str() );
  strcat( path, ".bin" );

  FILE* fd = fopen( path, "rb" );
  if( fd != NULL )
  {
    uint16_t sdata;
    fread( &sdata, sizeof( sdata ), 1, fd );
    fclose( fd );

    switch( sdata )
    {
      case 0:
      {
        result= Main_States::E_init;
        break;
      }
      case 1:
      {
        result= Main_States::E_Main;
        break;
      }
      case 2:
      {
        result= Main_States::E_Open;
        break;
      }
      case 3:
      {
        result= Main_States::E_Closing;
        break;
      }
      case 4:
      {
        result= Main_States::E_Close;
        break;
      }
      case 5:
      {
        result= Main_States::E_Opening;
        break;
      }
      case 6:
      {
        result= Main_States::E_final;
        break;
      }
    }
  }

  return result;
}  // End of loader function: load_Shallow_Main

// End of Door_Auxilary.cpp
