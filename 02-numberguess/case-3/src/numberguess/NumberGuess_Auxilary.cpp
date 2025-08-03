/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-12 GMT
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

#include "NumberGuess.hh"

#include <cassert>
#include <iostream>
#include <random>

#include <unistd.h>

namespace
{
  constexpr std::chrono::minutes GAME_TIME( 1U );
  constexpr std::chrono::seconds ESTIMATION_TIME( 20U );
  constexpr std::chrono::seconds WARNING_TIME( 10U );
}  // namespace

// The implementation of the guards
bool NumberGuess::AreNumbersEqual( ) const
{
  bool const result = ( instanceData.guess == instanceData.number );
  return result;
}  // End of guard function: AreNumbersEqual

bool NumberGuess::IsAnsweringTimeUp( ) const
{
  TimePoint now     = std::chrono::system_clock::now( );
  bool const result = now >= ( instanceData.estimation_begin + ESTIMATION_TIME );
  return result;
}  // End of guard function: IsAnsweringTimeUp

bool NumberGuess::IsAnswerNo( ) const
{
  bool const result = ( instanceData.answer == 'N' || instanceData.answer == 'n' );
  return result;
}  // End of guard function: IsAnswerNo

bool NumberGuess::IsAnswerYes( ) const
{
  bool const result = ( instanceData.answer == 'Y' || instanceData.answer == 'y' );
  return result;
}  // End of guard function: IsAnswerYes

bool NumberGuess::IsANumberRead( ) const
{
  return instanceData.scan_result;
}  // End of guard function: IsANumberRead

bool NumberGuess::IsDraw( ) const
{
  bool const result = ( instanceData.answer == '?' );
  return result;
}  // End of guard function: IsDraw

bool NumberGuess::IsGameTimeOver( ) const
{
  TimePoint now     = std::chrono::system_clock::now( );
  bool const result = now >= ( instanceData.game_begin + GAME_TIME );
  return result;
}  // End of guard function: IsGameTimeOver

bool NumberGuess::IsNumberInRange( ) const
{
  bool const result = ( instanceData.guess > 0 && instanceData.guess < 100 );
  return result;
}  // End of guard function: IsNumberInRange

bool NumberGuess::IsOnLeave( ) const
{
  bool const result = ( instanceData.answer == '!' );
  return result;
}  // End of guard function: IsOnLeave

bool NumberGuess::IsTimeRunOut( ) const
{
  bool result = instanceData.warn;

  if( result )
  {
    TimePoint now = std::chrono::system_clock::now( );
    result        = now >= ( instanceData.estimation_begin + WARNING_TIME );
  }

  return result;
}  // End of guard function: IsTimeRunOut

// The implementation of the actions
void NumberGuess::AskEstimation( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "Please make an estimation : ";
  std::cout.flush( );
}  // End of action function: AskEstimation

void NumberGuess::PrintAskNewDeal( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "Do you wanna play more game? ";
  std::cout.flush( );
}  // End of action function: PrintAskNewDeal

void NumberGuess::PrintConguratulation( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "\n   *** Done. Congratulations! ***\n\n";
}  // End of action function: PrintConguratulation

void NumberGuess::PrintGameOver( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "\n *** Time is up. Game is over *** \n\n";
}  // End of action function: PrintGameOver

void NumberGuess::PrintGoodBye( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "\nSee you next time. Bye bye\n";
}  // End of action function: PrintGoodBye

void NumberGuess::PrintHints( [[maybe_unused]] NumberGuess_DataType const& input )
{
  if( input.number > input.guess )
  {
    std::cout << "Your guess, " << input.guess << ", is smaller\n";
  }
  else if( input.number < input.guess )
  {
    std::cout << "Your guess, " << input.guess << ", is bigger\n";
  }
}  // End of action function: PrintHints

void NumberGuess::PrintHurryUp( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "\n *** Time is going up. Hurry up! *** \n\n";
  instanceData.warn = false;
}  // End of action function: PrintHurryUp

