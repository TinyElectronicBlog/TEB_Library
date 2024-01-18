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

#include "TEB_String.h"
#include "../Number/TEB_Number.h"

TEB_size_t TEB_String_strlen (const TEB_char* str) {
  TEB_debug_function_start("TEB_String_strlen");
  if (str == TEB_NULL_POINTER) TEB_fatal_error(174, "str cannot be NULL.", 2);
  TEB_size_t l = 0;
  while (str[l] != TEB_NULL_CHAR) l = l + 1;
  TEB_debug_function_end(0);
  return l;
}

TEB_small_int TEB_String_equals (const TEB_char* str1,
                                const TEB_char* to1,
                                const TEB_char* str2,
                                const TEB_char* to2) {
  TEB_debug_function_start("TEB_String_equals");
  if (str1 == TEB_NULL_POINTER) TEB_fatal_error(175, "str1 cannot be NULL.", 2);
  if (to1 == TEB_NULL_POINTER) TEB_fatal_error(176, "to1 cannot be NULL.", 2);
  if (str2 == TEB_NULL_POINTER) TEB_fatal_error(177, "str2 cannot be NULL.", 2);
  if (to2 == TEB_NULL_POINTER) TEB_fatal_error(178, "to2 cannot be NULL.", 2);
  if (str1 >= to1) TEB_fatal_error(179, "str1 must be < to1.", 2);
  if (str2 >= to2) TEB_fatal_error(180, "str2 must be < to2.", 2);
  if (to1 - str1 != to2 - str2) {return TEB_debug_function_end(0);}
  while (str1 < to1) {
    if (*str1 != *str2) break;
    str1 = str1 + 1;
    str2 = str2 + 1;
  }
  if (str1 == to1) {return TEB_debug_function_end(1);}
  return TEB_debug_function_end(0);
}

TEB_small_int TEB_String_equals2 (const TEB_char* str1,
                                 const TEB_char* str2) {
  TEB_debug_function_start("TEB_String_equals2");
  return TEB_debug_function_end(TEB_String_equals(str1, str1 + TEB_String_strlen(str1), str2, str2 + TEB_String_strlen(str2)));
}

TEB_small_int TEB_String_equals3 (const TEB_char* str1,
                                 const TEB_char* to1,
                                 const TEB_char* str2) {
  TEB_debug_function_start("TEB_String_equals3");
  return TEB_debug_function_end(TEB_String_equals(str1, to1, str2, str2 + TEB_String_strlen(str2)));
}

const TEB_char* TEB_String_index_of (const TEB_char* str1,
                                    const TEB_char* to1,
                                    const TEB_char* str2,
                                    const TEB_char* to2) {
  TEB_debug_function_start("TEB_String_index_of");
  if (str1 == TEB_NULL_POINTER) TEB_fatal_error(181, "str1 cannot be NULL.", 2);
  if (to1 == TEB_NULL_POINTER) TEB_fatal_error(182, "to1 cannot be NULL.", 2);
  if (str2 == TEB_NULL_POINTER) TEB_fatal_error(183, "str2 cannot be NULL.", 2);
  if (to2 == TEB_NULL_POINTER) TEB_fatal_error(184, "to2 cannot be NULL.", 2);
  if (str1 >= to1) TEB_fatal_error(185, "str1 must be < to1.", 2);
  if (str2 >= to2) TEB_fatal_error(186, "str2 must be < to2.", 2);
  if (to1 - str1 < to2 - str2) {
    TEB_debug_function_end(0);
    return TEB_NULL_POINTER;
  }
  to1 = to1 - (to2 - str2 - 1);
  const TEB_char* const str2_b = str2;
  while (str1 < to1) {
    if (*str1 == *str2) {
      str2 = str2 + 1;
      if (str2 == to2) {
        TEB_debug_function_end(0);
        return str1 - (str2 - str2_b) + 1;
      }
    } else if (str2 != str2_b) {
      str1 = str1 - (str2 - str2_b);
      str2 = str2_b;
    }
    str1 = str1 + 1;
  }
  if (str2 != str2_b) {
    do {
      if (*str1 == *str2) {
        str1 = str1 + 1;
        str2 = str2 + 1;
      } else break;
    } while (str2 < to2);
    if (str2 == to2) {
      TEB_debug_function_end(0);
      return str1 - (str2 - str2_b);
    }
  }
  TEB_debug_function_end(0);
  return TEB_NULL_POINTER;
}

