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

#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

class Paroot
{
    static constexpr double EPSILON = 1e-8;

    typedef enum E_Paroot_Solution
    {
      UNDEFINED,
      MONO,
      REAL,
      COMPLEX
    } E_Paroot_Solution_t;

    double paramA;
    double paramB;
    double paramC;

    double root1;
    double root2;
    complex< double > croot1;
    complex< double > croot2;

    E_Paroot_Solution_t solutionType;

  public:
    Paroot( );

    void Run( );

  private:
    void FindTheRoots( );
    void ReadParameters( );
    void WriteSolutions( );

    static bool ReadParameter( double* const param );
    static void PrintComplexNumber( double real, double imag );
};

Paroot::Paroot( )
{
  paramA = 1.0;
  paramB = paramC = root1 = root2 = 0.0;
  croot1 = croot2 = 0.0;
}

void Paroot::Run( )
{
  ReadParameters( );
  FindTheRoots( );
  WriteSolutions( );
}

void Paroot::ReadParameters( )
{
  bool readingOkay = false;
  do
  {
    std::cout << "Enter parameter A : ";
    std::cout.flush( );

    readingOkay = ReadParameter( &paramA ) && fabs( paramA ) > EPSILON;
  } while( ! readingOkay );

  do
  {
    cout << "Enter parameter B : ";
    cout.flush( );
    readingOkay = ReadParameter( &paramB );
  } while( ! readingOkay );

  do
  {
    cout << "Enter parameter C : ";
    cout.flush( );
    readingOkay = ReadParameter( &paramC );
  } while( ! readingOkay );
}

void Paroot::FindTheRoots( )
{
  double delta = ( paramB * paramB - 4.0 * paramA * paramC );

  if( fabs( delta ) <= EPSILON )
  {
    delta = 0.0;
    root1 = root2 = -paramB / ( 2.0 * paramA );
    croot1 = croot2 = 0.0;
    solutionType    = MONO;
  }
  else if( delta > 0.0 )
  {
    double deltaSq = sqrt( delta );
    root1          = ( -paramB - deltaSq ) / ( 2.0 * paramA );
    root2          = ( -paramB + deltaSq ) / ( 2.0 * paramA );
    croot1 = croot2 = 0.0;
    solutionType    = REAL;
  }
  else
  {
    auto deltaSq = sqrt( complex< double >( delta ) );

    root1 = root2 = 0.0;
    croot1        = ( -paramB - deltaSq ) / ( 2.0 * paramA );
    croot2        = ( -paramB + deltaSq ) / ( 2.0 * paramA );
    solutionType  = COMPLEX;
  }
}

void Paroot::WriteSolutions( )
{
  switch( solutionType )
  {
    case MONO:
    {
      cout << "both roots are equal to : " << root1 << '\n';
      break;
    }
    case REAL:
    {
      cout << "root1 : " << root1 << '\n';
      cout << "root2 : " << root2 << '\n';
      break;
    }
    case COMPLEX:
    {
      cout << "root1 : ";
      PrintComplexNumber( croot1.real(), croot1.imag());
      cout << '\n';

      cout << "root2 : ";
      PrintComplexNumber( croot2.real(), croot2.imag());
      cout << '\n';
      break;
    }
  }
}

bool Paroot::ReadParameter( double* const param )
{
  std::string line;

  bool result = false;

  if( std::getline( cin, line ) )
  {
    std::istringstream iss( line );

    if( ( iss >> *param ) )
    {
      char remaining;
      iss >> remaining;

      result = true;
    }
  }

  return result;
}

void Paroot::PrintComplexNumber( double real, double imag )
{
  cout << real;

  if ( fabs(imag) > EPSILON)
  {
    if (imag > 0 )
    {
      cout << '+';
    }
    cout << imag << 'i';
  }
}

int main( int const, char const* const* )
{
  Paroot paroot;

  paroot.Run( );

  return EXIT_SUCCESS;
}
