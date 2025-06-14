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

#include "Sensor_Close_End.hh"

#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <optional>
#include <thread>
#include <unistd.h>

Sensor_Close_End::Sensor_Close_End( )
{
  initialize( );
}

Sensor_Close_End::~Sensor_Close_End( )
{
  deinitialize( );
}

void Sensor_Close_End::initialize( )
{
  std::lock_guard<std::mutex> lockGuard( guard );;

  instanceData.initialize( );
  runningState.Main = Main_States::E_init;
}

void Sensor_Close_End::deinitialize( )
{
  std::lock_guard<std::mutex> lockGuard( guard );;

  terminate( );
  runningState.Main = Main_States::E_final;

  instanceData.deinitialize( );
}

void Sensor_Close_End::start( )
{
  if ( ! isIn_Main_Region( ) )
  {
    std::lock_guard<std::mutex> lockGuard( guard );

    init_Main( );
  }
}

void Sensor_Close_End::halt( )
{
  finalize_Main( );
}

bool Sensor_Close_End::isReady( ) const noexcept
{
  auto const ready = ( runningState.Main == Main_States::E_init );
  return ready;
}

bool Sensor_Close_End::isAlive( ) const noexcept
{
  auto const alive = isIn_Main_Region( );
  return alive;
}

bool Sensor_Close_End::isTerminated( ) const noexcept
{
  auto const terminated = ( runningState.Main == Main_States::E_final );
  return terminated;
}

bool Sensor_Close_End::is_Main_Region_Ready( ) const noexcept
{
  auto const ready = ( runningState.Main == Main_States::E_init );
  return ready;
}

bool Sensor_Close_End::is_Main_Region_Terminated( ) const noexcept
{
  auto const terminated = ( runningState.Main == Main_States::E_final );
  return terminated;
}

bool Sensor_Close_End::isIn_Main_Region( ) const noexcept
{
  bool const result = ( runningState.Main != Main_States::E_init ) &&
                      ( runningState.Main != Main_States::E_final );

  return result;
}

bool Sensor_Close_End::isIn_Main_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( ( runningState.Main == Main_States::E_Main ) || 
      ( runningState.Main == Main_States::E_Idle ) || 
      ( runningState.Main == Main_States::E_Check ) );

  return result;
}

bool Sensor_Close_End::isIn_Idle_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_Idle );

  return result;
}

bool Sensor_Close_End::isIn_Check_State( ) const noexcept
{
  bool const result = isIn_Main_Region( ) &&
    ( runningState.Main == Main_States::E_Check );

  return result;
}

Sensor_Close_End_DataType* Sensor_Close_End::getData( ) noexcept
{
  Sensor_Close_End_DataType* const pCustomData = &instanceData;
  return pCustomData;
}

void Sensor_Close_End::finalize_Main( )
{
  if ( isIn_Main_Region( ) )
  {
    if ( isIn_Idle_State( ) )
    {
      if ( doActionHandler.has_value( )
        && pthread_equal( doActionHandler.value( ), pthread_self( ) ) )
      {
        pthread_cancel( doActionHandler.value( ) );
        doActionHandler.reset( );
      }
    }
    else if ( isIn_Check_State( ) )
    {
      if ( doActionHandler.has_value( )
        && pthread_equal( doActionHandler.value( ), pthread_self( ) ) )
      {
        pthread_cancel( doActionHandler.value( ) );
        doActionHandler.reset( );
      }
    }
    else
    {
      // blank : to satistify MISRA rules
    }
    runningState.Main = Main_States::E_final;
  }
}

void Sensor_Close_End::terminate( )
{
  finalize_Main( );
}

void Sensor_Close_End::init_Main( )
{
  enter_Idle( );
  runningState.Main = Main_States::E_Idle;
}

void* Sensor_Close_End::doAction_Idle( )
{
  waitUntilDoorStartClosing( instanceData );

  std::lock_guard<std::mutex> lockGuard( guard );

  doActionHandler.reset( );

  if ( isIn_Idle_State( ) )
  {
    exit_Idle( );
    enter_Check( );
    runningState.Main = Main_States::E_Check;
  }

  return NULL;
}

void* Sensor_Close_End::doAction_Check( )
{
  checkDoorClosed( instanceData );

  std::lock_guard<std::mutex> lockGuard( guard );

  doActionHandler.reset( );

  if ( isIn_Check_State( ) )
  {
    notifyDoorClosed( instanceData );

    exit_Check( );
    enter_Idle( );
    runningState.Main = Main_States::E_Idle;
  }

  return NULL;
}

void Sensor_Close_End::enter_Idle( )
{
  runningState.Main = Main_States::E_Idle;

  doActionHandler = launchDoAction( callDoAction_Idle, this, nullptr, 0 );
}

void Sensor_Close_End::enter_Check( )
{
  runningState.Main = Main_States::E_Check;

  doActionHandler = launchDoAction( callDoAction_Check, this, nullptr, 0 );
}

void Sensor_Close_End::exit_Idle( )
{
  runningState.Main = Main_States::E_Idle;
  if ( doActionHandler.has_value( )
    && pthread_equal( doActionHandler.value( ), pthread_self( ) ) )
  {
    pthread_cancel( doActionHandler.value( ) );
    doActionHandler.reset( );
  }
}

void Sensor_Close_End::exit_Check( )
{
  runningState.Main = Main_States::E_Check;
  if ( doActionHandler.has_value( )
    && pthread_equal( doActionHandler.value( ), pthread_self( ) ) )
  {
    pthread_cancel( doActionHandler.value( ) );
    doActionHandler.reset( );
  }
}

void* Sensor_Close_End::callDoAction_Idle( void* arg )
{
  Sensor_Close_End* obj = reinterpret_cast< Sensor_Close_End* >( arg );
  obj->doAction_Idle( );

  return NULL;
}

void* Sensor_Close_End::callDoAction_Check( void* arg )
{
  Sensor_Close_End* obj = reinterpret_cast< Sensor_Close_End* >( arg );
  obj->doAction_Check( );

  return NULL;
}

pthread_t Sensor_Close_End::launchDoAction( void *(*threadStart)(void *), Sensor_Close_End* pStateMachine, void *stackAddr, size_t stackSize )
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

// End of Sensor_Close_End.cpp
