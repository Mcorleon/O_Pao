#ifndef _DEFINE_H
#define _DEFINE_H

#define AvoidBlock    1 //�Ƿ���������ϰ�ģʽ
#define Blo_Slodown   1 //�Ƿ������ϰ�����ģʽ
#define MotProtection 0 //�Ƿ������������ģʽ
#define Emer_Turn     0 //�Ƿ�����ǿ�Ʒ���ģʽ
#define Single_run    1 //������
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
#define Double_run    1 //˫���Կ���
#endif


#if PID_Helix
#define PID_Regular 0
#else
#define PID_Regular 1
#endif


#define LEFT                    0
#define RIGHT                   255
//#define LOST_LIMIT             9   //����A��

//#define Turn_Speed              195  //B��
#define Straighten_Speed        220 //�����ٶ�
#define Security_Dis            60  //��ȫ��ţ���ֹ��ͻȻ����ת��ײ��Ŀ���
#define TUR_AVOIDBLO_LIMIT      30



#endif
