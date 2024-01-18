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

#include "device.h"

DHT dht(DHT22_DIGITAL_PIN, DHT22);  //Digital pin connected to the DHT sensor, DHT type
Adafruit_BMP280 bmp;
TEB_clock watch;
TEB_timeZoneDst tm;

char device::accessTokenBuffer[250];
char device::refreshTokenBuffer[250];

const char device::str1[] = "buttons: *C - *F, ENG - ITA, customizable value, DISPLAY ON - OFF;\nvalues: ";
const char device::str2_0[] = "Temperatura";
const char device::str2_1[] = "Temperature";
const char device::str3_C[] = " *C, ";
const char device::str3_F[] = " *F, ";
const char device::str4_0[] = "Umidita' relativa";
const char device::str4_1[] = "Relative humidity";
const char device::str5_0[] = " alle ";
const char device::str5_1[] = " at ";
const char device::str6_0[] = "Intervallo aggiornamento dati";
const char device::str6_1[] = "Data update interval";
const char device::str7_0[] = "Pressione livello del mare";
const char device::str7_1[] = "Sea level pressure";
const char device::str8[] = ", Display is ";
const char device::str9[] PROGMEM = "  STAZIONCINA METEO\n\nTEMPERATURA ";
const char device::str10[] PROGMEM = "   WEATHER STATION\n\nTEMPERATURE ";

uint8_t device::temperature_in = TEMPERATURE_IN;
uint8_t device::language = LANGUAGE;
float device::sea_level_pressure = SEA_LEVEL_PRESSURE;
uint32_t device::data_update_interval = DATA_UPDATE_INTERVAL;
bool device::display_status = DISPLAY_STATUS;

bool device::driveSynchronized = false;
char device::workspaceFolderID[60];
char device::deviceFileID[60];
char device::textBuffer[400];

float device::DHT22h;
float device::DHT22c;
float device::DHT22f;
float device::DHT22hif;
float device::DHT22hic;
float device::BMP280c;
float device::BMP280f;
float device::BMP280p;
float device::BMP280a;

device::device() {
  teb.time.clock.defaultInit(&watch);
  TEB_small_int time_zone_utc_offset[2];
  time_zone_utc_offset[0] = TIME_ZONE_UTC_OFFSET_HOUR;
  time_zone_utc_offset[1] = TIME_ZONE_UTC_OFFSET_MINUTE;
  TEB_small_int dst_start[5];
  dst_start[0] = DST_START_MONTH;
  dst_start[1] = DST_START_DAY_OF_THE_WEEK;
  dst_start[2] = DST_START_TH_DAY_OF_THE_WEEK;
  dst_start[3] = DST_START_HOURS;
  dst_start[4] = DST_START_MINUTES;
  TEB_small_int dst_end[5];
  dst_end[0] = DST_END_MONTH;
  dst_end[1] = DST_END_DAY_OF_THE_WEEK;
  dst_end[2] = DST_END_TH_DAY_OF_THE_WEEK;
  dst_end[3] = DST_END_HOURS;
  dst_end[4] = DST_END_MINUTES;
  teb.time.tz.init(&tm, TIME_ZONE_DATABASE_NAME, time_zone_utc_offset, dst_start, dst_end);
}

