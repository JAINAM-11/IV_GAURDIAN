#include <Adafruit_NeoPixel.h>

// Define pin connected to the LED strip
#define LED_PIN 14  // GPIO14 (Change to your pin if necessary)

// Define the number of LEDs
#define NUM_LEDS 8

// Create the NeoPixel object
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize the LED strip
  strip.begin();
  strip.show();
  strip.setBrightness(64);
}

void loop() {
  // Set all LEDs to green using fill()
  strip.fill(strip.Color(0, 255, 0), 0, NUM_LEDS); // RGB for green (0, 255, 0)
  strip.show();
  delay(1000); // Keep the LEDs on for 1 second

  // Turn off all LEDs using fill()
  strip.fill(strip.Color(0, 0, 0), 0, NUM_LEDS); // Turn off all LEDs (0, 0, 0)
  strip.show();
  delay(1000); // Keep the LEDs off for 1 second

  strip.fill(strip.Color(255, 0, 0), 0, NUM_LEDS); // RGB for green (0, 255, 0)
  strip.show();
  delay(1000); // Keep the LEDs on for 1 second

  // Turn off all LEDs using fill()
  strip.fill(strip.Color(0, 0, 0), 0, NUM_LEDS); // Turn off all LEDs (0, 0, 0)
  strip.show();
  delay(1000); // Keep the LEDs off for 1 second

  strip.fill(strip.Color(255, 255, 0), 0, NUM_LEDS); // RGB for green (0, 255, 0)
  strip.show();
  delay(1000); // Keep the LEDs on for 1 second

  // Turn off all LEDs using fill()
  strip.fill(strip.Color(0, 0, 0), 0, NUM_LEDS); // Turn off all LEDs (0, 0, 0)
  strip.show();
  delay(1000); // Keep the LEDs off for 1 second
}
