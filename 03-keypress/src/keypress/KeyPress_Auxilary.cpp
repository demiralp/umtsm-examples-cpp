/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-10 GMT
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

#include "KeyPress.hh"

#include <cassert>
#include <cstddef>
#include <cstring>

#include <ncurses.h>

// The implementation of the guards
bool KeyPress::IsCountingFinished( ) const
{
  bool const result = ! isIn_Numeric_Region( ) && ! isIn_Alpha_Region( );
  return result;
}  // End of guard function: IsCountingFinished

// The implementation of the actions
void KeyPress::Count1( KeyPress_DataType const& input )
{
  instanceData.countDigit[ 0 ] = input.countDigit[ 0 ] + 1;
}  // End of action function: Count1

void KeyPress::Count2( KeyPress_DataType const& input )
{
  instanceData.countDigit[ 1 ] = input.countDigit[ 1 ] + 1;
}  // End of action function: Count2

void KeyPress::Count3( KeyPress_DataType const& input )
{
  instanceData.countDigit[ 2 ] = input.countDigit[ 2 ] + 1;
}  // End of action function: Count3

void KeyPress::Count4( KeyPress_DataType const& input )
{
  instanceData.countDigit[ 3 ] = input.countDigit[ 3 ] + 1;
}  // End of action function: Count4

void KeyPress::Count5( KeyPress_DataType const& input )
{
  instanceData.countDigit[ 4 ] = input.countDigit[ 4 ] + 1;
}  // End of action function: Count5

void KeyPress::Count6( KeyPress_DataType const& input )
{
  instanceData.countDigit[ 5 ] = input.countDigit[ 5 ] + 1;
}  // End of action function: Count6

void KeyPress::Count7( KeyPress_DataType const& input )
{
  instanceData.countDigit[ 6 ] = input.countDigit[ 6 ] + 1;
}  // End of action function: Count7

void KeyPress::Count8( KeyPress_DataType const& input )
{
  instanceData.countDigit[ 7 ] = input.countDigit[ 7 ] + 1;
}  // End of action function: Count8

void KeyPress::Count9( KeyPress_DataType const& input )
{
  instanceData.countDigit[ 8 ] = input.countDigit[ 8 ] + 1;
}  // End of action function: Count9

void KeyPress::CountA( KeyPress_DataType const& input )
{
  instanceData.countA = input.countA + 1;
}  // End of action function: CountA

void KeyPress::CountB( KeyPress_DataType const& input )
{
  instanceData.countB = input.countB + 1;
}  // End of action function: CountB

void KeyPress::CountC( KeyPress_DataType const& input )
{
  instanceData.countC = input.countC + 1;
}  // End of action function: CountC

void KeyPress::CountEven( KeyPress_DataType const& input )
{
  instanceData.countEven = input.countEven + 1;
}  // End of action function: CountEven

void KeyPress::CountOdd( KeyPress_DataType const& input )
{
  instanceData.countOdd = input.countOdd + 1;
}  // End of action function: CountOdd

void KeyPress::LogCounters( KeyPress_DataType const& input )
{
  printw( "\r%5u %-4zu %-4zu %-4zu %-4zu %-4zu",
          input.issueId,
          input.countA,
          input.countB,
          input.countC,
          input.countOdd,
          input.countEven );
  for( size_t i = 0; i < sizeof( input.countDigit ) / sizeof( input.countDigit[ 0 ] ); ++i )
  {
    printw( " %-4zu", input.countDigit[ i ] );
  }

  char alphaStatus;
  char numericStatus;

  if( isIn_ReadLetters_State( ) )
  {
    alphaStatus = 'Y';
  }
  else if( isIn_Pause_State( ) )
  {
    alphaStatus = 'P';
  }
  else
  {
    alphaStatus = 'N';
  }

  if( isIn_ReadDigits_State( ) )
  {
    numericStatus = 'Y';
  }
  else
  {
    numericStatus = 'N';
  }

  printw( " %-2c %-2c", alphaStatus, numericStatus );

  instanceData.issueId = input.issueId + 1;
}  // End of action function: LogCounters

void KeyPress::LogHeaders( KeyPress_DataType const& input )
{
  printw( "\n%5s %-4s %-4s %-4s %-4s %-4s", "Issue", "A", "B", "C", "Odd", "Even" );
  for( size_t i = 0; i < sizeof( input.countDigit ) / sizeof( input.countDigit[ 0 ] ); ++i )
  {
    printw( " %-4zu", i + 1 );
  }
  printw( " CA CN\n" );

  printw( "----- ---- ---- ---- ---- ----" );
  for( size_t i = 0; i < sizeof( input.countDigit ) / sizeof( input.countDigit[ 0 ] ); ++i )
  {
    printw( " ----" );
  }

  printw( " -- --\n" );
}  // End of action function: LogHeaders

void KeyPress::MessageGoodBye( KeyPress_DataType const& input )
{
  printw( "\nSee you next time. Good Bye\n" );
}  // End of action function: MessageGoodBye

void KeyPress::MessageHello( KeyPress_DataType const& input )
{
  printw( "Counts letter A, B and C, all are incase sensitive, and mumbers between 1 and 9 pressed using by keyboard.\n" );
  printw( "Pressing F12 will pause the counting letters A, B and C.\n" );
  printw( "To resume the counting press F12 again.\n" );
  printw( "Pressing F1 will stop the counting letters perminantly.\n" );
  printw( "Pressing F2 key will stop the counting numbers perminantly.\n" );
  printw( "Pressing DEL or BACKSPACE will be reset the counters for numeric keys.\n" );
  printw( "Pressing SPACE will be reset the counters for letters keys.\n\n" );
}  // End of action function: MessageHello

void KeyPress::MessagePressSpaceToExit( KeyPress_DataType const& input )
{
  printw( "\nPress SPACE to exit\n" );
}  // End of action function: MessagePressSpaceToExit

void KeyPress::ResetLetterCounters( KeyPress_DataType const& input )
{
  instanceData.countA = instanceData.countB = instanceData.countC = 0;
}  // End of action function: ResetLetterCounters

void KeyPress::ResetNumericCounters( KeyPress_DataType const& input )
{
  instanceData.countOdd = instanceData.countEven = 0;

  for( size_t i = 0; i < sizeof( instanceData.countDigit ) / sizeof( instanceData.countDigit[ 0 ] ); ++i )
  {
    instanceData.countDigit[ i ] = 0;
  }
}  // End of action function: ResetNumericCounters

// End of KeyPress_Auxilary.cpp
