#include "ws2812.h"

static pio_hw_t* target_pio = NULL;

pio_hw_t* ws2812_init( pio_hw_t* target ){
    target_pio = target;
    int sm = 0; // not sure what this means
    const uint offset = pio_add_program( target_pio, &ws2812_program);
    ws2812_program_init( target_pio, sm, offset, 16, 800000, true);
    return target_pio;
}

void status_set_ok(){
    ws2812_put_mask( 0x008100 << 8u );
}

void status_set_caution(){
    ws2812_put_mask( 0x816100 << 8u );
}

void status_set_error(){
    ws2812_put_mask( 0x810000 << 8u );
}

void ws2812_put_rgb( uint8_t red, uint8_t green, uint8_t blue) {
    const uint32_t mask = (green << 16) | (red << 8) | (blue << 0);
    pio_sm_put_blocking( target_pio, 0, mask << 8u);
}

void ws2812_put_mask( uint32_t mask ) {
    pio_sm_put_blocking( target_pio, 0, mask );
}

