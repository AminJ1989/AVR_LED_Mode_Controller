# AVR LED Mode Controller

## Overview

This project implements a LED controller on the ATmega328P.
A switch input changes the LED blinking mode.

* Switch LEFT → Red LED blinks
* Switch RIGHT → Green + Blue LEDs blink 

Logic is separated from hardware so the core behavior can be tested on a host machine.
---


## Build Instructions

### 1. Build firmware 

```bash
./build.sh
```

This will:

* compile `main.c` and `logic.c` using avr-gcc
* generate:

  * `main.elf`
  * `main.hex`

(see build script: )

---

### 2. Run tests 

```bash
./build.sh test
```

This will:

* compile `logic.c` with `test.c`
* run unit tests

Expected output:

```
All tests passed
```
---

## Pin Mapping

| Component | MCU Pin |
| --------- | ------- |
| Switch    | PD5     |
| Red LED   | PB5     |
| Green LED | PB4     |
| Blue LED  | PB3     |

---

## Design Notes

* Logic is implemented in `logic.c` and is independent of hardware 
* Hardware interaction (GPIO, interrupts, delays) is handled in `main.c` 
---

## Assumptions / Tradeoffs

* Debouncing is implemented using a blocking delay for simplicity
* LED blinking also uses timer based delays (500 ms)
---

