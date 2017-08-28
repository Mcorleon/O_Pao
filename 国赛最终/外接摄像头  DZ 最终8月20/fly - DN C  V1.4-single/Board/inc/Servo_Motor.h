/********************************S-D�������**********************************
*����   �� ɳ���Ѿ�
*�ļ��� �� Servo_Motor.c
*����   �� �������ͷ�ļ�
*ʱ��   �� 2015/10/30
*ʹ��˵���� 
              ��ɫ        GND
              ��ɫ        VCC
              ��ɫ        PWM
����Ƶ�ʣ�   300HZ    
*   
***************************************************************************/
#ifndef  _SERVO_MOTOR_H_
#define  _SERVO_MOTOR_H_

#include "include.h"



typedef struct servos_status
{
    float direction_p;                         //�������P����
    float direction_d;                         //�������D����
    int16  PID ;
    float direction_last_error;               //�����ϴ�ƫ��
    float diretion_current_error;             //����ǰƫ��
    int16 direction_duty_output;               //����������ռ�ձ�
    
}servos_status;

extern servos_status servos;


//���²���ΪFTM_PRECISON 10000u    ]��ռ�ձȾ���Ϊ10000ʱ����
#define   Servo_freq    50        //c���������Ƶ��Ϊ100HZ b��300
#define   Servo_ftm     FTM2      //FTMģ��
#define   Servo_CH      FTM_CH1       //ͨ�� 
#ifdef FIRSTCAR
#define   Servo_mid     790
#define   Servo_lmax    710
#define   Servo_rmax    868
#else  //ǰ��
#define   Servo_mid     821
#define   Servo_lmax    738//734
#define   Servo_rmax    904//908

#endif

/*
CI��ģ
����Ƶ��Ϊ100HZ
#define   Servo_mid     1290     // ���� С��
#define   Servo_lmax    1120     //
#define   Servo_rmax    1460     //
CI��ģ
����Ƶ��Ϊ150HZ
#define   Servo_mid     1930     // ���� С��
#define   Servo_lmax    1640     //
#define   Servo_rmax    2225     //
C��ģ
����Ƶ��Ϊ100HZ
#define   Servo_mid     1644//1480 ���� С��
#define   Servo_lmax    1470//1336      //��С�� 325 355   320
#define   Servo_rmax    1818//1630    //����ܵ� 555 585   555
C��ģ
����Ƶ��Ϊ50HZ
#define   Servo_mid     822
#define   Servo_lmax    735
#define   Servo_rmax    906
*/
void Servo_Motor_init(void);
void direction_control();


#endif  