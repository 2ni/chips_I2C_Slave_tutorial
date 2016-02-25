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
 */
 
/* Arduino A1C1 Demo */

/*
 * This demo code will blink LED-1 then Glow LED-2.
 */

#include <Wire.h>

/* *** LOCAL PROTOTYPES *** */
uint8_t makeHeader( uint8_t len );

#define  SLAVE_ADRS  0x40    // MUST match AVR chip I2C address

// Single LED control
#define   DEV_LED_ID    0x20
#define   DEV_LED_OFF   1
#define   DEV_LED_ON    2
#define   DEV_LED_LEN   3

// Single LED PWM glow
#define   DEV_LED_PWM_ID    0x30

#define   DEV_LED_PWM_OFF   1
#define   DEV_LED_PWM_ON    2
#define   DEV_LED_PWM_LEN   3

#define   DEV_LED_PWM_RATE      3
#define   DEV_LED_PWM_RATE_LEN  4


int slave = SLAVE_ADRS;      // has to be an int or a warning pops up.
int cmdLen;                  // number of bytes to send after the I2C SDA_W code.

uint8_t outBuff[4];
uint8_t count = 0;

void setup()
{
  Wire.begin();              // enable i2c bus support
}

void loop()
{
  int data_len;

  if( count == 0 )
  {
    // Turn on LED-2 Glow
    outBuff[0] = makeHeader( DEV_LED_PWM_LEN-3 );
    outBuff[1] = DEV_LED_PWM_ID;
    outBuff[2] = DEV_LED_PWM_ON;
    cmdLen = DEV_LED_PWM_LEN;

    Wire.beginTransmission(slave);      // identify the Slave to transmit to.
    Wire.write(outBuff, cmdLen);        // send out data.
    Wire.endTransmission();             // complete transmission.
  }

  // Send Command to Slave.
  if( count % 12 < 11 )
  {
    // Toggle LED-1 off/on
    outBuff[0] = makeHeader( DEV_LED_LEN-3 );
    outBuff[1] = DEV_LED_ID;
    if( count % 2 == 0 ) {
      outBuff[2] = DEV_LED_OFF;
    } else {
      outBuff[2] = DEV_LED_ON;
    }
    cmdLen = DEV_LED_LEN;
  }
  else
  {
    // LED-2 Glow Rate
    outBuff[0] = makeHeader( DEV_LED_PWM_RATE_LEN-3 );
    outBuff[1] = DEV_LED_PWM_ID;
    outBuff[2] = DEV_LED_PWM_RATE;

    if( outBuff[3] == 0x02 )
      outBuff[3] = 0x10;
    else
      outBuff[3] = 0x02;

    cmdLen = DEV_LED_PWM_RATE_LEN;
  }

  ++count;

  Wire.beginTransmission(slave);      // identify the Slave to transmit to. Have to do this each time.
  Wire.write(outBuff, cmdLen);        // send out data.
  Wire.endTransmission();             // complete transmission.

  delay(1000);                       // wait for 1 second.
}

/*
 * This is a simple utility to build the first byte of the
 * header by generating the one comp of the lower 4 bits.
 */
uint8_t makeHeader( uint8_t len )
{
  uint8_t temp;
 
  temp = ((~len) << 4) & 0xF0;    // shift and mask
  temp = temp | (len & 0x0F);
  return (temp);
}

