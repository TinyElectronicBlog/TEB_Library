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

#include "TEB_Number.h"
#include "../String/TEB_String.h"
#include "../DeviceInterfaces/TEB_DeviceInterfaces.h"

TEB_big_u_int TEB_Number_number_of_digits (TEB_big_u_int number) {
  TEB_debug_function_start("TEB_Number_number_of_digits");
  TEB_big_u_int r = 1;
  while (number >= 10) {
    number = number / 10;
    r = r + 1;
  }
  TEB_debug_function_end(0);
  return r;
}

TEB_bool TEB_Number_is_int (const TEB_char* str) {
  TEB_debug_function_start("TEB_Number_is_int");
  if (str == TEB_NULL_POINTER) TEB_fatal_error(166, "str cannot be NULL.", 2);
  TEB_bool r = TEB_Number_is_int2(str, str + TEB_String_strlen(str));
  return TEB_debug_function_end(r);
}

TEB_bool TEB_Number_is_int2 (const TEB_char* from, const TEB_char* to) {
  TEB_debug_function_start("TEB_Number_is_int2");
  if (from == TEB_NULL_POINTER) TEB_fatal_error(167, "from cannot be NULL.", 2);
  if (to == TEB_NULL_POINTER) TEB_fatal_error(168, "to cannot be NULL.", 2);
  if (from >= to) TEB_fatal_error(169, "from must be < to.", 2);
  while (from < to) {
    if (TEB_Number_char_digit(*from) == -1) {
      return TEB_debug_function_end(0);
    }
    from = from + 1;
  }
  return TEB_debug_function_end(1);
}

TEB_big_u_int TEB_Number_exp10 (TEB_small_u_int exp) {
  TEB_debug_function_start("TEB_Number_exp10");
  if (exp == 0) {
    TEB_debug_function_end(0);
    return 1;
  }
  TEB_big_u_int r = 10;
  TEB_small_u_int t = 1;
  while (t < exp) {
    r = r * 10;
    t = t + 1;
  }
  TEB_debug_function_end(0);
  return r;
}

TEB_small_int TEB_Number_char_digit (TEB_char number) {
  TEB_debug_function_start("TEB_Number_char_digit");
  switch (number) {
    case '0': return TEB_debug_function_end(0);
    case '1': return TEB_debug_function_end(1);
    case '2': return TEB_debug_function_end(2);
    case '3': return TEB_debug_function_end(3);
    case '4': return TEB_debug_function_end(4);
    case '5': return TEB_debug_function_end(5);
    case '6': return TEB_debug_function_end(6);
    case '7': return TEB_debug_function_end(7);
    case '8': return TEB_debug_function_end(8);
    case '9': return TEB_debug_function_end(9);
  }
  return TEB_debug_function_end(-1);
}

TEB_big_u_int TEB_Number_str_int (const TEB_char* str) {
  TEB_debug_function_start("TEB_Number_str_int");
  if (str == TEB_NULL_POINTER) TEB_fatal_error(170, "str cannot be NULL.", 2);
  TEB_big_u_int r = TEB_Number_str_int2(str, str + TEB_String_strlen(str));
  TEB_debug_function_end(0);
  return r;
}

TEB_big_u_int TEB_Number_str_int2 (const TEB_char* from, const TEB_char* to) {
  TEB_debug_function_start("TEB_Number_str_int2");
  if (from == TEB_NULL_POINTER) TEB_fatal_error(171, "from cannot be NULL.", 2);
  if (to == TEB_NULL_POINTER) TEB_fatal_error(172, "to cannot be NULL.", 2);
  if (from >= to) TEB_fatal_error(173, "from must be < to.", 2);
  TEB_big_u_int r = 0;
  to = to - 1;
  while (from <= to) {
    r = r + TEB_Number_char_digit(*from) * TEB_Number_exp10(to - from);
    from = from + 1;
  }
  TEB_debug_function_end(0);
  return r;
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
static void TEB_Number_function_end(const TEB_char* f_name, TEB_bool ok) {
  if (ok == 0) {
    TEB_debug_print("\n");
    TEB_debug_print(f_name);
    TEB_debug_print(" ko");
  } else {
    TEB_debug_print("\n");
    TEB_debug_print(f_name);
    TEB_debug_print(" ok");
  }
}

TEB_small_int TEB_Number_test () {
  TEB_debug_function_start("TEB_Number_test");

  const TEB_char* s1 = "12345";
  TEB_medium_u_int n1 = 12345;

  if (TEB_Number_char_digit(s1[0]) == 1) TEB_Number_function_end("TEB_Number_char_digit", 1);
  else {
    TEB_Number_function_end("TEB_Number_char_digit", 0);
    return TEB_debug_function_end(-1);
  }

  if (TEB_Number_str_int2(s1, s1 + 5) == n1) TEB_Number_function_end("TEB_Number_str_int2", 1);
  else {
    TEB_Number_function_end("TEB_Number_str_int2", 0);
    return TEB_debug_function_end(-2);
  }

  if (TEB_Number_str_int(s1) == n1) TEB_Number_function_end("TEB_Number_str_int", 1);
  else {
    TEB_Number_function_end("TEB_Number_str_int", 0);
    return TEB_debug_function_end(-3);
  }

  if (TEB_Number_number_of_digits(n1) == 5) TEB_Number_function_end("TEB_Number_number_of_digits", 1);
  else {
    TEB_Number_function_end("TEB_Number_number_of_digits", 0);
    return TEB_debug_function_end(-5);
  }

  if (TEB_Number_exp10(5) == 100000) TEB_Number_function_end("TEB_Number_exp10", 1);
  else {
    TEB_Number_function_end("TEB_Number_exp10", 0);
    return TEB_debug_function_end(-6);
  }

  if (TEB_Number_is_int2(s1, s1 + 5) == 1) TEB_Number_function_end("TEB_Number_is_int2", 1);
  else {
    TEB_Number_function_end("TEB_Number_is_int2", 0);
    return TEB_debug_function_end(-7);
  }

  if (TEB_Number_is_int(s1) == 1) TEB_Number_function_end("TEB_Number_is_int", 1);
  else {
    TEB_Number_function_end("TEB_Number_is_int", 0);
    return TEB_debug_function_end(-4);
  }

  return TEB_debug_function_end(1);
}
#endif