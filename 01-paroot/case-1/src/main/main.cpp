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

#include <Paroot.hh>

#include <csignal>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <atomic>
#include <unistd.h>

Paroot parabole;

volatile std::sig_atomic_t haltParoot;

void signal_handler( int sig )
{
  switch( sig )
  {
    case SIGINT:
    {
      haltParoot= true;
      break;
    }
  }
}

int main( )
{
  /* Start entire the State Machines */
  parabole.start( );

  signal( SIGINT, signal_handler );

  while( parabole.isAlive( ) )
  {
    std::this_thread::sleep_for( std::chrono::milliseconds(100));
    if ( haltParoot)
    {
      parabole.halt();
    }
  }

  /* exit the application */
  std::cout << "\nExited!\n";

  return EXIT_SUCCESS;
}
