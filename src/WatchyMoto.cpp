// WatchyMoto.cpp
#include "WatchyMoto.h"

// Static member initialization
RTC_DATA_ATTR bool WatchyMoto::light = true;
RTC_DATA_ATTR int WatchyMoto::face = 0;

// London
#define LAT "51.5074"
#define LON "-0.1278"
#define GMT_OFFSET_SEC 3600 * 0 // GMT

#define OPENWEATHERMAP_URL "http://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&lang={lang}&units={units}&appid={apiKey}" //open weather api using lat lon
#define OPENWEATHERMAP_APIKEY "f058fe1cad2afe8e2ddc5d063a64cecb" //use your own API key :)
#define TEMP_UNIT "metric" //metric = Celsius , imperial = Fahrenheit
#define TEMP_LANG "en"
#define WEATHER_UPDATE_INTERVAL 30 //must be greater than 5, measured in minutes
//NTP Settings
#define NTP_SERVER "pool.ntp.org"


watchySettings settings{
    .cityID = "",
    .lat = LAT,
    .lon = LON,
    .weatherAPIKey = OPENWEATHERMAP_APIKEY,
    .weatherURL = OPENWEATHERMAP_URL,
    .weatherUnit = TEMP_UNIT,
    .weatherLang = TEMP_LANG,
    .weatherUpdateInterval = WEATHER_UPDATE_INTERVAL,
    .ntpServer = NTP_SERVER,
    .gmtOffset = GMT_OFFSET_SEC,
    .vibrateOClock = true,
};

WatchyMoto::WatchyMoto() : Watchy(settings) {

}

void WatchyMoto::drawWatchFace() {
    if (currentTime.Hour == 00 && currentTime.Minute == 00) {
        sensor.resetStepCounter();
    }

     drawCaptnWednesday(light, 1);
}

void WatchyMoto::drawCaptnWednesday(bool light, float batt) {

    // ** SETUP **

    int16_t x1, y1;
    uint16_t w, h;
    String textstring, textstringday, textstringtime, textstringsteps;

    // draw background
    display.fillScreen(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawBitmap(0,0, captnwednesday_img, 200, 200, light ? GxEPD_WHITE : GxEPD_BLACK);

    display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextWrap(false);

    // draw date  //////////////////////////////////////////////////////////////// draw date //

    display.setFont(&Tintin_Dialogue9pt7b);

    textstringday = dayStr(currentTime.Wday);
    //textstringday.toUpperCase();
    display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(76, 66); // weekday position
    display.print(textstringday);
    
    display.setFont(&Tintin_Dialogue10pt7b);
    
    textstring = currentTime.Day;
    textstring += "-";
    textstring += monthShortStr(currentTime.Month);
    //textstring.toUpperCase();

    display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(0, 194); // date position
    display.print(textstring);
    
    // draw time /////////////////////////////////////////////////////////////////////////////////////////////// TIME 
    
    display.setFont(&Tintin_Dialogue16pt7b);
    display.setCursor(60, 199);
    int displayHour;
    if(HOUR_12_24==12){
      displayHour = ((currentTime.Hour+11)%12)+1;
    } else {
      displayHour = currentTime.Hour;
    }
    if(displayHour < 10){
        display.print("0");
    }
    display.print(displayHour);
    display.print(":");
    if(currentTime.Minute < 10){
        display.print("0");
    }
    display.println(currentTime.Minute);
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////// END 7SEG

    // draw battery  ///////////////////////////////////////////////////////////////// draw battery //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //  Draw Battery from 7_SEG
    //display.drawBitmap(05, 05, battery, 37, 21, light ? GxEPD_BLACK : GxEPD_WHITE);
    //display.fillRect(160, 30, 27, BATTERY_SEGMENT_HEIGHT, light ? GxEPD_WHITE : GxEPD_BLACK);//clear battery segments
    int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();
    if(VBAT > 4.1){
        batteryLevel = 3;
    }
    else if(VBAT > 3.95 && VBAT <= 4.1){
        batteryLevel = 2;
    }
    else if(VBAT > 3.80 && VBAT <= 3.95){
        batteryLevel = 1;
    }
    else if(VBAT <= 3.80){
        batteryLevel = 0;
    }

    for(int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++){
        display.fillRect(159, 151 + (batterySegments * (BATTERY_SEGMENT_SPACING-2)), BATTERY_SEGMENT_HEIGHT-3, BATTERY_SEGMENT_WIDTH-2, light ? GxEPD_BLACK : GxEPD_WHITE);
    } //  END OF Draw Battery from 7_SEG

    ////////////// Draw Steps
    // reset step counter at midnight
        
    if (currentTime.Hour == 0 && currentTime.Minute == 0){
      sensor.resetStepCounter();
    }
    uint32_t stepCount = sensor.getCounter();
    //display.drawBitmap(180, 177, steps, 19, 23, light ? GxEPD_BLACK : GxEPD_WHITE);
    display.setFont(&Tintin_Dialogue8pt7b);
    display.setCursor(160, 184);
    display.print("Steps");
    display.drawFastHLine(159,184, 40, light ? GxEPD_BLACK : GxEPD_WHITE);
    
    display.setFont(&Tintin_Dialogue8pt7b);
    textstringsteps = String(stepCount);
    display.getTextBounds(textstringsteps, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(198 - w, 199);
    display.println(textstringsteps);
    
}
