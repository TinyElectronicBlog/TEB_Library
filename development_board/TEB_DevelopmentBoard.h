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

#ifndef TEB_DevelopmentBoard_h
#define TEB_DevelopmentBoard_h

#include "../TEB_Library.h"
#ifdef TEB_DB_DEBUG
#include "../TEB_Some_global_values.h"
#endif

/**
    \class TEB_DevelopmentBoard
    \brief This class contains most of the methods that require the specific libraries of the development board used. Thus, to change the latter it is sufficient to readjust TEB_DevelopmentBoard and little other code to the new development board.
*/
class TEB_DevelopmentBoard  {

  public:

#ifdef TEB_DB_DEBUG
    /**
       \class TEB_Debug
       \brief This class contains methods related to debugging. Debug mode can be selected in the TEB_Library.h file.
    */
    class TEB_Debug {

      public:

        /**
           \brief Constructor used with TEB_DB_DEBUG 2 or 0 mode. Is meant to be inserted at the beginning of each function, in order to keep track of the order in which the functions are executed.
           \param [in] text Function name.
        */
        TEB_Debug (const char* text);

        /**
           \brief Constructor used with TEB_DB_DEBUG 2 or 0 mode. Is meant to be inserted at the beginning of each function, in order to keep track of the order in which the functions are executed.
           \param [in] text Function name saved with PROGMEM.
        */
        TEB_Debug (const __FlashStringHelper* text);

        /**
           \brief Do not use. It is executed automatically.
        */
        ~TEB_Debug ();

        /**
           \brief In TEB_DB_DEBUG 1 or 0 mode prints information to the debug monitor.
           \param [in] c The character to be printed.
        */
        static void print (const char c);

        /**
           \brief In TEB_DB_DEBUG 1 or 0 mode prints information to the debug monitor.
           \param [in] number The number to be printed.
        */
        static void print (int32_t number);

        /**
           \brief In TEB_DB_DEBUG 1 or 0 mode prints information to the debug monitor.
           \param [in] number The number to be printed.
        */
        static void print (uint32_t number);

        /**
           \brief In TEB_DB_DEBUG 1 or 0 mode prints information to the debug monitor.
           \param [in] text The text to be printed.
        */
        static void print (const char* text);

        /**
           \brief In TEB_DB_DEBUG 1 or 0 mode prints information to the debug monitor.
           \param [in] text The text saved with PROGMEM to be printed.
        */
        static void print (const __FlashStringHelper* text);

        /**
           \brief Prints an error message on the debug monitor.
           \param [in] number Error number.
           \param [in] text Error text.
        */
        static void error (size_t number, const char* text);

        /**
           \brief Prints an error message on the debug monitor.
           \param [in] number Error number.
           \param [in] text Error text saved with PROGMEM.
        */
        static void error (size_t number, const __FlashStringHelper* text);

        /**
           \brief Prints an error message on the debug monitor and blocks the execution of the program.
           \param [in] number Error number.
           \param [in] text Error text.
        */
        static void fatalError (size_t number, const char* text);

        /**
           \brief Prints an error message on the debug monitor and blocks the execution of the program.
           \param [in] number Error number.
           \param [in] text Error text saved with PROGMEM.
        */
        static void fatalError (size_t number, const __FlashStringHelper* text);


        /**
           \return The total free heap.
        */
        static size_t totalFreeHeap();

        /**
           \return The size of the largest block of free heap.
        */
        static size_t largestHeapFreeBlock();

        static void test ();

    };
    static TEB_Debug debug;
#endif

    /**
       \class TEB_Display
       \brief This class contains methods to manage a display connected to the development board.
    */
    class TEB_Display {

      public:

        /**
           \brief Print a message on the display.
           \param [in] text Text to print.
           \param [in] textSize Text size. Must be > 0.
        */
        static void print (const char* text, uint8_t textSize);

        /**
           \brief Print a message on the display.
           \param [in] text Text saved with PROGMEM to print.
           \param [in] textSize Text size. Must be > 0.
        */
        static void print (const __FlashStringHelper* text, uint8_t textSize);

#ifdef TEB_DB_DEBUG
        static void test ();
#endif

    };
    static TEB_Display display;

    /**
       \class TEB_EEPROM
       \brief This class contains methods to manage the EEPROM memory of the development board.
    */
    class TEB_EEPROM {

      public:

        /**
           \brief Set it to the smallest unsigned int type that can index EEPROM elements.
        */
        typedef uint8_t uintDataType;

        /**
           \brief Saves data in EEPROM.
           \param [in] value Data to be saved.
           \param [in] valueLength Value length. Must be > 0 and <= 512.
           \return 1 if ok.
        */
        static int8_t write (const uint8_t* value, uintDataType valueLength);

