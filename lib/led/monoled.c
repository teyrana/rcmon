#include "monoled.h"

// automatically set by board-specific header, upstream?
static const uint LED_PIN = PICO_DEFAULT_LED_PIN;


void mono_led_init(){
// #IF PICO_BOARD == "adafruit_feather_rp2040”
    // static uint LED_PIN = PICO_DEFAULT_LED_PIN; // ???? // not tested
// #ELSE IF 
    // static uint LED_PIN = PICO_DEFAULT_LED_PIN;
// #ENDIF
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void mono_led_on(){
    gpio_put(LED_PIN,1);
}

void mono_led_off(){
    gpio_put(LED_PIN,0);
}
