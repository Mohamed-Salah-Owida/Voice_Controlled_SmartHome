/*
 * Project.c
 *
 *  Created on: May 23, 2025
 *      Author: Mohamed Salah Owida
 */
#include "../LIB/STD_TYPES.h"

#include "../MCAL/PORT_Interface.h"
#include "../MCAL/DIO_Interface.h"
#include "../MCAL/GIE_Interface.h"
#include "../MCAL/TIMER_Interface.h"
#include "../MCAL/USART_Interface.h"


#include "../HAL/LED_Interface.h"
#include "../HAL/Servo_Interface.h"
#include "../HAL/DC_Motor_Interface.h"
#include "../HAL/LDR_Interface.h"
#include "../HAL/LM35_Interface.h"
#include "../HAL/CLCD_interface.h"


#include <string.h>
#include "util/delay.h"


#include "Project.h"



// ----------------------------
// Global Object Definitions
// ----------------------------


// Configuration for fan motor (PORTC, PIN0/PIN1 for direction control)
MotorConfig_t Fan ={
		DIO_u8PORTC,
		DIO_u8PIN0,
		DIO_u8PIN1,
};

// Timer0 configuration for LDR sensor polling
Timer0_2Cfg_t  LDR = {
		T0_2Normal,
		T0_2Disconnected_Non,
		T0_2Disconnected_Fast,
		T0_2Disconnected_Phase,
		CLK_1024
};




// ----------------------------
// Global Variables
// ----------------------------
uint8 Global_LDR_Reading  = 0;  // LDR sensor digital value
uint8 Global_LM35_Reading = 0;  // Temperature sensor value
uint8 Global_LDRFlag      = 0;  // Flag to enable/disable auto-lighting


void main (void){
	// Variable to store login result (1 = success, 0 = failure)
	uint8 PasswordAccepted= 0 ;

	// ----------------------------
	// Drivers Initialization
	// ----------------------------
	PORT_voidInit();       // Set directions for all configured pins
	USART_Init();          // Initialize USART communication
	Servo_VoidInit();      // Initialize servo motor
	LDR_voidInit();        // Initialize LDR driver
	CLCD_VoidInit();       // Initialize LCD display

	GIE_voidEnableGlobal(); // Enable global interrupt

	// ----------------------------
	// Configure Timer0 for LDR auto control (runs in background)
	// ----------------------------
	Timers_SetCallBack(T0_Ovf_Int, &LightIntensityControl);
	Timer0_VoidSetPreloadVal(230);  // Set preload value for desired overflow rate
	Timer0_u8Init(&LDR);            // Initialize Timer0 with configured values

	// ----------------------------
	// User Login
	// ----------------------------
	PasswordAccepted= LoginHandler();     // Prompt user to enter the password
	TIMER0_u8IntEnable(T0_Ovf_Int); // Enable Timer0 Overflow Interrupt

	if(PasswordAccepted== 1)
	{
		SystemControl(); // Start smart home control system
	}
	else
	{
		SystemClosed();  // Deny access and shut down system
	}

	while (1)
	{
		// Infinite loop - all logic is interrupt or command driven
	}
}


void SystemControl(void)
{
	// Variable to store user input command
	uint8 UserCommand[MAX_INPUT_SIZE] = {0};

	// Display control options to the user
	Menu();

	// The system waits for voice/text commands from the user continuously
	while(1)
	{
		// Receive a command string from the user via USART
		USART_voidReceiveString(UserCommand);

		// Handle the command using string comparison with known options

		// Turn on the light
		if(strcmp((char*)UserCommand, "turn on the light") == 0)
		{
			DIO_u8SetPortValue(DIO_u8PORTB, DIO_u8PORTHIGH); // Turn on all lights (PORTB)
			CLCD_voidGoToXY(12, 0);
			CLCD_u8SendString("ON "); // Display "ON" on LCD
			USART_u8SendString("the light turned on\n"); // Send status over USART
		}
		// Turn off the light
		else if(strcmp((char*)UserCommand, "turn off the light") == 0)
		{
			DIO_u8SetPortValue(DIO_u8PORTB, DIO_u8PORTLOW); // Turn off all lights
			CLCD_voidGoToXY(12, 0);
			CLCD_u8SendString("OFF"); // Display "OFF" on LCD
			USART_u8SendString("the light turned off\n");
		}
		// Open the door using the servo
		else if(strcmp((char*)UserCommand, "open the door") == 0)
		{
			Servo_VoidSetAngle(90); // Set servo angle to 90° to open door
			CLCD_voidGoToXY(13, 1);
			CLCD_u8SendString("OP "); // Show "OP" (Open) on LCD
			USART_u8SendString("the door opened\n");
		}
		// Close the door
		else if(strcmp((char*)UserCommand, "close the door") == 0)
		{
			Servo_VoidSetAngle(0); // Set servo angle to 0° to close door
			CLCD_voidGoToXY(13, 1);
			CLCD_u8SendString("CL "); // Show "CL" (Closed) on LCD
			USART_u8SendString("the door closed\n");
		}
		// Turn on the fan (motor)
		else if(strcmp((char*)UserCommand, "open the fan") == 0)
		{
			Motor_voidRotateCCW(&Fan); // Start fan in counter-clockwise direction
			CLCD_voidGoToXY(4, 1);
			CLCD_u8SendString("ON "); // Display "ON" at fan position on LCD
			USART_u8SendString("the fan opened\n");
		}
		// Turn off the fan
		else if(strcmp((char*)UserCommand, "close the fan") == 0)
		{
			Motor_voidStop(&Fan); // Stop the fan
			CLCD_voidGoToXY(4, 1);
			CLCD_u8SendString("OFF"); // Display "OFF"
			USART_u8SendString("the fan closed\n");
		}
		// Enable automatic light intensity control based on LDR
		else if(strcmp((char*)UserCommand, "auto light intensity") == 0)
		{
			Global_LDRFlag = 1; // Set flag to enable LDR-based auto lighting
			CLCD_voidGoToXY(12, 0);
			CLCD_u8SendString("ON "); // Show "ON" for auto light
			USART_u8SendString("the auto light intensity working\n");
		}
		// Disable automatic light intensity control
		else if(strcmp((char*)UserCommand, "stop auto light intensity") == 0)
		{
			Global_LDRFlag = 0; // Disable auto light control
			DIO_u8SetPortValue(DIO_u8PORTB, DIO_u8PORTLOW); // Turn off all lights
			CLCD_voidGoToXY(12, 0);
			CLCD_u8SendString("OFF"); // Show "OFF"
			USART_u8SendString("the auto light intensity stopped\n");
		}
		// Display the menu again (user help)
		else if(strcmp((char*)UserCommand, "show the options") == 0)
		{
			Menu(); // Re-display control options
		}
		// Close the system and exit loop
		else if(strcmp((char*)UserCommand, "close the system") == 0)
		{
			SystemClosed(); // Shut down system and return to login
			break;
		}
		// If the command doesn't match any known command
		else
		{
			USART_u8SendString("the Option Not found!!\n"); // Notify invalid command
		}
	}
}


// LDR Interrupt Service Routine (called periodically)
void LightIntensityControl(void)
{
	static uint8 Counter1 = 0;  // Counter for managing LDR update interval
	static uint8 Counter2 = 0;  // Counter for managing temperature update interval

	Counter1++;
	Counter2++;

	// Execute this block approximately every 100ms (based on Timer0 interval and Counter1)
	if(Counter1 == 7)
	{
		// Check if automatic light intensity control is enabled
		if(Global_LDRFlag == 1)
		{
			//Timer0_VoidSetPreloadVal(230);
			// Read LDR sensor value from channel 0
			Global_LDR_Reading = LDR_u8GetReading(0);

			// Convert reading to a bitmask for controlling LED brightness (e.g., 3 -> 0b00000111)
			Global_LDR_Reading = ((1 << Global_LDR_Reading) - 1);

			// Set LED output intensity on PORTB based on LDR reading
			DIO_u8SetPortValue(DIO_u8PORTB, Global_LDR_Reading);
		}

		// Reset LDR timing counter
		Counter1 = 0;
	}

	// Execute this block approximately every ~875ms (based on Timer0 and Counter2)
	if(Counter2 == 61)
	{
		// Get temperature from LM35 sensor on channel 7
		Global_LM35_Reading = LM35_u8GetTemperatureValue(7);

		// Display temperature value on LCD at position (5,0)
		CLCD_voidGoToXY(5, 0);
		CLCD_VoidSendNumber((uint32)Global_LM35_Reading);

		// Reset temperature timing counter
		Counter2 = 0;
	}
}



