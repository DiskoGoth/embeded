#include "Hemming.h"

/*
 * encode
 *
 * 0 0 0 0 b1 b2 b3 b4 -> c1 c2 b1 c3 b2 b3 b4 c0
 *                     n: n1 n2 n3 n4 n5 n6 n7 n8
 * Where
 *      b - data bits
 *      c - control bits
 *      n - position of bit
 *
 *  For Hemming (7,4): ⊕ is for XOR operation
 *  c1 = n1 ⊕ n3 ⊕ n5 ⊕ n7 = b1 ⊕ b2 ⊕ b4
 *  c2 = n2 ⊕ n3 ⊕ n6 ⊕ n7 = b1 ⊕ b3 ⊕ b4
 *  c3 = n3 ⊕ n4 ⊕ n5 ⊕ n6 = b2 ⊕ b3 ⊕ b4
 *
 *  c0 = c1 ⊕ c2 ⊕ b1 ⊕ c3 ⊕ b2 ⊕ b3 ⊕ b4
 *
 *  returns encoded data byte with control bits
 */
char Hemming::encode (char input) {
    char buff = input & 0xf;

    buff |= (buff & 0x8) << 1;
    buff &= ~0x8;
    buff <<= 1;

    char controlBits = getControlBits(buff);
    buff |= controlBits;

    bool b0 = isEvenNumberOfBits(buff);

    buff |= b0;

    return buff;
};
/*
 * c1 c2 b1 c3 b2 b3 b4 c0 -> 0 0 0 0 b1 b2 b3 b4
 *
 * returns data byte
 */
char Hemming::decode (char input) {
    char buff = correctError(input);

    buff >>= 1;
    buff |= (buff & 0x10) >> 1;
    buff &= 0xf;

    return buff;
};

/*
 * get control bits
 *
 * 0 0 b1 0 b2 b3 b4 0 -> c1 c2  0 c3  0  0  0  0
 *                     n: n1 n2 n3 n4 n5 n6 n7 n8
 * Where
 *      b - data bits
 *      c - control bits
 *      n - position of bit
 *
 *  For Hemming (7,4): ⊕ is for XOR operation
 *  c1 = n1 ⊕ n3 ⊕ n5 ⊕ n7 = b1 ⊕ b2 ⊕ b4
 *  c2 = n2 ⊕ n3 ⊕ n6 ⊕ n7 = b1 ⊕ b3 ⊕ b4
 *  c3 = n3 ⊕ n4 ⊕ n5 ⊕ n6 = b2 ⊕ b3 ⊕ b4
 *
 * returns control bits only
 */
char Hemming::getControlBits (char input) {
    bool c1 = isEvenNumberOfBits(input & 0xaa);
    bool c2 = isEvenNumberOfBits(input & 0x66);
    bool c3 = isEvenNumberOfBits(input & 0x1e);

    return (c1 << 7) | (c2 << 6) | (c3 << 4);
}

/*
 * byte mirroring
 *
 * b1 b2 b3 b4 b5 b6 b7 b8 -> b8 b7 b6 b5 b4 b3 b2 b1
 *
 * returns mirrored byte
 */
char Hemming::mirror(char x) {

    x = ((x & 0x55) << 1) | ((x & 0xAA) >> 1);
    x = ((x & 0xCC) >> 2) | ((x & 0x33) << 2);
    x = (x >> 4) | (x << 4);

    /* second option just in case
        x = (x & 0x55) << 1 | (x & 0xAA) >> 1;
        x = (x & 0x33) << 2 | (x & 0xCC) >> 2;
        x = (x & 0x0F) << 4 | (x & 0xF0) >> 4; 
   */

    return x;
}

/*
 * correct error
 *
 * c1 c2 b1 c3 b2 b3 b4 c0
 * n1 n2 n3 n3 n5 n6 n7 n8
 *
 * Where
 *      b - data bits
 *      c - control bits
 *      n - position of bit
 *
 *  For Hemming (7,4): ⊕ is for XOR operation
 *  s0 = c1 ⊕ c2 ⊕ b1 ⊕ c3 ⊕ b2 ⊕ b3 ⊕ b4 ⊕ c0
 *  s1 = n1 ⊕ n3 ⊕ n5 ⊕ n7 = c1 ⊕ b1 ⊕ b2 ⊕ b4
 *  s2 = n2 ⊕ n3 ⊕ n6 ⊕ n7 = c2 ⊕ b1 ⊕ b3 ⊕ b4
 *  s3 = n3 ⊕ n4 ⊕ n5 ⊕ n6 = c3 ⊕ b2 ⊕ b3 ⊕ b4
 *
 *  if s0 is 0 it means there is no error or two errors
 *  is s0 is 0 and s1 ⊕ s2 ⊕ s3 is 0 then there is two errors
 *  byte 0 0 0 0 0 s1 s2 s3 is a position of bit with error
 *
 *  returns corrected byte;
 */
char Hemming::correctError(char input) {
    bool b0 = isEvenNumberOfBits(input);
    char controlBits = getControlBits(input);

    controlBits |= (controlBits & 0x10) << 1;
    controlBits &= ~0x10; //TODO not sure if neccesary operation

    controlBits = mirror(controlBits);

    if (!b0 && controlBits) {
        //std::cout << "Double error :(" << std::endl;
    }

    if(b0 && !controlBits) {
        //std::cout << "Error in the last bit" << std::endl;
        return input;
    }

    return input ^ 0x80 >> (controlBits - 1);
};

/*
 * XOR operation on all bits in byte
 */
bool Hemming::isEvenNumberOfBits(char n) {
    n = ((n>>1) & 0x55) + (n & 0x55);
    n = ((n>>2) & 0x33) + (n & 0x33);
    n = ((n>>4) & 0x0F) + (n & 0x0F);

    return n%2;
};

