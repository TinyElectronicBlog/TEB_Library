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

#include "device.h"
#include <TimeLib.h>

DHT dht(DHT22_DIGITAL_PIN, DHT22); //Digital pin connected to the DHT sensor, DHT type
Adafruit_BMP280 bmp;

char device::accessTokenBuffer[250];

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

device::device () {}

bool device::initializeSensors () {
  dht.begin();
  if (!bmp.begin(BMP280_ADDRESS_ALT)) {
    if (device::language == 0) teb.db.display.print(F("Problemi col sensore BMP280 :(\nProva a resettare il dispositivo!"), 1);
    else if (device::language == 1) teb.db.display.print(F("Problems with BMP280 sensor:(\nTry resetting the device!"), 1);
#ifdef TEB_DB_DEBUG
    teb.db.debug.print(F("BMP280 ERROR"));
#endif
    return false;
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  return true;
}

uint8_t device::getLanguage () {
  return device::language;
}

uint32_t device::getDataUpdateInterval () {
  return device::data_update_interval;
}

bool device::readSensorValues () {
  delay(2000);
  DHT22h = dht.readHumidity();
  DHT22c = dht.readTemperature();
  DHT22f = dht.readTemperature(true);
  if (isnan(DHT22h) || isnan(DHT22c) || isnan(DHT22f)) {
    return false;
  }
  DHT22hif = dht.computeHeatIndex(DHT22f, DHT22h, true);
  DHT22hic = dht.computeHeatIndex(DHT22c, DHT22h, false);
  BMP280c = bmp.readTemperature();
  BMP280f = (BMP280c * 1.8) + 32;
  BMP280p = bmp.readPressure();
  BMP280a = bmp.readAltitude(sea_level_pressure);
  return true;
}

bool device::timeSynchronization () {
  TEB_HTTP::request req;
  req.serverAddress = "https://oauth2.googleapis.com";
  req.requestText = "POST \r\n\r\n";
  req.rootCA = "";
  req.serverPort = 443;
  req.connectionTimeout = 5000;
  req.responseDelay = 5000;
  TEB_HTTP::response httpResponse;
  char buf[190];
  teb.db.http.sendRequest(req, httpResponse, buf, 190);
  buf[189] = '\0';
  httpResponse.payload = (char*)teb.strings.indexOf(buf, "Date: ");
  if (httpResponse.payload != 0) httpResponse.payload = (char*)(teb.strings.indexOf(httpResponse.payload, ", ") + 2);
  else return false;
  if (httpResponse.payload != 0) httpResponse.header = (char*)teb.strings.indexOf(httpResponse.payload, " GMT");
  else return false;
  if (httpResponse.header != 0) *httpResponse.header = '\0';
  else return false;
  teb.db.clock.setDate(httpResponse.payload, true);
  return true;
}

void device::s3PrintText (const char* t) {
  TEB_Display::print(t, 1);
}

int8_t device::isDriveSynchronized () {
  if (driveSynchronized) return 0;
  if (teb.oauth2.relogin(accessTokenBuffer) != 1) {
    if (teb.oauth2.login("https://www.googleapis.com/auth/drive.file", accessTokenBuffer, true, s3PrintText) != 1 ) {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("DRIVE LOGIN KO"));
#endif
      if (language == 0) teb.db.display.print("Accesso a Google Drive non riuscito.", 1);
      else if (language == 1) teb.db.display.print("Google Drive login failed.", 1);
      delay(5000);
      return -81;
    }
  }
  teb.gdrive.setAccessToken(accessTokenBuffer);
  char b[151];
  teb.strings.percentEncoding(b, WORKSPACE_FOLDER_NAME);
  int8_t r = teb.rcinterface.getWorkspaceFolderID(b, workspaceFolderID);
  if (r == 1 || r == 2) return r;
  if (r == 0) {
    r = teb.rcinterface.newDeviceFile(DEVICE_ID, workspaceFolderID, deviceFileID);
    if (r == 0 || r == 1) {
      driveSynchronized = true;
      return 0;
    }
    else return -80;
  }
  return r;
}

