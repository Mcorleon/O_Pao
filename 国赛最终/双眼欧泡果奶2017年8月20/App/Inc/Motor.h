#ifndef   _MOTOR_H_
#define   _MOTOR_H_

#include "include.h"

typedef struct motor_status
{
    volatile int16 speed_L;                           //当前速度左
    volatile int16 speed_R;                           //右
    int16 speed_L_save[3];                   //当前速度左
    int16 speed_R_save[3];                   //右
    int16 speed_set;                         //设定速度
    int16 speed_set_L;                       //设定速度左
    int16 speed_set_R;                       //设定速度右
    int16 last_speed_set_L;                  //上次速度偏差左
    int16 last_speed_set_R;                  //上次速度偏差右
    float speed_p;                           //速度控制P参数
    float speed_i;                           //速度控制i参数
//    float speed_p_R;                       //速度控制P参数右
//    float speed_i_R;                       //速度控制i参数右
    int16  speed_current_error_L;            //速度当前偏差左
    int16  speed_last_error_L;               //速度上次偏差左
    int16  speed_duty_output_L;              //速度控制输出占空比左
    int16  speed_current_error_R;            //速度当前偏差右
    int16  speed_last_error_R;               //速度上次偏差右
    int16  speed_duty_output_R;              //速度控制输出占空比右  
    int16  speed_filter_error[5];            //速度滤波数组左
//    int16  avg_speed;                        //平均速度

    int16 sigal_filter_error[5];

}motor_status;


extern motor_status motor;

/**************************************************************************
功能：    初始化引脚定义
说明:     直接在这里改IO就可以了 
时间：    2015/11/2
*************************************************************************/
//#if Old_Motor
//左电机前进的FTM通道
//#define         L_GO_FTM     FTM3
//#define         L_GO_CH      FTM_CH6
////左电机后退的FTM通道
//#define         L_BACK_FTM      FTM3
//#define         L_BACK_CH       FTM_CH5
////右电机前进的FTM通道
//#define         R_GO_FTM     FTM3
//#define         R_GO_CH      FTM_CH4
////右电机后退的FTM通道
//#define         R_BACK_FTM      FTM3
//#define         R_BACK_CH       FTM_CH3
//#endif
//#if New_Motor
#define         L_GO_FTM     FTM3
#define         L_GO_CH      FTM_CH3
//左电机后退的FTM通道
#define         L_BACK_FTM      FTM3
#define         L_BACK_CH       FTM_CH4
//右电机前进的FTM通道
#define         R_GO_FTM     FTM3
#define         R_GO_CH      FTM_CH6
//右电机后退的FTM通道
#define         R_BACK_FTM      FTM3
#define         R_BACK_CH       FTM_CH5
//#endif
//电机驱动频率
#define         MOTOR_FRE       10000//10000

#define         L_Speed_MAX  999
#define         L_Speed_MIN  -999
#define         R_Speed_MAX  999
#define         R_Speed_MIN  -999

//电机驱动初始化的占空比   
#define INIT_DUTY   0

//配置 编码器 参数
//#define LEFT_ENCODER_DMA_CH       DMA_CH1          //定义左编码器的DMA采集通道
//#define LEFT_ENCODER_COUNT        PTA9             //定义左编码器的DMA计数引脚
//#define LEFT_ENCODER_DIRECTION    PTA8             //定义左编码器的DMA采集正负引脚
//#define RIGHT_ENCODER_DMA_CH      DMA_CH2          //定义右编码器的DMA采集通道
//#define RIGHT_ENCODER_COUNT       PTA11            //定义右编码器的DMA计数引脚
//#define RIGHT_ENCODER_DIRECTION   PTA10            //定义右编码器的DMA采集正负引脚

void myMotor_Setspeed(int16 PWM_L,int16 PWM_R);

void Motor_init(void);       //电机驱动初始化
void speed_control1();       //速度控制
void speed_control2();
//void DMA_Speed_get();
void filter_speed_L();
void filter_speed_R();
void filter_Prospect_See();
void filter_Distance();
void Motor_protect();

typedef enum            //外接摄像头状态
{
    Car_Single     = 1,
    Car_Double     = 2,
} Car_STATUS_e;

#endif