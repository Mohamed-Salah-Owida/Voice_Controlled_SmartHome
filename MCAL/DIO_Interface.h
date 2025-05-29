#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

/* Port Definitions */
#define DIO_u8PORTA  0u
#define DIO_u8PORTB  1u
#define DIO_u8PORTC  2u
#define DIO_u8PORTD  3u

/* Pin Definitions */
#define DIO_u8PIN0  0u
#define DIO_u8PIN1  1u
#define DIO_u8PIN2  2u
#define DIO_u8PIN3  3u
#define DIO_u8PIN4  4u
#define DIO_u8PIN5  5u
#define DIO_u8PIN6  6u
#define DIO_u8PIN7  7u

/* Pin Direction Definitions */
#define DIO_u8PIN_INPUT  0u
#define DIO_u8PIN_OUTPUT 1u

/* Port Direction Definitions */
#define DIO_u8PORT_INPUT  0u
#define DIO_u8PORT_OUTPUT 0xffu

/* Port value */
#define DIO_u8PORTLOW  0u
#define DIO_u8PORTHIGH 0xffu

/* pin value */
#define DIO_u8PINLOW  0u   // Macro to represent a logic LOW value .
#define DIO_u8PINHIGH 1u  // Macro to represent a logic HIGH value .


/*Pin access */
uint8 DIO_u8SetPinDirection(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Direction );
uint8 DIO_u8SetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Value ); 
uint8 DIO_u8ReadPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8* Copy_Pu8Value);  
uint8 DIO_u8TogglePinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin); 

/*Port access */
uint8 DIO_u8SetPortDirection(uint8 Copy_u8Port, uint8 Copy_u8Direction); 
uint8 DIO_u8SetPortValue(uint8 Copy_u8Port, uint8 Copy_u8Value );     






#endif
