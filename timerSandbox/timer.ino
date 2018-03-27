const uint8_t btn = PB2;
const uint8_t led = PB3;
const uint8_t knob = PB4;

uint8_t holdDelay = 360; //from 360(6h) upto 720(12h)

volatile uint8_t secondParts = 0;
volatile uint8_t seconds = 0;
volatile uint16_t minutes = 0;

void setup() {
  DDRB |= (1 << led);
  PORTB |= (1 << led);

  PORTB |= (1 << btn);
  PCMSK |= (1 << btn);
  GIMSK |= (1 << INT0);


  TCCR1 = 0;
  TCCR1 |= (1 << CS12) | (1 << CS10);
  TIMSK |= (1 << TOIE1);


  sei();
}

ISR(INT0_vect) {
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
    PORTB |= (1 << led);
}

void unhold() {
    PORTB &= ~(1 << led);
}
