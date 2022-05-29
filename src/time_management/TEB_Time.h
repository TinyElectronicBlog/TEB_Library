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

#ifndef TEB_Time_h
#define TEB_Time_h

#include "../development_board/TEB_Debug.h"
#ifdef TEB_DB_DEBUG
#include "../TEB_Some_global_values.h"
#endif

/**
    \class TEB_Time
    \brief This class includes functions for converting dates and times from literal to numeric form and vice versa.
*/
class TEB_Time {

  public:

    /**
        \brief Save in date the input date in yyyy-mm-dd format.
        \param [in] day Must be >= 1 and <= 31.
        \param [in] month Must be >= 1 and <= 12.
        \param [in] year Must be >= 1000.
        \param [in] date Buffer in which the date is saved in yyyy-mm-dd format. Must not be NULL.
        \return A pointer to the \0 that ends date.
    */
    static char* strDate (uint8_t day, uint8_t month, uint16_t year, char* date);

    /**
        \brief Save in time the input time in hh-mm-ss format.
        \param [in] hours Must be >= 0 and <= 23.
        \param [in] minutes Must be >= 0 and <= 59.
        \param [in] seconds Must be >= 0 and <= 59.
        \param [in] time  Buffer in which the time is saved in hh-mm-ss format. Must not be NULL.
        \return A pointer to the \0 that ends time.
    */
    static char* strTime (uint8_t hours, uint8_t minutes, uint8_t seconds, char* time);

    /**
        \brief Extracts the year from the given input date in the yyyy-mm-dd format.
        \param [in] date Date in yyyy-mm-dd format. Must not be NULL.
        \return The year.
    */
    static uint16_t intYear (const char* date);

    /**
        \brief Extracts the month from the given input date in the yyyy-mm-dd format.
        \param [in] date Date in yyyy-mm-dd format. Must not be NULL.
        \return The month.
    */
    static uint8_t intMonth (const char* date);

    /**
        \brief Extracts the day from the given input date in the yyyy-mm-dd format.
        \param [in] date Date in yyyy-mm-dd format. Must not be NULL.
        \return The day.
    */
    static uint8_t intDay (const char* date);

    /**
        \brief Extracts the hours from the given input time in the hh-mm-ss format.
        \param [in] time Time in hh-mm-ss format. Must not be NULL.
        \return The hours.
    */
    static uint8_t intHours (const char* time);

    /**
         \brief Extracts the minutes from the given input time in the hh-mm-ss format.
         \param [in] time Time in hh-mm-ss format. Must not be NULL.
         \return The minutes.
    */
    static uint8_t intMinutes (const char* time);

    /**
        \brief Extracts the seconds from the given input time in the hh-mm-ss format.
        \param [in] time Time in hh-mm-ss format. Must not be NULL.
        \return The seconds.
    */
    static uint8_t intSeconds (const char* time);

    /**
       \brief Converts the desired date to epoch referring to 1-1-1970 at 00:00:00.
       \param [in] hours Must be >= 0 and <= 23.
       \param [in] minutes Must be >= 0 and <= 59.
       \param [in] seconds Must be >= 0 and <= 59.
       \param [in] day Must be >= 1 and <= 31.
       \param [in] month Must be >= 1 and <= 12.
       \param [in] year Must be >= 1970 and <= 2105.
       \return The epoch in seconds.
    */
    static uint32_t epoch1970 (uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint16_t year);

    /**
       \brief Converts the desired date to epoch referring to 1-1-1970 at 00:00:00.
       \param [in] dateTime Date and time to set provided in a similar way to the "HTTP-date" format (for example "15 Nov 1994 08:12:31"). For more information see the definition of the method.
       \return The epoch in seconds.
       \details The year must be >= 1970 and <= 2105.
    */
    static uint32_t epoch1970 (const char* dateTime);


#ifdef TEB_DB_DEBUG
    static void test ();
#endif

};

#endif