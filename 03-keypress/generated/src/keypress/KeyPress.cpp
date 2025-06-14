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

#include "KeyPress.hh"

#include <cassert>
#include <cstddef>
#include <cstring>

KeyPress::KeyPress( )
{
  initialize( );
}

KeyPress::~KeyPress( )
{
  deinitialize( );
}

void KeyPress::initialize( )
{
  instanceData.initialize( );
  runningState.Main = Main_States::E_init;
}

void KeyPress::deinitialize( )
{
  terminate( );
  runningState.Main = Main_States::E_final;

  instanceData.deinitialize( );
}

void KeyPress::start( )
{
  if ( ! isIn_Main_Region( ) )
  {
    enter_Main( );
    init_Main( );
  }
}

void KeyPress::halt( )
{
  finalize_Main( );
}

bool KeyPress::isReady( ) const noexcept
{
  auto const ready = ( runningState.Main == Main_States::E_init );
  return ready;
}

bool KeyPress::isAlive( ) const noexcept
{
  auto const alive = isIn_Main_Region( );
  return alive;
}

bool KeyPress::isTerminated( ) const noexcept
{
  auto const terminated = ( runningState.Main == Main_States::E_final );
  return terminated;
}

bool KeyPress::is_Main_Region_Ready( ) const noexcept
{
  auto const ready = ( runningState.Main == Main_States::E_init );
  return ready;
}

bool KeyPress::is_Alpha_Region_Ready( ) const noexcept
{
  auto const ready = ( runningState.Alpha == Alpha_States::E_init );
  return ready;
}

bool KeyPress::is_Numeric_Region_Ready( ) const noexcept
{
  auto const ready = ( runningState.Numeric == Numeric_States::E_init );
  return ready;
}

bool KeyPress::is_Log_Region_Ready( ) const noexcept
{
  auto const ready = ( runningState.Log == Log_States::E_init );
  return ready;
}

bool KeyPress::is_Main_Region_Terminated( ) const noexcept
{
  auto const terminated = ( runningState.Main == Main_States::E_final );
  return terminated;
}

bool KeyPress::is_Alpha_Region_Terminated( ) const noexcept
{
  auto const terminated = ( runningState.Alpha == Alpha_States::E_final );
  return terminated;
}

bool KeyPress::is_Numeric_Region_Terminated( ) const noexcept
{
  auto const terminated = ( runningState.Numeric == Numeric_States::E_final );
  return terminated;
}

bool KeyPress::is_Log_Region_Terminated( ) const noexcept
{
  auto const terminated = ( runningState.Log == Log_States::E_final );
  return terminated;
}

bool KeyPress::isIn_Main_Region( ) const noexcept
{
  bool const result = ( runningState.Main != Main_States::E_init ) &&
                      ( runningState.Main != Main_States::E_final );

  return result;
}

bool KeyPress::isIn_Alpha_Region( ) const noexcept
{
  bool const result = ( runningState.Alpha != Alpha_States::E_init ) &&
                      ( runningState.Alpha != Alpha_States::E_final ) &&
                      isIn_Main_State( );

  return result;
}

bool KeyPress::isIn_Numeric_Region( ) const noexcept
{
  bool const result = ( runningState.Numeric != Numeric_States::E_init ) &&
                      ( runningState.Numeric != Numeric_States::E_final ) &&
                      isIn_Main_State( );

  return result;
}

bool KeyPress::isIn_Log_Region( ) const noexcept
{
  bool const result = ( runningState.Log != Log_States::E_init ) &&
                      ( runningState.Log != Log_States::E_final ) &&
                      isIn_Main_State( );

  return result;
}

bool KeyPress::isIn_Main_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( ( runningState.Main == Main_States::E_Main ) || 
      ( runningState.Main == Main_States::E_WaitABit ) );

  return result;
}

bool KeyPress::isIn_ReadLetters_State( ) const noexcept
{
  bool const result = isIn_Alpha_Region( ) &&
    ( runningState.Alpha == Alpha_States::E_ReadLetters );

  return result;
}

bool KeyPress::isIn_Pause_State( ) const noexcept
{
  bool const result = isIn_Alpha_Region( ) &&
    ( runningState.Alpha == Alpha_States::E_Pause );

  return result;
}

