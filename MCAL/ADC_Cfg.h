/*
 * ADC_Cfg.h
 *
 *  Created on: Jan 22, 2025
 *      Author: moham
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/*Reference_Selection_bits , Options:   1) AREF_Internal_Vref_Turned_Off
 *                                      2) AVCC_With_External_Capacitor_On_AREF
 *                                      3) Reserved
 *                                      4) Internal_Voltage*/

#define ADC_u8ReferenceVoltage   AVCC_With_External_Capacitor_On_AREF


/*Resolution_Bits   , Options          1)  EIGHT_BITS
 *                                     2)  TEN_BITS */
#define   ADC_u8Resolution       TEN_BITS


/*Auto Trigger Mode, Options :    1)ENABLED
 *                                2)DISABLED*/

#define Auto_Trigger      DISABLED

/*Interrupt , Options : 1) ENABLED
 *                      2) DISABLED*/

#define ADC_Interrupt         DISABLED

/*Configure the Prescaler division Factor   , Options : 1) Division_By_2
 *                                                      2) Division_By_4
 *                                                      3) Division_By_8
 *                                                      4) Division_By_16
 *                                                      5) Division_By_32
 *                                                      6) Division_By_64
 *                                                      7) Division_By_128         */

#define ADC_u8Prescaler_Division_Factor            Division_By_128




#endif /* ADC_CFG_H_ */
