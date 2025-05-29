/*
 * USART_Cfg.h
 *
 *  Created on: Mar 8, 2025
 *      Author: moham
 */

#ifndef USART_CFG_H_
#define USART_CFG_H_

/****************************************************/
/************* Baud Rate Selection ****************/
/****************************************************/
/*Enter the system clock ( Hz )*/
#define SYSTEM_FREQUENCY		        16000000ul

/*Enter the baud rate value*/
#define USART_BAUD_RATE			         9600ul


/*
 * USART Timeout Calculation:
 * --------------------------
 * For one byte transmission/reception:
 * 1. Number of bits per frame = 10 bits (1 start + 8 data + 1 stop)
 * 2. Time for one bit = 1/Baud_Rate seconds
 * 3. Time for complete byte = (Number of bits) * (1/Baud_Rate) (sec)
 * 4. Converting to microseconds: multiply by 1,000,000
 *
 * Final Equation: ((1000000 * 10) / BAUD_RATE) microseconds
 *
 * Example for 9600 baud:
 * ----------------------
 * Timeout = (1000000 * 10) / 9600 = 1041.67 microseconds
 *
 * Note: 'ul' suffix ensures the number is treated as unsigned long
 * to prevent overflow in calculations
 */
#define USART_BYTE_TIMEOUT              ((1000000ul * 10) / USART_BAUD_RATE)




/****************************************************/
/************* Configuration of  Mode Selection ******/
/****************************************************/
/*Set USART Mode Select
 * 		                       	1. ASYNCHRONOUS
 * 		                     	2. SYNCHRONOUS
 */
#define USART_MODE	            ASYNCHRONOUS




/****************************************************/
/******************* Configuration of the Frame ***************/
/****************************************************/

/*Select the Character size (Data size):
 * 									1- FIVE_BITS
 * 									2- SIX_BITS
 * 									3- SEVEN_BITS
 * 									4- EIGHT_BITS
 * 									5- NINE_BITS
 *
 **/
#define USART_CHAR_SIZE			EIGHT_BITS


/*
 * Select the Parity mode:
 * 								1- EVEN_PARITY
 * 								2- ODD_PARITY
 * 								3- NO_PARITY
 **/
#define USART_PARITY_MODE		NO_PARITY


/*Chose the Stop bit mode:
 * 							1- SINGLE_STOP_BIT
 * 							2- TWO_STOP_BITS
 **/
#define USART_STOP_BIT_MODE		SINGLE_STOP_BIT




/*Select the CLK polarity (only when SYNCH mode is selected):
 * 												1- TXRISING_RXFALLING
 * 												2- TXFALLING_RXRISING
 *
 **/
#define USART_CLK_POLARITY		TXRISING_RXFALLING




/*Set Transmitter Enable
 * 													1. TX_ENABLED
 * 													2. TX_DISABLED
 */
#define USART_TRANSMITTER_ENABLE		           TX_ENABLED


/*Set Receiver Enable
 * 													1. RX_ENABLED
 * 													2. RX_DISABLED
 */
#define USART_RECEIVER_ENABLE			            RX_ENABLED


/*********************************************************************
 *                  USART Interrupt Configurations                     *
 *********************************************************************/

/* USART Interrupt Control */
#define USART_RX_INTERRUPT_ENABLE       DISABLE     /* Receive Complete Interrupt */
#define USART_TX_INTERRUPT_ENABLE       DISABLE     /* Transmit Complete Interrupt */
#define USART_UDRE_INTERRUPT_ENABLE     DISABLE     /* Data Register Empty Interrupt */

/* Error Interrupts */
#define USART_FRAME_ERROR_INTERRUPT     DISABLE     /* Frame Error Interrupt */
#define USART_PARITY_ERROR_INTERRUPT    DISABLE     /* Parity Error Interrupt */
#define USART_OVERRUN_ERROR_INTERRUPT   DISABLE     /* Data Overrun Interrupt */

/* Interrupt Priority (if supported by MCU) */
#define USART_INTERRUPT_PRIORITY        0           /* 0 is highest priority */






#endif /* USART_CFG_H_ */
