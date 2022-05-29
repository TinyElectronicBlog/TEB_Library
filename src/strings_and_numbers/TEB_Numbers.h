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

#ifndef TEB_Numbers_h
#define TEB_Numbers_h

#include "../development_board/TEB_Debug.h"
#ifdef TEB_DB_DEBUG
#include "../TEB_Some_global_values.h"
#endif

/**
    \class TEB_Numbers
    \brief This class contains various methods for handling integers.
*/
class TEB_Numbers {

  public:

    /**
        \param [in] from Initial delimiter of the string to analyze.
        \param [in] to Final delimiter of the string to analyze.
        \return true if the string delimited by from (included) - to (excluded) contains only digits.
    */
    static bool isInt (const char* from, const char* to);

    /**
        \param [in] str Must end with \0.
        \return true if str contains only digits.
    */
    static bool isInt (const char* str);

    /**
        \param [in] str String to analyze.
        \param [in] length Length of the string.
        \return true if the string contains only digits.
    */
    static bool isInt (const char* str, size_t length);

    /**
        \param [in] exp The exponent of an elevation to a power of base 10.
        \return 10 raised to exp.
    */
    static uint32_t exp10 (uint8_t exp);

    /**
        \param [in] number The character to be converted.
        \return number converted to an integer if it contains a number from 0 to 9, otherwise -1.
    */
    static int8_t charInt (char number);

    /**
        \param [in] from Initial delimiter (included) of the string to analyze.
        \param [in] to Final delimiter (excluded) of the string to analyze.
        \return The string converted to an integer.
    */
    static uint32_t charInt (const char* from, const char* to);

    /**
        \param [in] str String to convert. Must end with \0.
        \return str converted to an integer.
    */
    static uint32_t charInt (const char* str);

    /**
        \param [in] str String to convert. Must end with \0.
        \param [in] length String length.
        \return str converted to an integer.
    */static uint32_t charInt (const char* str, size_t length);

#ifdef TEB_DB_DEBUG
    static void test ();
#endif

};

#endif