/*
 * LM35_Prog.c
 *
 *  Created on: Mar 20, 2025
 *      Author: moham
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/MAP.h"
#include "../MCAL/ADC_Interface.h"
#include "LDR_Interface.h"
void LDR_voidInit(void)
{
	ADC_VoidInit();

}


/*
 * Function: LDR_u8GetReading
 * ----------------------------
 * Reads the ADC value from the specified channel, maps it to the 0-1024 range,
 * and converts it into brightness levels (1 to 8).
 *
 * Copy_u8Channel: The ADC channel number where the LDR is connected.
 *
 * Returns: A brightness level from 1 to 8 based on the mapped ADC value.
 *
 */uint16 LDR_u8GetReading(uint8 Copy_u8Channel )
 {
	 uint16 Local_u16DigitalReading ;
	 uint8  Local_u8Level;

	 Local_u16DigitalReading = ADC_u8GetChannelReading(Copy_u8Channel);



	 // Map the LDR value from its real-world range (Min_val to Max_val) to ADC range (0-1024)
	 Local_u16DigitalReading = Map(Local_u16DigitalReading, Min_val, Max_val, 0, 1024);

	 // Define ADC thresholds for levels 1 to 8 (assuming 10-bit ADC range 0-1023)
	 if (Local_u16DigitalReading < 128)
		 Local_u8Level = 8;
	 else if (Local_u16DigitalReading < 256)
		 Local_u8Level = 7;
	 else if (Local_u16DigitalReading < 384)
		 Local_u8Level = 6;
	 else if (Local_u16DigitalReading < 512)
		 Local_u8Level = 5;
	 else if (Local_u16DigitalReading < 640)
		 Local_u8Level = 4;
	 else if (Local_u16DigitalReading < 768)
		 Local_u8Level = 3;
	 else if (Local_u16DigitalReading < 896)
		 Local_u8Level = 2;
	 else
		 Local_u8Level = 1;


	 return Local_u8Level;

 }
