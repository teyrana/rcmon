#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"

// #include "pico/binary_info.h"

// #include "hardware/pio.h"
// #include "hardware/clocks.h"

// project includes
// #include "as5600/AS5600.h"
#include "led/monoled.h"
#include "led/ws2812.h"


// void lis3dh_read_data(uint8_t reg, float *final_value, bool IsAccel) {
//     // Read two bytes of data and store in a 16 bit data structure
//     uint8_t lsb;
//     uint8_t msb;
//     uint16_t raw_accel;
//     i2c_write_blocking(i2c_default, ADDRESS, &reg, 1, true);
//     i2c_read_blocking(i2c_default, ADDRESS, &lsb, 1, false);

//     reg |= 0x01;
//     i2c_write_blocking(i2c_default, ADDRESS, &reg, 1, true);
//     i2c_read_blocking(i2c_default, ADDRESS, &msb, 1, false);

//     raw_accel = (msb << 8) | lsb;

//     // return ...;
// }

int main(){

    stdio_init_all();

    // Initialize status led:
    PIO status_pio = ws2812_init( pio0 );

    // initialize activity led
    mono_led_init();

    uint8_t encoder_address = 0x36;


    // AS5600 encoder;

    // setup.  No errors detected.
    status_set_caution();


    while (true) {

        // sleep_ms(200);
        // gpio_put(LED_PIN, (int)led_state);
        // led_state = ! led_state;


        sleep_ms(500);
        // Clear terminal 
        printf("\033[1;1H\033[2J");
    }
}