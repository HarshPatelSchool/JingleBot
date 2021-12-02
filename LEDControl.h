#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//LED
#define colorPin 4 //pin for LEDs
#define NUMPIXELS 8//Number of LEDS

Adafruit_NeoPixel pixels(NUMPIXELS, colorPin, NEO_GRB + NEO_KHZ800);

void setupLEDS(int x, int y){
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  
}
