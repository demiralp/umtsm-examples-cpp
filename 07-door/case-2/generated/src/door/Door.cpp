/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-05-31 GMT
 *  Copyright (C) 2023-2025 Fedem (Fehmi Demiralp) <f.demiralp@gmail.com>
 *
 *  This file is generated by UMTSM using the code generator `CppGen`
 *
 *  !!! It is highly recommended that DO NOT EDIT THIS GENERATED FILE !!!
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

#include "Door.hh"

#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <optional>
#include <thread>
#include <unistd.h>

Door::Door( )
{
  initialize( );
}

Door::~Door( )
{
  deinitialize( );
}

void Door::initialize( )
{
  std::lock_guard<std::mutex> lockGuard( guard );;

  instanceData.initialize( );
  runningState.Main = Main_States::E_init;
}

void Door::deinitialize( )
{
  std::lock_guard<std::mutex> lockGuard( guard );;

  terminate( );
  runningState.Main = Main_States::E_final;

  instanceData.deinitialize( );
}

void Door::start( )
{
  if ( ! isIn_Main_Region( ) )
  {
    std::lock_guard<std::mutex> lockGuard( guard );

    storedState.shallow_Main = load_Shallow_Main( instanceData );

    init_Main( );
  }
}

void Door::halt( )
{
  finalize_Main( );
}

bool Door::isReady( ) const noexcept
{
  auto const ready = ( runningState.Main == Main_States::E_init );
  return ready;
}

bool Door::isAlive( ) const noexcept
{
  auto const alive = isIn_Main_Region( );
  return alive;
}

bool Door::isTerminated( ) const noexcept
{
  auto const terminated = ( runningState.Main == Main_States::E_final );
  return terminated;
}

bool Door::is_Main_Region_Ready( ) const noexcept
{
  auto const ready = ( runningState.Main == Main_States::E_init );
  return ready;
}

bool Door::is_Main_Region_Terminated( ) const noexcept
{
  auto const terminated = ( runningState.Main == Main_States::E_final );
  return terminated;
}

bool Door::isIn_Main_Region( ) const noexcept
{
  bool const result = ( runningState.Main != Main_States::E_init ) &&
                      ( runningState.Main != Main_States::E_final );

  return result;
}

bool Door::isIn_Main_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( ( runningState.Main == Main_States::E_Main ) || 
      ( runningState.Main == Main_States::E_Open ) || 
      ( runningState.Main == Main_States::E_Closing ) || 
      ( runningState.Main == Main_States::E_Close ) || 
      ( runningState.Main == Main_States::E_Opening ) );

  return result;
}

bool Door::isIn_Open_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_Open );

  return result;
}

bool Door::isIn_Closing_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_Closing );

  return result;
}

bool Door::isIn_Close_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_Close );

  return result;
}

bool Door::isIn_Opening_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_Opening );

  return result;
}

Door_DataType* Door::getData( ) noexcept
{
  Door_DataType* const pCustomData = &instanceData;
  return pCustomData;
}

void Door::trigger_ButtonPressed( )
{
  [[maybe_unused]] bool doneMain = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_Open_State( ) )
  {
    resetWaitingTime( instanceData );
  }
  else if ( isIn_Closing_State( ) )
  {
    engineStop( instanceData );

    enter_Opening( );
    runningState.Main = Main_States::E_Opening;
    storedState.shallow_Main = Main_States::E_Opening;
    store_Shallow_Main( storedState.shallow_Main, instanceData );
  }
  else if ( isIn_Close_State( ) )
  {
    enter_Opening( );
    runningState.Main = Main_States::E_Opening;
    storedState.shallow_Main = Main_States::E_Opening;
    store_Shallow_Main( storedState.shallow_Main, instanceData );
  }
  else
  {
    // left blank. the else block at the end is required by MISRA
  }
}

void Door::trigger_DoorClosed( )
{
  [[maybe_unused]] bool doneMain = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_Closing_State( ) )
  {
    engineStop( instanceData );

    runningState.Main = Main_States::E_Close;
    storedState.shallow_Main = Main_States::E_Close;
    store_Shallow_Main( storedState.shallow_Main, instanceData );
  }
}

