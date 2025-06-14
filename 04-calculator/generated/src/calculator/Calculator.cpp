/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-06-08 GMT
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

#include "Calculator.hh"

#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <optional>
#include <thread>
#include <unistd.h>

Calculator::Calculator( )
{
  initialize( );
}

Calculator::~Calculator( )
{
  deinitialize( );
}

void Calculator::initialize( )
{
  std::lock_guard<std::mutex> lockGuard( guard );;

  instanceData.initialize( );
  runningState.Main = Main_States::E_init;

  subSM.CalculatorKeypad.initialize( );
  subSM.CalculatorDisplay.initialize( );
}

void Calculator::deinitialize( )
{
  std::lock_guard<std::mutex> lockGuard( guard );;

  terminate( );
  runningState.Main = Main_States::E_final;

  instanceData.deinitialize( );
}

void Calculator::start( )
{
  if ( ! isIn_Main_Region( ) )
  {
    std::lock_guard<std::mutex> lockGuard( guard );

    init_Main( );
  }
}

void Calculator::halt( )
{
  finalize_Main( );
}

bool Calculator::isReady( ) const noexcept
{
  auto const ready = ( runningState.Main == Main_States::E_init );
  return ready;
}

bool Calculator::isAlive( ) const noexcept
{
  auto const alive = isIn_Main_Region( );
  return alive;
}

bool Calculator::isTerminated( ) const noexcept
{
  auto const terminated = ( runningState.Main == Main_States::E_final );
  return terminated;
}

bool Calculator::is_Main_Region_Ready( ) const noexcept
{
  auto const ready = ( runningState.Main == Main_States::E_init );
  return ready;
}

bool Calculator::is_Input_Region_Ready( ) const noexcept
{
  auto const ready = ( runningState.Input == Input_States::E_init );
  return ready;
}

bool Calculator::is_ProcessingUnit_Region_Ready( ) const noexcept
{
  auto const ready = ( runningState.ProcessingUnit == ProcessingUnit_States::E_init );
  return ready;
}

bool Calculator::is_Output_Region_Ready( ) const noexcept
{
  auto const ready = ( runningState.Output == Output_States::E_init );
  return ready;
}

bool Calculator::is_Main_Region_Terminated( ) const noexcept
{
  auto const terminated = ( runningState.Main == Main_States::E_final );
  return terminated;
}

bool Calculator::is_Input_Region_Terminated( ) const noexcept
{
  auto const terminated = ( runningState.Input == Input_States::E_final );
  return terminated;
}

bool Calculator::is_ProcessingUnit_Region_Terminated( ) const noexcept
{
  auto const terminated = ( runningState.ProcessingUnit == ProcessingUnit_States::E_final );
  return terminated;
}

bool Calculator::is_Output_Region_Terminated( ) const noexcept
{
  auto const terminated = ( runningState.Output == Output_States::E_final );
  return terminated;
}

bool Calculator::isIn_Main_Region( ) const noexcept
{
  bool const result = ( runningState.Main != Main_States::E_init ) &&
                      ( runningState.Main != Main_States::E_final );

  return result;
}

bool Calculator::isIn_Input_Region( ) const noexcept
{
  bool const result = ( runningState.Input != Input_States::E_init ) &&
                      ( runningState.Input != Input_States::E_final ) &&
                      isIn_Main_State( );

  return result;
}

bool Calculator::isIn_ProcessingUnit_Region( ) const noexcept
{
  bool const result = ( runningState.ProcessingUnit != ProcessingUnit_States::E_init ) &&
                      ( runningState.ProcessingUnit != ProcessingUnit_States::E_final ) &&
                      isIn_Main_State( );

  return result;
}

bool Calculator::isIn_Output_Region( ) const noexcept
{
  bool const result = ( runningState.Output != Output_States::E_init ) &&
                      ( runningState.Output != Output_States::E_final ) &&
                      isIn_Main_State( );

  return result;
}

bool Calculator::isIn_Main_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_Main );

  return result;
}

