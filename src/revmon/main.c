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


    const uint rx_gpio = 6;   // choose which GPIO pin is connected to the IR detector
    PIO rx_pio = pio0;         // choose which PIO block to use (RP2040 has two: pio0 and pio1)

    // const uint tx_gpio = 14;      // choose which GPIO pin is connected to the IR LED
    // PIO  tx_pio = pio0;       // (sufficient state-machines are available)

    // configure and enable the state machines
    // int tx_sm = nec_tx_init( tx_pio, tx_gpio);         // uses two state machines, 16 instructions and one IRQ
    const int rx_sm = nec_rx_init( rx_pio, rx_gpio);         // uses one state machine and 9 instructions


    // transmit and receive frames
    uint8_t rx_address = 0x00;
    uint8_t rx_command = 0x00;

    bool led_state = true;

    //, rx_address, rx_data; // Not Implemented
    while (true) {

        // if (tx_sm == -1 || rx_sm == -1) {
        if( rx_sm == -1 ){
            printf("could not configure PIO state-machine!!\n");
            sleep_ms(5000);
            continue;
        }

        // display any frames in the receive FIFO
        while (!pio_sm_is_rx_fifo_empty(rx_pio, rx_sm)) {
            uint32_t rx_frame = pio_sm_get(rx_pio, rx_sm);

            if (nec_decode_frame(rx_frame, &rx_address, &rx_command)) {
                printf("\t:rx:ok: %02x // %02xh (%d)\n", rx_address, rx_command, rx_command );
            } else {
                printf("\t:rx:bad: %08x\n", rx_frame);
            }

            gpio_put(LED_PIN, 1);
            sleep_ms(120);
            gpio_put(LED_PIN, 0);
        }

        // sleep_ms(200);
        // gpio_put(LED_PIN, (int)led_state);
        // led_state = ! led_state;

        // tx_data += 1;
    }
}