bool device::initializeSensors() {
#ifndef SIMULATE_DHT22_SENSOR
  dht.begin();
#endif
#ifndef SIMULATE_BMP280_SENSOR
  if (!bmp.begin(BMP280_ADDRESS_ALT)) {
    if (device::language == 0) teb.device.displayPrint(1, "Problemi col sensore BMP280 :(\nProva a resettare il dispositivo!", 1, 1);
    else if (device::language == 1) teb.device.displayPrint(1, "Problems with BMP280 sensor:(\nTry resetting the device!", 1, 1);
    teb.device.debugPrint("BMP280 ERROR");
    return false;
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
#endif
  return true;
}

uint8_t device::getLanguage() {
  return device::language;
}

uint32_t device::getDataUpdateInterval() {
  return device::data_update_interval;
}

bool device::readSensorValues() {
  teb.device.delay(2000, 1);
#ifndef SIMULATE_DHT22_SENSOR
  DHT22h = dht.readHumidity();
  DHT22c = dht.readTemperature();
  DHT22f = dht.readTemperature(true);
#endif
#ifdef SIMULATE_DHT22_SENSOR
  DHT22h = 50;
  DHT22c = 20;
  DHT22f = 68;
#endif
  if (isnan(DHT22h) || isnan(DHT22c) || isnan(DHT22f)) {
    return false;
  }
#ifndef SIMULATE_DHT22_SENSOR
  DHT22hif = dht.computeHeatIndex(DHT22f, DHT22h, true);
  DHT22hic = dht.computeHeatIndex(DHT22c, DHT22h, false);
#endif
#ifdef SIMULATE_DHT22_SENSOR
  DHT22hif = 20;
  DHT22hic = 68;
#endif
#ifndef SIMULATE_BMP280_SENSOR
  BMP280c = bmp.readTemperature();
  BMP280f = (BMP280c * 1.8) + 32;
  BMP280p = bmp.readPressure();
  BMP280a = bmp.readAltitude(sea_level_pressure);
#endif
#ifdef SIMULATE_BMP280_SENSOR
  BMP280c = 20;
  BMP280f = 68;
  BMP280p = 1013;
  BMP280a = 0;
#endif
  return true;
}

bool device::timeSynchronization() {
  TEB_httpRequest req;
  req.server_address = "https://oauth2.googleapis.com";
  req.request_text = "POST \r\n\r\n";
  req.root_ca = "";
  req.server_port = 443;
  req.connection_timeout_in_ms = 5000;
  req.response_delay_in_ms = 5000;
  req.use_ssl = true;
  TEB_httpResponse httpResponse;
  char buf[190];
  teb.device.httpStandardSendRequest(&req, &httpResponse, buf, 190, 1);
  buf[189] = '\0';
  httpResponse.payload = (char*)teb.string.indexOf2(buf, "Date: ");
  if (httpResponse.payload != 0) httpResponse.payload = (char*)(teb.string.indexOf2(httpResponse.payload, ", ") + 2);
  else return false;
  if (httpResponse.payload != 0) httpResponse.header = (char*)teb.string.indexOf2(httpResponse.payload, " GMT");
  else return false;
  if (httpResponse.header != 0) *httpResponse.header = '\0';
  else return false;
  TEB_time_t epoch = teb.time.manage.httpDateToEpoch(httpResponse.payload, teb.time.clock.initialYearEpoch(&watch));
  teb.time.tz.setEpoch(&watch, &tm, epoch, false, true);
  return true;
}

void device::s3PrintText(const char* t) {
  teb.device.displayPrint(1, t, 1, 1);
}

int8_t device::isDriveSynchronized() {
  if (driveSynchronized) return 0;
  TEB_bool authenticated = false;
  if (get_refresh_token_from_the_eeprom(refreshTokenBuffer)) {
    teb.device.debugPrint("\nFOUND A REFRESH TOKEN IN MEMORY.\n");
    if (language == 0) teb.device.displayPrint(1, "Trovato un refresh token in memoria.\nRelogin in corso...", 1, 1);
    else if (language == 1) teb.device.displayPrint(1, "Found a refresh token in memory.\nRelogin in progress...", 1, 1);
    teb.device.delay(2000, 1);
    if (teb.google.oauth2.relogin(refreshTokenBuffer, accessTokenBuffer, NULL) == 1) {
      teb.device.debugPrint("\nRELOGIN OK.\n");
      if (language == 0) teb.device.displayPrint(1, "Relogin riuscito!", 1, 1);
      else if (language == 1) teb.device.displayPrint(1, "Relogin successful!", 1, 1);
      teb.device.delay(3000, 1);
      authenticated = true;
    } else {
      teb.device.debugPrint("\nRELOGIN KO.\n");
      if (language == 0) teb.device.displayPrint(1, "Relogin non riuscito.", 1, 1);
      else if (language == 1) teb.device.displayPrint(1, "Relogin failed.", 1, 1);
      teb.device.delay(2500, 1);
    }
  } else {
    teb.device.debugPrint("\nNOT FOUND A REFRESH TOKEN IN MEMORY.\n");
    if (language == 0) teb.device.displayPrint(1, "Refresh token non trovato in memoria.", 1, 1);
    else if (language == 1) teb.device.displayPrint(1, "Not found a refresh token in memory.", 1, 1);
    teb.device.delay(2500, 1);
  }
  if (!authenticated) {
    if (language == 0) teb.device.displayPrint(1, "Login in corso...", 1, 1);
    else if (language == 1) teb.device.displayPrint(1, "Login in progress...", 1, 1);
    teb.device.delay(2000, 1);
    if (teb.google.oauth2.login(accessTokenBuffer, refreshTokenBuffer, "https://www.googleapis.com/auth/drive.file", NULL, teb.google.oauth2.standardStep3ShowUserCode) != 1) {
      return -3;
    } else {
      teb.device.debugPrint("DRIVE LOGIN OK");
      if (language == 0) teb.device.displayPrint(1, "Accesso a Google Drive riuscito!", 1, 1);
      else if (language == 1) teb.device.displayPrint(1, "Google Drive login successful!", 1, 1);
      teb.device.delay(3000, 1);
      if (save_refresh_token_in_the_eeprom(refreshTokenBuffer)) teb.device.debugPrint("REFRESH TOKEN SAVED IN MEMORY");
      else teb.device.debugPrint("SAVING REFRESH TOKEN IN MEMORY FAILED");
    }
  }
  char b[151];
  teb.string.urlEncoding2(b, WORKSPACE_FOLDER_NAME);
  int8_t r = teb.google.rci.getWorkspaceFolderID(accessTokenBuffer, b, workspaceFolderID, NULL);
  if (r == 1 || r == 2) return r;
  if (r == 0) {
    r = teb.google.rci.newDeviceFile(accessTokenBuffer, DEVICE_ID, workspaceFolderID, deviceFileID, NULL);
    if (r == 0 || r == 1) {
      driveSynchronized = true;
      return 0;
    } else if (r == -2) { /*Error, found multiple device files. The Android Remote control  
						  cannot handle multiple device files properly, therefore they are all deleted.*/
      while (true) {
        if (teb.google.rci.deleteDeviceFile(accessTokenBuffer, deviceFileID, NULL) == 1) {
          if (r == 0) return -1;
          teb.string.urlEncoding2(b, DEVICE_ID);
          r = teb.google.rci.getDeviceFileID(accessTokenBuffer, b, workspaceFolderID, deviceFileID, NULL);
          if (r == 0 || r == -2) continue;
          if (r == 1) return -1;
          else return -2;
        } else return -2;
      }
    } else return -2;
  }
  return -4;
}

void device::printSensorValuesOnDisplay(bool isOnline) {
#ifdef TEB_DB_DEBUG
  teb.device.debugPrint("SENSOR DHT22:\nHumidity: ");
  teb.device.debugPrintInt(DHT22h);
  teb.device.debugPrint("%\nTemperature: ");
  teb.device.debugPrintInt(DHT22c);
  teb.device.debugPrint("°C - ");
  teb.device.debugPrintInt(DHT22f);
  teb.device.debugPrint("°F\nHeat index: ");
  teb.device.debugPrintInt(DHT22hic);
  teb.device.debugPrint("°C - ");
  teb.device.debugPrintInt(DHT22hif);
  teb.device.debugPrint(" °F\nSENSOR BMP280:\n");
  teb.device.debugPrint("Temperature = ");
  teb.device.debugPrintInt(BMP280c);
  teb.device.debugPrint(" °C - ");
  teb.device.debugPrintInt(BMP280f);
  teb.device.debugPrint(" °F\nPressure = ");
  teb.device.debugPrintInt(BMP280p);
  teb.device.debugPrint(" Pa\n");
  teb.device.debugPrint("Approx altitude = ");
  teb.device.debugPrintInt(BMP280a);
  teb.device.debugPrint(" m\n");
#endif
  char buffer[150];
  int d;
  char* p;
  if (language == 0) {
    p = teb.string.append2(buffer, str9);
  } else if (language == 1) {
    p = teb.string.append2(buffer, str10);
  }
  if (temperature_in == 0) {
    d = (int)DHT22c;
    p = teb.string.intStr(d, p);
    p = teb.string.append2(p, ".");
    p = teb.string.intStr((int)((DHT22c - d) * 100), p);
    p = teb.string.append2(p, " *C");
  } else if (temperature_in == 1) {
    d = (int)DHT22f;
    p = teb.string.intStr(d, p);
    p = teb.string.append2(p, ".");
    p = teb.string.intStr((int)((DHT22f - d) * 100), p);
    p = teb.string.append2(p, " *F");
  }
  if (language == 0) p = teb.string.append2(p, "\nUMIDITA' ");
  else if (language == 1) p = teb.string.append2(p, "\nHUMIDITY ");
  d = (int)DHT22h;
  p = teb.string.intStr(d, p);
  p = teb.string.append2(p, ".");
  p = teb.string.intStr((int)((DHT22h - d) * 100), p);
  if (language == 0) p = teb.string.append2(p, " %\nT. APPARENTE ");
  else if (language == 1) p = teb.string.append2(p, " %\nHEAT INDEX ");
  if (temperature_in == 0) {
    d = (int)DHT22hic;
    p = teb.string.intStr(d, p);
    p = teb.string.append2(p, ".");
    p = teb.string.intStr((int)((DHT22hic - d) * 100), p);
    p = teb.string.append2(p, " *C");
  } else if (temperature_in == 1) {
    d = (int)DHT22hif;
    p = teb.string.intStr(d, p);
    p = teb.string.append2(p, ".");
    p = teb.string.intStr((int)((DHT22hif - d) * 100), p);
    p = teb.string.append2(p, " *F");
  }
  if (language == 0) p = teb.string.append2(p, "\nPRESSIONE ");
  else if (language == 1) p = teb.string.append2(p, "\nPRESSURE ");
  d = (int)BMP280p;
  p = teb.string.intStr(d, p);
  p = teb.string.append2(p, ".");
  p = teb.string.intStr((int)((BMP280p - d) * 100), p);
  if (language == 0) p = teb.string.append2(p, " Pa\nALTITUDINE ");
  else if (language == 1) p = teb.string.append2(p, " Pa\nALTITUDE ");
  d = (int)BMP280a;
  p = teb.string.intStr(d, p);
  p = teb.string.append2(p, ".");
  p = teb.string.intStr((int)((BMP280a - d) * 100), p);
  p = teb.string.append2(p, " m");
  if (isOnline) teb.string.append2(p, "\n      ONLINE :D");
  if (display_status) teb.device.displayPrint(1, buffer, 1, 1);
}

void device::updateOfflineDeviceFile() {
  uint16_t i;
  char is[] = " is ";
  char* p = teb.string.append2(textBuffer, str1);
  if (language == 0) p = teb.string.append2(p, str2_0);
  else if (language == 1) p = teb.string.append2(p, str2_1);
  p = teb.string.append2(p, is);
  if (temperature_in == 0) {
    i = DHT22c;
    p = teb.string.intStr(i, p);
    p = teb.string.append2(p, ".");
    p = teb.string.intStr((uint16_t)(((DHT22c - (float)i)) * 100), p);
    p = teb.string.append2(p, str3_C);
  } else if (temperature_in == 1) {
    i = DHT22f;
    p = teb.string.intStr(i, p);
    p = teb.string.append2(p, ".");
    p = teb.string.intStr((uint16_t)(((DHT22f - (float)i)) * 100), p);
    p = teb.string.append2(p, str3_F);
  }
  if (language == 0) p = teb.string.append2(p, str4_0);
  else if (language == 1) p = teb.string.append2(p, str4_1);
  p = teb.string.append2(p, is);
  p = teb.string.intStr((uint32_t)DHT22h, p);
  p = teb.string.append2(p, "%, ");
  if (language == 0) p = teb.string.append2(p, "T. percepita");
  else if (language == 1) p = teb.string.append2(p, "Heat index");
  p = teb.string.append2(p, is);
  if (temperature_in == 0) {
    i = DHT22hic;
    p = teb.string.intStr(i, p);
    p = teb.string.append2(p, ".");
    p = teb.string.intStr((uint16_t)(((DHT22hic - (float)i)) * 100), p);
    p = teb.string.append2(p, " *C, ");
  } else if (temperature_in == 1) {
    i = DHT22hif;
    p = teb.string.intStr(i, p);
    p = teb.string.append2(p, ".");
    p = teb.string.intStr((uint16_t)(((DHT22hif - (float)i)) * 100), p);
    p = teb.string.append2(p, " *F, ");
  }
  if (language == 0) p = teb.string.append2(p, "Pressione");
  else if (language == 1) p = teb.string.append2(p, "Pressure");
  p = teb.string.append2(p, is);
  i = BMP280p;
  p = teb.string.intStr(i, p);
  p = teb.string.append2(p, ".");
  p = teb.string.intStr((uint16_t)(((BMP280p - (float)i)) * 100), p);
  p = teb.string.append2(p, " hPa, ");
  if (language == 0) p = teb.string.append2(p, "Altitudine");
  else if (language == 1) p = teb.string.append2(p, "Altitude");
  p = teb.string.append2(p, is);
  i = BMP280a;
  p = teb.string.intStr(i, p);
  p = teb.string.append2(p, ".");
  p = teb.string.intStr((uint16_t)(((BMP280a - (float)i)) * 100), p);
  p = teb.string.append2(p, " m, ");
  if (language == 0) p = teb.string.append2(p, str7_0);
  else if (language == 1) p = teb.string.append2(p, str7_1);
  p = teb.string.append2(p, is);
  i = sea_level_pressure;
  p = teb.string.intStr(i, p);
  p = teb.string.append2(p, ".");
  i = ((sea_level_pressure - (float)i) + 1.0) * 100.0 + 0.1;
  char e[4];
  teb.string.intStr(i, e);
  p = teb.string.append2(p, e + 1);
  p = teb.string.append2(p, " hPa, ");
  if (language == 0) p = teb.string.append2(p, "Del");
  else if (language == 1) p = teb.string.append2(p, "Of");
  p = teb.string.append2(p, is);
  TEB_timeManagement t;
  teb.time.tz.time(&watch, &tm, false, false, &t);
  if (language == 0) {
    p = teb.string.intStr(t.day, p);
    *p = '-';
    p++;
    p = teb.string.intStr(t.month, p);
    *p = '-';
    p++;
    p = teb.string.intStr(t.year, p);
    p = teb.string.append2(p, str5_0);
  } else if (language == 1) {
    p = teb.string.intStr(t.year, p);
    *p = '-';
    p++;
    p = teb.string.intStr(t.month, p);
    *p = '-';
    p++;
    p = teb.string.intStr(t.day, p);
    p = teb.string.append2(p, str5_1);
  }
  p = teb.string.intStr(t.hour, p);
  *p = ':';
  p++;
  p = teb.string.intStr(t.minute, p);
  *p = ':';
  p++;
  p = teb.string.intStr(t.second, p);
  p = teb.string.append2(p, str8);
  if (display_status) p = teb.string.append2(p, "ON, ");
  else p = teb.string.append2(p, "OFF, ");
  if (language == 0) p = teb.string.append2(p, str6_0);
  else if (language == 1) p = teb.string.append2(p, str6_1);
  p = teb.string.append2(p, is);
  p = teb.string.intStr(data_update_interval, p);
  teb.string.append2(p, " s;");
}

int8_t device::updateOnlineDeviceFile() {
  return teb.google.rci.updateDeviceFileText(accessTokenBuffer, deviceFileID, textBuffer, NULL);
}

bool device::updateSettingsFromOnlineDeviceFile() {
  char* p = (char*)teb.string.indexOf2(textBuffer, "values: ");
  char* p2;
  if (p == NULL) return false;
  if (teb.string.indexOf2(p, str3_C) != NULL) temperature_in = 0;
  else if (teb.string.indexOf2(p, str3_F) != NULL) temperature_in = 1;
  else return false;
  if (language == 0) {
    p = (char*)teb.string.indexOf2(p, str7_0);
    if (p == NULL) return false;
    p = p + 30;
    p2 = p + 1;
    while (*p2 != ' ') p2++;
    if (!set_sea_level_pressure(p, p2)) return false;
  } else if (language == 1) {
    p = (char*)teb.string.indexOf2(p, str7_1);
    if (p == NULL) return false;
    p = p + 22;
    p2 = p + 1;
    while (*p2 != ' ') p2++;
    if (!set_sea_level_pressure(p, p2)) return false;
  } else return false;
  p = (char*)teb.string.indexOf2(p, str8);
  if (p == NULL) return false;
  p = p + 14;
  if (*p == 'N') display_status = true;
  else if (*p == 'F') {
    display_status = false;
    teb.device.displayPrint(1, "", 1, 1);
  } else return false;
  if (language == 0) {
    p = (char*)teb.string.indexOf2(p, str6_0);
    if (p == 0) return false;
    p = p + 33;
    p2 = p + 1;
    while (*p2 != ' ') p2++;
    if (!set_data_update_interval(p, p2)) return false;
  } else if (language == 1) {
    p = (char*)teb.string.indexOf2(p, str6_1);
    if (p == NULL) return false;
    p = p + 24;
    p2 = p + 1;
    while (*p2 != ' ') p2++;
    if (!set_data_update_interval(p, p2)) return false;
  }
  return true;
}

int8_t device::verifyOnlineDeviceFile() {
  if (teb.google.rci.getDeviceFileText(accessTokenBuffer, deviceFileID, textBuffer, NULL) == 1) {
    if (teb.string.strlen(str1) > teb.string.strlen(textBuffer)) return -4;
    if (teb.string.indexOf2(textBuffer, str1) == NULL) return -2;
    if (teb.string.lastIndexOf2(textBuffer, str6_0) == NULL) {    //Italian language not found
      if (teb.string.lastIndexOf2(textBuffer, str6_1) == NULL) {  //English language not found
        return -3;
      } else {  // English language found
        language = 1;
        return 0;
      }
    } else {  // Italian language found
      language = 0;
      return 0;
    }
  } else return -1;
}

bool device::getDisplayStatus() {
  return display_status;
}

bool device::sendACK(uint8_t commandNumber) {
  switch (commandNumber) {
    case 1:
      if (teb.google.rci.sendCommandACK(accessTokenBuffer, DEVICE_ID, COMMAND_1, workspaceFolderID, NULL) == 1) return true;
      else return false;
      break;
    case 2:
      if (teb.google.rci.sendCommandACK(accessTokenBuffer, DEVICE_ID, COMMAND_2, workspaceFolderID, NULL) == 1) return true;
      else return false;
      break;
    case 3:
      if (teb.google.rci.sendCommandACK(accessTokenBuffer, DEVICE_ID, COMMAND_3, workspaceFolderID, NULL) == 1) return true;
      else return false;
      break;
  }
  return false;
}

void device::change_C_F() {
  if (temperature_in == 0) temperature_in = 1;
  else temperature_in = 0;
}

void device::changeLanguage() {
  if (language == 0) language = 1;
  else language = 0;
}

void device::displayOnOff() {
  if (display_status) {
    teb.device.displayPrint(1, "", 1, 1);
    display_status = false;
  } else display_status = true;
}

int8_t device::getCommand() {
  char commandNameBuffer[151];
  teb.string.urlEncoding2(commandNameBuffer, DEVICE_ID);
  int8_t r = teb.google.rci.isThereACK(accessTokenBuffer, commandNameBuffer, workspaceFolderID, NULL);
  if (r == 0) return 0;  //ack present online
  if (r != 1) return -10;
  //ack not present online
  switch (teb.google.rci.getCommand(accessTokenBuffer, DEVICE_ID, workspaceFolderID, commandNameBuffer, NULL)) {
    case 1:  // no online commands
      return 0;
    case 0:  // online command present
      if (teb.string.strlen(COMMAND_1) <= teb.string.strlen(commandNameBuffer)) {
        if (teb.string.indexOf2(commandNameBuffer, COMMAND_1) == commandNameBuffer && teb.string.strlen(commandNameBuffer) == teb.string.strlen(COMMAND_1)) {
          if (sendACK(1)) {  // I run the command only if I send the ak correctly
            change_C_F();
            return 1;
          } else return -1;
        }
      }
      if (strlen(COMMAND_2) <= teb.string.strlen(commandNameBuffer)) {
        if (teb.string.indexOf2(commandNameBuffer, COMMAND_2) == commandNameBuffer && teb.string.strlen(commandNameBuffer) == teb.string.strlen(COMMAND_2)) {
          if (sendACK(2)) {  // I run the command only if I send the ak correctly
            changeLanguage();
            return 2;
          } else return -2;
        }
      }
      if (strlen(COMMAND_3) <= strlen(commandNameBuffer)) {
        if (teb.string.indexOf2(commandNameBuffer, COMMAND_3) == commandNameBuffer && teb.string.strlen(commandNameBuffer) == teb.string.strlen(COMMAND_3)) {
          if (sendACK(3)) {  // I run the command only if I send the ak correctly
            displayOnOff();
            return 3;
          } else return -3;
        }
      }
      return -10;
  }
  return -11;
}

int8_t device::getCustomCommand() {
  char commandNameBuffer[60], b[151], b2[151];
  teb.string.urlEncoding2(b, DEVICE_ID);
  char* p;
  switch (teb.google.rci.getCustomCommand(accessTokenBuffer, DEVICE_ID, workspaceFolderID, commandNameBuffer, NULL)) {
    case 1:  //no custom command
      return 0;
    case 0:  //custom command present
      if (teb.string.strlen(COMMAND_4) <= teb.string.strlen(commandNameBuffer)) {
        p = (char*)teb.string.indexOf2(commandNameBuffer, COMMAND_4);
        if (p != NULL) {
          // I don't run the command if I can't delete the file online
          teb.string.urlEncoding2(b2, commandNameBuffer);
          if (teb.google.rci.deleteCustomCommand(accessTokenBuffer, b, b2, workspaceFolderID, NULL) == 1)
            if (set_sea_level_pressure(commandNameBuffer, p)) return 4;
          return -4;
        }
      }
      if (teb.string.strlen(COMMAND_5) <= teb.string.strlen(commandNameBuffer)) {
        p = (char*)teb.string.indexOf2(commandNameBuffer, COMMAND_5);
        if (p != NULL) {
          // I don't run the command if I can't delete the file online
          teb.string.urlEncoding2(b2, commandNameBuffer);
          if (teb.google.rci.deleteCustomCommand(accessTokenBuffer, b, b2, workspaceFolderID, NULL) == 1)
            if (set_data_update_interval(commandNameBuffer, p)) return 5;
          return -5;
        }
      }
      // command not recognized, I just delete it
      teb.string.urlEncoding2(b2, commandNameBuffer);
      if (teb.google.rci.deleteCustomCommand(accessTokenBuffer, b, b2, workspaceFolderID, NULL) == 1) return 6;
      else return -6;
  }
  return -11;
}

bool device::set_sea_level_pressure(const char* from, const char* to) {
  const char* p = from;
  while (*(to - 1) == ' ') to--;
  while (*p != '.' && *p != ',' && p != to) p++;
  if (*p == '.' || *p == ',') {
    if (teb.number.isInt2(from, p) && teb.number.isInt2(p + 1, to)) {
      uint32_t i = teb.number.strInt2(from, p);
      float d = teb.number.strInt2(p + 1, to);
      uint8_t l = to - (p + 1);
      while (l > 0) {
        d = d / 10;
        l--;
      }
      sea_level_pressure = d + i;
      return true;
    }
  }
  return false;
}

bool device::set_data_update_interval(const char* from, const char* to) {
  while (*(to - 1) == ' ') to--;
  if (teb.number.isInt2(from, to)) {
    data_update_interval = teb.number.strInt2(from, to);
    return true;
  }
  return false;
}

bool device::save_refresh_token_in_the_eeprom(const char* refresh_token) {
  TEB_medium_int l = teb.string.strlen(refresh_token);
  char b[l + 11];
  teb.string.append2(teb.string.append2(b, "teb9270716"), refresh_token);  //control string
  if (teb.device.memoryWrite(1, b, l + 11, sizeof(char), 1) == 1) return true;
  else return false;
}

bool device::get_refresh_token_from_the_eeprom(char* refresh_token_buffer) {
  char b[510];
  if (teb.device.memoryRead(1, b, 510, sizeof(char), 1) != 1) return false;
  if (teb.string.equals3(b, b + 10, "teb9270716") != 1) return false;  //control string absent
  teb.string.append(refresh_token_buffer, b + 10, b + 10 + teb.string.strlen(b + 10));
  return true;
}
