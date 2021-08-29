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

  Time is a library of PaulStoffregen (https://github.com/PaulStoffregen/Time).
*/

#include "TEB_DevelopmentBoard.h"
#include <TimeLib.h>
#include "../strings_and_numbers/TEB_Numbers.h"
#include "../time_management/TEB_Time.h"

char TEB_DevelopmentBoard_TEB_Clock_timezone_database_name[35] = "Etc/GMT";
int8_t TEB_DevelopmentBoard_TEB_Clock_timezone_utc_offset_hours = 0;
int8_t TEB_DevelopmentBoard_TEB_Clock_timezone_utc_offset_minutes = 0;

uint8_t TEB_DevelopmentBoard_TEB_Clock_dst_start_day = 0;
int8_t TEB_DevelopmentBoard_TEB_Clock_dst_start_thday = 0;
uint8_t TEB_DevelopmentBoard_TEB_Clock_dst_start_month = 0;
uint8_t TEB_DevelopmentBoard_TEB_Clock_dst_start_hour = 0;

uint8_t TEB_DevelopmentBoard_TEB_Clock_dst_end_day = 0;
int8_t TEB_DevelopmentBoard_TEB_Clock_dst_end_thday = 0;
uint8_t TEB_DevelopmentBoard_TEB_Clock_dst_end_month = 0;
uint8_t TEB_DevelopmentBoard_TEB_Clock_dst_end_hour = 0;

bool TEB_DevelopmentBoard_TEB_Clock_is_leap_year (uint16_t year) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard_TEB_Clock_is_leap_year (uint8_t year)"));
#endif
  if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) return true;
  return false;
}

time_t TEB_DevelopmentBoard_TEB_Clock_get_dst_start_or_end (bool is_start, uint8_t year) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard_TEB_Clock_get_dst_start_or_end (bool is_start, uint8_t year)"));
#endif
  const uint8_t months_lengths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  tmElements_t tm;
  tm.Second = 0;
  tm.Minute = 0;
  tm.Year = year;
  if (is_start) {
    tm.Hour = TEB_DevelopmentBoard_TEB_Clock_dst_start_hour;
    tm.Month = TEB_DevelopmentBoard_TEB_Clock_dst_start_month;
    if (TEB_DevelopmentBoard_TEB_Clock_dst_start_thday > 0) tm.Day = 1;
    else {
      if (TEB_DevelopmentBoard_TEB_Clock_is_leap_year(tm.Year + 1970) && TEB_DevelopmentBoard_TEB_Clock_dst_start_month == 2) tm.Day = 29;
      else tm.Day = months_lengths[TEB_DevelopmentBoard_TEB_Clock_dst_start_month - 1];
    }
  }
  else {
    tm.Hour = TEB_DevelopmentBoard_TEB_Clock_dst_end_hour;
    tm.Month = TEB_DevelopmentBoard_TEB_Clock_dst_end_month;
    if (TEB_DevelopmentBoard_TEB_Clock_dst_end_thday > 0) tm.Day = 1;
    else {
      if (TEB_DevelopmentBoard_TEB_Clock_is_leap_year(tm.Year + 1970) && TEB_DevelopmentBoard_TEB_Clock_dst_end_month == 2) tm.Day = 29;
      else tm.Day = months_lengths[TEB_DevelopmentBoard_TEB_Clock_dst_end_month - 1];
    }
  }
  tm.Wday = weekday(makeTime(tm)) - 1;
  int8_t t2;
  if (is_start) {
    if (TEB_DevelopmentBoard_TEB_Clock_dst_start_thday > 0) {
      t2 = TEB_DevelopmentBoard_TEB_Clock_dst_start_thday - 1;
      if (TEB_DevelopmentBoard_TEB_Clock_dst_start_day < tm.Wday) tm.Day = 8;
    }
    else {
      t2 = TEB_DevelopmentBoard_TEB_Clock_dst_start_thday + 1;
      if (TEB_DevelopmentBoard_TEB_Clock_dst_start_day > tm.Wday) tm.Day = tm.Day - 7;
    }
    tm.Day = (tm.Day + TEB_DevelopmentBoard_TEB_Clock_dst_start_day) - tm.Wday;
  }
  else {
    if (TEB_DevelopmentBoard_TEB_Clock_dst_end_thday > 0) {
      t2 = TEB_DevelopmentBoard_TEB_Clock_dst_end_thday - 1;
      if (TEB_DevelopmentBoard_TEB_Clock_dst_end_day < tm.Wday) tm.Day = 8;
    }
    else {
      t2 = TEB_DevelopmentBoard_TEB_Clock_dst_end_thday + 1;
      if (TEB_DevelopmentBoard_TEB_Clock_dst_end_day > tm.Wday) tm.Day = tm.Day - 7;
    }
    tm.Day = (tm.Day + TEB_DevelopmentBoard_TEB_Clock_dst_end_day) - tm.Wday;
  }
  tm.Day = tm.Day + (t2) * 7;
  return makeTime(tm);
}

