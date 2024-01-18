/*
  MIT License

  Copyright (c) 2024 TinyElectronicBlog

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

#include "TEB_TimeManagement.h"
#include "../String/TEB_String.h"
#include "../Number/TEB_Number.h"

TEB_small_int TEB_TimeManagement_first_weekday_year (TEB_medium_int year) {
  TEB_debug_function_start("TEB_TimeManagement_first_weekday_year");
  //Sunday = 1, Thursday = 5, ..., Saturday = 7
  TEB_medium_int reference_year = 1970;
  TEB_small_int reference_weekday = 5;  //1-1-1970 was Thursday
  while (year > reference_year) {
    if (TEB_TimeManagement_is_leap_year(reference_year) == 1) reference_weekday = reference_weekday + 2;
    else reference_weekday = reference_weekday + 1;
    if (reference_weekday > 7) reference_weekday = reference_weekday - 7;
    reference_year = reference_year + 1;
  }
  while (year < reference_year) {
    reference_year = reference_year - 1;
    if (TEB_TimeManagement_is_leap_year(reference_year) == 1) reference_weekday = reference_weekday - 2;
    else reference_weekday = reference_weekday - 1;
    if (reference_weekday < 1) reference_weekday = reference_weekday + 7;
  }
  return TEB_debug_function_end(reference_weekday);
}

TEB_bool TEB_TimeManagement_is_leap_year (TEB_medium_int year) {
  TEB_debug_function_start("TEB_TimeManagement_is_leap_year");
  if (year % 4 != 0) return TEB_debug_function_end(0);
  if (year % 100 != 0) return TEB_debug_function_end(1);
  if (year % 400 == 0) return TEB_debug_function_end(1);
  return TEB_debug_function_end(0);
}

TEB_small_u_int TEB_TimeManagement_days_of_month (TEB_small_u_int month,
                                                 TEB_bool is_a_leap_year) {
  TEB_debug_function_start("TEB_TimeManagement_days_of_month");
  if (month < 0 || month > 12) TEB_fatal_error(237, "Value not allowed for month.", 2);
  switch (month) {
    case 1:
      {
        return TEB_debug_function_end(31);
      }
    case 2:
      if (is_a_leap_year == 0) {
        return TEB_debug_function_end(28);
      } else {
        return TEB_debug_function_end(29);
      }
    case 3:
      {
        return TEB_debug_function_end(31);
      }
    case 4:
      {
        return TEB_debug_function_end(30);
      }
    case 5:
      {
        return TEB_debug_function_end(31);
      }
    case 6:
      {
        return TEB_debug_function_end(30);
      }
    case 7:
      {
        return TEB_debug_function_end(31);
      }
    case 8:
      {
        return TEB_debug_function_end(31);
      }
    case 9:
      {
        return TEB_debug_function_end(30);
      }
    case 10:
      {
        return TEB_debug_function_end(31);
      }
    case 11:
      {
        return TEB_debug_function_end(30);
      }
    case 12:
      {
        return TEB_debug_function_end(31);
      }
  }
  return TEB_debug_function_end(0);
}

TEB_time_t TEB_TimeManagement_time_to_epoch (const struct TEB_TimeManagement_struct* time_to_convert,
                                            TEB_medium_int initial_year_of_the_epoch) {
  TEB_debug_function_start("TEB_TimeManagement_time_to_epoch");
  if (time_to_convert == TEB_NULL_POINTER) TEB_fatal_error(238, "time_to_convert cannot be NULL.", 2);
  if (time_to_convert->second < 0 || time_to_convert->second > 59) TEB_fatal_error(239, "Value not allowed for time_to_convert->second.", 2);
  if (time_to_convert->minute < 0 || time_to_convert->minute > 59) TEB_fatal_error(240, "Value not allowed for time_to_convert->minute.", 2);
  if (time_to_convert->hour < 0 || time_to_convert->hour > 23) TEB_fatal_error(241, "Value not allowed for time_to_convert->hour.", 2);
  if (time_to_convert->day < 1 || time_to_convert->day > 31) TEB_fatal_error(242, "Value not allowed for time_to_convert->day.", 2);
  if (time_to_convert->month < 1 || time_to_convert->month > 12) TEB_fatal_error(243, "Value not allowed for time_to_convert->month.", 2);
  TEB_time_t r = 0;
  while (initial_year_of_the_epoch < time_to_convert->year) {
    if (TEB_TimeManagement_is_leap_year(initial_year_of_the_epoch) == 0) r = r + 3600 * 24 * 365;
    else r = r + 3600 * 24 * 366;
    initial_year_of_the_epoch = initial_year_of_the_epoch + 1;
  }
  TEB_small_u_int i2 = 1;
  TEB_bool k = TEB_TimeManagement_is_leap_year(time_to_convert->year);
  while (i2 < time_to_convert->month) {
    r = r + TEB_TimeManagement_days_of_month(i2, k) * 3600 * 24;
    i2 = i2 + 1;
  }
  r = r + 24 * 3600 * (time_to_convert->day - 1);
  r = r + 3600 * time_to_convert->hour;
  r = r + 60 * time_to_convert->minute;
  TEB_debug_function_end(0);
  return r + time_to_convert->second;
}

TEB_small_int TEB_TimeManagement_epoch_to_time (TEB_time_t epoch_to_convert,
                                               TEB_medium_int initial_year_of_the_epoch,
                                               struct TEB_TimeManagement_struct* time_converted) {
  TEB_debug_function_start("TEB_TimeManagement_epoch_to_time");
  if (epoch_to_convert < 0) TEB_fatal_error(244, "Value not allowed for epoch_to_convert.", 2);
  if (time_converted == TEB_NULL_POINTER) TEB_fatal_error(245, "time_converted cannot be NULL.", 2);
  TEB_time_t r = 0;
  TEB_time_t t;
  while (r <= epoch_to_convert) {
    if (TEB_TimeManagement_is_leap_year(initial_year_of_the_epoch) == 0) t = 365 * 24 * 3600;
    else t = 366 * 24 * 3600;
    r = r + t;
    initial_year_of_the_epoch = initial_year_of_the_epoch + 1;
  }
  r = r - t;
  initial_year_of_the_epoch = initial_year_of_the_epoch - 1;
  time_converted->year = initial_year_of_the_epoch;
  TEB_bool k = TEB_TimeManagement_is_leap_year(initial_year_of_the_epoch);
  initial_year_of_the_epoch = 1;
  while (r <= epoch_to_convert) {
    t = TEB_TimeManagement_days_of_month(initial_year_of_the_epoch, k);
    r = r + t * 24 * 3600;
    initial_year_of_the_epoch = initial_year_of_the_epoch + 1;
  }
  r = r - t * 24 * 3600;
  initial_year_of_the_epoch = initial_year_of_the_epoch - 1;
  time_converted->month = initial_year_of_the_epoch;
  initial_year_of_the_epoch = 1;
  while (r <= epoch_to_convert) {
    r = r + 24 * 3600;
    initial_year_of_the_epoch = initial_year_of_the_epoch + 1;
  }
  r = r - 24 * 3600;
  initial_year_of_the_epoch = initial_year_of_the_epoch - 1;
  time_converted->day = initial_year_of_the_epoch;
  initial_year_of_the_epoch = 0;
  while (r <= epoch_to_convert) {
    r = r + 3600;
    initial_year_of_the_epoch = initial_year_of_the_epoch + 1;
  }
  r = r - 3600;
  initial_year_of_the_epoch = initial_year_of_the_epoch - 1;
  time_converted->hour = initial_year_of_the_epoch;
  initial_year_of_the_epoch = 0;
  while (r <= epoch_to_convert) {
    r = r + 60;
    initial_year_of_the_epoch = initial_year_of_the_epoch + 1;
  }
  r = r - 60;
  initial_year_of_the_epoch = initial_year_of_the_epoch - 1;
  time_converted->minute = initial_year_of_the_epoch;
  time_converted->second = epoch_to_convert - r;
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_TimeManagement_weekday_from_epoch (TEB_time_t epoch,
                                                    TEB_medium_int initial_year_of_the_epoch,
                                                    TEB_small_int initial_weekday_of_the_epoch) {
  TEB_debug_function_start("TEB_TimeManagement_weekday_from_epoch");
  if (epoch < 0) TEB_fatal_error(246, "Value not allowed for epoch.", 2);
  if (initial_weekday_of_the_epoch < 1 || initial_weekday_of_the_epoch > 7) TEB_fatal_error(247, "Value not allowed for initial_weekday_of_the_epoch.", 2);
  struct TEB_TimeManagement_struct t;
  if (TEB_TimeManagement_epoch_to_time(epoch, initial_year_of_the_epoch, &t) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end(TEB_TimeManagement_weekday_from_date(t.year, t.month, t.day));
}

TEB_small_int TEB_TimeManagement_weekday_from_date (TEB_medium_int year,
                                                   TEB_small_u_int month,
                                                   TEB_small_u_int day) {
  TEB_debug_function_start("TEB_TimeManagement_weekday_from_date");
  if (day < 1 || day > 31) TEB_fatal_error(248, "Value not allowed for day.", 2);
  if (month < 1 || month > 12) TEB_fatal_error(249, "Value not allowed for month.", 2);
  //Sunday = 1, Thursday = 5, ..., Saturday = 7
  TEB_medium_int reference_year = 1970;
  TEB_small_int reference_weekday = 5;  //1-1-1970 was Thursday
  while (reference_year < year) {
    if (TEB_TimeManagement_is_leap_year(reference_year) == 0) {  //365%7 = 1
      reference_weekday = reference_weekday + 1;
    } else {  //366%7 = 1
      reference_weekday = reference_weekday + 2;
    }
    if (reference_weekday > 7) reference_weekday = reference_weekday - 7;
    reference_year = reference_year + 1;
  }
  while (reference_year > year) {
    if (TEB_TimeManagement_is_leap_year(reference_year - 1) == 0) {  //365%7 = 1
      reference_weekday = reference_weekday - 1;
    } else {  //366%7 = 1
      reference_weekday = reference_weekday - 2;
    }
    if (reference_weekday < 1) reference_weekday = reference_weekday + 7;
    reference_year = reference_year - 1;
  }
  //ora reference_year = year and reference_weekday is January 1 of year
  TEB_small_u_int m = 1;
  TEB_bool k = TEB_TimeManagement_is_leap_year(year);
  reference_year = 0;  //temp
  while (m < month) {
    reference_year = reference_year + TEB_TimeManagement_days_of_month(m, k);
    m = m + 1;
  }
  reference_year = reference_year + day - 1;  //giorni tra il 1 gennaio e la data inserita
  reference_year = reference_year % 7;
  reference_weekday = reference_weekday + reference_year;
  if (reference_weekday > 7) reference_weekday = reference_weekday - 7;
  return TEB_debug_function_end(reference_weekday);
}

TEB_bool TEB_TimeManagement_is_time_passed (const struct TEB_TimeManagement_struct* time_to_evaluate,
								            const struct TEB_TimeManagement_struct* reference_time) {
  TEB_debug_function_start("TEB_TimeManagement_is_time_passed");
  if (reference_time == TEB_NULL_POINTER) TEB_fatal_error(250, "reference_time cannot be NULL.", 2);
  if (reference_time->second < 0 || reference_time->second > 59) TEB_fatal_error(251, "Value not allowed for reference_time->second.", 2);
  if (reference_time->minute < 0 || reference_time->minute > 59) TEB_fatal_error(252, "Value not allowed for reference_time->minute.", 2);
  if (reference_time->hour < 0 || reference_time->hour > 23) TEB_fatal_error(253, "Value not allowed for reference_time->hour.", 2);
  if (reference_time->day < 1 || reference_time->day > 31) TEB_fatal_error(254, "Value not allowed for reference_time->day.", 2);
  if (reference_time->month < 1 || reference_time->month > 12) TEB_fatal_error(255, "Value not allowed for reference_time->month.", 2);
  if (time_to_evaluate == TEB_NULL_POINTER) TEB_fatal_error(256, "time_to_evaluate cannot be NULL.", 2);
  if (time_to_evaluate->second < 0 || time_to_evaluate->second > 59) TEB_fatal_error(257, "Value not allowed for time_to_evaluate->second.", 2);
  if (time_to_evaluate->minute < 0 || time_to_evaluate->minute > 59) TEB_fatal_error(258, "Value not allowed for time_to_evaluate->minute.", 2);
  if (time_to_evaluate->hour < 0 || time_to_evaluate->hour > 23) TEB_fatal_error(259, "Value not allowed for time_to_evaluate->hour.", 2);
  if (time_to_evaluate->day < 1 || time_to_evaluate->day > 31) TEB_fatal_error(260, "Value not allowed for time_to_evaluate->day.", 2);
  if (time_to_evaluate->month < 1 || time_to_evaluate->month > 12) TEB_fatal_error(261, "Value not allowed for time_to_evaluate->month.", 2);
  if (reference_time->year > time_to_evaluate->year) {
    return TEB_debug_function_end(1);
  } else if (reference_time->year < time_to_evaluate->year) {
    return TEB_debug_function_end(0);
  }
  if (reference_time->month > time_to_evaluate->month) {
    return TEB_debug_function_end(1);
  } else if (reference_time->month < time_to_evaluate->month) {
    return TEB_debug_function_end(0);
  }
  if (reference_time->day > time_to_evaluate->day) {
    return TEB_debug_function_end(1);
  } else if (reference_time->day < time_to_evaluate->day) {
    return TEB_debug_function_end(0);
  }
  if (reference_time->hour > time_to_evaluate->hour) {
    return TEB_debug_function_end(1);
  } else if (reference_time->hour < time_to_evaluate->hour) {
    return TEB_debug_function_end(0);
  }
  if (reference_time->minute > time_to_evaluate->minute) {
    return TEB_debug_function_end(1);
  } else if (reference_time->minute < time_to_evaluate->minute) {
    return TEB_debug_function_end(0);
  }
  if (reference_time->second > time_to_evaluate->second) {
    return TEB_debug_function_end(1);
  } else if (reference_time->second < time_to_evaluate->second) {
    return TEB_debug_function_end(0);
  }
  return TEB_debug_function_end(0);
}

TEB_small_int TEB_TimeManagement_is_dst_time (const struct TEB_TimeManagement_struct* time_to_evaluate,
                                             const TEB_small_int dst_start[5], //month, weekday, th_weekday, hour, minute
                                             const TEB_small_int dst_end[5]) {//month, weekday, th_weekday, hour, minute
                                                                                /* 
dst_start is considered standard time, while dst_end is considered daylight saving time.
the function returns:
- 0 if dst_start[0] and dst_end[0] are both 0 (regardless of the other input parameters) (state that does not adopt daylight saving time);
- 1 if dst_start[0] and dst_end[0] are both -1 (regardless of other input parameters) (state that always adopts daylight saving time)
- 0 if time is solar (if (epoch >= dst_start_epoch && epoch < dst_end_epoch) == false)
- 1 if time is legal (if (epoch >= dst_start_epoch && epoch < dst_end_epoch) == true)
- -1 if it is not possible to make the evaluation because the time falls in one of these (extremes included) ambiguous intervals [dst_start_epoch : dst_start_epoch + 3599 seconds] or [dst_end_epoch(solar) : dst_end_epoch(solar) + 3599 seconds)] */
  TEB_debug_function_start("TEB_TimeManagement_is_dst_time");
  if (time_to_evaluate == TEB_NULL_POINTER) TEB_fatal_error(262, "time_to_evaluate cannot be NULL.", 2);
  if (time_to_evaluate->second < 0 || time_to_evaluate->second > 59) TEB_fatal_error(263, "Value not allowed for time_to_evaluate->second.", 2);
  if (time_to_evaluate->minute < 0 || time_to_evaluate->minute > 59) TEB_fatal_error(264, "Value not allowed for time_to_evaluate->minute.", 2);
  if (time_to_evaluate->hour < 0 || time_to_evaluate->hour > 23) TEB_fatal_error(265, "Value not allowed for time_to_evaluate->hour.", 2);
  if (time_to_evaluate->day < 1 || time_to_evaluate->day > 31) TEB_fatal_error(266, "Value not allowed for time_to_evaluate->day.", 2);
  if (time_to_evaluate->month < 1 || time_to_evaluate->month > 12) TEB_fatal_error(267, "Value not allowed for time_to_evaluate->month.", 2);
  if (dst_start == TEB_NULL_POINTER) TEB_fatal_error(268, "time_to_evaluate cannot be NULL.", 2);
  if (dst_start[0] < -1 || dst_start[0] > 12) TEB_fatal_error(269, "Value not allowed for dst_start[0].", 2);
  if (dst_start[1] < 1 || dst_start[1] > 7) TEB_fatal_error(270, "Value not allowed for dst_start[1].", 2);
  if (dst_start[2] < -5 || dst_start[2] > 5) TEB_fatal_error(271, "Value not allowed for dst_start[2].", 2);
  if (dst_start[3] < 0 || dst_start[3] > 23) TEB_fatal_error(272, "Value not allowed for dst_start[3].", 2);
  if (dst_start[4] < 0 || dst_start[4] > 59) TEB_fatal_error(273, "Value not allowed for dst_start[4].", 2);
  if (dst_end == TEB_NULL_POINTER) TEB_fatal_error(274, "time_to_evaluate cannot be NULL.", 2);
  if (dst_end[0] < -1 || dst_end[0] > 12) TEB_fatal_error(275, "Value not allowed for dst_end[0].", 2);
  if (dst_end[1] < 1 || dst_end[1] > 7) TEB_fatal_error(276, "Value not allowed for dst_end[1].", 2);
  if (dst_end[2] < -5 || dst_end[2] > 5) TEB_fatal_error(277, "Value not allowed for dst_end[2].", 2);
  if (dst_end[3] < 0 || dst_end[3] > 23) TEB_fatal_error(278, "Value not allowed for dst_end[3].", 2);
  if (dst_end[4] < 0 || dst_end[4] > 59) TEB_fatal_error(279, "Value not allowed for dst_end[4].", 2);
  if (dst_start[0] == 0 && dst_end[0] != 0 || dst_start[0] != 0 && dst_end[0] == 0) TEB_fatal_error(280, "Value not allowed for dst_start[0] and dst_end[0].", 2);
  if (dst_start[0] == -1 && dst_end[0] != -1 || dst_start[0] != -1 && dst_end[0] == -1) TEB_fatal_error(281, "Value not allowed for dst_start[0] and dst_end[0].", 2);
  if (dst_start[0] == 0 && dst_end[0] == 0) {return TEB_debug_function_end(0);}
  if (dst_start[0] == -1 && dst_end[0] == -1) {return TEB_debug_function_end(1);}
  TEB_small_int initial_weekday_of_the_epoch = TEB_TimeManagement_first_weekday_year(time_to_evaluate->year);
  TEB_time_t epoch = TEB_TimeManagement_time_to_epoch(time_to_evaluate, time_to_evaluate->year);
  TEB_time_t dst_start_epoch = TEB_TimeManagement_get_dst_epoch(time_to_evaluate->year,
                                                                (TEB_small_u_int)dst_start[0],
                                                                (TEB_small_u_int)dst_start[1],
                                                                dst_start[2],
                                                                (TEB_small_u_int)dst_start[3],
                                                                (TEB_small_u_int)dst_start[4],
                                                                time_to_evaluate->year,
                                                                initial_weekday_of_the_epoch,
                                                                0);
  TEB_time_t dst_end_epoch = TEB_TimeManagement_get_dst_epoch(time_to_evaluate->year,
                                                              (TEB_small_u_int)dst_end[0],
                                                              (TEB_small_u_int)dst_end[1],
                                                              dst_end[2],
                                                              (TEB_small_u_int)dst_end[3],
                                                              (TEB_small_u_int)dst_end[4],
                                                              time_to_evaluate->year,
                                                              initial_weekday_of_the_epoch,
                                                              1);
  if ((dst_start_epoch <= epoch && epoch <= dst_start_epoch + 3599) || (dst_end_epoch <= epoch && epoch <= dst_end_epoch + 3599)) {return TEB_debug_function_end(-1);}
  if ((epoch >= dst_start_epoch && epoch < dst_end_epoch) == 1) {return TEB_debug_function_end(1);}
  return TEB_debug_function_end(0);
}

