/*
 * Project.h
 *
 * Created on: May 23, 2025
 * Author: Mohamed Salah Owida
 */

#ifndef PROJECT_H_
#define PROJECT_H_

// System password used for user authentication (4-digit string)
#define PASSWORD  "1234"

// Maximum length for input command strings
#define MAX_INPUT_SIZE  30

// Function prototypes for main system operations

// Handles user login by verifying password input
uint8 LoginHandler (void);

// Controls the system based on user commands via USART
void SystemControl(void);

// ISR function for controlling light intensity via LDR sensor
void LightIntensityControl(void);

// Reads temperature value from LM35 sensor
void GetTemp(void);

// Initializes the LCD screen with default labels and values
void ScreenInit(void);

// Closes the system safely by turning off devices and disabling interrupts
void SystemClosed(void);

// Displays the command menu over USART interface
void Menu(void);

#endif /* PROJECT_H_ */
