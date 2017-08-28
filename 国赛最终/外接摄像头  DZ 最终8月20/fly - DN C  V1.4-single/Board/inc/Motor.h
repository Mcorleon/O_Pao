/********************************�������**********************************
*
*����   �� ɳ���Ѿ�
*�ļ��� �� Motor.h
*����   �� �������ͷ�ļ�
*ʱ��   �� 2015/11/2
˵��    ���ο�let_it_go Դ����  ʹ��ɽ��V5.3��
*
****************************************************************************/
#ifndef   _MOTOR_H_
#define   _MOTOR_H_

#include "include.h"

typedef struct motor_status
{
    int16 speed_L;                           //��ǰ�ٶ���
    int16 speed_R;                           //��
    int16 speed_L_save[3];                      //��ǰ�ٶ���
    int16 speed_R_save[3];                      //��
    int16 speed_set;                         //�趨�ٶ�
    int16 speed_set_L;                       //�趨�ٶ���
    int16 speed_set_R;                       //�趨�ٶ���
    int16 last_speed_set_L;                  //�ϴ��ٶ�ƫ����
    int16 last_speed_set_R;                  //�ϴ��ٶ�ƫ����
    float speed_p;                           //�ٶȿ���P����
    float speed_i;                         //�ٶȿ���i����
//    float speed_p_R;                       //�ٶȿ���P������
//    float speed_i_R;                         //�ٶȿ���i������
    int16  speed_current_error_L;             //�ٶȵ�ǰƫ����
    int16  speed_last_error_L;                //�ٶ��ϴ�ƫ����
    int16  speed_duty_output_L;              //�ٶȿ������ռ�ձ���
    int16  speed_current_error_R;             //�ٶȵ�ǰƫ����
    int16  speed_last_error_R;                //�ٶ��ϴ�ƫ����
    int16  speed_duty_output_R;              //�ٶȿ������ռ�ձ���  
    int16  speed_filter_error[3];          //�ٶ��˲�������
    int16  avg_speed;                         //ƽ���ٶ�
}motor_status;


extern motor_status motor;

/**************************************************************************
���ܣ�    ��ʼ�����Ŷ���
˵��:     ֱ���������IO�Ϳ����� 
ʱ�䣺    2015/11/2
*************************************************************************/
#ifdef FIRSTCAR//c1��

//����ǰ����FTMͨ��
#define         L_GO_FTM     FTM0
#define         L_GO_CH      FTM_CH4
//�������˵�FTMͨ��
#define         L_BACK_FTM      FTM0
#define         L_BACK_CH       FTM_CH5
//�ҵ��ǰ����FTMͨ��
#define         R_GO_FTM     FTM0
#define         R_GO_CH      FTM_CH6
//�ҵ�����˵�FTMͨ��
#define         R_BACK_FTM      FTM0
#define         R_BACK_CH       FTM_CH7

#else     //c��

//����ǰ����FTMͨ��
#define         L_GO_FTM     FTM0
#define         L_GO_CH      FTM_CH4
//�������˵�FTMͨ��
#define         L_BACK_FTM      FTM0
#define         L_BACK_CH       FTM_CH5
//�ҵ��ǰ����FTMͨ��
#define         R_GO_FTM     FTM0
#define         R_GO_CH      FTM_CH6
//�ҵ�����˵�FTMͨ��
#define         R_BACK_FTM      FTM0
#define         R_BACK_CH       FTM_CH7

#endif


//�������Ƶ��
#define         MOTOR_FRE       15000//10000


#ifdef FIRSTCAR

#define         L_Speed_MAX  999
#define         L_Speed_MIN  -999
#define         R_Speed_MAX  999
#define         R_Speed_MIN  -999

#else

#define         L_Speed_MAX  1000
#define         L_Speed_MIN  -1000
#define         R_Speed_MAX  1000
#define         R_Speed_MIN  -1000

#endif

//���������ʼ����ռ�ձ�   
#define INIT_DUTY   0

//���� ������ ����
#define LEFT_ENCODER_DMA_CH       DMA_CH1          //�������������DMA�ɼ�ͨ��
#define LEFT_ENCODER_COUNT        PTB9             //�������������DMA��������
#define LEFT_ENCODER_DIRECTION    PTB8             //�������������DMA�ɼ���������
#define RIGHT_ENCODER_DMA_CH      DMA_CH2          //�����ұ�������DMA�ɼ�ͨ��
#define RIGHT_ENCODER_COUNT       PTC12            //�����ұ�������DMA��������
#define RIGHT_ENCODER_DIRECTION   PTC13            //�����ұ�������DMA�ɼ���������


void myMotor_Setspeed(int16 PWM_L,int16 PWM_R);

void Motor_init(void) ;      //���������ʼ��
void speed_control();        //�ٶȿ���
void DMA_Speed_get();
void filter_speed_L();
void filter_speed_R();
void filter_Prospect_See();
void filter_Distance();











#endif