/*
 * TIMER_Reg.h
 *
 *  Created on: Feb 14, 2025
 *      Author: moham
 */

#ifndef TIMER_REG_H_
#define TIMER_REG_H_

/*----------------------------------------------------------------------------------------------------------*/

/*TIMER 0 Registers*/

#define TCCR0 *((volatile uint8*)0x53) /*Timer/Counter Control Register*/
#define TCCR0_CS00        0u   /* Clock Select*/
#define TCCR0_CS01        1u   /* Clock Select*/
#define TCCR0_CS02        2u   /* Clock Select*/
#define TCCR0_WGM01       3u   /*Waveform Generation Mode*/
#define TCCR0_COM00       4u   /*Compare Match Output Mode*/
#define TCCR0_COM01       5u   /*Compare Match Output Mode*/
#define TCCR0_WGM00       6u   /*Waveform Generation Mode*/
#define TCCR0_FOC0        7u   /*Force Output Compare*/
#define TIMSK *((volatile uint8*)0x59)/*Timer/Counter Interrupt Mask Register*/
#define TIMSK_TOIEO       0u  /*Timer/Counter0 Overflow Interrupt Enable*/
#define TIMSK_OCIE0       1u  /*Timer/Counter0 Output Compare Match Interrupt Enable*/
#define TIMSK_TOIE1       2u   /*Timer/Counter1 Overflow Interrupt Enable*/
#define TIMSK_OCIE1B      3u   /*Timer1 /Output Compare Register 1 B*/
#define TIMSK_OCIE1A      4u   /*Timer1 /Output Compare Register 1 A*/
#define TIMSK_TICIE1      5u   /*Timer1 Input Capture Interrupt Enable*/
#define TIMSK_TOIE2       6u   /*Timer/Counter2 Overflow Interrupt Enable*/
#define TIMSK_OCIE2       7u   /*Timer/Counter2 Output Compare Match Interrupt Enable*/
#define TCNT0 *((volatile uint8*)0x52)  /*Timer/Counter Register*/
#define OCR0  *((volatile uint8 *)0x5C) /*Timer/Counter0 Output Compare Register*/
#define TIFR  *((volatile uint8 *)0x58)/*Timer/Counter Interrupt Flag Register*/
#define TOV0              0u /*Timer/Counter0 Overflow Flag*/
#define OCF0              1u /*Output Compare Flag 0*/


/*----------------------------------------------------------------------------------------------------------*/

/*TIMER2 Registers*/
#define TCCR2 *((volatile uint8*)0x45)		/*Timer/Counter Control Register*/
#define TCCR2_CS20              0u			/* Clock Cycle*/
#define TCCR2_CS21				1u	        /* Clock Cycle*/
#define TCCR2_CS22				2u	        /* Clock Cycle*/
#define TCCR2_WGM21				3u	        /* Wave Generation*/
#define TCCR2_COM20				4u	        /* Compare Match Output Mode channel 20*/
#define TCCR2_COM21				5u	        /* Compare Match Output Mode channel 23*/
#define TCCR2_WGM20             6u          /* Wave Generation*/
#define TCCR2_FOC2              7u          /* Force Output Compare*/
#define TCNT2  *((volatile uint8*)0x44)      /* Timer2/Counter Register*/
#define OCR2   *((volatile uint8*)0x43)      /* Timer/Counter2 Output Compare Register*/


/*----------------------------------------------------------------------------------------------------------*/

/*TIMER1 Registers*/

#define TCCR1A *((volatile uint8*)0x4F)     /*Timer/Counter1 Control register A*/
#define TCCR1A_WGM10                         0u   /*Wave generation channel 10*/
#define TCCR1A_WGM11                         1u   /*Wave generation channel 11*/
#define TCCR1A_FOC1B                         2u   /*Force Output Compare for Channel A*/
#define TCCR1A_FOC1A                         3u   /*Force Output Compare for Channel B*/
#define TCCR1A_COM1B0                        4u   /* Compare Output Mode for Channel B0*/
#define TCCR1A_COM1B1                        5u   /* Compare Output Mode for Channel B1*/
#define TCCR1A_COM1A0                        6u   /* Compare Output Mode for Channel A0*/
#define TCCR1A_COM1A1                        7u   /* Compare Output Mode for Channel A1*/
#define TCCR1B *((volatile uint8*)0x4E)     /*Timer/Counter1 Control register B*/
#define TCCR1B_CS10                           0u   /*Clock Cycle Channel 10*/
#define TCCR1B_CS11                           1u   /*Clock Cycle Channel 11*/
#define TCCR1B_CS12                           2u   /*Clock Cycle Channel 12*/
#define TCCR1B_WGM12                          3u   /*Wave generation Channel 12*/
#define TCCR1B_WGM13                          4u   /*Wave generation Channel 13*/
#define TCCR1B_ICES1                          6u   /*Input Capture Edge Select*/
#define TCCR1B_ICNC1                          7u   /*Input Capture Noise Canceler*/

#define TCNT1H      *((volatile uint8*)0x4D)   /*Timer/Counter1 – Counter Register High Byte*/
#define TCNT1L      *((volatile uint8*)0x4C)   /*Timer/Counter1 – Counter Register Low Byte*/
#define TCNT1       *((volatile uint16*)0x4C)  /*Timer1 Register*/

#define OCR1AH      *((volatile uint8*)0x4B)   /*Timer/Counter1 – Output Compare Register A High Byte*/
#define OCR1AL      *((volatile uint8*)0x4A)   /*Timer/Counter1 – Output Compare Register A Low Byte*/
#define OCR1A		*((volatile uint16 *)0x4A) /*ChannelA Output Compare Match Register*/

#define OCR1BH      *((volatile uint8*)0x49)   /*Timer/Counter1 – Output Compare Register B High Byte*/
#define OCR1BL      *((volatile uint8*)0x48)   /*Timer/Counter1 – Output Compare Register B Low Byte*/
#define OCR1B		*((volatile uint16 *)0x48) /*ChannelB Output Compare Match Register*/

#define ICR1H       *((volatile uint8*)0x47)   /*Timer/Counter1 – Input Capture Register High Byte*/
#define ICR1L       *((volatile uint8*)0x46)   /*Timer/Counter1 – Input Capture Register Low Byte*/
#define ICR1		*((volatile uint16 *)0x46) /*Input capture register*/









#endif /* TIMER_REG_H_ */
