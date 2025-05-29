/*
 * GIE_Reg.h
 *
 *  Created on: Jan 11, 2025
 *      Author: moham
 */

#ifndef GIE_REG_H_
#define GIE_REG_H_


#define SREG *((volatile uint8*)0x5F)  /*Status Register*/
#define SREG_I   7u                    /*Global interrupt enable PIN*/



#endif /* GIE_REG_H_ */