bool KeyPress::isIn_ReadDigits_State( ) const noexcept
{
  bool const result = isIn_Numeric_Region( ) &&
    ( runningState.Numeric == Numeric_States::E_ReadDigits );

  return result;
}

bool KeyPress::isIn_PrintLog_State( ) const noexcept
{
  bool const result = isIn_Log_Region( ) &&
    ( runningState.Log == Log_States::E_PrintLog );

  return result;
}

bool KeyPress::isIn_WaitABit_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_WaitABit );

  return result;
}

KeyPress_DataType* KeyPress::getData( ) noexcept
{
  KeyPress_DataType* const pCustomData = &instanceData;
  return pCustomData;
}

void KeyPress::trigger_clock4log( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneLog = false;

  if ( isIn_Log_Region( ) )
  {
    doneLog = true;

    if ( isIn_PrintLog_State( ) )
    {
      LogCounters( instanceData );
    }
    else
    {
      doneLog = false;
    }
  }
}

void KeyPress::trigger_key1( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      CountOdd( instanceData );
      Count1( instanceData );
    }
    else
    {
      doneNumeric = false;
    }
  }
}

void KeyPress::trigger_key2( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      CountEven( instanceData );
      Count2( instanceData );
    }
    else
    {
      doneNumeric = false;
    }
  }
}

void KeyPress::trigger_key3( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      CountOdd( instanceData );
      Count3( instanceData );
    }
    else
    {
      doneNumeric = false;
    }
  }
}

void KeyPress::trigger_key4( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      CountEven( instanceData );
      Count4( instanceData );
    }
    else
    {
      doneNumeric = false;
    }
  }
}

void KeyPress::trigger_key5( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      CountOdd( instanceData );
      Count5( instanceData );
    }
    else
    {
      doneNumeric = false;
    }
  }
}

void KeyPress::trigger_key6( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      CountEven( instanceData );
      Count6( instanceData );
    }
    else
    {
      doneNumeric = false;
    }
  }
}

void KeyPress::trigger_key7( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      CountOdd( instanceData );
      Count7( instanceData );
    }
    else
    {
      doneNumeric = false;
    }
  }
}

void KeyPress::trigger_key8( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      CountEven( instanceData );
      Count8( instanceData );
    }
    else
    {
      doneNumeric = false;
    }
  }
}

void KeyPress::trigger_key9( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      CountOdd( instanceData );
      Count9( instanceData );
    }
    else
    {
      doneNumeric = false;
    }
  }
}

void KeyPress::trigger_keyA( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneAlpha = false;

  if ( isIn_Alpha_Region( ) )
  {
    doneAlpha = true;

    if ( isIn_ReadLetters_State( ) )
    {
      CountA( instanceData );
    }
    else
    {
      doneAlpha = false;
    }
  }
}

void KeyPress::trigger_keyB( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneAlpha = false;

  if ( isIn_Alpha_Region( ) )
  {
    doneAlpha = true;

    if ( isIn_ReadLetters_State( ) )
    {
      CountB( instanceData );
    }
    else
    {
      doneAlpha = false;
    }
  }
}

void KeyPress::trigger_keyBackspace( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      ResetNumericCounters( instanceData );
    }
    else
    {
      doneNumeric = false;
    }
  }
}

void KeyPress::trigger_keyC( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneAlpha = false;

  if ( isIn_Alpha_Region( ) )
  {
    doneAlpha = true;

    if ( isIn_ReadLetters_State( ) )
    {
      CountC( instanceData );
    }
    else
    {
      doneAlpha = false;
    }
  }
}

void KeyPress::trigger_keyDelete( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      ResetNumericCounters( instanceData );
    }
    else
    {
      doneNumeric = false;
    }
  }
}

void KeyPress::trigger_keyF1( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneAlpha = false;
  [[maybe_unused]] bool doneLog = false;

  if ( isIn_Alpha_Region( ) )
  {
    doneAlpha = true;

    if ( isIn_ReadLetters_State( ) )
    {
      finalize_Alpha( );
      checkAndRun_JoinSyncronize( );
    }
    else if ( isIn_Pause_State( ) )
    {
      finalize_Alpha( );
      checkAndRun_JoinSyncronize( );
    }
    else
    {
      doneAlpha = false;
    }
  }

  if ( isIn_Log_Region( ) )
  {
    doneLog = true;

    if ( isIn_PrintLog_State( ) )
    {
      if ( IsCountingFinished( ) )
      {
        finalize_Log( );
        checkAndRun_JoinSyncronize( );
      }
    }
    else
    {
      doneLog = false;
    }
  }
}

