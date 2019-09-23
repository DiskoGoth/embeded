#include <FastLED.h>
#nclude "config.h"

CRGB chunked_leds[NUM_LEDS * NUM_CHUNKS];

void setup() {
    Serial.begin(9600);
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(chunked_leds, NUM_LEDS*NUM_CHUNKS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

}

void loop() {
}

