#ifndef ESP32
  #error "This is for ESP32 boards only"
#endif

// Select temperature sensor
// #define DS18B20Sensor
// #define BME280Sensor
#define SHT45Sensor

// #define DISPDEBUG
// #define ENCODER_ACTIVE
// #define FASTDEBUG
// #define LOOPDEBBUG
// #define MQTTDEBUG
// #define PREFDEBBUG
// #define SETUPDEBUG

// Screen Pinout
#define pin_DC 17             // Purple   
#define pin_RST 4             // Yellow
#define pin_BL 27             // Green
#define pin_CS 5              // White
#define pin_MISO 19           // Grey
#define pin_CLK 18            // Black
#define pin_MOSI 13           // Blue
// Touch Pinout
#define pin_YM 26             // can be a digital pin
#define pin_YP 25             // must be an analog pin
#define pin_XM 33             // must be an analog pin
#define pin_XP 32             // can be a digital pin

// Sensor Pinout
#ifdef DS18B20Sensor
  #define pinOneWire
#endif
#ifdef BME280Sensor
#endif
#ifdef SHT45Sensor
#define pinSDA 21
#define pinSCL 22
#endif
// Onboard devices
#define pinWake 0           // Active LOW 
#define pinRelayOut 16      // Active High
#define pinLED 23           // Active High
// Alias Definitions
#define RELAY_ON 1
#define RELAY_OFF !RELAY_ON

// Encoder Pinout
#ifdef ENCODER_ACTIVE
#define pinEncoderA 15           // aka CLK pin
#define pinEncoderB 14           // aka DT pin
#define pinEncoderButton 12
#define pinEncoderVCC -1         // -1 for VCC, any other for switchable power
#endif

// Screen Settings
#define MODE_XPOS 280
#define MODE_YPOS 30
#define WIFI_XPOS 280
#define WIFI_YPOS 140
#define SET_XPOS 280
#define SET_YPOS 175
#define TEMP_XPOS 0
#define TEMP_YPOS 50
#define TEMPSET_XPOS 230
#define TEMPSET_YPOS 200
#define HISTORY_SIZE 180

// Input Settings
#ifdef ENCODER_ACTIVE
#define ENCODER_STEPS 4            // Rotary encoder sensitivity (1,2,4 are valid entries)
#endif
#define XPlateR 350

// Include libraries
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ArduinoJson.h>
#ifdef ENCODER_ACTIVE
#include <AiEsp32RotaryEncoder.h>
#include "AiEsp32RotaryEncoderNumberSelector.h"
#endif
#include <TouchScreen.h>
#ifdef DS18B20Sensor
  #include <DallasTemperature.h>
  #include <OneWire.h>
#endif
#ifdef BME280Sensor
#endif
#ifdef SHT45Sensor
#include "Adafruit_SHT4x.h"
#endif
#include <SPI.h>
#include <nvs_flash.h>
#include <Preferences.h>
#include <PubSubClient.h>
#include <WiFi.h>

// Library interface objects
#ifdef ENCODER_ACTIVE
AiEsp32RotaryEncoder *rotaryEncoder = new AiEsp32RotaryEncoder(pinEncoderA, pinEncoderB, pinEncoderButton pinEncoderVCC, ENCODER_STEPS);
AiEsp32RotaryEncoderNumberSelector numberSelector = AiEsp32RotaryEncoderNumberSelector();
#endif
Adafruit_ILI9341 screen = Adafruit_ILI9341(pin_CS, pin_DC, pin_MOSI, pin_CLK, pin_RST, pin_MISO);
#ifdef DS18B20Sensor
OneWire oneWire(pinOneWire);                                          // 1-wire bus object
DallasTemperature DS18B20(&oneWire);                                  // Dallas OneWire protocol sensors object
DeviceAddress ds18Addr;                                               // DS18B20 1-wire address object
#endif
#ifdef SHT45Sensor
Adafruit_SHT4x sht4 = Adafruit_SHT4x();
#endif
Preferences preferences;                                              // Preferences object for saved settings
TouchScreen ts = TouchScreen(pin_XP, pin_YP, pin_XM, pin_YM, XPlateR);
WiFiClient TStatWiFiClient;                                           // WiFi client object
PubSubClient MQTTClient(TStatWiFiClient);                             // MQTT client object

