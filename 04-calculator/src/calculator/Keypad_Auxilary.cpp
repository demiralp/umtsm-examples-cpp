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

#include "Keypad.hh"

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

#include <ncurses.h>
#include <wchar.h>

// The implementation of the guards
bool Keypad::IsBackspace( ) const
{
  bool const result = instanceData.LastInputKey == KEY_BACKSPACE;
  return result;
}  // End of guard function: IsBackspace

bool Keypad::IsClear( ) const
{
  bool const result = instanceData.LastInputKey == KEY_DC;
  return result;
}  // End of guard function: IsClear

bool Keypad::IsDigit( ) const
{
  bool const result = isdigit(instanceData.LastInputKey);
  return result;
}  // End of guard function: IsDigit

bool Keypad::IsDivisor( ) const
{
  bool const result = instanceData.LastInputKey == '/';
  return result;
}  // End of guard function: IsDivisor

bool Keypad::IsDot( ) const
{
  /* @todo Missing implementation */
  bool const result = instanceData.LastInputKey == '.' || instanceData.LastInputKey == ',';
  return result;
}  // End of guard function: IsDot

bool Keypad::IsEnter( ) const
{
  bool const result = instanceData.LastInputKey == '\n' || instanceData.LastInputKey == KEY_ENTER || instanceData.LastInputKey == '=';
  return result;
}  // End of guard function: IsEnter

bool Keypad::IsExponent( ) const
{
  bool const result = instanceData.LastInputKey == 'e' || instanceData.LastInputKey == 'E';
  return result;
}  // End of guard function: IsExponent

bool Keypad::IsMinus( ) const
{
  bool const result = instanceData.LastInputKey == '-';
  return result;
}  // End of guard function: IsMinus

bool Keypad::IsMultiplay( ) const
{
  bool const result = instanceData.LastInputKey == '*';
  return result;
}  // End of guard function: IsMultiplay

bool Keypad::IsPlus( ) const
{
  bool const result = instanceData.LastInputKey == '+';
  return result;
}  // End of guard function: IsPlus

bool Keypad::IsReset( ) const
{
  bool const result = instanceData.LastInputKey == 'c' || instanceData.LastInputKey == 'C';
  return result;
}  // End of guard function: IsReset

bool Keypad::IsSignature( ) const
{
  bool const result = instanceData.LastInputKey == 's' || instanceData.LastInputKey == 'S';
  return result;
}  // End of guard function: IsSignature

// The implementation of the actions
void Keypad::NotifyBackspce( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_Backspace( );
}  // End of action function: NotifyBackspce

void Keypad::NotifyClear( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_Clear( );
}  // End of action function: NotifyClear

void Keypad::NotifyDigit( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_Digit( );
}  // End of action function: NotifyDigit

void Keypad::NotifyDivisor( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_Division( );
}  // End of action function: NotifyDivisor

void Keypad::NotifyDot( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_Dot( );
}  // End of action function: NotifyDot

void Keypad::NotifyEnter( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_Enter( );
}  // End of action function: NotifyEnter

void Keypad::NotifyExponent( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_Exponents( );
}  // End of action function: NotifyExponent

void Keypad::NotifyMinus( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_Minus( );
}  // End of action function: NotifyMinus

void Keypad::NotifyMultiplay( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_Multiplay( );
}  // End of action function: NotifyMultiplay

void Keypad::NotifyPlus( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_Plus( );
}  // End of action function: NotifyPlus

void Keypad::NotifyReset( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_Reset( );
}  // End of action function: NotifyReset

void Keypad::NotifySignatureChange( Keypad_DataType const& input )
{
  instanceData.pCalculator->trigger_ChangeSign( );
}  // End of action function: NotifySignatureChange

void Keypad::ReadKey( Keypad_DataType const& input )
{
  static char const * const keyChar = ".,+-/*=eEsScC";
  while( true )
  {
    int ch;
    instanceData.LastInputKey = ch = wgetch(stdscr);

    if ( isdigit(ch) ||
         strchr(keyChar, ch) != NULL ||
         ch == '\n' ||
         ch == KEY_ENTER ||
         ch == KEY_BACKSPACE ||
         ch == KEY_DC )
    {
      trigger_Notify();
    }
  }
}  // End of action function: ReadKey

// End of Keypad_Auxilary.cpp