const TEB_char* TEB_String_index_of2 (const TEB_char* str1, const TEB_char* str2) {
  TEB_debug_function_start("TEB_String_index_of2");
  const TEB_char* r = TEB_String_index_of(str1, str1 + TEB_String_strlen(str1), str2, str2 + TEB_String_strlen(str2));
  TEB_debug_function_end(0);
  return r;
}

const TEB_char* TEB_String_index_of3 (const TEB_char* str1, const TEB_char* to1, const TEB_char* str2) {
  TEB_debug_function_start("TEB_String_index_of3");
  const TEB_char* r = TEB_String_index_of(str1, to1, str2, str2 + TEB_String_strlen(str2));
  TEB_debug_function_end(0);
  return r;
}

const TEB_char* TEB_String_last_index_of (const TEB_char* str1, 
								          const TEB_char* to1, 
										  const TEB_char* str2, 
										  const TEB_char* to2) {
  TEB_debug_function_start("TEB_String_last_index_of");
  if (str1 == TEB_NULL_POINTER) TEB_fatal_error(187, "str1 cannot be NULL.", 2);
  if (to1 == TEB_NULL_POINTER) TEB_fatal_error(188, "to1 cannot be NULL.", 2);
  if (str2 == TEB_NULL_POINTER) TEB_fatal_error(189, "str2 cannot be NULL.", 2);
  if (to2 == TEB_NULL_POINTER) TEB_fatal_error(190, "to2 cannot be NULL.", 2);
  if (str1 >= to1) TEB_fatal_error(191, "str1 must be < to1.", 2);
  if (str2 >= to2) TEB_fatal_error(192, "str2 must be < to2.", 2);
  if (to1 - str1 < to2 - str2) {
    TEB_debug_function_end(0);
    return TEB_NULL_POINTER;
  }
  to1 = to1 - 1;
  to2 = to2 - 1;
  str1 = str1 + (to2 - str2) - 1;
  const TEB_char* const str2_e = to2;
  while (str1 < to1) {
    if (*to1 == *to2) {
      to2 = to2 - 1;
      if (str2 > to2) {
        TEB_debug_function_end(0);
        return to1;
      }
    } else if (to2 != str2_e) {
      to1 = to1 + (str2_e - to2) - 1;
      to2 = str2_e;
    }
    to1 = to1 - 1;
  }
  if (to2 != str2_e) {
    do {
      if (*to1 == *to2) {
        to1 = to1 - 1;
        to2 = to2 - 1;
      } else break;
    } while (str2 <= to2);
    if (str2 > to2) {
      TEB_debug_function_end(0);
      return to1 + 1;
    }
  }
  TEB_debug_function_end(0);
  return TEB_NULL_POINTER;
}

const TEB_char* TEB_String_last_index_of2 (const TEB_char* str1, const TEB_char* str2) {
  TEB_debug_function_start("TEB_String_last_index_of2");
  const TEB_char* r = TEB_String_last_index_of(str1, str1 + TEB_String_strlen(str1), str2, str2 + TEB_String_strlen(str2));
  TEB_debug_function_end(0);
  return r;
}

const TEB_char* TEB_String_last_index_of3 (const TEB_char* str1,
										   const TEB_char* to1, 
										   const TEB_char* str2) {
  TEB_debug_function_start("TEB_String_last_index_of3");
  const TEB_char* r = TEB_String_last_index_of(str1, to1, str2, str2 + TEB_String_strlen(str2));
  TEB_debug_function_end(0);
  return r;
}

