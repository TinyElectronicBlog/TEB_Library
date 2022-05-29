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

#include "../TEB_Some_global_values.h"
#include "TEB_DevelopmentBoard.h"

void TEB_DevelopmentBoard::reset () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_DevelopmentBoard::reset ()"));
#endif
  ESP.restart();
}

#ifdef TEB_DB_DEBUG
void TEB_DevelopmentBoard::test (const char* ssid, const char* password, uint32_t timeOut) {
  TEB_Debug tebdb = TEB_Debug(F("TEB_DevelopmentBoard::test (const char* ssid, const char* password, uint32_t timeOut)"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_Debug::print(F("TEB_DevelopmentBoard"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  TEB_Debug::test();
  TEB_Display::test();
  TEB_EEPROM::test();
  TEB_HTTP::test(ssid, password, timeOut);
  TEB_Led::test();
  TEB_Clock::test();
  TEB_WiFi::test(ssid, password, timeOut);
  TEB_Debug::print(F("\nReboot the device in 5...")); delay(1000);
  TEB_Debug::print(F("4...")); delay(1000);
  TEB_Debug::print(F("3...")); delay(1000);
  TEB_Debug::print(F("2...")); delay(1000);
  TEB_Debug::print(F("1...")); delay(1000);
  TEB_Debug::print(F("\nRebooting.\n"));
  reset();
}
#endif