/*
 * <copyright>
 * Copyright (c) 2016: Tuomas Huuki / Miikka Tammi tut.fi
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the (Lesser) GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * </copyright>
 */

/* $Id$ */

/*! \file
 * Proximia debug header. (license: GPLv2 or LGPLv2.1)
 * \author Tuomas Huuki tuomas.huuki@proximia.fi
 * \copyright 2017 Tuomas Huuki / proximia.fi
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "debug.h"
#include "softuart.h"
#include "adc.h"

#define SWVERMAJ 0
#define SWVERMIN 0
#define SWVERBUILD 1

#define LEDPIN 1

int main(void)
{
    // Init UART
	softuart_init();
	softuart_turn_rx_off();
	sei();
		
	// Init adc.
	adc_init();
	
	OUTPUT("%u.%u.%u\n\r", SWVERMAJ, SWVERMIN, SWVERBUILD);
	
	// Main loop.
	int32_t current = 0;
	uint16_t voltage = 0;
	int8_t chipTemp = 0;
	
	// Init leds
	DDRB |= _BV(LEDPIN);
	
    while (1){
		current = adc_getCurrentmA();
		voltage = adc_getVoltagemV();
		chipTemp = adc_getChipTemp();
		
		OUTPUT("%6.0ldmA %5.0umV %2.0dC\n\r", current, voltage, chipTemp);
		
		if(current > 10)
			PORTB |= _BV(LEDPIN);	
		else
			PORTB &= ~_BV(LEDPIN);	
			
		_delay_ms(50); 
    }
}

