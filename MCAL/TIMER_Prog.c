/*
 * TIMER_Prog.c
 *
 *  Created on: Feb 14, 2025
 *      Author: moham
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/ErrorType.h"
#include "TIMER_interface.h"
#include "TIMER_reg.h"
#include "TIMER_prv.h"

/* Array of function pointers for Timer callbacks */
static void (*Timer_CallBackFunc[9])(void) = {NULL};

/*
 * Function: Timer0_u8Init
 * -----------------------
 * Initializes Timer0 with the provided configuration.
 *
 * Timer0_Cfg: Pointer to the Timer0 configuration structure.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 Timer0_u8Init(const Timer0_2Cfg_t *Timer0_Cfg)
{
	uint8 Local_u8ErroState = OK;

	/* Set Waveform Generation Mode */
	switch (Timer0_Cfg->WGM)
	{
	case T0_2Normal: CLR_BIT(TCCR0, TCCR0_WGM00); CLR_BIT(TCCR0, TCCR0_WGM01); break;
	case T0_2Phase_Correct: SET_BIT(TCCR0, TCCR0_WGM00); CLR_BIT(TCCR0, TCCR0_WGM01); break;
	case T0_2CTC: CLR_BIT(TCCR0, TCCR0_WGM00); SET_BIT(TCCR0, TCCR0_WGM01); break;
	case T0_2Fast_PWM: SET_BIT(TCCR0, TCCR0_WGM00); SET_BIT(TCCR0, TCCR0_WGM01); break;
	default: Local_u8ErroState = NOK; break;
	}

	/* Set Compare Output Mode (Non-PWM) */
	switch (Timer0_Cfg->Com_NonPWM)
	{
	case T0_2Disconnected_Non: break;
	case T0_2Toggle: SET_BIT(TCCR0, TCCR0_COM00); CLR_BIT(TCCR0, TCCR0_COM01); break;
	case T0_2Clear: CLR_BIT(TCCR0, TCCR0_COM00); SET_BIT(TCCR0, TCCR0_COM01); break;
	case T0_2Set: SET_BIT(TCCR0, TCCR0_COM00); SET_BIT(TCCR0, TCCR0_COM01); break;
	default: Local_u8ErroState = NOK; break;
	}
	switch(Timer0_Cfg -> Com_FastPWM)
	{
	case(T0_2Disconnected_Fast):break;
	case(T0_2ClearOnCom_SetAtTop):CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break;
	case(T0_2SetOnCom_ClearAtTop):SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break;
	default: Local_u8ErroState =NOK; break;
	}

	switch(Timer0_Cfg -> Com_PhaseCor)
	{
	case(T0_2Disconnected_Phase):break;
	case(T0_2ClearUpCounting_SetDownCounting):CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break;
	case(T0_2SetUpCounting_ClearDownCounting):SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break;
	default: Local_u8ErroState =NOK; break;
	}

	/* Set Clock Prescaler */
	switch (Timer0_Cfg->CLK_prescaler)
	{
	case No_CLK_Source: CLR_BIT(TCCR0, TCCR0_CS00); CLR_BIT(TCCR0, TCCR0_CS01); CLR_BIT(TCCR0, TCCR0_CS02); break;
	case No_Prescaling: TCCR0 &= Clear_Prescaler_Bits; SET_BIT(TCCR0, TCCR0_CS00); break;
	case CLK_8: TCCR0 &= Clear_Prescaler_Bits; SET_BIT(TCCR0, TCCR0_CS01); break;
	case CLK_64: TCCR0 &= Clear_Prescaler_Bits; SET_BIT(TCCR0, TCCR0_CS00); SET_BIT(TCCR0, TCCR0_CS01); break;
	case CLK_1024: TCCR0 &= Clear_Prescaler_Bits; SET_BIT(TCCR0, TCCR0_CS00); CLR_BIT(TCCR0, TCCR0_CS01);SET_BIT(TCCR0, TCCR0_CS02); break;
	default: Local_u8ErroState = NOK; break;
	}

	return Local_u8ErroState;
}

/*
 * Function: Timer0_VoidSetPreloadVal
 * ----------------------------------
 * Sets the preload value for Timer0.
 *
 * Copy_u8Val: The preload value to be set in the TCNT0 register.
 */
void Timer0_VoidSetPreloadVal(uint8 Copy_u8Val)
{
	TCNT0 = Copy_u8Val;
}

