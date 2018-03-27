/*
  Fading my way
*/

void setup() {
  Serial.begin(9600);

  DDRB |= (1 << PB5) | (1 << PB2);

  TCCR1A = 0;
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~((1 << CS11) | (1 << CS10));

  TCNT1 = 0;
  OCR1A = 62484;


  TIMSK1 = (1 << OCIE1A);

  sei();

  Serial.println("start");
}

volatile uint8_t seconds = 0;
volatile uint8_t minutes = 4;
volatile uint8_t hours = 0;

ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;
  tick();
  check();
  clock();
}

void tick() {
  seconds ++;
  if (seconds == 60) {
      seconds = 0;
      minutes++;
  }
  if (minutes == 60) {
      minutes = 0;
      hours++;
  }
  if (hours == 24) {
      hours = 0;
  }
}

void clock() {
  Serial.println();
  if (hours < 10)
      Serial.print(0);
  Serial.print(hours);
  Serial.print(':');

  if (minutes < 10)
      Serial.print(0);
  Serial.print(minutes);
  Serial.print(':');

  if (seconds < 10)
      Serial.print(0);
  Serial.print(seconds);
}
void check() {
  if (seconds == 0) {
    PORTB ^= (1 << PB5);
  }
}

void loop() {
  PORTB ^= (1 << PB2);
  delay(2);
  PORTB ^= (1 << PB2);
  delay(4);
}
