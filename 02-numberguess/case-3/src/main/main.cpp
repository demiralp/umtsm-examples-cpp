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

/**********************************************/
/*               CASE 3                       */
/**********************************************/

#include <NumberGuess.hh>

#include <csignal>
#include <cstdlib>

#include <unistd.h>

NumberGuess numberguess;
std::sig_atomic_t volatile signalReceived = -1;

void signal_handler( int sig )
{
  signalReceived = sig;
}

void SignalHandler( )
{
  do
  {
    std::this_thread::sleep_for( std::chrono::milliseconds( 20 ) );
    switch( signalReceived )
    {
      case SIGINT:
      {
        numberguess.trigger_abort( );
        break;
      }
      case SIGUSR1:
      {
        numberguess.trigger_show( );
        break;
      }
      case SIGUSR2:
      {
        numberguess.trigger_newgame( );
        break;
      }
      default:
      {
        // blank
      }
    }
    signalReceived = -1;
  } while( true );
}

int main( )
{
  std::thread SignalExecutor( SignalHandler );
  SignalExecutor.detach( );

  signal( SIGINT, signal_handler );
  signal( SIGUSR1, signal_handler );
  signal( SIGUSR2, signal_handler );

  numberguess.start( );

  while( numberguess.isAlive( ) )
  {
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    numberguess.trigger_clock1sec( );
  }

  return EXIT_SUCCESS;
}
