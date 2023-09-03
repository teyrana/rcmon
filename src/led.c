#include "led.h"


void put_rgb(uint8_t red, uint8_t green, uint8_t blue) {
    const uint32_t mask = (green << 16) | (red << 8) | (blue << 0);
    pio_sm_put_blocking(pio0, 0, mask << 8u);
}