bool TEB_DevelopmentBoard_TEB_Clock_check_dst (time_t time) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard_TEB_Clock_check_dst (time_t time)"));
#endif
  if ((uint32_t)time >= (uint32_t)TEB_DevelopmentBoard_TEB_Clock_get_dst_start_or_end(true, year(time) - 1970)) {
    if ((uint32_t)time < (uint32_t)TEB_DevelopmentBoard_TEB_Clock_get_dst_start_or_end(false, year(time) - 1970) - 3600) {
      return true;
    }
  }
  return false;
}

uint32_t TEB_DevelopmentBoard_TEB_Clock_convert_to_local_time (uint32_t time) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard_TEB_Clock_convert_to_local_time (uint32_t time)"));
#endif
  time = time + ((int32_t)TEB_DevelopmentBoard_TEB_Clock_timezone_utc_offset_hours * 3600 + (int32_t)TEB_DevelopmentBoard_TEB_Clock_timezone_utc_offset_minutes * 60);
  if (TEB_DevelopmentBoard_TEB_Clock_dst_start_thday != 0) {
    if (TEB_DevelopmentBoard_TEB_Clock_check_dst(time)) return time + 3600;
  }
  return time;
}

uint32_t TEB_DevelopmentBoard_TEB_Clock_convert_to_utc_time (uint32_t time) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard_TEB_Clock_convert_to_utc_time (uint32_t time)"));
#endif
  if (TEB_DevelopmentBoard_TEB_Clock_dst_start_thday != 0) {
    uint32_t t2 = (uint32_t)TEB_DevelopmentBoard_TEB_Clock_get_dst_start_or_end(true, year(time) - 1970);
    if (t2 <= time && time <= t2 + 59 * 60 + 59) time = t2 + 3600;
    if (TEB_DevelopmentBoard_TEB_Clock_check_dst(time)) time = time - 3600;
  }
  return time - ((int32_t)TEB_DevelopmentBoard_TEB_Clock_timezone_utc_offset_hours * 3600 + (int32_t)TEB_DevelopmentBoard_TEB_Clock_timezone_utc_offset_minutes * 60);
}

