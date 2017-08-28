/*!
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     欧泡果奶
 * @version    v5.0
 * @date       2017-08-28
 * @description:无规划重新排版
   真实距离 8.00 对应行数 13
真实距离 7.50 对应行数 13
真实距离 7.00 对应行数 13
真实距离 6.50 对应行数 14
真实距离 6.00 对应行数 14
真实距离 5.50 对应行数 15
真实距离 5.00 对应行数 16
真实距离 4.50 对应行数 16
真实距离 4.00 对应行数 18
真实距离 3.50 对应行数 19
真实距离 3.00 对应行数 22
真实距离 2.50 对应行数 25
真实距离 2.00 对应行数 31
真实距离 1.50 对应行数 41
真实距离 1.00 对应行数 57
真实距离 0.50 对应行数 84
一盏灯到下一盏灯的两灭间隔是 6-8个周期  
红外接收   直射4.5米接收
 */
/**********************
2米对应行数30    晚上
从信标灯中心算起
1米对应行数 56  晚上

记录第一次看到灯的时候的距离 然后启动哪一个速度表
   *******************/
#include "common.h"    //不要动
#include "include.h"  //不要动
#include "math.h"     //暂时存着
#include "MK60_it.h" 
/*****************************
**系统应用定义
*****************************/
extern volatile IMG_STATUS_e      ov7725_eagle_img_flag  ;
extern volatile IMG_STATUS_e      ov7725_eagle_img_flag_1;
extern motor_status motor  ;
extern servos_status servos;
extern uint8 Sig_permit    ;  //是否发现信标灯标志
extern int16 PID           ;
extern int8 Light_RecLeft  ;
extern int8 Light_RecRight ;
extern uint8 Las_Sigpermit ;  //上一场是否发现信标灯
extern int8 Sig_row        ;  //信标灯行数
extern uint8 TurDirection  ;  //turn direction  寻完灯后左拐还是右拐
extern int32 Divide_count  ;  //打脚分十个周期 这是0到10的计数
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
/*********************************修改3*****************************/
/*********************************修改3*****************************/
/*********************************修改3*****************************/
void  main()
{
/****************
*一堆初始化
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
          ov7725_eagle_get_img_1();//摄像头获取图像

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
 
          sigal_finding();
          Forced_TurDirection();

/******************************
*外接摄像头检测左右方向
*得到 TurDirection
******************************/     
          Level_Detection();

/******************************
*寻找障碍灯(封装可动)
*得到障碍灯的行数   Blo_row
*得到障碍灯的中线   Blo_Midline
******************************/   
         
          block_finding();  


/**********************
*前瞻滤波(封装勿动)
*对信标灯的行数进行滤波
**********************/
          Prospect_see=Sig_row;
/*封装完*/filter_ProspectSee(); 


/**********************
*方向控制(封装勿动)
*P控制舵机打脚
**********************/

          direction_control();
if(Blo_STATE==Blo_Founded)
gpio_set(PTE12,1);
else
gpio_set(PTE12,0);
//  ftm_pwm_duty(Servo_ftm,Servo_CH,802);


/**********************
*将信标灯的行数畸变还原
*目前是个空函数没影响
**********************/
//          Rev_PerCorrection(Prospect_see);


          FuzzyGiv_DMAXMIN();

/**********************
*模糊给出目标速度
**********************/
          motor.speed_set=FuzzySet_Speed(0,Prospect_see);

       
/**********************
*对目标速度滤波
**********************/
/*封装完*/filter_speed();

/**********************
*电机PI控制
**********************/
          Spe_Speedset_Giv();   
          filter_speed_L();
          filter_speed_R();
/*封装完*/if(Staup_Begin==1){
            speed_control2();
          }

          
/**********************
*电机保护
**********************/
#if MotProtection
        if(number_adding>30){
/*封装完*/Motor_protect();
        }
#endif




/**********************
*起跑
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
          while(ov7725_eagle_img_flag_1 != IMG_FINISH)           //等待图像采集完毕
          {
              if(ov7725_eagle_img_flag_1 == IMG_FAIL)            //假如图像采集错误，则重新开始采集
              {
                  ov7725_eagle_img_flag_1 = IMG_START;           //开始采集图像
                  PORTB_ISFR = ~0;                //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
                  enable_irq(PORTB_IRQn);                 //允许PTA的中断
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
