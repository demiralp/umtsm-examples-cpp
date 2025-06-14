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

#include <PedestrianLights.hh>

#undef private
#undef protected

namespace sm
{
  namespace test
  {
    class PedestrianLights_Mock
      : public PedestrianLights
    {
      public:
        // The mock of the guards
        MOCK_METHOD( bool, IsStopCheckAndGo, ( ), ( const, override ) );
        MOCK_METHOD( bool, IsCheckAndGo, ( ), ( const, override ) );
        MOCK_METHOD( bool, IsSystemSwitching, ( ), ( const, override ) );
        MOCK_METHOD( bool, IsLaneClose, ( ), ( const, override ) );
        MOCK_METHOD( bool, IsSystemOperational, ( ), ( const, override ) );
        MOCK_METHOD( bool, IsLaneOpen, ( ), ( const, override ) );

        // The mock of the actions
        MOCK_METHOD( void, SwitchRedLightOff, ( PedestrianLights_DataType const& input ), ( override ) );
        MOCK_METHOD( void, CountForFlashing, ( PedestrianLights_DataType const& input ), ( override ) );
        MOCK_METHOD( void, SwitchRedLightOn, ( PedestrianLights_DataType const& input ), ( override ) );
        MOCK_METHOD( void, SwitchGreenLightOff, ( PedestrianLights_DataType const& input ), ( override ) );
        MOCK_METHOD( void, SwitchGreenLightOn, ( PedestrianLights_DataType const& input ), ( override ) );
    }; // End Of the class `PedestrianLights_Mock`
  }  // End namespace test
}  // End namespace sm

// End of PedestrianLights_Mock.hh

