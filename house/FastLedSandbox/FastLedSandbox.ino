#include <FastLED.h>

#define LED_PIN     10
#define NUM_CHUNKS  5
#define NUM_LEDS    50
#define BRIGHTNESS  250
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define MUTATION    3

CRGB chunked_leds[NUM_LEDS * NUM_CHUNKS];
bool valDir[NUM_LEDS];
bool satDir[NUM_LEDS];
bool hueDir[NUM_LEDS];
CHSV leds[NUM_LEDS];

void setup() {
    Serial.begin(9600);
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(chunked_leds, NUM_LEDS*NUM_CHUNKS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    for (byte ledInd = 0; ledInd < NUM_LEDS; ledInd++) {
        leds[ledInd] = CHSV(random() % 35, 250 - random() % 50, 200);

        valDir[ledInd] = random() % 2;
        satDir[ledInd] = random() % 2;
        hueDir[ledInd] = random() % 2;

        for (byte chunkInd = 0; chunkInd < NUM_CHUNKS; chunkInd++) {
            byte cLedInd = (ledInd+1)*(chunkInd+1)-1;
            chunked_leds[cLedInd] = leds[ledInd];
        }
    }

}


void loop()
{

    for (byte ledInd = 0; ledInd < NUM_LEDS; ledInd++) {
        leds[ledInd].v = valDir[ledInd] ?
                                leds[ledInd].v + (random() % MUTATION):
                                leds[ledInd].v - (random() % MUTATION);

        if (leds[ledInd].v > 255 - MUTATION) {
            valDir[ledInd] = false;
        } else if (leds[ledInd].v < 150) {
            valDir[ledInd] = true;
        }

        leds[ledInd].s = satDir[ledInd] ?
                            leds[ledInd].s + (random() % MUTATION):
                            leds[ledInd].s - (random() % MUTATION);

        if (leds[ledInd].s > 255 - MUTATION) {
            satDir[ledInd] = false;
        } else if (leds[ledInd].s < 200) {
            satDir[ledInd] = true;
        }

        leds[ledInd].h = hueDir[ledInd] ?
                            leds[ledInd].h + (random() % MUTATION):
                            leds[ledInd].h - (random() % MUTATION);

        if (leds[ledInd].h > 35) {
            hueDir[ledInd] = false;
        } else if (leds[ledInd].h < 5) {
            hueDir[ledInd] = true;
        }

        Serial.print(leds[ledInd].h, DEC);
        Serial.print("-");
        Serial.print(leds[ledInd].s, DEC);
        Serial.print("-");
        Serial.print(leds[ledInd].v, DEC);
        Serial.print(" ");

        for (byte chunkInd = 0; chunkInd < NUM_CHUNKS; chunkInd++) {
            chunked_leds[(ledInd+1)*(chunkInd+1)-1] = leds[ledInd];
        }
    }
    Serial.println("");

    FastLED.show();
    delay(1);
}
