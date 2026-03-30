#include <Arduino.h>
#include <FastLED.h>

#define LED_COUNT 16

#define ARRAY1_PIN 3
#define ARRAY2_PIN 5

#define ARRAY1_ENABLE 7
#define ARRAY1_MODE   9

#define ARRAY2_ENABLE 11
#define ARRAY2_MODE   12

CRGB leds1[LED_COUNT];
CRGB leds2[LED_COUNT];

int mode1 = 0;
int mode2 = 0;
int maxMode = 3;

int runIndex1 = 0;
int runIndex2 = 0;

bool blinkState1 = false;
bool blinkState2 = false;
unsigned long lastBlink = 0;
unsigned long lastRun = 0;

void setAll(CRGB *leds, CRGB color) {
    for(int i=0;i<LED_COUNT;i++)
        leds[i] = color;
}

void clearStrip(CRGB *leds) {
    for(int i=0;i<LED_COUNT;i++)
        leds[i] = CRGB::Black;
}

void running(CRGB *leds, CRGB color, int &index) {
    clearStrip(leds);
    leds[index] = color;

    index++;
    if(index >= LED_COUNT)
        index = 0;
}

void knightRider(CRGB *leds, CRGB color) {
  static int position = 0;
  static int direction = 1;

  fadeToBlackBy(leds, LED_COUNT, 80);  // creates the trailing fade

  leds[position] = color;

  FastLED.show();
  delay(40);

  position += direction;

  if (position == LED_COUNT - 1 || position == 0) {
    direction = -direction;
  }
}

// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void updateModePins() {
    static bool last1 = true;
    static bool last2 = true;

    bool m1 = readSwitch(ARRAY1_MODE, false);
    bool m2 = readSwitch(ARRAY2_MODE, false);

    if(m1 == false && last1 == true) {
        mode1++;
        if(mode1 > maxMode) mode1 = 1;
    }

    if(m2 == false && last2 == true) {
        mode2++;
        if(mode2 > maxMode) mode2 = 1;
    }

    last1 = m1;
    last2 = m2;
}

void setup() {
    FastLED.addLeds<WS2812, ARRAY1_PIN, GRB>(leds1, LED_COUNT);
    FastLED.addLeds<WS2812, ARRAY2_PIN, GRB>(leds2, LED_COUNT);

    pinMode(ARRAY1_ENABLE, INPUT);
    pinMode(ARRAY1_MODE, INPUT);

    pinMode(ARRAY2_ENABLE, INPUT);
    pinMode(ARRAY2_MODE, INPUT);

    Serial.begin(115200);
}

void loop() {
    updateModePins();

    bool en1 = readSwitch(ARRAY1_ENABLE, false);
    bool en2 = readSwitch(ARRAY2_ENABLE, false);

    if(en1) {
        if(mode1 == 1)
            setAll(leds1, CRGB::White);
            FastLED.show();
        if(mode1 == 2)
            knightRider(leds1, CRGB::White);
        if(mode1 == 3)
            if(blinkState1) {
                setAll(leds1,CRGB::White);
                blinkState1 = false;
            } else {
                clearStrip(leds1);
                blinkState1 = true;
            }
            FastLED.show();
    } else {
        clearStrip(leds1);
        FastLED.show();
    }
    // ARRAY 2 (RED)
    if(en2) {
        if(mode2 == 1) // regular ON
            setAll(leds2, CRGB::Red);
            FastLED.show();
        if(mode2 == 2) // knightRider
            knightRider(leds2, CRGB::Red);
        if(mode2 == 3) // blink
            if(blinkState2) {
                setAll(leds2,CRGB::Red);
                blinkState2 = false;
            } else {
                clearStrip(leds2);
                blinkState2 = true;
            }
            FastLED.show();
    } else {
        clearStrip(leds2);
        FastLED.show();
    }
}