void TEB_DevelopmentBoard::TEB_Clock::setTimeZone (const char* databaseName, int8_t utcOffsetHours, int8_t utcOffsetMinutes) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::setTimeZone (const char* databaseName, int8_t utcOffsetHours, int8_t utcOffsetMinutes)"));
  if (databaseName == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(96, F("databaseName cannot be NULL."));
  if (utcOffsetHours < -12 || 14 < utcOffsetHours) TEB_DevelopmentBoard::TEB_Debug::fatalError(97, F("Wrong value of utcOffsetHours."));
  if (utcOffsetMinutes != 0 && utcOffsetMinutes != 15 && utcOffsetMinutes != 30 && utcOffsetMinutes != 45) TEB_DevelopmentBoard::TEB_Debug::fatalError(98, F("Wrong value of utcOffsetMinutes."));
#endif
  TEB_DevelopmentBoard_TEB_Clock_timezone_utc_offset_hours = utcOffsetHours;
  TEB_DevelopmentBoard_TEB_Clock_timezone_utc_offset_minutes = utcOffsetMinutes;
  TEB_Strings::append(TEB_DevelopmentBoard_TEB_Clock_timezone_database_name, databaseName);
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nSet the timezone ")); TEB_DevelopmentBoard::TEB_Debug::print(TEB_DevelopmentBoard_TEB_Clock_timezone_database_name); TEB_DevelopmentBoard::TEB_Debug::print(F(" ("));
  if (utcOffsetHours < 0) {
    TEB_DevelopmentBoard::TEB_Debug::print('-');
    TEB_DevelopmentBoard::TEB_Debug::print(-1 * utcOffsetHours);
  }
  else {
    TEB_DevelopmentBoard::TEB_Debug::print('+');
    TEB_DevelopmentBoard::TEB_Debug::print(utcOffsetHours);
  }
  TEB_DevelopmentBoard::TEB_Debug::print(F(":"));
  TEB_DevelopmentBoard::TEB_Debug::print(utcOffsetMinutes); TEB_DevelopmentBoard::TEB_Debug::print(F(").\n"));
#endif
}

void TEB_DevelopmentBoard::TEB_Clock::setDSTStart (uint8_t dayOfWeek, int8_t thDay, uint8_t month, uint8_t hour) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::setDSTStart (uint8_t dayOfWeek, int8_t thDay, uint8_t month, uint8_t hour)"));
  if (dayOfWeek < 0 || 6 < dayOfWeek) TEB_DevelopmentBoard::TEB_Debug::fatalError(99, F("dayOfWeek must be >= 0 and <= 6."));
  if (thDay < -5 || 5 < thDay) TEB_DevelopmentBoard::TEB_Debug::fatalError(100, F("thDay must be >= -5 and <= 5."));
  if (month < 0 || 12 < month) TEB_DevelopmentBoard::TEB_Debug::fatalError(101, F("month must be >= 0 and <= 12."));
  if (hour < 0 || 23 < hour) TEB_DevelopmentBoard::TEB_Debug::fatalError(102, F("hour must be >= 0 and <= 23."));
  if (thDay == 0 || hour == 0) if (thDay != 0 || month != 0 || dayOfWeek != 0 || hour != 0) TEB_DevelopmentBoard::TEB_Debug::fatalError(103, F("The input parameters must all be 0 to disable the dst."));
#endif
  TEB_DevelopmentBoard_TEB_Clock_dst_start_day = dayOfWeek;
  TEB_DevelopmentBoard_TEB_Clock_dst_start_thday = thDay;
  TEB_DevelopmentBoard_TEB_Clock_dst_start_month = month;
  TEB_DevelopmentBoard_TEB_Clock_dst_start_hour = hour;
#ifdef TEB_DB_DEBUG
  if (thDay == 0) TEB_DevelopmentBoard::TEB_Debug::print(F("\nDaylight saving time is disabled.\n"));
  else {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nSet the start of daylight saving time on "));
    if (thDay > 0) TEB_DevelopmentBoard::TEB_Debug::print(thDay);
    else {
      TEB_DevelopmentBoard::TEB_Debug::print('-');
      TEB_DevelopmentBoard::TEB_Debug::print(thDay * -1);
    }
    TEB_DevelopmentBoard::TEB_Debug::print(F("° "));
    switch (dayOfWeek) {
      case 0:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Sunday")); break;
      case 1:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Monday")); break;
      case 2:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Tuesday")); break;
      case 3:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Wednesday")); break;
      case 4:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Thursday")); break;
      case 5:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Friday")); break;
      case 6:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Saturday")); break;
    }
    TEB_DevelopmentBoard::TEB_Debug::print(F(" of the month n. ")); TEB_DevelopmentBoard::TEB_Debug::print(month);
    TEB_DevelopmentBoard::TEB_Debug::print(F(" at ")); TEB_DevelopmentBoard::TEB_Debug::print(hour);
    TEB_DevelopmentBoard::TEB_Debug::print(F(" local time.\n"));
  }
#endif
}

void TEB_DevelopmentBoard::TEB_Clock::setDSTEnd (uint8_t dayOfWeek, int8_t thDay, uint8_t month, uint8_t hour) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::setDSTEnd (uint8_t dayOfWeek, int8_t thDay, uint8_t month, uint8_t hour)"));
  if (dayOfWeek < 0 || 6 < dayOfWeek) TEB_DevelopmentBoard::TEB_Debug::fatalError(104, F("dayOfWeek must be >= 0 and <= 6."));
  if (thDay < -5 || 5 < thDay) TEB_DevelopmentBoard::TEB_Debug::fatalError(105, F("thDay must be >= -5 and <= 5."));
  if (month < 0 || 12 < month) TEB_DevelopmentBoard::TEB_Debug::fatalError(106, F("month must be >= 0 and <= 12."));
  if (hour < 0 || 23 < hour) TEB_DevelopmentBoard::TEB_Debug::fatalError(107, F("hour must be >= 0 and <= 23."));
  if (thDay == 0 || hour == 0) if (thDay != 0 || month != 0 || dayOfWeek != 0 || hour != 0) TEB_DevelopmentBoard::TEB_Debug::fatalError(108, F("The input parameters must all be 0 to disable the dst."));
