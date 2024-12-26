// WatchyMoto.h

#ifndef WATCHY_MOTO_H
#define WATCHY_MOTO_H

#include <Watchy.h>
#include "captnwednesday_img.h"
#include "icons.h"
#include "fonts/Tintin_Dialogue8pt7b.h"
#include "fonts/Tintin_Dialogue9pt7b.h"
#include "fonts/Tintin_Dialogue10pt7b.h"
#include "fonts/Tintin_Dialogue16pt7b.h"

// Constants
const uint8_t BATTERY_SEGMENT_WIDTH = 7;
const uint8_t BATTERY_SEGMENT_HEIGHT = 11;
const uint8_t BATTERY_SEGMENT_SPACING = 9;
const uint8_t WEATHER_ICON_WIDTH = 48;
const uint8_t WEATHER_ICON_HEIGHT = 32;


class WatchyMoto : public Watchy {
public:
        using Watchy::Watchy;

    WatchyMoto();
    void drawWatchFace() override;
    // void handleButtonPress() override;

protected:
    void drawCaptnWednesday(bool light, float batt);

private:
    RTC_DATA_ATTR static bool light;
    RTC_DATA_ATTR static int face;
};


#endif // WATCHY_MOTO_H