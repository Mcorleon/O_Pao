/********************************�������**********************************
*
*����   �� ɳ���Ѿ�
*�ļ��� �� System.h
*����   �� ϵͳ��ʼ��ͷ�ļ�
*ʱ��   �� 2015/11/9
˵��    �� ʹ��ɽ��V5.3��
*
****************************************************************************/
#ifndef   _SYSTEM_H_
#define   _SYSTEM_H_

#include  "common.h"


//#define key1   PTB3_IN
//#define key2   PTB9_IN
//#define key3   PTB10_IN
//#define key4   PTB11_IN

void show_img(void);
void OLED_Show_Road(void);
void System_init(void);
void Buzzer_init(void); 
//void beepms(uint8 ms);//ʹ���ж�
void Caosheng_init();
void Key_init(void);  
void BM_init(void);
void RED_init(void);
//void Boot_reset(void);
void ADC_init(void);
//void beep(uint8 ms);
float Battery_voltage(void);
void beep();
void didi();

























#endif