#endif
  TEB_DevelopmentBoard_TEB_Clock_dst_end_day = dayOfWeek;
  TEB_DevelopmentBoard_TEB_Clock_dst_end_thday = thDay;
  TEB_DevelopmentBoard_TEB_Clock_dst_end_month = month;
  TEB_DevelopmentBoard_TEB_Clock_dst_end_hour = hour;
#ifdef TEB_DB_DEBUG
  if (thDay == 0) TEB_DevelopmentBoard::TEB_Debug::print(F("\nDaylight saving time is disabled.\n"));
  else {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nSet the end of daylight saving time on "));
    if (thDay > 0) TEB_DevelopmentBoard::TEB_Debug::print(thDay);
    else {
      TEB_DevelopmentBoard::TEB_Debug::print('-');
      TEB_DevelopmentBoard::TEB_Debug::print(thDay * -1);
    }
    TEB_DevelopmentBoard::TEB_Debug::print(F("° "));
    switch (dayOfWeek) {
      case 0:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Sunday")); break;
      case 1:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Monday")); break;
      case 2:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Tuesday")); break;
      case 3:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Wednesday")); break;
      case 4:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Thursday")); break;
      case 5:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Friday")); break;
      case 6:
        TEB_DevelopmentBoard::TEB_Debug::print(F("Saturday")); break;
    }
    TEB_DevelopmentBoard::TEB_Debug::print(F(" of the month n. ")); TEB_DevelopmentBoard::TEB_Debug::print(month);
    TEB_DevelopmentBoard::TEB_Debug::print(F(" at ")); TEB_DevelopmentBoard::TEB_Debug::print(hour);
    TEB_DevelopmentBoard::TEB_Debug::print(F(" local time.\n"));
  }
#endif
}

void TEB_DevelopmentBoard::TEB_Clock::setDate (uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint16_t year, bool UTC) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::setDate (uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint16_t year, bool UTC)"));
  if (hours < 0 || 23 < hours) TEB_DevelopmentBoard::TEB_Debug::fatalError(109, F("hours must be >= 0 and <= 23."));
  if (minutes < 0 || 59 < minutes) TEB_DevelopmentBoard::TEB_Debug::fatalError(110, F("minutes must be >= 0 and <= 59."));
  if (seconds < 0 || 59 < seconds) TEB_DevelopmentBoard::TEB_Debug::fatalError(111, F("seconds must be >= 0 and <= 59."));
  if (day < 1 || 31 < day) TEB_DevelopmentBoard::TEB_Debug::fatalError(112, F("day must be >= 1 and <= 31."));
  if (month < 1 || 12 < month) TEB_DevelopmentBoard::TEB_Debug::fatalError(113, F("month must be >= 1 and <= 12."));
  if (year < 1970 || 2105 < year) TEB_DevelopmentBoard::TEB_Debug::fatalError(114, F("year must be >= 1970 and <= 2105."));
  if (TEB_DevelopmentBoard_TEB_Clock_dst_start_thday == 0 || TEB_DevelopmentBoard_TEB_Clock_dst_end_thday == 0) if (TEB_DevelopmentBoard_TEB_Clock_dst_start_thday != 0 || TEB_DevelopmentBoard_TEB_Clock_dst_end_thday != 0)  TEB_DevelopmentBoard::TEB_Debug::fatalError(115, F("To disable the dst it is necessary to set all the input parameters of the functions setDSTStart and setDSTEnd to 0."));
#endif
  setDate(TEB_Time::epoch1970(hours, minutes, seconds, day, month, year), UTC);
}

void TEB_DevelopmentBoard::TEB_Clock::setDate (const char* dateTime, bool UTC) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::setDate (const char* dateTime, bool UTC)"));
  if (dateTime == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(116, F("dateTime cannot be NULL."));
#endif
  setDate(TEB_Time::epoch1970(dateTime), UTC);
}

void TEB_DevelopmentBoard::TEB_Clock::setDate (uint32_t epoch1970, bool UTC) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::setDate (uint32_t epoch1970, bool UTC)"));
  if (TEB_DevelopmentBoard_TEB_Clock_dst_start_thday == 0 || TEB_DevelopmentBoard_TEB_Clock_dst_end_thday == 0) if (TEB_DevelopmentBoard_TEB_Clock_dst_start_thday != 0 || TEB_DevelopmentBoard_TEB_Clock_dst_end_thday != 0)  TEB_DevelopmentBoard::TEB_Debug::fatalError(117, F("To disable the dst it is necessary to set all the input parameters of the functions setDSTStart and setDSTEnd to 0."));
#endif
  if (!UTC) setTime(TEB_DevelopmentBoard_TEB_Clock_convert_to_utc_time(epoch1970));
  else setTime((time_t)epoch1970);
#ifdef TEB_DB_DEBUG
  if (!UTC) epoch1970 = TEB_DevelopmentBoard_TEB_Clock_convert_to_utc_time(epoch1970);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nSet the UTC time "));
  TEB_DevelopmentBoard::TEB_Debug::print(hour(epoch1970));
  TEB_DevelopmentBoard::TEB_Debug::print(F(":"));
  TEB_DevelopmentBoard::TEB_Debug::print(minute(epoch1970));
  TEB_DevelopmentBoard::TEB_Debug::print(F(":"));
  TEB_DevelopmentBoard::TEB_Debug::print(second(epoch1970));
  TEB_DevelopmentBoard::TEB_Debug::print(F(" and the date "));
  TEB_DevelopmentBoard::TEB_Debug::print(day(epoch1970));
  TEB_DevelopmentBoard::TEB_Debug::print(F("-"));
  TEB_DevelopmentBoard::TEB_Debug::print(month(epoch1970));
  TEB_DevelopmentBoard::TEB_Debug::print(F("-"));
  TEB_DevelopmentBoard::TEB_Debug::print(year(epoch1970));
  TEB_DevelopmentBoard::TEB_Debug::print(F(". The DST is "));
  if (TEB_DevelopmentBoard_TEB_Clock_dst_start_thday == 0) TEB_DevelopmentBoard::TEB_Debug::print(F("undefined"));
  else if (TEB_DevelopmentBoard_TEB_Clock_check_dst(epoch1970 + ((int32_t)TEB_DevelopmentBoard_TEB_Clock_timezone_utc_offset_hours * 3600 + (int32_t)TEB_DevelopmentBoard_TEB_Clock_timezone_utc_offset_minutes * 60))) TEB_DevelopmentBoard::TEB_Debug::print(F("ON"));
  else TEB_DevelopmentBoard::TEB_Debug::print(F("OFF"));
  TEB_DevelopmentBoard::TEB_Debug::print(F(".\n"));
#endif
}

uint32_t TEB_DevelopmentBoard::TEB_Clock::getDate (char* date, bool UTC) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::getDate (char* date, bool UTC)"));
  if (date == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(118, F("date cannot be NULL."));
#endif
  const uint32_t t = getDate(UTC);
  date = TEB_Strings::intChar(year(t), date);
  *date = '-';
  date++;
  date = TEB_Strings::intChar(month(t), date);
  *date = '-';
  date++;
  TEB_Strings::intChar(day(t), date);
  return t;
}

uint32_t TEB_DevelopmentBoard::TEB_Clock::getTime (char* time, bool UTC) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::getTime (char* time, bool UTC)"));
  if (time == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(119, F("time cannot be NULL."));
#endif
  const uint32_t t = getDate(UTC);
  time = TEB_Strings::intChar(hour(t), time);
  *time = ':';
  time++;
  time = TEB_Strings::intChar(minute(t), time);
  *time = ':';
  time++;
  TEB_Strings::intChar(second(t), time);
  return t;
}

uint32_t TEB_DevelopmentBoard::TEB_Clock::getDate (bool UTC) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::getDate (bool UTC)"));
#endif
  if (!UTC) return TEB_DevelopmentBoard_TEB_Clock_convert_to_local_time(now());
  else return now();
}

void TEB_DevelopmentBoard::TEB_Clock::adjust (int32_t adjustment) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::adjust (int32_t adjustment)"));
#endif
  adjustTime(adjustment);
}

