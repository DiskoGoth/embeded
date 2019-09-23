#ifndef WARM_ANIM
    #define WARM_ANIM

#include "Animator.h"
#include <FastLed.h>

class WarmAnimator : Animator {
        public:
            void tick (CRGB leds, int ledsCount, int chunks);
            WarmAnimator () {};

        private:
            bool valDir[NUM_LEDS];
            bool satDir[NUM_LEDS];
            bool hueDir[NUM_LEDS];
            CHSV chunk[NUM_LEDS];
};

#endif