        /**
           \brief Read data from EEPROM.
           \param [in] buffer Buffer in which to save the data.
           \param [in] bufferSize Buffer size. Must be > 0 and <= 512.
           \return 1 if ok.
        */
        static int8_t read (uint8_t* buffer, uintDataType bufferSize);

#ifdef TEB_DB_DEBUG
        static void test ();
#endif

    };
    static TEB_EEPROM eeprom;

    /**
       \class TEB_HTTP
       \brief This class contains methods to send request and receive http response. sendRequest is an independent function while connect, send, receive and stop are used together. sendRequest is less efficient but makes it easier to handle long HTTP requests and responses.
    */
    class TEB_HTTP {

      public:

        /**
           \brief HTTP request data type used in sendRequest. All fields must be initialized. connectionTimeout and responseDelay are in ms. If rootCA == "" is not evaluated.
        */
        struct request {
          const char* requestText;
          const char* serverAddress;
          uint16_t serverPort;
          const char* rootCA;
          uint16_t connectionTimeout;
          uint16_t responseDelay;
        };

        /**
           \brief HTTP response data type used in sendRequest. The fields do not need to be initialized.
        */
        struct response {
          char* header;
          size_t headerLength;
          char* payload;
          size_t payloadLength;
        };

        /**
           \brief It sends an HTTP request and receives the relative response.
           \param [in] httpRequest The HTTP request.
           \param [in] httpResponse TThe HTTP response.
           \param [in] responseBuffer Buffer in which to save the response.
           \param [in] responseBufferSize Buffer length.
           \return 1 if ok, 2 if "\n\r\n\r" was not found at the end of the HTTP response header.
           \details if return 2 the whole http response is saved in httpResponse.header. All fields of httpRequest must be initialized. If the HTTP response is longer than responseBufferSize it is truncated. If httpRequest.rootCA = "" the rootCA of httpRequest.serverAddress is not considered. The char* fields of httpResponse do not end with \0 while those of httpRequest do. httpResponse contains pointers to responseBuffer.
        */
        static int8_t sendRequest (request& httpRequest, response& httpResponse, char* responseBuffer, size_t responseBufferSize);

        /**
           \brief It sends an HTTP request and receives the relative response.
           \param [in] httpRequest The HTTP request.
           \param [in] httpResponse The HTTP response.
           \param [in] responseBuffer Buffer in which to save the response.
           \param [in] responseBufferSize Buffer length.
           \param [in] responseReceptionAlgorithm Custom algorithm for receiving the HTTP response.
           \return 1 if ok, 2 if "\n\r\n\r" was not found at the end of the HTTP response header.
           \details if return 2 the whole http response is saved in httpResponse.header. All fields of httpRequest must be initialized. If the HTTP response is longer than responseBufferSize it is truncated. If httpRequest.rootCA = "" the rootCA of httpRequest.serverAddress is not considered. The char* fields of httpResponse do not end with \0 while those of httpRequest do. httpResponse contains pointers to responseBuffer.
        */
        static int8_t sendRequest (request& httpRequest, response& httpResponse, char* responseBuffer, size_t responseBufferSize, char* (*responseReceptionAlgorithm) (void* client, char* responseBuffer, size_t responseBufferSize, uint16_t responseDelay));

        /**
           \brief Connect to a server.
           \param [in] serverAddress Server Address.
           \param [in] serverPort Server port.
           \param [in] rootCA If "" the rootCA of serverAddress is not considered.
           \param [in] connectionTimeout ms within which the connection must take place.
           \return 1 if ok.
           \details It can only be re-executed after the stop function or after a connect, send or receive failure.
        */
        static int8_t connect (const char* serverAddress, uint16_t serverPort, const char* rootCA, uint16_t connectionTimeout);

        /**
           \brief Sends an HTTP request.
           \param [in] requestText Request text.
           \param [in] requestTextLength Length of request.
           \return 1 if ok.
           \details If the send fails you must start over with connect. It can be executed after connect or another send.
        */
        static int8_t send (const char* requestText, size_t requestTextLength);

        /**
           \brief Receive an HTTP response.
           \param [in] responseBuffer Buffer in which to save the response.
           \param [in] requestTextLength Length of buffer.
           \return The number of characters saved in responseBuffer, otherwise a negative value.
           \details If it doesn't read anything return 0 (in this case it is recommended to repeat the reading several times to be sure to have received all the data). It can be executed after connect, send or another receive.
        */
        static int receive (const char* responseBuffer, size_t bufferSize);

        /**
           \brief Closes the connection with the server.
           \details It can be executed after connect, send or receive.
        */
        static void stop ();

#ifdef TEB_DB_DEBUG
        static void test (const char* ssid, const char* password, uint32_t timeOut);
#endif

    };
    static TEB_HTTP http;

