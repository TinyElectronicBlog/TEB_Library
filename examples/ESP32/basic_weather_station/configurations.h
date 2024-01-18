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

#ifndef configurations_h
#define configurations_h

#include "TEB_Library.h"

//ENTER THE NAME AND PASSWORD OF THE WIFI NETWORK
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

//ENTER THE NAME OF THE WORKSPACE FOLDER
#define WORKSPACE_FOLDER_NAME "Workspace TEST"  //Maximum length of 50 characters
//ENTER THE UNIQUE NAME OF THE DEVELOPMENT BOARD
#define DEVICE_ID "Weather station"  //Maximum length of 50 characters

//ENTER THE SETTINGS (THEY ARE NEGLECTED IF THEY DIFFER FROM THOSE IN THE ONLINE DEVICE FILE)
#define LANGUAGE 1                  //0 Italiano, 1 English
#define TEMPERATURE_IN 0            //0 Celsius, 1 Fahreheit
#define SEA_LEVEL_PRESSURE 1013.25  // the current hPa at sea level
#define DATA_UPDATE_INTERVAL 10     // in seconds
#define DISPLAY_STATUS true;        //true = disply on

//ENTER THE TIME ZONE AND THE DEFINITION OF DST
#define TIME_ZONE_DATABASE_NAME "Europe/Rome"  //TZ database name
#define TIME_ZONE_UTC_OFFSET_HOUR 1            //UTC hour offset in standard time
#define TIME_ZONE_UTC_OFFSET_MINUTE 0          //UTC minute offset in standard
#define DST_START_MONTH 3
#define DST_START_DAY_OF_THE_WEEK 1      //1 for Sunday, 2 for Monday, 3 for Tuesday, ..., 7 for Saturday
#define DST_START_TH_DAY_OF_THE_WEEK -1  //1 if dst_start[1] refers to the first week of the month or -1 for the last, 2 for the second week of the month or -2 for the penultimate ... (max +5 or -5 included);
#define DST_START_HOURS 2
#define DST_START_MINUTES 0
#define DST_END_MONTH 10
#define DST_END_DAY_OF_THE_WEEK 1      //1 for Sunday, 2 for Monday, 3 for Tuesday, ..., 7 for Saturday
#define DST_END_TH_DAY_OF_THE_WEEK -1  //1 if dst_end[1] refers to the first week of the month or -1 for the last, 2 for the second week of the month or -2 for the penultimate ... (max +5 or -5 included);
#define DST_END_HOURS 3
#define DST_END_MINUTES 0

//DHT22 SENSOR CONNECTION PIN
#define DHT22_DIGITAL_PIN 14

#define SIMULATE_DHT22_SENSOR   //UNCOMMENT IF A DHT22 SENSOR IS NOT CONNECTED TO THE DEVICE
#define SIMULATE_BMP280_SENSOR  //UNCOMMENT IF A BMP280 SENSOR IS NOT CONNECTED TO THE DEVICE

#endif
