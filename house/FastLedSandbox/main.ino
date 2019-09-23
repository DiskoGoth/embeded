#include <FastLED.h>
#nclude "config.h"
#include "Animator.h"
#include "WarmAnimator.h"

#define ANIM_COUNT  1

CRGB chunked_leds[NUM_LEDS * NUM_CHUNKS];
Animator animators[ANIM_COUNT];

bool animSetupFlag[ANIM_COUNT];
byte animatorNum = 0;

void setup() {
    Serial.begin(9600);
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(chunked_leds, NUM_LEDS*NUM_CHUNKS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

    for (byte i = 0; i < ANIM_COUNT; i++) {
        animSetupFlag[i] = false;
    }
}

void loop() {
    if (!animSetupFlag[animatorNum]) {
        //TODO move this to some AnimatorFactory
        switch (animatorNum) {
            case 0:
                animators[animatorNum] = WarmAnimator()
                break;
        }
        animSetupFlag[animatorNum] = true;
    }

    animators[animatorNum].tick();
}

