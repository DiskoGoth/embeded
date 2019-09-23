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
    for (byte ledInd = 0; ledInd < ledsCount / chunks; ledInd++) {

        this.chunk[ledInd].v = valDir[ledInd] ?
                                this.chunk[ledInd].v + (random() % MUTATION):
                                this.chunk[ledInd].v - (random() % MUTATION);

        if (this.chunk[ledInd].v > 255 - MUTATION) {
            valDir[ledInd] = false;
        } else if (this.chunk[ledInd].v < 150) {
            valDir[ledInd] = true;
        }

        this.chunk[ledInd].s = satDir[ledInd] ?
                            this.chunk[ledInd].s + (random() % MUTATION):
                            this.chunk[ledInd].s - (random() % MUTATION);

        if (this.chunk[ledInd].s > 255 - MUTATION) {
            satDir[ledInd] = false;
        } else if (this.chunk[ledInd].s < 200) {
            satDir[ledInd] = true;
        }

        this.chunk[ledInd].h = hueDir[ledInd] ?
                            this.chunk[ledInd].h + (random() % MUTATION):
                            this.chunk[ledInd].h - (random() % MUTATION);

        if (this.chunk[ledInd].h > 35) {
            hueDir[ledInd] = false;
        } else if (this.chunk[ledInd].h < 5) {
            hueDir[ledInd] = true;
        }

        /*
        Serial.print(this.chunk[ledInd].h, DEC);
        Serial.print("-");
        Serial.print(this.chunk[ledInd].s, DEC);
        Serial.print("-");
        Serial.print(this.chunk[ledInd].v, DEC);
        Serial.print(" ");
        */

        for (byte chunkInd = 0; chunkInd < chunks; chunkInd++) {
            leds[(ledInd + 1) * (chunkInd + 1) - 1] = this.chunk[ledInd];
        }
    }

    delay(1);
    FastLED.show();
};
