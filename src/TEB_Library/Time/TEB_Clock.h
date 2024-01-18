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

#ifndef TEB_Clock_h
#define TEB_Clock_h

#include "TEB_TimeManagement.h"

/**
    \brief This file contains the definition of struct TEB_Clock_struct that represents a clock to measure the passage of time. The TEB_Clock_struct is intended to be handled only by the functions in this file. 
    Warning: if you change initial_year_of_the_epoch, then the time must be reset.
    Warning: you must run TEB_Clock_get_epoch or TEB_Clock_get_time at least once every TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE milliseconds to keep the time of a struct TEB_Clock_struct updated.
    Warning: make sure that current_epoch_in_seconds can handle the date range you want to work with; for example, you cannot put initial_year_of_the_epoch = 1970 and consider year 3000 if current_epoch_in_seconds is a 32-bit variable. 
*/

/**
       \brief Represents a clock with seconds accuracy. Members starting with do_not_edit_manually___ must not be edited manually.	   
	    initial_year_of_the_epoch: initial year allocated to current_epoch_in_seconds = 0, can be negative;
	   initial_weekday_of_the_epoch: day of the week related to epoch = 0 (1 = Sunday, 2 = Monday, ..., 7 = Saturday);
	   current_epoch_in_seconds: the variable used by the clock to measure time in seconds, is considered a utc value without dst that never goes into overflow.
    */
struct TEB_Clock_struct {
  TEB_medium_int initial_year_of_the_epoch;
  TEB_small_u_int initial_weekday_of_the_epoch;
  TEB_time_t current_epoch_in_seconds;
  TEB_bool do_not_edit_manually___the_epoch_is_set;
  TEB_bool do_not_edit_manually___automatic_epoch_update;
  TEB_time_t do_not_edit_manually___last_read_value_of_TEB_ms_elapsed;
};

/**
       \brief Initialize a clock with default values (initial_year_of_the_epoch = 1970, initial_weekday_of_the_epoch = 5, current_epoch_in_seconds = 0, automatic_epoch_update on). 
	   \param [in] clock Clock to initialize.
	   \return 1 if all ok.
    */
TEB_small_int TEB_Clock_struct_default_init (struct TEB_Clock_struct* clock);

/**
       \brief Set a clock on the default values initial_year_of_the_epoch = 1970 and initial_weekday_of_the_epoch = 5.
	   \param [in] clock Clock to set.
	   \return 1 if all ok.
    */
TEB_small_int TEB_Clock_set_default_initial_year_epoch (struct TEB_Clock_struct* clock);

/**     
       \brief Set a clock on the desired values of initial_year_of_the_epoch and initial_weekday_of_the_epoch.
	   \param [in] clock Clock to set.
	   \return 1 if all ok.
    */
TEB_small_int TEB_Clock_set_initial_year_epoch (struct TEB_Clock_struct* clock,
                                               TEB_medium_int initial_year_of_the_epoch,
                                               TEB_small_u_int initial_weekday_of_the_epoch);
											   
/**     
       \brief Set a clock on the desired epoch.
	   \param [in] clock Clock to set.
	   \param [in] epoch_to_set_in_seconds Epoch in seconds to set.
	   \return 1 if all ok.
    */
TEB_small_int TEB_Clock_set_epoch (struct TEB_Clock_struct* clock, TEB_time_t epoch_to_set_in_seconds);

/**     
       \brief Set a clock on the desired values of epoch provided in the format struct TEB_TimeManagement_struct.
	   \param [in] clock Clock to set.
	   \param [in] time_to_set Epoch to set provided in the format struct TEB_TimeManagement_struct.
	   \return 1 if all ok.
    */
TEB_small_int TEB_Clock_set_time (struct TEB_Clock_struct* clock,
							      struct TEB_TimeManagement_struct* time_to_set);

/**     
       \brief Turns automatic clock update on or off. Default is on.
	   \param [in] clock Clock to set.
	   \param [in] enable_automatic_update 1 to turn on automatic clock update, 0 to turn it off.
	   \return 1 if all ok.
    */
TEB_small_int TEB_Clock_set_automatic_update (struct TEB_Clock_struct* clock, 
											  TEB_bool enable_automatic_update);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return current_epoch_in_seconds of the clock.
    */
TEB_time_t TEB_Clock_get_epoch (const struct TEB_Clock_struct* clock);

