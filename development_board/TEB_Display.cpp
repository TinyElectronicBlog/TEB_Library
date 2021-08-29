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

  OakOLED is a library of netguy204 (https://github.com/netguy204/OakOLED).
*/

#include "TEB_DevelopmentBoard.h"
#include "OakOLED.h"

OakOLED TEB_DevelopmentBoard_TEB_Display_oled;

bool TEB_DevelopmentBoard_TEB_Display_display_not_initialized = true;

void TEB_DevelopmentBoard_TEB_Display_display_initialize () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard_TEB_Display_display_initialize ()"));
#endif
  if (TEB_DevelopmentBoard_TEB_Display_display_not_initialized) {
    TEB_DevelopmentBoard_TEB_Display_oled.begin();
    delay(50);
    TEB_DevelopmentBoard_TEB_Display_display_not_initialized = false;
  }
}

void TEB_DevelopmentBoard_TEB_Display_print_i (uint8_t text_size) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard_TEB_Display_print_i (uint8_t text_size)"));
#endif
  TEB_DevelopmentBoard_TEB_Display_display_initialize();
  TEB_DevelopmentBoard_TEB_Display_oled.clearDisplay();
  TEB_DevelopmentBoard_TEB_Display_oled.setTextSize(text_size);
  TEB_DevelopmentBoard_TEB_Display_oled.setCursor(0, 0);
}

void TEB_DevelopmentBoard::TEB_Display::print (const char* text, uint8_t textSize) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Display::print (const char* text, uint8_t textSize)"));
  if (text == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(130, F("text cannot be NULL."));
  if (textSize == 0) TEB_DevelopmentBoard::TEB_Debug::fatalError(131, F("textSize cannot be 0."));
#endif
  TEB_DevelopmentBoard_TEB_Display_print_i(textSize);
  TEB_DevelopmentBoard_TEB_Display_oled.print(text);
  TEB_DevelopmentBoard_TEB_Display_oled.display();
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nShown on the display \""));
  TEB_DevelopmentBoard::TEB_Debug::print(text);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\".\n"));
#endif
}

void TEB_DevelopmentBoard::TEB_Display::print (const __FlashStringHelper* text, uint8_t textSize) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Display::print (const __FlashStringHelper* text, uint8_t textSize)"));
  if (text == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(132, TEB_DevelopmentBoard_TEB_Debug_debug1);
  if (textSize == 0) TEB_DevelopmentBoard::TEB_Debug::fatalError(133, TEB_DevelopmentBoard_TEB_Debug_debug2);
#endif
  TEB_DevelopmentBoard_TEB_Display_print_i(textSize);
  TEB_DevelopmentBoard_TEB_Display_oled.print(text);
  TEB_DevelopmentBoard_TEB_Display_oled.display();
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nShown on the display \""));
  TEB_DevelopmentBoard::TEB_Debug::print(text);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\".\n"));
#endif
}

#ifdef TEB_DB_DEBUG
void TEB_DevelopmentBoard::TEB_Display::test () {
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Display::test ()"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_DevelopmentBoard::TEB_Debug::print(F("TEB_DevelopmentBoard::TEB_Display"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  print("Test 1", 1);
  delay(2000);
  print(F("Test 2"), 2);
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif