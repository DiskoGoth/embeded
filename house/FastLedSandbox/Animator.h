#ifndef ANIMATOR_HEADER
    #define ANIMATOR_HEADER

    class Animator {
        public:
            virtual void tick (CRGB leds, int ledsCount, int chunks) = 0;
    };

#endif
