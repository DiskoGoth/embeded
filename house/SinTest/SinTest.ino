#include <FastLED.h>

#define LED_PIN     10
#define BRIGHTNESS  250
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[8];
bool once = true;

void setup() {
    Serial.begin(9600);
    delay(3000); // power-up safety delay

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, 8).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

    for (int i = 0; i < 256; i++) {
        fract8 fract = quadwave8(i);
        CRGB blended = blend(CRGB(0,255,200), CRGB(255,0,50), fract);
        Serial.println(String("") + i + "," + fract + " ~ " + blended.r + "-" + blended.g + "-" + blended.b);
    }
}

void loop() {
    delay(1000);
    FastLED.show();
}

