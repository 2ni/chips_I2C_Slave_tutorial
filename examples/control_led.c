/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Nels D. "Chip" Pearson (aka CmdrZin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Slave_A2B1.c
 *
 * Created: 1/28/2016	0.01	ndp
 *  Author: Chip
 *
 * Demo code for Slave_A2B1 project.
 * Target: ATmega85 (by sure to set Project > Properties > Device to this AVR chip)
 * NOTE: Uncheck the CKDIV8 fuse to use an 8 MHz CPU clock.
 *
 * This code demonstrates a simple I2C Slave to control an LED.
 *
 * The Commands from the Master are either:
 * SDA_W 00		- turn the LED OFF
 * SDA_W 01		- turn the LED ON
 * where SDA_W is the I2C address in Write Mode. [ i.e. (SLAVE_ADRS<<1)|0 ]
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "i2c_slave.h"

#define SLAVE_ADRS	0x21

// LED hardware support
#define LED_DDR		DDRB			// Port direction bit. 0:Input 1:output
#define LED_PORT	PORTB			// Port being used.
#define LED_P		PB1				// Port bit being used.

int main(void) {
    uint8_t data;

    LED_DDR |= (1<<LED_P);			// Set LED pin as an output.

    i2cSlaveInit(SLAVE_ADRS);		// Initialize TWI hardware for Slave operation.
    sei();							// Enable interrupts.

    while(1) {
        if (i2cDataInReceiveBuffer()) {
            data = i2cReceiveByte();

			// If the data is 00, then turn OFF the LED. Turn it ON for any non-zero value.
            if( data == 0) {
                LED_PORT &= ~(1<<LED_P);		// Turn LED OFF.
            } else {
                LED_PORT |= (1<<LED_P);			// Turn LED ON.
            }
        }
    }
}