void device::printSensorValuesOnDisplay (bool isOnline) {
#ifdef TEB_DB_DEBUG
  teb.db.debug.print(F("SENSOR DHT22:\nHumidity: ")); teb.db.debug.print(DHT22h); teb.db.debug.print(F("%\nTemperature: "));
  teb.db.debug.print(DHT22c); teb.db.debug.print(F("°C - ")); teb.db.debug.print(DHT22f); teb.db.debug.print(F("°F\nHeat index: "));
  teb.db.debug.print(DHT22hic); teb.db.debug.print(F("°C - ")); teb.db.debug.print(DHT22hif);
  teb.db.debug.print(F(" °F\nSENSOR BMP280:\n")); teb.db.debug.print(F("Temperature = ")); teb.db.debug.print(BMP280c);
  teb.db.debug.print(" °C - "); teb.db.debug.print(BMP280f); teb.db.debug.print(" °F\nPressure = ");
  teb.db.debug.print(BMP280p); teb.db.debug.print(" Pa\n"); teb.db.debug.print(F("Approx altitude = ")); teb.db.debug.print(bmp.readAltitude(sea_level_pressure)); Serial.println(" m");
#endif
  char buffer[150];
  int d;
  char* p;
  if (language == 0) {
    p = teb.strings.append_P(buffer, str9);
  }
  else if (language == 1) {
    p = teb.strings.append_P(buffer, str10);
  }
  if (temperature_in == 0) {
    d = (int)DHT22c;
    p = teb.strings.intChar(d, p);
    p = teb.strings.append(p, ".");
    p = teb.strings.intChar((int)((DHT22c - d) * 100), p);
    p = teb.strings.append(p, " *C");
  }
  else if (temperature_in == 1) {
    d = (int)DHT22f;
    p = teb.strings.intChar(d, p);
    p = teb.strings.append(p, ".");
    p = teb.strings.intChar((int)((DHT22f - d) * 100), p);
    p = teb.strings.append(p, " *F");
  }
  if (language == 0) p = teb.strings.append(p, "\nUMIDITA' ");
  else if (language == 1) p = teb.strings.append(p, "\nHUMIDITY ");
  d = (int)DHT22h;
  p = teb.strings.intChar(d, p);
  p = teb.strings.append(p, ".");
  p = teb.strings.intChar((int)((DHT22h - d) * 100), p);
  if (language == 0) p = teb.strings.append(p, " %\nT. APPARENTE ");
  else if (language == 1) p = teb.strings.append(p, " %\nHEAT INDEX ");
  if (temperature_in == 0) {
    d = (int)DHT22hic;
    p = teb.strings.intChar(d, p);
    p = teb.strings.append(p, ".");
    p = teb.strings.intChar((int)((DHT22hic - d) * 100), p);
    p = teb.strings.append(p, " *C");
  }
  else if (temperature_in == 1) {
    d = (int)DHT22hif;
    p = teb.strings.intChar(d, p);
    p = teb.strings.append(p, ".");
    p = teb.strings.intChar((int)((DHT22hif - d) * 100), p);
    p = teb.strings.append(p, " *F");
  }
  if (language == 0) p = teb.strings.append(p, "\nPRESSIONE ");
  else if (language == 1) p = teb.strings.append(p, "\nPRESSURE ");
  d = (int)BMP280p;
  p = teb.strings.intChar(d, p);
  p = teb.strings.append(p, ".");
  p = teb.strings.intChar((int)((BMP280p - d) * 100), p);
  if (language == 0) p = teb.strings.append(p, " Pa\nALTITUDINE ");
  else if (language == 1) p = teb.strings.append(p, " Pa\nALTITUDE ");
  d = (int)BMP280a;
  p = teb.strings.intChar(d, p);
  p = teb.strings.append(p, ".");
  p = teb.strings.intChar((int)((BMP280a - d) * 100), p);
  p = teb.strings.append(p, " m");
  if (isOnline) teb.strings.append(p, "\n      ONLINE :D");
  if (display_status) teb.db.display.print(buffer, 1);
}

