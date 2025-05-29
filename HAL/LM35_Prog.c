/*
 * LM35_Prog.c
 *
 *  Created on: Mar 20, 2025
 *      Author: moham
 */
#include "../LIB/STD_TYPES.h"
#include "../MCAL/ADC_Interface.h"
#include "LM35_Interface.h"


void LM35_voidInit(void)
{
	ADC_VoidInit();

}


//resolution is 10bits default
uint8 LM35_u8GetTemperatureValue(uint8 Copy_u8Channel )
{
	uint16 Local_u16DigitalReading ;
	uint16 Local_u16AnalogReading ;

	Local_u16DigitalReading = ADC_u8GetChannelReading(Copy_u8Channel);
	Local_u16AnalogReading = (uint16) ( (uint32)Local_u16DigitalReading * 5000UL / 1024UL); // Convert ADC reading to millivolts

	return (uint8) ( Local_u16AnalogReading / 10 ); // Convert millivolts to Celsius

}
