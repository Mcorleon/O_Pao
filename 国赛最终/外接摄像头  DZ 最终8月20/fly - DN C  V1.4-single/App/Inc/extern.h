/******************************************************************
*
*����   �� ɳ���Ѿ�
*�ļ��� �� extern.h
*����   �� ȫ�ֱ���ͷ�ļ�
*ʱ��   �� 2015/11/2
*
*****************************************************************************/
#ifndef  _EXTERN_H_
#define  _EXTERN_H_

#include "include.h"

extern uint8 host_flag ;                       //ǰ�󳵱�־ 0��ʾǰ��; 1��ʾ��
extern int8 CarGo ;                          //��λ
extern uint8 beep_flag ;
extern uint8 img_switch_flag;                      //ͼ���ַ�л���־ 
extern uint8 img_buffer[CAMERA_SIZE];              //ͼ�񻺴��ַһ
extern uint8 img_buffer2[CAMERA_SIZE];             //ͼ�񻺴��ַ��
extern uint8 img_handle[CAMERA_H][CAMERA_W];       //����ͼ����
extern int16 Lline[CAMERA_H];   //����������
extern int16 Rline[CAMERA_H];
extern int16 Mline[CAMERA_H];

extern int16  Track_complexity ;                //�������ӳ̶�
extern int16 Prospect_See ;                    //ǰհ
extern int16 Last_Prospect_See ;
extern int16 Distance;
extern int16 Last_Distance;


extern uint8 PID_Control_flag ;         //�ٶȿ���PID���ƿ�����־
extern uint8 Robust_Control_count;      //³�����Ƽ���
extern uint8 Robust_Control_flag;       //³�����Ʊ�־
extern uint8 Robust_Control_Sub_flag ;  
extern uint8 Car_Stop_flag;             //ͣ����־
extern uint8 Car_start_line;
extern int16 cartime;

extern uint8 LCDRAM[8][80];     //OLED��ʾ

extern uint8 stop ;                     //��������ͣ����־
extern uint8 oled_show_road_flag  ;      //oled�Ƿ�����־
extern uint8 img_send_flag ;            //ͼ���Ƿ��͵���λ��
extern uint8 img_save_flag ;            //ͼ���Ƿ���sd�������־

extern uint8 send_osc_flag ;             //�Ƿ��͵�����ʾ������־
extern uint8 img_send_flag ;            //ͼ���Ƿ��͵���λ��
extern uint8 img_sendmatlab_flag;
extern uint8 TFTShow_img_flag;
extern uint8 OLED_dis_flag;

//extern float voltage ;

extern uint16 servo_stop_duty ;              //ͣ�����ֹͣ���  

extern uint16 Time;

/************nrf*************/
extern uint8 nrf_rxbuff[DATA_PACKET];
extern uint8 nrf_txbuff[DATA_PACKET];
extern int8 nrf_rxbuff1[DATA_PACKET];
extern uint8 nrf_txbuff1[DATA_PACKET];

extern uint8 Ultrasonic_flag;
extern uint8 Front_flag ;//ǰ�󳵱�־λ0��1ǰ
extern uint8 Turn_state ;//ת��16������0��1��
extern uint8 Current_Turn_state;
extern uint8 Texting_state;//�ж�ת��16������
extern uint8 start_up;
extern int8 current_ring_state;
extern int8 last_ring_state;
extern uint8 HX_text;
//extern int8 Front_flag ;
//extern int8 Normal_Front_flag;
//extern int8 current_ring_state;
//extern int8 last_ring_state;
//extern int8 start_up;
//extern int8 to_turn;//0��ת��1��ת



#endif