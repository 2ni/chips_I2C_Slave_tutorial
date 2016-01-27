/* Arduino A1B1 Demo */

/* This demo code will cause the LED to blink ON and OFF at a 1 second rate. */

#include <Wire.h>

#define  SLAVE_ADRS  0x40    // MUST match AVR chip I2C address

int slave = SLAVE_ADRS;      // has to be an int or a warning pops up.
int cmdLen;                  // number of bytes to send after the I2C SDA_W code.

uint8_t outBuff[4];
uint8_t count;

void setup()
{
  Wire.begin();              // enable i2c bus support
}

void loop()
{
  // Send Command to Slave.
  outBuff[0] = count % 2;             // A 0x00 turns OFF the LED. A 0x01 turns it ON.
  cmdLen = 1;
  ++count;

  Wire.beginTransmission(slave);      // identify the Slave to transmit to. Have to do this each time.
  Wire.write(outBuff, cmdLen);        // send out data.
  Wire.endTransmission();             // complete transmission.

  delay(1000);                        // wait for 1 second.
}

