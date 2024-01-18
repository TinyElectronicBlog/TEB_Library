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

#include "TEB_TimeZoneDST.h"
#include "../String/TEB_String.h"
#include "../Number/TEB_Number.h"

TEB_small_int TEB_TimeZoneDST_struct_init (struct TEB_TimeZoneDST_struct* tz_dst_to_init,
                                          const char* time_zone_database_name,
                                          TEB_small_int time_zone_utc_offset[2],
                                          TEB_small_int dst_start[5],
                                          TEB_small_int dst_end[5]) {
  TEB_debug_function_start("TEB_TimeZoneDST_struct_init");
  if (tz_dst_to_init == TEB_NULL_POINTER) TEB_fatal_error(311, "tz_dst_to_init cannot be NULL.", 2);
  if (time_zone_database_name == TEB_NULL_POINTER) TEB_fatal_error(312, "time_zone_database_name cannot be NULL.", 2);
  if (time_zone_utc_offset == TEB_NULL_POINTER) TEB_fatal_error(313, "time_zone_utc_offset cannot be NULL.", 2);
  if (dst_start == TEB_NULL_POINTER) TEB_fatal_error(314, "dst_start cannot be NULL.", 2);
  if (dst_end == TEB_NULL_POINTER) TEB_fatal_error(315, "dst_end cannot be NULL.", 2);
  if (time_zone_utc_offset[1] < -59 || time_zone_utc_offset[1] > 59) TEB_fatal_error(316, "Value not allowed for time_zone_utc_offset[1].", 2);
  if (time_zone_utc_offset[0] < -23 || time_zone_utc_offset[0] > 23) TEB_fatal_error(317, "Value not allowed for time_zone_utc_offset[0].", 2);
  if (dst_start[0] < -1 || dst_start[0] > 12) TEB_fatal_error(318, "Value not allowed for dst_start[0].", 2);
  if (dst_start[1] < 1 || dst_start[1] > 7) TEB_fatal_error(319, "Value not allowed for dst_start[1].", 2);
  if (dst_start[2] < -5 || dst_start[2] > 5) TEB_fatal_error(320, "Value not allowed for dst_start[2].", 2);
  if (dst_start[3] < 0 || dst_start[3] > 23) TEB_fatal_error(321, "Value not allowed for dst_start[3].", 2);
  if (dst_start[4] < 0 || dst_start[4] > 59) TEB_fatal_error(322, "Value not allowed for dst_start[4].", 2);
  if (dst_end[0] < -1 || dst_end[0] > 12) TEB_fatal_error(323, "Value not allowed for dst_end[0].", 2);
  if (dst_end[1] < 1 || dst_end[1] > 7) TEB_fatal_error(324, "Value not allowed for dst_end[1].", 2);
  if (dst_end[2] < -5 || dst_end[2] > 5) TEB_fatal_error(325, "Value not allowed for dst_end[2].", 2);
  if (dst_end[3] < 0 || dst_end[3] > 23) TEB_fatal_error(326, "Value not allowed for dst_end[3].", 2);
  if (dst_end[4] < 0 || dst_end[4] > 59) TEB_fatal_error(327, "Value not allowed for dst_end[4].", 2);
  TEB_String_append2(tz_dst_to_init->time_zone_database_name, time_zone_database_name);
  tz_dst_to_init->time_zone_utc_offset[0] = time_zone_utc_offset[0];
  tz_dst_to_init->time_zone_utc_offset[1] = time_zone_utc_offset[1];
  tz_dst_to_init->dst_start[0] = dst_start[0];
  tz_dst_to_init->dst_start[1] = dst_start[1];
  tz_dst_to_init->dst_start[2] = dst_start[2];
  tz_dst_to_init->dst_start[3] = dst_start[3];
  tz_dst_to_init->dst_start[4] = dst_start[4];
  tz_dst_to_init->dst_end[0] = dst_end[0];
  tz_dst_to_init->dst_end[1] = dst_end[1];
  tz_dst_to_init->dst_end[2] = dst_end[2];
  tz_dst_to_init->dst_end[3] = dst_end[3];
  tz_dst_to_init->dst_end[4] = dst_end[4];
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_TimeZoneDST_set_epoch (struct TEB_Clock_struct* clock_to_adjust,
                                        const struct TEB_TimeZoneDST_struct* time_zone_dst_to_set,
                                        TEB_time_t epoch_to_set_in_seconds,
                                        TEB_bool epoch_to_set_is_dst,
                                        TEB_bool epoch_to_set_is_utc) {
  TEB_debug_function_start("TEB_TimeZoneDST_set_epoch");
  if (clock_to_adjust == TEB_NULL_POINTER) TEB_fatal_error(328, "clock_to_adjust cannot be NULL.", 2);
  if (time_zone_dst_to_set == TEB_NULL_POINTER) TEB_fatal_error(329, "time_zone_dst_to_set cannot be NULL.", 2);
  if (epoch_to_set_in_seconds < 0) TEB_fatal_error(330, "Value not allowed for epoch_to_set_in_seconds.", 2);
  if (time_zone_dst_to_set->time_zone_database_name == TEB_NULL_POINTER) TEB_fatal_error(331, "time_zone_dst_to_set->time_zone_database_name cannot be NULL.", 2);
  if (time_zone_dst_to_set->time_zone_utc_offset == TEB_NULL_POINTER) TEB_fatal_error(332, "time_zone_dst_to_set->time_zone_utc_offset cannot be NULL.", 2);
  if (time_zone_dst_to_set->dst_start == TEB_NULL_POINTER) TEB_fatal_error(333, "time_zone_dst_to_set->dst_start cannot be NULL.", 2);
  if (time_zone_dst_to_set->dst_end == TEB_NULL_POINTER) TEB_fatal_error(334, "time_zone_dst_to_set->dst_end cannot be NULL.", 2);
  if (time_zone_dst_to_set->time_zone_utc_offset[1] < -59 || time_zone_dst_to_set->time_zone_utc_offset[1] > 59) TEB_fatal_error(335, "Value not allowed for time_zone_dst_to_set->time_zone_utc_offset[1].", 2);
  if (time_zone_dst_to_set->time_zone_utc_offset[0] < -23 || time_zone_dst_to_set->time_zone_utc_offset[0] > 23) TEB_fatal_error(336, "Value not allowed for time_zone_dst_to_set->time_zone_utc_offset[0].", 2);
  if (time_zone_dst_to_set->dst_start[0] < -1 || time_zone_dst_to_set->dst_start[0] > 12) TEB_fatal_error(337, "Value not allowed for time_zone_dst_to_set->dst_start[0].", 2);
  if (time_zone_dst_to_set->dst_start[1] < 1 || time_zone_dst_to_set->dst_start[1] > 7) TEB_fatal_error(338, "Value not allowed for time_zone_dst_to_set->dst_start[1].", 2);
  if (time_zone_dst_to_set->dst_start[2] < -5 || time_zone_dst_to_set->dst_start[2] > 5) TEB_fatal_error(339, "Value not allowed for time_zone_dst_to_set->dst_start[2].", 2);
  if (time_zone_dst_to_set->dst_start[3] < 0 || time_zone_dst_to_set->dst_start[3] > 23) TEB_fatal_error(340, "Value not allowed for time_zone_dst_to_set->dst_start[3].", 2);
  if (time_zone_dst_to_set->dst_start[4] < 0 || time_zone_dst_to_set->dst_start[4] > 59) TEB_fatal_error(341, "Value not allowed for time_zone_dst_to_set->dst_start[4].", 2);
  if (time_zone_dst_to_set->dst_end[0] < -1 || time_zone_dst_to_set->dst_end[0] > 12) TEB_fatal_error(342, "Value not allowed for time_zone_dst_to_set->dst_end[0].", 2);
  if (time_zone_dst_to_set->dst_end[1] < 1 || time_zone_dst_to_set->dst_end[1] > 7) TEB_fatal_error(343, "Value not allowed for time_zone_dst_to_set->dst_end[1].", 2);
  if (time_zone_dst_to_set->dst_end[2] < -5 || time_zone_dst_to_set->dst_end[2] > 5) TEB_fatal_error(344, "Value not allowed for time_zone_dst_to_set->dst_end[2].", 2);
  if (time_zone_dst_to_set->dst_end[3] < 0 || time_zone_dst_to_set->dst_end[3] > 23) TEB_fatal_error(345, "Value not allowed for time_zone_dst_to_set->dst_end[3].", 2);
  if (time_zone_dst_to_set->dst_end[4] < 0 || time_zone_dst_to_set->dst_end[4] > 59) TEB_fatal_error(346, "Value not allowed for time_zone_dst_to_set->dst_end[4].", 2);
  if (epoch_to_set_is_dst != 0 && (time_zone_dst_to_set->dst_start[0] == 0 || time_zone_dst_to_set->dst_end[0] == 0)) {return TEB_debug_function_end(-1);}
  if (epoch_to_set_is_dst == 0 && (time_zone_dst_to_set->dst_start[0] == -1 || time_zone_dst_to_set->dst_end[0] == -1)) {return TEB_debug_function_end(-2);}
  if (epoch_to_set_is_dst != 0) epoch_to_set_in_seconds = epoch_to_set_in_seconds - 3600;
  if (epoch_to_set_is_utc == 0) epoch_to_set_in_seconds = TEB_TimeManagement_local_to_utc_epoch(epoch_to_set_in_seconds, time_zone_dst_to_set->time_zone_utc_offset[0], time_zone_dst_to_set->time_zone_utc_offset[1]);
  //now epoch is a utc solar time
  return TEB_debug_function_end(TEB_Clock_set_epoch(clock_to_adjust, epoch_to_set_in_seconds));
}

TEB_small_int TEB_TimeZoneDST_set_time (struct TEB_Clock_struct* clock_to_adjust,
                                       const struct TEB_TimeZoneDST_struct* time_zone_dst_to_set,
                                       const struct TEB_TimeManagement_struct* time_to_set,
                                       TEB_bool time_to_set_is_dst,
                                       TEB_bool time_to_set_is_utc) {
  TEB_debug_function_start("TEB_TimeZoneDST_set_time");
  if (time_to_set == TEB_NULL_POINTER) TEB_fatal_error(347, "time_to_set cannot be NULL.", 2);
  if (time_to_set->second < 0 || time_to_set->second > 59) TEB_fatal_error(348, "Value not allowed for time_to_set->second.", 2);
  if (time_to_set->minute < 0 || time_to_set->minute > 59) TEB_fatal_error(349, "Value not allowed for time_to_set->minute.", 2);
  if (time_to_set->hour < 0 || time_to_set->hour > 23) TEB_fatal_error(350, "Value not allowed for time_to_set->hour.", 2);
  if (time_to_set->day < 1 || time_to_set->day > 31) TEB_fatal_error(351, "Value not allowed for time_to_set->day.", 2);
  if (time_to_set->month < 1 || time_to_set->month > 12) TEB_fatal_error(352, "Value not allowed for time_to_set->month.", 2);
  TEB_time_t epoch = TEB_TimeManagement_time_to_epoch(time_to_set, clock_to_adjust->initial_year_of_the_epoch);
  return TEB_debug_function_end(TEB_TimeZoneDST_set_epoch(clock_to_adjust, time_zone_dst_to_set, epoch, time_to_set_is_dst, time_to_set_is_utc));
}

TEB_time_t TEB_TimeZoneDST_get_epoch (const struct TEB_Clock_struct* clock_to_convert,
                                     const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                     TEB_bool neglect_time_zone,
                                     TEB_bool neglect_dst) {
  TEB_debug_function_start("TEB_TimeZoneDST_get_epoch");
  if (clock_to_convert == TEB_NULL_POINTER) TEB_fatal_error(353, "clock_to_convert cannot be NULL.", 2);
  if (time_zone_dst_to_consider == TEB_NULL_POINTER) TEB_fatal_error(354, "time_zone_dst_to_consider cannot be NULL.", 2);
  if (clock_to_convert->initial_weekday_of_the_epoch < 1 || clock_to_convert->initial_weekday_of_the_epoch > 7) TEB_fatal_error(355, "Value not allowed for clock_to_convert->initial_weekday_of_the_epoch.", 2);
  if (clock_to_convert->current_epoch_in_seconds < 0) TEB_fatal_error(376, "Value not allowed for clock_to_convert->current_epoch_in_seconds.", 2);
  if (time_zone_dst_to_consider->time_zone_database_name == TEB_NULL_POINTER) TEB_fatal_error(76, "time_zone_dst_to_consider->time_zone_database_name cannot be NULL.", 2);
  if (time_zone_dst_to_consider->time_zone_utc_offset == TEB_NULL_POINTER) TEB_fatal_error(356, "time_zone_dst_to_consider->time_zone_utc_offset cannot be NULL.", 2);
  if (time_zone_dst_to_consider->dst_start == TEB_NULL_POINTER) TEB_fatal_error(357, "time_zone_dst_to_consider->dst_start cannot be NULL.", 2);
  if (time_zone_dst_to_consider->dst_end == TEB_NULL_POINTER) TEB_fatal_error(358, "time_zone_dst_to_consider->dst_end cannot be NULL.", 2);
  if (time_zone_dst_to_consider->time_zone_utc_offset[1] < -59 || time_zone_dst_to_consider->time_zone_utc_offset[1] > 59) TEB_fatal_error(359, "Value not allowed for time_zone_dst_to_consider->time_zone_utc_offset[1].", 2);
  if (time_zone_dst_to_consider->time_zone_utc_offset[0] < -23 || time_zone_dst_to_consider->time_zone_utc_offset[0] > 23) TEB_fatal_error(360, "Value not allowed for time_zone_dst_to_consider->time_zone_utc_offset[0].", 2);
  if (time_zone_dst_to_consider->dst_start[0] < -1 || time_zone_dst_to_consider->dst_start[0] > 12) TEB_fatal_error(361, "Value not allowed for time_zone_dst_to_consider->dst_start[0].", 2);
  if (time_zone_dst_to_consider->dst_start[1] < 1 || time_zone_dst_to_consider->dst_start[1] > 7) TEB_fatal_error(362, "Value not allowed for time_zone_dst_to_consider->dst_start[1].", 2);
  if (time_zone_dst_to_consider->dst_start[2] < -5 || time_zone_dst_to_consider->dst_start[2] > 5) TEB_fatal_error(363, "Value not allowed for time_zone_dst_to_consider->dst_start[2].", 2);
  if (time_zone_dst_to_consider->dst_start[3] < 0 || time_zone_dst_to_consider->dst_start[3] > 23) TEB_fatal_error(364, "Value not allowed for time_zone_dst_to_consider->dst_start[3].", 2);
  if (time_zone_dst_to_consider->dst_start[4] < 0 || time_zone_dst_to_consider->dst_start[4] > 59) TEB_fatal_error(365, "Value not allowed for time_zone_dst_to_consider->dst_start[4].", 2);
  if (time_zone_dst_to_consider->dst_end[0] < -1 || time_zone_dst_to_consider->dst_end[0] > 12) TEB_fatal_error(366, "Value not allowed for time_zone_dst_to_consider->dst_end[0].", 2);
  if (time_zone_dst_to_consider->dst_end[1] < 1 || time_zone_dst_to_consider->dst_end[1] > 7) TEB_fatal_error(367, "Value not allowed for time_zone_dst_to_consider->dst_end[1].", 2);
  if (time_zone_dst_to_consider->dst_end[2] < -5 || time_zone_dst_to_consider->dst_end[2] > 5) TEB_fatal_error(368, "Value not allowed for time_zone_dst_to_consider->dst_end[2].", 2);
  if (time_zone_dst_to_consider->dst_end[3] < 0 || time_zone_dst_to_consider->dst_end[3] > 23) TEB_fatal_error(369, "Value not allowed for time_zone_dst_to_consider->dst_end[3].", 2);
  if (time_zone_dst_to_consider->dst_end[4] < 0 || time_zone_dst_to_consider->dst_end[4] > 59) TEB_fatal_error(370, "Value not allowed for time_zone_dst_to_consider->dst_end[4].", 2);
  if (time_zone_dst_to_consider->dst_start[0] == 0 && time_zone_dst_to_consider->dst_end[0] != 0 || time_zone_dst_to_consider->dst_start[0] != 0 && time_zone_dst_to_consider->dst_end[0] == 0) TEB_fatal_error(371, "Value not allowed for time_zone_dst_to_consider->dst_start[0] and time_zone_dst_to_consider->dst_end[0].", 2);
  if (time_zone_dst_to_consider->dst_start[0] == -1 && time_zone_dst_to_consider->dst_end[0] != -1 || time_zone_dst_to_consider->dst_start[0] != -1 && time_zone_dst_to_consider->dst_end[0] == -1) TEB_fatal_error(372, "Value not allowed for time_zone_dst_to_consider->dst_start[0] and time_zone_dst_to_consider->dst_end[0].", 2);
  TEB_time_t epoch = clock_to_convert->current_epoch_in_seconds;
  if (neglect_time_zone == 0) {
    epoch = TEB_TimeManagement_utc_to_local_epoch(epoch, time_zone_dst_to_consider->time_zone_utc_offset[0], time_zone_dst_to_consider->time_zone_utc_offset[1]);
  }
  if (neglect_dst == 0) {
    if (time_zone_dst_to_consider->dst_start[0] == -1 && time_zone_dst_to_consider->dst_end[0] == -1) epoch = epoch + 3600;  //case dst always active
    else if (time_zone_dst_to_consider->dst_start[0] == 0 && time_zone_dst_to_consider->dst_end[0] == 0)
      ;  //case dst never active
    else {
      struct TEB_TimeManagement_struct time;
      TEB_TimeManagement_epoch_to_time(epoch, clock_to_convert->initial_year_of_the_epoch, &time);
      TEB_time_t dst_start_epoch = TEB_TimeManagement_get_dst_epoch(time.year,
                                                                    time_zone_dst_to_consider->dst_start[0],
                                                                    time_zone_dst_to_consider->dst_start[1],
                                                                    time_zone_dst_to_consider->dst_start[2],
                                                                    time_zone_dst_to_consider->dst_start[3],
                                                                    time_zone_dst_to_consider->dst_start[4],
                                                                    clock_to_convert->initial_year_of_the_epoch,
                                                                    clock_to_convert->initial_weekday_of_the_epoch,
                                                                    0);
      TEB_time_t dst_end_epoch = TEB_TimeManagement_get_dst_epoch(time.year,
                                                                  time_zone_dst_to_consider->dst_end[0],
                                                                  time_zone_dst_to_consider->dst_end[1],
                                                                  time_zone_dst_to_consider->dst_end[2],
                                                                  time_zone_dst_to_consider->dst_end[3],
                                                                  time_zone_dst_to_consider->dst_end[4],
                                                                  clock_to_convert->initial_year_of_the_epoch,
                                                                  clock_to_convert->initial_weekday_of_the_epoch,
                                                                  0);
      if (TEB_TimeManagement_is_dst_epoch(epoch, dst_start_epoch, dst_end_epoch, 0) == 1) epoch = epoch + 3600;
    }
  }
  TEB_debug_function_end(0);
  return epoch;
}

TEB_small_int TEB_TimeZoneDST_get_time (const struct TEB_Clock_struct* clock_to_convert,
                                       const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                       TEB_bool neglect_time_zone,
                                       TEB_bool neglect_dst,
                                       struct TEB_TimeManagement_struct* time_converted) {
  TEB_debug_function_start("TEB_TimeZoneDST_get_time");
  if (time_converted == TEB_NULL_POINTER) TEB_fatal_error(373, "time_converted cannot be NULL.", 2);
  TEB_time_t epoch = TEB_TimeZoneDST_get_epoch(clock_to_convert, time_zone_dst_to_consider, neglect_time_zone, neglect_dst);
  return TEB_debug_function_end(TEB_TimeManagement_epoch_to_time(epoch, clock_to_convert->initial_year_of_the_epoch, time_converted));
}

TEB_small_int TEB_TimeZoneDST_get_s (const struct TEB_Clock_struct* clock_to_convert,
                                    const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                    TEB_bool neglect_time_zone,
                                    TEB_bool neglect_dst) {
  TEB_debug_function_start("TEB_TimeZoneDST_get_s");
  struct TEB_TimeManagement_struct time;
  if (TEB_TimeZoneDST_get_time(clock_to_convert, time_zone_dst_to_consider, neglect_time_zone, neglect_dst, &time) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end((TEB_small_int)time.second);
}

TEB_small_int TEB_TimeZoneDST_get_min (const struct TEB_Clock_struct* clock_to_convert,
                                      const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                      TEB_bool neglect_time_zone,
                                      TEB_bool neglect_dst) {
  TEB_debug_function_start("TEB_TimeZoneDST_get_min");
  struct TEB_TimeManagement_struct time;
  if (TEB_TimeZoneDST_get_time(clock_to_convert, time_zone_dst_to_consider, neglect_time_zone, neglect_dst, &time) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end((TEB_small_int)time.minute);
}

TEB_small_int TEB_TimeZoneDST_get_h (const struct TEB_Clock_struct* clock_to_convert,
                                    const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                    TEB_bool neglect_time_zone,
                                    TEB_bool neglect_dst) {
  TEB_debug_function_start("TEB_TimeZoneDST_get_h");
  struct TEB_TimeManagement_struct time;
  if (TEB_TimeZoneDST_get_time(clock_to_convert, time_zone_dst_to_consider, neglect_time_zone, neglect_dst, &time) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end((TEB_small_int)time.hour);
}

TEB_small_int TEB_TimeZoneDST_get_d (const struct TEB_Clock_struct* clock_to_convert,
                                    const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                    TEB_bool neglect_time_zone,
                                    TEB_bool neglect_dst) {
  TEB_debug_function_start("TEB_TimeZoneDST_get_d");
  struct TEB_TimeManagement_struct time;
  if (TEB_TimeZoneDST_get_time(clock_to_convert, time_zone_dst_to_consider, neglect_time_zone, neglect_dst, &time) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end((TEB_small_int)time.day);
}

TEB_small_int TEB_TimeZoneDST_get_mon (const struct TEB_Clock_struct* clock_to_convert,
                                      const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                      TEB_bool neglect_time_zone,
                                      TEB_bool neglect_dst) {
  TEB_debug_function_start("TEB_TimeZoneDST_get_mon");
  struct TEB_TimeManagement_struct time;
  if (TEB_TimeZoneDST_get_time(clock_to_convert, time_zone_dst_to_consider, neglect_time_zone, neglect_dst, &time) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end((TEB_small_int)time.month);
}

TEB_medium_int TEB_TimeZoneDST_get_y (const struct TEB_Clock_struct* clock_to_convert,
                                     const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                     TEB_bool neglect_time_zone,
                                     TEB_bool neglect_dst) {
  TEB_debug_function_start("TEB_TimeZoneDST_get_y");
  struct TEB_TimeManagement_struct time;
  if (TEB_TimeZoneDST_get_time(clock_to_convert, time_zone_dst_to_consider, neglect_time_zone, neglect_dst, &time) != 1) {
    TEB_fatal_error(374, "TEB_TimeZoneDST_get_y returned -30000.", 2);
    return -30000;
  }
  TEB_debug_function_end(0);
  return time.year;
}

TEB_small_int TEB_TimeZoneDST_get_weekday (const struct TEB_Clock_struct* clock_to_convert,
                                          const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                          TEB_bool neglect_time_zone,
                                          TEB_bool neglect_dst) {
  TEB_debug_function_start("TEB_TimeZoneDST_get_weekday");
  struct TEB_TimeManagement_struct time;
  if (TEB_TimeZoneDST_get_time(clock_to_convert, time_zone_dst_to_consider, neglect_time_zone, neglect_dst, &time) != 1) {return TEB_debug_function_end(-1);}
  TEB_small_int r = TEB_TimeManagement_weekday_from_date(time.year, time.month, time.day);
  return TEB_debug_function_end(r);
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
static void TEB_TimeZoneDST_function_end (const TEB_char* f_name, TEB_bool ok) {
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

TEB_small_int TEB_TimeZoneDST_test () {
  TEB_debug_function_start("TEB_TimeZoneDST_test");

  struct TEB_TimeZoneDST_struct tz_dst;
  TEB_small_int time_zone_utc_offset[2] = { 1, 0 };
  TEB_small_int dst_start[5] = { 3, 1, -1, 2, 0 };
  TEB_small_int dst_end[5] = { 10, 1, -1, 3, 0 };
  struct TEB_Clock_struct clock;
  TEB_Clock_struct_default_init(&clock);
  TEB_Clock_set_automatic_update(&clock, 0);

  if (TEB_TimeZoneDST_struct_init(&tz_dst, "Europe/Rome", time_zone_utc_offset, dst_start, dst_end) == 1 && TEB_String_equals2(tz_dst.time_zone_database_name, "Europe/Rome") == 1 && tz_dst.time_zone_utc_offset[0] == 1 && tz_dst.time_zone_utc_offset[1] == 0 && tz_dst.dst_start[0] == 3 && tz_dst.dst_start[1] == 1 && tz_dst.dst_start[2] == -1 && tz_dst.dst_start[3] == 2 && tz_dst.dst_start[4] == 0 && tz_dst.dst_end[0] == 10 && tz_dst.dst_end[1] == 1 && tz_dst.dst_end[2] == -1 && tz_dst.dst_end[3] == 3 && tz_dst.dst_end[4] == 0) TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_struct_init", 1);
  else {
    TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_struct_init", 0);
    return TEB_debug_function_end(-1);
  }

  if (TEB_TimeZoneDST_set_epoch(&clock, &tz_dst, 1698080966, 1, 0) == 1 && TEB_TimeZoneDST_get_epoch(&clock, &tz_dst, 0, 0) == 1698080966) TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_set_epoch and TEB_TimeZoneDST_get_epoch", 1);
  else {
    TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_set_epoch and TEB_TimeZoneDST_get_epoch", 0);
    return TEB_debug_function_end(-2);
  }

  struct TEB_TimeManagement_struct time1, time2;
  time1.second = 30;
  time1.minute = 30;
  time1.hour = 12;
  time1.day = 6;
  time1.month = 5;
  time1.year = 2023;
  if (TEB_TimeZoneDST_set_time(&clock, &tz_dst, &time1, 1, 0) == 1 && TEB_TimeZoneDST_get_time(&clock, &tz_dst, 0, 0, &time2) == 1 && time1.second == time2.second && time1.minute == time2.minute && time1.hour == time2.hour && time1.day == time2.day && time1.month == time2.month && time1.year == time2.year) TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_set_time and TEB_TimeZoneDST_get_time", 1);
  else {
    TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_set_time and TEB_TimeZoneDST_get_time", 0);
    return TEB_debug_function_end(-3);
  }

  if (TEB_TimeZoneDST_get_s(&clock, &tz_dst, 0, 0) == 30) TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_s", 1);
  else {
    TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_s", 0);
    return TEB_debug_function_end(-4);
  }

  if (TEB_TimeZoneDST_get_min(&clock, &tz_dst, 0, 0) == 30) TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_min", 1);
  else {
    TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_min", 0);
    return TEB_debug_function_end(-5);
  }

  if (TEB_TimeZoneDST_get_h(&clock, &tz_dst, 0, 0) == 12) TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_h", 1);
  else {
    TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_h", 0);
    return TEB_debug_function_end(-6);
  }

  if (TEB_TimeZoneDST_get_d(&clock, &tz_dst, 0, 0) == 6) TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_d", 1);
  else {
    TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_d", 0);
    return TEB_debug_function_end(-7);
  }

  if (TEB_TimeZoneDST_get_mon(&clock, &tz_dst, 0, 0) == 5) TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_mon", 1);
  else {
    TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_mon", 0);
    return TEB_debug_function_end(-8);
  }

  if (TEB_TimeZoneDST_get_y(&clock, &tz_dst, 0, 0) == 2023) TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_y", 1);
  else {
    TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_y", 0);
    return TEB_debug_function_end(-9);
  }

  if (TEB_TimeZoneDST_get_weekday(&clock, &tz_dst, 0, 0) == 7) TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_weekday", 1);
  else {
    TEB_TimeZoneDST_function_end("TEB_TimeZoneDST_get_weekday", 0);
    return TEB_debug_function_end(-10);
  }

  return TEB_debug_function_end(1);
}
#endif