    /**
       \class TEB_Led
       \brief This class contains methods to manage a led connected to the development board.
    */
    class TEB_Led {

      public:

        /**
           \brief Turn on the led.
        */
        static void on ();

        /**
           \brief Turn on the off.
        */
        static void off ();

        /**
           \brief Flashes the LED once.
           \param [in] onMS How many ms the led stays on.
           \param [in] offMS How many ms the led stays off.
        */
        static void blink (uint16_t onMS, uint16_t offMS);

#ifdef TEB_DB_DEBUG
        static void test ();
#endif

    };
    static TEB_Led led;

    /**
        \class TEB_Clock
        \brief Class designed to offer minimal support for date, time, timezone, and DST.
    */
    class TEB_Clock {

      public:

        /**
            \brief Set a timezone.
            \param [in] databaseName Enter a TZ database name. For more information see https://en.wikipedia.org/wiki/List_of_tz_database_time_zones.
            \param [in] utcOffsetHours Enter a UTC offset for hours. For more information see https://en.wikipedia.org/wiki/List_of_tz_database_time_zones.
            \param [in] utcOffsetMinutes Enter a UTC offset for minutes. For more information see https://en.wikipedia.org/wiki/List_of_tz_database_time_zones.
            \details Then use setDate to set the new timezone.
        */
        static void setTimeZone (const char* databaseName, int8_t utcOffsetHours, int8_t utcOffsetMinutes);

        /**
            \brief Sets the start of the DST.
            \param [in] dayOfWeek The day of the week on which DST begins. Enter 0 for Sunday, 1 for Monday, 2 for Tuesday, ..., 6 for Saturday.
            \param [in] thDay Enter 1 to select the first dayOfWeek of the month or -1 for the last, 2 for the second dayOfWeek of the month or -2 for the penultimate ... (max +5 or -5 included).
            \param [in] month The month that the rule starts. Must be >= 1 and <= 12
            \param [in] hour The local hour that the rule starts. Must be >= 0 and <= 23.
            \details Set all input parameters to 0 to disable DST. After defining the DST use setDate to set the new rule.
        */
        static void setDSTStart (uint8_t dayOfWeek, int8_t thDay, uint8_t month, uint8_t hour);

        /**
            \brief Sets the end of the DST.
            \param [in] dayOfWeek The day of the week on which DST ends. Enter 0 for Sunday, 1 for Monday, 2 for Tuesday, ..., 6 for Saturday.
            \param [in] thDay Enter 1 to select the first dayOfWeek of the month or -1 for the last, 2 for the second dayOfWeek of the month or -2 for the penultimate ... (max +5 or -5 included).
            \param [in] month The month that the rule ends. Must be >= 1 and <= 12
            \param [in] hour The local hour that the rule ends. Must be >= 0 and <= 23.
            \details Set all input parameters to 0 to disable DST. After defining the DST use setDate to set the new rule.
        */
        static void setDSTEnd (uint8_t dayOfWeek, int8_t thDay, uint8_t month, uint8_t hour);

        /**
            \brief Set a new date and time.
            \param [in] hours Must be >= 0 and <= 23.
            \param [in] minutes Must be >= 0 and <= 59.
            \param [in] seconds Must be >= 0 and <= 59.
            \param [in] Day Must be >= 1 and <= 31.
            \param [in] Month Must be >= 1 and <= 12.
            \param [in] Year Must be >= 1970 and <= 2105.
            \param [in] UTC True if the time is UTC, false if local.
            \details By indicating with DST_S the start time of the DST and with DST_E the end time, if UTC is false it is not possible to enter the time between DST_E - 1 hour and DST_E - 1 second (extremes included). If UTC is false and the time between DST_S and DST_S + 59 minutes + 59 seconds (extremes included) is entered by mistake, the time is set to DST_S + 1 h.
        */
        static void setDate (uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint16_t year, bool UTC);

        /**
             \brief Set a new date and time.
             \param [in] dateTime Date and time to set provided in a similar way to the "HTTP-date" format (for example "15 Nov 1994 08:12:31"). For more information see TEB_Time::epoch1970 (const char* dateTime);
             \param [in] UTC True if the time is UTC, false if local.
             \details Year must be >= 1970 and <= 2105. By indicating with DST_S the start time of the DST and with DST_E the end time, if UTC is false it is not possible to enter the time between DST_E - 1 hour and DST_E - 1 second (extremes included). If UTC is false and the time between DST_S and DST_S + 59 minutes + 59 seconds (extremes included) is entered by mistake, the time is set to DST_S + 1 h.
        */
        static void setDate (const char* dateTime, bool UTC);

