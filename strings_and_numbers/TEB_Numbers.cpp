/*
  MIT License

  Copyright (c) 2021 TinyElectronicBlog

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

#include "TEB_Numbers.h"

bool TEB_Numbers::isInt (const char* from, const char* to) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Numbers::isInt (const char* from, const char* to)"));
  if (from == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(203, F("from cannot be NULL."));
  if (to == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(204, F("to cannot be NULL."));
  if (from >= to) TEB_DevelopmentBoard::TEB_Debug::fatalError(205, F("from must be < to."));
#endif
  while (from < to) {
    if (charInt(*from) == -1) return false;
    from++;
  }
  return true;
}

bool TEB_Numbers::isInt (const char* str) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Numbers::isInt (const char* str)"));
  if (str == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(206, F("str cannot be NULL."));
#endif
  return isInt(str, str + strlen(str));
}

bool TEB_Numbers::isInt (const char* str, size_t length) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Numbers::isInt (const char* str, size_t length)"));
  if (str == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(207, F("str cannot be NULL."));
  if (length == 0) TEB_DevelopmentBoard::TEB_Debug::fatalError(208, F("length cannot be 0."));
#endif
  return isInt(str, str + length);
}

uint32_t TEB_Numbers::exp10 (uint8_t arg) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Numbers::exp10 (uint8_t arg)"));
#endif
  if (arg == 0) return 1;
  uint32_t r = 10;
  uint8_t t = 1;
  while (t < arg) {
    r = r * 10;
    t++;
  }
  return r;
}

int8_t TEB_Numbers::charInt (char number) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Numbers::charInt (char number)"));
#endif
  switch (number) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
  }
  return -1;
}

uint32_t TEB_Numbers::charInt (const char* from, const char* to) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Numbers::charInt (const char* from, const char* to)"));
  if (from == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(210, F("from cannot be NULL."));
  if (to == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(211, F("to cannot be NULL."));
  if (from >= to) TEB_DevelopmentBoard::TEB_Debug::fatalError(212, F("from must be < to."));
#endif
  uint32_t r = 0;
  to--;
  while (from <= to) {
    r = r + TEB_Numbers::charInt(*from) * exp10(to - from);
    from++;
  }
  return r;
}

uint32_t TEB_Numbers::charInt (const char* str) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Numbers::charInt (const char* str)"));
  if (str == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(213, F("str cannot be NULL."));
#endif
  return charInt(str, str + strlen(str));
}

uint32_t TEB_Numbers::charInt (const char* str, size_t length) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Numbers::charInt (const char* str, size_t length)"));
  if (str == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(214, F("str cannot be NULL."));
  if (length == 0) TEB_DevelopmentBoard::TEB_Debug::fatalError(215, F("length cannot be 0."));
#endif
  return charInt(str, str + length);
}

#ifdef TEB_DB_DEBUG
void TEB_Numbers::test () {
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Numbers::test ()"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_DevelopmentBoard::TEB_Debug::print(F("TEB_Numbers"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
  char* s1 = "1234";
  if (isInt(s1, s1 + 4)) TEB_DevelopmentBoard::TEB_Debug::print(F("Is true\n\n")); else TEB_DevelopmentBoard::TEB_Debug::print(F("Is false\n\n"));
  if (isInt(s1)) TEB_DevelopmentBoard::TEB_Debug::print(F("Is true\n\n")); else TEB_DevelopmentBoard::TEB_Debug::print(F("Is false\n\n"));
  if (isInt(s1, 4)) TEB_DevelopmentBoard::TEB_Debug::print(F("Is true\n\n")); else TEB_DevelopmentBoard::TEB_Debug::print(F("Is false\n\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(exp10(3)); TEB_DevelopmentBoard::TEB_Debug::print(F("\n\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(charInt(s1, s1 + 4)); TEB_DevelopmentBoard::TEB_Debug::print(F("\n\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(charInt(s1)); TEB_DevelopmentBoard::TEB_Debug::print(F("\n\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(charInt(s1, 4)); TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif