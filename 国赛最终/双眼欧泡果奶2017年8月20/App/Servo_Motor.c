#include "Servo_Motor.h"
//servos_status servos;
/********************���Ӷ�̬D�޸�3************************************/
/********************���Ӷ�̬D�޸�3************************************/
/********************���Ӷ�̬D�޸�3************************************/
int16 sigal_Lline_normal[120]= {
 83, 82, 82, 81, 81, 80, 80, 79, 79, 78, 78, 77, 77, 76, 76, 75, 75, 74, 74, 73, 72, 72, 71, 71, 70, 70, 69, 69, 68, 68, 67, 67, 66, 66, 65, 65, 64, 64, 63, 63, 62, 62, 61, 61, 60, 60, 59, 59, 58, 58, 57, 57, 56, 56, 55, 55, 54, 54, 53, 53, 52, 52, 51, 51, 50, 50, 49, 49, 48, 48, 47, 47, 46, 46, 45, 45, 44, 44, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 38, 38, 37, 37, 36, 36, 35, 35, 34, 34, 33, 33, 32, 32, 31, 31, 30, 30, 29, 29, 28, 28, 27, 27, 26, 26, 25, 25, 24, 24, 23, 23
};
int16 sigal_Rline_normal[120]= {
76, 77, 77, 78, 78, 79, 79, 80, 80, 81, 81, 82, 82, 83, 83, 84, 84, 85, 85, 86, 87, 87, 88, 88, 89, 89, 90, 90, 91, 91, 92, 92, 93, 93, 94, 94, 95, 95, 96, 96, 97, 97, 98, 98, 99, 99,100,100,101,101,102,102,103,103,104,104,105,105,106,106,107,107,108,108,109,109,110,110,111,111,112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,119,120,120,121,121,122,122,123,123,124,124,125,125,126,126,127,127,128,128,129,129,130,130,131,131,132,132,133,133,134,134,135,135,136,136
};
int16 block_Lline[120]       = {
41, 40, 40, 39, 39, 39, 38, 38, 37, 37,
36, 36, 35, 35, 34, 34, 33, 33, 32, 32,
31, 31, 30, 30, 29, 29, 28, 28, 27, 27,
26, 26, 25, 25, 24, 24, 23, 23, 22, 22,
21, 21, 20, 20, 19, 19, 18, 18, 17, 17,
16, 16, 15, 15, 14, 14, 13, 13, 12, 12,
11, 11, 10, 10,  9,  9,  8,  8,  7,  7, 
 6,  6,  5,  5,  4,  4,  3,  3,  2,  2,
 2,  1,  1, 0 , 0 , 0 , 0 , -1, -1, -2,
-2, -3, -3, -4, -4, -5, -5, -6, -6, -7,
-7, -8, -8, -9, -9,-10,-10,-11,-11,-12,
-12,-13,-13,-14,-14,-15,-15,-16,-16,-17
};
int16 block_Rline[120]       = {
118,119,119,120,120,120,121,121,122,122,
123,123,124,124,125,125,126,126,127,127,
128,128,129,129,130,130,131,131,132,132,
133,133,134,134,135,135,136,136,137,137,
138,138,139,139,140,140,141,141,142,142,
143,143,144,144,145,145,146,146,147,147,
148,148,149,149,150,150,151,151,152,152,
153,153,154,154,155,155,156,156,157,157,
157,158,158,159,159,159,159,160,160,161,
161,162,162,163,163,164,164,165,165,166,
166,167,167,168,168,169,169,170,170,171,
171,172,172,173,173,174,174,175,175,176
};
int16 Rev_Vision_Line[160]   = {
37, 37, 37, 37, 36, 36, 36, 36, 35, 35,
35, 35, 34, 34, 34, 34, 34, 33, 33, 33,
33, 33, 32, 32, 32, 32, 32, 31, 31, 31,
31, 31, 31, 30, 30, 30, 30, 30, 30, 29,
29, 29, 29, 29, 29, 29, 28, 28, 28, 28,
28, 28, 28, 28, 28, 27, 27, 27, 27, 27, 
27, 27, 27, 27, 27, 26, 26, 26, 26, 26, 
26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
26, 26, 26, 26, 26, 27, 27, 27, 27, 27,
27, 27, 27, 27, 27, 28, 28, 28, 28, 28,
28, 28, 28, 28, 29, 29, 29, 29, 29, 29,
29, 30, 30, 30, 30, 30, 30, 31, 31, 31,
31, 31, 31, 32, 32, 32, 32, 32, 33, 33,
33, 33, 33, 34, 34, 34, 34, 34, 35, 35,
35, 35, 36, 36, 36, 36, 37, 37, 37, 37
};
int16 FuzRow_REV_LOSTLIMIT[120]={
7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
7,  7,  8,  8,  8,  8,  9,  9,  9, 10,
10, 10, 10, 11, 11, 11, 12, 12, 12, 13,
13, 13, 14, 14, 15, 15, 15, 16, 16, 16,
16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 
16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 
16, 16, 16, 16, 16, 16, 16, 16, 16, 16
};//�ݶ����ٵ�λ
int16 FuzRow_REV_LOSTLIMIT_A[120]={
6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7,  7,  7,  7,  7,  8,  8,  8,  8,  9,  9,  9, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11
};
int16 FuzForced_TurDirection[120]={
38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 
38, 39, 40, 41, 42, 43, 43, 44, 45, 46,
48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 
60, 60, 60, 60, 60, 60, 60, 60, 60, 60,
60, 60, 60, 60, 60, 60, 60, 60, 60, 60,
60, 60, 60, 60, 60, 60, 60, 60, 60, 60,
60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 
60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 
60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 
60, 60, 60, 60, 60, 60, 60, 60, 60, 60,
60, 60, 60, 60, 60, 60, 60, 60, 60, 60
};

int16 LOST_LIMIT             =  0;
//int16 block_Lline[120]       ={50,50,49,49,49,48,48,48,47,47,47,47,46,46,46,45,45,45,44,44,44,44,43,43,43,42,42,42,41,41,41,41,40,40,40,39,39,39,38,38,38,37,37,37,37,36,36,36,35,35,35,34,34,34,34,33,33,33,32,32,32,31,31,31,30,30,30,30,29,29,29,28,28,28,27,27,27,27,26,26,26,25,25,25,24,24,24,24,23,23,23,22,22,22,21,21,21,20,20,20,20,19,19,19,18,18,18,17,17,17,17,16,16,16,15,15,15,14,14,14};
//int16 block_Rline[120]       ={109,109,110,110,110,111,111,111,112,112,112,112,113,113,113,114,114,114,115,115,115,115,116,116,116,117,117,117,118,118,118,118,119,119,119,120,120,120,121,121,121,122,122,122,122,123,123,123,124,124,124,125,125,125,125,126,126,126,127,127,127,128,128,128,129,129,129,129,130,130,130,131,131,131,132,132,132,132,133,133,133,134,134,134,135,135,135,135,136,136,136,137,137,137,138,138,138,139,139,139,139,140,140,140,141,141,141,142,142,142,142,143,143,143,144,144,144,145,145,145};
int16 PID                    =  0;   
int32 Divide_count           =  0;
uint8 NorDirection           =  0;
uint8 TurDirection           =  0; //����ɺ���Թܾ���   0��1��
int16  Mov_dev               =  5;  //����� �ó���·���������ű�ƻ���Զ���ű��
int16  Movblo_dev            =  0;  //������ó��ܿ�·�ϵ�·���������ƻ���Զ���
int16 Spec_BloDev            =-30;  
int16 real_deviation         =  0;  //������������������ƫ��
int16 deviation              =  0;  
int16 Last_deviation         =  0;  //��һ����ƫ��
int16 direction_duty_output  =  0; //���ռ�ձ�
int16 LasLook_deviation      =  0; //��������ӿ����� ��ͻȻ������һ˲�� ��һ����ƫ��
uint8 Forced_Turdirection    =  0; //ǿ�ƴ�� ��ֹ������ת��ײ�Ƶ����
int8  Block_Judmid           =  0;  //������ϰ�����ջ����ҹյ����߷�ˮ��
int8  Sta_Count              =  0; //�������ƺ� ���а˸����ڵĺ������õļ���
int16 Sig_FuzzyRow           =  0;
uint8 Las_Sig_STATE          =  0;
int16 Las_Blo_Dev            =  0;   //�������ʱ���ϵ����һ��ƫ��
uint8 Blo_AgreeDelay         =  0;   //��������б�����ʱ�Ĳ���
uint8 Las_Blo_STATE          =  0;
int16 Sig_Ciring_flag        =  0;
uint8 Tur_AvoidBlo_flag      =  0;
int16 Tur_AvoidBlo_count     =  0;
float Direction_P           = 0.8;
extern int16 Sig_MidLine         ;
extern uint8 Staup_Begin         ;
extern int16 Blo_MidLine         ;
extern  int8 Sig_row             ;
extern uint8 Sig_permit          ;
extern uint8 Block_ComLeft       ;
extern uint8 Block_ComRight      ;
extern int8  Blo_row             ;
extern int32 Lost_flag           ;
extern Dis_STATUS_e Dis_STATE    ;

extern int16 Light_RecLeft       ;
extern int16 Light_RecRight      ;

extern uint8 Las_Dis_STATE       ;
extern uint8 Las_Sigpermit       ;
extern int8  Light_SecLeft       ;
extern int8  Light_SecRight      ;

extern uint8 Blo_Delay_Left      ;
extern uint8 Blo_Delay_Right     ;
extern int8  Blo_Delay           ;   //����Ǳ�����ʱ�ı�־λs 
extern int16 Blo_Delay_Count     ;
extern int16 Sig_Fuz_Row_1       ;
extern int16 Sig_Fuz_Row_2       ;
extern int16 Sig_Fuz_Row_3       ;
extern int16 Sig_Fuz_Row_4       ;
extern int16 Sig_Fuz_Row_5       ;
extern int16 Sig_Fuz_Row_6       ;
int16  Block_deviation;
int16 Sig_deviation   ;
int16 Blo_AgrDelay_Count          ;
int16 Block_DelDev                ;
//int16 Servo_rmax  =  1660                   //��С�� 345 355 1325
// int16  Servo_lmax   = 1360                   //����ܵ� 525 585 1665  
//����Ǳ�����ʱ�ĵ�������
uint8 Enter_Blo_ComLeft      = 0  ;
uint8 Enter_Blo_ComRight     = 0  ;
extern int16 var[8]              ;
float Servo_Space = Servo_rmax-Servo_mid;
float temporary             = 0.0;
float MAX_DIVNUM            =10.0;
Sig_STATUS_e    Sig_STATE   =  Sig_Finished   ;
Inf_STATUS_e    Inf_STATE   =  Inf_Finished   ;
Blo_STATUS_e    Blo_STATE   =  Blo_Missing    ;
Fuz_STATUS_e    Fuz_STATE   =  Fuz_RecReady   ;
Camer_STATUS_e  Camer_STATE =  Camer_Finished ;
Judge_STATUS_e  Judge_STATE =  Judge_Finished ;
void Servo_Motor_init(void){
    ftm_pwm_init(Servo_ftm,Servo_CH,Servo_freq,Servo_mid );  
}
void direction_control(){
#if Single_run
  Single_DevGiving();
#endif
  if(!Las_Sigpermit&&Sig_permit)
    Divide_count=0;
  if(real_deviation==0&&Sig_STATE==Sig_Finished){
#if PID_Helix
    PID = PID_generator_Helix(TurDirection,Servo_Space,MAX_DIVNUM,PID);
#endif
#if PID_Regular
    PID = PID_generator_Regular(TurDirection,Servo_Space,MAX_DIVNUM,PID);
#endif
    if(Divide_count> (int32)MAX_DIVNUM)
      Divide_count = (int32)MAX_DIVNUM;
  }
  else  
    PID = (int16)(Direction_P*real_deviation);
  if(PID>Servo_Space)
    PID=(int16) Servo_Space;
  if(PID<-Servo_Space)
    PID=(int16)-Servo_Space;
if(Staup_Begin==0)
  PID=0;
  direction_duty_output = PID+Servo_mid;

  if(direction_duty_output<Servo_lmax)
    direction_duty_output=Servo_lmax;
  else if(direction_duty_output>Servo_rmax)
    direction_duty_output=Servo_rmax;

  ftm_pwm_duty(Servo_ftm,Servo_CH,direction_duty_output);
  
}


/********************************
*@author:�����
*@Function:����ѡ��ƫ��
*@description:��δ��װ���(�����)
********************************/
void Single_DevGiving()
{
/*******************************************
*�ж�Sig_STATE
*�ű�Ƶ�״̬�ٷ��֢��쳣��ʧ��������ʧ
*******************************************/
  Las_Sig_STATE = Sig_STATE;
  Sig_STATE_Judgement();
  TurAvoidBlock_Delay();
#if AvoidBlock
/************************************************************
*�жϢ�Blo_STATE   �ڵó�Sig_chosse  �۵ó�Block_Left/Block_Right
*�ϰ��Ƶ�״̬�ٷ��֢ڶ�ʧ
************************************************************/
  
    Las_Blo_STATE = Blo_STATE;
    if(Blo_STATE == Blo_Missing)
      BloNor_JudAppear()   ;
    else if(Blo_STATE == Blo_Founded)              //����ҵ�Զ���ϰ�
      BloNor_JudDisappear();                       //�����ϰ�ȡ��ģʽ���ﵽ������ȡ���ϰ�

/*************************************
*�ó�NorDirection
*************************************/
   NorDirection_Chosse();//ѡ���ߵ������ߵ���

#endif
/***********************
*����״̬�����ʵ���ƫ��
************************/
 real_deviation = Nor_ChosseDev();                    //���ݴ�ʱԶ�����ϣ���������Ѱ���ű�ƣ�ѡ��ƫ��
 Sig_FuzRow_Collection();
}


/************************
*@author:�����
*�������ж���ʱ��������
*@description:��װ���(�Ѽ��) ���ò���
************************/
void Blo_DelayFunction()
{
//����Ƕ���ԭ����ת״̬,�����ǽӽ��ű��״̬,����ת�Ƿ����ѡ���ߵƵ���߻����ұߵķ���һ��
    if(Sig_STATE==Sig_Finished&&Dis_STATE==Dis_Clo)
      Blo_AgreeDelay = 1;
    //������������Ѱ���ϰ��Ƶ�����£���������Զ����ʼ�����ϣ�
    //����һ˲���⵽�˷��Ͻ����ϰ���·�����  �����ӳٱ��ϱ�־����
    if((Blo_Delay_Left||Blo_Delay_Right)&&Blo_AgreeDelay){//����ҵ��˽������ϰ�Ȼ����������ʱ������
      Blo_AgreeDelay=0;
      Blo_STATE = Blo_Delaying;
      Blo_AgrDelay_Count=0;
    }
    if((!Las_Sigpermit&&Sig_permit&&Blo_AgreeDelay)||Blo_AgrDelay_Count){//��һ���������� ��һ�������˵�
        Blo_AgrDelay_Count++;
        if(Blo_AgrDelay_Count>22){
          Blo_AgrDelay_Count=0;    //mark
          Blo_AgreeDelay =0;            
          Blo_Delay_Left =0;
          Blo_Delay_Right=0;
        }
    }
    if(Blo_STATE==Blo_Delaying)//������ӳ�״̬
    {
      Blo_Delay_Count++;
      if(Blo_Delay_Count>7){//�ӳ�ʱ�䵽 һ�й�0 ���ұ���״̬Ϊ��������
        Blo_Delay_Count=0;
        Blo_STATE=Blo_Missing;
        Blo_Delay_Left=0;
        Blo_Delay_Right=0;
      }
    }

}












/********************************
*@author:�����
*@Function:�����ڴ��PID����
*description:��װ��ϣ��Ѽ�⣩ ������
********************************/
int16 PID_generator_Helix(uint8 Direction,float Space,float MAXNUM,int16 LasValue)
{
   float Scr_Limit = 0;
   float temp       = 0;
   int16  FinValue   = 0;
     if(Lost_flag<30&&Lost_flag){
       Scr_Limit = Space;}
     else{
       Scr_Limit = Space - 30;
     }
    if(!Divide_count){
        if( Direction){
            for(;(int16)temp< LasValue;Divide_count++)
                temp=-((Space/MAXNUM)*Divide_count);
        }
        if(!Direction){
            for(;(int16)temp>-LasValue;Divide_count++)
                temp=((Space/MAXNUM)*Divide_count);
        }
        Divide_count++;
    }
    else if(Divide_count<=(int8)MAXNUM){
        if(Direction){
            FinValue=-(int16)((Space/MAXNUM)*Divide_count);
        }
        else{
            FinValue=(int16)((Space/MAXNUM)*Divide_count);
        }
        Divide_count++;
    }
    else{
        if(Direction){
            FinValue=-(int16)Space;
        }
        else{
            FinValue=(int16)Space;
        }
    }
   if(ABS(FinValue)>(int16)Scr_Limit){
     if(Direction)
      FinValue = -(int16)Scr_Limit;
     else
       FinValue=  (int16)Scr_Limit;
   }
 return FinValue;
}

/********************************
*@author:�����
*@Function:�����ڴ��PID����
*description:��װ��ϣ��Ѽ�⣩ ������
********************************/
int16 PID_generator_Regular(uint8 Direction,float Space,float MAXNUM,int16 LasValue)
{
   float temp       = 0;
   int16  FinValue   = 0;
    if(!Divide_count){
        if( Direction){
            for(;(int16)temp< LasValue;Divide_count++)
                temp=-((Space/MAXNUM)*Divide_count);
        }
        if(!Direction){
            for(;(int16)temp>-LasValue;Divide_count++)
                temp=((Space/MAXNUM)*Divide_count);
        }
        Divide_count++;
    }
    else if(Divide_count<=(int8)MAXNUM){
        if(Direction){
            FinValue=-(int16)((Space/MAXNUM)*Divide_count);
        }
        else{
            FinValue=(int16)((Space/MAXNUM)*Divide_count);
        }
        Divide_count++;
    }
    else{
        if(Direction){
            FinValue=-(int16)Space;
        }
        else{
            FinValue=(int16)Space;
        }
    }
 return FinValue;
}
/********************************
*@author:�����
*@Function:���ݵ�ǰ״̬ѡ��ƫ��
*description:��װ��ϣ��Ѽ�⣩
********************************/
int16 Nor_ChosseDev()
{
  
  if(Blo_STATE == Blo_Founded){
    if(Block_ComLeft==1){
      Block_deviation=(int16)(block_Lline[Blo_row]-Blo_MidLine+Movblo_dev);
    }
    else if(Block_ComRight==1){
      Block_deviation=(int16)(block_Rline[Blo_row]-Blo_MidLine-Movblo_dev);
    }
  }
    if(Sig_STATE==Sig_Chasing&&Sig_permit){
      if(NorDirection==LEFT){
        LasLook_deviation = Sig_deviation;
        Sig_deviation = sigal_Rline_normal[Sig_row]- Sig_MidLine+Mov_dev;
      }
      else{
        LasLook_deviation = Sig_deviation;
        Sig_deviation = sigal_Lline_normal[Sig_row]- Sig_MidLine-Mov_dev;
      }
    }
if(Blo_STATE==Blo_Founded)
return Block_deviation;
else if(Sig_STATE==Sig_Chasing&&Sig_permit){
  return Sig_deviation;}
else if(Sig_STATE==Sig_Missing||(Sig_STATE==Sig_Chasing&&Lost_flag<=2&&Lost_flag>0)) {
  return LasLook_deviation;
}
else if(Sig_STATE==Sig_Finished)
  return 0;
else
  return 0;
}

/********************************
*@author:�����
*@Function:ѡ���ߵƵ���߻����ұ�
*description:��װ��ϣ��Ѽ�⣩
********************************/
void NorDirection_Chosse()
{
    /**************ѡ���ߵƵ���໹���Ҳ�***************/
  /**************��������ж�����������*************/
  if(Las_Dis_STATE==Dis_Clo&&Dis_STATE==Dis_Far){//���ɿ������Ƶ�ת��״̬��ͻȻ�����Ƶ�һ˲��
    if(Sig_MidLine>79){
      NorDirection =  LEFT;
    }
    else if(Sig_MidLine<=79&&Sig_MidLine!=0){
      NorDirection = RIGHT;
    }
  }
  if(Las_Sig_STATE==Sig_Finished && Sig_STATE == Sig_Chasing){
    if(Sig_MidLine>79){
      NorDirection =  LEFT;
    }
    else if(Sig_MidLine<=79&&Sig_MidLine!=0){
      NorDirection = RIGHT;
    }
  }
  /***********�����Ϻ󣬷�ֹ˦β�ı䷽���ж���������****/
  /***************2017��8��11��01:12:20����*********************/
  /**********��ֹ����˦β��ײ�Ƴ�������ʱ�ı䷽��**************/
  if(Las_Blo_STATE==Blo_Founded&&Blo_STATE==Blo_Missing){
    if(Sig_MidLine>79)
      NorDirection =  LEFT;
    else
      NorDirection = RIGHT;
  }
  if(NorDirection == LEFT && Sig_MidLine<46&&Sig_MidLine!=0&& Sig_row>70)
    NorDirection = ~NorDirection;
  else if(NorDirection == RIGHT && Sig_MidLine >113&& Sig_row>70)
    NorDirection = ~NorDirection;
  /**************************************************************/
}
//void NorDirection_Chosse()
//{
//    /**************ѡ���ߵƵ���໹���Ҳ�***************/
//  /**************��������ж�����������*************/
//  if(Las_Dis_STATE==Dis_Clo&&Dis_STATE==Dis_Far){//���ɿ������Ƶ�ת��״̬��ͻȻ�����Ƶ�һ˲��
//    if(Sig_MidLine>79){
//    NorDirection=RIGHT;//NorDirection =  LEFT;
//    }
//    else{
//      NorDirection = RIGHT;
//    }
//  }
//  if(Las_Sig_STATE==Sig_Finished && Sig_STATE == Sig_Chasing){
//    if(Sig_MidLine>79){
//      NorDirection =  RIGHT;
//    }
//    else{
//      NorDirection = RIGHT;
//    }
//  }
//  /***********�����Ϻ󣬷�ֹ˦β�ı䷽���ж���������****/
//  /***************2017��8��11��01:12:20����*********************/
//  /**********��ֹ����˦β��ײ�Ƴ�������ʱ�ı䷽��**************/
//  if(Las_Blo_STATE==Blo_Founded&&Blo_STATE==Blo_Missing){
//    if(Sig_MidLine>79)
//     NorDirection==RIGHT;// NorDirection =  LEFT;
//    else
//      NorDirection = RIGHT;
//  }
////  if(NorDirection == LEFT && Sig_MidLine<46&& Sig_row>75)
////    NorDirection = ~NorDirection;
////  else if(NorDirection == RIGHT && Sig_MidLine >113&& Sig_row>75)
////    NorDirection = ~NorDirection;
//  /**************************************************************/
//}
/********************************
*@author:�����
*@Function:��Ӻ���
*ת��Ѱ�Ƶ���һ˲�� PID<30�����  Sig_Finishing �� Sig_Chasing
*2017��8��11��01:33:16
********************************/


/********************************
*@author:�����
*@Function:�����жϴ�ʱ�ű�Ƶ�״̬
*description:��װ��ϣ�δ��⣩
*2017��8��11��01:59:34
********************************/
void Sig_STATE_Judgement()
{
  if(Lost_flag<=2){
    Sig_STATE = Sig_Chasing  ;}
  else if(Lost_flag<LOST_LIMIT&&Lost_flag>0)
    Sig_STATE = Sig_Chasing;
  else if((Lost_flag>LOST_LIMIT&&Dis_STATE==Dis_Clo)){
    Sig_STATE = Sig_Finished;}
  else if(Lost_flag>LOST_LIMIT&&Dis_STATE==Dis_Far)
    Sig_STATE = Sig_Finished;
}

/********************************
*@author:�����
*@Function:�ռ�Sig_FuzRow �����а�������
*description:��װ��ϣ�δ��⣩
*2017��8��11��20:10:34
********************************/
void Sig_FuzRow_Collection()
{
  if(Fuz_STATE == Fuz_RecFinished){
    if((Las_Dis_STATE == Dis_Clo&&Dis_STATE == Dis_Far)||(Las_Sig_STATE == Sig_Finished&&Sig_STATE==Sig_Chasing)){
      Fuz_STATE = Fuz_RecReady;
    }
  }
  if(Fuz_STATE==Fuz_RecReady&&Sig_STATE==Sig_Chasing)
    if(ABS(real_deviation)<30){
      Sig_FuzzyRow = Sig_row;
      Fuz_STATE = Fuz_RecFinished;
  }
  LOST_LIMIT_Judging();
}

/*********************************
*@author:�����
*@Function:������ռ�������жϴ���
*@description:��װ���(�Ѽ��)
*********************************/
void Single_Infra_Sensor()
{
  if(Dis_STATE==Dis_Far){  //Զ��
     Light_RecLeft  = 0;     //����״̬
     Light_RecRight = 0;     
     Inf_STATE = Inf_Ready;  //Ԥ����������ģʽһ
     Sta_Count=0;            //����״̬  
  }
  else if(Sta_Count>7||Inf_STATE==Inf_Finished){
    disable_irq(PORTC_IRQn);
    Inf_STATE = Inf_Finished;
  }
  /************�����ж���ƺ���ջ����ҹ�**************/
  if(Inf_STATE==Inf_Ready&&Dis_STATE==Dis_Clo&&Lost_flag>2&&Sta_Count<=7){  //������ǰ���� ��յ���ҵ����
    enable_irq (PORTC_IRQn);
    if(NorDirection==RIGHT&&Light_RecRight){
      TurDirection = RIGHT;
      Inf_STATE=Inf_Finished;
    }
    else if(NorDirection==LEFT&&Light_RecLeft){//������ǰ���� ��յ��������
      TurDirection = LEFT;
      Inf_STATE=Inf_Finished;
    }
    else if(Sta_Count==7){
      if(NorDirection==RIGHT&&!Light_RecRight){//������   �ұ߽��ղ����ź�
          TurDirection = LEFT;
      }
      else if(NorDirection==LEFT&&!Light_RecLeft){//������ �����ղ����ź�
          TurDirection = RIGHT;
      }
      Inf_STATE=Inf_Finished;
    }
        Sta_Count++;//5������֮���5��������Ϊ�������ʱ��
  }
}

