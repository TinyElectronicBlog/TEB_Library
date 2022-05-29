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

#include "TEB_Strings.h"

const char* TEB_Strings::indexOf (const char* str1, const char* to1, const char* str2, const char* to2) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::indexOf (const char* str1, const char* to1, const char* str2, const char* to2)"));
  if (str1 == NULL) TEB_Debug::fatalError(216, F("str1 cannot be NULL."));
  if (str2 == NULL) TEB_Debug::fatalError(217, F("str2 cannot be NULL."));
  if (to1 == NULL) TEB_Debug::fatalError(218, F("to1 cannot be NULL."));
  if (to2 == NULL) TEB_Debug::fatalError(219, F("to1 cannot be NULL."));
  if (to1 <= str1) TEB_Debug::fatalError(220, F("str1 must be < to1."));
  if (to2 <= str2) TEB_Debug::fatalError(221, F("str2 must be < to2."));
#endif
  if (to1 - str1 < to2 - str2) return 0;
  to1 = to1 - (to2 - str2 - 1);
  const char* const str2_b = str2;
  while (str1 < to1) {
    if (*str1 == *str2) {
      str2++;
      if (str2 == to2) return str1 - (str2 - str2_b) + 1;
    }
    else if (str2 != str2_b) {
      str1 = str1 - (str2 - str2_b);
      str2 = str2_b;
    }
    str1++;
  }
  if (str2 != str2_b) {
    do {
      if (*str1 == *str2) {
        str1++;
        str2++;
      }
      else break;
    } while (str2 < to2);
    if (str2 == to2) return str1 - (str2 - str2_b) ;
  }
  return 0;
}

const char* TEB_Strings::indexOf (const char* str1, const char* to1, const char* str2) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::indexOf (const char* str1, const char* to1, const char* str2)"));
  if (str1 == NULL) TEB_Debug::fatalError(222, F("str1 cannot be NULL."));
  if (str2 == NULL) TEB_Debug::fatalError(223, F("str2 cannot be NULL."));
  if (to1 == NULL) TEB_Debug::fatalError(224, F("to1 cannot be NULL."));
  if (to1 <= str1) TEB_Debug::fatalError(225, F("str1 must be < to1."));
#endif
  return indexOf(str1, to1, str2, str2 + strlen(str2));
}

const char* TEB_Strings::indexOf (const char* str1, const char* str2) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::indexOf (const char* str1, const char* str2)"));
  if (str1 == NULL) TEB_Debug::fatalError(226, F("str1 cannot be NULL."));
  if (str2 == NULL) TEB_Debug::fatalError(227, F("str2 cannot be NULL."));
#endif
  return indexOf(str1, str1 + strlen(str1), str2, str2 + strlen(str2));
}

const char* TEB_Strings::lastIndexOf (const char* str1, const char* to1, const char* str2, const char* to2) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::lastIndexOf (const char* str1, const char* to1, const char* str2, const char* to2)"));
  if (str1 == NULL) TEB_Debug::fatalError(228, F("str1 cannot be NULL."));
  if (str2 == NULL) TEB_Debug::fatalError(229, F("str2 cannot be NULL."));
  if (to1 == NULL) TEB_Debug::fatalError(230, F("to1 cannot be NULL."));
  if (to2 == NULL) TEB_Debug::fatalError(231, F("to2 cannot be NULL."));
  if (to1 <= str1) TEB_Debug::fatalError(232, F("str1 must be < to1."));
  if (to2 <= str2) TEB_Debug::fatalError(233, F("str2 must be < to2."));
#endif
  if (to1 - str1 < to2 - str2) return 0;
  to1--;
  to2--;
  str1 = str1 + (to2 - str2) - 1;
  const char* const str2_e = to2;
  while (str1 < to1) {
    if (*to1 == *to2) {
      to2--;
      if (str2 > to2) return to1;
    }
    else if (to2 != str2_e) {
      to1 = to1 + (str2_e - to2) - 1;
      to2 = str2_e;
    }
    to1--;
  }
  if (to2 != str2_e) {
    do {
      if (*to1 == *to2) {
        to1--;
        to2--;
      }
      else break;
    } while (str2 <= to2);
    if (str2 > to2) return to1 + 1;
  }
  return 0;
}

