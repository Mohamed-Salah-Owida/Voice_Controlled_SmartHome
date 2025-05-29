/*
 * TIMER_Interface.h
 *
 *  Created on: Feb 14, 2025
 *      Author: moham
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_



/* Enumeration for Timer Interrupt Types */
typedef enum{
	T0_2Com_Int,  // Compare Match Interrupt
	T0_Ovf_Int,   // Overflow Interrupt
	T2_Ovf_Int,
	T1_InpCapT_Int,  // Input Capture Interrupt
	T1_ComA_Int,     // Compare Match A Interrupt
	T1_ComB_Int,     // Compare Match B Interrupt
	T1_Ovf_Int      // Overflow Interrupt
} Timers_INT_Source_t;


/*-----------------------------------------------------------------------------------*/
/*                             TIMER0 & TIMER2 CONFIGURATION                         */
/*-----------------------------------------------------------------------------------*/

/* Enumeration for Timer0 and Timer2 Waveform Generation Modes */
typedef enum{
	T0_2Normal,                // Normal mode (counter overflows at MAX value)
	T0_2Phase_Correct,         // Phase Correct PWM mode (adjusts pulse width symmetrically)
	T0_2CTC,                   // Clear Timer on Compare Match (CTC) mode
	T0_2Fast_PWM               // Fast PWM mode (used for high-speed PWM control)
} Timer0_2WGM_t;

/* Enumeration for Timer0 and Timer2 Compare Output Modes in Non-PWM Mode */
/* Defines the behavior of the OC0 pin when operating in Normal or CTC mode */
typedef enum{
	T0_2Disconnected_Non,      // OC0 disconnected (Normal operation, no output)
	T0_2Toggle,                // Toggle OC0 on compare match
	T0_2Clear,                 // Clear OC0 on compare match
	T0_2Set                    // Set OC0 on compare match
} Timer0_2Com_OutMode_NonPwm_t;

/* Enumeration for Timer0 and Timer2 Compare Output Modes in Fast PWM Mode */
typedef enum{
	T0_2Disconnected_Fast,             // OC0 disconnected
	T0_2ClearOnCom_SetAtTop,           // Clear OC0 on compare match, set at TOP (non-inverting mode)
	T0_2SetOnCom_ClearAtTop            // Set OC0 on compare match, clear at TOP (inverting mode)
} Timer0_2Com_OutMode_FastPwm_t;

/* Enumeration for Timer0 and Timer2 Compare Output Modes in Phase Correct PWM Mode */
typedef enum{
	T0_2Disconnected_Phase,              // OC0 disconnected
	T0_2ClearUpCounting_SetDownCounting, // Clear OC0 on up-counting, set on down-counting
	T0_2SetUpCounting_ClearDownCounting  // Set OC0 on up-counting, clear on down-counting
} Timer0_2Com_OutMode_PhaseCorrect_t;

/* Enumeration for Clock Source Selection and Prescaler Values */
typedef enum{
	No_CLK_Source,              // Timer stopped (No clock source)
	No_Prescaling,              // No prescaler (Direct system clock)
	CLK_8,                      // Clock divided by 8
	CLK_32,                     // Clock divided by 32
	CLK_64,                     // Clock divided by 64
	CLK_128,                    // Clock divided by 128
	CLK_256,                    // Clock divided by 256
	CLK_1024,                   // Clock divided by 1024
	Ext_ClkSource_Falling_Edge, // External clock source on T0 pin (falling edge trigger)
	Ext_ClkSource_Rising_Edge   // External clock source on T0 pin (rising edge trigger)
} Timers_CLK_Select_t;


/* Structure to configure Timer0 and Timer2 settings */
typedef struct{
	Timer0_2WGM_t WGM;                        // Waveform Generation Mode
	Timer0_2Com_OutMode_NonPwm_t Com_NonPWM;  // Compare Output Mode (Non-PWM)
	Timer0_2Com_OutMode_FastPwm_t Com_FastPWM;// Compare Output Mode (Fast PWM)
	Timer0_2Com_OutMode_PhaseCorrect_t Com_PhaseCor; // Compare Output Mode (Phase Correct PWM)
	Timers_CLK_Select_t CLK_prescaler;        // Clock prescaler selection
} Timer0_2Cfg_t;

/*-------------------------------------------------------------------------------*/
/*                                  TIMER1 CONFIGURATION                         */
/*-------------------------------------------------------------------------------*/

/* Enumeration for Timer1 Compare Output Mode in Non-PWM mode */
typedef enum{
	T1_CHA_Disconnected_Non,      // Channel A: Disconnected (No Output)
	T1_CHA_Toggle,                // Channel A: Toggle output on compare match
	T1_CHA_Clear,                 // Channel A: Clear output on compare match
	T1_CHA_Set,                   // Channel A: Set output on compare match
	T1_CHB_Disconnected_Non,      // Channel B: Disconnected (No Output)
	T1_CHB_Toggle,                // Channel B: Toggle output on compare match
	T1_CHB_Clear,                 // Channel B: Clear output on compare match
	T1_CHB_Set                    // Channel B: Set output on compare match
}Timer1_Com_OutMode_NonPWM_t;