void device::updateOfflineDeviceFile () {
  uint16_t i;
  char is[] = " is ";
  char* p = teb.strings.append(textBuffer, str1);
  if (language == 0) p = teb.strings.append(p, str2_0);
  else if (language == 1) p = teb.strings.append(p, str2_1);
  p = teb.strings.append(p, is);
  if (temperature_in == 0) {
    i = DHT22c;
    p = teb.strings.intChar(i, p);
    p = teb.strings.append(p, ".");
    p = teb.strings.intChar((uint16_t)(((DHT22c - (float)i)) * 100), p);
    p = teb.strings.append(p, str3_C);
  }
  else if (temperature_in == 1) {
    i = DHT22f;
    p = teb.strings.intChar(i, p);
    p = teb.strings.append(p, ".");
    p = teb.strings.intChar((uint16_t)(((DHT22f - (float)i)) * 100), p);
    p = teb.strings.append(p, str3_F);
  }
  if (language == 0) p = teb.strings.append(p, str4_0);
  else if (language == 1) p = teb.strings.append(p, str4_1);
  p = teb.strings.append(p, is);
  p = teb.strings.intChar((uint32_t)DHT22h, p);
  p = teb.strings.append(p, "%, ");
  if (language == 0) p = teb.strings.append(p, "T. percepita");
  else if (language == 1) p = teb.strings.append(p, "Heat index");
  p = teb.strings.append(p, is);
  if (temperature_in == 0) {
    i = DHT22hic;
    p = teb.strings.intChar(i, p);
    p = teb.strings.append(p, ".");
    p = teb.strings.intChar((uint16_t)(((DHT22hic - (float)i)) * 100), p);
    p = teb.strings.append(p, " *C, ");
  }
  else if (temperature_in == 1) {
    i = DHT22hif;
    p = teb.strings.intChar(i, p);
    p = teb.strings.append(p, ".");
    p = teb.strings.intChar((uint16_t)(((DHT22hif - (float)i)) * 100), p);
    p = teb.strings.append(p, " *F, ");
  }
  if (language == 0) p = teb.strings.append(p, "Pressione");
  else if (language == 1) p = teb.strings.append(p, "Pressure");
  p = teb.strings.append(p, is);
  i = BMP280p;
  p = teb.strings.intChar(i, p);
  p = teb.strings.append(p, ".");
  p = teb.strings.intChar((uint16_t)(((BMP280p - (float)i)) * 100), p);
  p = teb.strings.append(p, " hPa, ");
  if (language == 0) p = teb.strings.append(p, "Altitudine");
  else if (language == 1) p = teb.strings.append(p, "Altitude");
  p = teb.strings.append(p, is);
  i = BMP280a;
  p = teb.strings.intChar(i, p);
  p = teb.strings.append(p, ".");
  p = teb.strings.intChar((uint16_t)(((BMP280a - (float)i)) * 100), p);
  p = teb.strings.append(p, " m, ");
  if (language == 0) p = teb.strings.append(p, str7_0);
  else if (language == 1) p = teb.strings.append(p, str7_1);
  p = teb.strings.append(p, is);
  i = sea_level_pressure;
  p = teb.strings.intChar(i, p);
  p = teb.strings.append(p, ".");
  i = ((sea_level_pressure - (float)i) + 1.0) * 100.0 + 0.1;
  char e[4];
  teb.strings.intChar(i, e);
  p = teb.strings.append(p, e + 1);
  p = teb.strings.append(p, " hPa, ");
  if (language == 0) p = teb.strings.append(p, "Del");
  else if (language == 1) p = teb.strings.append(p, "Of");
  p = teb.strings.append(p, is);
  uint32_t t = teb.db.clock.getDate(false);
  if (language == 0) {
    p = teb.strings.intChar(day(t), p);
    *p = '-'; p++;
    p = teb.strings.intChar(month(t), p);
    *p = '-'; p++;
    p = teb.strings.intChar(year(t), p);
    p = teb.strings.append(p, str5_0);
  }
  else if (language == 1) {
    p = teb.strings.intChar(year(t), p);
    *p = '-'; p++;
    p = teb.strings.intChar(month(t), p);
    *p = '-'; p++;
    p = teb.strings.intChar(day(t), p);
    p = teb.strings.append(p, str5_1);
  }
  p = teb.strings.intChar(hour(t), p);
  *p = ':'; p++;
  p = teb.strings.intChar(minute(t), p);
  *p = ':'; p++;
  p = teb.strings.intChar(second(t), p);
  p = teb.strings.append(p, str8);
  if (display_status) p = teb.strings.append(p, "ON, ");
  else p = teb.strings.append(p, "OFF, ");
  if (language == 0) p = teb.strings.append(p, str6_0);
  else if (language == 1) p = teb.strings.append(p, str6_1);
  p = teb.strings.append(p, is);
  p = teb.strings.intChar(data_update_interval, p);
  teb.strings.append(p, " s;");
}