TEB_bool TEB_TimeManagement_is_dst_epoch (TEB_time_t epoch_to_evaluate,
                                         TEB_time_t dst_start_epoch,
                                         TEB_time_t dst_end_epoch,
                                         TEB_bool dst_end_epoch_is_standard_time) {
  TEB_debug_function_start("TEB_TimeManagement_is_dst_epoch");
  if (epoch_to_evaluate < 0) TEB_fatal_error(282, "Value not allowed for epoch_to_evaluate.", 2);
  if (dst_start_epoch < 0) TEB_fatal_error(283, "Value not allowed for dst_start_epoch.", 2);
  if (dst_end_epoch < 0) TEB_fatal_error(284, "Value not allowed for dst_end_epoch.", 2);
  if (dst_end_epoch_is_standard_time == 0) dst_end_epoch = dst_end_epoch - 3600;  //conversion from daylight saving time to solar time
  if (dst_start_epoch <= epoch_to_evaluate && epoch_to_evaluate < dst_end_epoch) {
    return TEB_debug_function_end(1);
  } else {
    return TEB_debug_function_end(0);
  }
}

TEB_time_t TEB_TimeManagement_get_dst_epoch (TEB_medium_int year,
                                            TEB_small_u_int month,
                                            TEB_small_u_int weekday,
                                            TEB_small_int th_weekday,
                                            TEB_small_u_int hour,
                                            TEB_small_u_int minute,
                                            TEB_medium_int initial_year_of_the_epoch,
                                            TEB_small_int initial_weekday_of_the_epoch,
                                            TEB_bool get_dst_end_in_standard_time) {
  TEB_debug_function_start("TEB_TimeManagement_get_dst_epoch");
  if (initial_weekday_of_the_epoch < 1 || initial_weekday_of_the_epoch > 7) TEB_fatal_error(285, "Value not allowed for initial_weekday_of_the_epoch.", 2);
  if (weekday < 1 || weekday > 7) TEB_fatal_error(286, "Value not allowed for weekday.", 2);
  if (month < 1 || month > 12) TEB_fatal_error(287, "Value not allowed for month.", 2);
  if (th_weekday < -5 || th_weekday > 5) TEB_fatal_error(288, "Value not allowed for th_weekday.", 2);
  if (minute < 0 || minute > 59) TEB_fatal_error(289, "Value not allowed for minute.", 2);
  if (hour < 0 || hour > 23) TEB_fatal_error(290, "Value not allowed for hour.", 2);
  TEB_small_int day;
  if (th_weekday > 0) {
    day = TEB_TimeManagement_weekday_from_date(year, month, 1);  //weekday of the first of the month
    if (weekday >= day) day = 1 + (weekday - day);
    else day = 8 - (day - weekday);
    //now day is the first dst_start_weekday of the month
    day = day + 7 * (th_weekday - 1);
  } else {
    TEB_small_int l = TEB_TimeManagement_days_of_month(month, TEB_TimeManagement_is_leap_year(year));
    day = TEB_TimeManagement_weekday_from_date(year, month, l);  //weekday of the last of the month
    if (weekday <= day) day = l - (day - weekday);
    else day = l + (weekday - day) - 7;
    //now day is the last dst_start_weekday of the month
    day = day + 7 * (th_weekday + 1);
  }
  struct TEB_TimeManagement_struct time;
  time.second = 0;
  time.minute = minute;
  time.hour = hour;
  time.day = day;
  time.month = month;
  time.year = year;
  TEB_time_t r = TEB_TimeManagement_time_to_epoch(&time, initial_year_of_the_epoch);
  if (get_dst_end_in_standard_time != 0) r = r - 3600;
  TEB_debug_function_end(0);
  return r;
}

