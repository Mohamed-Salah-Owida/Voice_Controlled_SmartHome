#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_

/*
 * Macros defining the minimum and maximum ADC values
 * obtained from the voltage divider circuit of the LDR.
 * Adjust these values based on the actual sensor readings.
 */
#define Min_val  105
#define Max_val  400




void LDR_voidInit(void);
uint16 LDR_u8GetReading(uint8 Copy_u8Channel );


#endif /* LDR_INTERFACE_H_ */