int8_t device::updateOnlineDeviceFile () {
  return teb.rcinterface.updateDeviceFileText(deviceFileID, textBuffer);
}

bool device::updateSettingsFromOnlineDeviceFile () {
  char* p = (char*)teb.strings.indexOf(textBuffer, "values: ");
  char* p2;
  if (p == 0) return false;
  if (teb.strings.indexOf(p, str3_C) != 0) temperature_in = 0;
  else if (teb.strings.indexOf(p, str3_F) != 0) temperature_in = 1;
  else return false;
  if (language == 0) {
    p = (char*)teb.strings.indexOf(p, str7_0);
    if (p == 0) return false;
    p = p + 30;
    p2 = p + 1;
    while (*p2 != ' ') p2++;
    if (!set_sea_level_pressure(p, p2)) return false;
  }
  else if (language == 1) {
    p = (char*)teb.strings.indexOf(p, str7_1);
    if (p == 0) return false;
    p = p + 22;
    p2 = p + 1;
    while (*p2 != ' ') p2++;
    if (!set_sea_level_pressure(p, p2)) return false;
  }
  else return false;
  p = (char*)teb.strings.indexOf(p, str8);
  if (p == 0) return false;
  p = p + 14;
  if (*p == 'N') display_status = true;
  else if (*p == 'F') {
    display_status = false;
    teb.db.display.print("", 1);
  }
  else return false;
  if (language == 0) {
    p = (char*)teb.strings.indexOf(p, str6_0);
    if (p == 0) return false;
    p = p + 33;
    p2 = p + 1;
    while (*p2 != ' ') p2++;
    if (!set_data_update_interval(p, p2)) return false;
  }
  else if (language == 1) {
    p = (char*)teb.strings.indexOf(p, str6_1);
    if (p == 0) return false;
    p = p + 24;
    p2 = p + 1;
    while (*p2 != ' ') p2++;
    if (!set_data_update_interval(p, p2)) return false;
  }
  return true;
}

int8_t device::verifyOnlineDeviceFile () {
  if (teb.rcinterface.getDeviceFileText(deviceFileID, textBuffer) == 1) {
    if (strlen(str1) > strlen(textBuffer)) return -4;
    if (teb.strings.indexOf(textBuffer, str1) == 0) return -2;
    if (teb.strings.lastIndexOf(textBuffer, str6_0) == 0) { //Italian language not found
      if (teb.strings.lastIndexOf(textBuffer, str6_1) == 0) { //English language not found
        return -3;
      }
      else { // English language found
        language = 1;
        return 0;
      }
    }
    else {// Italian language found
      language = 0;
      return 0;
    }
  }
  else return -1;
}

bool device::getDisplayStatus () {
  return display_status;
}

bool device::sendACK (uint8_t commandNumber) {
  switch (commandNumber) {
    case 1:
      if (teb.rcinterface.sendCommandACK(DEVICE_ID, COMMAND_1, workspaceFolderID) == 1) return true;
      else return false;
      break;
    case 2:
      if (teb.rcinterface.sendCommandACK(DEVICE_ID, COMMAND_2, workspaceFolderID) == 1) return true;
      else return false;
      break;
    case 3:
      if (teb.rcinterface.sendCommandACK(DEVICE_ID, COMMAND_3, workspaceFolderID) == 1) return true;
      else return false;
      break;
  }
  return false;
}

void device::change_C_F () {
  if (temperature_in == 0) temperature_in = 1;
  else temperature_in = 0;
}

void device::changeLanguage () {
  if (language == 0) language = 1;
  else language = 0;
}

void device::displayOnOff () {
  if (display_status) {
    teb.db.display.print("", 1);
    display_status = false;
  }
  else display_status = true;
}

