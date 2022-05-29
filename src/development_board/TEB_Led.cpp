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

static bool TEB_Led_led_not_initialized = true;

static void TEB_Led_led_initialize () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Led_led_initialize ()"));
#endif
  if (TEB_Led_led_not_initialized) {
    pinMode(LED_BUILTIN, OUTPUT);
    delay(20);
    TEB_Led_led_not_initialized = false;
  }
}

void TEB_Led::on () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Led::on ()"));
#endif
  TEB_Led_led_initialize();
  digitalWrite(LED_BUILTIN, HIGH);
}

void TEB_Led::off () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Led::off ()"));
#endif
  TEB_Led_led_initialize();
  digitalWrite(LED_BUILTIN, LOW);
}

void TEB_Led::blink (uint16_t onMS, uint16_t offMS) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Led::blink (uint16_t onMS, uint16_t offMS)"));
#endif
  on();
  delay(onMS);
  off();
  delay(offMS);
}

#ifdef TEB_DB_DEBUG
void TEB_Led::test () {
  TEB_Debug tebdb = TEB_Debug(F("TEB_Led::test ()"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_Debug::print(F("TEB_Led"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  for (uint8_t i = 0; i < 6; i++) blink(50, 50);
  for (uint8_t i = 0; i < 6; i++) blink(100, 100);
  for (uint8_t i = 0; i < 4; i++) blink(250, 250);
  TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif