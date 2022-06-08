#include "device.h"

device ws;

void setup() {
#ifdef TEB_DB_DEBUG
  teb.db.debug.print("\nPROGRAM START\n");
#endif

  //Development board timezone and dst
  teb.db.clock.setTimeZone("Europe/Rome", 1, 0);
  teb.db.clock.setDSTStart(0, -1, 3, 2);
  teb.db.clock.setDSTEnd(0, -1, 10, 3);

  if (ws.getLanguage() == 0) teb.db.display.print(" CIAO!", 3);
  else if (ws.getLanguage() == 1) teb.db.display.print(" HELLO!", 3);
  delay(2000);

  if (!ws.initializeSensors()) {
#ifdef TEB_DB_DEBUG
    teb.db.debug.print("\nINITIALIZATION KO\n");
#endif
    if (ws.getLanguage() == 0) teb.db.display.print("Impossibile inizializzare i sensori :(", 1);
    else if (ws.getLanguage() == 1) teb.db.display.print("Failed to initialize sensors :(", 1);
    while (true) delay(10000);
  }

#ifdef TEB_DB_DEBUG
  teb.db.debug.print("\nINITIALIZATION OK\n");
#endif
  delay(1500);

}

uint8_t time_sync = 8;
bool online_file = false;

void loop() {
  uint32_t t = millis();

  //I read the updated values of the sensors
  if (!ws.readSensorValues()) return;

  //I check the internet connection
  bool internet;
  if (teb.db.wifi.check() == 1) internet = true;
  else {
    if (teb.db.wifi.connect(WIFI_SSID, WIFI_PASSWORD, 7500) == 1) internet = true;
    else internet = false;
  }
#ifdef TEB_DB_DEBUG
  if (internet) teb.db.debug.print(F("\nINTERNET OK\n"));
  else teb.db.debug.print(F("\nINTERNET KO\n"));
#endif

  //time synchronization
  if (internet && time_sync >= 7) {
    if (ws.timeSynchronization()) {
      time_sync = 0;
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nTIME SYNCHRONIZED\n"));
#endif
    }
    else {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nTIME NOT SYNCHRONIZED\n"));
#endif
    }
  }
  else time_sync++;

  //I check the synchronization with Google Drive (login and access to the online file of the device)
  bool driveSynchronized = false;
  if (internet) {
    switch (ws.isDriveSynchronized()) {
      case 0:
        driveSynchronized = true;
#ifdef TEB_DB_DEBUG
        teb.db.debug.print(F("\nDRIVE SYNCHRONIZATION OK\n"));
#endif
        break;
      case 1:
        if (ws.getLanguage() == 0) teb.db.display.print("La cartella di Tiny Electronic Blog non esiste su Drive; avvia l'applicazione Android Remote Control per crearla.", 1);
        else if (ws.getLanguage() == 1) teb.db.display.print("Tiny Electronic Blog folder does not exist on Drive; launch the Android Remote Control application to create it.", 1);
#ifdef TEB_DB_DEBUG
        teb.db.debug.print(F("\nDRIVE SYNCHRONIZATION KO\n"));
#endif
        delay(5000);
        break;
      case 2:
        if (ws.getLanguage() == 0) teb.db.display.print("La cartella di workspace non esiste su Drive; avvia l'applicazione Android Remote Control per crearla.", 1);
        else if (ws.getLanguage() == 1) teb.db.display.print("The workspace folder does not exist on Drive; launch the Android Remote Control application to create it.", 1);
#ifdef TEB_DB_DEBUG
        teb.db.debug.print(F("\nDRIVE SYNCHRONIZATION KO\n"));
#endif
        delay(5000);
        break;
      default :
#ifdef TEB_DB_DEBUG
        teb.db.debug.print(F("\nDRIVE SYNCHRONIZATION KO\n"));
#endif
        break;
    }
  }

  // check the integrity of the device's online file
  if (driveSynchronized && !online_file) {
    if (ws.verifyOnlineDeviceFile() != 0) {
      ws.updateOfflineDeviceFile();
      if (ws.updateOnlineDeviceFile() == 1) {
#ifdef TEB_DB_DEBUG
        teb.db.debug.print(F("\nONLINE DEVICE FILE OK\n"));
#endif
        online_file = true;
      }
      else {
#ifdef TEB_DB_DEBUG
        teb.db.debug.print(F("\nONLINE DEVICE FILE KO\n"));
#endif
      }
    }
    else {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nONLINE DEVICE FILE OK\n"));
#endif
      // get the settings from the online file
      if (ws.updateSettingsFromOnlineDeviceFile()) {
#ifdef TEB_DB_DEBUG
        teb.db.debug.print(F("\nUPDATE SETTINGS FROM ONLINE DEVICE FILE OK\n"));
#endif
      }
      else {
#ifdef TEB_DB_DEBUG
        teb.db.debug.print(F("\nUPDATE SETTINGS FROM ONLINE DEVICE FILE KO\n"));
#endif
      }
      online_file = true;
    }
  }

  // check for the presence of commands to execute
  if (driveSynchronized && online_file) {
    int8_t r = ws.getCommand();
    if (r == 0) {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nNO COMMAND\n"));
#endif
    }
    else if (r == 1 || r == 2 || r == 3) {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nCOMMAND OK\n"));
#endif
    }
    else {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nCOMMAND KO\n"));
#endif
    }
  }

  // check for the presence of custom commands to execute
  if (driveSynchronized && online_file) {
    int8_t r = ws.getCustomCommand();
    if (r == 0) {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nNO CUSTOM COMMAND\n"));
#endif
    }
    else if (r == 4 || r == 5) {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nCUSTOM COMMAND OK\n"));
#endif
    }
    else if (r == 6) {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nCUSTOM COMMAND NOT RECOGNIZED\n"));
#endif
    }
    else {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nCUSTOM COMMAND KO\n"));
#endif
    }
  }

  // update the offline file with the new values, then the online one (if internet connection is available)
  if (online_file && driveSynchronized) {
    ws.updateOfflineDeviceFile();
    if (ws.updateOnlineDeviceFile() == 1) {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nONLINE DEVICE FILE UPDATE OK\n"));
#endif
    }
    else {
#ifdef TEB_DB_DEBUG
      teb.db.debug.print(F("\nONLINE DEVICE FILE UPDATE KO\n"));
#endif
    }
  }

  // print the updated sensor values on the display
  ws.printSensorValuesOnDisplay(driveSynchronized && online_file);

  // clear the display if necessary
  if (!ws.getDisplayStatus()) teb.db.display.print("", 1);

  // wait at least the desired time
  t = millis() - t;
  if (t < ws.getDataUpdateInterval() * 1000) delay(ws.getDataUpdateInterval() * 1000 - t);
}
