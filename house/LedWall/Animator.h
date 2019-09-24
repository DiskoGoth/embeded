#ifndef ANIMATOR_HEADER
    #define ANIMATOR_HEADER

#include <FastLed.h>

    class Animator {
        public:
            virtual void tick (CRGB leds[], int ledsCount) = 0;
    };

#endif
