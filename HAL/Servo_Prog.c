#include "../LIB/STD_TYPES.h"
#include "../LIB/MAP.h"

#include "../MCAL/DIO_Interface.h"
#include "../MCAL/TIMER_Interface.h"

#include "Servo_Prv.h"
#include "Servo_Cfg.h"
#include "Servo_Interface.h"


/* Timer1 Configuration Structure for Servo Control */
Timer1_Cfg_t Servo = {
    T1_FastPwm1,             // Fast PWM Mode 14 (ICR1 as TOP)
    T1_CHA_Disconnected_Non, // Channel A disconnected (not used)
    T1_CHA_Disconnected_Fast, // Fast PWM mode for Channel A
    T1_CHA_Disconnected_Phase, // Phase correct PWM (not used here)
    CLK_8                    // Timer clock prescaler set to 8
};

/*
 * Function: Servo_VoidInit
 * -------------------------
 * Initializes the servo motor by configuring Timer1 in Fast PWM mode
 * and setting the corresponding output pin as an output.
 */
void Servo_VoidInit()
{
	// Initialize Timer1 with the predefined configuration
	Timer1_u8Init(&Servo);

    // Configure the output pin based on the defined ServoPIn
#if ServoPIn == ServoPin_OC1A
    DIO_u8SetPinDirection(ServoPort, ServoPin_OC1A, DIO_u8PIN_OUTPUT);
    TIMER1_u8SetComFastPWM_Mode(T1_CHA_ClearOnCom_SetOnTop);
#elif ServoPIn == ServoPin_OC1B
    DIO_u8SetPinDirection(ServoPort, ServoPin_OC1B, DIO_u8PIN_OUTPUT);
    TIMER1_u8SetComFastPWM_Mode(T1_CHB_ClearOnCom_SetOnTop);
#endif

    // Set the TOP value to define the PWM period (20ms for 50Hz PWM)
    Timer1_VoidSetTopVal(40000);
}

/*
 * Function: Servo_VoidSetAngle
 * ----------------------------
 * Sets the servo motor to a specific angle (0 to 180 degrees) by
 * calculating the corresponding PWM duty cycle.
 *
 * Parameters:
 *  - Copy_u8Angle: Desired angle (0 to 180 degrees)
 */
void Servo_VoidSetAngle(uint8 Copy_u8Angle) {
    // Map the input angle (0-180) to the required PWM duty cycle (pulse width in microseconds)
#if ServoPIn == ServoPin_OC1A
    Timer1_VoidSetComAVal(Map((uint16)Copy_u8Angle, 0, 180, 1000, 4900));
#elif ServoPIn == ServoPin_OC1B
    Timer1_VoidSetComBVal(Map((uint16)Copy_u8Angle, 0, 180, 1000, 4900));
#endif
}

