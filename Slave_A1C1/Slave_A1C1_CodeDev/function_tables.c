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
 * Slave API Project - EM 8x8 board
 *
 * org: 08/08/2015					0.01	ndp
 * author: Nels "Chip" Pearson
 * revision: 02/23/2016				0.02	ndp		A1C1 mods
 *
 * Dependent on:
 *	module function files
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "sysdefs.h"

// Device prototypes
#include "dev_led_1.h"
#include "dev_led_pwm.h"


/* *** Call Tables for INIT, SERVICE, and ACCESS *** */

/*
 * Used by intialize.c :: init_all()
 * Format:
 *  struct {
 *	  uint16_t	id;
 *	  void		(*function)();
 *	}
 */
const MOD_FUNCTION_ENTRY mod_init_table[] PROGMEM =
{
	{ DEV_LED_1_ID, dev_led_1_init },
	{ DEV_LED_PWM_ID, dev_led_pwm_init },
	{ 0, 0}
};

/*
 * Used by service.c :: service_all()
 */
const MOD_FUNCTION_ENTRY mod_service_table[] PROGMEM =
{
	// No LED service
	{ DEV_LED_PWM_ID, dev_led_pwm_service },
	{ 0, 0}
};

/*
 * Used by access.c :: access_all() for access functions specific to this device.
 * Returned by mod_access_table[] for access functions specific to this device.
 * NOTE: This array has to be before the access table.
 */
const MOD_FUNCTION_ENTRY dev_led_1_access[] PROGMEM =
{
	{ CMD_LED_OFF, dev_led_1_off },
	{ CMD_LED_ON, dev_led_1_on },
	{ 0, 0 }
};

/*
 * Used by access.c :: access_all() for access functions specific to this device.
 * Returned by mod_access_table[] for access functions specific to this device.
 * NOTE: This array has to be before the access table.
 */
const MOD_FUNCTION_ENTRY dev_led_pwm_access[] PROGMEM =
{
	{ CMD_LED_PWM_OFF, dev_led_pwm_off },
	{ CMD_LED_PWM_ON, dev_led_pwm_on },
	{ CMD_LED_PWM_RATE, dev_led_pwm_setRate },
	{ 0, 0 }
};

/*
 * Used by access.c :: access_all()
 */
const MOD_ACCESS_ENTRY mod_access_table[] PROGMEM =
{
	{ DEV_LED_1_ID, dev_led_1_access },			// table to all functions supported by dev_led_1.
	{ DEV_LED_PWM_ID, dev_led_pwm_access },		// table to all functions supported by dev_led_pwm.
	{ 0, 0 }
};
