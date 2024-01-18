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

#ifndef TEB_TimeZoneDST_h
#define TEB_TimeZoneDST_h

#include "TEB_Clock.h"

/**
	\brief This file contains the definition of struct TEB_TimeZoneDST_struct, designed to contain the definitions of a time zone, a dst, and be associated with a TEB_Clock_struct. 
*/

/**
\brief This structure can contain the definitions of a time zone and a dst; it is designed to be associated with a struct TEB_Clock_struct.
	time_zone_database_name: a TZ database name (for more information see https://en.wikipedia.org/wiki/List_of_tz_database_time_zones);
	time_zone_utc_offset[0]: UTC hour offset in standard time (for more information see https://en.wikipedia.org/wiki/List_of_tz_database_time_zones);
	time_zone_utc_offset[1]: UTC minute offset in standard time (for more information see https://en.wikipedia.org/wiki/List_of_tz_database_time_zones);
	dst_start[0]: dst start month (must be >= -1 and <= 12);
	dst_start[1]: day of the week on which dst begins (enter 1 for Sunday, 2 for Monday, 3 for Tuesday, ..., 7 for Saturday);
	dst_start[2]: set to 1 if dst_start[1] refers to the first week of the month or -1 for the last, 2 for the second week of the month or -2 for the penultimate ... (max +5 or -5 included);
	dst_start[3]: dst start hours, is considered solar time by definition (must be >= 0 and <= 23);
	dst_start[4]: dst start minutes, is considered solar time by definition (must be >= 0 and <= 59);
	dst_end[0]: dst end month (must be >= -1 and <= 12);
	dst_end[1]: day of the week on which dst ends (enter 1 for Sunday, 2 for Monday, 3 for Tuesday, ..., 7 for Saturday);
	dst_end[2]: set to 1 if dst_end[1] refers to the first week of the month or -1 for the last, 2 for the second week of the month or -2 for the penultimate ... (max +5 or -5 included);
	dst_end[3]: dst end hours, is considered daylight saving time by definition (must be >= 0 and <= 23);
	dst_end[4]: dst end minutes, is considered daylight saving time by definition (must be >= 0 and <= 59);
	Set dst_start[0] and dst_end[0] both to 0 to indicate dst never applied.
	Set dst_start[0] and dst_end[0] both to -1 to indicate dst always applied.
	The definition of beginning dst is considered to be daylight saving time, while the definition of ending time is considered to be standard time. 
*/
struct TEB_TimeZoneDST_struct {
  char time_zone_database_name[35];
  TEB_small_int time_zone_utc_offset[2];
  TEB_small_int dst_start[5];
  TEB_small_int dst_end[5];
};

/**
	\brief Initialize a TEB_TimeZoneDST_struct.
	\param [in] tz_dst_to_init Structure to be initialized.
	\param [in] time_zone_database_name The TZ database name.
	\param [in] time_zone_utc_offset The UTC offsets in standard time.
	\param [in] dst_start Definition of the beginning of the dst. 
	\param [in] dst_end Definition of the end of the dst.
	\details For more information on input parameters see the description of struct TEB_TimeZoneDST_struct.
*/
TEB_small_int TEB_TimeZoneDST_struct_init (struct TEB_TimeZoneDST_struct* tz_dst_to_init,
                                          const char* time_zone_database_name,
                                          TEB_small_int time_zone_utc_offset[2],
                                          TEB_small_int dst_start[5],
                                          TEB_small_int dst_end[5]);

/**     
	\brief Set a clock on the desired epoch considering time zone and dst.
	\param [in] clock_to_adjust Clock to set.
	\param [in] time_zone_dst_to_set Time zone and DST to set (for more information see the description of struct TEB_TimeZoneDST_struct).
	\param [in] epoch_to_set_in_seconds Epoch in seconds to set.
	\param [in] epoch_to_set_is_dst Set to 1 if epoch_to_set_in_seconds is DST, otherwise 0.
	\param [in] epoch_to_set_is_utc Set to 1 if epoch_to_set_in_seconds is UTC, otherwise 0.
	\return 1 if all ok.
*/
TEB_small_int TEB_TimeZoneDST_set_epoch (struct TEB_Clock_struct* clock_to_adjust,
                                        const struct TEB_TimeZoneDST_struct* time_zone_dst_to_set,
                                        TEB_time_t epoch_to_set_in_seconds,
                                        TEB_bool epoch_to_set_is_dst,
                                        TEB_bool epoch_to_set_is_utc);

/**     
	\brief Set a clock on the desired time considering time zone and dst.
	\param [in] clock_to_adjust Clock to set.
	\param [in] time_zone_dst_to_set Time zone and DST to set (for more information see the description of struct TEB_TimeZoneDST_struct).
	\param [in] time_to_set Time to set.
	\param [in] time_to_set_is_dst Set to 1 if time_to_set is DST, otherwise 0.
	\param [in] time_to_set_is_utc Set to 1 if time_to_set is UTC, otherwise 0.
	\return 1 if all ok.
*/
TEB_small_int TEB_TimeZoneDST_set_time (struct TEB_Clock_struct* clock_to_adjust,
                                       const struct TEB_TimeZoneDST_struct* time_zone_dst_to_set,
                                       const struct TEB_TimeManagement_struct* time_to_set,
                                       TEB_bool time_to_set_is_dst,
                                       TEB_bool time_to_set_is_utc);

