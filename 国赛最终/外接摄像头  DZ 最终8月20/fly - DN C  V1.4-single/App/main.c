/*!
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ŷ�ݹ���
 * @version    v5.0
 * @date       2017-08-28
 * @description:�������ͷ
   ��ʵ���� 8.00 ��Ӧ���� 13
*/
#include "common.h"    //��Ҫ��
#include "include.h"  //��Ҫ��
#include "math.h"     //��ʱ����
#include "MK60_it.h" 
/*****************************
**ϵͳӦ�ö���
*****************************/
extern volatile IMG_STATUS_e      ov7725_eagle_img_flag  ;
extern volatile IMG_STATUS_e      ov7725_eagle_img_flag_1;

extern uint8 Sig_permit_A    ;  //�Ƿ����ű�Ʊ�־
extern uint8 Sig_permit_B    ;

extern uint8 Las_Sigpermit ;  //��һ���Ƿ����ű��
extern int8 Sig_row        ;  //�ű������
extern int32 Lost_flag;
/***********************/
uint8 send_image_flag=0;
uint8 img_send_flag = 0 ;
int16  var[8]; 
void  main()
{
/****************
*һ�ѳ�ʼ��
****************/
      Init();
      Set_vector();  
      DELAY_MS(500);
      while(1)
      {
          ov7725_eagle_get_img_1();
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
          sigal_finding_A();

          sigal_finding_B();
          LCD_img();
          if(Sig_permit_A){
            gpio_set(PTB9,0);
          }
          else{
            gpio_set(PTB9,1);
          }
          if(Sig_permit_B){
            gpio_set(PTB3,0);
          }
          else{
            gpio_set(PTB3,1);
          }
          var[0] = (int16)      0  ;
          var[1] = (int16)     0  ;
          var[2] = (int16)      0;
          var[3] = (int16)Sig_permit_A*100        ;
          var[4] = (int16)Sig_permit_B*100   ;
          var[5] = (int16)0     ;
          var[6] = (int16)0;
          var[7] = (int16)0   ;
          while(ov7725_eagle_img_flag_1 != IMG_FINISH)           //�ȴ�ͼ��ɼ����
          {
              if(ov7725_eagle_img_flag_1 == IMG_FAIL)            //����ͼ��ɼ����������¿�ʼ�ɼ�
              {
                  ov7725_eagle_img_flag_1 = IMG_START;           //��ʼ�ɼ�ͼ��
                  PORTC_ISFR = ~0;                //д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
                  enable_irq(PORTC_IRQn);                 //����PTA���ж�
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