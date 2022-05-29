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

#include "../TEB_External_dependencies.h"
#include "../TEB_Some_global_values.h"
#include "TEB_Debug.h"
#include "TEB_WiFi.h"

int8_t TEB_WiFi::connect (const char* ssid, const char* password, uint32_t timeOut) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_WiFi::connect (const char* ssid, const char* password, uint32_t timeOut)"));
  if (ssid == NULL) TEB_Debug::fatalError(152, F("ssid cannot be NULL."));
  if (password == NULL) TEB_Debug::fatalError(153, F("password cannot be NULL."));
#endif
  timeOut = millis() + timeOut;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() > timeOut) {
#ifdef TEB_DB_DEBUG
      TEB_Debug::error(15, F("Internet connection failed within the maximum time of timeOut ms."));
#endif
      return -1;
    }
  }
#ifdef TEB_DB_DEBUG
  TEB_Debug::print(F("\nSuccessful Internet connection with IP address "));
  TEB_Debug::print(WiFi.localIP()[0]);
  TEB_Debug::print(F("."));
  TEB_Debug::print(WiFi.localIP()[1]);
  TEB_Debug::print(F("."));
  TEB_Debug::print(WiFi.localIP()[2]);
  TEB_Debug::print(F("."));
  TEB_Debug::print(WiFi.localIP()[3]);
  TEB_Debug::print(F(".\n"));
#endif
  return 1;
}

void TEB_WiFi::disconnect () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_WiFi::disconnect ()"));
#endif
  WiFi.disconnect();
#ifdef TEB_DB_DEBUG
  TEB_Debug::print(F("\nThe device has been disconnected from the Internet.\n"));
#endif
}

int8_t TEB_WiFi::check () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_WiFi::check ()"));
#endif
  if (WiFi.status() == WL_CONNECTED) {
#ifdef TEB_DB_DEBUG
    TEB_Debug::print(F("\nThe device is connected to the Internet.\n"));
#endif
    return 1;
  }
  else {
#ifdef TEB_DB_DEBUG
    TEB_Debug::print(F("\nThe device is not connected to the Internet.\n"));
#endif
    return -1;
  }
}

#ifdef TEB_DB_DEBUG
void TEB_WiFi::test (const char* ssid, const char* password, uint32_t timeOut) {
  TEB_Debug tebdb = TEB_Debug(F("TEB_WiFi::test (const char* ssid, const char* password, uint32_t timeOut)"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_Debug::print(F("TEB_WiFi"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  if (check() == -1) connect(ssid, password, timeOut);
  check();
  disconnect();
  TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif