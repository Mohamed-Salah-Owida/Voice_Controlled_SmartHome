#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H


typedef enum
{
	ACTIVE_H = 1u,
	ACTIVE_L = 2u
}LED_Activity_t;

typedef struct
{
	uint8 PORT ;
	uint8 PIN  ;
	LED_Activity_t ActivityType;

}LED_cfg_t;



uint8 LED_u8SetON(const LED_cfg_t* Copy_pstCfg);
uint8 LED_u8SetOFF(const LED_cfg_t* Copy_pstCfg);
uint8 LED_u8Toggle(const LED_cfg_t* Copy_pstCfg);



#endif
