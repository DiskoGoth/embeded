#include "WarmAnimator.h"
#include <FastLed.h>
#nclude "config.h"

RoadAnimator::RoadAnimator () {
    this.step = 1;
    this.generateGradients();
    this.lastSkyInd = random() % 13;
    this.lastTreeInd = random() % 12;
};

void RoadAnimator::generateGradients () {
    byte newSkyInd = random() % 13;
    byte newTreeInd = random() % 12;

    fill_gradient(this.skyChunk,
            0,
            this.skyPallete[this.lastSkyInd],
            NUM_LEDS,
            this.skyPallete[newSkyInd],
            SHORTEST_HUES);

    fill_gradient(this.treesChunk,
            0,
            this.treesPallete[this.lastTreeInd],
            NUM_LEDS,
            this.treesPallete[newTreeInd],
            SHORTEST_HUES);

    this.lastSkyInd = newSkyInd;
    this.lastTreeInd = newTreeInd;
};

//TODO implement shisf funciton to shift chunks on leds array
void RoadAnimator::shift() {
};

void RoadAnimator::tick (CRGB leds, int ledsCount, int chunks) {

    delay(1);
    FastLED.show();
};
