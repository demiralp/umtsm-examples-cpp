/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-08 GMT
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

#include "ExecutionDirector_DataType.hh"

ExecutionDirector_DataType::ExecutionDirector_DataType( )
{
  initialize( );
}

ExecutionDirector_DataType::~ExecutionDirector_DataType( )
{
  deinitialize( );
}

void ExecutionDirector_DataType::initialize( )
{
  ControlModeStatus    = ControlMode::PERSISTENT_CONTROL_MODE;
  StartSwitchingTime   = std::chrono::system_clock::now( );
  pCrossroad           = nullptr;
  pMonitor             = nullptr;
  LaneClosingCompleted = false;
  LaneRequested        = -1;
  NextLane             = -1;
  LaneCmd1             = Lane_Command::E_CMD_NOPE;
  LaneCmd2             = Lane_Command::E_CMD_NOPE;
  LaneCmd3             = Lane_Command::E_CMD_NOPE;
  LaneCmd4             = Lane_Command::E_CMD_NOPE;
}

void ExecutionDirector_DataType::deinitialize( )
{
  // blank
}

// End of ExecutionDirector_DataType.cpp
