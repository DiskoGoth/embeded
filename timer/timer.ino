#include "Clock.h"
#include "Initiator.h"

const uint8_t relay = PB0;
const uint8_t balancer = PB1;
const uint8_t knobInterupt = PB2;
const uint8_t knob = PB3;
const uint8_t btn = PB4;

Clock clock;
Initiator intr (relay);

void setup() {
  DDRB |= (1 << relay); //make pin output

  //does not need to be height
  //PORTB |= (1 << relay); //make pin hight

  PCMSK |= (1 << knobInterupt); //for PCIE
  GIMSK |= (1 << INT0) | (1 << PCIE);

  PORTB |= (1 << btn) | (1 << knobInterupt); //pullup

  TCCR1 = 0;
  TCCR1 |= (1 << CS12) | (1 << CS10);
  TIMSK |= (1 << TOIE1);

  sei();
}

void loop() {
  delay(check() ? 500 : 60000);
}

//on knob input
ISR(INT0_vect) {
  balanceInterupt();
}

//on button pressed
ISR(PCINT0_vect) {
  clock.clear();
  check();
}

ISR(TIMER1_OVF_vect) {
    clock.tick();
    check();
}

bool check () {
    return intr.checkDelay(clock, analogRead(knob));
}

void balanceInterupt () {
  int val = (analogRead(knob) / 4) + 20;
  
  val = val > 255 ? 255 : val;
  //val = val < 30 ? 30 : val;

  analogWrite(balancer, val);
}