bool TEB_DevelopmentBoard::TEB_Clock::isDatePassed (uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint16_t year, bool UTC) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::isDatePassed (uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint16_t year, bool UTC)"));
  if (hours < 0 || 23 < hours) TEB_DevelopmentBoard::TEB_Debug::fatalError(120, F("hours must be >= 0 and <= 23."));
  if (minutes < 0 || 59 < minutes) TEB_DevelopmentBoard::TEB_Debug::fatalError(121, F("minutes must be >= 0 and <= 59."));
  if (seconds < 0 || 59 < seconds) TEB_DevelopmentBoard::TEB_Debug::fatalError(122, F("seconds must be >= 0 and <= 59."));
  if (day < 1 || 31 < day) TEB_DevelopmentBoard::TEB_Debug::fatalError(123, F("day must be >= 1 and <= 31."));
  if (month < 1 || 12 < month) TEB_DevelopmentBoard::TEB_Debug::fatalError(124, F("month must be >= 1 and <= 12."));
  if (year < 1970 || 2105 < year) TEB_DevelopmentBoard::TEB_Debug::fatalError(125, F("year must be >= 1970 and <= 2105."));
#endif
  return isDatePassed(TEB_Time::epoch1970(hours, minutes, seconds, day, month, year), UTC);
}

bool TEB_DevelopmentBoard::TEB_Clock::isDatePassed (const char* dateTime, bool UTC) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::isDatePassed (const char* dateTime, bool UTC)"));
  if (dateTime == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(126, F("dateTime cannot be NULL."));
#endif
  return isDatePassed(TEB_Time::epoch1970(dateTime), UTC);
}

bool TEB_DevelopmentBoard::TEB_Clock::isDatePassed (uint32_t epoch1970, bool UTC) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::isDatePassed (uint32_t epoch1970, bool UTC)"));
#endif
  if (!UTC) epoch1970 = TEB_DevelopmentBoard_TEB_Clock_convert_to_utc_time(epoch1970);
  if ((uint32_t)now() > epoch1970) return true;
  return false;
}

