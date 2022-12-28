// Color Clock
// originally made in Summer 2020
// updated October 2022 to run with ESP32
// december 2022 added daylight savings time

/// trying to add functionality for user to change timezone via web.... 

// Create a clock but tell the time using color
// Using ws2812 addressable leds, we represent the hour by lighting up the hour
// the color of that hour tells you the minutes of the hour, by cycling around the color wheel

// TODO:
// - make ESP an access point so you can enter wifi info that way instead of having to upload code again
//  - if there is no wifi, set the time manually from your device via the access point. (can we grab the device's time and just use that?)
//  - having to set the timezone is annoying
//    - could use wifiLocation: https://www.arduino.cc/reference/en/libraries/wifilocation/
//    - or geolocation of ipaddress
// - do fun animation at the top of the hour. like a cukoo clock.


#include <TimeLib.h>
#include <FastLED.h>
#include <WiFi.h>
#include <Time.h>
#include <SPIFFS.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "time.h"
#include "time_zones.h"
#include "dali_config.h"
#include "dali_status.h"





DaliConfig config;
DaliStatus info;



WebServer server(80);
DNSServer dnsServer;

#include <soc/rtc.h>

// time server setup constants
#define NTP_SERVER     "pool.ntp.org"

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

//void  startWifi() {
//  WiFi.begin(ssid, wifipw, 6);
//  Serial.println("Connecting to WiFi");
//  while (WiFi.status() != WL_CONNECTED) {
//    Serial.print(".");
//    delay(500);
//  }
//  Serial.println("WiFi connected");
//  Serial.print("Wifi RSSI= ");
//  Serial.println(WiFi.RSSI());
//  Serial.println("");
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());
//}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println("Hello, ESP32!");
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();  // clear all pixel data
  FastLED.show();
  // setTime( hrs, mins, secs, days, months, yrs); // alternative to above, yr is 2 or 4 digit yr
  // time_t t = now(); // store the current time in time variable t

  // -- Initializing the accespoint // wifi configuration.
  wifi_start();
}

void loop() {
  // once connected, connect to the NTP servers and set the time
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


/********************************* WEB SERVER *********************************/
constexpr char *ap_ssid = "ESP32 Dali Clock";
constexpr uint32_t wifiTimeout = 10000;
constexpr char * webpage = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <title>ESP32 Dali Clock</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
            body {width: max-content;}
            form div {display: flex; gap: 1em; margin: 0.5em 0;}
            label {flex-grow: 1}
            input:not([type = "submit"]), select {
                min-width: 20em;
                box-sizing: border-box;
            }
        </style>
        <script>
            // When the user selects a general location from the list,
            // repopulate it with more specific locations from the server
            async function onFilterChanged(el) {
                if(!el.value) return;
                tz = await fetch("timezones?prefix=" + el.value);
                tz = await tz.json();
                el.innerText = "";
                tz.forEach(x => {
                    o = document.createElement("option");
                    o.innerText = x;
                    el.appendChild(o);
                })
                el.name = "timezone";
                el.removeAttribute("onchange");
            }
        </script>
    </head>
    <body>
        <h1>ESP32 Dali Clock</h1>
        <form action="/config_prefs" method="get">
            <h2>Clock Preferences</h2>
            <div><label for="theme_id">Color Theme:</label>
            <select id="theme_id" name="theme_id">
                <option value="99">Time-of-Day Blend</option>
                <option value="98">Minute Blend</option>
                <option value="0">Night Theme Only</option>
                <option value="1">Dawn Theme Only</option>
                <option value="2">Day Theme Only</option>
                <option value="3">Dusk Theme Only</option>
            </select></div>
            <br>
            <input type="submit" value="Submit">
        </form>
        <form action="/config_time" method="get">
            <h2>Manual Time Selection</h2>
            <div><label for="datetime-local">Time:</label>
            <input type="datetime-local" id="datetime-local" name="datetime-local" step="1"></div>
            </div>
            <div><label for="mil_time">Show 24-hour clock:</label>
            <input type="checkbox" id="mil_time" name="mil_time" checked></div>
            <br>
            <input type="submit" value="Submit">
        </form>
        <form action="/config_wifi" method="get">
            <h2>Network Configuration</h2>
            <div><label for="net_ssid">Network Name:</label>
            <input type="text" id="net_ssid" name="net_ssid"></div>
            <div><label for="net_pass">Network Password:</label>
            <input type="text" id="net_pass" name="net_pass"></div>
            <br>
            <div><label for="ntp_addr">Time Server:</label>
            <input type="text" id="ntp_addr" name="ntp_addr" value="pool.ntp.org"></div>
            <div><label for="location">Location:</label>
            <select id="location" onchange="onFilterChanged(this)">
                <option value="">-- none selected --</option>
                <option>Africa</option>
                <option>America</option>
                <option>Asia</option>
                <option>Antartica</option>
                <option>Arctic</option>
                <option>Asia</option>
                <option>Atlantic</option>
                <option>Australia</option>
                <option>Etc</option>
                <option>Europe</option>
                <option>Indian</option>
                <option>Pacific</option>
            </select></div>
            <br>
            <input type="submit" value="Submit">
        </form>
    </body>
</html>
)rawliteral";

