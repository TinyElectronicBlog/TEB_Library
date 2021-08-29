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

#include "TEB_Time.h"
#include <TimeLib.h>

char* TEB_Time::strDate (uint8_t day, uint8_t month, uint16_t year, char* date) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Time::strDate (uint8_t day, uint8_t month, uint16_t year, char* date)"));
  if (day < 1 || 31 < day) TEB_DevelopmentBoard::TEB_Debug::fatalError(258, F("day must be >= 1 and <= 31."));
  if (month < 1 || 12 < month) TEB_DevelopmentBoard::TEB_Debug::fatalError(259, F("month must be >= 1 and <= 12."));
  if (year < 1000) TEB_DevelopmentBoard::TEB_Debug::fatalError(260, F("year must be >= 1000."));
  if (date == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(261, F("date cannot be NULL."));
#endif
  date = TEB_Strings::intChar(year, date);
  *date = '-'; date++;
  if (month < 10) {
    *date = '0'; date++;
  }
  date = TEB_Strings::intChar(month, date);
  *date = '-'; date++;
  if (day < 10) {
    *date = '0'; date++;
  }
  return TEB_Strings::intChar(day, date);
}

char* TEB_Time::strTime (uint8_t hours, uint8_t minutes, uint8_t seconds, char* time) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Time::strTime (uint8_t hours, uint8_t minutes, uint8_t seconds, char* time)"));
  if (hours < 0 || 23 < hours) TEB_DevelopmentBoard::TEB_Debug::fatalError(262, F("hours must be >= 0 and <= 23."));
  if (minutes < 0 || 59 < minutes) TEB_DevelopmentBoard::TEB_Debug::fatalError(263, F("minutes must be >= 0 and <= 59."));
  if (seconds < 0 || 59 < seconds) TEB_DevelopmentBoard::TEB_Debug::fatalError(264, F("seconds must be >= 0 and <= 59."));
  if (time == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(265, F("time cannot be NULL."));
#endif
  if (hours < 10) {
    *time = '0'; time++;
  }
  time = TEB_Strings::intChar(hours, time);
  *time = ':'; time++;
  if (minutes < 10) {
    *time = '0'; time++;
  }
  time = TEB_Strings::intChar(minutes, time);
  *time = ':'; time++;
  if (seconds < 10) {
    *time = '0'; time++;
  }
  return TEB_Strings::intChar(seconds, time);
}

uint16_t TEB_Time::intYear (const char* date) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Time::intYear (const char* date)"));
  if (date == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(266, F("date cannot be NULL."));
#endif
  return TEB_Numbers::charInt(date, date + 4);
}

uint8_t TEB_Time::intMonth (const char* date) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Time::intMonth (const char* date)"));
  if (date == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(267, F("date cannot be NULL."));
#endif
  return TEB_Numbers::charInt(date + 5, date + 7);
}

uint8_t TEB_Time::intDay (const char* date) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Time::intDay (const char* date)"));
  if (date == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(268, F("date cannot be NULL."));
#endif
  return TEB_Numbers::charInt(date + 8, date + 10);
}

uint8_t TEB_Time::intHours (const char* time) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Time::intHours (const char* time)"));
  if (time == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(269, F("time cannot be NULL."));
#endif
  return TEB_Numbers::charInt(time, time + 2);
}

uint8_t TEB_Time::intMinutes (const char* time) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Time::intMinutes (const char* time)"));
  if (time == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(270, F("time cannot be NULL."));
#endif
  return TEB_Numbers::charInt(time + 3, time + 5);
}

uint8_t TEB_Time::intSeconds (const char* time) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Time::intSeconds (const char* time)"));
  if (time == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(271, F("time cannot be NULL."));
#endif
  return TEB_Numbers::charInt(time + 6, time + 8);
}