TEB_time_t TEB_TimeManagement_utc_to_local_epoch (TEB_time_t epoch_to_convert,
                                                 TEB_small_int time_zone_utc_offset_hour,
                                                 TEB_small_int time_zone_utc_offset_minute) {
  TEB_debug_function_start("TEB_TimeManagement_utc_to_local_epoch");
  if (epoch_to_convert < 0) TEB_fatal_error(291, "Value not allowed for epoch_to_convert.", 2);
  if (time_zone_utc_offset_minute < -59 || time_zone_utc_offset_minute > 59) TEB_fatal_error(292, "Value not allowed for time_zone_utc_offset_minute.", 2);
  if (time_zone_utc_offset_hour < -23 || time_zone_utc_offset_hour > 23) TEB_fatal_error(293, "Value not allowed for time_zone_utc_offset_hour.", 2);
  epoch_to_convert = epoch_to_convert + ((TEB_big_int)time_zone_utc_offset_hour * 3600 + (TEB_big_int)time_zone_utc_offset_minute * 60);
  TEB_debug_function_end(0);
  return epoch_to_convert;
}

TEB_time_t TEB_TimeManagement_local_to_utc_epoch (TEB_time_t epoch_to_convert,
                                                 TEB_small_int time_zone_utc_offset_hour,
                                                 TEB_small_int time_zone_utc_offset_minute) {
  TEB_debug_function_start("TEB_TimeManagement_local_to_utc_epoch");
  if (epoch_to_convert < 0) TEB_fatal_error(294, "Value not allowed for epoch_to_convert.", 2);
  if (time_zone_utc_offset_minute < -59 || time_zone_utc_offset_minute > 59) TEB_fatal_error(295, "Value not allowed for time_zone_utc_offset_minute.", 2);
  if (time_zone_utc_offset_hour < -23 || time_zone_utc_offset_hour > 23) TEB_fatal_error(296, "Value not allowed for time_zone_utc_offset_hour.", 2);
  epoch_to_convert = epoch_to_convert - ((TEB_big_int)time_zone_utc_offset_hour * 3600 + (TEB_big_int)time_zone_utc_offset_minute * 60);
  TEB_debug_function_end(0);
  return epoch_to_convert;
}

TEB_char* TEB_TimeManagement_str_date (TEB_small_u_int day,
                                      TEB_small_u_int month,
                                      TEB_medium_u_int year,
									  TEB_char* date_buffer) {
  TEB_debug_function_start("TEB_TimeManagement_str_date");
  if (day < 1 || 31 < day) TEB_fatal_error(297, "day must be >= 1 and <= 31.", 2);
  if (month < 1 || 12 < month) TEB_fatal_error(298, "month must be >= 1 and <= 12.", 2);
  if (date_buffer == TEB_NULL_POINTER) TEB_fatal_error(299, "date_buffer cannot be NULL.", 2);
  if (year < 0) {
    *date_buffer = '-';
    date_buffer = date_buffer + 1;
  }
  date_buffer = TEB_String_int_str(year, date_buffer);
  *date_buffer = '-';
  date_buffer = date_buffer + 1;
  if (month < 10) {
    *date_buffer = '0';
    date_buffer = date_buffer + 1;
  }
  date_buffer = TEB_String_int_str(month, date_buffer);
  *date_buffer = '-';
  date_buffer = date_buffer + 1;
  if (day < 10) {
    *date_buffer = '0';
    date_buffer = date_buffer + 1;
  }
  TEB_char* r = TEB_String_int_str(day, date_buffer);
  TEB_debug_function_end(0);
  return r;
}

TEB_char* TEB_TimeManagement_str_time (TEB_small_u_int hour,
                                      TEB_small_u_int minute,
                                      TEB_small_u_int second, 
									  TEB_char* time_buffer) {
  TEB_debug_function_start("TEB_TimeManagement_str_time");

  if (hour < 0 || 23 < hour) TEB_fatal_error(300, "hour must be >= 0 and <= 23.", 2);
  if (minute < 0 || 59 < minute) TEB_fatal_error(301, "minute must be >= 0 and <= 59.", 2);
  if (second < 0 || 59 < second) TEB_fatal_error(302, "second must be >= 0 and <= 59.", 2);
  if (time_buffer == TEB_NULL_POINTER) TEB_fatal_error(303, "time_buffer cannot be NULL.", 2);
  if (hour < 10) {
    *time_buffer = '0';
    time_buffer = time_buffer + 1;
  }
  time_buffer = TEB_String_int_str(hour, time_buffer);
  *time_buffer = ':';
  time_buffer = time_buffer + 1;
  if (minute < 10) {
    *time_buffer = '0';
    time_buffer = time_buffer + 1;
  }
  time_buffer = TEB_String_int_str(minute, time_buffer);
  *time_buffer = ':';
  time_buffer = time_buffer + 1;
  if (second < 10) {
    *time_buffer = '0';
    time_buffer = time_buffer + 1;
  }
  TEB_char* r = TEB_String_int_str(second, time_buffer);
  TEB_debug_function_end(0);
  return r;
}

TEB_medium_int TEB_TimeManagement_str_int_y (const TEB_char* date) {
  TEB_debug_function_start("TEB_TimeManagement_str_int_y");
  if (date == TEB_NULL_POINTER) TEB_fatal_error(304, "date cannot be NULL.", 2);
  TEB_bool n = 0;
  if (*date == '-') {
    n = 1;
    date = date + 1;
  }
  const TEB_char* end = date;
  while (TEB_Number_char_digit(*end) != -1) end = end + 1;
  TEB_medium_int r = TEB_Number_str_int2(date, end);
  if (n != 0) r = r * -1;
  TEB_debug_function_end(0);
  return r;
}

TEB_small_u_int TEB_TimeManagement_str_int_mon (const TEB_char* date) {
  TEB_debug_function_start("TEB_TimeManagement_str_int_mon");
  if (date == TEB_NULL_POINTER) TEB_fatal_error(305, "date cannot be NULL.", 2);
  if (*date == '-') date = date + 1;
  while (*date != '-') date = date + 1;
  TEB_small_u_int r = TEB_Number_str_int2(date + 1, date + 3);
  return TEB_debug_function_end(r);
}

TEB_small_u_int TEB_TimeManagement_str_int_d (const TEB_char* date) {
  TEB_debug_function_start("TEB_TimeManagement_str_int_d");
  if (date == TEB_NULL_POINTER) TEB_fatal_error(306, "date cannot be NULL.", 2);
  if (*date == '-') date = date + 1;
  while (*date != '-') date = date + 1;
  TEB_small_u_int r = TEB_Number_str_int2(date + 4, date + 6);
  return TEB_debug_function_end(r);
}

TEB_small_u_int TEB_TimeManagement_str_int_h (const TEB_char* time) {
  TEB_debug_function_start("TEB_TimeManagement_str_int_h");
  if (time == TEB_NULL_POINTER) TEB_fatal_error(307, "time cannot be NULL.", 2);
  TEB_small_u_int r = TEB_Number_str_int2(time, time + 2);
  return TEB_debug_function_end(r);
}

TEB_small_u_int TEB_TimeManagement_str_int_min (const TEB_char* time) {
  TEB_debug_function_start("TEB_TimeManagement_str_int_min");
  if (time == TEB_NULL_POINTER) TEB_fatal_error(308, "time cannot be NULL.", 2);
  TEB_small_u_int r = TEB_Number_str_int2(time + 3, time + 5);
  return TEB_debug_function_end(r);
}

TEB_small_u_int TEB_TimeManagement_str_int_s (const TEB_char* time) {
  TEB_debug_function_start("TEB_TimeManagement_str_int_s");
  if (time == TEB_NULL_POINTER) TEB_fatal_error(309, "time cannot be NULL.", 2);
  TEB_small_u_int r = TEB_Number_str_int2(time + 6, time + 8);
  return TEB_debug_function_end(r);
}

TEB_time_t TEB_TimeManagement_http_date_to_epoch (const TEB_char* http_date_to_convert,
                                                 TEB_medium_int initial_year_of_the_epoch) {
  TEB_debug_function_start("TEB_TimeManagement_http_date_to_epoch");
  if (http_date_to_convert == TEB_NULL_POINTER) TEB_fatal_error(310, "http_date_to_convert cannot be NULL.", 2);
  struct TEB_TimeManagement_struct time;
  time.day = TEB_Number_str_int2(http_date_to_convert, http_date_to_convert + 2);
  http_date_to_convert = http_date_to_convert + 2;
  while (*http_date_to_convert == ' ') http_date_to_convert = http_date_to_convert + 1;
  if (http_date_to_convert[0] == 'J' && http_date_to_convert[1] == 'a') time.month = 1;
  else if (http_date_to_convert[0] == 'F') time.month = 2;
  else if (http_date_to_convert[0] == 'M' && http_date_to_convert[2] == 'r') time.month = 3;
  else if (http_date_to_convert[0] == 'A' && http_date_to_convert[1] == 'p') time.month = 4;
  else if (http_date_to_convert[0] == 'M' && http_date_to_convert[2] == 'y') time.month = 5;
  else if (http_date_to_convert[1] == 'u' && http_date_to_convert[2] == 'n') time.month = 6;
  else if (http_date_to_convert[2] == 'l') time.month = 7;
  else if (http_date_to_convert[0] == 'A') time.month = 8;
  else if (http_date_to_convert[0] == 'S') time.month = 9;
  else if (http_date_to_convert[0] == 'O') time.month = 10;
  else if (http_date_to_convert[0] == 'N') time.month = 11;
  else if (http_date_to_convert[0] == 'D') time.month = 12;
  http_date_to_convert = http_date_to_convert + 3;
  while (*http_date_to_convert == ' ') http_date_to_convert = http_date_to_convert + 1;
  time.year = TEB_Number_str_int2(http_date_to_convert, http_date_to_convert + 4);
  http_date_to_convert = http_date_to_convert + 4;
  while (*http_date_to_convert == ' ') http_date_to_convert = http_date_to_convert + 1;
  time.hour = TEB_Number_str_int2(http_date_to_convert, http_date_to_convert + 2);
  http_date_to_convert = http_date_to_convert + 3;
  time.minute = TEB_Number_str_int2(http_date_to_convert, http_date_to_convert + 2);
  http_date_to_convert = http_date_to_convert + 3;
  time.second = TEB_Number_str_int2(http_date_to_convert, http_date_to_convert + 2);
  TEB_time_t r = TEB_TimeManagement_time_to_epoch(&time, initial_year_of_the_epoch);
  TEB_debug_function_end(0);
  return r;
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
static void TEB_TimeManagement_function_end(const TEB_char* f_name, TEB_bool ok) {
  if (ok == 0) {
    TEB_debug_print("\n");
    TEB_debug_print(f_name);
    TEB_debug_print(" ko");
  } else {
    TEB_debug_print("\n");
    TEB_debug_print(f_name);
    TEB_debug_print(" ok");
  }
}

TEB_small_int TEB_TimeManagement_test() {
  TEB_debug_function_start("TEB_TimeManagement_test");

  if (TEB_TimeManagement_first_weekday_year(2060) == 5 && TEB_TimeManagement_first_weekday_year(1940) == 2) TEB_TimeManagement_function_end("TEB_TimeManagement_first_weekday_year", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_first_weekday_year", 0);
    return TEB_debug_function_end(-1);
  }

  if (TEB_TimeManagement_get_dst_epoch(2023, 3, 1, -1, 2, 0, 1970, 5, 0) == 1679796000) TEB_TimeManagement_function_end("TEB_TimeManagement_get_dst_epoch", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_get_dst_epoch", 0);
    return TEB_debug_function_end(-2);
  }

  struct TEB_TimeManagement_struct time1;
  time1.second = 30;
  time1.minute = 30;
  time1.hour = 12;
  time1.day = 6;
  time1.month = 5;
  time1.year = 2023;
  struct TEB_TimeManagement_struct time2;
  time2.second = 30;
  time2.minute = 30;
  time2.hour = 12;
  time2.day = 13;
  time2.month = 5;
  time2.year = 2023;
  struct TEB_TimeManagement_struct time3;
  time3.second = 30;
  time3.minute = 30;
  time3.hour = 12;
  time3.day = 30;
  time3.month = 5;
  time3.year = 2023;
  TEB_small_int dst_start[5], dst_end[5];
  dst_start[0] = 5;
  dst_start[1] = 1;
  dst_start[2] = 1;
  dst_start[3] = 12;
  dst_start[4] = 0;
  dst_end[0] = 5;
  dst_end[1] = 1;
  dst_end[2] = -1;
  dst_end[3] = 12;
  dst_end[4] = 0;
  if (TEB_TimeManagement_is_dst_time(&time1, dst_start, dst_end) == 0 && TEB_TimeManagement_is_dst_time(&time2, dst_start, dst_end) == 1 && TEB_TimeManagement_is_dst_time(&time3, dst_start, dst_end) == 0) TEB_TimeManagement_function_end("TEB_TimeManagement_is_dst_time", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_is_dst_time", 0);
    return TEB_debug_function_end(-3);
  }

  if (TEB_TimeManagement_is_leap_year(2023) == 0 && TEB_TimeManagement_is_leap_year(2024) == 1) TEB_TimeManagement_function_end("TEB_TimeManagement_is_leap_year", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_is_leap_year", 0);
    return TEB_debug_function_end(-4);
  }

  if (TEB_TimeManagement_days_of_month(2, 0) == 28 && TEB_TimeManagement_days_of_month(2, 1) == 29) TEB_TimeManagement_function_end("TEB_TimeManagement_days_of_month", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_days_of_month", 0);
    return TEB_debug_function_end(-5);
  }

  if (TEB_TimeManagement_time_to_epoch(&time1, 1970) == 1683376230) TEB_TimeManagement_function_end("TEB_TimeManagement_time_to_epoch", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_time_to_epoch", 0);
    return TEB_debug_function_end(-6);
  }

  if (TEB_TimeManagement_epoch_to_time(1683376230, 1970, &time2) == 1 && time1.second == time2.second && time1.minute == time2.minute && time1.hour == time2.hour && time1.day == time2.day && time1.month == time2.month && time1.year == time2.year) TEB_TimeManagement_function_end("TEB_TimeManagement_epoch_to_time", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_epoch_to_time", 0);
    return TEB_debug_function_end(-7);
  }

  if (TEB_TimeManagement_weekday_from_epoch(1683376230, 1970, 5) == 7) TEB_TimeManagement_function_end("TEB_TimeManagement_weekday_from_epoch", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_weekday_from_epoch", 0);
    return TEB_debug_function_end(-8);
  }

  if (TEB_TimeManagement_weekday_from_date(2023, 5, 6) == 7) TEB_TimeManagement_function_end("TEB_TimeManagement_weekday_from_date", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_weekday_from_date", 0);
    return TEB_debug_function_end(-9);
  }

  if (TEB_TimeManagement_is_time_passed(&time1, &time2) == 0) TEB_TimeManagement_function_end("TEB_TimeManagement_is_time_passed", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_is_time_passed", 0);
    return TEB_debug_function_end(-10);
  }

  TEB_char b[13];
  TEB_TimeManagement_str_date(11, 10, 2023, b);
  if (TEB_String_equals2(b, "2023-10-11") == 1) TEB_TimeManagement_function_end("TEB_TimeManagement_str_date", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_str_date", 0);
    return TEB_debug_function_end(-11);
  }

  if (TEB_TimeManagement_str_int_y(b) == 2023) TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_y", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_y", 0);
    return TEB_debug_function_end(-12);
  }

  if (TEB_TimeManagement_str_int_mon(b) == 10) TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_mon", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_mon", 0);
    return TEB_debug_function_end(-13);
  }

  if (TEB_TimeManagement_str_int_d(b) == 11) TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_d", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_d", 0);
    return TEB_debug_function_end(-14);
  }

  TEB_TimeManagement_str_time(10, 18, 45, b);
  if (TEB_String_equals2(b, "10:18:45") == 1) TEB_TimeManagement_function_end("TEB_TimeManagement_str_time", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_str_time", 0);
    return TEB_debug_function_end(-15);
  }

  if (TEB_TimeManagement_str_int_h(b) == 10) TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_h", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_h", 0);
    return TEB_debug_function_end(-16);
  }

  if (TEB_TimeManagement_str_int_min(b) == 18) TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_min", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_min", 0);
    return TEB_debug_function_end(-17);
  }

  if (TEB_TimeManagement_str_int_s(b) == 45) TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_s", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_str_int_s", 0);
    return TEB_debug_function_end(-18);
  }

  if (TEB_TimeManagement_http_date_to_epoch("15 Nov 1994 08:12:31", 1970) == 784887151) TEB_TimeManagement_function_end("TEB_TimeManagement_http_date_to_epoch", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_http_date_to_epoch", 0);
    return TEB_debug_function_end(-19);
  }

  if (TEB_TimeManagement_is_dst_epoch(1686816000, 1678867200, 1697356800, 0) == 1) TEB_TimeManagement_function_end("TEB_TimeManagement_is_dst_epoch", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_is_dst_epoch", 0);
    return TEB_debug_function_end(-20);
  }

  if (TEB_TimeManagement_get_dst_epoch(2023, 10, 5, 1, 2, 0, 1970, 5, 0) == 1696471200) TEB_TimeManagement_function_end("TEB_TimeManagement_get_dst_epoch", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_get_dst_epoch", 0);
    return TEB_debug_function_end(-21);
  }

  if (TEB_TimeManagement_local_to_utc_epoch(TEB_TimeManagement_utc_to_local_epoch(1696471200, 5, 15), 5, 15) == 1696471200) TEB_TimeManagement_function_end("TEB_TimeManagement_local_to_utc_epoch and TEB_TimeManagement_utc_to_local_epoch", 1);
  else {
    TEB_TimeManagement_function_end("TEB_TimeManagement_local_to_utc_epoch and TEB_TimeManagement_utc_to_local_epoch", 0);
    return TEB_debug_function_end(-22);
  }

  return TEB_debug_function_end(1);
}
#endif