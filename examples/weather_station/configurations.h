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

#ifndef configurations_h
#define configurations_h

//ENTER THE NAME AND PASSWORD OF THE WIFI NETWORK
#define WIFI_SSID "WiFi"
#define WIFI_PASSWORD "password"

//ENTER THE NAME OF THE WORKSPACE FOLDER
#define WORKSPACE_FOLDER_NAME "Workspace TEST" //Maximum length of 50 characters
//ENTER THE UNIQUE NAME OF THE DEVELOPMENT BOARD
#define DEVICE_ID "Weather station" //Maximum length of 50 characters

//ENTER THE SETTINGS (THEY ARE NEGLECTED IF THEY DIFFER FROM THOSE IN THE ONLINE DEVICE FILE)
#define LANGUAGE 1 //0 Italiano, 1 English
#define TEMPERATURE_IN 0 //0 Celsius, 1 Fahreheit
#define SEA_LEVEL_PRESSURE 1013.25 // the current hPa at sea level
#define DATA_UPDATE_INTERVAL 10 // in seconds
#define DISPLAY_STATUS true; //true = disply on

//Set the timezone and daylight saving time in the sketch setup() function

//DHT22 SENSOR CONNECTION PIN
#define DHT22_DIGITAL_PIN 14

#endif
