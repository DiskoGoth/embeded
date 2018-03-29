const int analogInPin = 3;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 0; // Analog output pin that the LED is attached to


void setup() {
}

void loop() {
  // read the analog in value:
  int sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  int outputValue = (sensorValue / 4) + 20;
  
  if (outputValue > 255) {
    outputValue = 255;
  }
  if (outputValue < 30) {
    //outputValue = 30;
  }
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2000);
}
