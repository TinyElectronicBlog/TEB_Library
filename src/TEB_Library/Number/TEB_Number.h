/*
  MIT License

  Copyright (c) 2024 TinyElectronicBlog

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

#ifndef TEB_Number_h
#define TEB_Number_h

#include "../../TEB_LibrarySettings.h"
#include "../DeviceInterfaces/TEB_DeviceInterfaces.h"

/**
    \brief This class contains various methods for handling integers.
*/

/**
        \param [in] number An integer.
        \return The number of digits of which the number is composed.
    */
TEB_big_u_int TEB_Number_number_of_digits (TEB_big_u_int number);

/**
        \param [in] str Must end with \0.
        \return 1 if str contains only digits.
    */
TEB_bool TEB_Number_is_int (const TEB_char* str);

/**
        \param [in] from Initial delimiter of the string to analyze.
        \param [in] to Final delimiter of the string to analyze.
        \return 1 if the string delimited by from (included) - to (excluded) contains only digits.
    */
TEB_bool TEB_Number_is_int2 (const TEB_char* from, const TEB_char* to);

/**
         \brief Returns a power of 10.
        \param [in] exp Exponent of the power with base 10.
        \return Returns 10 raised to exp.
    */
TEB_big_u_int TEB_Number_exp10 (TEB_small_u_int exp);

/**
        \param [in] number The character to be converted.
        \return number converted to an integer if it contains a number from 0 to 9, otherwise -1.
    */
TEB_small_int TEB_Number_char_digit (TEB_char number);

/**
        \param [in] str String to convert. Must end with \0 and must contain only digits.
        \return str converted to an integer.
    */
TEB_big_u_int TEB_Number_str_int (const TEB_char* str);

/** 
        \param [in] from Initial delimiter (included) of the string (must contain only digits) to analyze. 
        \param [in] to Final delimiter (excluded) of the string (must contain only digits) to analyze.
        \return The string converted to an integer.
    */
TEB_big_u_int TEB_Number_str_int2 (const TEB_char* from, const TEB_char* to);

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_Number_test();
#endif

struct TEB_Number_rename_f {
  TEB_big_u_int (*numberOfDigits)(TEB_big_u_int);
  TEB_bool (*isInt)(const TEB_char*);
  TEB_bool (*isInt2)(const TEB_char*, const TEB_char*);
  TEB_big_u_int (*exp10)(TEB_small_u_int);
  TEB_small_int (*charDigit)(TEB_char);
  TEB_big_u_int (*strInt)(const TEB_char*);
  TEB_big_u_int (*strInt2)(const TEB_char*, const TEB_char*);
};

#endif