TEB_char* TEB_String_append (TEB_char* destination, const TEB_char* source, const TEB_char* to) {
  TEB_debug_function_start("TEB_String_append");
  if (destination == TEB_NULL_POINTER) TEB_fatal_error(193, "destination cannot be NULL.", 2);
  if (source == TEB_NULL_POINTER) TEB_fatal_error(194, "source cannot be NULL.", 2);
  if (to == TEB_NULL_POINTER) TEB_fatal_error(195, "to cannot be NULL.", 2);
  if (source >= to) TEB_fatal_error(196, "source must be < to.", 2);
  while (source < to) {
    *destination = *source;
    destination =  destination + 1;
    source = source + 1;
  }
  *destination = TEB_NULL_CHAR;
  TEB_debug_function_end(0);
  return destination;
}

TEB_char* TEB_String_append2 (TEB_char* destination, const TEB_char* source) {
  TEB_debug_function_start("TEB_String_append2");
  TEB_char* r = TEB_String_append(destination, source, source + TEB_String_strlen(source));
  TEB_debug_function_end(0);
  return r;
}

TEB_char* TEB_String_append_end (TEB_char* last_element_of_the_destination_buffer,
								 const TEB_char* source,
								 const TEB_char* to, 
								 TEB_bool ends_with_null_character) {
  TEB_debug_function_start("TEB_String_append_end");
  if (last_element_of_the_destination_buffer == TEB_NULL_POINTER) TEB_fatal_error(197, "last_element_of_the_destination_buffer cannot be NULL.", 2);
  if (source == TEB_NULL_POINTER) TEB_fatal_error(198, "source cannot be NULL.", 2);
  if (to == TEB_NULL_POINTER) TEB_fatal_error(199, "to cannot be NULL.", 2);
  if (source >= to) TEB_fatal_error(200, "source must be < to.", 2);
  to = to - 1;
  if (ends_with_null_character != 0) {
    *last_element_of_the_destination_buffer = TEB_NULL_CHAR;
    last_element_of_the_destination_buffer = last_element_of_the_destination_buffer - 1;
  }
  while (source <= to) {
    *last_element_of_the_destination_buffer = *to;
    last_element_of_the_destination_buffer = last_element_of_the_destination_buffer - 1;
    to = to - 1;
  }
  TEB_debug_function_end(0);
  return last_element_of_the_destination_buffer + 1;
}

TEB_char* TEB_String_append_end2 (TEB_char* last_element_of_the_destination_buffer,
							      const TEB_char* source,
								  TEB_bool ends_with_null_character) {
  TEB_debug_function_start("TEB_String_append_end2");
  TEB_char* r = TEB_String_append_end(last_element_of_the_destination_buffer, source, source + TEB_String_strlen(source), ends_with_null_character);
  TEB_debug_function_end(0);
  return r;
}

TEB_char TEB_String_int_char (TEB_small_u_int digit) {
  TEB_debug_function_start("TEB_String_int_char");
  if (digit > 9) TEB_fatal_error(201, "digit must be <= 9.", 2);
  switch (digit) {
    case 0: TEB_debug_function_end(0); return '0';
    case 1: TEB_debug_function_end(0); return '1';
    case 2: TEB_debug_function_end(0); return '2';
    case 3: TEB_debug_function_end(0); return '3';
    case 4: TEB_debug_function_end(0); return '4';
    case 5: TEB_debug_function_end(0); return '5';
    case 6: TEB_debug_function_end(0); return '6';
    case 7: TEB_debug_function_end(0); return '7';
    case 8: TEB_debug_function_end(0); return '8';
    case 9: TEB_debug_function_end(0); return '9';
  }
  TEB_debug_function_end(0);
  return 0;
}

TEB_char* TEB_String_int_str (TEB_big_u_int number, TEB_char* buffer) {
  TEB_debug_function_start("TEB_String_int_str");
  if (buffer == TEB_NULL_POINTER) TEB_fatal_error(202, "buffer cannot be NULL.", 2);
  if (number == 0) {
    *buffer = '0';
    buffer = buffer + 1;
    *buffer = TEB_NULL_CHAR;
    TEB_debug_function_end(0);
    return buffer;
  }
  TEB_size_t l = TEB_Number_number_of_digits(number);
  buffer = buffer + l;
  *buffer = TEB_NULL_CHAR;
  buffer = buffer - 1;
  while (number >= 10) {
    *buffer = TEB_String_int_char(number % 10);
    number = number / 10;
    buffer = buffer - 1;
  }
  *buffer = TEB_String_int_char(number % 10);
  TEB_debug_function_end(0);
  return buffer + l;
}

