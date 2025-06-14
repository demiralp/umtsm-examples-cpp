/*  ==============================================================================
 *  Created by Fehmi Demiralp(Fedem) on 2025-06-08 GMT
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

#pragma once

#include <cstdint>

#include <mutex>
#include <optional>
#include <thread>

#include <Keypad_DataType.hh>

class Keypad
{
  private:
    enum class Main_States
    {
      E_init,
      E_Main,
      E_final
    };

  private:
    std::mutex guard;

    struct
    {
      Main_States Main;
    } runningState;

  private:
    std::optional< pthread_t > doActionHandler;

  public:
    Keypad_DataType instanceData;

  public:
    Keypad( );
    virtual ~Keypad( );

    void initialize( );
    void deinitialize( );

    void start( );
    void halt( );

    bool isReady( ) const noexcept;
    bool isAlive( ) const noexcept;
    bool isTerminated( ) const noexcept;

    bool is_Main_Region_Ready( ) const noexcept;

    bool is_Main_Region_Terminated( ) const noexcept;

    bool isIn_Main_Region( ) const noexcept;

    bool isIn_Main_State( ) const noexcept;

    void trigger_Notify( );

    Keypad_DataType* getData( ) noexcept;

  private:
    void finalize_Main( );
    void terminate( );

    void* doAction_Main( );

    void enter_Main( );

    void exit_Main( );


  // The interface of the guards
  public:
    virtual bool IsBackspace( ) const;
    virtual bool IsClear( ) const;
    virtual bool IsDigit( ) const;
    virtual bool IsDivisor( ) const;
    virtual bool IsDot( ) const;
    virtual bool IsEnter( ) const;
    virtual bool IsExponent( ) const;
    virtual bool IsMinus( ) const;
    virtual bool IsMultiplay( ) const;
    virtual bool IsPlus( ) const;
    virtual bool IsReset( ) const;
    virtual bool IsSignature( ) const;

  // The interface of the actions
  protected:
    virtual void NotifyBackspce( Keypad_DataType const& input );
    virtual void NotifyClear( Keypad_DataType const& input );
    virtual void NotifyDigit( Keypad_DataType const& input );
    virtual void NotifyDivisor( Keypad_DataType const& input );
    virtual void NotifyDot( Keypad_DataType const& input );
    virtual void NotifyEnter( Keypad_DataType const& input );
    virtual void NotifyExponent( Keypad_DataType const& input );
    virtual void NotifyMinus( Keypad_DataType const& input );
    virtual void NotifyMultiplay( Keypad_DataType const& input );
    virtual void NotifyPlus( Keypad_DataType const& input );
    virtual void NotifyReset( Keypad_DataType const& input );
    virtual void NotifySignatureChange( Keypad_DataType const& input );
    virtual void ReadKey( Keypad_DataType const& input );

  // The interface of the thread support functions
  private:
    static void* callDoAction_Main( void* arg );

    static pthread_t launchDoAction( void *(*threadStart)(void *), Keypad* pStateMachine, void *stackAddr, size_t stackSize );
  };

  // End of Keypad.hh