/* Enumeration for Timer1 Compare Output Mode in Fast PWM mode */
typedef enum{
	T1_CHA_Disconnected_Fast,          // Channel A: Disconnected (No Output)
	T1_CHA_NormalPort_Fast,            // Channel A: Normal port operation
	T1_CHA_ClearOnCom_SetOnTop,        // Channel A: Clear on compare match, set at top
	T1_CHA_SetOnCom_ClearOnTop,        // Channel A: Set on compare match, clear at top
	T1_CHB_Disconnected_Fast,          // Channel B: Disconnected (No Output)
	T1_CHB_NormalPort_Fast,            // Channel B: Normal port operation
	T1_CHB_ClearOnCom_SetOnTop,        // Channel B: Clear on compare match, set at top
	T1_CHB_SetOnCom_ClearOnTop         // Channel B: Set on compare match, clear at top
}Timer1_Com_OutMode_FastPWM_t;

/* Enumeration for Timer1 Compare Output Mode in Phase Correct PWM mode */
typedef enum{
	T1_CHA_Disconnected_Phase,                // Channel A: Disconnected (No Output)
	T1_CHA_NormalPort_Phase,                  // Channel A: Normal port operation
	T1_CHA_ClearUpCounting_SetDownCounting,   // Channel A: Clear on up-counting, set on down-counting
	T1_CHA_SetUpCounting_ClearDownCounting,   // Channel A: Set on up-counting, clear on down-counting
	T1_CHB_Disconnected_Phase,                // Channel B: Disconnected (No Output)
	T1_CHB_NormalPort_Phase,                  // Channel B: Normal port operation
	T1_CHB_ClearUpCounting_SetDownCounting,   // Channel B: Clear on up-counting, set on down-counting
	T1_CHB_SetUpCounting_ClearDownCounting    // Channel B: Set on up-counting, clear on down-counting
}Timer1_Com_OutMode_PhaseCorrrectPWM_t;

/* Enumeration for Timer1 Waveform Generation Modes */
typedef enum{
	T1_Normal,                               // Normal mode
	T1_Pwm_PhaseCorrect_8Bit,               // Phase Correct PWM (8-bit)
	T1_Pwm_PhaseCorrect_9Bit,               // Phase Correct PWM (9-bit)
	T1_Pwm_PhaseCorrect_10Bit,              // Phase Correct PWM (10-bit)
	T1_CTC1,                                // Clear Timer on Compare Match (CTC Mode 1)
	T1_FastPwm_8bit,                        // Fast PWM (8-bit)
	T1_FastPwm_9bit,                        // Fast PWM (9-bit)
	T1_FastPwm_10bit,                       // Fast PWM (10-bit)
	T1_Pwm_PhaseAndFrequency_Correct1,      // Phase and Frequency Correct PWM Mode 1
	T1_Pwm_PhaseAndFrequency_Correct2,      // Phase and Frequency Correct PWM Mode 2
	T1_Pwm_Phase_Correct1,                  // Phase Correct PWM Mode 1
	T1_Pwm_Phase_Correct2,                  // Phase Correct PWM Mode 2
	T1_CTC2,                                // Clear Timer on Compare Match (CTC Mode 2)
	T1_FastPwm1,                            // Fast PWM Mode 1
	T1_FastPwm2                             // Fast PWM Mode 2
}Timer1_WGM_t;


typedef enum{
	ICU_RAISING_EDGE,
	ICU_FALLING_EDGE

}Timer1_ICU_Trig_Init_State;


/* Timer1 Configuration Structure */
typedef struct
{
	Timer1_WGM_t WGM;                           // Waveform Generation Mode
	Timer1_Com_OutMode_NonPWM_t Com_NonPWM;     // Compare Output Mode for Non-PWM
	Timer1_Com_OutMode_FastPWM_t Com_FastPWM;   // Compare Output Mode for Fast PWM
	Timer1_Com_OutMode_PhaseCorrrectPWM_t Com_PhaseCor; // Compare Output Mode for Phase Correct PWM
	Timers_CLK_Select_t CLK_Prescaler;          // Clock Prescaler Selection
	Timer1_ICU_Trig_Init_State ICU_Trig_I_State; // Initial State of the ICU Trigger
}Timer1_Cfg_t;



/*-------------------------------------------------------------------------------*/
/*                                  FUNCTIONS_DECLERATION                         */
/*-------------------------------------------------------------------------------*/

/*---- Timer0 Function Declarations --- */

/* Initializes Timer0 with the given configuration */
uint8 Timer0_u8Init(const Timer0_2Cfg_t *Timer0_Cfg);

/* Sets the preload value for Timer0 */
void Timer0_VoidSetPreloadVal(uint8 Copy_u8Val);