/*******************************
*@auther:�����
*@Function:����������ͷ��ƽ���жϴ��
*2017��8��14��13:30:20
*******************************/
//          Port_5 = gpio_get(PTC5)               ;
//          Port_4 = gpio_get(PTC4)               ;
//          var[0] = (int16)Dis_STATE*100         ;
//          var[1] = (int16)Judge_STATE*100       ;
//          var[2] = (int16)Camer_STATE*100       ;
//          var[3] = (int16)Sig_permit*100        ;
//          var[4] = (int16)(Sig_row)    ;
//          var[5] = (int16)(Lost_flag)     ;
//          var[6] = (int16)Port_5*100 ;
//          var[7] = (int16)Port_4*100     ;
//void Level_Detection()
//{
//  if(Judge_STATE == Judge_Finished){
//    if(Sig_permit==1){
//      Judge_STATE = Judge_Ready;
//    }
//  }
//  if(Judge_STATE == Judge_Ready){
//    if(Dis_STATE == Dis_Clo){
//      if(Lost_flag>5){
//        Camer_STATE = Camer_Ready;
//        Judge_STATE = Judge_Finished;
//      }
//    }
//    else if(Dis_STATE == Dis_Far){
//      if(Lost_flag>4){
//        Camer_STATE = Camer_Ready;
//        Judge_STATE = Judge_Finished;
//      }
//    }
//  }
//  if(Camer_STATE==Camer_Ready){
//    if(((gpio_get(PTC5)==0)||(gpio_get(PTC4)==0))&&Lost_flag<LOST_LIMIT){
//      gpio_set(PTC0,1)          ;
//      gpio_set(PTA17,1)         ;
//      gpio_set(PTD15,0)         ;
//      gpio_set(PTE26,0)         ;
//      TurDirection=RIGHT        ;
//      Camer_STATE=Camer_Finished;
//    }
//    else if(Lost_flag>=LOST_LIMIT){
//      gpio_set(PTC0,0)          ;
//      gpio_set(PTA17,0)         ;
//      gpio_set(PTD15,1)         ;
//      gpio_set(PTE26,1)         ;
//      TurDirection=LEFT         ;
//      Camer_STATE=Camer_Finished;
//    }
//  }
//}

void Level_Detection()
{
  if(Forced_Turdirection==0)
  {
    if(Sig_permit==1&&Camer_STATE==Camer_Finished){
      Judge_STATE =  Judge_Ready ;
    }
    if(Judge_STATE == Judge_Ready&&Sig_permit==1)
      Judge_STATE = Judge_Finished;
    if(Lost_flag>5&&Judge_Ready){
      Camer_STATE = Camer_Ready;
    }
    if(Camer_STATE==Camer_Ready&&Sig_permit==1)
      Camer_STATE=Camer_Finished;
    if(Camer_STATE==Camer_Ready){
      if(((gpio_get(PTC5)==0)||(gpio_get(PTC4)==0))){
        gpio_set(PTC0,1)          ;
        gpio_set(PTA17,1)         ;
        gpio_set(PTD15,0)         ;
        gpio_set(PTE26,0)         ;
        TurDirection=RIGHT        ;
        Camer_STATE=Camer_Finished;
      }
      else
        TurDirection=LEFT         ;
    }
  }
  else
  {
    if(NorDirection==LEFT)
      TurDirection=LEFT;
    else
      TurDirection=RIGHT;
  }
}


void TurAvoidBlock_Delay()
{
  if(Tur_AvoidBlo_count>=TUR_AVOIDBLO_LIMIT){
    Tur_AvoidBlo_flag = 0;
    Tur_AvoidBlo_count= 0;
  }
  if(Las_Sig_STATE == Sig_Finished && Sig_STATE == Sig_Chasing&&Sig_permit&&Sig_row>25){
    Tur_AvoidBlo_flag = 1;
  }
  if(Tur_AvoidBlo_flag == 1){
    Tur_AvoidBlo_count++;
  }
}
void LOST_LIMIT_Judging()
{
  LOST_LIMIT = FuzRow_REV_LOSTLIMIT_A[Sig_FuzzyRow];
}