#include <Adafruit_NeoPixel.h>

#define PIN 2	 // input pin Neopixel is attached to

#define NUMPIXELS      12 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10; // timing delay in milliseconds

int colors[] = {100, 100, 100};

void setup() {
  // Initialize the NeoPixel library.
    pixels.begin();
    Serial.begin(9600);
}

void loop() {
  setColor();

  for (int i=0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(colors[0], colors[1], colors[2]));

    // This sends the updated pixel color to the hardware.
    pixels.show();

    // Delay for a period of time (in milliseconds).
    delay(delayval);
  }
}

// setColor()
// picks random values to set for RGB
void setColor(){
    int color = random(0, 2);
    int direction = random(-100,100);

    colors[color] += direction;

    if (colors[color] > 255) {
     colors[color] = 0;
    }
    if (colors[color] < 0) {
     colors[color] = 255;
    }
    Serial.println(String("") + colors[0] + ", " + colors[1] + ", " + colors[2]);
}