/*
 * Function: Timer0_VoidSetCompareMatchVal
 * --------------------------------------
 * Sets the compare match value for Timer0.
 *
 * Copy_u8Val: The value to be set in the OCR0 register.
 */
void Timer0_VoidSetCompareMatchVal(uint8 Copy_u8Val)
{
	OCR0 = Copy_u8Val;
}


/*
 * Function: TIMER0_u8SetComNonPWM_Mode
 * ------------------------------------
 * Configures the Compare Output Mode for Timer0 in non-PWM mode.
 *
 * Mode: The desired mode of operation.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 TIMER0_u8SetComNonPWM_Mode(Timer0_2Com_OutMode_NonPwm_t Mode)
{
	uint8 Local_u8ErroState = OK;
	switch (Mode)
	{
	case T0_2Disconnected_Non: break;
	case T0_2Toggle: SET_BIT(TCCR0, TCCR0_COM00); CLR_BIT(TCCR0, TCCR0_COM01); break;
	case T0_2Clear: CLR_BIT(TCCR0, TCCR0_COM00); SET_BIT(TCCR0, TCCR0_COM01); break;
	case T0_2Set: SET_BIT(TCCR0, TCCR0_COM00); SET_BIT(TCCR0, TCCR0_COM01); break;
	default: Local_u8ErroState = NOK; break;
	}
	return Local_u8ErroState;
}

/*
 * Function: TIMER0_u8SetComFastPWM_Mode
 * ------------------------------------
 * Configures the Compare Output Mode for Timer0 in Fast PWM mode.
 *
 * Mode: The desired mode of operation.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 TIMER0_u8SetComFastPWM_Mode(Timer0_2Com_OutMode_FastPwm_t Mode)
{
	uint8 Local_u8ErroState = OK;
	switch (Mode)
	{
	case T0_2Disconnected_Fast: break;
	case T0_2ClearOnCom_SetAtTop: CLR_BIT(TCCR0, TCCR0_COM00); SET_BIT(TCCR0, TCCR0_COM01); break;
	case T0_2SetOnCom_ClearAtTop: SET_BIT(TCCR0, TCCR0_COM00); SET_BIT(TCCR0, TCCR0_COM01); break;
	default: Local_u8ErroState = NOK; break;
	}
	return Local_u8ErroState;
}

/*
 * Function: TIMER0_u8SetComPhaseCorPWM_Mode
 * ------------------------------------
 * Configures the Compare Output Mode for Timer0 in Phase Correct PWM mode.
 *
 * Mode: The desired mode of operation.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 TIMER0_u8SetComPhaseCorPWM_Mode(Timer0_2Com_OutMode_PhaseCorrect_t Mode)
{
	uint8 Local_u8ErroState = OK;
	switch (Mode)
	{
	case T0_2Disconnected_Phase: break;
	case T0_2ClearUpCounting_SetDownCounting: CLR_BIT(TCCR0, TCCR0_COM00); SET_BIT(TCCR0, TCCR0_COM01); break;
	case T0_2SetUpCounting_ClearDownCounting: SET_BIT(TCCR0, TCCR0_COM00); SET_BIT(TCCR0, TCCR0_COM01); break;
	default: Local_u8ErroState = NOK; break;
	}
	return Local_u8ErroState;
}

/*
 * Function: TIMER0_u8IntEnable
 * ------------------------------------
 * Enables the specified Timer0 interrupt.
 *
 * Int_Type: The interrupt type to enable.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 TIMER0_u8IntEnable(Timers_INT_Source_t Int_Type)
{
	uint8 Local_u8ErroState = OK;
	switch (Int_Type)
	{
	case T0_Ovf_Int: SET_BIT(TIMSK, TIMSK_TOIEO); break;
	case T0_2Com_Int: SET_BIT(TIMSK, TIMSK_OCIE0); break;
	default: Local_u8ErroState = NOK; break;
	}
	return Local_u8ErroState;
}

/*
 * Function: TIMER0_u8IntDisable
 * ------------------------------------
 * Disables the specified Timer0 interrupt.
 *
 * Int_Type: The interrupt type to disable.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 TIMER0_u8IntDisable(Timers_INT_Source_t Int_Type)
{
	uint8 Local_u8ErroState = OK;
	switch (Int_Type)
	{
	case T0_Ovf_Int: CLR_BIT(TIMSK, TIMSK_TOIEO); break;
	case T0_2Com_Int: CLR_BIT(TIMSK, TIMSK_OCIE0); break;
	default: Local_u8ErroState = NOK; break;
	}
	return Local_u8ErroState;
}


/*
 * Function: Timer2_u8Init
 * -----------------------
 * Initializes Timer2 with the provided configuration.
 *
 * Timer2_Cfg: Pointer to the Timer2 configuration structure.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 Timer2_u8Init(const Timer0_2Cfg_t *Timer2_Cfg)
{
	uint8 Local_u8ErroState = OK;

	// Set Waveform Generation Mode
	switch (Timer2_Cfg->WGM)
	{
	case T0_2Normal: CLR_BIT(TCCR2, TCCR2_WGM20); CLR_BIT(TCCR2, TCCR2_WGM21); break;
	case T0_2Phase_Correct: SET_BIT(TCCR2, TCCR2_WGM20); CLR_BIT(TCCR2, TCCR2_WGM21); break;
	case T0_2CTC: CLR_BIT(TCCR2, TCCR2_WGM20); SET_BIT(TCCR2, TCCR2_WGM21); break;
	case T0_2Fast_PWM: SET_BIT(TCCR2, TCCR2_WGM20); SET_BIT(TCCR2, TCCR2_WGM21); break;
	default: Local_u8ErroState = NOK; break;
	}

	// Set Compare Output Mode (Non-PWM)
	switch (Timer2_Cfg->Com_NonPWM)
	{
	case T0_2Disconnected_Non: break;
	case T0_2Toggle: SET_BIT(TCCR2, TCCR2_COM20); CLR_BIT(TCCR2, TCCR2_COM21); break;
	case T0_2Clear: CLR_BIT(TCCR2, TCCR2_COM20); SET_BIT(TCCR2, TCCR2_COM21); break;
	case T0_2Set: SET_BIT(TCCR2, TCCR2_COM20); SET_BIT(TCCR2, TCCR2_COM21); break;
	default: Local_u8ErroState = NOK; break;
	}

	// Set Clock Prescaler
	switch (Timer2_Cfg->CLK_prescaler)
	{
	case No_CLK_Source: CLR_BIT(TCCR2, TCCR2_CS20); CLR_BIT(TCCR2, TCCR2_CS21); CLR_BIT(TCCR2, TCCR2_CS22); break;
	case No_Prescaling: TCCR2 &= Clear_Prescaler_Bits; SET_BIT(TCCR2, TCCR2_CS20); break;
	case CLK_8: TCCR2 &= Clear_Prescaler_Bits; SET_BIT(TCCR2, TCCR2_CS21); break;
	case CLK_64: TCCR2 &= Clear_Prescaler_Bits; SET_BIT(TCCR2, TCCR2_CS22); break;
	case CLK_1024: TCCR2 &= Clear_Prescaler_Bits; SET_BIT(TCCR2, TCCR2_CS22); SET_BIT(TCCR2, TCCR2_CS21);SET_BIT(TCCR2, TCCR2_CS20); break;
	default: Local_u8ErroState = NOK; break;
	}

	return Local_u8ErroState;
}

/*
 * Function: TIMER2_u8SetComNonPWM_Mode
 * ------------------------------------
 * Configures the Compare Output Mode for Timer2 in non-PWM mode.
 *
 * Mode: The desired mode of operation.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 TIMER2_u8SetComNonPWM_Mode(Timer0_2Com_OutMode_NonPwm_t Mode)
{
	uint8 Local_u8ErroState = OK;
	switch (Mode)
	{
	case T0_2Disconnected_Non: break;
	case T0_2Toggle: SET_BIT(TCCR2, TCCR2_COM20); CLR_BIT(TCCR2, TCCR2_COM21); break;
	case T0_2Clear: CLR_BIT(TCCR2, TCCR2_COM20); SET_BIT(TCCR2, TCCR2_COM21); break;
	case T0_2Set: SET_BIT(TCCR2, TCCR2_COM20); SET_BIT(TCCR2, TCCR2_COM21); break;
	default: Local_u8ErroState = NOK; break;
	}
	return Local_u8ErroState;
}

/*
 * Function: TIMER2_u8SetComFastPWM_Mode
 * ------------------------------------
 * Configures the Compare Output Mode for Timer2 in Fast PWM mode.
 *
 * Mode: The desired mode of operation.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 TIMER2_u8SetComFastPWM_Mode(Timer0_2Com_OutMode_FastPwm_t Mode)
{
	uint8 Local_u8ErroState = OK;
	switch (Mode)
	{
	case T0_2Disconnected_Fast: break;
	case T0_2ClearOnCom_SetAtTop: CLR_BIT(TCCR2, TCCR2_COM20); SET_BIT(TCCR2, TCCR2_COM21); break;
	case T0_2SetOnCom_ClearAtTop: SET_BIT(TCCR2, TCCR2_COM20); SET_BIT(TCCR2, TCCR2_COM21); break;
	default: Local_u8ErroState = NOK; break;
	}
	return Local_u8ErroState;
}

/*
 * Function: TIMER2_u8SetComPhaseCorPWM_Mode
 * ------------------------------------
 * Configures the Compare Output Mode for Timer2 in Phase Correct PWM mode.
 *
 * Mode: The desired mode of operation.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 TIMER2_u8SetComPhaseCorPWM_Mode(Timer0_2Com_OutMode_PhaseCorrect_t Mode)
{
	uint8 Local_u8ErroState = OK;
	switch (Mode)
	{
	case T0_2Disconnected_Phase: break;
	case T0_2ClearUpCounting_SetDownCounting: CLR_BIT(TCCR2, TCCR2_COM20); SET_BIT(TCCR2, TCCR2_COM21); break;
	case T0_2SetUpCounting_ClearDownCounting: SET_BIT(TCCR2, TCCR2_COM20); SET_BIT(TCCR2, TCCR2_COM21); break;
	default: Local_u8ErroState = NOK; break;
	}
	return Local_u8ErroState;
}

/*
 * Function: TIMER2_u8IntEnable
 * ------------------------------------
 * Enables the specified Timer2 interrupt.
 *
 * Int_Type: The interrupt type to enable.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 TIMER2_u8IntEnable(Timers_INT_Source_t  Int_Type)
{
	uint8 Local_u8ErroState = OK;
	switch (Int_Type)
	{
	case T2_Ovf_Int: SET_BIT(TIMSK, TIMSK_TOIE2); break;
	case T0_2Com_Int: SET_BIT(TIMSK, TIMSK_OCIE2); break;
	default: Local_u8ErroState = NOK; break;
	}
	return Local_u8ErroState;
}

/*
 * Function: TIMER2_u8IntDisable
 * ------------------------------------
 * Disables the specified Timer2 interrupt.
 *
 * Int_Type: The interrupt type to disable.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 TIMER2_u8IntDisable(Timers_INT_Source_t Int_Type)
{
	uint8 Local_u8ErroState = OK;
	switch (Int_Type)
	{
	case T2_Ovf_Int: CLR_BIT(TIMSK, TIMSK_TOIE2); break;
	case T0_2Com_Int: CLR_BIT(TIMSK, TIMSK_OCIE2); break;
	default: Local_u8ErroState = NOK; break;
	}
	return Local_u8ErroState;
}

void Timer2_VoidSetPreloadVal(uint8 Copy_u8Val)
{
	TCNT2 = Copy_u8Val;
}

/*
 * Function: Timer1_u8Init
 * -----------------------
 * Initializes Timer1 with the provided configuration.
 *
 * Timer1_Cfg: Pointer to the Timer1 configuration structure.
 *
 * Returns: Error status (OK or NOK).
 */
