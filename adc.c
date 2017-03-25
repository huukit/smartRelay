#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#define SAMPLES 128
#define MAVGSAMPLES 32

int16_t sampleQueue[MAVGSAMPLES];
uint8_t samplePos;

void adc_init(void){
	// Internal 1.1 ref
	ADMUX = _BV(REFS1);
	// Enable ADC, highest clock divisor.
	ADCSRA = _BV(ADEN) | /*_BV(ADPS0) |*/ _BV(ADPS1) | _BV(ADPS2);
	// Disable digital buffers on AI pins.
	DIDR0 = _BV(ADC1D) | _BV(ADC2D) | _BV(ADC3D);
	
	samplePos = 0;
}

uint16_t getResult(){
	// Start conversion.
	ADCSRA |= _BV(ADSC);
	
	// Wait for conversion.
	while(ADCSRA & _BV(ADSC)){
		;
	}
	
	uint16_t result = 0;
	result = ADCL;
	result |= ADCH << 8;
	return result;
}

int32_t adc_getCurrentmA(void){
	uint16_t tempres = 0;
	int16_t result = 0;
	int16_t offset = 0;
	int32_t averageSum = 0;
	
	// Select bipolar mode.
	ADCSRB = _BV(BIN);
	
	ADMUX = _BV(REFS1) | _BV(REFS2) |  _BV(MUX2) | _BV(MUX0);
	_delay_ms(2);
			// Get channel offset:
		
	tempres = getResult();
		
	// If result is negative.
	if(tempres & 0x0200)
		offset = 0xFE00 | tempres;
	else{
		offset = tempres;
	}
		
	offset /= 2;
			
	for(int i = 0; i < SAMPLES; i++){
		// Get measurement.
		ADMUX = _BV(REFS1) | _BV(REFS2) | _BV(MUX0) | _BV(MUX1) | _BV(MUX2);

		tempres = getResult();

		// If result is negative.
		if(tempres & 0x0200)
			result = 0xFE00 | tempres;
		else{
			result = tempres;
		}		
		averageSum += (result - offset);
	}
	// Exit bipolar mode.
	ADCSRB = 0;
	
	// Filter
	sampleQueue[samplePos++] = averageSum / SAMPLES;
	if(samplePos == MAVGSAMPLES)samplePos = 0;
	
	averageSum = 0;
	
	// Filter result
	for(int i = 0; i < MAVGSAMPLES; i++){
		averageSum += sampleQueue[i];
	}

	return averageSum / MAVGSAMPLES * 166;
	
}

uint16_t adc_getVoltagemV(void){
	// Select ADC channel 1 (PB2)
	ADMUX = (_BV(MUX0));
	// Need to wait for ref to stablize.
	_delay_ms(2);
	uint16_t result = getResult() * (5000/1024);
	return result;
}

int8_t adc_getChipTemp(){
	// Select internal 1.1vref and chip temp;
	ADMUX = _BV(REFS1) | _BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3);
	// Need to wait for ref to stablize.
	_delay_ms(2);
	uint16_t result = getResult();
	return result;
}
