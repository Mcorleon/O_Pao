#ifndef  _SERVO_MOTOR_H_
#define  _SERVO_MOTOR_H_

#include "include.h"
typedef struct servos_status
{
    float direction_p;                         //�������P����
    float direction_d;                         //�������D����
    float direction_last_error;                //�����ϴ�ƫ��
    float diretion_current_error;              //����ǰƫ��
    int16 direction_duty_output;               //����������ռ�ձ�
    
}servos_status;

typedef enum
{
    Sig_Chasing = 1,
    Sig_Finished=2,
    Sig_Missing = 3,
} Sig_STATUS_e;
typedef enum
{
    Blo_Founded = 1,
    Blo_Missing = 2,
    Blo_Delaying= 3,
} Blo_STATUS_e;
typedef enum            //������״̬
{
    Inf_Ready     = 1,
    Inf_Finished  = 2,
} Inf_STATUS_e;
typedef enum            //�������ͷ״̬
{
    Camer_Ready     = 1,
    Camer_Finished  = 2,
} Camer_STATUS_e;
typedef enum            //�������ͷ״̬
{
    Judge_Ready     = 1,
    Judge_Finished  = 2,
} Judge_STATUS_e;
extern servos_status servos;
#define   Servo_freq     50                   //�������Ƶ��Ϊ50HZ
#define   Servo_ftm     FTM0                   //FTMģ��
#define   Servo_CH      FTM_CH3                //ͨ�� 
#define   Servo_mid     718//727//1455//1520                   //��ֵ  435  470   
#define   Servo_rmax   793//1615                   //��С�� 345 355 1325
#define   Servo_lmax    643//650//1300                   //����ܵ� 525 585 1665  
void Servo_Motor_init()     ;
void direction_control()    ;
void Single_Infra_Sensor()  ;
void Double_Infra_Sensor()  ;
void Blo_DelayFunction()    ;
void Single_DevGiving()     ;
void Double_DevGiving()     ;
void Sig_FuzRow_Collection();
void NorDirection_Chosse()  ;
void Sig_STATE_Judgement()  ;
void Level_Detection()      ;
void TurAvoidBlock_Delay()  ;
void LOST_LIMIT_Judging()   ;
int16 Nor_ChosseDev()       ;
int16 PID_generator_Helix(uint8 Direction,float Space,float MAXNUM,int16 LasValue);
int16 PID_generator_Regular(uint8 Direction,float Space,float MAXNUM,int16 LasValue);
/*************************************************ͼ�������ݴ�����*******/

/*************************************************ͼ�������ݴ�����*******/
#endif