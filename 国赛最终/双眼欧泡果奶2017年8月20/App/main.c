/*!
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ŷ�ݹ���
 * @version    v5.0
 * @date       2017-08-28
 * @description:�޹滮�����Ű�
   ��ʵ���� 8.00 ��Ӧ���� 13
��ʵ���� 7.50 ��Ӧ���� 13
��ʵ���� 7.00 ��Ӧ���� 13
��ʵ���� 6.50 ��Ӧ���� 14
��ʵ���� 6.00 ��Ӧ���� 14
��ʵ���� 5.50 ��Ӧ���� 15
��ʵ���� 5.00 ��Ӧ���� 16
��ʵ���� 4.50 ��Ӧ���� 16
��ʵ���� 4.00 ��Ӧ���� 18
��ʵ���� 3.50 ��Ӧ���� 19
��ʵ���� 3.00 ��Ӧ���� 22
��ʵ���� 2.50 ��Ӧ���� 25
��ʵ���� 2.00 ��Ӧ���� 31
��ʵ���� 1.50 ��Ӧ���� 41
��ʵ���� 1.00 ��Ӧ���� 57
��ʵ���� 0.50 ��Ӧ���� 84
һյ�Ƶ���һյ�Ƶ��������� 6-8������  
�������   ֱ��4.5�׽���
 */
/**********************
2�׶�Ӧ����30    ����
���ű����������
1�׶�Ӧ���� 56  ����

��¼��һ�ο����Ƶ�ʱ��ľ��� Ȼ��������һ���ٶȱ�
   *******************/
