// old version of Color Clock code
// if using MCU without RTC or wifi, so need to set the time manually in the code
// very clunky

#include <Time.h>
#include <TimeLib.h>
#include <FastLED.h>

int hrs=13;
int mins=11;
int secs=0;
int days=7;
int months=1;
int yrs=2020;
int hue;
int sat; 
int intensity;
int minsecs;

//int hr1[] = {25, 24};
//int hr2[] = {21, 20};
//int hr3[] = {19, 18};
//int hr4[] = {17, 16};
//int hr5[] = {15, 14};
//int hr6[] = {13, 12};
//int hr7[] = {11, 10};
//int hr8[] = {9, 8};
//int hr9[] = {7,6};
//int hr10[] = {5, 4};
//int hr11[] = {3, 2};
//int hr12[] = {1, 0};
int AMPM[] = {22, 23};
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
                         {1, 0}};  

#define DATA_PIN    10
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    26
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          255

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  setTime( hrs,mins,secs,days,months,yrs); // alternative to above, yr is 2 or 4 digit yr
  time_t t = now(); // store the current time in time variable t


}

void loop() {
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(" month: ");
  Serial.print(month());
  Serial.print("day: ");
  Serial.print(day());
  Serial.print("year: ");
  Serial.print(year());
  secs = second();
  mins = minute();
  hrs = hourFormat12()-1;
  minsecs = 60*(mins)+(secs+1);
  //for int(i = 1; i<60

  
  hue = NewMap(minsecs, 1 , 3600, 0, 255);
  Serial.print("seconds in this hour: ");
  Serial.println(minsecs);
  Serial.print("hue: ");
  Serial.println(hue);
  //int whatLeds[2] = {hoursArray[hrs]};
  
  if (minsecs = 1) {
    FastLED.clear();
  }
  for(int i = 0; i<2; i++) {
    leds[hoursArray[hrs][i]] = CHSV( hue, 255, 255);
  }
  if (isPM()) {
    for(int i = 0; i<2; i++) {
      leds[AMPM[i]] = CHSV( 0, 0, 255);
    }
  }
  FastLED.show();  

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
 if (in_min == in_max) return out_min/2 + out_max/2;    // out_min or out_max? better

 // test if there will be an overflow with well known (unbalanced) formula
 if (( (MAXLONG / abs(out_max - out_min)) < (val - in_min) )  // multiplication overflow test
 || ((MAXLONG - in_max) < -in_min ))                        // division overflow test
 {
   // if overflow would occur that means the ranges are too big
   // To solve this we divide both the input & output range in two
   // alternative is to throw an error.
   // Serial.print(" >> "); // just to see the dividing
   long mid = in_min/2 + in_max/2;
   long Tmid = out_min/2 + out_max/2;  
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

 unsigned long newpos = ((pos * nov) + niv-1) / niv;  // new position with rounding
 if (out_min < out_max) return out_min + newpos -1;
 return out_min - newpos + 1;
}
