/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-06-09 GMT
 *  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
 *
 *  This file is generated by UMTSM using the code generator `CppGen`
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

#pragma once

#include <gmock/gmock.h>

#define private public
#define protected public

#include <Calculator.hh>

#undef private
#undef protected

namespace sm
{
  namespace test
  {
    class Calculator_Mock
      : public Calculator
    {
      public:
        // The mock of the guards
        MOCK_METHOD( bool, IsBaseZero, ( ), ( const, override ) );
        MOCK_METHOD( bool, IsFractionZero, ( ), ( const, override ) );
        MOCK_METHOD( bool, IsThereSpaceForExponent, ( ), ( const, override ) );
        MOCK_METHOD( bool, IsExponentZero, ( ), ( const, override ) );
        MOCK_METHOD( bool, HasDivisionByZeroError, ( ), ( const, override ) );
        MOCK_METHOD( bool, HasOverflowError, ( ), ( const, override ) );
        MOCK_METHOD( bool, IsFaulty, ( ), ( const, override ) );

        // The mock of the actions
        MOCK_METHOD( void, ResetAccumulations, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, NotifyDisplayUpdate, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, CheckErrorStatus, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, ClearLastEntry, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, DrawSpliteLine, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, Additions, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, Substractions, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, Multiplications, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, Divides, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, Calculate, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, ClearFraction, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, ClearExponent, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, PushBaseDigit, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, EraseBaseDigit, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, ChangeBaseSign, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, SetFractionEntry, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, PushFractionDigit, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, EraseFractionDigit, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, RemoveZerosFromFraction, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, SetExponentEntry, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, PushExponentDigit, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, EraseExponentDigit, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, ChangeExponetSign, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, NotifyReset, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, NotifyFaultError, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, NotifyDivisionByZeroError, ( Calculator_DataType const& input ), ( override ) );
        MOCK_METHOD( void, NotifyOverflowError, ( Calculator_DataType const& input ), ( override ) );
    }; // End Of the class `Calculator_Mock`
  }  // End namespace test
}  // End namespace sm

// End of Calculator_Mock.hh