#include "common.h"    //��Ҫ��
#include "include.h"  //��Ҫ��
#include "math.h"     //��ʱ����
#include "MK60_it.h" 
/*****************************
**ϵͳӦ�ö���
*****************************/
extern volatile IMG_STATUS_e      ov7725_eagle_img_flag  ;
extern volatile IMG_STATUS_e      ov7725_eagle_img_flag_1;
extern motor_status motor  ;
extern servos_status servos;
extern uint8 Sig_permit    ;  //�Ƿ����ű�Ʊ�־
extern int16 PID           ;
extern int8 Light_RecLeft  ;
extern int8 Light_RecRight ;
extern uint8 Las_Sigpermit ;  //��һ���Ƿ����ű��
extern int8 Sig_row        ;  //�ű������
extern uint8 TurDirection  ;  //turn direction  Ѱ��ƺ���ջ����ҹ�
extern int32 Divide_count  ;  //��ŷ�ʮ������ ����0��10�ļ���
extern int8  Sig_FuzzyRow  ;
extern uint8 NorDirection  ;
extern Inf_STATUS_e    Inf_STATE  ;
extern Blo_STATUS_e    Blo_STATE  ;
extern Dis_STATUS_e    Dis_STATE  ;
extern Judge_STATUS_e Judge_STATE ;
extern Camer_STATUS_e Camer_STATE ;
extern int16 Blo_AgrDelay_Count   ;
extern uint8 Las_Dis_state        ;
extern int32 Lost_flag            ;
extern int16 Block_deviation      ;
extern uint8 Block_ComLeft        ;
extern uint8 Block_ComRight       ;
extern int16 direction_duty_output;
extern uint8 Las_Blo_STATE        ;
extern int16 Sig_MidLine          ;
extern uint8 Tur_AvoidBlo_flag    ;
extern int16 Tur_AvoidBlo_count   ;
extern Sig_STATUS_e   Sig_STATE   ;
extern uint8 Motor_Protection_Flag;
extern int8 Last_sigal_row        ;
extern uint8 Forced_Turdirection  ;
extern int8 Losing_Row            ;
int16 Port_5 = 0;
int16 Port_4 = 0;
int16 Buffer_Count = 0  ;
/***********************/
uint8 send_image_flag=0 ;
uint8 img_send_flag = 0 ;
/***********************/
uint8 Staup_Begin =0 ;
uint8 Start_flag=1 ;
int8 Prospect_see=0;
int16 var[8] ;
int16 DMAX=50;
int16 DMIN=10;
extern int8  Light_SecLeft       ;
extern int8  Light_SecRight      ;
int8 start_count=0  ;
int8 number_adding=0;
int16 Time = 0      ;
//void Reset_Checking();
/*********************************�޸�3*****************************/
/*********************************�޸�3*****************************/
/*********************************�޸�3*****************************/
void  main()
{
/****************
*һ�ѳ�ʼ��
****************/
      Init();
      Set_vector();
      enable_irq (PIT0_IRQn); 
    //  uart_rx_irq_en (UART4);
  //    Reset_Checking();
      while(1)
      {

    //      pit_time_start(PIT1)    ;
          Key_using()             ;
          OLED_show()             ;
      //   Time=pit_time_get_us(PIT1);
          ov7725_eagle_get_img_1();//����ͷ��ȡͼ��

          ov7725_eagle_get_img()  ;
/**********************
*ͼ��˫����(��װ��)
**********************/
          Buffer_switch()         ;
/**********************
*��λ����ʾ(��װ��)
**********************/
          if(send_image_flag==1){
            send_image()          ;
          }


/******************************
*Ѱ���ű��(��װ�ɶ�)
*�õ��ű���Ƿ���� Sig_permit
*�õ��ű�Ƶ�����   Sig_row;
*�õ��ű�Ƶ�����   Sig_MidLine
******************************/        
 
          sigal_finding();
          Forced_TurDirection();

/******************************
*�������ͷ������ҷ���
*�õ� TurDirection
******************************/     
          Level_Detection();

/******************************
*Ѱ���ϰ���(��װ�ɶ�)
*�õ��ϰ��Ƶ�����   Blo_row
*�õ��ϰ��Ƶ�����   Blo_Midline
******************************/   
         
          block_finding();  


/**********************
*ǰհ�˲�(��װ��)
*���ű�Ƶ����������˲�
**********************/
          Prospect_see=Sig_row;
/*��װ��*/filter_ProspectSee(); 


/**********************
*�������(��װ��)
*P���ƶ�����
**********************/

          direction_control();
if(Blo_STATE==Blo_Founded)
gpio_set(PTE12,1);
else
gpio_set(PTE12,0);
//  ftm_pwm_duty(Servo_ftm,Servo_CH,802);


/**********************
*���ű�Ƶ��������仹ԭ
*Ŀǰ�Ǹ��պ���ûӰ��
**********************/
//          Rev_PerCorrection(Prospect_see);


          FuzzyGiv_DMAXMIN();

/**********************
*ģ������Ŀ���ٶ�
**********************/
          motor.speed_set=FuzzySet_Speed(0,Prospect_see);

       
/**********************
*��Ŀ���ٶ��˲�
**********************/
/*��װ��*/filter_speed();

/**********************
*���PI����
**********************/
          Spe_Speedset_Giv();   
          filter_speed_L();
          filter_speed_R();
/*��װ��*/if(Staup_Begin==1){
            speed_control2();
          }

          
/**********************
*�������
**********************/
#if MotProtection
        if(number_adding>30){
/*��װ��*/Motor_protect();
        }
#endif




/**********************
*����
**********************/
          if(Staup_Begin==1&&number_adding<50){
            if(start_count<=10)
              start_count++;
            number_adding++;
          }
          Port_5 = gpio_get(PTC5)            ;
          Port_4 = gpio_get(PTC4)            ;
          var[0] = (int16)Losing_Row         ;
          var[1] = (int16)TurDirection       ;
          var[2] = (int16)Forced_Turdirection;
          var[3] = (int16)Sig_FuzzyRow       ;
          var[4] = (int16)Losing_Row         ;
          var[5] = (int16)Last_sigal_row     ;
          var[6] = (int16)motor.speed_set_L  ;
          var[7] = (int16)motor.speed_set_R  ;
          vcan_sendware((uint8_t *)var, sizeof(var)); 
          while(ov7725_eagle_img_flag_1 != IMG_FINISH)           //�ȴ�ͼ��ɼ����
          {
              if(ov7725_eagle_img_flag_1 == IMG_FAIL)            //����ͼ��ɼ����������¿�ʼ�ɼ�
              {
                  ov7725_eagle_img_flag_1 = IMG_START;           //��ʼ�ɼ�ͼ��
                  PORTB_ISFR = ~0;                //д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
                  enable_irq(PORTB_IRQn);                 //����PTA���ж�
              }
          }
          while(ov7725_eagle_img_flag != IMG_FINISH)           //�ȴ�ͼ��ɼ����
          {
              if(ov7725_eagle_img_flag == IMG_FAIL)            //����ͼ��ɼ����������¿�ʼ�ɼ�
              {
                  ov7725_eagle_img_flag = IMG_START;           //��ʼ�ɼ�ͼ��
                  PORTA_ISFR = ~0;                //д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
                  enable_irq(PORTA_IRQn);                 //����PTA���ж�
              }
          }
       }
}
//void Reset_Checking()
//{
//    if (MC_SRSH & MC_SRSH_SW_MASK)
//        printf("Software Reset\n");
//    if (MC_SRSH & MC_SRSH_LOCKUP_MASK)
//        printf("Core Lockup Event Reset\n");
//    if (MC_SRSH & MC_SRSH_JTAG_MASK)
//        printf("JTAG Reset\n");
//    if (MC_SRSL & MC_SRSL_POR_MASK)
//        printf("Power-on Reset\n");
//    if (MC_SRSL & MC_SRSL_PIN_MASK)
//        printf("External Pin Reset\n");
//    if (MC_SRSL & MC_SRSL_COP_MASK)
//       printf("Watchdog(COP) Reset\n");
//    if (MC_SRSL & MC_SRSL_LOC_MASK)
//        printf("Loss of Clock Reset\n");
//    if (MC_SRSL & MC_SRSL_LVD_MASK)
//        printf("Low-voltage Detect Reset\n");
//    if (MC_SRSL & MC_SRSL_WAKEUP_MASK)
//        printf("LLWU Reset\n");
//}
