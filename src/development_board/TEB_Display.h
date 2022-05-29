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

#ifndef TEB_Display_h
#define TEB_Display_h

#include "../TEB_Configurations.h"
#include <Arduino.h>

/**
   \class TEB_Display
   \brief This class contains methods to manage a display connected to the development board.
*/
class TEB_Display {

  public:

    /**
       \brief Print a message on the display.
       \param [in] text Text to print.
       \param [in] textSize Text size. Must be > 0.
    */
    static void print (const char* text, uint8_t textSize);

    /**
       \brief Print a message on the display.
       \param [in] text Text saved with PROGMEM to print.
       \param [in] textSize Text size. Must be > 0.
    */
    static void print (const __FlashStringHelper* text, uint8_t textSize);

#ifdef TEB_DB_DEBUG
    static void test ();
#endif

};

#endif