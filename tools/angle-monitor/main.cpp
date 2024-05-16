#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"

// #include "pico/binary_info.h"

// #include "hardware/pio.h"
// #include "hardware/clocks.h"

// project includes
#include "as5600/AS5600.h"
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

    printf(">>> Initializing lights...\n");


    // initialize activity led
    mono_led_init();
    mono_led_off();

    // Initialize status led:
    PIO status_pio = ws2812_init( pio0 );
    status_set_caution();

    printf(">>> Initializing encoder library...\n");
    uint8_t encoder_address = 0x36;

    AS5600 encoder;

    if( ! encoder.good() ){
        status_set_error();
    }

    printf(">>> Starting Main Loop... \n");

    while (true) {

        // const uint8_t conf = encoder.read_config();
        // const uint16_t raw_angle = encoder.read_raw_angle();
        const uint16_t scale_angle = encoder.read_scale_angle();

        const uint8_t status = encoder.read_status();

        // printf("    :Status:     %02X\n", status );
        const bool magnet_detected = (status >> 5) & 1;
        // printf("        :MD:     %d\n", magnet_detected );

        if( magnet_detected ){
            // printf("    :Conf:       %04X\n", conf );
            printf("    :MagLow:       %d\n", ((status>>4)&1) );
            printf("    :MagHigh:      %d\n", ((status>>3)&1) );
            printf("    :Scale Angle:  %d\n", scale_angle );
        }else{
            printf("Magnet missing!\n");
        }

        sleep_ms(2000);
        printf("----\n");

        // Clear terminal 
        // printf("\033[1;1H\033[2J");
    }
}