#include "WarmAnimator.h"
#include <FastLed.h>
#nclude "config.h"

WarmAnimator::WarmAnimator () {
    for (byte ledInd = 0; ledInd < NUM_LEDS; ledInd++) {
        this.leds[ledInd] = CHSV(random() % 35, 250 - random() % 50, 200);

        this.valDir[ledInd] = random() % 2;
        this.satDir[ledInd] = random() % 2;
        this.hueDir[ledInd] = random() % 2;
    }
};

void WarmAnimator::tick (CRGB leds, int ledsCount, int chunks) {
    for (byte ledInd = 0; ledInd < NUM_LEDS; ledInd++) {

        leds[ledInd].v = valDir[ledInd] ?
                                leds[ledInd].v + (random() % MUTATION):
                                leds[ledInd].v - (random() % MUTATION);

        if (leds[ledInd].v > 255 - MUTATION) {
            valDir[ledInd] = false;
        } else if (leds[ledInd].v < 150) {
            valDir[ledInd] = true;
        }

        leds[ledInd].s = satDir[ledInd] ?
                            leds[ledInd].s + (random() % MUTATION):
                            leds[ledInd].s - (random() % MUTATION);

        if (leds[ledInd].s > 255 - MUTATION) {
            satDir[ledInd] = false;
        } else if (leds[ledInd].s < 200) {
            satDir[ledInd] = true;
        }

        leds[ledInd].h = hueDir[ledInd] ?
                            leds[ledInd].h + (random() % MUTATION):
                            leds[ledInd].h - (random() % MUTATION);

        if (leds[ledInd].h > 35) {
            hueDir[ledInd] = false;
        } else if (leds[ledInd].h < 5) {
            hueDir[ledInd] = true;
        }

        /*
        Serial.print(leds[ledInd].h, DEC);
        Serial.print("-");
        Serial.print(leds[ledInd].s, DEC);
        Serial.print("-");
        Serial.print(leds[ledInd].v, DEC);
        Serial.print(" ");
        */

        for (byte chunkInd = 0; chunkInd < NUM_CHUNKS; chunkInd++) {
            chunked_leds[(ledInd+1)*(chunkInd+1)-1] = leds[ledInd];
        }
    }

    delay(1);
    FastLED.show();
};
