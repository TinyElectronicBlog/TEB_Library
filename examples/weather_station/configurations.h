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
