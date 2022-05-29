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

#ifndef TEB_DevelopmentBoard_h
#define TEB_DevelopmentBoard_h

#include "../TEB_Configurations.h"
#include <Arduino.h>
#ifdef TEB_DB_DEBUG
#include "TEB_Debug.h"
#endif
#include "TEB_Display.h"
#include "TEB_EEPROM.h"
#include "TEB_HTTP.h"
#include "TEB_WiFi.h"
#include "TEB_Led.h"
#include "TEB_Clock.h"

/**
    \class TEB_DevelopmentBoard
    \brief This class contains most of the methods that require the specific libraries of the development board used. Thus, to change the latter it is sufficient to readjust TEB_DevelopmentBoard and little other code to the new development board.
*/
class TEB_DevelopmentBoard  {

  public:

#ifdef TEB_DB_DEBUG
    static TEB_Debug debug;
#endif

    static TEB_Display display;
    static TEB_EEPROM eeprom;
    static TEB_HTTP http;
    static TEB_WiFi wifi;
    static TEB_Led led;
    static TEB_Clock clock;


    /**
          \brief Reboot the development board.
    */
    static void reset();

#ifdef TEB_DB_DEBUG
    static void test (const char* ssid, const char* password, uint32_t timeOut);
#endif

};

#endif