// Pinned Tasks
TaskHandle_t fastLoop;

// Data objects
typedef struct struct_cal  {                                          // Calibration settings
  #ifdef DS18B20Sensor
  float ds18CalOffset = 0;                                                    // DS18B20 temperature offset (1-point calibration)
  float ds18RawHi = 98.5;                                                     // DS18B20 calibration boiling water reading (2-point calibration)
  float ds18RawLo = 0.1;                                                      // DS18B20 temperature frozen water reading (2-point calibration)
  float ds18RefHi = 97.91;                                                    // DS18B20 temperature boiling water actual (2-point calibration)
  float ds18RefLo = 0.00;                                                     // DS18B20 temperature frozen water actual (2-point calibration)
  #endif
  #ifdef SHT45Sensor
  float sht4xOffset = 0.0;                                                    // SHT4x temperature offset (1-point calibration)
  #endif
  int ts_minX = 0;
  int ts_maxX = 737;
  int ts_minY = 120;
  int ts_maxY = 900;
} struct_cal;
struct_cal calibrations;

typedef struct user_settings  {                                       // User settings
  float sleepTime = 0.5;                                                      // Time between polling intervals in minutes
  float tempSet = 22.0;                                                       // Default temperature setting
  float tempHyst = 0.5;                                                       // Temperature Hysteresis
  char brightness = 7;                                                        // Screen brightness
  char netSSID[33] = "LANSolo";                                               // STA mode WiFi SSID (33b)
  char netPassword[64] = "AccioNetwork!";                                     // STA mode WiFi Password (64b)
  String hostname = "CFThermostat";                                           // WiFi hostname (11b)
  uint16_t mqttPort = 1883;                                                   // MQTT broker port
  char mqttBaseTopic[65] = "custom/CatsForehead";                             // MQTT base topic
  char mqttCtrlTopic[9] = "/cmd/";                                            // MQTT control topic
  char mqttDataTopic[9] = "/tele/";                                           // MQTT data topic
} user_settings;
user_settings settings;

typedef struct button  {                                       // Input buttons
  bool status = false;
  unsigned long last_press = 0;
  int deb_time = 200;
} button;
button button_sel;
button button_up;
button button_down;

//Touchscreen varables
int mapX;
int mapY;

// Global variables
IPAddress mqttBroker(10, 0, 0, 2);                                    // MQTT broker address
char MQTTTopics[3][65];
char myteleTopic[65];
char mycmcdTopic[65];
unsigned long timeStart = millis();
unsigned long lastRead = 0;
char flags = 0b00000000;                                              // 0-7: 0, Wifi Connected; 1, MQTT Connected; 2, Furnace On; 3, Fans On; 4, AC On; 5-7, Available
static char opMode[5] = "Heat";                                       // Options: Heat, Fan, Cool, Off
int timeout = 30000;                                                  // Mode timeout

float tempCurr = NAN;
float tempHistory[HISTORY_SIZE];
float humidityCurr = NAN;
float humidHistory[HISTORY_SIZE];

