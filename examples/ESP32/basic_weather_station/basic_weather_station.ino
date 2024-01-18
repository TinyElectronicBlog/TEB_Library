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

// For more information about the example visit https://sites.google.com/view/tiny-electronic-blog/home/video-tutorial-to-manage-an-esp32-from-android-smartphone-using-tiny-electr

#include "device.h"
#include "TEB_Library.h"

device ws;

void setup() {
  teb.device.init(NULL, 1);
  teb.device.debugPrint("\nPROGRAM START\n");

  if (ws.getLanguage() == 0) teb.device.displayPrint(1, " CIAO!", 3, 1);
  else if (ws.getLanguage() == 1) teb.device.displayPrint(1, " HELLO!", 3, 1);
  teb.device.delay(2000, 1);

  if (!ws.initializeSensors()) {
    teb.device.debugPrint("\nINITIALIZATION KO\n");
    if (ws.getLanguage() == 0) teb.device.displayPrint(1, "Impossibile inizializzare i sensori :(", 1, 1);
    else if (ws.getLanguage() == 1) teb.device.displayPrint(1, "Failed to initialize sensors :(", 1, 1);
    while (true) teb.device.delay(10000, 1);
  }

  teb.device.debugPrint("\nINITIALIZATION OK\n");
  teb.device.delay(1500, 1);
}

uint8_t time_sync = 8;
bool online_file = false;