uint32_t TEB_Time::epoch1970 (uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint16_t year) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Time::epoch1970 (uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint16_t year)"));
  if (hours < 0 || 23 < hours) TEB_DevelopmentBoard::TEB_Debug::fatalError(272, F("hours must be >= 0 and <= 23."));
  if (minutes < 0 || 59 < minutes) TEB_DevelopmentBoard::TEB_Debug::fatalError(273, F("minutes must be >= 0 and <= 59."));
  if (seconds < 0 || 59 < seconds) TEB_DevelopmentBoard::TEB_Debug::fatalError(274, F("secons must be >= 0 and <= 59."));
  if (day < 1 || 31 < day) TEB_DevelopmentBoard::TEB_Debug::fatalError(275, F("day must be >= 1 and <= 31."));
  if (month < 1 || 12 < month) TEB_DevelopmentBoard::TEB_Debug::fatalError(9, F("month must be >= 1 and <= 12."));
  if (year < 1970 || 2105 < year) TEB_DevelopmentBoard::TEB_Debug::fatalError(254, F("year must be >= 1970 and <= 2105."));
#endif
  tmElements_t tm;
  tm.Second = seconds;
  tm.Minute = minutes;
  tm.Hour = hours;
  tm.Day = day;
  tm.Month = month;
  tm.Year = year - 1970;
  return (uint32_t)makeTime(tm);
}

uint32_t TEB_Time::epoch1970 (const char* dateTime) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Time::epoch1970 (const char* dateTime)"));
  if (dateTime == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(257, F("dateTime cannot be NULL."));
#endif
  uint8_t hh, mm, ss, day, month;
  uint16_t year;
  day = TEB_Numbers::charInt(dateTime, dateTime + 2);
  dateTime = dateTime + 2;
  while (*dateTime == ' ') dateTime++;
  if (dateTime[0] == 'J' && dateTime[1] == 'a') mm = 1;
  else if (dateTime[0] == 'F') month = 2;
  else if (dateTime[0] == 'M' && dateTime[2] == 'r') month = 3;
  else if (dateTime[0] == 'A' && dateTime[1] == 'p') month = 4;
  else if (dateTime[0] == 'M' && dateTime[2] == 'y') month = 5;
  else if (dateTime[1] == 'u' && dateTime[2] == 'n') month = 6;
  else if (dateTime[2] == 'l') month = 7;
  else if (dateTime[0] == 'A') month = 8;
  else if (dateTime[0] == 'S') month = 9;
  else if (dateTime[0] == 'O') month = 10;
  else if (dateTime[0] == 'N') month = 11;
  else if (dateTime[0] == 'D') month = 12;
  dateTime = dateTime + 3;
  while (*dateTime == ' ') dateTime++;
  year = TEB_Numbers::charInt(dateTime, dateTime + 4);
  dateTime = dateTime + 4;
  while (*dateTime == ' ') dateTime++;
  hh = TEB_Numbers::charInt(dateTime, dateTime + 2);
  dateTime = dateTime + 3;
  mm = TEB_Numbers::charInt(dateTime, dateTime + 2);
  dateTime = dateTime + 3;
  ss = TEB_Numbers::charInt(dateTime, dateTime + 2);
  return epoch1970(hh, mm, ss, day, month, year);
}

#ifdef TEB_DB_DEBUG
void TEB_Time::test () {
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_Time::test ()"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_DevelopmentBoard::TEB_Debug::print(F("TEB_Time"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  char date[] = "1994-11-15";
  char time[] = "08:12:31";
  char t[11];
  strDate(intDay(date), intMonth(date), intYear(date), t);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n")); TEB_DevelopmentBoard::TEB_Debug::print(t); TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
  strTime(intHours(time), intMinutes(time), intSeconds(time), t);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n")); TEB_DevelopmentBoard::TEB_Debug::print(t); TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n")); TEB_DevelopmentBoard::TEB_Debug::print(epoch1970("15 Nov 1994 08:12:31")); TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n")); TEB_DevelopmentBoard::TEB_Debug::print(epoch1970(0, 0, 0, 1, 1, 1970)); TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n")); TEB_DevelopmentBoard::TEB_Debug::print(epoch1970(23, 59, 59, 31, 12, 2105)); TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif