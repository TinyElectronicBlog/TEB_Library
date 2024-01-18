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

#ifndef TEB_TimeManagement_h
#define TEB_TimeManagement_h

#include "../../TEB_LibrarySettings.h"
#include "../DeviceInterfaces/TEB_DeviceInterfaces.h"

/**
    \brief This file contains useful structs and functions for manipulating time.
*/

/**
       \brief A TEB_TimeManagement_struct can contain a date and a time.
*/
struct TEB_TimeManagement_struct {
  TEB_small_u_int second;
  TEB_small_u_int minute;
  TEB_small_u_int hour;
  TEB_small_u_int day;
  TEB_small_u_int month;
  TEB_medium_int year;
};

/**
       \brief Determine the first weekday of a year.
	   \param [in] year Year to consider.
	   \return The weekday (Sunday = 1, Thursday = 5, ..., Saturday = 7)
*/
TEB_small_int TEB_TimeManagement_first_weekday_year (TEB_medium_int year);

/**
       \brief Determines whether a year is a leap year.
	   \param [in] year Year to consider.
	   \return 1 if year is a leap year, otherwise 0.
*/
TEB_bool TEB_TimeManagement_is_leap_year (TEB_medium_int year);

/**
       \brief Determines the number of days in a month.
	   \param [in] is_a_leap_year Put 1 if the month is in a leap year.
	   \return The number of days in the month.
*/
TEB_small_u_int TEB_TimeManagement_days_of_month (TEB_small_u_int month,
                                                 TEB_bool is_a_leap_year);

/**
       \brief Converts a struct TEB_TimeManagement_struct to epoch expressed in seconds.
	   \param [in] time_to_convert Time to convert.
	   \param [in] initial_year_of_the_epoch Initial year to be associated with epoch = 0.
	   \return The converted epoch.
*/
TEB_time_t TEB_TimeManagement_time_to_epoch (const struct TEB_TimeManagement_struct* time_to_convert,
                                            TEB_medium_int initial_year_of_the_epoch);

/**
       \brief Converts an epoch expressed in seconds to a struct TEB_TimeManagement_struct.
	   \param [in] epoch_to_convert Epoch to convert.
	   \param [in] initial_year_of_the_epoch Initial year associated with epoch_to_convert = 0.
	   \param [in] time_converted Where to save the struct TEB_TimeManagement_struct converted.
	   \return 1 if all ok.
*/
TEB_small_int TEB_TimeManagement_epoch_to_time (TEB_time_t epoch_to_convert,
                                               TEB_medium_int initial_year_of_the_epoch,
                                               struct TEB_TimeManagement_struct* time_converted);

/**
       \brief Determines the weekday of an epoch.
	   \param [in] epoch Epoch to consider.
	   \param [in] initial_year_of_the_epoch Year associated with epoch = 0.
	   \param [in] initial_weekday_of_the_epoch Weekday associated with epoch = 0. 
	   \return The weekday determined.
*/
TEB_small_int TEB_TimeManagement_weekday_from_epoch (TEB_time_t epoch,
                                                    TEB_medium_int initial_year_of_the_epoch,
                                                    TEB_small_int initial_weekday_of_the_epoch);

/**
       \brief Determines the weekday of a date.
	   \param [in] year Year to consider.
	   \param [in] month Month to consider.
	   \param [in] day Day to consider.
	   \return The weekday determined.
*/
TEB_small_int TEB_TimeManagement_weekday_from_date (TEB_medium_int year,
                                                   TEB_small_u_int month,
                                                   TEB_small_u_int day);

/**
       \brief Evaluates whether one time instant is prior to another.
       \param [in] time_to_evaluate Time instant to evaluate.
       \param [in] reference_time Reference time instant.
	   \return 1 if time_to_evaluate < reference_time.
    */
TEB_bool TEB_TimeManagement_is_time_passed (const struct TEB_TimeManagement_struct* time_to_evaluate,
								            const struct TEB_TimeManagement_struct* reference_time);

/**
       \brief This function evaluates whether a time is daylight saving or solar time.
       \param [in] time_to_evaluate Time to evaluate.
       \param [in] dst_start When DST starts (month, weekday, th_weekday, hour, minute). For example, the second weekday is denoted by dst_start[2]=2, the penultimate weekday by dst_start[2]=-2.
	   \param [in] dst_end When DST ends (month, weekday, th_weekday, hour, minute). For example, the first weekday is denoted by dst_end[2]=1, the third-to-last weekday by dst_end[2]=-3.
	   \return 1 if time is daylight saving time, 0 if not, -1 if the evaluation is not possible.
	   \details time, dst_start and dst_end must refer to the same time zone. Set dst_start[0] = dst_end[0] = 0 to consider the time to be always solar time. Set dst_start[0] = dst_end[0] = -1 to consider the time to be always daylight saving time.
    */
TEB_small_int TEB_TimeManagement_is_dst_time (const struct TEB_TimeManagement_struct* time_to_evaluate,
                                             const TEB_small_int dst_start[5],
                                             const TEB_small_int dst_end[5]);