/**     
       \brief Converts a struct TEB_Clock_struct to a struct TEB_TimeManagement_struct.
	   \param [in] clock_to_convert The struct TEB_Clock_struct to be converted.
	   \param [in] time_converted The converted TEB_TimeManagement_struct.
	   \return 1 if all ok.
    */
TEB_small_int TEB_Clock_get_time (const struct TEB_Clock_struct* clock_to_convert, 
						          struct TEB_TimeManagement_struct* time_converted);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return initial_year_of_the_epoch of the clock.
    */
TEB_medium_int TEB_Clock_get_initial_year_epoch (const struct TEB_Clock_struct* clock);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return initial_weekday_of_the_epoch of the clock.
    */
TEB_small_u_int TEB_Clock_get_initial_weekday_epoch (const struct TEB_Clock_struct* clock);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return seconds of the clock.
    */
TEB_small_int TEB_Clock_get_s (const struct TEB_Clock_struct* clock);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return minutes of the clock.
    */
TEB_small_int TEB_Clock_get_min (const struct TEB_Clock_struct* clock);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return hour of the clock.
    */
TEB_small_int TEB_Clock_get_h (const struct TEB_Clock_struct* clock);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return day of the clock.
    */
TEB_small_int TEB_Clock_get_d (const struct TEB_Clock_struct* clock);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return month of the clock.
    */
TEB_small_int TEB_Clock_get_mon (const struct TEB_Clock_struct* clock);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return year of the clock.
	   \details If an error occurs, the function returns -111, which is also among the correct values that can be returned.
    */
TEB_medium_int TEB_Clock_get_y (const struct TEB_Clock_struct* clock);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return weekday of the clock.
    */
TEB_small_int TEB_Clock_get_weekday (const struct TEB_Clock_struct* clock);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return do_not_edit_manually___the_epoch_is_set of the clock.
    */
TEB_bool TEB_Clock_is_epoch_set (const struct TEB_Clock_struct* clock);

/**     
	   \param [in] clock An struct TEB_Clock_struct.
	   \return do_not_edit_manually___automatic_epoch_update of the clock.
    */
TEB_bool TEB_Clock_get_automatic_update (const struct TEB_Clock_struct* clock);

/**     
       \brief Moves the clock forward or backward.
	   \param [in] clock Clock to set.
	   \param [in] adjustment_in_seconds The seconds of adjustment. Set a negative value to move the clock backward.
	   \return 1 if all ok.
    */
TEB_small_int TEB_Clock_adjust (struct TEB_Clock_struct* clock, TEB_big_int adjustment_in_seconds);

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_Clock_test ();
#endif

struct TEB_Clock_rename_f {
  TEB_small_int (*defaultInit)(struct TEB_Clock_struct*);
  TEB_small_int (*setDefaultInitialYearEpoch)(struct TEB_Clock_struct*);
  TEB_small_int (*setInitialYearEpoch)(struct TEB_Clock_struct*, TEB_medium_int, TEB_small_u_int);
  TEB_small_int (*setEpoch)(struct TEB_Clock_struct*, TEB_time_t);
  TEB_small_int (*setTime)(struct TEB_Clock_struct*, struct TEB_TimeManagement_struct*);
  TEB_small_int (*setAutomaticUpdate)(struct TEB_Clock_struct*, TEB_bool);
  TEB_time_t (*epoch)(const struct TEB_Clock_struct*);
  TEB_small_int (*time)(const struct TEB_Clock_struct*, struct TEB_TimeManagement_struct*);
  TEB_medium_int (*initialYearEpoch)(const struct TEB_Clock_struct*);
  TEB_small_u_int (*initialWeekdayEpoch)(const struct TEB_Clock_struct*);
  TEB_small_int (*s)(const struct TEB_Clock_struct*);
  TEB_small_int (*min)(const struct TEB_Clock_struct*);
  TEB_small_int (*h)(const struct TEB_Clock_struct*);
  TEB_small_int (*d)(const struct TEB_Clock_struct*);
  TEB_small_int (*mon)(const struct TEB_Clock_struct*);
  TEB_medium_int (*y)(const struct TEB_Clock_struct*);
  TEB_small_int (*w)(const struct TEB_Clock_struct*);
  TEB_bool (*isEpochSet)(const struct TEB_Clock_struct*);
  TEB_bool (*automaticUpdate)(const struct TEB_Clock_struct*);
  TEB_small_int (*adjust)(struct TEB_Clock_struct*, TEB_big_int);
};

#endif