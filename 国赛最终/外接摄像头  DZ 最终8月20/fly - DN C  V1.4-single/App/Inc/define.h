/**********************************全局变量定义****************************
*文件名：  define.h
*说明：   全局变量定义
*时间：    2015/11/21
**************************************************************************/


#ifndef _DEFINE_H_
#define _DEFINE_H_

#include "include.h"


uint8 beep_flag = 1;
uint8 a=0;

int8 CarGo = 0 ;                           //档位
uint8 img_switch_flag = 0;                  //图像地址切换标志                        
uint8 img_buffer[CAMERA_SIZE];              //定义存储接收图像的数组
uint8 img_buffer2[CAMERA_SIZE];             //定义存储接收图像的另一数组    （乒乓算法实现交替存储）
uint8 img_handle[Data_Line][Data_Count];    //定义存储解压后要处理的图像的数组
int16 Lline[CAMERA_H];   //左右线数组
int16 Rline[CAMERA_H];
int16 Mline[CAMERA_H];

int16 Track_complexity ;                //赛道复杂程度
int16 Prospect_See ;                    //前瞻 
int16 Last_Prospect_See ;               //上一场的前瞻
int16 Distance=0 ;                   //距离
int16 Last_Distance=0 ;                  //上一场距离


uint8 Car_start_line=0;
uint8 Car_Stop_flag = 0;                //停车标志
int16 cartime=0;
uint8 Robust_Control_flag=0;            //鲁棒控制标志                
uint8 Robust_Control_count=0;

uint16 servo_stop_duty ;              //停车舵机停止打角
uint8 LCDRAM[8][80];

uint8 stop = 0;                       //蓝牙一键停车标志
uint8 oled_show_road_flag = 0 ;       //oled是否开启标志
uint8 img_send_flag = 0 ;             //图像是否发送到上位机
uint8 img_sendmatlab_flag = 0;
uint8 img_save_flag = 0 ;             //图像是否用sd卡保存标志
uint8 send_osc_flag = 0 ;             //是否发送到虚拟示波器标志
uint8 TFTShow_img_flag = 0 ;
uint8 OLED_dis_flag = 0 ;

float var[6];
//float voltage = 7.2;                          

extern IMG_STATUS_e  ov7725_eagle_img_flag;   //图像状态 

uint8 nrf_rxbuff[DATA_PACKET];
uint8 nrf_txbuff[DATA_PACKET];
int8 nrf_rxbuff1[DATA_PACKET];
uint8 nrf_txbuff1[DATA_PACKET];


uint8 Ultrasonic_flag = 0;//超声波信号标志位置
#ifdef FIRSTCAR//后
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
//int8 to_turn = 1;//0左转；1右转
  
#else  //前
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
// int8 to_turn = 0;//0左转；1右转
 
#endif


#endif