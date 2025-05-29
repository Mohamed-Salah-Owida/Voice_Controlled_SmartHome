/*
 * Motor_Prog.c
 *
 *  Created on: Nov 26, 2023
 *      Author: Mahmoud
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/ErrorType.h"

#include "../MCAL/DIO_Interface.h"
#include "DC_Motor_Cfg.h"
#include "DC_Motor_Interface.h"
#include "DC_Motor_Prv.h"


// Function to rotate the motor in the clockwise direction
uint8 Motor_voidRotateCW(const MotorConfig_t* Copy_pstMotor)
{
	uint8 Local_u8ErrorState = OK ; // Local variable to store error state
	// Check if the motor configuration pointer is not NULL
	if(Copy_pstMotor != NULL)
	{
		// Set the first pin to LOW and the second pin to HIGH for clockwise rotation
		DIO_u8SetPinValue(Copy_pstMotor -> PORT , Copy_pstMotor -> PIN1 , DIO_u8PINLOW);
		DIO_u8SetPinValue(Copy_pstMotor -> PORT , Copy_pstMotor -> PIN2 , DIO_u8PINHIGH);

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR ;// Set error state to NULL pointer error
	}
	return Local_u8ErrorState ;// Return the error state
}


// Function to rotate the motor in the counterclockwise direction
uint8 Motor_voidRotateCCW(const MotorConfig_t* Copy_pstMotor)
{
	uint8 Local_u8ErrorState = OK ;

	if(Copy_pstMotor != NULL)
	{
		// Set the second pin to LOW and the first pin to HIGH for counterclockwise rotation
		DIO_u8SetPinValue(Copy_pstMotor -> PORT , Copy_pstMotor -> PIN2 , DIO_u8PINLOW);
		DIO_u8SetPinValue(Copy_pstMotor -> PORT , Copy_pstMotor -> PIN1 , DIO_u8PINHIGH);

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR ;
	}
	return Local_u8ErrorState ;
}


// Function to stop the motor
uint8 Motor_voidStop(const MotorConfig_t* Copy_pstMotor)
{
	uint8 Local_u8ErrorState = OK ;

	if(Copy_pstMotor != NULL)
	{
		// Set both pins to LOW to stop the motor
		DIO_u8SetPinValue(Copy_pstMotor -> PORT , Copy_pstMotor -> PIN1 , DIO_u8PINLOW);
		DIO_u8SetPinValue(Copy_pstMotor -> PORT , Copy_pstMotor -> PIN2 , DIO_u8PINLOW);

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR ;
	}

	return Local_u8ErrorState ;
}