uint8 Timer1_u8Init(const Timer1_Cfg_t  *Timer1_Cfg)
{
	uint8 Local_u8ErroState=OK;
	switch(Timer1_Cfg->WGM){
	case (T1_Normal): CLR_BIT(TCCR1A,TCCR1A_WGM10);CLR_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_Pwm_PhaseCorrect_8Bit): SET_BIT(TCCR1A,TCCR1A_WGM10);CLR_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_Pwm_PhaseCorrect_9Bit): CLR_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_Pwm_PhaseCorrect_10Bit): SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_CTC1): CLR_BIT(TCCR1A,TCCR1A_WGM10);CLR_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_FastPwm_8bit): SET_BIT(TCCR1A,TCCR1A_WGM10);CLR_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_FastPwm_9bit): CLR_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_FastPwm_10bit): SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_Pwm_PhaseAndFrequency_Correct1): CLR_BIT(TCCR1A,TCCR1A_WGM10);CLR_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_Pwm_PhaseAndFrequency_Correct2): SET_BIT(TCCR1A,TCCR1A_WGM10);CLR_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_Pwm_Phase_Correct1): CLR_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_Pwm_Phase_Correct2): SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_CTC2): CLR_BIT(TCCR1A,TCCR1A_WGM10);CLR_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_FastPwm1): CLR_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case (T1_FastPwm2): SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	default: Local_u8ErroState = NOK; break;
	}

	switch(Timer1_Cfg->Com_NonPWM)
	{

	case (T1_CHA_Disconnected_Non):break;
	case (T1_CHB_Disconnected_Non):break;
	case (T1_CHA_Toggle):SET_BIT(TCCR1A,TCCR1A_COM1A0);CLR_BIT(TCCR1A,TCCR1A_COM1A1);break;
	case (T1_CHB_Toggle):SET_BIT(TCCR1A,TCCR1A_COM1B0);CLR_BIT(TCCR1A,TCCR1A_COM1B1);break;
	case (T1_CHA_Clear):CLR_BIT(TCCR1A,TCCR1A_COM1A0);SET_BIT(TCCR1A,TCCR1A_COM1A1);break;
	case (T1_CHB_Clear):CLR_BIT(TCCR1A,TCCR1A_COM1B0);SET_BIT(TCCR1A,TCCR1A_COM1B1);break;
	case (T1_CHA_Set): SET_BIT(TCCR1A,TCCR1A_COM1A0);SET_BIT(TCCR1A,TCCR1A_COM1A1);break;
	case (T1_CHB_Set): SET_BIT(TCCR1A,TCCR1A_COM1B0);SET_BIT(TCCR1A,TCCR1A_COM1B1);break;
	default: Local_u8ErroState = NOK;break;
	}

	switch(Timer1_Cfg->Com_FastPWM)
	{
	case T1_CHA_Disconnected_Fast:break;
	case T1_CHB_Disconnected_Fast:break;
	case T1_CHA_NormalPort_Fast: SET_BIT(TCCR1A,TCCR1A_COM1A0);CLR_BIT(TCCR1A,TCCR1A_COM1A1);break;
	case T1_CHB_NormalPort_Fast: SET_BIT(TCCR1A,TCCR1A_COM1B0);CLR_BIT(TCCR1A,TCCR1A_COM1B1);break;
	case T1_CHA_ClearOnCom_SetOnTop: CLR_BIT(TCCR1A,TCCR1A_COM1A0);SET_BIT(TCCR1A,TCCR1A_COM1A1);break;
	case T1_CHB_ClearOnCom_SetOnTop: CLR_BIT(TCCR1A,TCCR1A_COM1B0);SET_BIT(TCCR1A,TCCR1A_COM1B1);break;
	case T1_CHA_SetOnCom_ClearOnTop: SET_BIT(TCCR1A,TCCR1A_COM1A0);SET_BIT(TCCR1A,TCCR1A_COM1A1);break;
	case T1_CHB_SetOnCom_ClearOnTop: SET_BIT(TCCR1A,TCCR1A_COM1B0);SET_BIT(TCCR1A,TCCR1A_COM1B1);break;
	default: Local_u8ErroState = NOK;break;
	}

	switch(Timer1_Cfg->Com_PhaseCor)
	{

	case T1_CHA_Disconnected_Phase:break;
	case T1_CHB_Disconnected_Phase:break;
	case T1_CHA_NormalPort_Phase: SET_BIT(TCCR1A,TCCR1A_COM1A0);CLR_BIT(TCCR1A,TCCR1A_COM1A1);break;
	case T1_CHB_NormalPort_Phase: SET_BIT(TCCR1A,TCCR1A_COM1B0);CLR_BIT(TCCR1A,TCCR1A_COM1B1);break;
	case T1_CHA_ClearUpCounting_SetDownCounting: CLR_BIT(TCCR1A,TCCR1A_COM1A0);SET_BIT(TCCR1A,TCCR1A_COM1A1);break;
	case T1_CHB_ClearUpCounting_SetDownCounting: CLR_BIT(TCCR1A,TCCR1A_COM1B0);SET_BIT(TCCR1A,TCCR1A_COM1B1);break;
	case T1_CHA_SetUpCounting_ClearDownCounting: SET_BIT(TCCR1A,TCCR1A_COM1A0);SET_BIT(TCCR1A,TCCR1A_COM1A1);break;
	case T1_CHB_SetUpCounting_ClearDownCounting: SET_BIT(TCCR1A,TCCR1A_COM1B0);SET_BIT(TCCR1A,TCCR1A_COM1B1);break;
	default: Local_u8ErroState = NOK;break;
	}

	switch(Timer1_Cfg->CLK_Prescaler){
	case No_CLK_Source:TCCR1B &=Clear_Prescaler_Bits; CLR_BIT(TCCR1B,TCCR1B_CS10);CLR_BIT(TCCR1B,TCCR1B_CS11);CLR_BIT(TCCR1B,TCCR1B_CS12);break;
	case No_Prescaling: TCCR1B &=Clear_Prescaler_Bits;SET_BIT(TCCR1B,TCCR1B_CS10);CLR_BIT(TCCR1B,TCCR1B_CS11);CLR_BIT(TCCR1B,TCCR1B_CS12);break;
	case CLK_8: TCCR1B &=Clear_Prescaler_Bits;CLR_BIT(TCCR1B,TCCR1B_CS10);SET_BIT(TCCR1B,TCCR1B_CS11);CLR_BIT(TCCR1B,TCCR1B_CS12);break;
	case CLK_64: TCCR1B &=Clear_Prescaler_Bits;SET_BIT(TCCR1B,TCCR1B_CS10);SET_BIT(TCCR1B,TCCR1B_CS11);CLR_BIT(TCCR1B,TCCR1B_CS12);break;
	case CLK_256: TCCR1B &=Clear_Prescaler_Bits;CLR_BIT(TCCR1B,TCCR1B_CS10);CLR_BIT(TCCR1B,TCCR1B_CS11);SET_BIT(TCCR1B,TCCR1B_CS12);break;
	case CLK_1024: TCCR1B &=Clear_Prescaler_Bits;SET_BIT(TCCR1B,TCCR1B_CS10);CLR_BIT(TCCR1B,TCCR1B_CS11);SET_BIT(TCCR1B,TCCR1B_CS12);break;
	case Ext_ClkSource_Falling_Edge: TCCR1B &=Clear_Prescaler_Bits;CLR_BIT(TCCR1B,TCCR1B_CS10);SET_BIT(TCCR1B,TCCR1B_CS11);SET_BIT(TCCR1B,TCCR1B_CS12);break;
	case Ext_ClkSource_Rising_Edge: TCCR1B &=Clear_Prescaler_Bits;SET_BIT(TCCR1B,TCCR1B_CS10);SET_BIT(TCCR1B,TCCR1B_CS11);SET_BIT(TCCR1B,TCCR1B_CS12);break;
	default: Local_u8ErroState = NOK;break;
	}




	return Local_u8ErroState;
}

