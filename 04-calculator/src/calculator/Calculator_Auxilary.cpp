/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-29 GMT
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

#include "Calculator.hh"
#include "Calculator_DataType.hh"
#include "Calculator_Utilities.hh"

#include "Display.hh"
#include "Display_DataType.hh"

#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <optional>
#include <thread>
#include <unistd.h>

#include <algorithm>
#include <ncurses.h>

// The implementation of the guards
bool Calculator::HasDivisionByZeroError( ) const
{
  bool result = instanceData.ErrorNo == Calculator_Error::E_DIVISION_BY_ZERO;
  return result;
}  // End of guard function: HasDivisionByZeroError

bool Calculator::HasOverflowError( ) const
{
  bool result = instanceData.ErrorNo == Calculator_Error::E_OVERFLOW;
  return result;
}  // End of guard function: HasOverflowError

bool Calculator::IsBaseZero( ) const
{
  bool result = true;
  char const * pStr= &subSM.CalculatorDisplay.instanceData.BaseDigits[0];
  while( result && *pStr != '\0')
  {
    result = (*pStr == '0');
    pStr++;
  }

  return result;
}  // End of guard function: IsBaseZero

bool Calculator::IsExponentZero( ) const
{
  bool result = true;
  char const * pStr= &subSM.CalculatorDisplay.instanceData.ExponantionalDigits[0];
  while( result && *pStr != '\0')
  {
    result = (*pStr == '0');
    pStr++;
  }

  return result;
}  // End of guard function: IsExponentZero

bool Calculator::IsFaulty( ) const
{
  bool const result = instanceData.ErrorNo == Calculator_Error::E_FAULTY;
  return result;
}  // End of guard function: IsFaulty

bool Calculator::IsFractionZero( ) const
{
  bool result = true;
  char const * pStr= &subSM.CalculatorDisplay.instanceData.FractionalDigits[0];
  while( result && *pStr != '\0')
  {
    result = (*pStr == '0');
    pStr++;
  }

  return result;
}  // End of guard function: IsFractionZero

bool Calculator::IsThereSpaceForExponent( ) const
{
  size_t const baseLen = std::max<int>(1, strlen( subSM.CalculatorDisplay.instanceData.BaseDigits ) ) + 1;
  bool const isFracZero = IsFractionZero( );
  size_t const fractionLen = isFracZero? 0 : ( strlen( subSM.CalculatorDisplay.instanceData.FractionalDigits ) + 1 );

  bool result = (baseLen+fractionLen) < 18;
  return result;
}  // End of guard function: IsThereSpaceForExponent

// The implementation of the actions
void Calculator::Additions( [[maybe_unused]] Calculator_DataType const& input )
{
  Calculator_Internal::CalculateAccumulator( this, &input, &instanceData, Calculator_Operator::E_OP_PLUS );
}  // End of action function: Additions

void Calculator::Calculate( [[maybe_unused]] Calculator_DataType const& input )
{
  Calculator_Internal::CalculateAccumulator( this, &input, &instanceData, Calculator_Operator::E_OP_ENTER );
}  // End of action function: Calculate

void Calculator::ChangeBaseSign( [[maybe_unused]] Calculator_DataType const& input )
{
  subSM.CalculatorDisplay.instanceData.BaseSignaturePositive = ! subSM.CalculatorDisplay.instanceData.BaseSignaturePositive;
}  // End of action function: ChangeBaseSign

void Calculator::ChangeExponetSign( [[maybe_unused]] Calculator_DataType const& input )
{
  subSM.CalculatorDisplay.instanceData.ExponantionalSignaturePositive = (! subSM.CalculatorDisplay.instanceData.ExponantionalSignaturePositive);
}  // End of action function: ChangeExponetSign

void Calculator::CheckErrorStatus( [[maybe_unused]] Calculator_DataType const& input )
{
  while (input.ErrorNo == Calculator_Error::E_NO_ERROR)
  {
    std::this_thread::sleep_for( std::chrono::microseconds( 500000 ) );
  }
}  // End of action function: CheckErrorStatus

void Calculator::ClearExponent( [[maybe_unused]] Calculator_DataType const& input )
{
  subSM.CalculatorDisplay.instanceData.ExponentStart = false;
  subSM.CalculatorDisplay.instanceData.ExponantionalSignaturePositive= true;
  subSM.CalculatorDisplay.instanceData.ExponantionalDigits[0] = '\0';
}  // End of action function: ClearExponent