/**     
	\brief Convert a struct TEB_Clock_struct to epoch considering time zone and dst.
	\param [in] clock_to_convert Clock to convert.
	\param [in] time_zone_dst_to_consider Time zone and DST to consider (for more information see the description of struct TEB_TimeZoneDST_struct).
	\param [in] neglect_time_zone Set to 1 to neglect the time zone, otherwise 0.
	\param [in] neglect_dst Set to 1 to neglect the dst (always consider solar time), otherwise 0.
	\return The epoch.	   	  
*/
TEB_time_t TEB_TimeZoneDST_get_epoch (const struct TEB_Clock_struct* clock_to_convert,
                                     const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                     TEB_bool neglect_time_zone,
                                     TEB_bool neglect_dst);

/**     
	\brief Convert a struct TEB_Clock_struct to struct TEB_TimeManagement_struct considering time zone and dst.
	\param [in] clock_to_convert Clock to convert.
	\param [in] time_zone_dst_to_consider Time zone and DST to consider (for more information see the description of struct TEB_TimeZoneDST_struct).
	\param [in] neglect_time_zone Set to 1 to neglect the time zone, otherwise 0.
	\param [in] neglect_dst Set to 1 to neglect the dst (always consider solar time), otherwise 0.
	\param [in] time_converted Where to save the struct TEB_TimeManagement_struct converted.
	\return 1 if all ok.   	  
*/
TEB_small_int TEB_TimeZoneDST_get_time (const struct TEB_Clock_struct* clock_to_convert,
                                       const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                       TEB_bool neglect_time_zone,
                                       TEB_bool neglect_dst,
                                       struct TEB_TimeManagement_struct* time_converted);

/**     
	\brief Execute TEB_TimeZoneDST_get_time and returns the seconds of the obtained struct TEB_TimeManagement_struct.
	\param [in] clock_to_convert Clock to convert.
	\param [in] time_zone_dst_to_consider Time zone and DST to consider (for more information see the description of struct TEB_TimeZoneDST_struct).
	\param [in] neglect_time_zone Set to 1 to neglect the time zone, otherwise 0.
	\param [in] neglect_dst Set to 1 to neglect the dst (always consider solar time), otherwise 0.
	\return The seconds of the obtained struct TEB_TimeManagement_struct.  	  
*/
TEB_small_int TEB_TimeZoneDST_get_s (const struct TEB_Clock_struct* clock_to_convert,
                                    const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                    TEB_bool neglect_time_zone,
                                    TEB_bool neglect_dst);

/**     
	\brief Execute TEB_TimeZoneDST_get_time and returns the minutes of the obtained struct TEB_TimeManagement_struct.
	\param [in] clock_to_convert Clock to convert.
	\param [in] time_zone_dst_to_consider Time zone and DST to consider (for more information see the description of struct TEB_TimeZoneDST_struct).
	\param [in] neglect_time_zone Set to 1 to neglect the time zone, otherwise 0.
	\param [in] neglect_dst Set to 1 to neglect the dst (always consider solar time), otherwise 0.
	\return The minutes of the obtained struct TEB_TimeManagement_struct.  	  
*/
TEB_small_int TEB_TimeZoneDST_get_min (const struct TEB_Clock_struct* clock_to_convert,
                                      const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                      TEB_bool neglect_time_zone,
                                      TEB_bool neglect_dst);

/**     
	\brief Execute TEB_TimeZoneDST_get_time and returns the hours of the obtained struct TEB_TimeManagement_struct.
	\param [in] clock_to_convert Clock to convert.
	\param [in] time_zone_dst_to_consider Time zone and DST to consider (for more information see the description of struct TEB_TimeZoneDST_struct).
	\param [in] neglect_time_zone Set to 1 to neglect the time zone, otherwise 0.
	\param [in] neglect_dst Set to 1 to neglect the dst (always consider solar time), otherwise 0.
	\return The hours of the obtained struct TEB_TimeManagement_struct.  	  
	*/
TEB_small_int TEB_TimeZoneDST_get_h (const struct TEB_Clock_struct* clock_to_convert,
                                    const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                    TEB_bool neglect_time_zone,
                                    TEB_bool neglect_dst);

/**     
       \brief Execute TEB_TimeZoneDST_get_time and returns the days of the obtained struct TEB_TimeManagement_struct.
	   \param [in] clock_to_convert Clock to convert.
	   \param [in] time_zone_dst_to_consider Time zone and DST to consider (for more information see the description of struct TEB_TimeZoneDST_struct).
	   \param [in] neglect_time_zone Set to 1 to neglect the time zone, otherwise 0.
	   \param [in] neglect_dst Set to 1 to neglect the dst (always consider solar time), otherwise 0.
	   \return The days of the obtained struct TEB_TimeManagement_struct.  	  
    */
