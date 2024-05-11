// standard library includes
#include <stdlib.h>
#include <stdio.h>

// pico-c-sdk includes
#include "pico/stdlib.h"
#include "hardware/clocks.h"

// project includes
#include "led/monoled.h"
#include "led/ws2812.h"

// simple alias, for convenience
#define put_rgb_led ws2812_put

int main() {

    //set_sys_clock_48();
    stdio_init_all();

    // assign to hardware PIO #0
    PIO rgb_led_pio = pio0;
    ws2812_init(rgb_led_pio);
    mono_led_init();

    puts("Adafruit-Feather-RP2040 Blink Test");

    uint8_t cnt = 0;
    while(true){

        mono_led_on();
        for (cnt = 0; cnt < 0xff; cnt++){
            put_rgb_led(rgb_led_pio, cnt, 0xff - cnt, 0);
            sleep_ms(3);
        }
        mono_led_off();

        for (cnt = 0; cnt < 0xff; cnt++){
            put_rgb_led(rgb_led_pio, 0xff - cnt, 0, cnt);
            sleep_ms(3);
        }
        for (cnt = 0; cnt < 0xff; cnt++){
            put_rgb_led(rgb_led_pio, 0, cnt, 0xff - cnt);
            sleep_ms(3);
        }

    }
}
