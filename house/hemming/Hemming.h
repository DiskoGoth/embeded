#ifndef HEMMING_HEADER
    #define HEMMING_HEADER

    class Hemming {
        public:
            char encode (char i);
            char decode (char i);
        private:
            bool isEvenNumberOfBits (char i);
            char getControlBits (char i);
            char correctError (char i);
            char mirror (char x);
    };

#endif