void Door::trigger_DoorOpen( )
{
  [[maybe_unused]] bool doneMain = false;

  std::lock_guard<std::mutex> lockGuard( guard );

  if ( isIn_Opening_State( ) )
  {
    engineStop( instanceData );

    enter_Open( );
    runningState.Main = Main_States::E_Open;
    storedState.shallow_Main = Main_States::E_Open;
    store_Shallow_Main( storedState.shallow_Main, instanceData );
  }
}

void Door::finalize_Main( )
{
  if ( isIn_Main_Region( ) )
  {
    if ( isIn_Open_State( ) )
    {
      if ( doActionHandler.has_value( )
        && pthread_equal( doActionHandler.value( ), pthread_self( ) ) )
      {
        pthread_cancel( doActionHandler.value( ) );
        doActionHandler.reset( );
      }
    }
    runningState.Main = Main_States::E_final;
  }
}

void Door::terminate( )
{
  storeEntireStates( );
  finalize_Main( );
}

void Door::storeEntireStates( )
{
  store_Shallow_Main( storedState.shallow_Main, instanceData );
}

void Door::init_Main( )
{
  // started by history stored
  switch ( storedState.shallow_Main )
  {
    case Main_States::E_Open:
    {
      enter_Open( );
      runningState.Main = Main_States::E_Open;
      break;
    }
    case Main_States::E_Closing:
    {
      enter_Closing( );
      runningState.Main = Main_States::E_Closing;
      break;
    }
    case Main_States::E_Close:
    {
      runningState.Main = Main_States::E_Close;
      break;
    }
    case Main_States::E_Opening:
    {
      enter_Opening( );
      runningState.Main = Main_States::E_Opening;
      break;
    }
    default:
    {
      enter_Open( );
      runningState.Main = Main_States::E_Open;
      storedState.shallow_Main = Main_States::E_Open;
      store_Shallow_Main( storedState.shallow_Main, instanceData );
      break;
    }
  }
}

void* Door::doAction_Open( )
{
  wait( instanceData );

  std::lock_guard<std::mutex> lockGuard( guard );

  doActionHandler.reset( );

  if ( isIn_Open_State( ) )
  {
    exit_Open( );
    enter_Closing( );
    runningState.Main = Main_States::E_Closing;
    storedState.shallow_Main = Main_States::E_Closing;
    store_Shallow_Main( storedState.shallow_Main, instanceData );
  }

  return NULL;
}

void Door::enter_Open( )
{
  runningState.Main = Main_States::E_Open;

  resetWaitingTime( instanceData );

  doActionHandler = launchDoAction( callDoAction_Open, this, nullptr, 0 );
}

void Door::enter_Closing( )
{
  runningState.Main = Main_States::E_Closing;

  engineRunACCW( instanceData );
}

void Door::enter_Opening( )
{
  runningState.Main = Main_States::E_Opening;

  engineRunCCW( instanceData );
}

void Door::exit_Open( )
{
  runningState.Main = Main_States::E_Open;
  if ( doActionHandler.has_value( )
    && pthread_equal( doActionHandler.value( ), pthread_self( ) ) )
  {
    pthread_cancel( doActionHandler.value( ) );
    doActionHandler.reset( );
  }
}

void* Door::callDoAction_Open( void* arg )
{
  Door* obj = reinterpret_cast< Door* >( arg );
  obj->doAction_Open( );

  return NULL;
}

pthread_t Door::launchDoAction( void *(*threadStart)(void *), Door* pStateMachine, void *stackAddr, size_t stackSize )
{
  pthread_t thr = 0;

  if ( threadStart != NULL )
  {
    pthread_attr_t attr;

    int err = pthread_attr_init( &attr );
    if ( err == 0 )
    {
      err = pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );

      if ( err == 0 )
      {
        err = pthread_attr_setinheritsched( &attr, PTHREAD_EXPLICIT_SCHED );
      }

      if ( ( err == 0 ) && ( stackAddr != nullptr ) && ( stackSize > 0 ) )
      {
        err = pthread_attr_setstack( &attr, stackAddr, stackSize );
        err = 0;
      }

      if ( err == 0 )
      {
        err = pthread_create( &thr, &attr, threadStart, pStateMachine);
      }

      if ( err != 0 )
      {
        thr = 0;
      }

      pthread_attr_destroy( &attr );
    }
  }

  return thr;
}

// End of Door.cpp
