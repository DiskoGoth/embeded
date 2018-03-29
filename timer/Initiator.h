#ifndef HEADER_INITIATOR
    #define HEADER_INITIATOR

    class Initiator {
        private:
            uint8_t holdDelay = 360; //from 360(6h) upto 720(12h)
            uint8_t relay;
            void hold (void);
            void unhold (void);
        public:
            Initiator (uint8_t);
            bool checkDelay (Clock, int);
    };

#endif
