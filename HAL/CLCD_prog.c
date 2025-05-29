#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/ErrorType.h"


/* MCAL files inclusion */
#include "../MCAL/DIO_Interface.h"

/* CLCD files inclusion */
#include "CLCD_interface.h"
#include "CLCD_prv.h"
#include "CLCD_cfg.h"

#include "util/delay.h"


#if CLCD_u8BIT_MODE ==  FOUR_BIT

static void voidSetHalfDataPort (uint8 Copy_u8Data)
{
	DIO_u8SetPinValue(CLCD_u8Data_PORT , CLCD_u8D4_PIN , GET_BIT(Copy_u8Data,0));
	DIO_u8SetPinValue(CLCD_u8Data_PORT , CLCD_u8D5_PIN , GET_BIT(Copy_u8Data,1));
	DIO_u8SetPinValue(CLCD_u8Data_PORT , CLCD_u8D6_PIN , GET_BIT(Copy_u8Data,2));
	DIO_u8SetPinValue(CLCD_u8Data_PORT , CLCD_u8D7_PIN , GET_BIT(Copy_u8Data,3));
}

#endif


static void voidSendEnablePulse(void)
{
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_u8PINHIGH);
	_delay_ms(2); // Delay for the command to be processed
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_u8PINLOW);
}


void CLCD_VoidSendCmd(uint8 Copy_u8Cmd)
{

	/* Set RS pin to low for command */
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_u8PINLOW);

	/* Set RW pin to low for command */
#if CLCD_u8RW_CONN_STS == DIO_CONNECTED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_u8PINLOW);
#endif

#if CLCD_u8BIT_MODE ==  EIGHT_BIT
	/* Send the command */
	DIO_u8SetPortValue(CLCD_u8Data_PORT, Copy_u8Cmd);
	voidSendEnablePulse();

#elif CLCD_u8BIT_MODE ==  FOUR_BIT
	/* send the 4 most significant bits of the command first */
	voidSetHalfDataPort(Copy_u8Cmd >> 4 );
	voidSendEnablePulse();
	/*  4 least significant bits  by sending all command */
	voidSetHalfDataPort(Copy_u8Cmd);
	voidSendEnablePulse();

#else
#error wrong CLCD_u8BIT_MODE  configuration option
#endif


}


void CLCD_VoidSendData(uint8 Copy_u8Data)
{
	/* Set RS pin to high for data */
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_u8PINHIGH);

	/* Set RW pin to low for write operation */
#if CLCD_u8RW_CONN_STS == DIO_CONNECTED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_u8PINLOW);
#endif
#if CLCD_u8BIT_MODE ==  EIGHT_BIT
	/* Send the Data */
	DIO_u8SetPortValue(CLCD_u8Data_PORT, Copy_u8Data);
	voidSendEnablePulse();

#elif CLCD_u8BIT_MODE ==  FOUR_BIT
	/* send the 4 most significant bits of the Data first */
	voidSetHalfDataPort(Copy_u8Data >> 4 );
	voidSendEnablePulse();
	/*  4 least significant bits  by sending all Data */
	voidSetHalfDataPort(Copy_u8Data);
	voidSendEnablePulse();

#else
#error wrong CLCD_u8BIT_MODE  configuration option
#endif

}

void CLCD_VoidInit(void)
{
	/*Wait for m+ ore than 30ms after power on */
	_delay_ms(40);

	/* function set command : 2 lines  , font size: 5x7*/
#if CLCD_u8BIT_MODE ==  EIGHT_BIT
	CLCD_VoidSendCmd(0b00111000);

#elif CLCD_u8BIT_MODE ==  FOUR_BIT

	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b1000);
	voidSendEnablePulse();
#endif

	/* Display on off  control : Display on , cursor off , blink cursor off  */
	CLCD_VoidSendCmd(0b00001100);
	/* Clear  Display  */
	CLCD_VoidSendCmd(1);

}

uint8 CLCD_u8SendString(const char* Copy_pchString)
{
	// Check if the input string is not NULL.
	if (Copy_pchString != NULL)
	{
		uint8 Local_u8LoopIterator = 0;

		// Iterate through the string until the null-terminator is encountered.
		while (Copy_pchString[Local_u8LoopIterator] != '\0')
		{
			// Send each character of the string to the CLCD.
			CLCD_VoidSendData(Copy_pchString[Local_u8LoopIterator]);
			Local_u8LoopIterator++;
		}

	}
	else
	{
		// Handle the case where the input string is NULL.
		return NULL_PTR_ERR;
	}

	// Return OK to indicate successful string transmission.
	return OK;
}




void CLCD_VoidSendNumber(sint32 Copy_s32Number)
{
	uint8 Local_u8LastDigit = 0;
	uint32 Local_u32ReversedNumber = 0;
	sint8 Local_s8Counter = 0;

	if (Copy_s32Number < 0)
	{
		CLCD_VoidSendData('-');    // Display the negative sign.
		Copy_s32Number *= -1;      // Make the number positive for processing.
	}
	else if (Copy_s32Number == 0)  // Handle the special case of a zero.
	{
		CLCD_VoidSendData('0');
		return;  // Exit the function.
	}

	while (Copy_s32Number > 0)
	{
		Local_u8LastDigit =(uint8)((uint32) Copy_s32Number % 10); // Extract the last digit of the number.
		Local_u32ReversedNumber = (Local_u32ReversedNumber * 10) + Local_u8LastDigit; // Reverse the digits.
		Copy_s32Number /= 10; // Remove the last digit.
		Local_s8Counter++; // Increment the counter for the number of digits.
	}

	while (Local_s8Counter > 0)
	{
		Local_u8LastDigit = Local_u32ReversedNumber % 10; // Extract the last digit of the reversed number.
		CLCD_VoidSendData((Local_u8LastDigit + 48)); // Send the digit to a display function.
		Local_u32ReversedNumber /= 10; // Remove the last digit.
		Local_s8Counter--; // Decrement the counter.
	}
}

void CLCD_voidGoToXY(uint8 Copy_u8XPos , uint8 Copy_u8YPos)
{
	uint8 Local_u8Address ;

	if(Copy_u8YPos == 0u)
	{
		Local_u8Address	= Copy_u8XPos ;
	}
	else if (Copy_u8YPos == 1u)
	{
		Local_u8Address = 0x40 + Copy_u8XPos ;
	}
	// Local_u8Address = 0x40 * Copy_u8YPos + Copy_u8XPos    --- general form

	/* Set bit 7 for setDDRRAM address command */
	SET_BIT(Local_u8Address, 7); // fixed bit

	/*execute set DDRRAM address command  */
	CLCD_VoidSendCmd(Local_u8Address); //

}

uint8 CLCD_u8SendSpecialCharacter(uint8 Copy_u8LocationNnm , uint8* Copy_pu8Pattern, uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	uint8 Local_u8ErrorState = OK ;

	if (Copy_pu8Pattern != NULL )
	{
		uint8 Local_u8Counter;
		uint8 Local_u8CGRAMAddress = Copy_u8LocationNnm * 8 ;
		/*Set bit 6 for CGRAM address command */
		SET_BIT(Local_u8CGRAMAddress , 6u);

		/*Set CGRAM address */
		CLCD_VoidSendCmd(Local_u8CGRAMAddress);

		/* write the input pattern inside CGRAM */
		for(Local_u8Counter =0  ; Local_u8Counter < 8 ; Local_u8Counter++ )
		{
			CLCD_VoidSendData(Copy_pu8Pattern[Local_u8Counter]);
		}

		/* Go back to DDRM */
		CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);

		/*display the special pattern inside CGRAAM */
		CLCD_VoidSendData(Copy_u8LocationNnm);

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState  ;
}



