/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-06-12 GMT
 *  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
 *
 *  This file is generated by UMTSM using the code generator `CppGen`
 *
 *  !!! It is highly recommended that DO NOT EDIT THIS GENERATED FILE !!!
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

#include "Display.hh"

#include <cassert>
#include <cstddef>
#include <cstring>

Display::Display( )
{
  initialize( );
}

Display::~Display( )
{
  deinitialize( );
}

void Display::initialize( )
{
  instanceData.initialize( );
  runningState.Main = Main_States::E_init;
}

void Display::deinitialize( )
{
  terminate( );
  runningState.Main = Main_States::E_final;

  instanceData.deinitialize( );
}

void Display::start( )
{
  if ( ! isIn_Main_Region( ) )
  {
    init_Main( );
  }
}

void Display::halt( )
{
  finalize_Main( );
}

bool Display::isReady( ) const noexcept
{
  auto const ready = ( runningState.Main == Main_States::E_init );
  return ready;
}

bool Display::isAlive( ) const noexcept
{
  auto const alive = isIn_Main_Region( );
  return alive;
}

bool Display::isTerminated( ) const noexcept
{
  auto const terminated = ( runningState.Main == Main_States::E_final );
  return terminated;
}

bool Display::is_Main_Region_Ready( ) const noexcept
{
  auto const ready = ( runningState.Main == Main_States::E_init );
  return ready;
}

bool Display::is_Main_Region_Terminated( ) const noexcept
{
  auto const terminated = ( runningState.Main == Main_States::E_final );
  return terminated;
}

bool Display::isIn_Main_Region( ) const noexcept
{
  bool const result = ( runningState.Main != Main_States::E_init ) &&
                      ( runningState.Main != Main_States::E_final );

  return result;
}

bool Display::isIn_Main_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( ( runningState.Main == Main_States::E_Main ) || 
      ( runningState.Main == Main_States::E_DisplayEntry ) || 
      ( runningState.Main == Main_States::E_ErrorMessages ) || 
      ( runningState.Main == Main_States::E_OverflowError ) || 
      ( runningState.Main == Main_States::E_DivisionByZeroError ) || 
      ( runningState.Main == Main_States::E_FaultyError ) );

  return result;
}

bool Display::isIn_DisplayEntry_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_DisplayEntry );

  return result;
}

bool Display::isIn_ErrorMessages_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( ( runningState.Main == Main_States::E_ErrorMessages ) || 
      ( runningState.Main == Main_States::E_OverflowError ) || 
      ( runningState.Main == Main_States::E_DivisionByZeroError ) || 
      ( runningState.Main == Main_States::E_FaultyError ) );

  return result;
}

bool Display::isIn_OverflowError_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_OverflowError );

  return result;
}

bool Display::isIn_DivisionByZeroError_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_DivisionByZeroError );

  return result;
}

bool Display::isIn_FaultyError_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_FaultyError );

  return result;
}

Display_DataType* Display::getData( ) noexcept
{
  Display_DataType* const pCustomData = &instanceData;
  return pCustomData;
}

void Display::trigger_Clear( )
{
  [[maybe_unused]] bool doneMain = false;

  if ( isIn_ErrorMessages_State( ) )
  {
    if ( isIn_OverflowError_State( ) )
    {
      enter_DisplayEntry( );
      runningState.Main = Main_States::E_DisplayEntry;
    }
    else if ( isIn_DivisionByZeroError_State( ) )
    {
      enter_DisplayEntry( );
      runningState.Main = Main_States::E_DisplayEntry;
    }
    else if ( isIn_FaultyError_State( ) )
    {
      enter_DisplayEntry( );
      runningState.Main = Main_States::E_DisplayEntry;
    }
    else
    {
      enter_DisplayEntry( );
      runningState.Main = Main_States::E_DisplayEntry;
    }
  }
}

void Display::trigger_DivisionByZero( )
{
  [[maybe_unused]] bool doneMain = false;

  if ( isIn_DisplayEntry_State( ) )
  {
    enter_DivisionByZeroError( );
    runningState.Main = Main_States::E_DivisionByZeroError;
  }
}

void Display::trigger_Faulty( )
{
  [[maybe_unused]] bool doneMain = false;

  if ( isIn_DisplayEntry_State( ) )
  {
    enter_FaultyError( );
    runningState.Main = Main_States::E_FaultyError;
  }
}

void Display::trigger_Overflow( )
{
  [[maybe_unused]] bool doneMain = false;

  if ( isIn_DisplayEntry_State( ) )
  {
    enter_OverflowError( );
    runningState.Main = Main_States::E_OverflowError;
  }
}

void Display::trigger_Reset( )
{
  [[maybe_unused]] bool doneMain = false;

  if ( isIn_ErrorMessages_State( ) )
  {
    if ( isIn_OverflowError_State( ) )
    {
      enter_DisplayEntry( );
      runningState.Main = Main_States::E_DisplayEntry;
    }
    else if ( isIn_DivisionByZeroError_State( ) )
    {
      enter_DisplayEntry( );
      runningState.Main = Main_States::E_DisplayEntry;
    }
    else if ( isIn_FaultyError_State( ) )
    {
      enter_DisplayEntry( );
      runningState.Main = Main_States::E_DisplayEntry;
    }
    else
    {
      enter_DisplayEntry( );
      runningState.Main = Main_States::E_DisplayEntry;
    }
  }
}

void Display::trigger_SwitchOff( )
{
  [[maybe_unused]] bool doneMain = false;

  if ( isIn_Main_State( ) )
  {
    if ( isIn_DisplayEntry_State( ) )
    {
      terminate( );
    }
    else if ( isIn_ErrorMessages_State( ) )
    {
      if ( isIn_OverflowError_State( ) )
      {
        terminate( );
      }
      else if ( isIn_DivisionByZeroError_State( ) )
      {
        terminate( );
      }
      else if ( isIn_FaultyError_State( ) )
      {
        terminate( );
      }
      else
      {
        terminate( );
      }
    }
    else
    {
      terminate( );
    }
  }
}

void Display::trigger_Update( )
{
  [[maybe_unused]] bool doneMain = false;

  if ( isIn_DisplayEntry_State( ) )
  {
    DisplayUpdate( instanceData );
  }
}

void Display::finalize_Main( )
{
  if ( isIn_Main_Region( ) )
  {
    runningState.Main = Main_States::E_final;
  }
}

void Display::terminate( )
{
  finalize_Main( );
}

void Display::init_Main( )
{
  enter_DisplayEntry( );
  runningState.Main = Main_States::E_DisplayEntry;
}

void Display::enter_DisplayEntry( )
{
  runningState.Main = Main_States::E_DisplayEntry;

  DisplayUpdate( instanceData );
}

void Display::enter_OverflowError( )
{
  runningState.Main = Main_States::E_OverflowError;

  DisplayOverflowError( instanceData );
}

void Display::enter_DivisionByZeroError( )
{
  runningState.Main = Main_States::E_DivisionByZeroError;

  DisplayDivisionByZeroError( instanceData );
}

void Display::enter_FaultyError( )
{
  runningState.Main = Main_States::E_FaultyError;

  DisplayFaultyError( instanceData );
}

// End of Display.cpp
