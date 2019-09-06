#include <Adafruit_NeoPixel.h>

#define PIN 2	 // input pin Neopixel is attached to

#define NUMPIXELS      12 // number of neopixels in strip
#define NUMGRADS      4 // number of gradient steps
#define RESOLUTION      100 // color resolution

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1; // timing delay in milliseconds

int leds[NUMPIXELS][3];
int gradient[NUMGRADS][3] = {
    {220,220,70},
    {0, 255, 243},
    {220,78,200},
  	{220,220,70}
};

void setup() {
    // Initialize the NeoPixel library.
    pixels.begin();
    Serial.begin(9600);
}

void loop() {
    int colors[3];
    for (int g = 0; g < NUMGRADS - 1; g++) {
        for (int c = 0; c < RESOLUTION; c++) {
            for (int l=0; l < NUMPIXELS; l++) {

                int step = c + l;
                int gi = 0;

                if (step > RESOLUTION) {
                    step = step -RESOLUTION;
                    gi++;
                }
                int grad = g + gi;
                if (grad >= NUMGRADS - 1) {
                    grad = 0;
                }

                for (int b = 0; b < 3; b++) {

                    colors[b] = gradient[grad][b] * (RESOLUTION - step) / RESOLUTION  + gradient[grad+1][b] * step / RESOLUTION;
                }
                pixels.setPixelColor(l, pixels.Color(colors[0], colors[1], colors[2]));
            }

            pixels.show();
            delay(delayval);
            Serial.println(String() + ": " + colors[0] + ", " + colors[1] + ", " + colors[2]);
        }
    }

}

