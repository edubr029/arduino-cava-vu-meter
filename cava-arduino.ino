#include <Adafruit_NeoPixel.h>

#define NUM_STRIPS 1            // Number of neopixel strips
#define NUM_PIXELS 60           // Number of neopixels per strip
#define BRIGHTNESS_LEVEL 5      // Brightness level for the neopixels

// Define the visualizer modes
#define MODE_SINGLE_DOT 0
#define MODE_FULL_STRIP 1
#define MODE_DECAY 2

const int visualizer_mode = MODE_DECAY;  // Change this to switch between modes

// Define the color modes
#define COLOR_MODE_PURPLE 0
#define COLOR_MODE_RGY 1

const int color_mode = COLOR_MODE_PURPLE;  // Change this to switch between color modes

// Define the pins for the neopixels
const int stripPin[NUM_STRIPS] = {3};

Adafruit_NeoPixel strips[NUM_STRIPS]; // Neopixel strips

// Extract the red, green, and blue components from a 32-bit color
uint8_t red(uint32_t color) {
    return (color >> 16) & 0xFF;
}

uint8_t green(uint32_t color) {
    return (color >> 8) & 0xFF;
}

uint8_t blue(uint32_t color) {
    return color & 0xFF;
}

void setup() {
    for(int i = 0; i < NUM_STRIPS; i++) {
        // Initialize neopixels
        strips[i] = Adafruit_NeoPixel(NUM_PIXELS, stripPin[i], NEO_GRB + NEO_KHZ800);
        strips[i].setBrightness(BRIGHTNESS_LEVEL);
        strips[i].begin();
    }
    Serial.begin(1000000);
    Serial.setTimeout(2000);
}

void loop() {
    visualizer();
}

void visualizer() {
    char pixel_value[NUM_PIXELS*4];
    char* phc;

    if(Serial.available() > 0) {
        Serial.readBytesUntil('\n', pixel_value, NUM_PIXELS*4);
        phc = strtok(pixel_value, ";");
        
        for(int i = 0; i < NUM_STRIPS; i++) {
            strips[i].clear();
        }

        while(phc != NULL) {
            int pixel = atoi(phc);
            for(int i = 0; i < NUM_STRIPS; i++) {
                uint32_t color;
                if(color_mode == COLOR_MODE_PURPLE) {
                    color = strips[i].Color(221, 160, 221); // Purple
                } else if(color_mode == COLOR_MODE_RGY) {
                    color = strips[i].Color(255, 0, 0); // Red
                    if(pixel > NUM_PIXELS / 3) color = strips[i].Color(0, 255, 0); // Green
                    if(pixel > 2 * NUM_PIXELS / 3) color = strips[i].Color(255, 255, 0); // Yellow
                }

                if(visualizer_mode == MODE_SINGLE_DOT) {
                    strips[i].setPixelColor(pixel, color);
                } else if(visualizer_mode == MODE_FULL_STRIP || visualizer_mode == MODE_DECAY) {
                    for(int j = 0; j <= pixel; j++) {
                        // Calculate decay factor (1 at peak, 0 at base)
                        float decay = visualizer_mode == MODE_DECAY ? (float)(pixel - j) / pixel : 1;
                        // Apply decay factor to color
                        uint8_t r = (uint8_t)(red(color) * decay);
                        uint8_t g = (uint8_t)(green(color) * decay);
                        uint8_t b = (uint8_t)(blue(color) * decay);
                        strips[i].setPixelColor(j, strips[i].Color(r, g, b));
                    }
                }
            }
            phc = strtok(NULL, ";");
        }

        for(int i = 0; i < NUM_STRIPS; i++)
            strips[i].show();
    }
}