// Function to set the top value for Timer1
void Timer1_VoidSetTopVal(uint16 Copy_u16Val)
{
	ICR1 = Copy_u16Val;
}

// Function to set the Compare Match A value for Timer1
void Timer1_VoidSetComAVal(uint16 Copy_u16Val)
{
	OCR1A = Copy_u16Val;
}

// Function to set the Compare Match B value for Timer1
void Timer1_VoidSetComBVal(uint16 Copy_u16Val)
{
	OCR1B = Copy_u16Val;
}

// Function to configure the Compare Output Mode for Timer1 in Non-PWM mode
uint8 TIMER1_u8SetComNonPWM_Mode(Timer1_Com_OutMode_NonPWM_t Mode)
{
	uint8 Local_u8ErroState = OK;

	switch (Mode)
	{
	case T1_CHA_Disconnected_Non: break;
	case T1_CHB_Disconnected_Non: break;
	case T1_CHA_Toggle: SET_BIT(TCCR1A, TCCR1A_COM1A0); CLR_BIT(TCCR1A, TCCR1A_COM1A1); break;
	case T1_CHB_Toggle: SET_BIT(TCCR1A, TCCR1A_COM1B0); CLR_BIT(TCCR1A, TCCR1A_COM1B1); break;
	case T1_CHA_Clear: CLR_BIT(TCCR1A, TCCR1A_COM1A0); SET_BIT(TCCR1A, TCCR1A_COM1A1); break;
	case T1_CHB_Clear: CLR_BIT(TCCR1A, TCCR1A_COM1B0); SET_BIT(TCCR1A, TCCR1A_COM1B1); break;
	case T1_CHA_Set: SET_BIT(TCCR1A, TCCR1A_COM1A0); SET_BIT(TCCR1A, TCCR1A_COM1A1); break;
	case T1_CHB_Set: SET_BIT(TCCR1A, TCCR1A_COM1B0); SET_BIT(TCCR1A, TCCR1A_COM1B1); break;
	default: Local_u8ErroState = NOK; break; // Return error state if mode is invalid
	}

	return Local_u8ErroState;
}

