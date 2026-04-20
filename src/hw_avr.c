#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "../include/hw.h"

#define SWITCH_PIN     PD5
#define RED_LED_PIN    PB5
#define GREEN_LED_PIN  PB4
#define BLUE_LED_PIN   PB3

void hw_init(void)
{
    // LED pins as output
    DDRB |= (1 << RED_LED_PIN) | (1 << GREEN_LED_PIN) | (1 << BLUE_LED_PIN);
    PORTB &= ~((1 << RED_LED_PIN) | (1 << GREEN_LED_PIN) | (1 << BLUE_LED_PIN));

    // switch as input
    DDRD &= ~(1 << SWITCH_PIN);

    // enable pin change interrupt on PD5
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT21);
}

void hw_timer1_init(void)
{
    TCCR1A = 0;
    TCCR1B = 0;

    TCCR1B |= (1 << WGM12);

    TCCR1B |= (1 << CS12) | (1 << CS10);

    OCR1A = 7812;

    TIMSK1 |= (1 << OCIE1A);
}

bool hw_read_switch(void)
{
    return (PIND & (1 << SWITCH_PIN)) != 0;
}

void hw_write_leds(State s)
{
    if (s.red)   PORTB |=  (1 << RED_LED_PIN);
    else         PORTB &= ~(1 << RED_LED_PIN);

    if (s.green) PORTB |=  (1 << GREEN_LED_PIN);
    else         PORTB &= ~(1 << GREEN_LED_PIN);

    if (s.blue)  PORTB |=  (1 << BLUE_LED_PIN);
    else         PORTB &= ~(1 << BLUE_LED_PIN);
}

void hw_delay_ms(unsigned int ms)
{
    while (ms--) {
        _delay_ms(1);
    }
}