void KeyPress::trigger_keyF12( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneAlpha = false;

  if ( isIn_Alpha_Region( ) )
  {
    doneAlpha = true;

    if ( isIn_ReadLetters_State( ) )
    {
      runningState.Alpha = Alpha_States::E_Pause;
    }
    else if ( isIn_Pause_State( ) )
    {
      runningState.Alpha = Alpha_States::E_ReadLetters;
    }
    else
    {
      doneAlpha = false;
    }
  }
}

void KeyPress::trigger_keyF2( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneNumeric = false;
  [[maybe_unused]] bool doneLog = false;

  if ( isIn_Numeric_Region( ) )
  {
    doneNumeric = true;

    if ( isIn_ReadDigits_State( ) )
    {
      finalize_Numeric( );
      checkAndRun_JoinSyncronize( );
    }
    else
    {
      doneNumeric = false;
    }
  }

  if ( isIn_Log_Region( ) )
  {
    doneLog = true;

    if ( isIn_PrintLog_State( ) )
    {
      if ( IsCountingFinished( ) )
      {
        finalize_Log( );
        checkAndRun_JoinSyncronize( );
      }
    }
    else
    {
      doneLog = false;
    }
  }
}

void KeyPress::trigger_space( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneAlpha = false;

  if ( isIn_WaitABit_State( ) )
  {
    MessageGoodBye( instanceData );

    terminate( );
  }

  if ( isIn_Alpha_Region( ) )
  {
    doneAlpha = true;

    if ( isIn_ReadLetters_State( ) )
    {
      ResetLetterCounters( instanceData );
    }
    else
    {
      doneAlpha = false;
    }
  }
}

void KeyPress::finalize_Main( )
{
  if ( isIn_Main_Region( ) )
  {
    runningState.Main = Main_States::E_final;
  }
}

void KeyPress::finalize_Alpha( )
{
  if ( isIn_Alpha_Region( ) )
  {
    runningState.Alpha = Alpha_States::E_final;
  }
}

void KeyPress::finalize_Numeric( )
{
  if ( isIn_Numeric_Region( ) )
  {
    runningState.Numeric = Numeric_States::E_final;
  }
}

void KeyPress::finalize_Log( )
{
  if ( isIn_Log_Region( ) )
  {
    runningState.Log = Log_States::E_final;
  }
}

void KeyPress::terminate( )
{
  finalize_Main( );
}

void KeyPress::init_Main( )
{
  // fork destination -> `:Alpha:ReadLetters`
  runningState.Main = Main_States::E_Main;
  init_Log( );
  runningState.Alpha = Alpha_States::E_ReadLetters;

  // fork destination -> `:Numeric:ReadDigits`
  runningState.Main = Main_States::E_Main;
  runningState.Numeric = Numeric_States::E_ReadDigits;
}

void KeyPress::init_Log( )
{
  enter_PrintLog( );
  runningState.Log = Log_States::E_PrintLog;
}

void KeyPress::enter_Main( )
{
  runningState.Main = Main_States::E_Main;

  MessageHello( instanceData );
}

void KeyPress::enter_WaitABit( )
{
  runningState.Main = Main_States::E_WaitABit;

  LogCounters( instanceData );

  MessagePressSpaceToExit( instanceData );
}

void KeyPress::enter_PrintLog( )
{
  runningState.Log = Log_States::E_PrintLog;

  LogHeaders( instanceData );

  LogCounters( instanceData );
}

void KeyPress::checkAndRun_JoinSyncronize( )
{
  bool const alive = isIn_Alpha_Region( )
    || isIn_Numeric_Region( )
    || isIn_Log_Region( );

  if ( ! alive )
  {
    if ( isIn_Main_State( ) )
    {
      enter_WaitABit( );
      runningState.Main = Main_States::E_WaitABit;
    }
  }
}

// End of KeyPress.cpp