const char* TEB_Strings::lastIndexOf (const char* str1, const char* to1, const char* str2) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::lastIndexOf (const char* str1, const char* to1, const char* str2)"));
  if (str1 == NULL) TEB_Debug::fatalError(234, F("str1 cannot be NULL."));
  if (str2 == NULL) TEB_Debug::fatalError(235, F("str2 cannot be NULL."));
  if (to1 == NULL) TEB_Debug::fatalError(236, F("to1 cannot be NULL."));
  if (to1 <= str1) TEB_Debug::fatalError(237, F("str1 must be < to1."));
#endif
  return lastIndexOf(str1, to1, str2, str2 + strlen(str2));
}

const char* TEB_Strings::lastIndexOf (const char* str1, const char* str2) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::lastIndexOf (const char* str1, const char* str2)"));
  if (str1 == NULL) TEB_Debug::fatalError(238, F("str1 cannot be NULL."));
  if (str2 == NULL) TEB_Debug::fatalError(239, F("str2 cannot be NULL."));
#endif
  return lastIndexOf(str1, str1 + strlen(str1), str2, str2 + strlen(str2));
}

char* TEB_Strings::append (char* destination, const char* source, const char* to) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::append (char* destination, const char* source, const char* to)"));
  if (destination == NULL) TEB_Debug::fatalError(240, F("destination cannot be NULL."));
  if (source == NULL) TEB_Debug::fatalError(241, F("source cannot be NULL."));
  if (to == NULL) TEB_Debug::fatalError(242, F("to cannot be NULL."));
  if (to <= source) TEB_Debug::fatalError(51, F("source must be < to."));
#endif
  while (source < to) {
    *destination = *source;
    destination++;
    source++;
  }
  *destination = '\0';
  return destination;
}

char* TEB_Strings::append (char* destination, const char* source) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::append (char* destination, const char* source)"));
  if (destination == NULL) TEB_Debug::fatalError(244, F("destination cannot be NULL."));
  if (source == NULL) TEB_Debug::fatalError(245, F("source cannot be NULL."));
#endif
  return append(destination, source, source + strlen(source));
}

char* TEB_Strings::append_P (char* destination, const char* source) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::append_P (char* destination, const char* source)"));
  if (destination == NULL) TEB_Debug::fatalError(246, F("destination cannot be NULL."));
  if (source == NULL) TEB_Debug::fatalError(247, F("source cannot be NULL."));
#endif
  return strcpy_P(destination, source) + strlen_P(source);
}

char* TEB_Strings::append_P (char* destination, const char* source, size_t sourceLength) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::append_P (char* destination, const char* source, size_t sourceLength)"));
  if (destination == NULL) TEB_Debug::fatalError(248, F("destination cannot be NULL."));
  if (source == NULL) TEB_Debug::fatalError(249, F("source cannot be NULL."));
  if (sourceLength == 0) TEB_Debug::fatalError(250, F("sourceLength cannot be 0."));
#endif
  char* r = strncpy_P(destination, source, sourceLength) + sourceLength - 1;
  *r = '\0';
  return r;
}

char TEB_Strings::intChar (uint8_t n) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::intChar (uint8_t n)"));
#endif
  switch (n) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
  }
#ifdef TEB_DB_DEBUG
  TEB_Debug::fatalError(251, F("n must be >= 0 and <= 9."));
#endif
  return 0;
}

char* TEB_Strings::intChar (uint32_t n, char* buffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::intChar (uint32_t n, char* buffer)"));
  if (buffer == NULL) TEB_Debug::fatalError(252, F("buffer cannot be NULL."));
#endif
  if (n == 0) {
    *buffer = '0';
    buffer++;
    *buffer = '\0';
    return buffer;
  }
  uint8_t l = log10(n) + 1;
  buffer = buffer + l;
  *buffer = '\0';
  buffer--;
  while (n >= 10) {
    *buffer = intChar(n % 10);
    n = n / 10;
    buffer--;
  }
  *buffer = intChar(n % 10);
  return buffer + l;
}

char* TEB_Strings::invIntChar (uint32_t n, char* buffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::invIntChar (uint32_t n, char* buffer)"));
  if (buffer == NULL) TEB_Debug::fatalError(253, F("buffer cannot be NULL."));
#endif
  while (n >= 10) {
    *buffer = intChar(n % 10);
    n = n / 10;
    buffer++;
  }
  *buffer = intChar(n);
  buffer++;
  *buffer = '\0';
  return buffer;
}

