/*
 * ADC_Reg.h
 *
 *  Created on: Jan 22, 2025
 *      Author: moham
 */

#ifndef ADC_REG_H_
#define ADC_REG_H_

#define  ADMUX  *((volatile uint8*)0x27)/*ADC Multiplexer Selection Register*/
#define  ADMUX_REFS1  7u                /*Reference Selection Bit 1*/
#define  ADMUX_REFS0  6u                /*Reference Selection Bit 0*/
#define  ADMUX_ADLAR  5u                /*Left Adjust Result*/
#define  ADCSRA   *((volatile uint8*)0x26)     /*ADC Control And Statue Register*/
#define ADCSRA_ADEN    7u                      /*ENABLE*/
#define ADCSRA_ADSC    6u                      /*Start Conversion*/
#define ADCSRA_ADATE   5u                      /*Auto Trigger Enable*/
#define ADCSRA_ADIF    4u                      /*Interrupt Flag*/
#define ADCSRA_ADIE    3u                      /*Interrupt Enable*/


#define ADCH   *((volatile uint8*)0x25)       /*ADC Data High Register*/
#define ADCL   *((volatile uint8*)0x24)       /*ADC Data Low Register*/

#define ADC    *((volatile uint16*)0x24)     /*ADC Data High & Low*/


#endif /* ADC_REG_H_ */
