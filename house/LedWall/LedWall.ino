#include <FastLED.h>
#include "Animator.h"
#include "WarmAnimator.h"
#include "conf.h"

#define LED_PIN     10
#define BRIGHTNESS  250
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB


const int ledsCount = ledsInChunk * chunksCount;
CRGB leds[ledsCount];


void setup() {
    Serial.begin(9600);
    delay( 3000 ); // power-up safety delay

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, ledsInChunk*chunksCount).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
}

void loop() {
    static WarmAnimator wAnim;

    wAnim.tick(leds, ledsCount);
}

