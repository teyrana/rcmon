#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"

// #include "hardware/pio.h"
// #include "hardware/clocks.h"
// #include "ws2812.pio.h"

#include "receive.h"


const uint LED_PIN = PICO_DEFAULT_LED_PIN;


int main(){

    //set_sys_clock_48();
    stdio_init_all();

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


int main() {
    stdio_init_all();

    // use the led as an activity indicator
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    PIO pio = pio0;                                 // choose which PIO block to use (RP2040 has two: pio0 and pio1)
    uint tx_gpio = 14;                              // choose which GPIO pin is connected to the IR LED
    uint rx_gpio = 15;                              // choose which GPIO pin is connected to the IR detector

    // configure and enable the state machines
    int tx_sm = nec_tx_init(pio, tx_gpio);         // uses two state machines, 16 instructions and one IRQ
    int rx_sm = nec_rx_init(pio, rx_gpio);         // uses one state machine and 9 instructions

    if (tx_sm == -1 || rx_sm == -1) {
        printf("could not configure PIO\n");
        return -1;
    }

    // transmit and receive frames
    uint8_t tx_address = 0x00, tx_data = 0x00, rx_address, rx_data;
    while (true) {
        // create a 32-bit frame and add it to the transmit FIFO
        uint32_t tx_frame = nec_encode_frame(tx_address, tx_data);
        pio_sm_put(pio, tx_sm, tx_frame);
        printf("\nsent: %02x, %02x", tx_address, tx_data);

        // allow time for the frame to be transmitted (optional)
        sleep_ms(100);

        // display any frames in the receive FIFO
        while (!pio_sm_is_rx_fifo_empty(pio, rx_sm)) {
            uint32_t rx_frame = pio_sm_get(pio, rx_sm);

            if (nec_decode_frame(rx_frame, &rx_address, &rx_data)) {
                printf("\treceived: %02x, %02x", rx_address, rx_data);
            } else {
                printf("\treceived: %08x", rx_frame);
            }
        }

        sleep_ms(900);
        tx_data += 1;
    }
}