void savePrefs(bool clearPrefs=true)  {
  String tempString;

  if (clearPrefs==true)  {         // clear all saved settings
    nvs_flash_erase(); // erase the NVS partition and...
    nvs_flash_init(); // initialize the NVS partition.
  }

  #ifdef PREFDEBBUG
  Serial.println("Saving preferences:");                      // save all current settings
  #endif
  preferences.begin("cal", false);         // Calibrations
  #ifdef DS18B20Sensor
  preferences.putFloat("ds18_offset", calibrations.ds18CalOffset);
  preferences.putFloat("ds18_raw_hi", calibrations.ds18RawHi);
  preferences.putFloat("ds18_raw_lo",  calibrations.ds18RawLo);
  preferences.putFloat("ds18_ref_hi", calibrations.ds18RefHi);
  preferences.putFloat("ds18_ref_lo", calibrations.ds18RefLo);
  #endif
  #ifdef SHT45Sensor
  preferences.putFloat("sht4x_offset", calibrations.sht4xOffset);
  #endif
  preferences.end();
  
  preferences.begin("user_set", false);                       // User Settings
  preferences.putFloat("sleep_time", settings.sleepTime);               // Time between polling intervals in minutes
  preferences.putFloat("temp_set", settings.tempSet);
  preferences.putFloat("temp_hys", settings.tempHyst);
  preferences.putChar("bright", settings.brightness);                   // Screen brightness
  preferences.putString("hostname", settings.hostname);                 // WiFi hostname (11b)
  tempString = mqttBroker.toString();
  preferences.putUInt("mqttBroker", (uint32_t)mqttBroker);              // MQTT broker address
  preferences.putUInt("mqtt_port", settings.mqttPort);                  // MQTT broker port
  tempString = String(settings.mqttBaseTopic);
  preferences.putString("mqtt_base_topic", tempString);                 // MQTT base topic
  tempString = String(settings.mqttCtrlTopic);
  preferences.putString("mqtt_ctrl", tempString);                       // MQTT control topic
  tempString = String(settings.mqttDataTopic);
  preferences.putString("mqtt_data", tempString);                       // MQTT data topic
  preferences.end();
}

void loadPrefs(bool reset=false)  {
  String tempString;
  if (reset==true)  {savePrefs(true);}
  preferences.begin("cal", true);         // Calibrations
  #ifdef DS18B20Sensor
  calibrations.ds18CalOffset = preferences.getFloat("ds18_offset", 0.00);
  calibrations.ds18RawHi = preferences.getFloat("ds18_raw_hi", 100.00);
  calibrations.ds18RawLo = preferences.getFloat("ds18_raw_lo",  0.00);
  calibrations.ds18RefHi = preferences.getFloat("ds18_ref_hi", 97.91);
  calibrations.ds18RefLo = preferences.getFloat("ds18_ref_lo", 0.00);
  #endif
  #ifdef SHT45Sensor
  calibrations.sht4xOffset = preferences.getFloat("sht4x_offset", 0.00);
  #endif
  preferences.end();
  #ifdef PREFDEBBUG
  #ifdef DS18B20Sensor
  if ((calibrations.ds18CalOffset!=0.00) && (calibrations.ds18RawHi!=100.00))  {Serial.println("Loaded DS18B20 calibrations:");}
  else  {
    Serial.println("DS18B20 calibrations not found - using defaults");
    }
  Serial.print("Temperature offset (1-point calibration): "); Serial.print(calibrations.ds18CalOffset); Serial.println("°C");
  Serial.print("\nBoiling water reading (2-point calibration): "); Serial.print(calibrations.ds18RawHi); Serial.println("°C");
  Serial.print("Frozen water reading  (2-point calibration): "); Serial.print(calibrations.ds18RawLo); Serial.println("°C");
  Serial.print("Boiling water actual  (2-point calibration): "); Serial.print(calibrations.ds18RefHi); Serial.println("°C");
  Serial.print("Frozen water actual   (2-point calibration): "); Serial.print(calibrations.ds18RefLo); Serial.println("°C");
  #endif
  #ifdef SHT45Sensor
  if (calibrations.sht4xOffset==0.00)  {Serial.println("SHT4x calibrations not found - using default...");}
  else  {Serial.println("Loaded SHT4x calibration:");}
  Serial.print("Temperature offset (1-point calibration): "); Serial.print(calibrations.sht4xOffset); Serial.println("°C");
  #endif
  #endif
  
  preferences.begin("user_set", true);         // User Settings
  preferences.clear();
  settings.sleepTime = preferences.getFloat("sleep_time", 1.0);         // Time between polling intervals in minutes
  settings.tempSet = preferences.getFloat("temp_set", 0.00);
  settings.tempHyst = preferences.getFloat("temp_hys", 0.0);
  settings.brightness = preferences.getChar("bright", 15);              // Screen brightness
  settings.hostname = preferences.getString("hostname", "");            // WiFi hostname (11b)
  
  mqttBroker = IPAddress(preferences.getUInt("mqttBroker", 0));            // MQTT broker address
  
  settings.mqttPort = preferences.getUInt("mqtt_port", 1883);           // MQTT broker port
  tempString = preferences.getString("mqtt_base_topic", "");
  tempString.toCharArray(settings.mqttBaseTopic, 65);                   // MQTT base topic
  tempString = preferences.getString("mqtt_ctrl", "/cmd/");
  tempString.toCharArray(settings.mqttCtrlTopic, 9);                    // MQTT control topic
  tempString = preferences.getString("mqtt_data", "/tele/");
  tempString.toCharArray(settings.mqttDataTopic, 9);                    // MQTT data topic
  preferences.end();
  #ifdef PREFDEBBUG
  if (settings.tempSet!=0.00)  {Serial.println("Loaded preferences:");}
  else  {
    Serial.println("User settings not found - using defaults:");
    }
  Serial.print("Time between readings:    "); Serial.print(settings.sleepTime); Serial.println(" minutes");
  Serial.print("\nIdeal temperature:        "); Serial.print(settings.tempSet); Serial.println("°C");
  Serial.print("Temperature buffer range: "); Serial.print(settings.tempHyst); Serial.println("°C");
  Serial.print("\nDisplay brightness:       "); Serial.print(int(settings.brightness)); Serial.println("/15");
  Serial.print("\nDevice WiFi hostname:     "); Serial.println(settings.hostname);
  Serial.print("MQTT broker:              "); Serial.println(mqttBroker);
  Serial.print("MQTT port:                "); Serial.println(settings.mqttPort);
  Serial.print("MQTT base topic:          "); Serial.println(settings.mqttBaseTopic);
  Serial.print("MQTT control topic:       "); Serial.println(settings.mqttCtrlTopic);
  Serial.print("MQTT data topic:          "); Serial.println(settings.mqttDataTopic);
  #endif
}

