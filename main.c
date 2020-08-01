/*
 * Digital Temperature Sensor.c
 *
 * Created: 01/08/2020 10:25:47 ص
 * Author : ahmed
 */ 

#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD_ECU_driver.h"
#include "ADC_MCAL.h"
#include "Data_Type.h"
#include "Register.h"
#include "std_macros.h"
#define F_CPU 8000000UL


int main(void)
{
	OBJ x;
	LCD_vGet_Config(&x, EIGHT_BIT, HIGH_NIBBLE, 'D', 'B', 0, 'B', 1, 'B', 2);
	LCD_vInit();
	ADC_vInit();
	LCD_vSend_String("Temp=");
	u_int16 temp;
	while (1) {
		temp = (ADC_u16Read(ADC0) * 0.25);
		LCD_vMove_Cursor(1, 6);
		LCD_vSend_Number(temp);
	}
}

