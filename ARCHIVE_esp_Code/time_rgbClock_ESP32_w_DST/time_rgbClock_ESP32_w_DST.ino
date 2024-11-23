// Color Clock
// originally made in Summer 2020
// updated October 2022 to run with ESP32

// Create a clock but tell the time using color
// Using ws2812 addressable leds, we represent the hour by lighting up the hour
// the color of that hour tells you the minutes of the hour, by cycling around the color wheel

// TODO:
// - make ESP an access point so you can enter wifi info that way instead of having to upload code again
//  - if there is no wifi, set the time manually from your device via the access point. (can we grab the device's time and just use that?)
//  - having to set the UTC_OFFSET and DST manually in code is a little annoying too.
//    - could use wifiLocation: https://www.arduino.cc/reference/en/libraries/wifilocation/
//    - or geolocation of ipaddress
// - do fun animation at the top of the hour. like a cukoo clock.


#include <TimeLib.h>
#include <FastLED.h>
#include <WiFi.h>
#include <Time.h>

const char * ssid = "barn mesh net";
const char * wifipw = "317nelmsave";

// time server setup constants
#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     -14400
#define UTC_OFFSET_DST 0

// led strip setup constants
#define DATA_PIN    2
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    26
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          255

//time variables

int8_t secs;
int8_t mins;
int8_t hrs;
int8_t hrs_raw;
int hue;
int sat;
int intensity;
int minsecs;

struct tm timeinfo;

//breakdown of which leds correspond to which numbers
//int hr1[] = {25, 24};
//int hr2[] = {21, 20};
//int hr3[] = {19, 18};
//int hr4[] = {17, 16};
//int hr5[] = {15, 14};
//int hr6[] = {13, 12};
//int hr7[] = {11, 10};
//int hr8[] = {9, 8};
//int hr9[] = {7, 6};
//int hr10[] = {5, 4};
//int hr11[] = {3, 2};
//int hr12[] = {1, 0};
int AMPM[] = {22, 23};
// index 0 is hour1, index 1 is hour 2, index 11 is hr12
int hoursArray[12][2] = {{25, 24},
  {21, 20},
  {19, 18},
  {17, 16},
  {15, 14},
  {13, 12},
  {11, 10},
  {9, 8},
  {7, 6},
  {5, 4},
  {3, 2},
  {1, 0}
};

//helper functions

void setTimezone(String timezone) {
  Serial.printf("  Setting Timezone to %s\n", timezone.c_str());
  setenv("TZ", timezone.c_str(), 1); //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();
}

void initTime(String timezone) {
  struct tm timeinfo;

  Serial.println("Setting up time");
  configTime(0, 0, "pool.ntp.org");    // First connect to NTP server, with 0 TZ offset
  if (!getLocalTime(&timeinfo)) {
    Serial.println("  Failed to obtain time");
   }
  Serial.println("  Got the time from NTP");
  // Now we can set the real timezone
  setTimezone(timezone);
}


