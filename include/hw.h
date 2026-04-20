#ifndef HW_H
#define HW_H

#include <stdbool.h>
#include "logic.h"

bool hw_read_switch(void);
void hw_write_leds(State s);
void hw_delay_ms(unsigned int ms);
void hw_init(void);
void hw_timer1_init(void);

#endif