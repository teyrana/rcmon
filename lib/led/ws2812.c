#include "ws2812.h"

pio_hw_t* ws2812_init(){
    PIO pio = pio0;
    int sm = 0;
    const uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, 16, 800000, true);
}

void ws2812_put( pio_hw_t* target_pio, uint8_t red, uint8_t green, uint8_t blue) {
    const uint32_t mask = (green << 16) | (red << 8) | (blue << 0);
    pio_sm_put_blocking( target_pio, 0, mask << 8u);
}

