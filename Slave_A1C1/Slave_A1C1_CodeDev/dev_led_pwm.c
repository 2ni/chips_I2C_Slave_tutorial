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
 * dev_led_1.c
 *
 * Created: 2/24/2016		0.01	ndp
 *  Author: Chip
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#include "sysTimer.h"
#include "access.h"

#include "dev_led_pwm.h"

#define DEMO_BOARD	0					// Use for testing. Set to 0 for proto-board set up.

bool	dlp_state;
int		dlp_rate;
int		dlp_rateAdjust;					// Controls how fast the glow cycles.

void dev_led_pwm_init()
{
	dlp_state = false;
	dlp_rate = 0;
	dlp_rateAdjust = 4;
	
	DEV_LED_PWM_DDR |= (1<<DEV_LED_PWM_P);			// set HIGH for output

#if DEMO_BOARD == 1
	// Extras for demo board use.
	DDRD |= (1<<PD1);					// use Port D B1 as output
	PORTD &= ~(1<<PD1);
#endif

	// Set up Timer 1
	TCCR1A |= (1<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(1<<WGM11)|(1<<WGM10);	// Use OC1A pin for PWM
	TCCR1B |= (0<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(1<<CS10);						// WGM = 0111 for 0x03FF as TOP..CPU div 1 = 0.050us
	OCR1A = 0x0200;			// 50%
	TIMSK1 |= (1<<TOIE1);					// OV bit intr

	return;
}

/*
 * Turn LED Glow OFF
 * CMD: F0 DEV 01
 */
void dev_led_pwm_off()
{
	DEV_LED_PWM_DDR &= ~(1<<DEV_LED_PWM_P);			// set LOW for input to turn off
	dlp_state = false;
	return;
}

/*
 * Turn LED Glow ON
 * CMD: F0 DEV 02
 */
void dev_led_pwm_on()
{
	DEV_LED_PWM_DDR |= (1<<DEV_LED_PWM_P);			// set HIGH for output to turn on
	dlp_state = true;
	return;
}

/*
 * Set glow rate
 * CMD: F0 DEV 03 RATE
 */
void dev_led_pwm_setRate()
{
	dlp_rateAdjust = getMsgData(3) & 0x03FF;				// Limit to max count of Timer1
}

/*
 * Called continuously.
 */
void dev_led_pwm_service()
{
	if( GPIOR0 & (1<<DEV_10MS_TIC) )
	{
		GPIOR0 &= ~(1<<DEV_10MS_TIC);

		dlp_rate += dlp_rateAdjust;
		if( dlp_rate > 0x03FF )
			dlp_rate = 0;		
	}
}

ISR( TIMER1_OVF_vect )
{
	OCR1A = dlp_rate;
}
