# Arduino CAVA VU Meter

VU Meter for Arduino using CAVA (Console-based Audio Visualizer for Alsa) and NeoPixel LED strip.

## Requirements

> [!NOTE]
> This project is desenvolved and tested on a **Linux based** system. It may not work on other systems.

- Arduino (or compatible board)
- NeoPixel LED strip (WS2812B or similar)
- Adafruit NeoPixel [library][adaifruit-neopixel]
- Linux based system (for the `cava_out.sh` script)
- [CAVA][cava] (Console-based Audio Visualizer for Alsa)

## Configuration

### Arduino

Change the Arduino Neopixel LED strip pin in the `cava-vu-meter.ino` file.

```cpp
// Define the pins for the neopixels
const int stripPin[NUM_STRIPS] = {3, 5, 6};
```

Change the number of LEDs, brightness level and number of strips in the `cava-vu-meter.ino` file.

```cpp
#define NUM_STRIPS 1            // Number of neopixel strips
#define NUM_PIXELS 60           // Number of neopixels per strip
#define BRIGHTNESS_LEVEL 5      // Brightness level for the neopixels
```

Change the mode of the VU Meter in the `cava-vu-meter.ino` file.

```cpp
// Define the visualizer modes
#define MODE_SINGLE_DOT 0
#define MODE_FULL_STRIP 1
#define MODE_DECAY      2
```

VU Meter color mode in the `cava-vu-meter.ino` file.

```cpp
// Define the color modes
#define COLOR_MODE_PURPLE 0
#define COLOR_MODE_RGY    1
```

### CAVA

Strip quantity and LED quantity in the `config` file.

```sh
[general]
# Strip quantity
bars = 1

[output]
# LED quantity
ascii_max_range = 60
```

> [!IMPORTANT]
> If the serial port is different from */dev/ttyUSB0*, you can change it to another one in the `cava_out.sh` file.


## Credits

Special thanks to [Sahaj Sarup][ric96] for [MatrixVizCava][matrixvizcava] project inspiration and the `cava_out.sh` script.

<!-- Links Variables -->
[adaifruit-neopixel]: https://github.com/adafruit/Adafruit_NeoPixel (Adafruit NeoPixel Library)
[cava]: https://github.com/karlstav/cava (CAVA)
[ric96]: https://gitlab.com/ric96 (Sahaj Sarup)
[matrixvizcava]: https://gitlab.com/ric96/matrixvizcava (MatrixVizCava)
