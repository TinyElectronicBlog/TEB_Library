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

#include "TEB_Clock.h"
#include "../String/TEB_String.h"
#include "../Number/TEB_Number.h"

static void TEB_Clock_synchronize_the_clock_epoch_with_the_current_epoch_in_seconds (struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_synchronize_the_clock_epoch_with_the_current_epoch_in_seconds");
  if (clock->do_not_edit_manually___automatic_epoch_update == 1) {
    //clock->current_epoch_in_seconds is considered not to overflow
    TEB_time_t current_epoch_in_ms = TEB_ms_elapsed();
    if (current_epoch_in_ms > clock->do_not_edit_manually___last_read_value_of_TEB_ms_elapsed) {
      clock->current_epoch_in_seconds = clock->current_epoch_in_seconds + ((current_epoch_in_ms - clock->do_not_edit_manually___last_read_value_of_TEB_ms_elapsed) / 1000);
      clock->do_not_edit_manually___last_read_value_of_TEB_ms_elapsed = current_epoch_in_ms;
    } else if (current_epoch_in_ms < clock->do_not_edit_manually___last_read_value_of_TEB_ms_elapsed) {  //if the variable used by the device to measure time goes into overflow.
      clock->current_epoch_in_seconds = clock->current_epoch_in_seconds + (((TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE - clock->do_not_edit_manually___last_read_value_of_TEB_ms_elapsed) + current_epoch_in_ms + 1) / 1000);
      clock->do_not_edit_manually___last_read_value_of_TEB_ms_elapsed = current_epoch_in_ms;
    }
  }
  TEB_debug_function_end(0);
}