int8_t device::getCommand () {
  char commandNameBuffer[151];
  teb.strings.percentEncoding(commandNameBuffer, DEVICE_ID);
  int8_t r = teb.rcinterface.isThereACK(commandNameBuffer, workspaceFolderID);
  if (r == 0) return 0; //ack present online
  if (r != 1) return -10;
  //ack not present online
  switch (teb.rcinterface.getCommand(DEVICE_ID, workspaceFolderID, commandNameBuffer)) {
    case 1: // no online commands
      return 0;
    case 0: // online command present
      if (strlen(COMMAND_1) <= strlen(commandNameBuffer)) {
        if (teb.strings.indexOf(commandNameBuffer, COMMAND_1) == commandNameBuffer && strlen(commandNameBuffer) == strlen(COMMAND_1)) {
          if (sendACK(1)) {// I run the command only if I send the ak correctly
            change_C_F();
            return 1;
          }
          else return -1;
        }
      }
      if (strlen(COMMAND_2) <= strlen(commandNameBuffer)) {
        if (teb.strings.indexOf(commandNameBuffer, COMMAND_2) == commandNameBuffer && strlen(commandNameBuffer) == strlen(COMMAND_2)) {
          if (sendACK(2)) { // I run the command only if I send the ak correctly
            changeLanguage();
            return 2;
          }
          else return -2;
        }
      }
      if (strlen(COMMAND_3) <= strlen(commandNameBuffer)) {
        if (teb.strings.indexOf(commandNameBuffer, COMMAND_3) == commandNameBuffer && strlen(commandNameBuffer) == strlen(COMMAND_3)) {
          if (sendACK(3)) { // I run the command only if I send the ak correctly
            displayOnOff();
            return 3;
          }
          else return -3;
        }
      }
      return -10;
  }
  return -11;
}

int8_t device::getCustomCommand () {
  char commandNameBuffer[60], b[151], b2[151];
  teb.strings.percentEncoding(b, DEVICE_ID);
  char* p;
  switch (teb.rcinterface.getCustomCommand(DEVICE_ID, workspaceFolderID, commandNameBuffer)) {
    case 1: //no custom command
      return 0;
    case 0: //custom command present
      if (strlen(COMMAND_4) <= strlen(commandNameBuffer)) {
        p = (char*)teb.strings.indexOf(commandNameBuffer, COMMAND_4);
        if (p != 0) {
          // I don't run the command if I can't delete the file online
          teb.strings.percentEncoding(b2, commandNameBuffer);
          if (teb.rcinterface.deleteCustomCommand(b, b2, workspaceFolderID) == 1) if (set_sea_level_pressure(commandNameBuffer, p)) return 4;
          return -4;
        }
      }
      if (strlen(COMMAND_5) <= strlen(commandNameBuffer)) {
        p = (char*)teb.strings.indexOf(commandNameBuffer, COMMAND_5);
        if (p != 0) {
          // I don't run the command if I can't delete the file online
          teb.strings.percentEncoding(b2, commandNameBuffer);
          if (teb.rcinterface.deleteCustomCommand(b, b2, workspaceFolderID) == 1) if (set_data_update_interval(commandNameBuffer, p)) return 5;
          return -5;
        }
      }
      // command not recognized, I just delete it
      teb.strings.percentEncoding(b2, commandNameBuffer);
      if (teb.rcinterface.deleteCustomCommand(b, b2, workspaceFolderID) == 1) return 6;
      else return -6;
  }
  return -11;
}

bool device::set_sea_level_pressure (const char* from, const char* to) {
  const char* p = from;
  while (*(to - 1) == ' ') to--;
  while (*p != '.' && *p != ',' && p != to) p++;
  if (*p == '.' || *p == ',') {
    if (teb.numbers.isInt(from, p) && teb.numbers.isInt(p + 1, to)) {
      uint32_t i = teb.numbers.charInt(from, p);
      float d = teb.numbers.charInt(p + 1, to);
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

bool device::set_data_update_interval (const char* from, const char* to) {
  while (*(to - 1) == ' ') to--;
  if (teb.numbers.isInt(from, to)) {
    data_update_interval = teb.numbers.charInt(from, to);
    return true;
  }
  return false;
}
