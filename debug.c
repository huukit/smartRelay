#include "debug.h"

#include <avr/io.h>
#include <util/delay.h>

char __debugstrtmp__[__DEBUG_STR_TMPSIZE__];

void assertblinker(){
	while(1){
		_delay_ms(100);
		PORTB &= ~0b00000010;
		_delay_ms(100);
		PORTB |= 0b00000010;
	}
}