/*
       \brief Evaluates whether an epoch is daylight saving time or standard time.
       \param [in] epoch_to_evaluate Epoch to evaluate.
       \param [in] dst_start_epoch Epoch of the start of dst to be considered. Is a solar time by definition.
	   \param [in] dst_end_epoch Epoch of the end of dst to be considered. Is a daylight saving time by definition.
	   \param [in] dst_end_epoch_is_standard_time Set to 0 if dst_end_epoch is provided as daylight saving time, 1 if solar.
	   \return 1 if epoch_to_evaluate is daylight saving time, 0 otherwise.
	   \details The input parameters must refer to the same time zone.
    */
TEB_bool TEB_TimeManagement_is_dst_epoch (TEB_time_t epoch_to_evaluate,
                                         TEB_time_t dst_start_epoch,
                                         TEB_time_t dst_end_epoch,
                                         TEB_bool dst_end_epoch_is_standard_time);

/**
       \brief Determines the epoch of the beginning or end of a dst.
       \param [in] year Year to be considered.
       \param [in] month Month to be considered.
	   \param [in] weekday The day of the week on which DST begins/ends. Enter 1 for Sunday, 2 for Monday, 3 for Tuesday, ..., 7 for Saturday.
	   \param [in] th_weekday Enter 1 to select the first dayOfWeek of the month or -1 for the last, 2 for the second dayOfWeek of the month or -2 for the penultimate ... (max +5 or -5 included).
	   \param [in] hour Hour to be considered.
	   \param [in] minute Minute to be considered.
	   \param [in] initial_year_of_the_epoch Initial year of the epoch to be considered.
	   \param [in] initial_weekday_of_the_epoch Initial weekday of the epoch to be considered.
	   \param [in] get_dst_end_in_standard_time Set to 1 if you want to determine a dst end in standard time format.
	   \return The converted epoch. It is not a UTC value, i.e. it depends on the time zone of a state.
	   \details The input parameters must refer to the local time of the state for which you want to determine the start/end of the dst. The beginning of a dst is considered solar, while the end is legal (if you want the latter in solar form put get_dst_end_in_standard_time to 1). If you evaluate the start of a dst, get_dst_end_in_standard_time must always be set to 0.
    */
TEB_time_t TEB_TimeManagement_get_dst_epoch (TEB_medium_int year,
                                            TEB_small_u_int month,
                                            TEB_small_u_int weekday,
                                            TEB_small_int th_weekday,
                                            TEB_small_u_int hour,
                                            TEB_small_u_int minute,
                                            TEB_medium_int initial_year_of_the_epoch,
                                            TEB_small_int initial_weekday_of_the_epoch,
                                            TEB_bool get_dst_end_in_standard_time);

/**
       \brief Converts an epoch from utc to local (subject to time zone).
       \param [in] epoch_to_convert The epoch to convert.
       \param [in] time_zone_utc_offset_hour Enter an UTC hour offset in standard time (for more information see https://en.wikipedia.org/wiki/List_of_tz_database_time_zones).
	   \param [in] time_zone_utc_offset_minute Enter an UTC minute offset in standard time (for more information see https://en.wikipedia.org/wiki/List_of_tz_database_time_zones).
	   \return The converted epoch.
	   \details The function does not take into account daylight saving time.
    */
TEB_time_t TEB_TimeManagement_utc_to_local_epoch (TEB_time_t epoch_to_convert,
                                                 TEB_small_int time_zone_utc_offset_hour,
                                                 TEB_small_int time_zone_utc_offset_minute);

/**
       \brief Converts an epoch from local (subject to time zone) to utc.
       \param [in] epoch_to_convert The epoch to convert.
       \param [in] time_zone_utc_offset_hour Enter an UTC hour offset in standard time (for more information see https://en.wikipedia.org/wiki/List_of_tz_database_time_zones).
	   \param [in] time_zone_utc_offset_minute Enter an UTC minute offset in standard time (for more information see https://en.wikipedia.org/wiki/List_of_tz_database_time_zones).
	   \return The converted epoch.
	   \details The function does not take into account daylight saving time.
    */
TEB_time_t TEB_TimeManagement_local_to_utc_epoch (TEB_time_t epoch_to_convert,
                                                 TEB_small_int time_zone_utc_offset_hour,
                                                 TEB_small_int time_zone_utc_offset_minute);

/**
        \brief Save in date_buffer the input date in year-mm-dd format. If year is negative date_buffer starts with -.
        \param [in] day Must be >= 1 and <= 31.
        \param [in] month Must be >= 1 and <= 12.
        \param [in] year The year.
        \param [in] date_buffer Buffer in which the date is saved in year-mm-dd format. Must not be NULL.
        \return A pointer to the \0 that ends date_buffer.
    */
TEB_char* TEB_TimeManagement_str_date (TEB_small_u_int day,
                                      TEB_small_u_int month,
                                      TEB_medium_u_int year,
									  TEB_char* date_buffer);

/**
        \brief Save in time_buffer the input time in hh-mm-ss format.
        \param [in] hour Must be >= 0 and <= 23.
        \param [in] minute Must be >= 0 and <= 59.
        \param [in] second Must be >= 0 and <= 59.
        \param [in] time_buffer Buffer in which the time is saved in hh-mm-ss format. Must not be NULL.
        \return A pointer to the \0 that ends time_buffer.
    */