        /**
             \brief Set a new date and time.
             \param [in] epoch1970 Date and time provided as epoch from 1-1-1970 at 0:0:0. For more information see TEB_Time::epoch1970 (const char* dateTime);
             \param [in] UTC True if the time is UTC, false if local.
             \details Year must be >= 1970 and <= 2105. By indicating with DST_S the start time of the DST and with DST_E the end time, if UTC is false it is not possible to enter the time between DST_E - 1 hour and DST_E - 1 second (extremes included). If UTC is false and the time between DST_S and DST_S + 59 minutes + 59 seconds (extremes included) is entered by mistake, the time is set to DST_S + 1 h.
        */
        static void setDate (uint32_t epoch1970, bool UTC);

        /**
             \brief Returns the date.
             \param [in] date Buffer in which to save the date in the form yyyy-mm-dd.
             \param [in] UTC True to return the UTC date, false for the locale.
             \return The epoch in seconds from 1-1-1970 at 0:0:0.
        */
        static uint32_t getDate (char* date, bool UTC);

        /**
             \brief Returns the time.
             \param [in] time Buffer in which to save the time in the form hh-mm-ss.
             \param [in] UTC True to return the UTC time, false for the locale.
             \return The epoch in seconds from 1-1-1970 at 0:0:0.
        */
        static uint32_t getTime (char* time, bool UTC);

        /**
             \brief Returns the date and time.
             \param [in] UTC True to return the UTC time, false for the locale.
             \return The epoch in seconds from 1-1-1970 at 0:0:0.
        */
        static uint32_t getDate (bool UTC);

        /**
             \brief Shift the time.
             \param [in] adjust How many seconds to translate the time.
             \details Be careful not to move the date before 1970 or after 2105.
        */
        static void adjust (int32_t adjustment);

        /**
            \brief Evaluate whether the time and date precede that of the development board.
            \param [in] hours Must be >= 0 and <= 23.
            \param [in] minutes Must be >= 0 and <= 59.
            \param [in] seconds Must be >= 0 and <= 59.
            \param [in] Day Must be >= 1 and <= 31.
            \param [in] Month Must be >= 1 and <= 12.
            \param [in] Year Must be >= 1970 and <= 2105.
            \param [in] UTC True if the time is UTC, false if local.
            \return True if the date and time have passed, false if equal to or greater than those of the development board.
            \details By indicating with DST_S the start time of the DST and with DST_E the end time, if UTC is false it is not possible to enter the time between DST_E - 1 hour and DST_E - 1 second (extremes included). If UTC is false and the time between DST_S and DST_S + 59 minutes + 59 seconds (extremes included) is entered by mistake, the time is set to DST_S + 1 h.
        */
        static bool isDatePassed (uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint16_t year, bool UTC);

        /**
            \brief Evaluate whether the time and date precede that of the development board.
            \param [in] dateTime Date and time to  be evaluated provided in a similar way to the "HTTP-date" format (for example "15 Nov 1994 08:12:31"). For more information see TEB_Time::epoch1970 (const char* dateTime);
            \param [in] UTC True if the time is UTC, false if local.
            \return True if the date and time have passed, false if equal to or greater than those of the development board.
            \details By indicating with DST_S the start time of the DST and with DST_E the end time, if UTC is false it is not possible to enter the time between DST_E - 1 hour and DST_E - 1 second (extremes included). If UTC is false and the time between DST_S and DST_S + 59 minutes + 59 seconds (extremes included) is entered by mistake, the time is set to DST_S + 1 h.
        */
        static bool isDatePassed (const char* dateTime, bool UTC);

        /**
            \brief Evaluate whether the time and date precede that of the development board.
            \param [in] epoch1970 Date and time provided as epoch from 1-1-1970 at 0:0:0. For more information see TEB_Time::epoch1970 (const char* dateTime);
            \param [in] UTC True if the time is UTC, false if local.
            \return True if the date and time have passed, false if equal to or greater than those of the development board.
            \details By indicating with DST_S the start time of the DST and with DST_E the end time, if UTC is false it is not possible to enter the time between DST_E - 1 hour and DST_E - 1 second (extremes included). If UTC is false and the time between DST_S and DST_S + 59 minutes + 59 seconds (extremes included) is entered by mistake, the time is set to DST_S + 1 h.
        */
        static bool isDatePassed (uint32_t epoch1970, bool UTC);

#ifdef TEB_DB_DEBUG
        static void test ();
#endif

    };
    static TEB_Clock clock;

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
    static TEB_WiFi wifi;

    /**
          \brief Reboot the development board.
    */
    static void reset();

#ifdef TEB_DB_DEBUG
    static void test (const char* ssid, const char* password, uint32_t timeOut);
#endif

};

#endif