TEB_char* TEB_String_inv_int_str (TEB_big_u_int number, TEB_char* buffer) {
  TEB_debug_function_start("TEB_String_inv_int_str");
  if (buffer == TEB_NULL_POINTER) TEB_fatal_error(203, "buffer cannot be NULL.", 2);
  while (number >= 10) {
    *buffer = TEB_String_int_char(number % 10);
    number = number / 10;
    buffer = buffer + 1;
  }
  *buffer = TEB_String_int_char(number);
  buffer = buffer + 1;
  *buffer = TEB_NULL_CHAR;
  TEB_debug_function_end(0);
  return buffer;
}

TEB_small_u_int TEB_String_url_encoding_char (TEB_char c) {
  TEB_debug_function_start("TEB_String_url_encoding_char");
  switch (c) {
    case ':': TEB_debug_function_end(0); return 0x3A;
    case '/': TEB_debug_function_end(0); return 0x2F;
    case '?': TEB_debug_function_end(0); return 0x3F;
    case '#': TEB_debug_function_end(0); return 0x23;
    case '[': TEB_debug_function_end(0); return 0x5B;
    case ']': TEB_debug_function_end(0); return 0x5D;
    case '@': TEB_debug_function_end(0); return 0x40;
    case '!': TEB_debug_function_end(0); return 0x21;
    case '$': TEB_debug_function_end(0); return 0x24;
    case '&': TEB_debug_function_end(0); return 0x26;
    case '\'': TEB_debug_function_end(0); return 0x27;
    case '(': TEB_debug_function_end(0); return 0x28;
    case ')': TEB_debug_function_end(0); return 0x29;
    case '*': TEB_debug_function_end(0); return 0x2A;
    case '+': TEB_debug_function_end(0); return 0x2B;
    case ',': TEB_debug_function_end(0); return 0x2C;
    case ';': TEB_debug_function_end(0); return 0x3B;
    case '=': TEB_debug_function_end(0); return 0x3D;
    case '%': TEB_debug_function_end(0); return 0x25;
    case ' ': TEB_debug_function_end(0); return 0x20;
  }
  TEB_debug_function_end(0);
  return 0;
}