// Function to configure Timer1 in Fast PWM mode
uint8 TIMER1_u8SetComFastPWM_Mode(Timer1_Com_OutMode_FastPWM_t Mode)
{
	uint8 Local_u8ErroState = OK;

	switch (Mode)
	{
	case T1_CHA_Disconnected_Fast: break;
	case T1_CHB_Disconnected_Fast: break;
	case T1_CHA_NormalPort_Fast: SET_BIT(TCCR1A, TCCR1A_COM1A0); CLR_BIT(TCCR1A, TCCR1A_COM1A1); break;
	case T1_CHB_NormalPort_Fast: SET_BIT(TCCR1A, TCCR1A_COM1B0); CLR_BIT(TCCR1A, TCCR1A_COM1B1); break;
	case T1_CHA_ClearOnCom_SetOnTop: CLR_BIT(TCCR1A, TCCR1A_COM1A0); SET_BIT(TCCR1A, TCCR1A_COM1A1); break;
	case T1_CHB_ClearOnCom_SetOnTop: CLR_BIT(TCCR1A, TCCR1A_COM1B0); SET_BIT(TCCR1A, TCCR1A_COM1B1); break;
	case T1_CHA_SetOnCom_ClearOnTop: SET_BIT(TCCR1A, TCCR1A_COM1A0); SET_BIT(TCCR1A, TCCR1A_COM1A1); break;
	case T1_CHB_SetOnCom_ClearOnTop: SET_BIT(TCCR1A, TCCR1A_COM1B0); SET_BIT(TCCR1A, TCCR1A_COM1B1); break;
	default: Local_u8ErroState = NOK; break;
	}

	return Local_u8ErroState;
}

