/*
 * USART_Prv.h
 *
 *  Created on: Mar 8, 2025
 *      Author: moham
 */

#ifndef USART_PRV_H_
#define USART_PRV_H_


#define   ASYNCHRONOUS       1u
#define   SYNCHRONOUS        2u


#define    FIVE_BITS         1u
#define    SIX_BITS          2u
#define    SEVEN_BITS        3u
#define    EIGHT_BITS        4u
#define    NINE_BITS         5u

#define   EVEN_PARITY        1u
#define   ODD_PARITY         2u
#define   NO_PARITY          3u


#define  SINGLE_STOP_BIT    1u
#define  TWO_STOP_BITS      2u

#define  TXRISING_RXFALLING  1u


#define  TX_ENABLED          1u
#define  TX_DISABLED         2u

#define  RX_ENABLED          1u
#define  RX_DISABLED         2u


/* Interrupt Enable/Disable Options */
#define DISABLE                 0
#define ENABLE                  1


#define USART_IDLE								0
#define USART_BUSY								1



#endif /* USART_PRV_H_ */