bool Calculator::isIn_CalculatorKeypad_State( ) const noexcept
{
  bool const result = isIn_Input_Region( ) &&
    ( runningState.Input == Input_States::E_CalculatorKeypad );

  return result;
}

bool Calculator::isIn_Process_State( ) const noexcept
{
  bool const result = isIn_ProcessingUnit_Region( ) &&
    ( ( runningState.ProcessingUnit == ProcessingUnit_States::E_Process ) || 
      ( runningState.ProcessingUnit == ProcessingUnit_States::E_EnterBaseDigits ) || 
      ( runningState.ProcessingUnit == ProcessingUnit_States::E_EnterFractions ) || 
      ( runningState.ProcessingUnit == ProcessingUnit_States::E_EnterExponents ) );

  return result;
}

bool Calculator::isIn_EnterBaseDigits_State( ) const noexcept
{
  bool const result = isIn_ProcessingUnit_Region( ) &&
    ( runningState.ProcessingUnit == ProcessingUnit_States::E_EnterBaseDigits );

  return result;
}

bool Calculator::isIn_EnterFractions_State( ) const noexcept
{
  bool const result = isIn_ProcessingUnit_Region( ) &&
    ( runningState.ProcessingUnit == ProcessingUnit_States::E_EnterFractions );

  return result;
}

bool Calculator::isIn_EnterExponents_State( ) const noexcept
{
  bool const result = isIn_ProcessingUnit_Region( ) &&
    ( runningState.ProcessingUnit == ProcessingUnit_States::E_EnterExponents );

  return result;
}

bool Calculator::isIn_Error_State( ) const noexcept
{
  bool const result = isIn_ProcessingUnit_Region( ) &&
    ( ( runningState.ProcessingUnit == ProcessingUnit_States::E_Error ) || 
      ( runningState.ProcessingUnit == ProcessingUnit_States::E_Faulty ) || 
      ( runningState.ProcessingUnit == ProcessingUnit_States::E_DivisionByZero ) || 
      ( runningState.ProcessingUnit == ProcessingUnit_States::E_Overflow ) );

  return result;
}

bool Calculator::isIn_Faulty_State( ) const noexcept
{
  bool const result = isIn_ProcessingUnit_Region( ) &&
    ( runningState.ProcessingUnit == ProcessingUnit_States::E_Faulty );

  return result;
}

bool Calculator::isIn_DivisionByZero_State( ) const noexcept
{
  bool const result = isIn_ProcessingUnit_Region( ) &&
    ( runningState.ProcessingUnit == ProcessingUnit_States::E_DivisionByZero );

  return result;
}

bool Calculator::isIn_Overflow_State( ) const noexcept
{
  bool const result = isIn_ProcessingUnit_Region( ) &&
    ( runningState.ProcessingUnit == ProcessingUnit_States::E_Overflow );

  return result;
}

bool Calculator::isIn_CalculatorDisplay_State( ) const noexcept
{
  bool const result = isIn_Output_Region( ) &&
    ( runningState.Output == Output_States::E_CalculatorDisplay );

  return result;
}

Calculator_DataType* Calculator::getData( ) noexcept
{
  Calculator_DataType* const pCustomData = &instanceData;
  return pCustomData;
}

Keypad_DataType* Calculator::getSMData_CalculatorKeypad( ) noexcept
{
  Keypad_DataType* const pCustomData = subSM.CalculatorKeypad.getData( );
  return pCustomData;
}

Display_DataType* Calculator::getSMData_CalculatorDisplay( ) noexcept
{
  Display_DataType* const pCustomData = subSM.CalculatorDisplay.getData( );
  return pCustomData;
}

Keypad* Calculator::getSubSM_CalculatorKeypad( ) noexcept
{
  Keypad* const pSubSM = &subSM.CalculatorKeypad;
  return pSubSM;
}

Display* Calculator::getSubSM_CalculatorDisplay( ) noexcept
{
  Display* const pSubSM = &subSM.CalculatorDisplay;
  return pSubSM;
}

void Calculator::subSMTrigger_Backspace( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Backspace( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Backspace`
      break;
    }
  }
}

void Calculator::subSMTrigger_ChangeSign( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_ChangeSign( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `ChangeSign`
      break;
    }
  }
}

void Calculator::subSMTrigger_Clear( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Clear( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Clear`
      break;
    }
  }
}