// Function to configure Timer1 in Phase-Correct PWM mode
uint8 TIMER1_u8SetComPhaseCorPWM_Mode(Timer1_Com_OutMode_PhaseCorrrectPWM_t Mode)
{
	uint8 Local_u8ErroState = OK;

	switch (Mode)
	{
	case T1_CHA_Disconnected_Phase: break;
	case T1_CHB_Disconnected_Phase: break;
	case T1_CHA_NormalPort_Phase: SET_BIT(TCCR1A, TCCR1A_COM1A0); CLR_BIT(TCCR1A, TCCR1A_COM1A1); break;
	case T1_CHB_NormalPort_Phase: SET_BIT(TCCR1A, TCCR1A_COM1B0); CLR_BIT(TCCR1A, TCCR1A_COM1B1); break;
	case T1_CHA_ClearUpCounting_SetDownCounting: CLR_BIT(TCCR1A, TCCR1A_COM1A0); SET_BIT(TCCR1A, TCCR1A_COM1A1); break;
	case T1_CHB_ClearUpCounting_SetDownCounting: CLR_BIT(TCCR1A, TCCR1A_COM1B0); SET_BIT(TCCR1A, TCCR1A_COM1B1); break;
	case T1_CHA_SetUpCounting_ClearDownCounting: SET_BIT(TCCR1A, TCCR1A_COM1A0); SET_BIT(TCCR1A, TCCR1A_COM1A1); break;
	case T1_CHB_SetUpCounting_ClearDownCounting: SET_BIT(TCCR1A, TCCR1A_COM1B0); SET_BIT(TCCR1A, TCCR1A_COM1B1); break;
	default: Local_u8ErroState = NOK; break;
	}

	return Local_u8ErroState;
}

