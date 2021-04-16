/*
 * switch pins 14,12,13
 * Relay pins 16,00,02
 * PCF8574 Address 0x20, SW P1,P2,P3, RL P5,P6,P7
 */


 #include <Arduino.h>
 #include <FS.h>
 #include <EEPROM.h>
 #include <TimeLib.h>
 #include "RTClib.h"
 #include <ArduinoJson.h>
 #include <ESP8266WiFi.h>
 #include <WiFiUdp.h>
 #include <ESP8266mDNS.h>
 #include <ESPAsyncTCP.h>
 #include <ESPAsyncWebServer.h>
 #include "stdlib_noniso.h"

#include "SinricPro.h"
#include "SinricProSwitch.h"
 
 #include "webf/ediys.min.css.gz.h"
 #include "webf/ediys.min.js.gz.h"
 #include "webf/server.js.gz.h"
 #include "webf/index.html.gz.h"
 #include "webf/icomoon.woff.gz.h"


#define APP_KEY           "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID_1       "5dc1564130xxxxxxxxxxxxxx"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define SWITCH_ID_2       "5dc1564130xxxxxxxxxxxxxx"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define SWITCH_ID_3       "5dc1564130xxxxxxxxxxxxxx"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
//#define SWITCH_ID_4       "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

const char* hostName = "Ediys";
const char* ssid = "SSID"; 
const char* wifipass = "Password";

const int buttonPin0 = 14;     // the number of the pushbutton pin D5, D6, D7 (GPIO14,12,13)
const int buttonPin1 = 12;
const int buttonPin2 = 13;
const int relay0 =  16;      // the number of the LED pin pin D0, D3, D4, D8 (GPIO16,00,02,15)
const int relay1 =  02;
const int relay2 =  00;

int sw0,sw1,sw2;
int acs0=1,acs1=1,acs2=1;
unsigned long currentMillis =0;
unsigned long previousMillis = 0;
const long interval = 200; //1000
bool dtdisplay = false;
//bool restartRequired = false;
////int buttonState;


RTC_DS3231 rtc;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void ICACHE_FLASH_ATTR setupwifi(){
WiFi.disconnect();
int c=0;
//checkupdate();
WiFi.mode(WIFI_STA);

// Set Hostname.
  String host(hostName);
  host += String(ESP.getChipId(), HEX);
  WiFi.hostname(host);
   
  WiFi.begin(ssid, wifipass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
      c++;
    if(c>30){
      break;
   }
  }
}

void ICACHE_FLASH_ATTR setup() {
pinMode(relay0, OUTPUT);
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(buttonPin0, INPUT);
pinMode(buttonPin1, INPUT);
pinMode(buttonPin2, INPUT);
  EEPROM.begin(512);
  SPIFFS.begin();
  if (!rtc.begin()) 
    {
    Serial.println("Couldn't find RTC");
    }

  if (rtc.lostPower()) 
    {
    Serial.println("RTC lost power, lets set the time!");
    }
  delay(2000); // delay for relay on off prevention
  loadeeprom();
  setupwifi();
  setupSinricPro(); // for sinric pro
  startserver();
  }

void ICACHE_RAM_ATTR loop() {
  MDNS.update();
 currentMillis = millis();
 if (currentMillis - previousMillis >= interval) {
    previousMillis= currentMillis;
    if(dtdisplay){
  senddtime();
  }
  
switchin();
ws.cleanupClients();

}
SinricPro.handle();
}
