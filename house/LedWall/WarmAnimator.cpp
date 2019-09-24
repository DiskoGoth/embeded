#include "WarmAnimator.h"
#include <FastLed.h>
#include "conf.h"

#define MUTATION    3

WarmAnimator::WarmAnimator () {
    for (byte ledInd = 0; ledInd < ledsInChunk; ledInd++) {
        this->chunk[ledInd] = CHSV(random() % 35, 250 - random() % 50, 200);

        this->valDir[ledInd] = random() % 2;
        this->satDir[ledInd] = random() % 2;
        this->hueDir[ledInd] = random() % 2;
    }
};

void WarmAnimator::tick (CRGB leds[], int ledsCount) {
    for (byte ledInd = 0; ledInd < ledsCount / chunksCount; ledInd++) {

        this->chunk[ledInd].v = valDir[ledInd] ?
                                this->chunk[ledInd].v + (random() % MUTATION):
                                this->chunk[ledInd].v - (random() % MUTATION);

        if (this->chunk[ledInd].v > 255 - MUTATION) {
            valDir[ledInd] = false;
        } else if (this->chunk[ledInd].v < 150) {
            valDir[ledInd] = true;
        }

        this->chunk[ledInd].s = satDir[ledInd] ?
                            this->chunk[ledInd].s + (random() % MUTATION):
                            this->chunk[ledInd].s - (random() % MUTATION);

        if (this->chunk[ledInd].s > 255 - MUTATION) {
            satDir[ledInd] = false;
        } else if (this->chunk[ledInd].s < 200) {
            satDir[ledInd] = true;
        }

        this->chunk[ledInd].h = hueDir[ledInd] ?
                            this->chunk[ledInd].h + (random() % MUTATION):
                            this->chunk[ledInd].h - (random() % MUTATION);

        if (this->chunk[ledInd].h > 35) {
            hueDir[ledInd] = false;
        } else if (this->chunk[ledInd].h < 5) {
            hueDir[ledInd] = true;
        }

        for (byte chunkInd = 0; chunkInd < chunksCount; chunkInd++) {
            int ind = (ledInd + 1) * (chunkInd + 1) - 1;
            leds[ind] = this->chunk[ledInd];
        }
    }

    delay(1);
    FastLED.show();
};
