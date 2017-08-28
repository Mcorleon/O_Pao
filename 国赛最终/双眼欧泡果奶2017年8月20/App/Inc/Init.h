#ifndef   _INIT_H_
#define   _INIT_H_

void send_image();
void Set_vector();
void Init();
void Key_using();
void OLED_show();
extern uint8 Staup_Begin       ;
extern uint8 speed_level;

#define KEY1   PTD9_IN
#define KEY2   PTD6_IN
#define KEY3   PTD7_IN
#define KEY4   PTD4_IN
#define KEY5   PTD5_IN
#endif