void printLocalTime()
{
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

//TODO: need to make this keep searching for wifi if it doesnt connect the first time
// does this work?

void  startWifi() {
  WiFi.begin(ssid, wifipw, 6);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi connected");
  Serial.print("Wifi RSSI= ");
  Serial.println(WiFi.RSSI());
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println("Hello, ESP32!");
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  // setTime( hrs, mins, secs, days, months, yrs); // alternative to above, yr is 2 or 4 digit yr
  // time_t t = now(); // store the current time in time variable t
  startWifi();
  initTime("EST+5EDT,M3.2.0/2,M11.1.0/2");   // Set for EST (eastern standard time)
  printLocalTime();
}

void loop() {
  delay(1000);
  getLocalTime(&timeinfo);
  Serial.println(&timeinfo);
  // Serial.print(&timeinfo, "%H");
  // Serial.print(":");
  // Serial.print(&timeinfo, "%M");
  // Serial.print(":");
  // Serial.print(&timeinfo, "%S");
  // Serial.print(" month: ");
  // Serial.print(&timeinfo, "%B");
  // Serial.print(" day: ");
  // Serial.print(&timeinfo, "%d");
  // Serial.print(" year: ");
  // Serial.println(&timeinfo, "%Y");

  secs = timeinfo.tm_sec;
  mins = timeinfo.tm_min;
  hrs_raw =  timeinfo.tm_hour;
  hrs = hrs_raw % 12; //12pm or am becomes 0 ..
  if (hrs == 0) { //make index 0 be hour 12 so things are right with the world
    hrs = 12;
  }
  hrs = hrs - 1; // need to correct for our index starting at 0, but 0 is hour 1.

  minsecs = 60 * (mins) + (secs + 1); // for determining hue


  hue = NewMap(minsecs, 1, 3600, 0, 255);
  Serial.print("Hour: ");
  Serial.print(hrs);
  Serial.print(" seconds in this hour: ");
  Serial.println(minsecs);
  Serial.print("hue: ");
  Serial.println(hue);

  if (minsecs == 1) {
    Serial.println("clearing!");
    FastLED.clear();
  }

  //hour light
  for (int i = 0; i < 2; i++) {
    leds[hoursArray[hrs][i]] = CHSV( hue, 255, 255);
    //    debug for led number and color
    //    Serial.print("led number:" );
    //    Serial.print(hoursArray[hrs][i]);
    //    Serial.print(" hue of led: ");
    //    Serial.println(hue);

  }

  //AM/PM light if we are in the afternoon
  if ( hrs_raw >= 12) {
    int hrsMin = ((hrs_raw % 12) * 60) + (mins);
    int pmHue = NewMap(hrsMin, 0, 720, 0, 255);
    Serial.print("minutes after noon: ");
    Serial.print(hrsMin);
    Serial.print(" afternoon hue ");
    Serial.println(pmHue);
    for (int i = 0; i < 2; i++) {
      leds[AMPM[i]] = CHSV( pmHue, 255, 255);
    }
  }
  FastLED.show();

  //debug for color for each led
  //  for (int i = 0; i < 2; i++) {
  //    Serial.println(leds[hoursArray[hrs][i]].red);
  //    Serial.println(leds[hoursArray[hrs][i]].green);
  //    Serial.println(leds[hoursArray[hrs][i]].blue);
  //  }

  //  }
}

#define MAXLONG 2147483647

long NewMap(long val, long in_min, long in_max, long out_min, long out_max)
{
  // TEST: in_min must be lower than in_max => flip the ranges
  // must be done before out of range test
  if (in_min > in_max) return NewMap(val, in_max, in_min, out_max, out_min);

  // TEST: if input value out of range it is mapped to border values. By choice.
  if (val <= in_min) return out_min;
  if (val >= in_max) return out_max;

  // TEST: special range cases
  if (out_min == out_max) return out_min;
  if (in_min == in_max) return out_min / 2 + out_max / 2; // out_min or out_max? better

  // test if there will be an overflow with well known (unbalanced) formula
  if (( (MAXLONG / abs(out_max - out_min)) < (val - in_min) )  // multiplication overflow test
      || ((MAXLONG - in_max) < -in_min ))                        // division overflow test
  {
    // if overflow would occur that means the ranges are too big
    // To solve this we divide both the input & output range in two
    // alternative is to throw an error.
    // Serial.print(" >> "); // just to see the dividing
    long mid = in_min / 2 + in_max / 2;
    long Tmid = out_min / 2 + out_max / 2;
    if (val > mid)
    {
      // map with upper half of original range
      return NewMap(val, mid, in_max, Tmid, out_max);
    }
    // map with lower half of original range
    return NewMap(val, in_min, mid, out_min, Tmid);
  }

  // finally we have a range that can be calculated
  // unbalanced
  // return out_min + ((out_max - out_min) * (val - in_min)) / (in_max - in_min);

  // or balanced
  // return BalancedMap(val, in_min, in_max, out_min, out_max);
  unsigned long niv = in_max - in_min + 1;          // number input valuer
  unsigned long nov = abs(out_max - out_min) + 1;   // number output values
  unsigned long pos = val - in_min + 1;             // position of val

  unsigned long newpos = ((pos * nov) + niv - 1) / niv; // new position with rounding
  if (out_min < out_max) return out_min + newpos - 1;
  return out_min - newpos + 1;
}
