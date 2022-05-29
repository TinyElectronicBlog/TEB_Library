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

#ifndef TEB_WIFI_h
#define TEB_WIFI_h

#include "../TEB_Configurations.h"
#include <Arduino.h>

/**
    \class TEB_WiFi
    \brief Class designed to manage the Internet connection via WiFi.
*/
class TEB_WiFi {

  public:

    /**
          \brief Connects to a WiFi network.
          \param [in] ssid     Name of WiFi network.
          \param [in] password Password of WiFi network.
          \param [in] timeOut Maximum time in ms to make the connection.
          \return 1 if the Internet connection succeeds within timeOut ms.
    */
    static int8_t connect (const char* ssid, const char* password, uint32_t timeOut);

    /**
          \brief Disconnect from the Internet.
    */
    static void disconnect ();

    /**
          \return 1 if the device is connected to the Internet, otherwise -1.
    */
    static int8_t check ();

#ifdef TEB_DB_DEBUG
    static void test (const char* ssid, const char* password, uint32_t timeOut);
#endif

};

#endif