void Calculator::subSMTrigger_Digit( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Digit( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Digit`
      break;
    }
  }
}

void Calculator::subSMTrigger_Division( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Division( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Division`
      break;
    }
  }
}

void Calculator::subSMTrigger_DivisionByZero( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_DivisionByZero( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `DivisionByZero`
      break;
    }
  }
}

void Calculator::subSMTrigger_Dot( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Dot( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Dot`
      break;
    }
  }
}

void Calculator::subSMTrigger_Enter( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Enter( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Enter`
      break;
    }
  }
}

void Calculator::subSMTrigger_Exponents( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Exponents( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Exponents`
      break;
    }
  }
}

void Calculator::subSMTrigger_Faulty( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Faulty( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Faulty`
      break;
    }
  }
}

void Calculator::subSMTrigger_Minus( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Minus( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Minus`
      break;
    }
  }
}

void Calculator::subSMTrigger_Multiplay( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Multiplay( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Multiplay`
      break;
    }
  }
}

void Calculator::subSMTrigger_Notify( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Notify( );
      break;
    }
    case SubstateMachines::E_SubSM_CalculatorKeypad:
    {
      subSM.CalculatorKeypad.trigger_Notify( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Notify`
      break;
    }
  }
}

void Calculator::subSMTrigger_Overflow( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Overflow( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Overflow`
      break;
    }
  }
}

void Calculator::subSMTrigger_Plus( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Plus( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Plus`
      break;
    }
  }
}

void Calculator::subSMTrigger_Reset( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Reset( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Reset`
      break;
    }
  }
}

void Calculator::subSMTrigger_SwitchOff( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_SwitchOff( );
      break;
    }
    case SubstateMachines::E_SubSM_CalculatorDisplay:
    {
      subSM.CalculatorDisplay.trigger_SwitchOff( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `SwitchOff`
      break;
    }
  }
}

void Calculator::subSMTrigger_Update( SubstateMachines subsm )
{
  switch ( subsm )
  {
    case SubstateMachines::E_Self:
    {
      trigger_Update( );
      break;
    }
    default:
    {
      // the other state machine(s) do not support trigger `Update`
      break;
    }
  }
}

void Calculator::trigger_Backspace( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_EnterBaseDigits_State( ) )
    {
      EraseBaseDigit( instanceData );
      NotifyDisplayUpdate( instanceData );
    }
    else if ( isIn_EnterFractions_State( ) )
    {
      if ( IsFractionZero( ) )
      {
        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else
      {
        EraseFractionDigit( instanceData );
        NotifyDisplayUpdate( instanceData );
      }
    }
    else if ( isIn_EnterExponents_State( ) )
    {
      if ( IsExponentZero( ) && IsFractionZero( ) )
      {
        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else if ( IsExponentZero( ) )
      {
        enter_EnterFractions( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterFractions;
      }
      else
      {
        EraseExponentDigit( instanceData );
        NotifyDisplayUpdate( instanceData );
      }
    }
    else
    {
      // left blank. the else block at the end is required by MISRA
    }
  }
}

void Calculator::trigger_ChangeSign( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_EnterBaseDigits_State( ) )
    {
      ChangeBaseSign( instanceData );
      NotifyDisplayUpdate( instanceData );
    }
    else if ( isIn_EnterFractions_State( ) )
    {
      ChangeBaseSign( instanceData );
      NotifyDisplayUpdate( instanceData );
    }
    else if ( isIn_EnterExponents_State( ) )
    {
      ChangeExponetSign( instanceData );
      NotifyDisplayUpdate( instanceData );
    }
    else
    {
      // left blank. the else block at the end is required by MISRA
    }
  }
}

