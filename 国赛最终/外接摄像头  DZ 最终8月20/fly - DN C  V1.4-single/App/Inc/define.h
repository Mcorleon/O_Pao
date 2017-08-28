/**********************************ȫ�ֱ�������****************************
*�ļ�����  define.h
*˵����   ȫ�ֱ�������
*ʱ�䣺    2015/11/21
**************************************************************************/


#ifndef _DEFINE_H_
#define _DEFINE_H_

#include "include.h"


uint8 beep_flag = 1;
uint8 a=0;

int8 CarGo = 0 ;                           //��λ
uint8 img_switch_flag = 0;                  //ͼ���ַ�л���־                        
uint8 img_buffer[CAMERA_SIZE];              //����洢����ͼ�������
uint8 img_buffer2[CAMERA_SIZE];             //����洢����ͼ�����һ����    ��ƹ���㷨ʵ�ֽ���洢��
uint8 img_handle[Data_Line][Data_Count];    //����洢��ѹ��Ҫ�����ͼ�������
int16 Lline[CAMERA_H];   //����������
int16 Rline[CAMERA_H];
int16 Mline[CAMERA_H];

int16 Track_complexity ;                //�������ӳ̶�
int16 Prospect_See ;                    //ǰհ 
int16 Last_Prospect_See ;               //��һ����ǰհ
int16 Distance=0 ;                   //����
int16 Last_Distance=0 ;                  //��һ������


uint8 Car_start_line=0;
uint8 Car_Stop_flag = 0;                //ͣ����־
int16 cartime=0;
uint8 Robust_Control_flag=0;            //³�����Ʊ�־                
uint8 Robust_Control_count=0;

uint16 servo_stop_duty ;              //ͣ�����ֹͣ���
uint8 LCDRAM[8][80];

uint8 stop = 0;                       //����һ��ͣ����־
uint8 oled_show_road_flag = 0 ;       //oled�Ƿ�����־
uint8 img_send_flag = 0 ;             //ͼ���Ƿ��͵���λ��
uint8 img_sendmatlab_flag = 0;
uint8 img_save_flag = 0 ;             //ͼ���Ƿ���sd�������־
uint8 send_osc_flag = 0 ;             //�Ƿ��͵�����ʾ������־
uint8 TFTShow_img_flag = 0 ;
uint8 OLED_dis_flag = 0 ;

float var[6];
//float voltage = 7.2;                          

extern IMG_STATUS_e  ov7725_eagle_img_flag;   //ͼ��״̬ 

uint8 nrf_rxbuff[DATA_PACKET];
uint8 nrf_txbuff[DATA_PACKET];
int8 nrf_rxbuff1[DATA_PACKET];
uint8 nrf_txbuff1[DATA_PACKET];


uint8 Ultrasonic_flag = 0;//�������źű�־λ��
#ifdef FIRSTCAR//��
uint8 Front_flag = 0;
uint8 Turn_state = ~L_or_R;//10101010
uint8 Current_Turn_state = 0x00;
uint8 Texting_state = 0x01;
uint8 start_up = 0;
int8 current_ring_state = 0;
int8 last_ring_state = 0;
uint8 HX_text=0;

//int8 Front_flag = 0;
//int8 Normal_Front_flag = 0;
//int8 current_ring_state = 0;
//int8 last_ring_state = 0;
//int8 start_up = 0;
//int8 to_turn = 1;//0��ת��1��ת
  
#else  //ǰ
uint8 Front_flag = 255;
uint8 Turn_state = L_or_R;//01010101
uint8 Current_Turn_state = 0x00;
uint8 Texting_state = 0x01;
uint8 start_up = 0;
int8 current_ring_state = 0;
int8 last_ring_state = 0;
uint8 HX_text=0;
// int8 Front_flag = 1;
// int8 Normal_Front_flag = 1;
// int8 current_ring_state = 0;
// int8 last_ring_state = 0;
// int8 start_up = 0;
// int8 to_turn = 0;//0��ת��1��ת
 
#endif


#endif