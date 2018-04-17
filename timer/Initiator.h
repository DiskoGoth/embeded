#ifndef HEADER_INITIATOR
    #define HEADER_INITIATOR

    class Initiator {
        private:
            uint8_t holdDelay = 360; //from 360(6h) upto 720(12h)
            uint8_t accuracy = 3;
            uint8_t relay;
            bool active = false;
            void hold (void);
            void unhold (void);
        public:
            Initiator (uint8_t);
            void applyState(bool);
            bool checkDelay (Clock, int, bool = false);
            bool toggleActivity (bool = false, bool = false);
    };

#endif