/* Sets the compare match value for Timer0 */
void Timer0_VoidSetCompareMatchVal(uint8 Copy_u8Val);



/* Sets the output mode for Timer0 in Non-PWM mode */
uint8 TIMER0_u8SetComNonPWM_Mode(Timer0_2Com_OutMode_NonPwm_t Mode);

/* Sets the output mode for Timer0 in Fast PWM mode */
uint8 TIMER0_u8SetComFastPWM_Mode(Timer0_2Com_OutMode_FastPwm_t Mode);

/* Sets the output mode for Timer0 in Phase-Correct PWM mode */
uint8 TIMER0_u8SetComPhaseCorPWM_Mode(Timer0_2Com_OutMode_PhaseCorrect_t Mode);

/* Enables a specific Timer0 interrupt */
uint8 TIMER0_u8IntEnable(Timers_INT_Source_t Int_Type);

/* Disables a specific Timer0 interrupt */
uint8 TIMER0_u8IntDisable(Timers_INT_Source_t Int_Type);


/*---- Timer2 Function Declarations --- */

/* Initializes Timer2 with the given configuration */
uint8 Timer2_u8Init(const Timer0_2Cfg_t *Timer2_Cfg);

/* Sets the output mode for Timer2 in Non-PWM mode */
uint8 TIMER2_u8SetComNonPWM_Mode(Timer0_2Com_OutMode_NonPwm_t Mode);

/* Sets the output mode for Timer2 in Fast PWM mode */
uint8 TIMER2_u8SetComFastPWM_Mode(Timer0_2Com_OutMode_FastPwm_t Mode);

/* Sets the output mode for Timer2 in Phase-Correct PWM mode */
uint8 TIMER2_u8SetComPhaseCorPWM_Mode(Timer0_2Com_OutMode_PhaseCorrect_t Mode);

/* Enables a specific Timer2 interrupt */
uint8 TIMER2_u8IntEnable(Timers_INT_Source_t Int_Type);

/* Disables a specific Timer2 interrupt */
uint8 TIMER2_u8IntDisable(Timers_INT_Source_t Int_Type);
void Timer2_VoidSetPreloadVal(uint8 Copy_u8Val);



/*---- Timer1 Function Declarations --- */

/* Initializes Timer1 with the given configuration */
uint8 Timer1_u8Init(const Timer1_Cfg_t  *Timer1_Cfg);

/* Sets the top value for Timer1 */
void Timer1_VoidSetTopVal(uint16 Copy_u16Val);

/* Sets the compare match value for Timer1 Channel A */
void Timer1_VoidSetComAVal(uint16 Copy_u16Val);

/* Sets the compare match value for Timer1 Channel B */
void Timer1_VoidSetComBVal(uint16 Copy_u16Val);

/* Sets the output mode for Timer1 in Non-PWM mode */
uint8 TIMER1_u8SetComNonPWM_Mode(Timer1_Com_OutMode_NonPWM_t Mode);

/* Sets the output mode for Timer1 in Fast PWM mode */
uint8 TIMER1_u8SetComFastPWM_Mode(Timer1_Com_OutMode_FastPWM_t Mode);

/* Sets the output mode for Timer1 in Phase-Correct PWM mode */
uint8 TIMER1_u8SetComPhaseCorPWM_Mode(Timer1_Com_OutMode_PhaseCorrrectPWM_t Mode);

/* Enables a specific Timer1 interrupt */
uint8 TIMER1_u8IntEnable(Timers_INT_Source_t Int_Type);

/* Disables a specific Timer1 interrupt */
uint8 TIMER1_u8IntDisable(Timers_INT_Source_t Int_Type);

/* Returns the current Timer1 value */
uint16 Timer1_u16GetTimerVal(void);

/* Sets a specific value for Timer1 */
void Timer1_VoidSetVal(uint16 Copy_u16Val);


/* ICN using ICU mode in Timer1 */

/* Initializes ICU with Timer1 configuration */
void ICU_voidInit(const Timer1_Cfg_t *Timer1_Cfg);

/* Sets the trigger edge for input capture */
uint8 ICU_u8SetTriggerEdge(uint8 Copy_u8Edge);

/* Enables ICU interrupt */
void ICU_voidEnableInterrupt(void);

/* Disables ICU interrupt */
void ICU_voidDisableInterrupt(void);

/* Returns the captured value from ICU */
uint16 ICU_u16GetReadingInputCaptureUnit(void);

/* Calculates elapsed time based on the number of ticks    - time = n.of.ticks *tick time */
uint16 Timer1_ICU_Cal_Time(uint16 Copy_u16Ticks_num, uint8 Copy_u8CLK_Prescaler);




/* Sets a callback function for Timer1 ICU interrupts */
uint8  Timers_SetCallBack(Timers_INT_Source_t Copy_INT_Source, void(*Copy_PvCallBackFunc)(void));





#endif /* TIMER_INTERFACE_H_ */
