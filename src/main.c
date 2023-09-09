#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"

// #include "hardware/pio.h"
// #include "hardware/clocks.h"
// #include "ws2812.pio.h"

// #include "led.h"

int main(){

    //set_sys_clock_48();
    stdio_init_all();

#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {

        gpio_put(LED_PIN, 1);
        sleep_ms(1000);
        gpio_put(LED_PIN, 0);
        sleep_ms(1000);

        // Print Out Debug
        printf("Hello, world!\n");

    }
#endif
}