void NumberGuess::PrintNoNumberIsRead( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "Please enter a number!\n";
}  // End of action function: PrintNoNumberIsRead

void NumberGuess::PrintNumberIsNotInRange( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "Please enter a number betwen 1 and 99!\n";
}  // End of action function: PrintNumberIsNotInRange

void NumberGuess::PrintShowNumber( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "\n *** Sorry! Here is the secret number : " << input.number << " ***\n\n";
}  // End of action function: PrintShowNumber

void NumberGuess::PrintTimeIsUp( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "\n *** You are not fast enough. Game is over *** \n\n";
}  // End of action function: PrintTimeIsUp

void NumberGuess::PrintVola( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "Heyooo!\n";
}  // End of action function: PrintVola

void NumberGuess::PrintWarning( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "please answer pressing the key either 'Y' or 'N' only\n";
}  // End of action function: PrintWarning

void NumberGuess::ReadAnswerToContinue( [[maybe_unused]] NumberGuess_DataType const& input )
{
  char buffer[ 256 ];
  std::cin.clear( );
  std::cin.getline( buffer, sizeof( buffer ) - 1 );
  instanceData.answer = 0;
  if( ! std::cin.fail( ) )
  {
    static constexpr auto ws = " \t\n\r\v";

    std::string str( buffer );

    auto pos = str.find_first_not_of( ws );
    if( pos != str.npos )
    {
      str.erase( 0, pos );
    }

    if( ! str.empty( ) )
    {
      instanceData.answer = str.front( );
    }
  }

  std::cout << std::flush;
}  // End of action function: ReadAnswerToContinue

void NumberGuess::ReadEstimation( [[maybe_unused]] NumberGuess_DataType const& input )
{
  char buffer[ 256 ];
  std::cin.clear( );
  std::cin.getline( buffer, sizeof( buffer ) - 1 );
  instanceData.answer = 0;
  if( ! std::cin.fail( ) )
  {
    static constexpr auto ws     = " \t\n\r\v";
    static constexpr auto digits = "1234567890";

    std::string str( buffer );

    auto pos = str.find_first_not_of( ws );
    if( pos != str.npos )
    {
      str.erase( 0, pos );
    }

    pos = str.find_last_not_of( ws );
    if( pos != str.npos )
    {
      str.erase( pos + 1 );
    }

    pos = str.find_first_not_of( digits );
    if( pos != str.npos )
    {
      instanceData.scan_result = false;
    }
    else
    {
      try
      {
        instanceData.guess       = std::stoul( str );
        instanceData.scan_result = true;
      }
      catch( std::exception const& e )
      {
        instanceData.scan_result = false;
      }
    }
    if( ! instanceData.scan_result && ! str.empty( ) )
    {
      instanceData.answer = str.front( );
    }
  }

  std::cout << std::flush;
}  // End of action function: ReadEstimation

void NumberGuess::Salute( [[maybe_unused]] NumberGuess_DataType const& input )
{
  std::cout << "\nHello there. Let's play. I will pick a number between 1 and 99. And you will guess the number I picked\n";
}  // End of action function: Salute

void NumberGuess::SetANumber( [[maybe_unused]] NumberGuess_DataType const& input )
{
  static std::random_device rd;
  static std::mt19937 generator( rd( ) );
  static std::uniform_int_distribution< long unsigned int > numberDistribution( 1, 99 );
  instanceData.number = numberDistribution( generator );
}  // End of action function: SetANumber

void NumberGuess::StartAnswerTimer( [[maybe_unused]] NumberGuess_DataType const& input )
{
  instanceData.estimation_begin = std::chrono::system_clock::now( );
  instanceData.warn             = true;
}  // End of action function: StartAnswerTimer

void NumberGuess::StartEstimationTimer( [[maybe_unused]] NumberGuess_DataType const& input )
{
  instanceData.game_begin = std::chrono::system_clock::now( );
}  // End of action function: StartEstimationTimer

// End of NumberGuess_Auxilary.cpp