#ifdef TEB_DB_DEBUG
void TEB_DevelopmentBoard::TEB_Clock::test () {
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_Clock::test ()"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_DevelopmentBoard::TEB_Debug::print(F("TEB_DevelopmentBoard::TEB_Time"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  setTimeZone("Europe/Rome", 1, 0);
  setDSTStart(0, -1, 3, 2);
  setDSTEnd(0, -1, 10, 3);
  uint32_t dst_start = (uint32_t)TEB_DevelopmentBoard_TEB_Clock_get_dst_start_or_end(true, 2000 - 1970);
  uint32_t dst_end = (uint32_t)TEB_DevelopmentBoard_TEB_Clock_get_dst_start_or_end(false, 2000 - 1970);
  setDate(dst_start - 3600 * 4, false);
  uint32_t i = dst_start - 3600 * 4;
  char t2[20];
  TEB_DevelopmentBoard::TEB_Debug::print("UTC      LOCAL\n");
  while (i < dst_start + 3600 * 4) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i + 60 * 15;
  }
  while (i >= dst_start - 3600 * 4) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(-60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i - 60 * 15;
  }
  setDate(dst_end - 3600 * 4, false);
  i = dst_end - 3600 * 4;
  TEB_DevelopmentBoard::TEB_Debug::print("UTC      LOCAL\n");
  while (i < dst_end + 3600 * 4) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i + 60 * 15;
  }
  while (i >= dst_end - 3600 * 4) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(-60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i - 60 * 15;
  }
  setTimeZone("America/New_York", -5, 0);
  setDSTStart(0, 2, 3, 2);
  setDSTEnd(0, 1, 11, 2);
  dst_start = (uint32_t)TEB_DevelopmentBoard_TEB_Clock_get_dst_start_or_end(true, 2001 - 1970);
  dst_end = (uint32_t)TEB_DevelopmentBoard_TEB_Clock_get_dst_start_or_end(false, 2001 - 1970);
  setDate(dst_start - 3600 * 7, false);
  i = dst_start - 3600 * 7;
  TEB_DevelopmentBoard::TEB_Debug::print("UTC      LOCAL\n");
  while (i < dst_start + 3600 * 7) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i + 60 * 15;
  }
  while (i >= dst_start - 3600 * 7) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(-60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i - 60 * 15;
  }
  setDate(dst_end - 3600 * 7, false);
  i = dst_end - 3600 * 7;
  TEB_DevelopmentBoard::TEB_Debug::print("UTC      LOCAL\n");
  while (i < dst_end + 3600 * 7) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i + 60 * 15;
  }
  while (i >= dst_end - 3600 * 7) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(-60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i - 60 * 15;
  }
  setTimeZone("Test", 1, 30);
  setDSTStart(0, 4, 3, 2);
  setDSTEnd(0, -4, 11, 2);
  dst_start = (uint32_t)TEB_DevelopmentBoard_TEB_Clock_get_dst_start_or_end(true, 2001 - 1970);
  dst_end = (uint32_t)TEB_DevelopmentBoard_TEB_Clock_get_dst_start_or_end(false, 2001 - 1970);
  setDate(dst_start - 3600 * 3, false);
  i = dst_start - 3600 * 3;
  TEB_DevelopmentBoard::TEB_Debug::print("UTC      LOCAL\n");
  while (i < dst_start + 3600 * 3) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i + 60 * 15;
  }
  while (i >= dst_start - 3600 * 3) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(-60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i - 60 * 15;
  }
  setDate(dst_end - 3600 * 3, false);
  i = dst_end - 3600 * 3;
  TEB_DevelopmentBoard::TEB_Debug::print("UTC      LOCAL\n");
  while (i < dst_end + 3600 * 3) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i + 60 * 15;
  }
  while (i >= dst_end - 3600 * 3) {
    getTime(t2, true);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    TEB_DevelopmentBoard::TEB_Debug::print("   ");
    getTime(t2, false);
    TEB_DevelopmentBoard::TEB_Debug::print(t2);
    adjust(-60 * 15);
    TEB_DevelopmentBoard::TEB_Debug::print("\n");
    i = i - 60 * 15;
  }
  setTimeZone("Europe/Rome", 1, 0);
  setDSTStart(0, -1, 3, 2);
  setDSTEnd(0, -1, 10, 3);
  setDate(2, 1, 1, 11, 11, 2019, true);
  setDate(2, 1, 1, 11, 11, 2019, false);
  setDate("15 Aug 1998 08:12:31", true);
  setDate("15 Aug 1998 08:12:31", false);
  TEB_DevelopmentBoard::TEB_Debug::print("\n1\n");
  setDate(0, 59, 59, 26, 3, 2000, true);
  setDate(1, 0, 0, 26, 3, 2000, true);
  setDate(0, 59, 59, 29, 10, 2000, true);
  setDate(1, 0, 0, 29, 10, 2000, true);
  TEB_DevelopmentBoard::TEB_Debug::print("\n2\n");
  setDate(1, 59, 59, 26, 3, 2000, false);
  setDate(2, 0, 0, 26, 3, 2000, false);
  setDate(2, 59, 59, 26, 3, 2000, false);
  setDate(3, 0, 0, 26, 3, 2000, false);
  setDate(1, 59, 59, 29, 10, 2000, false);
  setDate(2, 0, 0, 29, 10, 2000, false);
  setDate(2, 59, 59, 29, 10, 2000, false);
  setDate(3, 0, 0, 29, 10, 2000, false);
  if (isDatePassed(getDate(false), false)) TEB_DevelopmentBoard::TEB_Debug::print(F("\nDate passed.\n"));
  else TEB_DevelopmentBoard::TEB_Debug::print(F("\nDate not passed or equal.\n"));
  if (isDatePassed(2, 59, 59, 29, 10, 2000, false)) TEB_DevelopmentBoard::TEB_Debug::print(F("\nDate passed.\n"));
  else TEB_DevelopmentBoard::TEB_Debug::print(F("\nDate not passed or equal.\n"));
  setDate(2, 0, 0, 29, 10, 2000, true);
  if (isDatePassed(getDate(true), true)) TEB_DevelopmentBoard::TEB_Debug::print(F("\nDate passed.\n"));
  else TEB_DevelopmentBoard::TEB_Debug::print(F("\nDate not passed or equal.\n"));
  if (isDatePassed("29 Oct 2000 01:59:59", true)) TEB_DevelopmentBoard::TEB_Debug::print(F("\nDate passed.\n"));
  else TEB_DevelopmentBoard::TEB_Debug::print(F("\nDate not passed or equal.\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif
