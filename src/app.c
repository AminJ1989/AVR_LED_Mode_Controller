#include "../include/app.h"
#include "../include/hw.h"
#include "../include/logic.h"
#include <stdbool.h>

static Mode active_mode;
static State led_state;
static uint8_t led_on;

void app_init(void)
{
    bool sw = hw_read_switch();
    active_mode = mode(sw);
    led_state = Led_state(active_mode);
    led_on = 0;
}

void app_on_switch_change(void)
{
    hw_delay_ms(20);
    bool sw = hw_read_switch();
    active_mode = mode(sw);
    led_state = Led_state(active_mode);
}

void app_on_blink_tick(void)
{
    if (led_on) {
        hw_write_leds(led_state);
    } else {
        hw_write_leds((State){false, false, false});
    }

    led_on ^= 1;
}