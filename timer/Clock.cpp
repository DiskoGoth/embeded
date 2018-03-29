#include "Arduino.h"
#include "Clock.h"

int Clock::getMinutes() {
    return minutes;
}

void Clock::clear() {
    secondParts = 0;
    seconds = 0;
    minutes = 0;
}

int Clock::tick() {
    secondParts++;
    if (secondParts >= 244) {
        secondParts = 0;
        seconds++;
    }
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
    }
    if (minutes >= 1440) {
        minutes = 0;
    }
    return minutes;
}
