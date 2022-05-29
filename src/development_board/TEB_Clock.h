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

#ifndef TEB_Clock_h
#define TEB_Clock_h

#include "../TEB_Configurations.h"
#include <Arduino.h>

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

#endif