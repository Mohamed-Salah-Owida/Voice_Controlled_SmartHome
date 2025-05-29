/*
 * Motor_Interface.h
 *
 *  Created on: Nov 26, 2023
 *      Author: Mahmoud
 */

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_


// Define a structure to hold motor configuration parameters
typedef struct
{
	uint8 PORT  ;
	uint8 PIN1  ;
	uint8 PIN2  ;

}MotorConfig_t;


// Function prototypes for motor control
uint8 Motor_voidRotateCW(const MotorConfig_t* Copy_pstMotor);
uint8 Motor_voidRotateCCW(const MotorConfig_t* Copy_pstMotor);
uint8 Motor_voidStop(const MotorConfig_t* Copy_pstMotor);



#endif /* MOTOR_INTERFACE_H_ */
