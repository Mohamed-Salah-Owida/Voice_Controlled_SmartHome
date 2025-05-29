/*
 * GIE_Prog.c
 *
 *  Created on: Jan 11, 2025
 *      Author: moham
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "GIE_Reg.h"
#include "GIE_Interface.h"


void  GIE_voidEnableGlobal(void)
{
	/*SET_BIT(SREG,SREG_I);*/
	__asm volatile  ("SEI");   /*Inline assembly:SET I_BIT */

}

void  GIE_voidDisableGlobal(void)
{
	/*LR_BIT(SREG,SREG_I);*/
	__asm volatile("CLI");  /*Inline assembly: CLR I_BIT */
}

/*But it will take some time for operation (3 Clock cycle)*/
/*So we will use an assembly instructions delivered by kit (1 Clock cycle) By SEI for setbit and CLI for clrbit*/
/*Every tool differs from each other in assembly instructions so , we use gcc
GCC: --asm volatile("Assembly instructions") (--) is optional and (volatile) is optional , it means that you don' want compiler to
optimize your code*/