// Function to enable Timer1 interrupts
uint8 TIMER1_u8IntEnable(Timers_INT_Source_t Int_Type)
{
	uint8 Local_u8ErroState = OK;

	switch (Int_Type)
	{
	case T1_Ovf_Int: SET_BIT(TIMSK, TIMSK_TOIE1); break; // Enable Overflow Interrupt
	case T1_ComA_Int: SET_BIT(TIMSK, TIMSK_OCIE1A); break; // Enable Compare Match A Interrupt
	case T1_ComB_Int: SET_BIT(TIMSK, TIMSK_OCIE1B); break; // Enable Compare Match B Interrupt
	case T1_InpCapT_Int: SET_BIT(TIMSK, TIMSK_TICIE1); break; // Enable Input Capture Interrupt
	default: Local_u8ErroState = NOK; break;
	}

	return Local_u8ErroState;
}

// Function to disable Timer1 interrupts
uint8 TIMER1_u8IntDisable(Timers_INT_Source_t Int_Type)
{
	uint8 Local_u8ErroState = OK;

	switch (Int_Type)
	{
	case T1_Ovf_Int: CLR_BIT(TIMSK, TIMSK_TOIE1); break; // Disable Overflow Interrupt
	case T1_ComA_Int: CLR_BIT(TIMSK, TIMSK_OCIE1A); break; // Disable Compare Match A Interrupt
	case T1_ComB_Int: CLR_BIT(TIMSK, TIMSK_OCIE1B); break; // Disable Compare Match B Interrupt
	case T1_InpCapT_Int: CLR_BIT(TIMSK, TIMSK_TICIE1); break; // Disable Input Capture Interrupt
	default: Local_u8ErroState = NOK; break;
	}

	return Local_u8ErroState;
}

