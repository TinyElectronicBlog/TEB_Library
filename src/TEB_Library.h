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

/**
    \mainpage Tiny Electronic Blog Library
    This is the official library of Tiny Electronig Blog. Is designed to simplify the management of development boards and add new features, such as:\n - partial support to OAuth 2.0 (https://developers.google.com/identity/protocols/oauth2) and Google Drive API (https://developers.google.com/drive/api/v3/reference);\n - basic time management with timezone and DST;\n - an alternative method to manage large arrays;\n and more. It not support all features of a development board; for example, there are currently no methods to control the bluetooth of an ESP32. For the moment, only the ESP32 development board is compatible.\n Not all functions include error checking and not all types of bugs are handled; the instructions and methods for managing errors are present only when debugging is active, in order to lighten the source code when debugging is disabled.\n Almost all external dependencies are contained in the file "TEB_External_dependencies.h", making it easier to support a new board.\n The library was not written aiming at maximum efficiency but to try to offer a good compromise between stability, efficiency and ease of editing, in order to simplify any future code changes.\n This documentation is not exhaustively written, however there are test functions in all classes which also serve as examples.\n The TEB_Library.h file contains various #defines that you can customize to suit your needs.\n THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef TEB_Library_h
#define TEB_Library_h

#include "TEB_Configurations.h"
#include "development_board/TEB_DevelopmentBoard.h"
#include "google/To_compile.h"
#include "strings_and_numbers/To_compile.h"
#include "time_management/To_compile.h"

/**
    \class TEB_Library
    \brief The TEB_Library class acts as a link for all the others classes in the library. It also includes a test function (when debugging is active) for all methods in the library.
*/
class TEB_Library {

  public:

    static TEB_DevelopmentBoard db;
    static TEB_Drive gdrive;
    static TEB_Drive_Remote_Control_Interface rcinterface;
    static TEB_Numbers numbers;
    static TEB_OAuth2 oauth2;
    static TEB_Strings strings;
    static TEB_Time time;

#ifdef TEB_DB_DEBUG
    static void test (const char* ssid, const char* password, uint32_t timeOut) {
      TEB_Time::test();
      TEB_Strings::test();
      TEB_Numbers::test();
      TEB_Abstract_Array::test();
      TEB_Splittable_Array::test();
      TEB_OAuth2::test(ssid, password, timeOut);
      TEB_Drive::test(ssid, password, timeOut);
      TEB_Drive_Remote_Control_Interface::test(ssid, password, timeOut);
      TEB_DevelopmentBoard::test(ssid, password, timeOut);
    }
#endif

};
extern TEB_Library teb;

#endif