TEB_small_int TEB_TimeZoneDST_get_d (const struct TEB_Clock_struct* clock_to_convert,
                                    const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                    TEB_bool neglect_time_zone,
                                    TEB_bool neglect_dst);

/**     
       \brief Execute TEB_TimeZoneDST_get_time and returns the month of the obtained struct TEB_TimeManagement_struct.
	   \param [in] clock_to_convert Clock to convert.
	   \param [in] time_zone_dst_to_consider Time zone and DST to consider (for more information see the description of struct TEB_TimeZoneDST_struct).
	   \param [in] neglect_time_zone Set to 1 to neglect the time zone, otherwise 0.
	   \param [in] neglect_dst Set to 1 to neglect the dst (always consider solar time), otherwise 0.
	   \return The month of the obtained struct TEB_TimeManagement_struct.  	  
    */
TEB_small_int TEB_TimeZoneDST_get_mon (const struct TEB_Clock_struct* clock_to_convert,
                                      const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                      TEB_bool neglect_time_zone,
                                      TEB_bool neglect_dst);

/**     
       \brief Execute TEB_TimeZoneDST_get_time and returns the year of the obtained struct TEB_TimeManagement_struct.
	   \param [in] clock_to_convert Clock to convert.
	   \param [in] time_zone_dst_to_consider Time zone and DST to consider (for more information see the description of struct TEB_TimeZoneDST_struct).
	   \param [in] neglect_time_zone Set to 1 to neglect the time zone, otherwise 0.
	   \param [in] neglect_dst Set to 1 to neglect the dst (always consider solar time), otherwise 0.
	   \return The year of the obtained struct TEB_TimeManagement_struct.  	
	   \details If an error occurs, the function returns -30000, which is also among the correct values that can be returned.
    */
TEB_medium_int TEB_TimeZoneDST_get_y (const struct TEB_Clock_struct* clock_to_convert,
                                     const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                     TEB_bool neglect_time_zone,
                                     TEB_bool neglect_dst);

/**     
       \brief Execute TEB_TimeZoneDST_get_time and returns the weekday of the obtained struct TEB_TimeManagement_struct.
	   \param [in] clock_to_convert Clock to convert.
	   \param [in] time_zone_dst_to_consider Time zone and DST to consider (for more information see the description of struct TEB_TimeZoneDST_struct).
	   \param [in] neglect_time_zone Set to 1 to neglect the time zone, otherwise 0.
	   \param [in] neglect_dst Set to 1 to neglect the dst (always consider solar time), otherwise 0.
	   \return The weekday of the obtained struct TEB_TimeManagement_struct.  	  
    */
TEB_small_int TEB_TimeZoneDST_get_weekday (const struct TEB_Clock_struct* clock_to_convert,
                                          const struct TEB_TimeZoneDST_struct* time_zone_dst_to_consider,
                                          TEB_bool neglect_time_zone,
                                          TEB_bool neglect_dst);

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_TimeZoneDST_test ();
#endif

struct TEB_TimeZoneDST_rename_f {
  TEB_small_int (*init)(struct TEB_TimeZoneDST_struct*, const char*, TEB_small_int[], TEB_small_int[], TEB_small_int[]);
  TEB_small_int (*setEpoch)(struct TEB_Clock_struct*, const struct TEB_TimeZoneDST_struct*, TEB_time_t, TEB_bool, TEB_bool);
  TEB_small_int (*setTime)(struct TEB_Clock_struct* clock_to_adjust, const struct TEB_TimeZoneDST_struct*, const struct TEB_TimeManagement_struct*, TEB_bool, TEB_bool);
  TEB_time_t (*epoch)(const struct TEB_Clock_struct*, const struct TEB_TimeZoneDST_struct*, TEB_bool, TEB_bool);
  TEB_small_int (*time)(const struct TEB_Clock_struct*, const struct TEB_TimeZoneDST_struct*, TEB_bool, TEB_bool, struct TEB_TimeManagement_struct*);
  TEB_small_int (*s)(const struct TEB_Clock_struct*, const struct TEB_TimeZoneDST_struct*, TEB_bool, TEB_bool);
  TEB_small_int (*min)(const struct TEB_Clock_struct*, const struct TEB_TimeZoneDST_struct*, TEB_bool, TEB_bool);
  TEB_small_int (*h)(const struct TEB_Clock_struct*, const struct TEB_TimeZoneDST_struct*, TEB_bool, TEB_bool);
  TEB_small_int (*d)(const struct TEB_Clock_struct*, const struct TEB_TimeZoneDST_struct*, TEB_bool, TEB_bool);
  TEB_small_int (*mon)(const struct TEB_Clock_struct*, const struct TEB_TimeZoneDST_struct*, TEB_bool, TEB_bool);
  TEB_medium_int (*y)(const struct TEB_Clock_struct*, const struct TEB_TimeZoneDST_struct*, TEB_bool, TEB_bool);
  TEB_small_int (*w)(const struct TEB_Clock_struct*, const struct TEB_TimeZoneDST_struct*, TEB_bool, TEB_bool);
};

#endif