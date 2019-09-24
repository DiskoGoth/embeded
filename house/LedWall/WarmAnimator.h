#ifndef WARM_ANIM
    #define WARM_ANIM

#include "Animator.h"
#include <FastLed.h>
#include "conf.h"

class WarmAnimator : Animator {
        public:
            void tick (CRGB leds[], int ledsCount);
            WarmAnimator ();

        private:
            bool valDir[ledsInChunk];
            bool satDir[ledsInChunk];
            bool hueDir[ledsInChunk];
            CHSV chunk[ledsInChunk];
};

#endif
