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

#ifndef TEB_Some_global_values_h
#define TEB_Some_global_values_h

//This file contains some global values.

#include <Arduino.h>

const char TEB_Library_global_string_for_debugging1[] PROGMEM = "\nStart of the ";
const char TEB_Library_global_string_for_debugging2[] PROGMEM = " class test.\n";
const char TEB_Library_global_string_for_debugging3[] PROGMEM = "\n\nEnd of the test :D\n";

const char TEB_Library_global_string_debug1[] PROGMEM = "text cannot be NULL.";
const char TEB_Library_global_string_debug2[] PROGMEM = "\n\n**********\nERROR ";
const char TEB_Library_global_string_debug3[] PROGMEM = ":\n";
const char TEB_Library_global_string_debug4[] PROGMEM = "\n----------";
const char TEB_Library_global_string_debug5[] PROGMEM = "\n\nFATAL ERROR ";
const char TEB_Library_global_string_debug6[] PROGMEM = "\n\nPROGRAM EXECUTION IS NOW INTERRUPTED. FIX YOUR CODE AND RUN IT AGAIN!";

#endif