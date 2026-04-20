/*
 * Build Notes
 * ----------
 * To build AVR firmware:
 *   ./build.sh
 * This:
 *   - compile main.c and logic.c using avr-gcc
 *   - generate main.elf and main.hex
 *
 * To run tests (host-side):
 *   ./build.sh test
 * This:
 *   - compile logic.c and test.c using gcc
 *   - run the test executable
 *
 * Assumptions / Tradeoffs
 * -----------------------
 * - A simple 20 ms delay after the interrupt is used for debouncing
 * - Timer1 is used for 500 ms blinking instead of a blocking delay
 */






// -----------------------------------------------------------------------------
// Candidate Assignment: AVR LED Mode Controller
// -----------------------------------------------------------------------------
// Objective
// Implement a small AVR C program that changes LED blinking behavior based on a
// switch input. Use the AVR GCC toolchain to build and Wokwi VSCode Extension
// to simulate the result.
//
// What is Wokwi?
// - Wokwi is a hardware simulator that lets you run embedded firmware without
//   a physical board.
// - Example: https://wokwi.com/projects/461302817329780737
// - In this assignment, you will compile your AVR program, then load the
//   generated .elf or .hex into Wokwi to verify LED behavior with the switch.
// - This means your submission can be validated consistently even without
//   real hardware.
//
// Target Platform
// - MCU: ATmega328P
// - Language: C
// - Toolchain: AVR GCC
// - Simulator: Wokwi VSCode Extension
//
// Functional Requirements
// 1. Switch input controls blinking mode.
// 2. If the switch is LEFT: blink RED LED every 500 ms.
// 3. If the switch is RIGHT: blink GREEN and BLUE LEDs every 500 ms.
// 4. Use an interrupt to detect switch changes and update the active mode.
//
// Note:
// 1. Reference build artifacts .elf and .hex are provided.
// 2. Complete main.c and simulate by editing wokwi.toml to point to your generated .elf or .hex file.
//
// Pin Mapping
// - Switch: pin 5
// - RED LED: pin 13
// - GREEN LED: pin 12
// - BLUE LED: pin 11
//
//
// Minimum Deliverables
// 1. Git repository with working implementation in this file.
//    - repo should include a README with build instructions and any notes.
//    - diagram.json should be included for Wokwi simulation.
//    - .elf or .hex file generated from your build process.
//    - source file used to build the .elf or .hex.
// 2. Behavior aligned with reference implementation according to requirements.
// 3. Build notes at the top of the file, including compiler flags and commands.
// 4. Testability support with test-build and release-build configurations.
// 5. Comments for any assumptions or tradeoffs.
//
// Build and Simulation (high level)
// 1. Build with AVR GCC and generate .elf or .hex.
// 2. Update wokwi.toml to point to your generated artifact.
// 3. Open the Wokwi diagram in VSCode and start the simulation.
// 4. Toggle the virtual switch and verify both required blinking modes.
//
// Evaluation Notes
// - The checklist above is a baseline.
// - You may add improvements or optimizations as long as core behavior remains
//   correct and requirements are met.
// - comment any assumptions and tradeoffs in your implementation
// - testability and maintainability will be considered in evaluation
//
// Helpful Resources
// - AVR GCC toolchain:
//   https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers
// - Wokwi VSCode getting started:
//   https://docs.wokwi.com/vscode/getting-started
// - ATmega328P quick reference:
//   https://github.com/amirbawab/AVR-cheat-sheet


#include <stdint.h>
#include <avr/interrupt.h>
#include "../include/app.h"
#include "../include/hw.h"

volatile uint8_t switch_changed = 1;
volatile uint8_t blink_tick = 0;

ISR(PCINT2_vect)
{
    switch_changed = 1;
}

ISR(TIMER1_COMPA_vect)
{
    blink_tick = 1;
}

int main(void)
{
    hw_init();
    hw_timer1_init();
    sei();

    app_init();

    while (1)
    {
        if (switch_changed) {
            app_on_switch_change();
            switch_changed = 0;
        }

        if (blink_tick) {
            blink_tick = 0;
            app_on_blink_tick();
        }
    }

    return 0;
}