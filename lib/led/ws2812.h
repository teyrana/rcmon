// #include <stdio.h>
// #include <stdlib.h>

// #include "pico/stdlib.h"
#include "hardware/pio.h"
// #include "hardware/clocks.h"

#include "ws2812.pio.h"

pio_hw_t* ws2812_init();

void ws2812_put( pio_hw_t* target_pio, uint8_t red, uint8_t green, uint8_t blue);

