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
 * Slave_A2B2.c
 *
 * Created: 1/30/2016 6:36:11 PM
 *  Author: Chip
 *
 * Demo code for Slave_A2B2 project.
 * Target: ATtiny85 (by sure to set Project > Properties > Device to this AVR chip)
 * NOTE: Uncheck the CKDIV8 fuse to use an 8 MHz CPU clock.
 *
 * This code demonstrates a simple I2C Slave sending back data.
 *
 * The Commands from the Master are either:
 * SDA_R 		- read data
 * where SDA_R is the I2C address in Read Mode. [ i.e. (SLAVE_ADRS<<1)|1 ]
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "i2c_slave.h"

#define SLAVE_ADRS	0x40

int main(void) {
    uint8_t count;

    count = 0;

    i2cSlaveInit(SLAVE_ADRS);
    sei(); // Enable interrupts.


    while(1) {
        if( !i2cDataInTransmitBuffer() ) {
            i2cTransmitByte(count);	// stuff count into TxBuf[]
            ++count;						// inc for next value.
        }
    }
}