void Calculator::ClearFraction( [[maybe_unused]] Calculator_DataType const& input )
{
  subSM.CalculatorDisplay.instanceData.FractinalStart= false;
  subSM.CalculatorDisplay.instanceData.FractionalDigits[0] = '\0';
}  // End of action function: ClearFraction

void Calculator::ClearLastEntry( [[maybe_unused]] Calculator_DataType const& input )
{
  subSM.CalculatorDisplay.instanceData.initialize();
}  // End of action function: ClearLastEntry

void Calculator::Divides( [[maybe_unused]] Calculator_DataType const& input )
{
  Calculator_Internal::CalculateAccumulator( this, &input, &instanceData, Calculator_Operator::E_OP_DIVIDE );
}  // End of action function: Divides

void Calculator::DrawSpliteLine( [[maybe_unused]] Calculator_DataType const& input )
{
  Calculator_Internal::DrawSeparator();
}  // End of action function: DrawSpliteLine

void Calculator::EraseBaseDigit( [[maybe_unused]] Calculator_DataType const& input )
{
  size_t len= strlen(subSM.CalculatorDisplay.instanceData.BaseDigits);
  if ( len > 0 )
  {
    len--;
    subSM.CalculatorDisplay.instanceData.BaseDigits[len]= '\0';
  }
}  // End of action function: EraseBaseDigit

void Calculator::EraseExponentDigit( [[maybe_unused]] Calculator_DataType const& input )
{
  size_t len= strlen(subSM.CalculatorDisplay.instanceData.ExponantionalDigits);
  if ( len > 0 )
  {
    len--;
    subSM.CalculatorDisplay.instanceData.ExponantionalDigits[len]= '\0';
  }
  else
  {
    subSM.CalculatorDisplay.instanceData.ExponentStart= false;
  }
}  // End of action function: EraseExponentDigit

void Calculator::EraseFractionDigit( [[maybe_unused]] Calculator_DataType const& input )
{
  size_t len= strlen(subSM.CalculatorDisplay.instanceData.FractionalDigits);
  if ( len > 0 )
  {
    len--;
    subSM.CalculatorDisplay.instanceData.FractionalDigits[len]= '\0';
  }
  else
  {
    subSM.CalculatorDisplay.instanceData.FractinalStart= false;
  }
}  // End of action function: EraseFractionDigit

void Calculator::Multiplications( [[maybe_unused]] Calculator_DataType const& input )
{
  Calculator_Internal::CalculateAccumulator( this, &input, &instanceData, Calculator_Operator::E_OP_MULTIPLY );
}  // End of action function: Multiplications

void Calculator::NotifyDisplayUpdate( [[maybe_unused]] Calculator_DataType const& input )
{
  subSM.CalculatorDisplay.trigger_Update();
}  // End of action function: NotifyDisplayUpdate

void Calculator::NotifyDivisionByZeroError( [[maybe_unused]] Calculator_DataType const& input )
{
  subSM.CalculatorDisplay.trigger_DivisionByZero();
}  // End of action function: NotifyDivisionByZeroError

void Calculator::NotifyFaultError( [[maybe_unused]] Calculator_DataType const& input )
{
  subSM.CalculatorDisplay.trigger_Faulty();
}  // End of action function: NotifyFaultError

void Calculator::NotifyOverflowError( [[maybe_unused]] Calculator_DataType const& input )
{
  subSM.CalculatorDisplay.trigger_Overflow();
}  // End of action function: NotifyOverflowError

void Calculator::NotifyReset( [[maybe_unused]] Calculator_DataType const& input )
{
  subSM.CalculatorDisplay.trigger_Reset();
}  // End of action function: NotifyReset

void Calculator::PushBaseDigit( [[maybe_unused]] Calculator_DataType const& input )
{
  size_t const allowence = std::min<int>( 19, sizeof( subSM.CalculatorDisplay.instanceData.BaseDigits )-2 );

  size_t baseLen= strlen( subSM.CalculatorDisplay.instanceData.BaseDigits );

  if ( baseLen == 1 && subSM.CalculatorDisplay.instanceData.BaseDigits[0] == '0')
  {
    subSM.CalculatorDisplay.instanceData.BaseDigits[0]= (char)subSM.CalculatorKeypad.instanceData.LastInputKey;
  }
  else if ((baseLen < allowence) &&
           (baseLen > 0 || subSM.CalculatorKeypad.instanceData.LastInputKey != '0'))
  {
    subSM.CalculatorDisplay.instanceData.BaseDigits[baseLen]= (char)subSM.CalculatorKeypad.instanceData.LastInputKey;
    subSM.CalculatorDisplay.instanceData.BaseDigits[baseLen+1]= '\0';
  }
  else
  {
    /* do nothing */
  }
}  // End of action function: PushBaseDigit

