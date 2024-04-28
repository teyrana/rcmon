#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"

// #include "hardware/pio.h"
// #include "hardware/clocks.h"
// #include "ws2812.pio.h"

#include "receive.h"

const uint LED_PIN = PICO_DEFAULT_LED_PIN;

void init_activity_led(){
    // use the led as an activity indicator
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int main(){

    //set_sys_clock_48();
    stdio_init_all();

    init_activity_led();

    bool led_state = true;

    //, rx_address, rx_data; // Not Implemented
    while (true) {
        gpio_put(LED_PIN, 1);
        gpio_put(LED_PIN,(64, 0, 0));
        sleep_ms(500);
        
        pixels.fill((0, 64, 0));
        sleep_ms(500);

        pixels.fill((0, 0, 64));
        sleep_ms(500);

        gpio_put(LED_PIN, 0);
        sleep_ms(500);

    }
}