uint16 Timer1_u16GetTimerVal(void)
{
	return TCNT1 ;
}

void Timer1_VoidSetVal(uint16 Copy_u16Val)
{
	TCNT1 = Copy_u16Val ;
}




/*-----------------ICU------------------------*/
void ICU_voidInit(const Timer1_Cfg_t  *Timer1_Cfg)
{
	uint8 Local_u8ErroState = OK ;


	/*Set ICU trigger source */
	switch(Timer1_Cfg -> ICU_Trig_I_State)
	{
	case ICU_RAISING_EDGE: SET_BIT(TCCR1B , TCCR1B_ICES1); break;
	case ICU_FALLING_EDGE: CLR_BIT(TCCR1B , TCCR1B_ICES1); break;
	default: Local_u8ErroState = NOK; break;
	}

	/*Set ICU interrupt enable */
	SET_BIT(TIMSK,TIMSK_TICIE1);


}
uint8 ICU_u8SetTriggerEdge(uint8 Copy_u8Edge)
{
	uint8 Local_u8ErroState = OK;

	switch (Copy_u8Edge)
	{
	case ICU_RAISING_EDGE: SET_BIT(TCCR1B , TCCR1B_ICES1); break;
	case ICU_FALLING_EDGE: CLR_BIT(TCCR1B , TCCR1B_ICES1); break;
	default: Local_u8ErroState = NOK; break;
	}

	return Local_u8ErroState;
}


void ICU_voidEnableInterrupt(void)
{
	SET_BIT(TIMSK , TIMSK_TICIE1);
}
void ICU_voidDisableInterrupt(void)
{
	CLR_BIT(TIMSK , TIMSK_TICIE1);
}
uint16 ICU_u16GetReadingInputCaptureUnit(void)
{
	return ICR1;
}

uint16 Timer1_ICU_Cal_Time(uint16 Copy_u16Ticks_num , uint8 Copy_u8CLK_Prescaler)
{

	return (Copy_u16Ticks_num * (Copy_u8CLK_Prescaler/16));

}





/*set call back function for all timer interrupt sources */
uint8  Timers_SetCallBack(Timers_INT_Source_t Copy_INT_Source, void(*Copy_PvCallBackFunc)(void))
{
	uint8 Local_u8ErroState = OK;

	if (Copy_PvCallBackFunc != NULL)
	{
		Timer_CallBackFunc[Copy_INT_Source] = Copy_PvCallBackFunc;
	}
	else
	{
		Local_u8ErroState = NULL_PTR_ERR;
	}

	return Local_u8ErroState;
}


/*Timer0 overflow ISR*/
void __vector_11(void)__attribute__((signal));
void __vector_11(void)
{
	if(Timer_CallBackFunc[T0_Ovf_Int]!= NULL)
	{
		Timer_CallBackFunc[T0_Ovf_Int]();
	}
	else
	{

	}
}
/*Timer2 overflow ISR*/
void __vector_5(void)__attribute__((signal));
void __vector_5(void)
{
	if(Timer_CallBackFunc[T2_Ovf_Int]!= NULL)
	{
		Timer_CallBackFunc[T2_Ovf_Int]();
	}
	else
	{

	}
}
/*Timer0 Compare match interrupt*/
void __vector_10(void)__attribute__((signal));
void __vector_10(void)
{
	if(Timer_CallBackFunc[T0_2Com_Int]!= NULL)
	{
		Timer_CallBackFunc[T0_2Com_Int]();
	}
	else
	{

	}
}

/*Timer1 Input capture unit  interrupt*/
void __vector_6(void)__attribute__((signal));
void __vector_6(void)
{
	if(Timer_CallBackFunc[T1_InpCapT_Int]!= NULL)
	{
		Timer_CallBackFunc[T1_InpCapT_Int]();
	}
	else
	{

	}
}


