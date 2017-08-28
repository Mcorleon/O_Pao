/*!
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     欧泡果奶
 * @version    v5.0
 * @date       2017-08-28
 * @description:外接摄像头
   真实距离 8.00 对应行数 13
*/
#include "common.h"    //不要动
#include "include.h"  //不要动
#include "math.h"     //暂时存着
#include "MK60_it.h" 
/*****************************
**系统应用定义
*****************************/
extern volatile IMG_STATUS_e      ov7725_eagle_img_flag  ;
extern volatile IMG_STATUS_e      ov7725_eagle_img_flag_1;

extern uint8 Sig_permit_A    ;  //是否发现信标灯标志
extern uint8 Sig_permit_B    ;

extern uint8 Las_Sigpermit ;  //上一场是否发现信标灯
extern int8 Sig_row        ;  //信标灯行数
extern int32 Lost_flag;
/***********************/
uint8 send_image_flag=0;
uint8 img_send_flag = 0 ;
int16  var[8]; 
void  main()
{
/****************
*一堆初始化
****************/
      Init();
      Set_vector();  
      DELAY_MS(500);
      while(1)
      {
          ov7725_eagle_get_img_1();
          ov7725_eagle_get_img()  ;
/**********************
*图像双缓冲(封装勿动)
**********************/
          Buffer_switch()         ;
/**********************
*上位机显示(封装勿动)
**********************/
          if(send_image_flag==1){
            send_image()          ;
          }

          
/******************************
*寻找信标灯(封装可动)
*得到信标灯是否存在 Sig_permit
*得到信标灯的行数   Sig_row;
*得到信标灯的中线   Sig_MidLine
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
          while(ov7725_eagle_img_flag_1 != IMG_FINISH)           //等待图像采集完毕
          {
              if(ov7725_eagle_img_flag_1 == IMG_FAIL)            //假如图像采集错误，则重新开始采集
              {
                  ov7725_eagle_img_flag_1 = IMG_START;           //开始采集图像
                  PORTC_ISFR = ~0;                //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
                  enable_irq(PORTC_IRQn);                 //允许PTA的中断
              }
          }
          while(ov7725_eagle_img_flag != IMG_FINISH)           //等待图像采集完毕
          {
              if(ov7725_eagle_img_flag == IMG_FAIL)            //假如图像采集错误，则重新开始采集
              {
                  ov7725_eagle_img_flag = IMG_START;           //开始采集图像
                  PORTA_ISFR = ~0;                //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
                  enable_irq(PORTA_IRQn);                 //允许PTA的中断
              }
          }
       }
}