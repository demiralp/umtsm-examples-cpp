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

#include "Calculator_Utilities.hh"

#include "Calculator_DataType.hh"
#include "Display_Utilities.hh"

#include <math.h>

#include <ncurses.h>

namespace Calculator_Internal
{
  void CalculateAccumulator(
    Calculator* const smInfo,
    Calculator_DataType const * const pInputData,
    Calculator_DataType* const pOutputData,
    Calculator_Operator currentOp )
  {
    static char const OpChar[] = { ' ', '+', '-', '*', '/', '=' };

    char dispdata[20];
    Display_Internal::GetAccumulatorData( smInfo->getSubSM_CalculatorDisplay()->getData(), dispdata, sizeof(dispdata) );
    long double value;
    int err= sscanf( dispdata, "%Le", &value );

    if ( pInputData->Operator != Calculator_Operator::E_OP_NONE )
    {
      DrawSeparator();
    }
    else
    {
      printw( "%c", OpChar[static_cast<int>( currentOp) ] );
    }

    if ( ( err != 1) && isinf( value ) )
    {
      pOutputData->ErrorNo= Calculator_Error::E_OVERFLOW;
    }
    else
    {
      switch (pInputData->Operator)
      {
        case Calculator_Operator::E_OP_ENTER:
        [[fallthrough]];
        case Calculator_Operator::E_OP_NONE:
        {
          pOutputData->Accumulator= value;
          break;
        }
        case Calculator_Operator::E_OP_PLUS:
        {
          pOutputData->Accumulator += value;
          break;
        }
        case Calculator_Operator::E_OP_MINUS:
        {
          pOutputData->Accumulator -= value;
          break;
        }
        case Calculator_Operator::E_OP_MULTIPLY:
        {
          pOutputData->Accumulator *= value;
          break;
        }
        case Calculator_Operator::E_OP_DIVIDE:
        {
          if ( value == 0.0 )
          {
            pOutputData->ErrorNo= Calculator_Error::E_DIVISION_BY_ZERO;
          }
          else
          {
            pOutputData->Accumulator /= value;
          }
          break;
        }
      }

      if ( pOutputData->ErrorNo == Calculator_Error::E_NO_ERROR)
      {
        if(isinf(pOutputData->Accumulator))
        {
          pOutputData->ErrorNo= Calculator_Error::E_OVERFLOW;
        }
        else if ( pOutputData->Operator != Calculator_Operator::E_OP_NONE )
        {
          printw("%-20.15LG%c", pOutputData->Accumulator, OpChar[static_cast<int>( currentOp ) ] );
        }
      }

      if ( pOutputData->ErrorNo == Calculator_Error::E_NO_ERROR)
      {
        if (currentOp == Calculator_Operator::E_OP_ENTER)
        {
          DrawSeparator();
        }
        else
        {
          printw("\n");
        }

        pOutputData->Operator = currentOp;
      }
      else if (pOutputData->Operator == Calculator_Operator::E_OP_NONE )
      {
          DrawSeparator();
      }
      else
      {
        // do nothing
      }
    }
  }

  void DrawSeparator( )
  {
    printw("\n");
    for(int i=20; i; --i)
    {
      printw("-");
    }
    printw("\n");
  }  // End of action function: DrawSpliteLine

}

// End of Calculator_Utilities.cpp
