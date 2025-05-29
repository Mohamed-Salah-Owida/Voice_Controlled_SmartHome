#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

/* Function to send a command to the Character LCD module */
void CLCD_VoidSendCmd(uint8 Copy_u8Cmd);

/* Function to send data to the Character LCD module */
void CLCD_VoidSendData(uint8 Copy_u8Data);

/* Function to initialize or configure the Character LCD module */
void CLCD_VoidInit(void);

/* Function to send a null-terminated string to the Character LCD module */
uint8 CLCD_u8SendString(const char* Copy_pchString);

/* Function to send a signed 32-bit integer to the Character LCD module */
void CLCD_VoidSendNumber(sint32 Copy_s32Number);

void CLCD_voidGoToXY(uint8 Copy_u8XPos , uint8 Copy_u8YPos);

uint8 CLCD_u8SendSpecialCharacter(uint8 Copy_u8LocationNnm , uint8* Copy_pu8Pattern, uint8 Copy_u8XPos, uint8 Copy_u8YPos);


#endif
