#ifndef device_h
#define device_h

#include "configurations.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "DHT.h"
#include "TEB_Library.h"

#define COMMAND_1 "*C - *F"
#define COMMAND_2 "ENG - ITA"
#define COMMAND_3 "DISPLAY ON - OFF"
#define COMMAND_4 " hPa"
#define COMMAND_5 " s"

class device {

  private:

    static char accessTokenBuffer[];

    static const char str1[];
    static const char str2_0[];
    static const char str2_1[];
    static const char str3_C[];
    static const char str3_F[];
    static const char str4_0[];
    static const char str4_1[];
    static const char str5_0[];
    static const char str5_1[];
    static const char str6_0[];
    static const char str6_1[];
    static const char str7_0[];
    static const char str7_1[];
    static const char str8[];
    static const char str9[];
    static const char str10[];

    static uint8_t temperature_in;
    static uint8_t language;
    static float sea_level_pressure;
    static uint32_t data_update_interval;
    static bool display_status;

    static bool driveSynchronized;
    static char workspaceFolderID[];
    static char deviceFileID[];
    static char textBuffer[];

    static float DHT22h, DHT22c, DHT22f; // relative humidity, temperature in Celsius and Fahrenheit
    static float DHT22hif; //heat index in Fahreheit
    static float DHT22hic; //heat index in Celsius
    static float BMP280c, BMP280f, BMP280p, BMP280a; // temperature in Celsius and Fahrenheit, atmospheric pressure and altitude (approximate)

    static bool sendACK (uint8_t commandNumber);
    static void change_C_F ();
    static void changeLanguage ();
    static void displayOnOff ();
    static void s3PrintText (const char* t);

    static bool set_sea_level_pressure (const char* from, const char* to);
    static bool set_data_update_interval (const char* from, const char* to);

  public:

    device ();

    static bool initializeSensors ();

    static uint8_t getLanguage ();

    static uint32_t getDataUpdateInterval ();

    static bool readSensorValues ();

    //Update the date and time from the Google server (requires internet access)
    static bool timeSynchronization ();

    //return 0 if Drive is synchronized, 1 if the Tiny Electronic Blog folder does not exist, 2 if the workspace folder does not exist, otherwise a negative value
    static int8_t isDriveSynchronized ();

    static void updateOfflineDeviceFile ();

    //return 1 on success, otherwise a negative value
    static int8_t updateOnlineDeviceFile ();
    static int8_t verifyOnlineDeviceFile ();
    static bool updateSettingsFromOnlineDeviceFile ();

    static int8_t getCommand ();
    static int8_t getCustomCommand ();

    static bool getDisplayStatus ();

    static void printSensorValuesOnDisplay (bool isOnline);
};

#endif
