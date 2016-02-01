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
 * Slave_A1B3.c
 *
 * Created: 1/31/2016 8:11:07 PM
 *  Author: Chip
 *
 * Demo code for Slave_A1B3 project.
 * Target: ATmega88A (by sure to set Project > Properties > Device to this AVR chip)
 * NOTE: Uncheck the CKDIV8 fuse to use an 8 MHz CPU clock.
 *
 * This code demonstrates a simple I2C Slave receiving a command and sending back data.
 *
 * The Commands from the Master are either:
 * SDA_W 55				- Prepare data to be read
 * SDA_R Data0 Data1	- Return 55 COUNT
 * NOTE: If a 0x55 is not the command byte, then 0 is returned instead of COUNT.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "twiSlave.h"

#define SLAVE_ADRS	0x40

int main(void)
{
	uint8_t data;
	uint8_t count;

	count = 0;

	twiSlaveInit( SLAVE_ADRS );		// Initialize TWI hardware for Slave operation.
	
	sei();							// Enable interrupts.
	
	twiSlaveEnable();				// Enable the TWI interface to receive data.
	
    while(1)
    {
		if( twiDataInReceiveBuffer() )
		{
			data = twiReceiveByte();

			// If the data is 0x55, then prepare count to be returned, else have 0 returned.
			if( data == 0x55)
			{
				twiTransmitByte( data );	// stuff command into TxBuf[]
				twiTransmitByte( count );	// stuff count into TxBuf[]
			}
			else
			{
				twiTransmitByte( data );	// stuff command into TxBuf[]
				twiTransmitByte( 0 );		// stuff 0 into TxBuf[]
			}
			// NOTE: The Master is expected to read both bytes before sending another command.
			
			++count;						// inc to track how many commands have been received.
		}
    }
}
