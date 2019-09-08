#include <iostream>
#include <bitset>
#include "Hemming.h"

char makeError(char input) {
    char r = rand() % 7;
    return input ^ (0x80 >> r);
}

int main(){
    Hemming hemming;

    for (char i = 0; i < 16; i++) {
        std::cout << "#" << (int)i << std::endl;
        std::cout << "encoding " << std::bitset<8>(i) << std::endl;

        char encoded = hemming.encode(i&0xf);
        std::cout << "encoded  " << std::bitset<8>(encoded) << std::endl;

        char error = makeError(encoded);
        std::cout <<  "recieved " << std::bitset<8>(error) << std::endl;

        char decoded = hemming.decode(error);
        std::cout << "decoded  " << std::bitset<8>(decoded) << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
