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
  int count=0;
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    count++;
    if (count > 20){
      break;
    }
  }
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  if (WiFi.status() != WL_CONNECTED){
    tft.drawString("no wifi.",tft.width() / 2, tft.height() / 2,4);
  }else{
    tft.drawString("wifi connected",tft.width() / 2, tft.height() / 2,4);
  }

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
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  connectWifi();
  getTime();
  tft.fillScreen(TFT_BLACK);

  sprite.createSprite(320,170);
  sprite.fillSprite(TFT_BLACK);
  //sprite.setTextDatum(MC_DATUM);
  sprite.loadFont(segaFont);
  sprite.setTextColor(TFT_ORANGE);
  sprite.pushSprite(0,0);
}


void loop() {

  if (millis() > currTime + period){
      currTime = millis(); getTime();
  }

  sprite.fillSprite(TFT_BLACK);
  
  // Always Center
  //sprite.drawString(String(timeHour) + ":" + String(timeMin) + ":" + String(timeSec),tft.width() / 2, tft.height() / 2);
  sprite.drawString(String(timeHour) + ":" + String(timeMin) + ":" + String(timeSec),20,50);

  sprite.pushSprite(0,0);
  delay(1000);

}
