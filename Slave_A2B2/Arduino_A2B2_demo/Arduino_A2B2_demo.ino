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
 
/* Arduino A2B2 Demo */

/*
 * This demo code will read data from the Slave.
 * The Slave will return an incremented count each time.
 */

#include <Wire.h>

#define  SLAVE_ADRS  0x40    // MUST match AVR chip I2C address

int slave = SLAVE_ADRS;      // has to be an int or a warning pops up.

void setup()
{
  Wire.begin();              // enable i2c bus support
  Serial.begin(57600);       // Set BAUD rate
}

void loop()
{
  int data_len;

  // Issues a SLA_R request and triggers N reads before NACKing Slave.
  data_len = 1;
  Wire.requestFrom(slave, data_len);  // request N bytes from (int)slave

  while(!Wire.available());           // wait for first data byte.
  unsigned char d = Wire.read();      // receive a byte as character.
  Serial.print(d, HEX);
  Serial.print(" ");

  // Fluxh entire buffer of any other data
  while(Wire.available())            // in case slave sends more or less than requested. Good for testing.
  { 
    d = Wire.read();                 // receive a byte as character.
    Serial.print(d, HEX);
    Serial.print(" ");
  }
  Serial.println("");

  delay(1000);                       // wait for 1 second.
}

