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
    This is the official library of Tiny Electronig Blog. Is designed to simplify the management of development boards and add new features, such as:\n - partial support to OAuth 2.0 (https://developers.google.com/identity/protocols/oauth2) and Google Drive API (https://developers.google.com/drive/api/v3/reference);\n - basic time management with timezone and DST;\n - an alternative method to manage large arrays;\n and more. It not support all features of a development board; for example, there are currently no methods to control the bluetooth of an ESP32. For the moment, only the ESP32 development board is compatible.\n Not all functions include error checking and not all types of bugs are handled; the instructions and methods for managing errors are present only when debugging is active, in order to lighten the source code when debugging is disabled.\n Almost all classes that depend on libraries specific to a particular development board are contained in the development_board folder, making it easier to support a new board.\n The library was not written aiming at maximum efficiency but to try to offer a good compromise between stability, efficiency and ease of editing, in order to simplify any future code changes.\n This documentation is not exhaustively written, however there are test functions in all classes which also serve as examples.\n The TEB_Library.h file contains various #defines that you can customize to suit your needs.\n THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef TEB_Library_h
#define TEB_Library_h



//SELECT DEBUG MODE
#define TEB_DB_DEBUG 1 //If uncommented, error handling functions are activated and various useful bug fix information is printed on the debug monitor. TEB_DB_DEBUG can be set to 0, 1 or 2; refer to the documentation of TEB_DevelopmentBoard::TEB_Debug to know what is enabled based on the value of TEB_DB_DEBUG.



//TEB_Splittable_Array CLASS VALUES
#define TEB_Splittable_Array_MAX_SPLIT_ADDRESSES_SX 100 //Maximum number of possible chunks on the left side.
#define TEB_Splittable_Array_MAX_SPLIT_ADDRESSES_DX 100 //Maximum number of possible chunks on the right side.



//TEB_OAuth2 CLASS VALUES
#define TEB_OAuth2_API_KEY ""
#define TEB_OAuth2_CLIENT_ID ""
#define TEB_OAuth2_CLIENT_SECRET ""
#define TEB_OAUTH2_HTTP_REQUEST_CONNECTION_TIMEOUT 5000 //Maximum time in ms to connect to the server.
//The following 3 sizes are those of dynamically allocated buffers used in related functions. If non-dynamic buffers are used, these sizes are the minimum ones.
#define TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_LOGIN 2300
#define TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_RELOGIN 2100
#define TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_LOGOUT 2000
// Root CA of "https://oauth2.googleapis.com"
#define TEB_OAuth2_ROOT_CA "-----BEGIN CERTIFICATE-----\nMIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG\nA1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\nb3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw\nMDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\nYWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT\naWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ\njc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp\nxy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp\n1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG\nsnUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ\nU26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8\n9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E\nBTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B\nAQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz\nyj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE\n38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP\nAbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad\nDKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME\nHMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==\n-----END CERTIFICATE-----\n"



//TEB_Drive CLASS VALUES
//The following 7 sizes are those of dynamically allocated buffers used in related functions. If non-dynamic buffers are used, these sizes are the minimum ones.
#define TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_CREATE_METADATA_ONLY_FILE 2500
#define TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_SEARCH_FILE 10000
#define TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_UPDATE_FILE_METADATA 2500
#define TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_UPDATE_FILE_CONTENT 10000
#define TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_GET_FILE_CONTENT 10000
#define TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_DELETE_FILE 2500
#define TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_EXPORT_GOOGLE_DOC_CONTENT 10000



//TEB_Drive_Remote_Control_Interface CLASS VALUES
//Name of the Google Drive folder containing the workspace folders of the Remote Control Android application
#define TEB_Drive_Remote_Control_Interface_TINY_ELECTRONIC_BLOG_FOLDER_NAME "Tiny Electronic Blog folder"










//DO NOT TOUCH ANYTHING FROM HERE ON////////////////////////////////////////////////////////////
#include "arrays/To_compile.h"
#include "development_board/To_compile.h"
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
      TEB_DevelopmentBoard::test(ssid, password, timeOut);
    }
#endif

};
extern TEB_Library teb;

#endif