uint8 LoginHandler (void)
{
	// Define variables
	uint8 Pass[4] = {0};                 // Buffer to store 4-digit password entered by user
	uint8 NumOfIteration;               // Loop counter for allowed login attempts
	uint8 IsPasswordCorrect = 0;        // Flag to indicate if login was successful

	// Welcome message sent via USART and shown on LCD
	USART_u8SendString("Welcome\n");
	USART_u8SendString("Enter the password[4 digits]:\n");

	CLCD_voidGoToXY(0, 0);
	CLCD_u8SendString("enter the pass");
	CLCD_voidGoToXY(0, 1);
	CLCD_u8SendString("On your Phone");

	// Allow user up to 3 attempts to enter the correct password
	for(NumOfIteration = 3 ; NumOfIteration > 0 ; NumOfIteration-- )
	{
		// Receive password input from user through USART
		USART_voidReceiveString(Pass);

		// Compare input password with the predefined PASSWORD
		if (strcmp((char *)Pass, PASSWORD ) == 0)
		{
			// If password is correct
			IsPasswordCorrect = 1;
			USART_u8SendString("System Works\n");

			// Initialize screen layout after successful login
			ScreenInit();
			break;  // Exit the loop
		}
		else
		{
			// Password is incorrect
			IsPasswordCorrect = 0;

			// If this is not the last attempt, notify user to try again
			if(NumOfIteration != 1)
			{
				USART_u8SendString("Wrong Pass,Try again\n");

				CLCD_VoidSendCmd(1);  // Clear the LCD
				CLCD_voidGoToXY(0, 0);
				CLCD_u8SendString("Pass wrong");
				CLCD_voidGoToXY(0, 1);
				CLCD_u8SendString("Try again!");
			}
			else
			{
				// On the last attempt, do not print "Try again"
				// (Optional place for system lockout or alert if needed)
			}
		}
	}

	// Return the result: 1 if password correct, 0 otherwise
	return IsPasswordCorrect;
}



void ScreenInit(void)
{
	// Clear the LCD screen
	CLCD_VoidSendCmd(1);

	// Display "TEMP:" at position (0, 0) to indicate temperature value will be shown here
	CLCD_voidGoToXY(0, 0);
	CLCD_u8SendString("TEMP:");

	// Display "LED:" at position (8, 0) to indicate the LED status area
	CLCD_voidGoToXY(8, 0);
	CLCD_u8SendString("LED:");

	// Display initial LED status as "OFF" at position (12, 0)
	CLCD_voidGoToXY(12, 0);
	CLCD_u8SendString("OFF");

	// Display "Fan:" at position (0, 1) to label the fan status
	CLCD_voidGoToXY(0, 1);
	CLCD_u8SendString("Fan:");

	// Display initial fan status as "OFF" at position (4, 1)
	CLCD_voidGoToXY(4, 1);
	CLCD_u8SendString("OFF");

	// Display "door:" at position (8, 1) to label the door status
	CLCD_voidGoToXY(8, 1);
	CLCD_u8SendString("door:");

	// Display initial door status as "CL " (Closed) at position (13, 1)
	CLCD_voidGoToXY(13, 1);
	CLCD_u8SendString("CL ");
}

void Menu(void)
{
	// Prompt the user to choose from the list of available options
	USART_u8SendString("Please choose an Option from the menu\n");

	// Display the list of available voice/text commands via USART (serial terminal)
	USART_u8SendString(
			"1-turn on the light\n"
			"2-turn off the light\n"
			"3-open the door\n"
			"4-close the door\n"
			"5-open the fan\n"
			"6-close the fan\n"
			"7-show the Options\n"
			"8-auto light intensity\n"
			"9-stop auto light intensity\n"
			"10-close the system\n");
}

void SystemClosed(void)
{
	// Disable global interrupts to stop sensors like LDR, Temperature, Ultrasonic
	GIE_voidDisableGlobal();

	// Turn off all LEDs connected to PORTB
	DIO_u8SetPortValue(DIO_u8PORTB, DIO_u8PORTLOW);

	// Close the door by setting the servo to 0 degrees
	Servo_VoidSetAngle(0);

	// Turn off the fan (stop the motor)
	Motor_voidStop(&Fan);

	// Send system closed message via USART (serial monitor or PC)
	USART_u8SendString("System Closed\n");

	// Clear the LCD screen
	CLCD_VoidSendCmd(1);

	// Display "System Closed" message on the LCD
	CLCD_voidGoToXY(1, 0);
	CLCD_u8SendString("System Closed");
}




