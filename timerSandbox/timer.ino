const uint8_t relay = PB0;
const uint8_t knobInterupt = PB2;
const uint8_t knob = PB3;
const uint8_t btn = PB4;

uint8_t holdDelay = 360; //from 360(6h) upto 720(12h)

volatile uint8_t secondParts = 0;
volatile uint8_t seconds = 0;
volatile uint16_t minutes = 0;

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

//on knob input
ISR(INT0_vect) {
}

//on button pressed
ISR(PCINT0_vect) {
  clear();
}

ISR(TIMER1_OVF_vect) {
    tick();
    checkHold();
}

//on knob val change checkHold();

void loop() {
  int newDelay = checkDelay();
  if (newDelay != holdDelay) {
      holdDelay = newDelay;
  }
  checkHold();
  delay(60000);

}

void checkHold() {
    if (minutes >= holdDelay) {
        unhold();
    } else { //TODO: if not already holded; or check in hold;
        hold();
    }
}

int checkDelay () {
    int knobVal = analogRead(knob);
    return map(knobVal, 0, 1023, 360, 720);
}

int tick() {
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

void clear() {
    secondParts = 0;
    seconds = 0;
    minutes = 0;
    hold();
}

void hold() {
    PORTB |= (1 << relay);
}

void unhold() {
    PORTB &= ~(1 << relay);
}
