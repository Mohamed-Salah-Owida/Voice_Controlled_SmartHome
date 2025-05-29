#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_

/*
 * Function: Servo_VoidInit
 * -------------------------
 * Initializes the servo motor by configuring Timer1 in Fast PWM mode
 * and setting the corresponding output pin as an output.
 */
void Servo_VoidInit();

/*
 * Function: Servo_VoidSetAngle
 * ----------------------------
 * Sets the servo motor to a specific angle (0 to 180 degrees) by
 * calculating the corresponding PWM duty cycle.
 *
 * Parameters:
 *  - Copy_u8Angle: Desired angle (0 to 180 degrees)
 */
void Servo_VoidSetAngle(uint8 Copy_u8Angle);

#endif /* SERVO_INTERFACE_H_ */
