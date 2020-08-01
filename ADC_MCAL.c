/*
 * ADC_MCAL.c
 *
 * Created: 31/07/2020 04:01:35 م
 *  Author: ahmed
 */ 

#include "ADC_MCAL.h"

void ADC_vInit(){
	/*Configuration Vref (Vcc on AVCC with external capacitor at AVREF pin)*/
	SET_BIT(XADMUX, REFS0);
	SET_BIT(XADMUX, REFS1);
	/*Enable ADC*/
	SET_BIT(XADCSRA, ADEN);
	/*Adjust ADC Clock make the division factor 64 (8M/64 = 125KHz)*/
	SET_BIT(XADCSRA, ADPS2);
	SET_BIT(XADCSRA, ADPS1);
	CLR_BIT(XADCSRA, ADPS0);
}

u_int16 ADC_u16Read(u_int8 Channel){
	u_int16 read_value;
	
	Channel &= 0x07;
	XADMUX &= 0xE0;
	XADMUX |= Channel;
	SET_BIT(XADCSRA, ADSC);
	while(IS_BIT_CLEAR(XADCSRA, ADIF));
	SET_BIT(XADCSRA, ADIF);
	read_value = XADCL;
	read_value |= (XADCH<<8);
	
	return read_value;
}