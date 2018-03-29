const int pwm = PB1; // Analog output pin that the LED is attached to
const int led = PB0;

const int btn = PB2;
const int aIn = PB3;  // Analog input pin that the potentiometer is attached to

void setup() {
  DDRB |= (1 << pwm) | (1 << led);
  PORTB |= (1 << btn);

  PCMSK |= (1 << btn);
  GIMSK |= (1 << PCIE) | (1 << INT0);

  sei();
}

ISR(PCINT0_vect) {
  PORTB ^= (1 << led);
}

void loop() {

  // read the analog in value:
  // map it to the range of the analog out:
  int sensorValue = analogRead(aIn);
  int outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(pwm, outputValue);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}