void loop() {
  uint32_t t = millis();

  //I read the updated values of the sensors
  if (!ws.readSensorValues()) return;

  //I check the internet connection
  bool internet;
  if (teb.device.wifiCheck(1, 1) == 1) internet = true;
  else {
    if (teb.device.wifiConnect(1, WIFI_SSID, WIFI_PASSWORD, 7500, 1) == 1) internet = true;
    else internet = false;
  }
  if (internet) teb.device.debugPrint("\nINTERNET OK\n");
  else teb.device.debugPrint("\nINTERNET KO\n");

  //time synchronization
  if (internet && time_sync >= 7) {
    if (ws.timeSynchronization()) {
      time_sync = 0;
      teb.device.debugPrint("\nTIME SYNCHRONIZED\n");
    } else {
      teb.device.debugPrint("\nTIME NOT SYNCHRONIZED\n");
    }
  } else time_sync++;

  //I check the synchronization with Google Drive (login and access to the online file of the device)
  bool driveSynchronized = false;
  if (internet) {
    switch (ws.isDriveSynchronized()) {
      case 0:
        driveSynchronized = true;
        teb.device.debugPrint("\nDRIVE SYNCHRONIZATION OK\n");
        break;
      case 1:
        if (ws.getLanguage() == 0) teb.device.displayPrint(1, "La cartella di Tiny Electronic Blog non esiste su Drive; avvia l'applicazione Android Remote Control per crearla.", 1, 1);
        else if (ws.getLanguage() == 1) teb.device.displayPrint(1, "Tiny Electronic Blog folder does not exist on Drive; launch the Android Remote Control application to create it.", 1, 1);
        teb.device.debugPrint("\nDRIVE SYNCHRONIZATION KO\n");
        teb.device.delay(10000, 1);
        break;
      case 2:
        if (ws.getLanguage() == 0) teb.device.displayPrint(1, "La cartella di workspace non esiste su Drive; avvia l'applicazione Android Remote Control per crearla.", 1, 1);
        else if (ws.getLanguage() == 1) teb.device.displayPrint(1, "The workspace folder does not exist on Drive; launch the Android Remote Control application to create it.", 1, 1);
        teb.device.debugPrint("\nDRIVE SYNCHRONIZATION KO\n");
        teb.device.delay(10000, 1);
        break;
      case -1:
        if (ws.getLanguage() == 0) teb.device.displayPrint(1, "Errore, sono stati trovati 2 o piu' device file e sono stati tutti cancellati.", 1, 1);
        else if (ws.getLanguage() == 1) teb.device.displayPrint(1, "Error, 2 or more device files were found and they were all deleted.", 1, 1);
        teb.device.debugPrint("\nDRIVE SYNCHRONIZATION KO\n");
        teb.device.delay(10000, 1);
        break;
      case -2:
        if (ws.getLanguage() == 0) teb.device.displayPrint(1, "Errore, controllare se la cartella di workspace su Drive contiene file errati.", 1, 1);
        else if (ws.getLanguage() == 1) teb.device.displayPrint(1, "Error, check if the workspace folder on Drive contains incorrect files.", 1, 1);
        teb.device.debugPrint("\nDRIVE SYNCHRONIZATION KO\n");
        teb.device.delay(10000, 1);
        break;
      case -3:
        if (ws.getLanguage() == 0) teb.device.displayPrint(1, "Accesso a Google Drive non riuscito.", 1, 1);
        else if (ws.getLanguage() == 1) teb.device.displayPrint(1, "Google Drive login failed.", 1, 1);
        teb.device.debugPrint("\nDRIVE LOGIN KO\n");
        teb.device.delay(3000, 1);
        break;
      default:
        if (ws.getLanguage() == 0) teb.device.displayPrint(1, "Sincronizzazione con Google Drive fallita.", 1, 1);
        else if (ws.getLanguage() == 1) teb.device.displayPrint(1, "Synchronization with Google Drive failed.", 1, 1);
        teb.device.debugPrint("\nDRIVE SYNCHRONIZATION KO\n");
        teb.device.delay(10000, 1);
        break;
    }
  }

  // check the integrity of the device's online file
  if (driveSynchronized && !online_file) {
    if (ws.verifyOnlineDeviceFile() != 0) {
      ws.updateOfflineDeviceFile();
      if (ws.updateOnlineDeviceFile() == 1) {
        teb.device.debugPrint("\nONLINE DEVICE FILE OK\n");
        online_file = true;
      } else {
        teb.device.debugPrint("\nONLINE DEVICE FILE KO\n");
      }
    } else {
      teb.device.debugPrint("\nONLINE DEVICE FILE OK\n");
      // get the settings from the online file
      if (ws.updateSettingsFromOnlineDeviceFile()) {
        teb.device.debugPrint("\nUPDATE SETTINGS FROM ONLINE DEVICE FILE OK\n");
      } else {
        teb.device.debugPrint("\nUPDATE SETTINGS FROM ONLINE DEVICE FILE KO\n");
      }
      online_file = true;
    }
  }

  // check for the presence of commands to execute
  if (driveSynchronized && online_file) {
    int8_t r = ws.getCommand();
    if (r == 0) {
      teb.device.debugPrint("\nNO COMMAND\n");
    } else if (r == 1 || r == 2 || r == 3) {
      teb.device.debugPrint("\nCOMMAND OK\n");
    } else {
      teb.device.debugPrint("\nCOMMAND KO\n");
    }
  }

  // check for the presence of custom commands to execute
  if (driveSynchronized && online_file) {
    int8_t r = ws.getCustomCommand();
    if (r == 0) {
      teb.device.debugPrint("\nNO CUSTOM COMMAND\n");
    } else if (r == 4 || r == 5) {
      teb.device.debugPrint("\nCUSTOM COMMAND OK\n");
    } else if (r == 6) {
      teb.device.debugPrint("\nCUSTOM COMMAND NOT RECOGNIZED\n");
    } else {
      teb.device.debugPrint("\nCUSTOM COMMAND KO\n");
    }
  }

  // update the offline file with the new values, then the online one (if internet connection is available)
  if (online_file && driveSynchronized) {
    ws.updateOfflineDeviceFile();
    if (ws.updateOnlineDeviceFile() == 1) {
      teb.device.debugPrint("\nONLINE DEVICE FILE UPDATE OK\n");
    } else {
      teb.device.debugPrint("\nONLINE DEVICE FILE UPDATE KO\n");
    }
  }

  // print the updated sensor values on the display
  ws.printSensorValuesOnDisplay(driveSynchronized && online_file);

  // clear the display if necessary
  if (!ws.getDisplayStatus()) teb.device.displayPrint(1, "", 1, 1);

  // wait at least the desired time
  t = millis() - t;
  if (t < ws.getDataUpdateInterval() * 1000) teb.device.delay(ws.getDataUpdateInterval() * 1000 - t, 1);
}
