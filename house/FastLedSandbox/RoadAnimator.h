#ifndef WARM_ANIM
    #define WARM_ANIM

#include "Animator.h"
#include <FastLed.h>

class RoadAnimator : Animator {
        public:
            void tick(CRGB leds, int ledsCount, int chunks);
            WarmAnimator() {};

        private:
            void generateGradients();
            byte step;

            byte lastSkyInd;
            byte lastTreeInd;

            CRGB skyChunk[NUM_LEDS];
            CRGB treesChunk[NUM_LEDS];

            byte skyPallete[12] = {0x6c8693, 0x92a1a6, 0xa7c2d3, 0xc4cccf, 0xe6eae9, 0xfaf7f2, 0x7bafcf, 0x8db7d3, 0xa8c6db, 0xc0d1dc, 0xd9e0e7, 0xedf2f1};
            byte treesChunk[11] = {0x1b3519, 0x36732f, 0x7b9a1b, 0x83aaa9, 0xf7f7f9, 0xe9f1b5, 0xc5df71, 0x608b43, 0x453a25, 0x3e6b4c, 0xa6dcaa};
};

#endif