void Calculator::PushExponentDigit( [[maybe_unused]] Calculator_DataType const& input )
{
  size_t const baseLen = std::max<int>(1, strlen( subSM.CalculatorDisplay.instanceData.BaseDigits ) ) + 1;
  bool const isFracZero = IsFractionZero( );
  size_t const fractionLen = isFracZero? 0 : ( strlen( subSM.CalculatorDisplay.instanceData.FractionalDigits ) + 1 );

  size_t const allowence = std::min<int>( sizeof( subSM.CalculatorDisplay.instanceData.ExponantionalDigits ) - 1, 18 - (baseLen+fractionLen) );

  size_t expLen= strlen( subSM.CalculatorDisplay.instanceData.ExponantionalDigits );

  if ((expLen < allowence) &&
      (expLen > 0 || subSM.CalculatorKeypad.instanceData.LastInputKey != '0'))
  {
    subSM.CalculatorDisplay.instanceData.ExponantionalDigits[expLen]= (char)subSM.CalculatorKeypad.instanceData.LastInputKey;
    subSM.CalculatorDisplay.instanceData.ExponantionalDigits[expLen+1]= '\0';
  }
}  // End of action function: PushExponentDigit

void Calculator::PushFractionDigit( [[maybe_unused]] Calculator_DataType const& input )
{
  size_t const allowence = std::min<int>( 17-strlen(subSM.CalculatorDisplay.instanceData.BaseDigits), sizeof( subSM.CalculatorDisplay.instanceData.FractionalDigits ) - 1 );

  size_t baseLen= strlen( subSM.CalculatorDisplay.instanceData.FractionalDigits);
  if (baseLen < allowence)
  {
    subSM.CalculatorDisplay.instanceData.FractionalDigits[baseLen]= (char)subSM.CalculatorKeypad.instanceData.LastInputKey;
    subSM.CalculatorDisplay.instanceData.FractionalDigits[baseLen+1]= '\0';
  }
}  // End of action function: PushFractionDigit

void Calculator::RemoveZerosFromFraction( [[maybe_unused]] Calculator_DataType const& input )
{
  size_t tLen= strlen(subSM.CalculatorDisplay.instanceData.FractionalDigits);
  while( tLen > 0 )
  {
    --tLen;
    if ( subSM.CalculatorDisplay.instanceData.FractionalDigits[tLen] == '0' )
    {
      subSM.CalculatorDisplay.instanceData.FractionalDigits[tLen] = '\0';
    }
    else
    {
     break;
    }
  }
  if ( subSM.CalculatorDisplay.instanceData.FractionalDigits[0] == '\0')
  {
    subSM.CalculatorDisplay.instanceData.FractinalStart= false;
  }
}  // End of action function: RemoveZerosFromFraction

void Calculator::ResetAccumulations( [[maybe_unused]] Calculator_DataType const& input )
{
  instanceData.initialize();
}  // End of action function: ResetAccumulations

void Calculator::SetExponentEntry( [[maybe_unused]] Calculator_DataType const& input )
{
  subSM.CalculatorDisplay.instanceData.ExponentStart = true;
}  // End of action function: SetExponentEntry

void Calculator::SetFractionEntry( [[maybe_unused]] Calculator_DataType const& input )
{
  size_t const baseLen= strlen( subSM.CalculatorDisplay.instanceData.BaseDigits);
  if (baseLen == 0 )
  {
    subSM.CalculatorDisplay.instanceData.BaseDigits[0] = '0';
    subSM.CalculatorDisplay.instanceData.BaseDigits[1] = '\0';
  }

  subSM.CalculatorDisplay.instanceData.FractinalStart= true;
}  // End of action function: SetFractionEntry

void Calculator::Substractions( [[maybe_unused]] Calculator_DataType const& input )
{
  Calculator_Internal::CalculateAccumulator( this, &input, &instanceData, Calculator_Operator::E_OP_MINUS );
}  // End of action function: Substractions

// End of Calculator_Auxilary.cpp
