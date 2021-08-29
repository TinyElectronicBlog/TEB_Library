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

#include "TEB_DevelopmentBoard.h"
#ifdef TEB_DB_DEBUG

const char TEB_DevelopmentBoard_TEB_Debug_debug1[] PROGMEM = "text cannot be NULL.";
const char TEB_DevelopmentBoard_TEB_Debug_debug2[] PROGMEM = "\n\n**********\nERROR ";
const char TEB_DevelopmentBoard_TEB_Debug_debug3[] PROGMEM = ":\n";
const char TEB_DevelopmentBoard_TEB_Debug_debug4[] PROGMEM = "\n----------";
const char TEB_DevelopmentBoard_TEB_Debug_debug5[] PROGMEM = "\n\nFATAL ERROR ";
const char TEB_DevelopmentBoard_TEB_Debug_debug6[] PROGMEM = "\n\nPROGRAM EXECUTION IS NOW INTERRUPTED. FIX YOUR CODE AND RUN IT AGAIN!";

bool TEB_DevelopmentBoard_TEB_Debug_debug_not_initialized = true;

uint16_t TEB_DevelopmentBoard_TEB_Debug_debug_level = 0;

void TEB_DevelopmentBoard_TEB_Debug_alert () {
  if (sizeof(char) != sizeof(uint8_t)) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(127, F("This library is developed for platforms where sizeof(char) is equal to sizeof(uint8_t.)"));
  }
}

void TEB_DevelopmentBoard_TEB_Debug_debug_initialize () {
  if (TEB_DevelopmentBoard_TEB_Debug_debug_not_initialized) {
    Serial.begin(115200);
    delay(300);
    TEB_DevelopmentBoard_TEB_Debug_debug_not_initialized = false;
    TEB_DevelopmentBoard_TEB_Debug_alert();
  }
}

void TEB_DevelopmentBoard_TEB_Debug_fatal_error_for_debug (size_t number, const __FlashStringHelper* text) {
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug5);
  Serial.print(number);
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug3);
  Serial.print(text);
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug6);
}

TEB_DevelopmentBoard::TEB_Debug::TEB_Debug (const char* text) {
#if TEB_DB_DEBUG == 2 || TEB_DB_DEBUG == 0
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  for (uint8_t i = 0; i < TEB_DevelopmentBoard_TEB_Debug_debug_level; i++) Serial.print('\t');
  Serial.print('L');
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug_level);
  Serial.print(" - Executing ");
  Serial.print(text);
  Serial.print(".\n\n");
  TEB_DevelopmentBoard_TEB_Debug_debug_level++;
#endif
}

TEB_DevelopmentBoard::TEB_Debug::TEB_Debug (const __FlashStringHelper* text) {
#if TEB_DB_DEBUG == 2 || TEB_DB_DEBUG == 0
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  for (uint8_t i = 0; i < TEB_DevelopmentBoard_TEB_Debug_debug_level; i++) Serial.print('\t');
  Serial.print('L');
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug_level);
  Serial.print(" - Executing ");
  Serial.print(text);
  Serial.print(".\n\n");
  TEB_DevelopmentBoard_TEB_Debug_debug_level++;
#endif
}

TEB_DevelopmentBoard::TEB_Debug::~TEB_Debug () {
#if TEB_DB_DEBUG == 2 || TEB_DB_DEBUG == 0
  TEB_DevelopmentBoard_TEB_Debug_debug_level--;
  for (uint8_t i = 0; i < TEB_DevelopmentBoard_TEB_Debug_debug_level; i++) Serial.print('\t');
  Serial.print('L');
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug_level);
  Serial.print(" - End.\n\n");
#endif
}

void TEB_DevelopmentBoard::TEB_Debug::print (const char c) {
#if TEB_DB_DEBUG == 1 || TEB_DB_DEBUG == 0
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  Serial.print(c);
#endif
}

void TEB_DevelopmentBoard::TEB_Debug::print (uint32_t number) {
#if TEB_DB_DEBUG == 1 || TEB_DB_DEBUG == 0
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  Serial.print(number);
#endif
}

void TEB_DevelopmentBoard::TEB_Debug::print (int32_t number) {
#if TEB_DB_DEBUG == 1 || TEB_DB_DEBUG == 0
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  Serial.print(number);
#endif
}

void TEB_DevelopmentBoard::TEB_Debug::print (const char* text) {
#if TEB_DB_DEBUG == 1 || TEB_DB_DEBUG == 0
  if (text == NULL) fatalError(128, TEB_DevelopmentBoard_TEB_Debug_debug1);
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  Serial.print(text);
#endif
}

void TEB_DevelopmentBoard::TEB_Debug::print (const __FlashStringHelper* text) {
#if TEB_DB_DEBUG == 1 || TEB_DB_DEBUG == 0
  if (text == NULL) fatalError(129, TEB_DevelopmentBoard_TEB_Debug_debug1);
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  Serial.print(text);
#endif
}

void TEB_DevelopmentBoard::TEB_Debug::error (size_t number, const char* text) {
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug2);
  Serial.print(number);
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug3);
  Serial.print(text);
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug4);
}

void TEB_DevelopmentBoard::TEB_Debug::error (size_t number, const __FlashStringHelper* text) {
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug2);
  Serial.print(number);
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug3);
  Serial.print(text);
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug4);
}

void TEB_DevelopmentBoard::TEB_Debug::fatalError (size_t number, const char* text) {
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug5);
  Serial.print(number);
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug3);
  Serial.print(text);
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug6);
  while (true) delay(3000);
}

void TEB_DevelopmentBoard::TEB_Debug::fatalError (size_t number, const __FlashStringHelper* text) {
  TEB_DevelopmentBoard_TEB_Debug_debug_initialize();
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug5);
  Serial.print(number);
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug3);
  Serial.print(text);
  Serial.print(TEB_DevelopmentBoard_TEB_Debug_debug6);
  while (true) delay(3000);
}

size_t TEB_DevelopmentBoard::TEB_Debug::totalFreeHeap () {
  return heap_caps_get_free_size(MALLOC_CAP_8BIT);
}

size_t TEB_DevelopmentBoard::TEB_Debug::largestHeapFreeBlock () {
  return heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
}

void TEB_DevelopmentBoard::TEB_Debug::test () {
  print("\nStart of");
  print(F(" the TEB_DevelopmentBoard:TEB_Debug"));
  print(TEB_Library_global_string_for_debugging2);
  error(4, "This is an error!");
  error(5, F("This is another error!"));
  print(F("\n\nThere are "));
  print(totalFreeHeap());
  print(F(" bytes of free heap."));
  print(F("\nThe largest free block in the heap is "));
  print(largestHeapFreeBlock());
  print(F(" bytes long."));
  TEB_DevelopmentBoard_TEB_Debug_fatal_error_for_debug(3, F("This is a fatal error which does not block the execution of the program!"));
  print(TEB_Library_global_string_for_debugging3);
}

#endif