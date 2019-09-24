#ifndef WARM_ANIM
    #define WARM_ANIM

#include "Animator.h"
#include <FastLed.h>

class WarmAnimator : Animator {
        public:
            void tick (CRGB leds, int ledsCount, int chunks);
            WarmAnimator () {};

        private:
            bool *valDir;
            bool *satDir;
            bool *hueDir;
            CHSV *chunk;
};

#endif