constexpr char * webpage_ok = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <title>ESP32 Dali Clock</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>
    <body>
        <h1>ESP32 Dali Clock</h1>
        <p>Configuration accepted!</p><br>
        <form>
            <input type="button" value="Okay" onclick="history.back()">
        </form>
    </body>
</html>
)rawliteral";

void wifi_start() {
    xTaskCreatePinnedToCore(wifi_task, "wifi_task", 3*1024, NULL, 0, NULL, 1);
}

bool connectToWirelessAccessPoint() {
    // Read the configuration file if it exists

    if(!SPIFFS.begin(true)) return false;
    if(!config.load()) return false;
    if(config.net_ssid.length() == 0) return false;
    info.set("Connecting to " + config.net_ssid + "...");
    WiFi.begin(config.net_ssid.c_str(), config.net_pass.c_str());
    const uint32_t start = millis();
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      if(millis() - start > wifiTimeout) return false;
    }
    info.set("Getting time from " + config.ntp_addr + "...");
    Serial.print("Timezone is ");
    Serial.print(config.timezone);
    String tz = getTzByLocation(config.timezone);
    Serial.print(". Setting TZ to ");
    Serial.print(tz);
    Serial.println();
    configTimeWithTz(tz, config.ntp_addr);
    delay(1000);
    return true;
}

bool becomeWirelessAccessPoint() {
    info.set(String("Starting access point \"") + ap_ssid + "\"");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ap_ssid);
    delay(100);
    Serial.print(String("Running AP at" ) + ap_ssid + " with IP address " + WiFi.softAPIP().toString());
    dnsServer.start(53, "*", WiFi.softAPIP());
    return true;
}

void wifi_task(void* arg) {
    // Either join an AP or become an AP
    if(connectToWirelessAccessPoint() || becomeWirelessAccessPoint()) {
        if (WiFi.getMode() == WIFI_AP)
            info.set(String("Join \"") + ap_ssid + "\" and then go to\nhttp://" + WiFi.softAPIP().toString() + " to configure");
        else
            info.set(String("Go to http://") + WiFi.localIP().toString() + " to reconfigure");

        // Start web server
        server.on("/config_prefs", HTTP_GET, [](){
            server.send(200, "text/html", webpage_ok);
            config.set("theme_id", server.arg("theme_id"));
            config.save();
        });
        server.on("/config_wifi", HTTP_GET, [](){
            server.send(200, "text/html", webpage_ok);
            if(server.arg("net_ssid") != "") {
                config.set("net_ssid", server.arg("net_ssid"));
                config.set("net_pass", server.arg("net_pass"));
            }
            config.set("ntp_addr", server.arg("ntp_addr"));
            config.set("time_dst", server.arg("time_dst"));
            config.set("timezone", server.arg("timezone"));
            config.save();
            info.set("Rebooting...");
            delay(2000);
            ESP.restart();
        });
        server.on("/config_time", HTTP_GET, [](){
            server.send(200, "text/html", webpage_ok);
            String str = server.arg("datetime-local");
            dali.set_date(str.substring( 5, 7).toInt(), str.substring( 8,10).toInt(), str.substring( 0, 4).toInt());
            dali.set_time(str.substring(11,13).toInt(), str.substring(14,16).toInt(), str.substring(17,19).toInt());
            config.set("mil_time", server.arg("mil_time"));
        });
        server.on("/timezones", HTTP_GET, [](){
            String separator = "";
            String prefix = server.arg("prefix");
            String buff = "[\"";
            // Use chunked send otherwise we run out of memory
            server.setContentLength(CONTENT_LENGTH_UNKNOWN);
            server.send(200, "text/html");
            for(int i = 0;;) {
                const char *location = getLocation(i, prefix.c_str());
                if(!location) break;
                buff += separator + location;
                separator = "\",\n\"";
                if(buff.length() > 100) {
                    server.sendContent(buff);
                    buff = "";
                }
            }
            buff += "\"]";
            server.sendContent(buff);
        });
        server.onNotFound([](){
            server.send(200, "text/html", webpage);
        });
        server.begin();
        while(1) {
            dnsServer.processNextRequest();
            server.handleClient();
            delay(2);//allow the cpu to switch to other tasks
        }
    }
    vTaskDelete( NULL );
}
