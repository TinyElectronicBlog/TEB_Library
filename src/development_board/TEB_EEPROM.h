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

#ifndef TEB_EEPROM_h
#define TEB_EEPROM_h

#include "../TEB_Configurations.h"
#include <Arduino.h>

/**
   \class TEB_EEPROM
   \brief This class contains methods to manage the EEPROM memory of the development board.
*/
class TEB_EEPROM {

  public:

    /**
       \brief Set it to the smallest unsigned int type that can index EEPROM elements.
    */
    typedef uint8_t uintDataType;

    /**
       \brief Saves data in EEPROM.
       \param [in] value Data to be saved.
       \param [in] valueLength Value length. Must be > 0 and <= 512.
       \return 1 if ok.
    */
    static int8_t write (const uint8_t* value, uintDataType valueLength);

    /**
       \brief Read data from EEPROM.
       \param [in] buffer Buffer in which to save the data.
       \param [in] bufferSize Buffer size. Must be > 0 and <= 512.
       \return 1 if ok.
    */
    static int8_t read (uint8_t* buffer, uintDataType bufferSize);

#ifdef TEB_DB_DEBUG
    static void test ();
#endif

};

#endif