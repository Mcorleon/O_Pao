#ifndef _DEFINE_H
#define _DEFINE_H

#define AvoidBlock    1 //是否启动躲避障碍模式
#define Blo_Slodown   1 //是否启动障碍减速模式
#define MotProtection 0 //是否启动电机保护模式
#define Emer_Turn     0 //是否启动强制方向模式
#define Single_run    1 //单车跑
#define Blo_NearDealy 0
#define PID_Helix     0
#define New_Motor     0


#if New_Motor
#define Old_Motor     1
#else
#define Old_Motor     0
#endif
#if Single_run
#define Double_run    0
#else
#define Double_run    1 //双车对抗跑
#endif


#if PID_Helix
#define PID_Regular 0
#else
#define PID_Regular 1
#endif


#define LEFT                    0
#define RIGHT                   255
//#define LOST_LIMIT             9   //国赛A档

//#define Turn_Speed              195  //B档
#define Straighten_Speed        220 //摆正速度
#define Security_Dis            60  //安全打脚，防止灯突然被抢转弯撞到目标灯
#define TUR_AVOIDBLO_LIMIT      30



#endif
