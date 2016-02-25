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
 * dev_led_pwm.h
 *
 * Created: 2/24/2016		0.01	ndp
 *  Author: Chip
 */ 


#ifndef DEV_LED_PWM_H_
#define DEV_LED_PWM_H_

// LED 1
#define DEV_LED_PWM_ID		0x30

#define DEV_LED_PWM_DDR			DDRB
#define DEV_LED_PWM_PORT		PORTB
#define DEV_LED_PWM_P			PD1

#define CMD_LED_PWM_OFF			1
#define CMD_LED_PWM_ON			2
#define CMD_LED_PWM_RATE		3


void dev_led_pwm_init();
void dev_led_pwm_off();
void dev_led_pwm_on();
void dev_led_pwm_setRate();

void dev_led_pwm_service();

#endif /* DEV_LED_PWM_H_ */