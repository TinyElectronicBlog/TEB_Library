/*
  MIT License

  Copyright (c) 2022 TinyElectronicBlog

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef TEB_Debug_h
#define TEB_Debug_h

#include "../TEB_Configurations.h"
#include <Arduino.h>

#ifdef TEB_DB_DEBUG

/**
   \class TEB_Debug
   \brief This class contains methods related to debugging. Debug mode can be selected in the TEB_Library.h file.
*/
class TEB_Debug {

  public:

    /**
       \brief Constructor used with TEB_DB_DEBUG 2 or 0 mode. Is meant to be inserted at the beginning of each function, in order to keep track of the order in which the functions are executed.
       \param [in] text Function name.
    */
    TEB_Debug (const char* text);

    /**
       \brief Constructor used with TEB_DB_DEBUG 2 or 0 mode. Is meant to be inserted at the beginning of each function, in order to keep track of the order in which the functions are executed.
       \param [in] text Function name saved with PROGMEM.
    */
    TEB_Debug (const __FlashStringHelper* text);

    /**
       \brief Do not use. It is executed automatically.
    */
    ~TEB_Debug ();

    /**
       \brief In TEB_DB_DEBUG 1 or 0 mode prints information to the debug monitor.
       \param [in] c The character to be printed.
    */
    static void print (const char c);

    /**
       \brief In TEB_DB_DEBUG 1 or 0 mode prints information to the debug monitor.
       \param [in] number The number to be printed.
    */
    static void print (int32_t number);

    /**
       \brief In TEB_DB_DEBUG 1 or 0 mode prints information to the debug monitor.
       \param [in] number The number to be printed.
    */
    static void print (uint32_t number);

    /**
       \brief In TEB_DB_DEBUG 1 or 0 mode prints information to the debug monitor.
       \param [in] number The number to be printed.
    */
    static void print (float number);

    /**
       \brief In TEB_DB_DEBUG 1 or 0 mode prints information to the debug monitor.
       \param [in] text The text to be printed.
    */
    static void print (const char* text);

    /**
       \brief In TEB_DB_DEBUG 1 or 0 mode prints information to the debug monitor.
       \param [in] text The text saved with PROGMEM to be printed.
    */
    static void print (const __FlashStringHelper* text);

    /**
       \brief Prints an error message on the debug monitor.
       \param [in] number Error number.
       \param [in] text Error text.
    */
    static void error (size_t number, const char* text);

    /**
       \brief Prints an error message on the debug monitor.
       \param [in] number Error number.
       \param [in] text Error text saved with PROGMEM.
    */
    static void error (size_t number, const __FlashStringHelper* text);

    /**
       \brief Prints an error message on the debug monitor and blocks the execution of the program.
       \param [in] number Error number.
       \param [in] text Error text.
    */
    static void fatalError (size_t number, const char* text);

    /**
       \brief Prints an error message on the debug monitor and blocks the execution of the program.
       \param [in] number Error number.
       \param [in] text Error text saved with PROGMEM.
    */
    static void fatalError (size_t number, const __FlashStringHelper* text);


    /**
       \return The total free heap.
    */
    static size_t totalFreeHeap();

    /**
       \return The size of the largest block of free heap.
    */
    static size_t largestHeapFreeBlock();

    static void test ();

};
#endif

#endif