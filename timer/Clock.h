#ifndef HEADER_CLOCK
        #define HEADER_CLOCK

    class Clock {
        private:
            volatile uint8_t secondParts = 0;
            volatile uint8_t seconds = 0;
            volatile uint16_t minutes = 0;
        public:
            int getMinutes (void);
            void clear (void);
            int tick(void);
    };

#endif
