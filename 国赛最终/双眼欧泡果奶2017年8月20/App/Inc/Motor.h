#ifndef   _MOTOR_H_
#define   _MOTOR_H_

#include "include.h"

typedef struct motor_status
{
    volatile int16 speed_L;                           //��ǰ�ٶ���
    volatile int16 speed_R;                           //��
    int16 speed_L_save[3];                   //��ǰ�ٶ���
    int16 speed_R_save[3];                   //��
    int16 speed_set;                         //�趨�ٶ�
    int16 speed_set_L;                       //�趨�ٶ���
    int16 speed_set_R;                       //�趨�ٶ���
    int16 last_speed_set_L;                  //�ϴ��ٶ�ƫ����
    int16 last_speed_set_R;                  //�ϴ��ٶ�ƫ����
    float speed_p;                           //�ٶȿ���P����
    float speed_i;                           //�ٶȿ���i����
//    float speed_p_R;                       //�ٶȿ���P������
//    float speed_i_R;                       //�ٶȿ���i������
    int16  speed_current_error_L;            //�ٶȵ�ǰƫ����
    int16  speed_last_error_L;               //�ٶ��ϴ�ƫ����
    int16  speed_duty_output_L;              //�ٶȿ������ռ�ձ���
    int16  speed_current_error_R;            //�ٶȵ�ǰƫ����
    int16  speed_last_error_R;               //�ٶ��ϴ�ƫ����
    int16  speed_duty_output_R;              //�ٶȿ������ռ�ձ���  
    int16  speed_filter_error[5];            //�ٶ��˲�������
//    int16  avg_speed;                        //ƽ���ٶ�

    int16 sigal_filter_error[5];

}motor_status;


extern motor_status motor;

/**************************************************************************
���ܣ�    ��ʼ�����Ŷ���
˵��:     ֱ���������IO�Ϳ����� 
ʱ�䣺    2015/11/2
*************************************************************************/
//#if Old_Motor
//����ǰ����FTMͨ��
//#define         L_GO_FTM     FTM3
//#define         L_GO_CH      FTM_CH6
////�������˵�FTMͨ��
//#define         L_BACK_FTM      FTM3
//#define         L_BACK_CH       FTM_CH5
////�ҵ��ǰ����FTMͨ��
//#define         R_GO_FTM     FTM3
//#define         R_GO_CH      FTM_CH4
////�ҵ�����˵�FTMͨ��
//#define         R_BACK_FTM      FTM3
//#define         R_BACK_CH       FTM_CH3
//#endif
//#if New_Motor
#define         L_GO_FTM     FTM3
#define         L_GO_CH      FTM_CH3
//�������˵�FTMͨ��
#define         L_BACK_FTM      FTM3
#define         L_BACK_CH       FTM_CH4
//�ҵ��ǰ����FTMͨ��
#define         R_GO_FTM     FTM3
#define         R_GO_CH      FTM_CH6
//�ҵ�����˵�FTMͨ��
#define         R_BACK_FTM      FTM3
#define         R_BACK_CH       FTM_CH5
//#endif
//�������Ƶ��
#define         MOTOR_FRE       10000//10000

#define         L_Speed_MAX  999
#define         L_Speed_MIN  -999
#define         R_Speed_MAX  999
#define         R_Speed_MIN  -999

//���������ʼ����ռ�ձ�   
#define INIT_DUTY   0

//���� ������ ����
//#define LEFT_ENCODER_DMA_CH       DMA_CH1          //�������������DMA�ɼ�ͨ��
//#define LEFT_ENCODER_COUNT        PTA9             //�������������DMA��������
//#define LEFT_ENCODER_DIRECTION    PTA8             //�������������DMA�ɼ���������
//#define RIGHT_ENCODER_DMA_CH      DMA_CH2          //�����ұ�������DMA�ɼ�ͨ��
//#define RIGHT_ENCODER_COUNT       PTA11            //�����ұ�������DMA��������
//#define RIGHT_ENCODER_DIRECTION   PTA10            //�����ұ�������DMA�ɼ���������

void myMotor_Setspeed(int16 PWM_L,int16 PWM_R);

void Motor_init(void);       //���������ʼ��
void speed_control1();       //�ٶȿ���
void speed_control2();
//void DMA_Speed_get();
void filter_speed_L();
void filter_speed_R();
void filter_Prospect_See();
void filter_Distance();
void Motor_protect();

typedef enum            //�������ͷ״̬
{
    Car_Single     = 1,
    Car_Double     = 2,
} Car_STATUS_e;

#endif