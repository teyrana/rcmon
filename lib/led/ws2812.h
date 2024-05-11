#pragma once

#include "hardware/pio.h"

#include "ws2812.pio.h"

pio_hw_t* ws2812_init( pio_hw_t* target );

void status_set_ok();

void status_set_caution();

void status_set_error();

// note: calling with a NULL pio pointer is undefined behavior 
void ws2812_put_rgb( uint8_t red, uint8_t green, uint8_t blue);
void ws2812_put_mask( uint32_t mask );