TEB_char* TEB_String_url_encoding (TEB_char* destination, const TEB_char* source, const TEB_char* to) {
  TEB_debug_function_start("TEB_String_url_encoding");
  if (destination == TEB_NULL_POINTER) TEB_fatal_error(204, "destination cannot be NULL.", 2);
  if (source == TEB_NULL_POINTER) TEB_fatal_error(205, "source cannot be NULL.", 2);
  if (to == TEB_NULL_POINTER) TEB_fatal_error(206, "to cannot be NULL.", 2);
  if (source >= to) TEB_fatal_error(207, "source must be < to.", 2);
  TEB_small_u_int c;
  while (source < to) {
    c = TEB_String_url_encoding_char(*source);
    if (c != 0) {
      *destination = '%';
      destination = destination + 1;
      switch (c) {
        case ':':
          *destination = '3';
          destination = destination + 1;
          *destination = 'A';
          break;
        case '/':
          *destination = '2';
          destination = destination + 1;
          *destination = 'F';
          break;
        case '?':
          *destination = '3';
          destination = destination + 1;
          *destination = 'F';
          break;
        case '#':
          *destination = '2';
          destination = destination + 1;
          *destination = '3';
          break;
        case '[':
          *destination = '5';
          destination = destination + 1;
          *destination = 'B';
          break;
        case ']':
          *destination = '5';
          destination = destination + 1;
          *destination = 'D';
          break;
        case '@':
          *destination = '4';
          destination = destination + 1;
          *destination = '0';
          break;
        case '!':
          *destination = '2';
          destination = destination + 1;
          *destination = '1';
          break;
        case '$':
          *destination = '2';
          destination = destination + 1;
          *destination = '4';
          break;
        case '&':
          *destination = '2';
          destination = destination + 1;
          *destination = '6';
          break;
        case '\'':
          *destination = '2';
          destination = destination + 1;
          *destination = '7';
          break;
        case '(':
          *destination = '2';
          destination = destination + 1;
          *destination = '8';
          break;
        case ')':
          *destination = '2';
          destination = destination + 1;
          *destination = '9';
          break;
        case '*':
          *destination = '2';
          destination = destination + 1;
          *destination = 'A';
          break;
        case '+':
          *destination = '2';
          destination = destination + 1;
          *destination = 'B';
          break;
        case ',':
          *destination = '2';
          destination = destination + 1;
          *destination = 'C';
          break;
        case ';':
          *destination = '3';
          destination = destination + 1;
          *destination = 'B';
          break;
        case '=':
          *destination = '3';
          destination = destination + 1;
          *destination = 'D';
          break;
        case '%':
          *destination = '2';
          destination = destination + 1;
          *destination = '5';
          break;
        case ' ':
          *destination = '2';
          destination = destination + 1;
          *destination = '0';
          break;
      }
    } else {
      *destination = *source;
    }
    destination = destination + 1;
    source = source + 1;
  }
  *destination = TEB_NULL_CHAR;
  TEB_debug_function_end(0);
  return destination;
}

