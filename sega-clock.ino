#include <TFT_eSPI.h>
#include <SPI.h>
#include "sega.h"
#include <WiFi.h>

TFT_eSPI tft=TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

//Set NTP Server
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -18000; // time zone offset
const int daylightOffset_sec = -18000;


// Setup Wifi
const char *ssid = "<YOUR_WIFI_NAME>";
const char *password = "<YOUR_WIFI_PASSWORD>";

//Set Time Constants
char timeHour[3];
char timeMin[3];
char timeSec[3];
char day[3];
char month[10];
char year[5];
char timeWeekDay[10];
int dayInWeek;
unsigned long currTime = 0;
int period = 900;


void connectWifi(){
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);

  }
  tft.drawString("Wifi Connected!",70,50,4);
  delay(2000);
}

void getTime() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return;
    }

    strftime(timeHour, 3, "%H", &timeinfo);
    strftime(timeMin, 3, "%M", &timeinfo);
    strftime(timeSec, 3, "%S", &timeinfo);
    strftime(timeWeekDay, 10, "%A", &timeinfo);

    strftime(day, 3, "%d", &timeinfo);
    strftime(month, 10, "%B", &timeinfo);
    strftime(year, 5, "%Y", &timeinfo);
}

void setup() {
  
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  connectWifi();
  getTime();
  tft.fillScreen(TFT_BLACK);

  sprite.createSprite(320,170);
  sprite.fillSprite(TFT_BLACK);
  sprite.loadFont(segaFont);
  sprite.setTextColor(TFT_ORANGE);
  sprite.pushSprite(0,0);
}


void loop() {

  if (millis() > currTime + period){
      currTime = millis(); getTime();
  }

  sprite.fillSprite(TFT_BLACK);
  sprite.drawString(String(timeHour) + ":" + String(timeMin) + ":" + String(timeSec),35,55);
  sprite.pushSprite(0,0);
  delay(1000);

}