uint8_t TEB_Strings::percentEncoding (char c) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::percentEncoding (char c)"));
#endif
  switch (c) {
    case ':': return 0x3A;
    case '/': return 0x2F;
    case '?': return 0x3F;
    case '#': return 0x23;
    case '[': return 0x5B;
    case ']': return 0x5D;
    case '@': return 0x40;
    case '!': return 0x21;
    case '$': return 0x24;
    case '&': return 0x26;
    case '\'': return 0x27;
    case '(': return 0x28;
    case ')': return 0x29;
    case '*': return 0x2A;
    case '+': return 0x2B;
    case ',': return 0x2C;
    case ';': return 0x3B;
    case '=': return 0x3D;
    case '%': return 0x25;
    case ' ': return 0x20;
  }
  return 0;
}

char* TEB_Strings::percentEncoding (char* destination, const char* source, const char* to) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::percentEncoding (char* destination, const char* source, const char* to)"));
  if (destination == NULL) TEB_Debug::fatalError(254, F("destination cannot be NULL."));
  if (source == NULL) TEB_Debug::fatalError(255, F("source cannot be NULL."));
  if (to == NULL) TEB_Debug::fatalError(256, F("to cannot be NULL."));
  if (to <= source) TEB_Debug::fatalError(52, F("source must be < to."));
#endif
  uint8_t c;
  while (source < to) {
    c = percentEncoding(*source);
    if (c != 0) {
      *destination = '%';  destination++;
      switch (c) {
        case ':': *destination = '3'; destination++; *destination = 'A'; break;
        case '/': *destination = '2'; destination++; *destination = 'F'; break;
        case '?': *destination = '3'; destination++; *destination = 'F'; break;
        case '#': *destination = '2'; destination++; *destination = '3'; break;
        case '[': *destination = '5'; destination++; *destination = 'B'; break;
        case ']': *destination = '5'; destination++; *destination = 'D'; break;
        case '@': *destination = '4'; destination++; *destination = '0'; break;
        case '!': *destination = '2'; destination++; *destination = '1'; break;
        case '$': *destination = '2'; destination++; *destination = '4'; break;
        case '&': *destination = '2'; destination++; *destination = '6'; break;
        case '\'': *destination = '2'; destination++; *destination = '7'; break;
        case '(': *destination = '2'; destination++; *destination = '8'; break;
        case ')': *destination = '2'; destination++; *destination = '9'; break;
        case '*': *destination = '2'; destination++; *destination = 'A'; break;
        case '+': *destination = '2'; destination++; *destination = 'B'; break;
        case ',': *destination = '2'; destination++; *destination = 'C'; break;
        case ';': *destination = '3'; destination++; *destination = 'B'; break;
        case '=': *destination = '3'; destination++; *destination = 'D'; break;
        case '%': *destination = '2'; destination++; *destination = '5'; break;
        case ' ': *destination = '2'; destination++; *destination = '0'; break;
      }
    }
    else {
      *destination = *source;
    }
    destination++;
    source++;
  }
  *destination = '\0';
  return destination;
}

char* TEB_Strings::percentEncoding (char* destination, const char* source) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::percentEncoding (char* destination, const char* source)"));
#endif
  return percentEncoding(destination, source, source + strlen(source));
}

#ifdef TEB_DB_DEBUG
const char TEB_Strings_s[] PROGMEM = "Hello!123\n";
void TEB_Strings::test () {
  TEB_Debug tebdb = TEB_Debug(F("TEB_Strings::test ()"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_Debug::print(F("TEB_Strings"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  TEB_Debug::print(F("\n"));
  char b[20];
  const char* p = append(b, "Hello!123\n") - strlen("Hello!123\n"); TEB_Debug::print(p); TEB_Debug::print(F("\n"));
  p = indexOf(append(b, "Hello!123\n") - strlen("Hello!123\n"), "o"); + '\n'; TEB_Debug::print(p); TEB_Debug::print(F("\n"));
  p = lastIndexOf(append_P(b, TEB_Strings_s) - strlen_P(TEB_Strings_s), "1"); TEB_Debug::print(p); TEB_Debug::print(F("\n"));
  p = intChar(123456, b) - 6; TEB_Debug::print(p); TEB_Debug::print(F("\n\n"));
  p = invIntChar(123456, b) - 6; TEB_Debug::print(p); TEB_Debug::print(F("\n"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif