/*
 * USART_Prog.c
 *
 *  Created on: Mar 8, 2025
 *      Author: moham
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/ErrorType.h"
#include "USART_reg.h"
#include "USART_Cfg.h"
#include "USART_Prv.h"
#include "USART_interface.h"


void USART_Init(void)
{
	/*UCSRC configurations will  hold in this variable   to assigned with the bit selection in one operation */
	uint8 Local_u8UCSRC_Cfg = 0;
	uint16 Local_u16UBRR   = 0;

	/*Calculating & Setting the Baud Rate*/
	Local_u16UBRR = ((uint16)((SYSTEM_FREQUENCY / (16ul * USART_BAUD_RATE)) - 1));

	UBRRH = (uint8)(Local_u16UBRR >> 8);
	UBRRL = (uint8)(Local_u16UBRR);


	/*Setting the Transmission mode*/
#if USART_MODE == ASYNCHRONOUS
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UMSEL);
#elif USART_MODE == SYNCHRONOUS
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UMSEL);
#else
#error Wrong configuratoin of transmission mode
#endif


	/*Selecting the data size*/
#if	USART_CHAR_SIZE == FIVE_BITS
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ1);
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ0);

#elif USART_CHAR_SIZE == SIX_BITS
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ0);

#elif USART_CHAR_SIZE == SEVEN_BITS
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ1);
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ0);

#elif USART_CHAR_SIZE == EIGHT_BITS
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ0);
#elif USART_CHAR_SIZE == NINE_BITS
	SET_BIT(UCSRB, UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ0);
#else
#error Wrong configuratoin of the Charachter size.
#endif



	/*Setting the Parity mode*/
#if USART_PARITY_MODE == NO_PARITY
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM0);
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM1);
#elif USART_PARITY_MODE == EVEN_PARITY
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM0);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM1);
#elif USART_PARITY_MODE == ODD_PARITY
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM0);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM1);
#else
#error Wrong configuratoin of Parity mode.
#endif


	/*Setting the stop bit mode*/
#if USART_STOP_BIT_MODE == SINGLE_STOP_BIT
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_USBS);
#elif USART_STOP_BIT_MODE == TWO_STOP_BITS
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_USBS);
#else
#error Wrong configuratoin of STOP_BOT_MODE
#endif



	/*Setting the CLK Polarity*/
#if (USART_MODE == SYNCHRONOUS && USART_CLK_POLARITY == TXRISING_RXFALLING)
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UCPOL);
#elif (USART_MODE == SYNCHRONOUS && USART_PARITY_MODE == TXFALLING_RXRISING)
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCPOL);
#endif




	/*Writing the configurations in the UCSRC Register  and set the selection bit in one operation*/
	UCSRC = (1 << UCSRC_URSEL) | Local_u8UCSRC_Cfg;





	/* RX Complete Interrupt Configuration */
#if USART_RX_INTERRUPT_ENABLE == DISABLE
	CLR_BIT(UCSRB, UCSRB_RXCIE);    /* Disable RX Complete Interrupt */
#elif USART_RX_INTERRUPT_ENABLE == ENABLE
	SET_BIT(UCSRB, UCSRB_RXCIE);    /* Enable RX Complete Interrupt */
#else
#error "Wrong USART_RX_INTERRUPT_ENABLE configuration"
#endif

	/* TX Complete Interrupt Configuration */
#if USART_TX_COMPLETE_INTERRUPT == DISABLE
	CLR_BIT(UCSRB, UCSRB_TXCIE);    /* Disable TX Complete Interrupt */
#elif USART_TX_COMPLETE_INTERRUPT == ENABLE
	SET_BIT(UCSRB, UCSRB_TXCIE);    /* Enable TX Complete Interrupt */
#else
#error "Wrong USART_TX_COMPLETE_INTERRUPT configuration"
#endif

	/* Data Register Empty Interrupt Configuration */
#if USART_UDRE_INTERRUPT_ENABLE == DISABLE
	CLR_BIT(UCSRB, UCSRB_UDRIE);    /* Disable UDRE Interrupt */
#elif USART_UDRE_INTERRUPT_ENABLE == ENABLE
	SET_BIT(UCSRB, UCSRB_UDRIE);    /* Enable UDRE Interrupt */
#else
#error "Wrong USART_UDRE_INTERRUPT_ENABLE configuration"
#endif



	/*Adjusting the initial states of the Receiver & Transmitter*/
#if USART_RECEIVER_ENABLE ==  RX_ENABLED
	SET_BIT(UCSRB, UCSRB_RXEN);
#elif USART_RECEIVER_ENABLE == RX_DISABLED
	CLR_BIT(UCSRB, UCSRB_RXEN);
#else
#error Wrong configuratoin of RX_INIT_STATE
#endif

#if USART_TRANSMITTER_ENABLE ==  TX_ENABLED
	SET_BIT(UCSRB, UCSRB_TXEN);
#elif USART_TRANSMITTER_ENABLE == TX_DISABLED
	CLR_BIT(UCSRB, UCSRB_TXEN);
#else
#error Wrong configuratoin of TX_INIT_STATE
#endif



}


void USART_VoidSendByte(uint8 Copy_u8Data)
{
	/*To transmit the signal , UDRE Flag must set to one First in the UCSRA Register*/
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR = Copy_u8Data;
}


uint8 USART_u8RecieveByte(void)
{
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
}


void USART_voidReceiveString(uint8 *Copy_pchString)
{
	uint8 Local_u8Counter = 0;

	Copy_pchString[Local_u8Counter] = USART_u8RecieveByte();

	while(  Copy_pchString[Local_u8Counter] != '\0' &&
			Copy_pchString[Local_u8Counter] != '\r' &&
			Copy_pchString[Local_u8Counter] != '\n'  )
	{

		Local_u8Counter++;
		Copy_pchString[Local_u8Counter] = USART_u8RecieveByte();
	}

	Copy_pchString[Local_u8Counter] = USART_u8RecieveByte(); // to get the extra char from the app
	Copy_pchString[Local_u8Counter] = '\0' ;



}


uint8 USART_u8SendString(const char * Copy_pchString)
{
	uint8 Local_u8ErrorState = OK;
	uint8 Local_u8Counter = 0;

	if (Copy_pchString != NULL)
	{
		while(Copy_pchString[Local_u8Counter] != '\0')
		{
			USART_VoidSendByte(Copy_pchString[Local_u8Counter]);
			Local_u8Counter++;
		}
	}

	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}



