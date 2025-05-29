#include "../LIB/STD_TYPES.h"
#include "../LIB/ErrorType.h"
#include "../LIB/BIT_MATH.h"


#include "../MCAL/DIO_Interface.h"
#include "LED_Interface.h"



uint8 LED_u8SetON(const LED_cfg_t* Copy_pstCfg)
{
	uint8 Local_u8ErrorState = OK ;

	if(Copy_pstCfg != NULL)
	{
		if(Copy_pstCfg -> ActivityType == ACTIVE_H)
		{
			DIO_u8SetPinValue(Copy_pstCfg -> PORT , Copy_pstCfg -> PIN ,DIO_u8PINHIGH);
		}
		else if(Copy_pstCfg -> ActivityType == ACTIVE_L)
		{
			DIO_u8SetPinValue(Copy_pstCfg -> PORT , Copy_pstCfg -> PIN ,DIO_u8PINLOW);
		}
		else
		{
			Local_u8ErrorState = NOK ;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR ;
	}



	return Local_u8ErrorState ;

}



uint8 LED_u8SetOFF(const LED_cfg_t* Copy_pstCfg)
{
	uint8 Local_u8ErrorState = OK ;

	if(Copy_pstCfg != NULL)
	{
		if(Copy_pstCfg -> ActivityType == ACTIVE_H)
		{
			DIO_u8SetPinValue(Copy_pstCfg -> PORT , Copy_pstCfg -> PIN ,DIO_u8PINLOW);
		}
		else if(Copy_pstCfg -> ActivityType == ACTIVE_L)
		{
			DIO_u8SetPinValue(Copy_pstCfg -> PORT , Copy_pstCfg -> PIN ,DIO_u8PINHIGH);
		}
		else
		{
			Local_u8ErrorState = NOK ;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR ;
	}



	return Local_u8ErrorState ;

}
uint8 LED_u8Toggle(const LED_cfg_t* Copy_pstCfg)
{
	uint8 Local_u8ErrorState = OK ;

	if(Copy_pstCfg != NULL)
	{
		DIO_u8TogglePinValue(Copy_pstCfg -> PORT , Copy_pstCfg -> PIN);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR ;
	}

	return Local_u8ErrorState ;


}