TEB_small_int TEB_Clock_struct_default_init (struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_struct_default_init");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(208, "clock cannot be NULL.", 2);
  if (TEB_Clock_set_default_initial_year_epoch(clock) != 1) {return TEB_debug_function_end(0);}
  clock->current_epoch_in_seconds = 0;
  clock->do_not_edit_manually___automatic_epoch_update = 1;
  clock->do_not_edit_manually___last_read_value_of_TEB_ms_elapsed = 0;
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_Clock_set_default_initial_year_epoch (struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_set_default_initial_year_epoch");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(209, "clock cannot be NULL.", 2);
  clock->initial_year_of_the_epoch = 1970;
  clock->initial_weekday_of_the_epoch = 5;
  clock->do_not_edit_manually___the_epoch_is_set = 0;
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_Clock_set_initial_year_epoch (struct TEB_Clock_struct* clock,
                                               TEB_medium_int initial_year_of_the_epoch,
                                               TEB_small_u_int initial_weekday_of_the_epoch) {
  TEB_debug_function_start("TEB_Clock_set_initial_year_epoch");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(210, "clock cannot be NULL.", 2);
  if (initial_weekday_of_the_epoch < 1 || initial_weekday_of_the_epoch > 7) TEB_fatal_error(211, "Value not allowed for initial_weekday_of_the_epoch.", 2);
  clock->initial_year_of_the_epoch = initial_year_of_the_epoch;
  clock->initial_weekday_of_the_epoch = initial_weekday_of_the_epoch;
  clock->do_not_edit_manually___the_epoch_is_set = 0;
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_Clock_set_epoch (struct TEB_Clock_struct* clock, TEB_time_t epoch_to_set_in_seconds) {
  TEB_debug_function_start("TEB_Clock_set_epoch");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(212, "clock cannot be NULL.", 2);
  if (epoch_to_set_in_seconds < 0) TEB_fatal_error(213, "Value not allowed for epoch_to_set_in_seconds.", 2);
  TEB_bool k = TEB_Clock_get_automatic_update(clock);
  if (k != 0) TEB_Clock_set_automatic_update(clock, 0);
  clock->current_epoch_in_seconds = epoch_to_set_in_seconds;
  clock->do_not_edit_manually___the_epoch_is_set = 1;
  if (k != 0) TEB_Clock_set_automatic_update(clock, 1);
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_Clock_set_time (struct TEB_Clock_struct* clock,
							      struct TEB_TimeManagement_struct* time_to_set) {
  TEB_debug_function_start("TEB_Clock_set_time");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(214, "clock cannot be NULL.", 2);
  if (time_to_set == TEB_NULL_POINTER) TEB_fatal_error(215, "time_to_set cannot be NULL.", 2);
  if (time_to_set->second < 0 || time_to_set->second > 59) TEB_fatal_error(216, "Value not allowed for time_to_set->second.", 2);
  if (time_to_set->minute < 0 || time_to_set->minute > 59) TEB_fatal_error(217, "Value not allowed for time_to_set->minute.", 2);
  if (time_to_set->hour < 0 || time_to_set->hour > 23) TEB_fatal_error(218, "Value not allowed for time_to_set->hour.", 2);
  if (time_to_set->day < 1 || time_to_set->day > 31) TEB_fatal_error(219, "Value not allowed for time_to_set->day.", 2);
  if (time_to_set->month < 1 || time_to_set->month > 12) TEB_fatal_error(220, "Value not allowed for time_to_set->month.", 2);
  TEB_bool k = TEB_Clock_get_automatic_update(clock);
  if (k != 0) TEB_Clock_set_automatic_update(clock, 0);
  clock->current_epoch_in_seconds = TEB_TimeManagement_time_to_epoch(time_to_set, clock->initial_year_of_the_epoch);
  clock->do_not_edit_manually___the_epoch_is_set = 1;
  if (k != 0) TEB_Clock_set_automatic_update(clock, 1);
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_Clock_set_automatic_update (struct TEB_Clock_struct* clock, 
											  TEB_bool enable_automatic_update) {
  TEB_debug_function_start("TEB_Clock_set_automatic_update");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(221, "clock cannot be NULL.", 2);
  if (enable_automatic_update != 0 && clock->do_not_edit_manually___automatic_epoch_update != 1) {
    clock->do_not_edit_manually___last_read_value_of_TEB_ms_elapsed = TEB_ms_elapsed();
  }
  clock->do_not_edit_manually___automatic_epoch_update = enable_automatic_update;
  return TEB_debug_function_end(1);
}

TEB_time_t TEB_Clock_get_epoch (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_get_epoch");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(222, "clock cannot be NULL.", 2);
  TEB_Clock_synchronize_the_clock_epoch_with_the_current_epoch_in_seconds((struct TEB_Clock_struct*)clock);
  TEB_debug_function_end(0);
  return clock->current_epoch_in_seconds;
}

TEB_small_int TEB_Clock_get_time (const struct TEB_Clock_struct* clock_to_convert, 
						          struct TEB_TimeManagement_struct* time_converted) {
  TEB_debug_function_start("TEB_Clock_get_time");
  if (clock_to_convert == TEB_NULL_POINTER) TEB_fatal_error(223, "clock_to_convert cannot be NULL.", 2);
  if (time_converted == TEB_NULL_POINTER) TEB_fatal_error(375, "time_converted cannot be NULL.", 2);
  return TEB_debug_function_end(TEB_TimeManagement_epoch_to_time(TEB_Clock_get_epoch(clock_to_convert), clock_to_convert->initial_year_of_the_epoch, time_converted));
}

TEB_medium_int TEB_Clock_get_initial_year_epoch (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_get_initial_year_epoch");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(224, "clock cannot be NULL.", 2);
  TEB_debug_function_end(0);
  return clock->initial_year_of_the_epoch;
}

TEB_small_u_int TEB_Clock_get_initial_weekday_epoch (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_get_initial_weekday_epoch");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(225, "clock cannot be NULL.", 2);
  return TEB_debug_function_end(clock->initial_weekday_of_the_epoch);
}

TEB_small_int TEB_Clock_get_s (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_get_s");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(226, "clock cannot be NULL.", 2);
  struct TEB_TimeManagement_struct time;
  if (TEB_Clock_get_time(clock, &time) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end(time.second);
}

TEB_small_int TEB_Clock_get_min (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_get_min");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(227, "clock cannot be NULL.", 2);
  struct TEB_TimeManagement_struct time;
  if (TEB_Clock_get_time(clock, &time) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end(time.minute);
}

TEB_small_int TEB_Clock_get_h (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_get_h");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(228, "clock cannot be NULL.", 2);
  struct TEB_TimeManagement_struct time;
  if (TEB_Clock_get_time(clock, &time) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end(time.hour);
}

TEB_small_int TEB_Clock_get_d (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_get_d");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(229, "clock cannot be NULL.", 2);
  struct TEB_TimeManagement_struct time;
  if (TEB_Clock_get_time(clock, &time) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end(time.day);
}

TEB_small_int TEB_Clock_get_mon (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_get_mon");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(230, "clock cannot be NULL.", 2);
  struct TEB_TimeManagement_struct time;
  if (TEB_Clock_get_time(clock, &time) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end(time.month);
}

TEB_medium_int TEB_Clock_get_y (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_get_y");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(231, "clock cannot be NULL.", 2);
  struct TEB_TimeManagement_struct time;
  if (TEB_Clock_get_time(clock, &time) != 1) {return TEB_debug_function_end(-111);}
  TEB_debug_function_end(0);
  return time.year;
}

TEB_small_int TEB_Clock_get_weekday (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_get_weekday");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(232, "clock cannot be NULL.", 2);
  struct TEB_TimeManagement_struct t;
  if (TEB_Clock_get_time(clock, &t) != 1) {return TEB_debug_function_end(-1);}
  return TEB_debug_function_end(TEB_TimeManagement_weekday_from_date(t.year, t.month, t.day));
}

TEB_bool TEB_Clock_is_epoch_set (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_is_epoch_set");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(233, "clock cannot be NULL.", 2);
  return TEB_debug_function_end(clock->do_not_edit_manually___the_epoch_is_set);
}

TEB_bool TEB_Clock_get_automatic_update (const struct TEB_Clock_struct* clock) {
  TEB_debug_function_start("TEB_Clock_get_automatic_update");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(234, "clock cannot be NULL.", 2);
  return TEB_debug_function_end(clock->do_not_edit_manually___automatic_epoch_update);
}

TEB_small_int TEB_Clock_adjust (struct TEB_Clock_struct* clock, TEB_big_int adjustment_in_seconds) {
  TEB_debug_function_start("TEB_Clock_adjust");
  if (clock == TEB_NULL_POINTER) TEB_fatal_error(235, "clock cannot be NULL.", 2);
  if (adjustment_in_seconds < 0)
    if (adjustment_in_seconds * -1 > clock->current_epoch_in_seconds) TEB_fatal_error(236, "Value not allowed for adjustment_in_seconds.", 2);
  clock->current_epoch_in_seconds = clock->current_epoch_in_seconds + adjustment_in_seconds;
  return TEB_debug_function_end(1);
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
static void TEB_Clock_function_end (const TEB_char* f_name, TEB_bool ok) {
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

TEB_small_int TEB_Clock_test () {
  TEB_debug_function_start("TEB_Clock_test");

  struct TEB_Clock_struct clock;
  if (TEB_Clock_struct_default_init(&clock) == 1 && clock.initial_year_of_the_epoch == 1970 && clock.initial_weekday_of_the_epoch == 5 && clock.current_epoch_in_seconds == 0 && clock.do_not_edit_manually___the_epoch_is_set == 0 && clock.do_not_edit_manually___automatic_epoch_update == 1 && clock.do_not_edit_manually___last_read_value_of_TEB_ms_elapsed == 0) TEB_Clock_function_end("TEB_Clock_struct_default_init", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_struct_default_init", 0);
    return TEB_debug_function_end(-1);
  }

  if (TEB_Clock_set_default_initial_year_epoch(&clock) == 1 && clock.initial_year_of_the_epoch == 1970 && clock.initial_weekday_of_the_epoch == 5 && clock.current_epoch_in_seconds == 0) TEB_Clock_function_end("TEB_Clock_set_default_initial_year_epoch", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_set_default_initial_year_epoch", 0);
    return TEB_debug_function_end(-2);
  }

  if (TEB_Clock_set_initial_year_epoch(&clock, 1970, 5) == 1 && clock.initial_year_of_the_epoch == 1970 && clock.initial_weekday_of_the_epoch == 5 && clock.current_epoch_in_seconds == 0) TEB_Clock_function_end("TEB_Clock_set_initial_year_epoch", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_set_initial_year_epoch", 0);
    return TEB_debug_function_end(-3);
  }

  if (TEB_Clock_get_initial_year_epoch(&clock) == 1970) TEB_Clock_function_end("TEB_Clock_get_initial_year_epoch", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_get_initial_year_epoch", 0);
    return TEB_debug_function_end(-4);
  }

  if (TEB_Clock_get_initial_weekday_epoch(&clock) == 5) TEB_Clock_function_end("TEB_Clock_get_initial_weekday_epoch", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_get_initial_weekday_epoch", 0);
    return TEB_debug_function_end(-5);
  }

  if (TEB_Clock_is_epoch_set(&clock) == 0) TEB_Clock_function_end("TEB_Clock_is_epoch_set", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_is_epoch_set", 0);
    return TEB_debug_function_end(-6);
  }

  TEB_Clock_set_automatic_update(&clock, 0);
  if (TEB_Clock_get_automatic_update(&clock) == 0) TEB_Clock_function_end("TEB_Clock_set_automatic_update and TEB_Clock_get_automatic_update", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_set_automatic_update and TEB_Clock_get_automatic_update", 0);
    return TEB_debug_function_end(-7);
  }

  if (TEB_Clock_set_epoch(&clock, 0) == 1 && TEB_Clock_adjust(&clock, 10000) == 1 && TEB_Clock_get_epoch(&clock) == 10000) TEB_Clock_function_end("TEB_Clock_set_epoch, TEB_Clock_adjust and TEB_Clock_get_epoch ok", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_set_epoch, TEB_Clock_adjust and TEB_Clock_get_epoch ok", 0);
    return TEB_debug_function_end(-8);
  }

  struct TEB_TimeManagement_struct time1, time2;
  time1.second = 10;
  time1.minute = 15;
  time1.hour = 18;
  time1.day = 23;
  time1.month = 11;
  time1.year = 2015;
  if (TEB_Clock_set_time(&clock, &time1) == 1 && TEB_Clock_get_time(&clock, &time2) == 1 && time1.second == time2.second && time1.minute == time2.minute && time1.hour == time2.hour && time1.day == time2.day && time1.month == time2.month && time1.year == time2.year) TEB_Clock_function_end("TEB_Clock_set_time and TEB_Clock_get_time", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_set_time and TEB_Clock_get_time", 0);
    return TEB_debug_function_end(-9);
  }

  if (TEB_Clock_get_s(&clock) == 10) TEB_Clock_function_end("TEB_Clock_get_s", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_get_s", 0);
    return TEB_debug_function_end(-10);
  }

  if (TEB_Clock_get_min(&clock) == 15) TEB_Clock_function_end("TEB_Clock_get_min", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_get_min", 0);
    return TEB_debug_function_end(-11);
  }

  if (TEB_Clock_get_h(&clock) == 18) TEB_Clock_function_end("TEB_Clock_get_h", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_get_h", 0);
    return TEB_debug_function_end(-12);
  }

  if (TEB_Clock_get_d(&clock) == 23) TEB_Clock_function_end("TEB_Clock_get_d", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_get_d", 0);
    return TEB_debug_function_end(-13);
  }

  if (TEB_Clock_get_mon(&clock) == 11) TEB_Clock_function_end("TEB_Clock_get_mon", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_get_mon", 0);
    return TEB_debug_function_end(-14);
  }

  if (TEB_Clock_get_y(&clock) == 2015) TEB_Clock_function_end("TEB_Clock_get_y", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_get_y", 0);
    return TEB_debug_function_end(-15);
  }

  if (TEB_Clock_get_weekday(&clock) == 2) TEB_Clock_function_end("TEB_Clock_get_weekday", 1);
  else {
    TEB_Clock_function_end("TEB_Clock_get_weekday", 0);
    return TEB_debug_function_end(-16);
  }

  TEB_small_int i = 0, end = 10;
  TEB_Clock_set_automatic_update(&clock, 1);
  const TEB_time_t t1 = TEB_Clock_get_epoch(&clock);
  TEB_debug_print("\n");
  while (i < end) {
    TEB_delay(1000, 1);
	TEB_debug_print("epoch1="); TEB_debug_print_int(t1 + i); TEB_debug_print(" epoch2="); TEB_debug_print_int(TEB_Clock_get_epoch(&clock)); TEB_debug_print("\n");
	if (t1 + i < TEB_Clock_get_epoch(&clock)-1 || t1 + i > TEB_Clock_get_epoch(&clock)+1) break;
    i = i + 1;
  }
  TEB_debug_print("\n");
  if (i == end) TEB_debug_print("Time measurement test ok");
  else {
    TEB_debug_print("Time measurement test ko");
    return TEB_debug_function_end(-17);
  }

  return TEB_debug_function_end(1);
}
#endif