void Calculator::trigger_Clear( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_Process_State( ) )
    {
      if ( isIn_EnterBaseDigits_State( ) )
      {
        ClearLastEntry( instanceData );
        NotifyDisplayUpdate( instanceData );
      }
      else if ( isIn_EnterFractions_State( ) )
      {
        ClearLastEntry( instanceData );
        NotifyDisplayUpdate( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else if ( isIn_EnterExponents_State( ) )
      {
        ClearLastEntry( instanceData );
        NotifyDisplayUpdate( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else
      {
        ClearLastEntry( instanceData );
        NotifyDisplayUpdate( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
    }
    else if ( isIn_Error_State( ) )
    {
      if ( isIn_Faulty_State( ) )
      {
        DrawSpliteLine( instanceData );

        exit_Error( );
        enter_Process( );
        init_Process( );
      }
      else if ( isIn_DivisionByZero_State( ) )
      {
        DrawSpliteLine( instanceData );

        exit_Error( );
        enter_Process( );
        init_Process( );
      }
      else if ( isIn_Overflow_State( ) )
      {
        DrawSpliteLine( instanceData );

        exit_Error( );
        enter_Process( );
        init_Process( );
      }
      else
      {
        DrawSpliteLine( instanceData );

        exit_Error( );
        enter_Process( );
        init_Process( );
      }
    }
    else
    {
      doneProcessingUnit = false;
    }
  }
}

void Calculator::trigger_Digit( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_EnterBaseDigits_State( ) )
    {
      PushBaseDigit( instanceData );
      NotifyDisplayUpdate( instanceData );
    }
    else if ( isIn_EnterFractions_State( ) )
    {
      PushFractionDigit( instanceData );
      NotifyDisplayUpdate( instanceData );
    }
    else if ( isIn_EnterExponents_State( ) )
    {
      PushExponentDigit( instanceData );
      NotifyDisplayUpdate( instanceData );
    }
    else
    {
      // left blank. the else block at the end is required by MISRA
    }
  }
}

void Calculator::trigger_Division( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_Process_State( ) )
    {
      if ( isIn_EnterBaseDigits_State( ) )
      {
        Divides( instanceData );
        ClearLastEntry( instanceData );
      }
      else if ( isIn_EnterFractions_State( ) )
      {
        Divides( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else if ( isIn_EnterExponents_State( ) )
      {
        Divides( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else
      {
        Divides( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
    }
    else
    {
      doneProcessingUnit = false;
    }
  }
}

void Calculator::trigger_DivisionByZero( )
{
  [[maybe_unused]] bool doneMain = false;

  std::lock_guard<std::mutex> lockGuard( guard );
}

void Calculator::trigger_Dot( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_EnterBaseDigits_State( ) )
    {
      enter_EnterFractions( );
      runningState.ProcessingUnit = ProcessingUnit_States::E_EnterFractions;
    }
  }
}

void Calculator::trigger_Enter( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_Process_State( ) )
    {
      if ( isIn_EnterBaseDigits_State( ) )
      {
        Calculate( instanceData );
        ClearLastEntry( instanceData );
      }
      else if ( isIn_EnterFractions_State( ) )
      {
        Calculate( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else if ( isIn_EnterExponents_State( ) )
      {
        Calculate( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else
      {
        Calculate( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
    }
    else
    {
      doneProcessingUnit = false;
    }
  }
}

void Calculator::trigger_Exponents( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_EnterBaseDigits_State( ) )
    {
      if ( ! IsBaseZero( ) )
      {
        enter_EnterExponents( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterExponents;
      }
    }
    else if ( isIn_EnterFractions_State( ) )
    {
      if ( ( ! IsBaseZero( ) || ! IsFractionZero( ) ) && IsThereSpaceForExponent( ) )
      {
        RemoveZerosFromFraction( instanceData );

        enter_EnterExponents( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterExponents;
      }
    }
    else
    {
      // left blank. the else block at the end is required by MISRA
    }
  }
}

void Calculator::trigger_Faulty( )
{
  [[maybe_unused]] bool doneMain = false;

  std::lock_guard<std::mutex> lockGuard( guard );
}

void Calculator::trigger_Minus( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_Process_State( ) )
    {
      if ( isIn_EnterBaseDigits_State( ) )
      {
        Substractions( instanceData );
        ClearLastEntry( instanceData );
      }
      else if ( isIn_EnterFractions_State( ) )
      {
        Substractions( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else if ( isIn_EnterExponents_State( ) )
      {
        Substractions( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else
      {
        Substractions( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
    }
    else
    {
      doneProcessingUnit = false;
    }
  }
}

void Calculator::trigger_Multiplay( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_Process_State( ) )
    {
      if ( isIn_EnterBaseDigits_State( ) )
      {
        Multiplications( instanceData );
        ClearLastEntry( instanceData );
      }
      else if ( isIn_EnterFractions_State( ) )
      {
        Multiplications( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else if ( isIn_EnterExponents_State( ) )
      {
        Multiplications( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else
      {
        Multiplications( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
    }
    else
    {
      doneProcessingUnit = false;
    }
  }
}

void Calculator::trigger_Notify( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneInput = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_Input_Region( ) )
  {
    doneInput = true;

    if ( isIn_CalculatorKeypad_State( ) )
    {
      subSM.CalculatorKeypad.trigger_Notify( );
    }
    else
    {
      doneInput = false;
    }
  }
}

void Calculator::trigger_Overflow( )
{
  [[maybe_unused]] bool doneMain = false;

  std::lock_guard<std::mutex> lockGuard( guard );
}

void Calculator::trigger_Plus( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_Process_State( ) )
    {
      if ( isIn_EnterBaseDigits_State( ) )
      {
        Additions( instanceData );
        ClearLastEntry( instanceData );
      }
      else if ( isIn_EnterFractions_State( ) )
      {
        Additions( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else if ( isIn_EnterExponents_State( ) )
      {
        Additions( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else
      {
        Additions( instanceData );
        ClearLastEntry( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
    }
    else
    {
      doneProcessingUnit = false;
    }
  }
}

void Calculator::trigger_Reset( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneProcessingUnit = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_ProcessingUnit_Region( ) )
  {
    doneProcessingUnit = true;

    if ( isIn_Process_State( ) )
    {
      if ( isIn_EnterBaseDigits_State( ) )
      {
        ClearLastEntry( instanceData );
        ResetAccumulations( instanceData );
        DrawSpliteLine( instanceData );
        NotifyDisplayUpdate( instanceData );
      }
      else if ( isIn_EnterFractions_State( ) )
      {
        ClearLastEntry( instanceData );
        ResetAccumulations( instanceData );
        DrawSpliteLine( instanceData );
        NotifyDisplayUpdate( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else if ( isIn_EnterExponents_State( ) )
      {
        ClearLastEntry( instanceData );
        ResetAccumulations( instanceData );
        DrawSpliteLine( instanceData );
        NotifyDisplayUpdate( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
      else
      {
        ClearLastEntry( instanceData );
        ResetAccumulations( instanceData );
        DrawSpliteLine( instanceData );
        NotifyDisplayUpdate( instanceData );

        enter_EnterBaseDigits( );
        runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
      }
    }
    else if ( isIn_Error_State( ) )
    {
      if ( isIn_Faulty_State( ) )
      {
        DrawSpliteLine( instanceData );

        exit_Error( );
        enter_Process( );
        init_Process( );
      }
      else if ( isIn_DivisionByZero_State( ) )
      {
        DrawSpliteLine( instanceData );

        exit_Error( );
        enter_Process( );
        init_Process( );
      }
      else if ( isIn_Overflow_State( ) )
      {
        DrawSpliteLine( instanceData );

        exit_Error( );
        enter_Process( );
        init_Process( );
      }
      else
      {
        DrawSpliteLine( instanceData );

        exit_Error( );
        enter_Process( );
        init_Process( );
      }
    }
    else
    {
      doneProcessingUnit = false;
    }
  }
}

void Calculator::trigger_SwitchOff( )
{
  [[maybe_unused]] bool doneMain = false;
  [[maybe_unused]] bool doneInput = false;
  [[maybe_unused]] bool doneProcessingUnit = false;
  [[maybe_unused]] bool doneOutput = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_Main_State( ) )
  {
    if ( isIn_Input_Region( ) )
    {
      doneInput = true;

      if ( isIn_CalculatorKeypad_State( ) )
      {
        terminate( );
      }
      else
      {
        doneInput = false;
      }
    }

    if ( isIn_ProcessingUnit_Region( ) )
    {
      doneProcessingUnit = true;

      if ( isIn_Process_State( ) )
      {
        if ( isIn_EnterBaseDigits_State( ) )
        {
          terminate( );
        }
        else if ( isIn_EnterFractions_State( ) )
        {
          terminate( );
        }
        else if ( isIn_EnterExponents_State( ) )
        {
          terminate( );
        }
        else
        {
          terminate( );
        }
      }
      else if ( isIn_Error_State( ) )
      {
        if ( isIn_Faulty_State( ) )
        {
          terminate( );
        }
        else if ( isIn_DivisionByZero_State( ) )
        {
          terminate( );
        }
        else if ( isIn_Overflow_State( ) )
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
        doneProcessingUnit = false;
      }
    }

    if ( isIn_Output_Region( ) )
    {
      doneOutput = true;

      if ( isIn_CalculatorDisplay_State( ) )
      {
        subSM.CalculatorDisplay.trigger_SwitchOff( );
        terminate( );
      }
      else
      {
        doneOutput = false;
      }
    }

    doneMain = doneInput || doneProcessingUnit || doneOutput;

    if( ! doneMain )
    {
      doneMain = true;

      terminate( );
    }
  }
}

void Calculator::trigger_Update( )
{
  [[maybe_unused]] bool doneMain = false;

  std::lock_guard<std::mutex> lockGuard( guard );
}

void Calculator::finalize_Main( )
{
  if ( isIn_Main_Region( ) )
  {
    runningState.Main = Main_States::E_final;
  }
}

void Calculator::finalize_Input( )
{
  if ( isIn_Input_Region( ) )
  {
    runningState.Input = Input_States::E_final;
  }
}

void Calculator::finalize_ProcessingUnit( )
{
  if ( isIn_ProcessingUnit_Region( ) )
  {
    if ( isIn_Process_State( ) )
    {
      if ( doActionHandler.has_value( )
        && pthread_equal( doActionHandler.value( ), pthread_self( ) ) )
      {
        pthread_cancel( doActionHandler.value( ) );
        doActionHandler.reset( );
      }
    }
    runningState.ProcessingUnit = ProcessingUnit_States::E_final;
  }
}

void Calculator::finalize_Output( )
{
  if ( isIn_Output_Region( ) )
  {
    runningState.Output = Output_States::E_final;
  }
}

void Calculator::terminate( )
{
  finalize_Main( );
}

void Calculator::init_Main( )
{
  // fork destination -> `:Input:CalculatorKeypad`
  runningState.Main = Main_States::E_Main;
  init_CalculatorKeypad( );
  runningState.Input = Input_States::E_CalculatorKeypad;

  // fork destination -> `:ProcessingUnit:Process`
  runningState.Main = Main_States::E_Main;
  enter_Process( );
  init_Process( );

  // fork destination -> `:Output:CalculatorDisplay`
  runningState.Main = Main_States::E_Main;
  init_CalculatorDisplay( );
  runningState.Output = Output_States::E_CalculatorDisplay;
}

void Calculator::init_CalculatorKeypad( )
{
  subSM.CalculatorKeypad.start( );
}

void Calculator::init_Process( )
{
  ResetAccumulations( instanceData );
  NotifyDisplayUpdate( instanceData );

  enter_EnterBaseDigits( );
  runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;
}

void Calculator::init_CalculatorDisplay( )
{
  subSM.CalculatorDisplay.start( );
}

void* Calculator::doAction_Process( )
{
  CheckErrorStatus( instanceData );

  std::lock_guard<std::mutex> lockGuard( guard );

  doActionHandler.reset( );

  if ( isIn_Process_State( ) )
  {
    if ( HasDivisionByZeroError( ) )
    {
      exit_Process( );
      enter_DivisionByZero( );
      runningState.ProcessingUnit = ProcessingUnit_States::E_DivisionByZero;
    }
    else if ( HasOverflowError( ) )
    {
      exit_Process( );
      enter_Overflow( );
      runningState.ProcessingUnit = ProcessingUnit_States::E_Overflow;
    }
    else if ( IsFaulty( ) )
    {
      exit_Process( );
      enter_Faulty( );
      runningState.ProcessingUnit = ProcessingUnit_States::E_Faulty;
    }
    else
    {
      // left blank. the else block at the end is required by MISRA
    }
  }

  return NULL;
}

void Calculator::enter_Process( )
{
  runningState.ProcessingUnit = ProcessingUnit_States::E_Process;

  ResetAccumulations( instanceData );

  doActionHandler = launchDoAction( callDoAction_Process, this, nullptr, 0 );
}

void Calculator::enter_EnterBaseDigits( )
{
  runningState.ProcessingUnit = ProcessingUnit_States::E_EnterBaseDigits;

  ClearFraction( instanceData );

  ClearExponent( instanceData );

  NotifyDisplayUpdate( instanceData );
}

void Calculator::enter_EnterFractions( )
{
  runningState.ProcessingUnit = ProcessingUnit_States::E_EnterFractions;

  ClearExponent( instanceData );

  SetFractionEntry( instanceData );

  NotifyDisplayUpdate( instanceData );
}

void Calculator::enter_EnterExponents( )
{
  runningState.ProcessingUnit = ProcessingUnit_States::E_EnterExponents;

  SetExponentEntry( instanceData );

  NotifyDisplayUpdate( instanceData );
}

void Calculator::enter_Faulty( )
{
  runningState.ProcessingUnit = ProcessingUnit_States::E_Faulty;

  NotifyFaultError( instanceData );
}

void Calculator::enter_DivisionByZero( )
{
  runningState.ProcessingUnit = ProcessingUnit_States::E_DivisionByZero;

  NotifyDivisionByZeroError( instanceData );
}

void Calculator::enter_Overflow( )
{
  runningState.ProcessingUnit = ProcessingUnit_States::E_Overflow;

  NotifyOverflowError( instanceData );
}

void Calculator::exit_CalculatorKeypad( )
{
  runningState.Input = Input_States::E_CalculatorKeypad;

  subSM.CalculatorKeypad.deinitialize( );
}

void Calculator::exit_Process( )
{
  runningState.ProcessingUnit = ProcessingUnit_States::E_Process;
  if ( doActionHandler.has_value( )
    && pthread_equal( doActionHandler.value( ), pthread_self( ) ) )
  {
    pthread_cancel( doActionHandler.value( ) );
    doActionHandler.reset( );
  }
}

void Calculator::exit_Error( )
{
  runningState.ProcessingUnit = ProcessingUnit_States::E_Error;

  NotifyReset( instanceData );
}

void Calculator::exit_CalculatorDisplay( )
{
  runningState.Output = Output_States::E_CalculatorDisplay;

  subSM.CalculatorDisplay.deinitialize( );
}

void* Calculator::callDoAction_Process( void* arg )
{
  Calculator* obj = reinterpret_cast< Calculator* >( arg );
  obj->doAction_Process( );

  return NULL;
}

pthread_t Calculator::launchDoAction( void *(*threadStart)(void *), Calculator* pStateMachine, void *stackAddr, size_t stackSize )
{
  pthread_t thr = 0;

  if ( threadStart != NULL )
  {
    pthread_attr_t attr;

    int err = pthread_attr_init( &attr );
    if ( err == 0 )
    {
      err = pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );

      if ( err == 0 )
      {
        err = pthread_attr_setinheritsched( &attr, PTHREAD_EXPLICIT_SCHED );
      }

      if ( ( err == 0 ) && ( stackAddr != nullptr ) && ( stackSize > 0 ) )
      {
        err = pthread_attr_setstack( &attr, stackAddr, stackSize );
        err = 0;
      }

      if ( err == 0 )
      {
        err = pthread_create( &thr, &attr, threadStart, pStateMachine);
      }

      if ( err != 0 )
      {
        thr = 0;
      }

      pthread_attr_destroy( &attr );
    }
  }

  return thr;
}

// End of Calculator.cpp
