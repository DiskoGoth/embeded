#include "Arduino.h"
#include "Clock.h"
#include "Initiator.h"

Initiator::Initiator (uint8_t relay) {
    relay = relay;
}

void Initiator::hold() {
    if (PORTB & (1 << relay)) {
        PORTB |= (1 << relay);
    }
}

void Initiator::unhold() {
    PORTB &= ~(1 << relay);
}

bool Initiator::checkDelay (Clock clock, int knobVal) {
    int delay = map(knobVal, 0, 1023, 360, 720);
    bool changed = delay != holdDelay;
    bool state = clock.getMinutes() >= delay;

    if (changed) {
        holdDelay = delay;
    }

    if (state) {
        unhold();
    } else {
        hold();
    }

    return changed;
}