void initWiFi()  {
  Serial.print("Connecting to ");
  Serial.print(settings.netSSID);
  screen.print("Connecting to ");
  screen.print(settings.netSSID); screen.print("...");
  WiFi.begin(settings.netSSID, settings.netPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  screen.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  screen.print("IP address: ");
  screen.println(WiFi.localIP());
}

/*{                                                                     // cmd JSON
  "Calibrations":{
    "DS18B20":{
      "Offset":0,
      "RawHi":98.5,
      "RawLo":0.1,
      "RefHi":97.91,
      "RefLo":0.00},
    "SHT45":{
      "sht4xOffset":0.0},
    "Touchscreen":{
      "minX":0,
      "maxX":737,
      "minY":120,
      "maxY":900}},
  "Settings":{
    "WiFi":{
      "netSSID":"LANSolo",
      "netPassword":"AccioNetwork!",
      "hostname":"CFThermostat"},
    "MQTT":{
      "port":1883,
      "baseTopic":"custom/CatsForehead"},
    "Screen":{
      "brightness":7,
      "timeout":30000},
    "Temperature":{
    "Mode":"Heat",
    "setting":22.0,
    "hysteresis":0.5,
    "readInterval":0.5}}
}*/

void MQTTSubCallback(char* topic, byte* payload, unsigned int length) {
  char msgBuf[256];
  static unsigned long lastBeacon = 0;
  Serial.println("\n     *****MQTT message received*****");
  Serial.print("Last beacon: "); Serial.println(lastBeacon);
  Serial.print("Now: "); Serial.println(millis());


  if (millis()-1000>lastBeacon)  {
    Serial.print("     Topic:"); Serial.println(topic);
    Serial.print("     Message: "); {Serial.print(msgBuf);} Serial.println("");
    Serial.print("     Length: "); Serial.print(length); Serial.println(" char");
    lastBeacon = millis();
  }
  else  {
    Serial.println("Received recently sent beacon");
  }
  Serial.println("     ******************************\n");
}

void initMQTT() {
  char name[17];
  MQTTClient.setServer(mqttBroker, settings.mqttPort);
  MQTTClient.setKeepAlive(90);                    // Keep connection alive for 90 seconds
  MQTTClient.setBufferSize(512);
  MQTTClient.setCallback(MQTTSubCallback);
  Serial.print("Connecting to MQTT broker...");
  screen.print("Connecting to MQTT...");
  
  while (!MQTTClient.connected()) {
    Serial.print(".");
    if (MQTTClient.connect("TStatWiFiClient")) {
      Serial.println("Connected");
      screen.println("Connected to broker  ");
      Serial.println("Subscribing to topic(s).");
      screen.println("Subscribing to topics");
      delay(1000);
      for (int i=0; i<2; i++)  {
        strcpy(MQTTTopics[i], settings.mqttBaseTopic);
        strcat(MQTTTopics[i], "/");
        settings.hostname.toCharArray(name, 16);
        strcat(MQTTTopics[i], name);
        if (i==0)  {strcat(MQTTTopics[i], settings.mqttDataTopic);}
        else  {strcat(MQTTTopics[i], settings.mqttCtrlTopic);}
        Serial.print("Built topic: "); Serial.println(MQTTTopics[i]);
      }
      strcat(name, "/#");
      if (MQTTClient.subscribe(MQTTTopics[1]))  {
        Serial.print("Subscribed to topic: "); Serial.println(MQTTTopics[1]);
        screen.print("Subscribed to "); screen.println(MQTTTopics[1]);
      }
      else  {
        Serial.println("Subscribing failed: "); Serial.println(MQTTTopics[1]);
        screen.println("Failed");
      }
      if (MQTTClient.subscribe(name))  {
        Serial.print("Subscribed to topic: "); Serial.println(name);
        screen.print("Subscribed to "); screen.println(name);
      }
      else  {
        Serial.println("Subscribing failed: "); Serial.println(name);
        screen.println("Failed");
      }
    }
    else {                                                              // Error messages if not connected
      int MQTTErr = MQTTClient.state();
      Serial.print("Failed - Error state "); Serial.println(MQTTErr);
      screen.println("ERROR!");
      screen.print("MQTT error state: "); screen.println(MQTTErr);
      if(MQTTErr==0)  {screen.println("No Error");}
      else if(MQTTErr==-1)  {screen.println("Connection Refused:\nUnacceptable protocol\nversion");}
      else if(MQTTErr==-2)  {screen.println("Connection Refused:\nIdentifier rejected");}
      else if(MQTTErr==-3)  {screen.println("Connection Refused:\nServer Unavailable");}
      else if(MQTTErr==-4)  {screen.println("Connection Refused:\nBad username or \npassword");}
      else if(MQTTErr==-5)  {screen.println("Connection Refused:\nAuthorization error");}
      else if(MQTTErr==-6)  {screen.println("Connection lost or bad");}
      else if(MQTTErr==-7)  {screen.println("Timeout waiting for\nLength bytes");}
      else if(MQTTErr==-8)  {screen.println("Timeout waiting for\nPayload");}
      else if(MQTTErr==-9)  {screen.println("Timeout waiting for\nCONNACK");}
      else if(MQTTErr==-10)  {screen.println("Timeout waiting for\nSUBACK");}
      else if(MQTTErr==-11)  {screen.println("Timeout waiting for\nUNSUBACK");}
      else if(MQTTErr==-12)  {screen.println("Timeout waiting for\nPINGRESP");}
      else if(MQTTErr==-13)  {screen.println("Malformed Remaining\nLength");}
      else if(MQTTErr==-14)  {screen.println("Problem with the\nunderlying com port");}
      else if(MQTTErr==-15)  {screen.println("Address could not be\nparsed");}
      else if(MQTTErr==-16)  {screen.println("Malformed received\npacket");}
      else if(MQTTErr==-17)  {screen.println("Subscription failure");}
      else if(MQTTErr==-18)  {screen.println("Payload decoding\nfailure");}
      else if(MQTTErr==-19)  {screen.println("Failed to compile a\nDecoder");}
      else if(MQTTErr==-20)  {screen.println("The received MQTT\npacket type is not\nsupported on this\nclient");}
      else if(MQTTErr==-21)  {screen.println("Timeout waiting for\nPUBACK");}
      else if(MQTTErr==-22)  {screen.println("Timeout waiting for\nPUBREC");}
      else if(MQTTErr==-23)  {screen.println("Timeout waiting for\nPUBCOMP");}
      else {screen.print("Unhandled error\nBroker site for meaning.");}
      while (true)  {delay(500);}
    }
  }
}

void sendStatus()  {
  char JSONFile[192];
  char junk[6];
  int scrap;
  JsonDocument doc;

  doc["Mode"] = opMode;

  JsonObject Temperature = doc["Temperature"].to<JsonObject>();
  if (tempCurr<0)  {dtostrf(tempCurr, 6, 1, junk);}
  else if(tempCurr<10) {dtostrf(tempCurr, 4, 1, junk);}
  else {dtostrf(tempCurr, 5, 1, junk);}
  Temperature["current"] = junk;
  Temperature["setting"] = settings.tempSet;
  doc["Humidty"]["current"] = round(humidityCurr);

  JsonObject Status = doc["Status"].to<JsonObject>();
  Status["furnace"] = bool(bitRead(flags, 2));
  Status["fans"] = bool(bitRead(flags, 3));
  Status["AC"] = bool(bitRead(flags, 4));

  // doc.shrinkToFit();  // optional

  serializeJson(doc, JSONFile);
  #ifdef MQTTDEBUG
  Serial.print("JSON Output:"); Serial.println(JSONFile);
  #endif
  MQTTClient.publish(MQTTTopics[0], JSONFile);
}
/*
void IRAM_ATTR isrSelect() {
  unsigned long this_press = millis();

  if (this_press-button_sel.last_press > button_sel.deb_time)  {
    button_sel.status = true;
    button_sel.last_press = millis();
  }
}

void IRAM_ATTR isrUp() {
  unsigned long this_press = millis();

  if (this_press-button_up.last_press > button_up.deb_time)  {
    button_up.status = true;
    button_up.last_press = millis();
  }
}

void IRAM_ATTR isrDown() {
  unsigned long this_press = millis();

  if (this_press-button_down.last_press > button_down.deb_time)  {
    button_down.status = true;
    button_down.last_press = millis();
  }
}
*/
void setup() {
  Serial.begin(115200);                                               // Start serial interface
  delay(2500);
  #ifdef SETUPDEBBUG
  Serial.println("Serial interface active.");
  #endif
  
  pinMode(pin_BL, OUTPUT);
  ledcAttach(pin_BL, 5000, 4);
  ledcWrite(pin_BL, 0);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
  pinMode(pinRelayOut, OUTPUT);
  digitalWrite(pinRelayOut, RELAY_OFF);
  pinMode(pinWake, INPUT_PULLUP);
  // pinMode(pinEncoderButton, INPUT_PULLUP);
  // pinMode(pinEncoderA, INPUT);
  // pinMode(pinEncoderB, INPUT);
  analogReadResolution(10);
  xTaskCreatePinnedToCore(loopFast, "fastLoop", 10000, NULL, 1, &fastLoop, 0);
  // xTaskCreatePinnedToCore(displayCurrTemp, "currTemp", 10000, NULL, 1, &currTemp, 0);

  delay(500);
  #ifdef SETUPDEBBUG
  Serial.println("Loading calibrations and preferences");
  #endif
  loadPrefs(true);
   ScreenInit();  


  /*          // Physical button setup
    screen.print("Setting up phsical Buttons... ");.
    pinMode(pinSel, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pinSel), isrSelect, FALLING);
    pinMode(pinUp, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pinUp), isrUp, HIGH);
    pinMode(pinDown, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pinDown), isrDown, HIGH);
    screen.print("Done");
  */

  /* Serial.println("Press Y/y to enter settings mode.");
    timeStart = milli s();
    while (timestart+10000<millis()) {
      char incomingByte;
      if (Serial.available() > 0) {
            // read the incoming byte:
            incomingByte = Serial.read();
            Serial.print("Received "); Serial.println(incomingByte);

      }
      if (incomingByte=='Y')||(incomingByte=='y')
    }
  */
  screen.print("Initializing history...");
  for (int count=0; count<=HISTORY_SIZE; count++)  {
    tempHistory[count] = NAN;
    humidHistory[count] = NAN;
    if (count>=HISTORY_SIZE) {Serial.print("Initialized "); Serial.print(count); Serial.println(" history records");}
  }
  screen.println("Done");

  screen.print("Initializing sensor...");
  #ifdef DS18B20Sensor                                                  // Set up DS18B20 sensor
  DS18B20.begin();
  #ifdef SETUPDEBBUG
  Serial.println("BME280 Sensor selected, but not programmed");
  #endif
  #endif
  #ifdef SHT45Sensor                                                    // Set up SHT4x sensor
  initSHT4x("H", 0, 0);
  readSHT4x();  
  #endif
  screen.print("Taking first reading...");
  do  {
    readTemp();                                                         // Initial temperature reading
    delay(100);
  } while ((isnan(tempCurr))||(isnan(humidityCurr)));
  screen.print(tempCurr, 1); screen.print("deg C @ "); screen.print(humidityCurr, 0); screen.println("% Rh.");
  
  // TouchInit();                                                       // Set up touch interface


  initWiFi();                                                           // Initialize WiFi
  initMQTT();                                                           // Initialize MQTT                                                     // Set up display
  sendStatus();
  delay(2500);

  screen.fillRect(0, 20, 320, 100, 0);
  RunScreen();
}

void sleepTimer()  {
  // Serial.println("Sleeping...");
  delay(60000*settings.sleepTime);
  // Serial.println("Waking up!");
  // Serial.println("Reconnecting to the network...");
}

void loopFast(void *pvParameters)  {
  for(;;)  {

    // Serial.print("loopFast() running on core "); Serial.println(xPortGetCoreID());
    // delay(10);
    // checkTouch();
    delay(10);
    if (digitalRead(pinWake)==0)  {
      Serial.println("*************MANUAL RESET*************");
      ESP.restart();
    }
    delay(10);
  }
}

void MQTTreconnect() {
  // Loop until we're reconnected
  while (!MQTTClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (MQTTClient.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      MQTTClient.subscribe("esp32/output");
    }
  }
  Serial.println("Connected");
}

void loop() {
  static unsigned long lastUpdate = millis();
  static int oldTarget = settings.tempSet;
  
  if (!MQTTClient.connected()) {
    MQTTreconnect();
  }
  MQTTClient.loop();

  if (millis()>=(lastRead+settings.sleepTime))  {
    #ifdef LOOPDEBBUG
    Serial.print("Millis: "); Serial.print(millis()); Serial.print(", Threshold: "); Serial.print(lastRead+(settings.sleepTime)); Serial.print(", Difference: "); Serial.println(millis()-lastRead);
    Serial.println("**************************************");            // Read temperature and respond
    #endif
    readTemp(); 
    #ifdef LOOPDEBBUG
    Serial.print("Latest reading: "); Serial.print(tempCurr, 1); Serial.print("°C @ "); Serial.print(humidityCurr, 0); Serial.println("% Rh.\n");
    #endif
    displayCurrTemp();
    displaySetTemp();
    if (strcmp(opMode, "Off")==0)  {                                                // All off no matter what
      digitalWrite(pinRelayOut, RELAY_OFF);                       // Heater off
      // Fan off
      // A/C off
      sendStatus();
      #ifdef LOOPDEBBUG
      Serial.println("Mode: All off");
      Serial.println("Furnace off, Fan off, A/C off");
      #endif
    }
    else if (strcmp(opMode, "Heat")==0)  {                                          // Heater auto, Fan off, A/C off
      #ifdef LOOPDEBBUG
      Serial.println("Mode: Heating");
      #endif
      // screen.println("Heating mode: ");
      if (tempCurr>settings.tempSet+(settings.tempHyst/2))  {                                                                      // Temp above set point
        if (digitalRead(pinRelayOut==RELAY_ON))  {                    // If heater is on - should be off
          #ifdef LOOPDEBBUG
          Serial.println("Furnace turning off, Fan off, A/C off");
          #endif
          sendStatus();
        }
        else if (digitalRead(pinRelayOut==RELAY_OFF))  {              // If heater is off - should be off
          #ifdef LOOPDEBBUG
          Serial.println("Furnace already off, Fan off, A/C off");
          #endif
        }
        digitalWrite(pinRelayOut, RELAY_OFF);
      }
      #ifdef LOOPDEBBUG
      if ((tempCurr>=settings.tempSet-(settings.tempHyst/2)) && (tempCurr<=settings.tempSet+(settings.tempHyst/2)))  {              // Temp in hysteresis range
        Serial.println("In hysteresis range, no change");
      }
      #endif
      else if (tempCurr<settings.tempSet-(settings.tempHyst/2))  {                                                                 // Temp below set point
        if (digitalRead(pinRelayOut==RELAY_ON))  {                    // If heater is on - should be on
          #ifdef LOOPDEBBUG
          Serial.println("Furnace already on, Fan off, A/C off");
          #endif
        }
        else if (digitalRead(pinRelayOut==RELAY_OFF))  {              // If heater is off - should be on
          #ifdef LOOPDEBBUG
          Serial.println("Furnace turning on, Fan off, A/C off");
          #endif
          sendStatus();
        }
        digitalWrite(pinRelayOut, RELAY_ON);
      }
    }
    else if (strcmp(opMode, "Fan")==0)  {                                           // Heater off, Fan auto, A/C off
      digitalWrite(pinRelayOut, RELAY_OFF);                       // Heater off
      // Fan on
      // A/C off
      #ifdef LOOPDEBBUG
      Serial.println("Fan only");
      Serial.println("Furnace off, Fan on, A/C off");
      #endif
      sendStatus();
    }
    else if (strcmp(opMode, "Cool")==0)  {                                          // Heater off, Fan off, A/C auto
      digitalWrite(pinRelayOut, RELAY_OFF);                       // Heater off
      // Fan off
      // A/C on
      #ifdef LOOPDEBBUG
      Serial.println("A/C on");
      Serial.println("Furnace off, Fan off, A/C on");
      #endif
      sendStatus();
    }

    #ifdef LOOPDEBBUG
    Serial.print("Furnace relay state: "); 
    if (digitalRead(pinRelayOut)==RELAY_ON)  {Serial.println("On");}
    else  {Serial.println("Off");}
    #endif

    drawHistoryGraph();
    /*
    if (button_sel.status==true)  {                                     // Button tester
      Serial.println("Select button pressed.");
      button_sel.status=false;
    }
    if (button_up.status==true)  {
      Serial.println("Up button pressed.");
      button_up.status=false;
    }
    if (button_down.status==true)  {
      Serial.println("Down button pressed.");
      button_down.status=false;
    }
    if (millis()>=(lastUpdate+5000))  {                                 // Mode tester
        modeIcon(opMode, MODE_XPOS, MODE_YPOS);
        if (strcmp(opMode, "Heat")==0)  {
          strcpy(opMode, "Fan");
        }
        else if (strcmp(opMode, "Fan")==0)  {
          strcpy(opMode, "Cool");
        }
        else if (strcmp(opMode, "Cool")==0)  {
          strcpy(opMode, "Err");
        }
        else  {
          strcpy(opMode, "Heat");
        }
        lastUpdate = millis();
      }
    
    if (millis()>=(lastUpdate+5000))  {                                 // Screen tester
      drawBar(4, 15, 0);
      titleText("Settings");
      lastUpdate = millis();
    }
    static bool countUp = true;                                            // Relay tester
    if (countUp==true)  {
      if (settings.tempSet<30)  {settings.tempSet = settings.tempSet+1;}
      else  {countUp = false;}
    }
    else  {
      if (settings.tempSet>0)  {settings.tempSet = settings.tempSet-1;}
      else  {countUp = true;}
    }
    #ifdef LOOPDEBBUG
    Serial.println("**************************************\n");
    #endif
  */
  }
}