TEB_char* TEB_TimeManagement_str_time (TEB_small_u_int hour,
                                      TEB_small_u_int minute,
                                      TEB_small_u_int second, 
									  TEB_char* time_buffer);

/**
        \brief Extracts the year from the given input date in the year-mm-dd format.
        \param [in] date Date in year-mm-dd format. Must not be NULL. It can start with - to indicate a BC year. 
        \return The year.
    */
TEB_medium_int TEB_TimeManagement_str_int_y (const TEB_char* date);

/**
        \brief Extracts the month from the given input date in the year-mm-dd format.
        \param [in] date Date in year-mm-dd format. Must not be NULL. It can start with - to indicate a BC year. 
        \return The month.
    */
TEB_small_u_int TEB_TimeManagement_str_int_mon (const TEB_char* date);

/**
        \brief Extracts the day from the given input date in the year-mm-dd format.
        \param [in] date Date in year-mm-dd format. Must not be NULL. It can start with - to indicate a BC year. 
        \return The day.
    */
TEB_small_u_int TEB_TimeManagement_str_int_d (const TEB_char* date);

/**
        \brief Extracts the hours from the given input time in the hh-mm-ss format.
        \param [in] time Time in hh-mm-ss format. Must not be NULL.
        \return The hours.
    */
TEB_small_u_int TEB_TimeManagement_str_int_h (const TEB_char* time);

/**
         \brief Extracts the minutes from the given input time in the hh-mm-ss format.
         \param [in] time Time in hh-mm-ss format. Must not be NULL.
         \return The minutes.
    */
TEB_small_u_int TEB_TimeManagement_str_int_min (const TEB_char* time);

/**
        \brief Extracts the seconds from the given input time in the hh-mm-ss format.
        \param [in] time Time in hh-mm-ss format. Must not be NULL.
        \return The seconds.
    */
TEB_small_u_int TEB_TimeManagement_str_int_s (const TEB_char* time);

/**
       \brief Converts a HTTP-date to epoch.
       \param [in] http_date_to_convert Date and time to convert provided in a similar way to the "HTTP-date" format (for example "15 Nov 1994 08:12:31"). For more information see the definition of the method.
	   \param [in] initial_year_of_the_epoch Initial year of the converted epoch.
       \return The epoch in seconds.
    */
TEB_time_t TEB_TimeManagement_http_date_to_epoch (const TEB_char* http_date_to_convert,
                                                 TEB_medium_int initial_year_of_the_epoch);

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_TimeManagement_test();
#endif

struct TEB_TimeManagement_rename_f {
  TEB_small_int (*firstWeekdayYear)(TEB_medium_int);
  TEB_bool (*isLeapYear)(TEB_medium_int);
  TEB_small_u_int (*daysOfMonth)(TEB_small_u_int, TEB_bool);
  TEB_time_t (*timeToEpoch)(const struct TEB_TimeManagement_struct*, TEB_medium_int);
  TEB_small_int (*epochToTime)(TEB_time_t, TEB_medium_int, struct TEB_TimeManagement_struct*);
  TEB_small_int (*weekdayFromEpoch)(TEB_time_t, TEB_medium_int, TEB_small_int);
  TEB_small_int (*weekdayFromDate)(TEB_medium_int, TEB_small_u_int, TEB_small_u_int);
  TEB_bool (*isTimePassed)(const struct TEB_TimeManagement_struct*, const struct TEB_TimeManagement_struct*);
  TEB_small_int (*isDstTime)(const struct TEB_TimeManagement_struct*, const TEB_small_int[], const TEB_small_int[]);
  TEB_bool (*isDstEpoch)(TEB_time_t, TEB_time_t, TEB_time_t, TEB_bool);
  TEB_time_t (*getDstEpoch)(TEB_medium_int, TEB_small_u_int, TEB_small_u_int, TEB_small_int, TEB_small_u_int, TEB_small_u_int, TEB_medium_int, TEB_small_int, TEB_bool);
  TEB_time_t (*utcToLocalEpoch)(TEB_time_t, TEB_small_int, TEB_small_int);
  TEB_time_t (*localToUtcEpoch)(TEB_time_t, TEB_small_int, TEB_small_int);
  TEB_char* (*strDate)(TEB_small_u_int, TEB_small_u_int, TEB_medium_u_int, TEB_char*);
  TEB_char* (*strTime)(TEB_small_u_int, TEB_small_u_int, TEB_small_u_int, TEB_char*);
  TEB_medium_int (*strIntY)(const TEB_char*);
  TEB_small_u_int (*strIntMon)(const TEB_char*);
  TEB_small_u_int (*strIntD)(const TEB_char*);
  TEB_small_u_int (*strIntH)(const TEB_char*);
  TEB_small_u_int (*strIntMin)(const TEB_char*);
  TEB_small_u_int (*strIntS)(const TEB_char*);
  TEB_time_t (*httpDateToEpoch)(const TEB_char*, TEB_medium_int);
};

#endif