TEB_char* TEB_String_url_encoding2 (TEB_char* destination, const TEB_char* source) {
  TEB_debug_function_start("TEB_String_url_encoding2");
  TEB_char* r = TEB_String_url_encoding(destination, source, source + TEB_String_strlen(source));
  TEB_debug_function_end(0);
  return r;
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
static void TEB_String_function_end (const TEB_char* f_name, TEB_bool ok) {
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

TEB_small_int TEB_String_test () {
  TEB_debug_function_start("TEB_String_test");
  const TEB_char* s1 = "Hello!123\n";
  if (TEB_String_strlen(s1) == 10) TEB_String_function_end("TEB_String_strlen", 1);
  else {
    TEB_String_function_end("TEB_String_strlen", 0);
    return TEB_debug_function_end(-1);
  }

  if (TEB_String_equals(s1, s1 + 10, s1, s1 + 10) == 1) TEB_String_function_end("TEB_String_equals", 1);
  else {
    TEB_String_function_end("TEB_String_equals", 0);
    return TEB_debug_function_end(-2);
  }

  if (TEB_String_equals2(s1, s1) == 1) TEB_String_function_end("TEB_String_equal2", 1);
  else {
    TEB_String_function_end("TEB_String_equals2", 0);
    return TEB_debug_function_end(-3);
  }

  if (TEB_String_equals3(s1, s1 + 10, s1) == 1) TEB_String_function_end("TEB_String_equals3", 1);
  else {
    TEB_String_function_end("TEB_String_equals3", 0);
    return TEB_debug_function_end(-4);
  }

  if (TEB_String_index_of(s1, s1 + 10, s1 + 3, s1 + 10) - s1 == 3) TEB_String_function_end("TEB_String_index_of", 1);
  else {
    TEB_String_function_end("TEB_String_index_of", 0);
    return TEB_debug_function_end(-5);
  }

  if (TEB_String_index_of2(s1, s1 + 3) - s1 == 3) TEB_String_function_end("TEB_String_index_of2", 1);
  else {
    TEB_String_function_end("TEB_String_index_of2", 0);
    return TEB_debug_function_end(-6);
  }

  if (TEB_String_index_of3(s1, s1 + 10, s1 + 3) - s1 == 3) TEB_String_function_end("TEB_String_index_of3", 1);
  else {
    TEB_String_function_end("TEB_String_index_of3", 0);
    return TEB_debug_function_end(-7);
  }

  if (TEB_String_last_index_of(s1, s1 + 10, s1 + 3, s1 + 10) - s1 == 3) TEB_String_function_end("TEB_String_last_index_of", 1);
  else {
    TEB_String_function_end("TEB_String_last_index_of", 0);
    return TEB_debug_function_end(-8);
  }

  if (TEB_String_last_index_of2(s1, s1 + 3) - s1 == 3) TEB_String_function_end("TEB_String_last_index_of2", 1);
  else {
    TEB_String_function_end("TEB_String_last_index_of2", 0);
    return TEB_debug_function_end(-9);
  }

  if (TEB_String_last_index_of3(s1, s1 + 10, s1 + 3) - s1 == 3) TEB_String_function_end("TEB_String_last_index_of3", 1);
  else {
    TEB_String_function_end("TEB_String_last_index_of3", 0);
    return TEB_debug_function_end(-10);
  }

  TEB_char b1[11], b2[11];
  TEB_String_append(b1, s1, s1 + 10);
  TEB_String_append2(b2, s1);
  if (TEB_String_equals2(b1, b2) == 1 && TEB_String_equals2(b1, s1) == 1) TEB_String_function_end("TEB_String_append and TEB_String_append2", 1);
  else {
    TEB_String_function_end("TEB_String_append and TEB_String_append2", 0);
    return TEB_debug_function_end(-11);
  }

  TEB_char* t1 = (TEB_char*)TEB_String_append_end(b1 + 10, s1, s1 + 10, 1);
  TEB_char* t2 = (TEB_char*)TEB_String_append_end2(b2 + 10, s1, 1);
  if (TEB_String_equals2(t1, t2) == 1 && TEB_String_equals2(t1, s1) == 1) TEB_String_function_end("TEB_String_append_end and TEB_String_append_end2", 1);
  else {
    TEB_String_function_end("TEB_String_append_end and TEB_String_append_end2", 0);
    return TEB_debug_function_end(-18);
  }

  const char c1[] = ":/?#[]@!$&'()*+,;=%";
  char c2[60];
  if (TEB_String_url_encoding_char(' ') == 0x20) TEB_String_function_end("TEB_String_url_encoding_char", 1);
  else {
    TEB_String_function_end("TEB_String_url_encoding_char", 0);
    return TEB_debug_function_end(-12);
  }

  TEB_String_url_encoding(c2, c1, c1 + 19);
  if (TEB_String_equals2(c2, "%3A%2F%3F%23%5B%5D%40%21%24%26%27%28%29%2A%2B%2C%3B%3D%25") == 1) TEB_String_function_end("TEB_String_url_encoding", 1);
  else {
    TEB_String_function_end("TEB_String_url_encoding", 0);
    return TEB_debug_function_end(-13);
  }

  TEB_String_url_encoding2(c2, c1);
  if (TEB_String_equals2(c2, "%3A%2F%3F%23%5B%5D%40%21%24%26%27%28%29%2A%2B%2C%3B%3D%25") == 1) TEB_String_function_end("TEB_String_url_encoding2", 1);
  else {
    TEB_String_function_end("TEB_String_url_encoding2", 0);
    return TEB_debug_function_end(-14);
  }

  if (TEB_String_int_char(1) == '1') TEB_String_function_end("TEB_String_int_char", 1);
  else {
    TEB_String_function_end("TEB_String_int_char", 0);
    return TEB_debug_function_end(-15);
  }

  TEB_String_int_str(8945, c2);
  if (TEB_String_equals2(c2, "8945") == 1) TEB_String_function_end("TEB_String_int_str", 1);
  else {
    TEB_String_function_end("TEB_String_int_str", 0);
    return TEB_debug_function_end(-16);
  }

  TEB_String_inv_int_str(8945, c2);
  if (TEB_String_equals2(c2, "5498") == 1) TEB_String_function_end("TEB_String_inv_int_str", 1);
  else {
    TEB_String_function_end("TEB_String_inv_int_str", 0);
    return TEB_debug_function_end(-17);
  }

  return TEB_debug_function_end(1);
}
#endif