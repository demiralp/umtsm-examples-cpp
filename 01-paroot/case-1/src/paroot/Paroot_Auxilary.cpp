/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-04-14 GMT
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

#include "Paroot.hh"

#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <optional>
#include <thread>
#include <unistd.h>

#include <cmath>
#include <complex>
#include <cstdio>
#include <iostream>

using namespace std;

namespace
{
  constexpr double EPSILON = 1e-8;

  bool ReadParameter( double* const param );
  void PrintComplexNumber( double real, double imag );
}  // namespace

// The implementation of the actions
void Paroot::FindTheRoots( [[maybe_unused]] Paroot_DataType const& input )
{
  double delta = ( input.paramB * input.paramB - 4.0 * input.paramA * input.paramC );

  if( fabs( delta ) <= EPSILON )
  {
    delta = 0.0;

    instanceData.root1 = instanceData.root2 = -input.paramB / ( 2.0 * input.paramA );
    instanceData.croot1 = instanceData.croot2 = 0.0;
    instanceData.solutionType                 = Paroot_Solution::MONO;
  }
  else if( delta > 0.0 )
  {
    double deltaSq = sqrt( delta );

    instanceData.root1  = ( -input.paramB - deltaSq ) / ( 2.0 * input.paramA );
    instanceData.root2  = ( -input.paramB + deltaSq ) / ( 2.0 * input.paramA );
    instanceData.croot1 = instanceData.croot2 = 0.0;
    instanceData.solutionType                 = Paroot_Solution::REAL;
  }
  else
  {
    auto deltaSq = sqrt( complex< double >( delta ) );

    instanceData.root1 = instanceData.root2 = 0.0;
    instanceData.croot1                     = ( -input.paramB - deltaSq ) / ( 2.0 * input.paramA );
    instanceData.croot2                     = ( -input.paramB + deltaSq ) / ( 2.0 * input.paramA );
    instanceData.solutionType               = Paroot_Solution::COMPLEX;
  }
}  // End of action function: FindTheRoots

void Paroot::ReadParameters( [[maybe_unused]] Paroot_DataType const& input )
{
  bool readingOkay = false;
  do
  {
    std::cout << "Enter parameter A : ";
    std::cout.flush( );

    readingOkay = ReadParameter( &instanceData.paramA ) && fabs( instanceData.paramA ) > EPSILON;
  } while( ! readingOkay );

  do
  {
    cout << "Enter parameter B : ";
    cout.flush( );
    readingOkay = ReadParameter( &instanceData.paramB );
  } while( ! readingOkay );

  do
  {
    cout << "Enter parameter C : ";
    cout.flush( );
    readingOkay = ReadParameter( &instanceData.paramC );
  } while( ! readingOkay );
}  // End of action function: ReadParameters

void Paroot::WriteSolutions( [[maybe_unused]] Paroot_DataType const& input )
{
  switch( input.solutionType )
  {
    case Paroot_Solution::MONO:
    {
      cout << "both roots are equal to : " << input.root1 << '\n';
      break;
    }
    case Paroot_Solution::REAL:
    {
      cout << "root1 : " << input.root1 << '\n';
      cout << "root2 : " << input.root2 << '\n';
      break;
    }
    case Paroot_Solution::COMPLEX:
    {
      cout << "root1 : ";
      PrintComplexNumber( input.croot1.real( ), input.croot1.imag( ) );
      cout << '\n';

      cout << "root2 : ";
      PrintComplexNumber( input.croot2.real( ), input.croot2.imag( ) );
      cout << '\n';
      break;
    }
  }
}  // End of action function: WriteSolutions

namespace
{
  bool ReadParameter( double* const param )
  {
    char buffer[ 256 ];
    int readByte = read( 0, buffer, sizeof( buffer ) - 1 );
    bool result  = ( readByte > 0 );
    if( result )
    {
      std::istringstream iss( buffer );

      iss >> *param;

      result = static_cast<bool>(iss);
    }

    fflush( stdin );

    return result;
  }

  void PrintComplexNumber( double real, double imag )
  {
    cout << real;

    if( fabs( imag ) > EPSILON )
    {
      if( imag > 0 )
      {
        cout << '+';
      }
      cout << imag << 'i';
    }
  }
}  // namespace

// End of Paroot_Auxilary.cpp
