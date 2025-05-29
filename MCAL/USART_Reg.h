/*
 * USART_Reg.h
 *
 *  Created on: Mar 8, 2025
 *      Author: moham
 */

#ifndef USART_REG_H_
#define USART_REG_H_

// USART Control and Status Register A (UCSRA)
#define UCSRA                      *((volatile uint8*)0x2B) // Base address of UCSRA register
#define UCSRA_MPCM                  0u  // Multi-processor Communication Mode
#define UCSRA_U2X                   1u  // Double the USART Transmission Speed
#define UCSRA_PE                    2u  // Parity Error
#define UCSRA_DOR                   3u  // Data OverRun
#define UCSRA_FE                    4u  // Frame Error
#define UCSRA_UDRE                  5u  // USART Data Register Empty
#define UCSRA_TXC                   6u  // Transmit Complete
#define UCSRA_RXC                   7u  // Receive Complete

// USART Control and Status Register B (UCSRB)
#define UCSRB                      *((volatile uint8*)0x2A) // Base address of UCSRB register
#define UCSRB_TXB8                  0u  // Transmit Data Bit 8
#define UCSRB_RXB8                  1u  // Receive Data Bit 8
#define UCSRB_UCSZ2                 2u  // Character Size Bit 2
#define UCSRB_TXEN                  3u  // Transmitter Enable
#define UCSRB_RXEN                  4u  // Receiver Enable
#define UCSRB_UDRIE                 5u  // USART Data Register Empty Interrupt Enable
#define UCSRB_TXCIE                 6u  // TX Complete Interrupt Enable
#define UCSRB_RXCIE                 7u  // RX Complete Interrupt Enable

// USART Control and Status Register C (UCSRC)
#define UCSRC                      *((volatile uint8*)0x40) // Base address of UCSRC register
#define UCSRC_UCPOL                  0u  // Clock Polarity
#define UCSRC_UCSZ0                  1u  // Character Size Bit 0
#define UCSRC_UCSZ1                  2u  // Character Size Bit 1
#define UCSRC_USBS                   3u  // Stop Bit Selection
#define UCSRC_UPM0                   4u  // Parity Mode Bit 0
#define UCSRC_UPM1                   5u  // Parity Mode Bit 1
#define UCSRC_UMSEL                  6u  // USART Mode Select
#define UCSRC_URSEL                  7u  // Register Select (should be set to 1 when writing to UCSRC)

// USART Baud Rate Registers
#define UBRRL                      *((volatile uint8*)0x29) // USART Baud Rate Register Low Byte
#define UBRRH                      *((volatile uint8*)0x40) // USART Baud Rate Register High Byte

// USART Data Register
#define UDR                         *((volatile uint8*)0x2C) // USART Data Register for transmitting/receiving data

#endif /* USART_REG_H_ */
