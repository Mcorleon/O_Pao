#include "include.h" 
extern uint8 imgbuff_sigal_1[OV7725_EAGLE_SIZE_1];
extern uint8 imgbuff_sigal_2[OV7725_EAGLE_SIZE_1];
extern uint8 imgbuff_block_1[OV7725_EAGLE_SIZE]; 
extern uint8 imgbuff_block_2[OV7725_EAGLE_SIZE];  
extern uint8 img_switch_flag;
extern uint8 img_send_flag  ;
extern uint8 send_image_flag;
extern uint8 CloSigal_Flag  ;//接近信标灯的标志
extern uint8 FarSigal_Flag  ;//距离信标灯还有一段距离的的标志
extern int16 Light_RecLeft  ;//左边接受红外的次数
extern int16 Light_RecRight ;//右边接受红外的次数
extern int16 LOST_LIMIT     ;
extern Sig_STATUS_e  Sig_STATE   ;
extern Dis_STATUS_e  Dis_STATE   ;
extern Judge_STATUS_e Judge_STATE;
extern Camer_STATUS_e Camer_STATE;
extern int16 Block_deviation     ;
extern int16 real_deviation      ;
extern int16 Blo_LTemoporary     ;
extern int16 Blo_RTemoporary     ;
extern uint8 Enter_Blo_ComLeft   ;
extern uint8 Enter_Blo_ComRight  ;
extern uint8 Tur_AvoidBlo_flag   ;
extern  int8 Forced_TurRow       ;
extern int16 Tur_AvoidBlo_count  ;
extern int8 Losing_Row           ;
uint8 page=1;//oled页面
uint8 speed_level=0;
uint8 show_menu_flag;
uint8 show_OLED_flag   ;
uint8 show_process_flag;
uint8 OLED_testing_flag;
uint8 LCD_sigal_flag   ;
uint8 LCD_block_flag   ;
uint8 Spec_testing_flag;
/***********显示的参数************/
extern int16 Uper_Limit     ;
extern int16 Lower_Limit    ;
extern int16 Blo_Delay_Count;
extern uint8 Missing_Flag   ;
extern uint8 Block_ComRight ;//障碍在右
extern uint8 Block_ComLeft  ;//障碍在左
extern int16 PID            ;
extern Blo_STATUS_e Blo_STATE;
extern int8 Prospect_see    ;//前瞻
extern int8 Sig_row         ;//信标灯的行数
extern int8 Blo_row         ;//障碍灯的行数
extern int16 Blo_MidLine    ;//障碍灯的中线
extern int16 deviation      ;//偏差暂时
extern int16 Last_deviation ;//上一场偏差
extern int16 Sig_MidLine    ;//信标灯的中线
extern int32 Lost_flag      ;//丢失信标的次数
extern uint8 NorDirection   ;//寻灯的时候选择走灯的左边还是右边  0左1右
extern uint8 TurDirection   ;//寻完灯的时候选择左拐还是右拐
extern int8  Record_count   ;//就是一个计数的
extern int32 Divide_count   ;//就是分周期打脚用的计数
extern int8  Sig_FuzzyRow   ;//先不管
extern int16 Blo_chosse     ;//
extern int16 Sig_chosse     ;
extern uint8 Blo_Delay_Left ;
extern uint8 Blo_Delay_Right;
extern int16 Avoid_BloOffset;
extern  uint8 Blo_AgreeDelay;  
extern int16 Block_DelDev   ;
extern uint8 Sig_permit     ;
extern int16 DMIN           ;
extern int16 DMAX           ;
extern int16 Rev_Vision_Row ;
extern int16 Blo_Row_Limit  ;
extern uint8 Forced_Turdirection;
extern int8 Last_sigal_row  ;
int16 Sig_Fuz_Row_1      = 0;
int16 Sig_Fuz_Row_2      = 0;
int16 Sig_Fuz_Row_3      = 0;
int16 Sig_Fuz_Row_4      = 0;
int16 Sig_Fuz_Row_5      = 0;
int16 Sig_Fuz_Row_6      = 0;
/********************************/
void Init() //封装完毕
{
//    port_init(PTC3, ALT1 | IRQ_FALLING | PULLUP );          //初始化 PTC内部上拉
//    port_init(PTC4, ALT1 | IRQ_FALLING | PULLUP );
    gpio_init(PTC5,GPI,1);  //C3        
    gpio_init(PTC4,GPI,1);
    motor.speed_filter_error[0] = 0;  
    motor.speed_filter_error[1] = 0;
    motor.speed_filter_error[2] = 0;
    motor.speed_filter_error[3] = 0;
    motor.speed_filter_error[4] = 0;
    motor.sigal_filter_error[0] = 0; 
    motor.sigal_filter_error[1] = 0;
    motor.sigal_filter_error[2] = 0;
    motor.sigal_filter_error[3] = 0;
    motor.sigal_filter_error[4] = 0;
    gpio_init(PTD15,GPO,0);
    gpio_init(PTE26,GPO,0);
    gpio_init( PTC0,GPO,0);
    gpio_init(PTA17,GPO,0);     
    gpio_init(PTE12,GPO,0);
    gpio_init(PTE12,GPO,0);
    gpio_init( PTD9,GPI,1);
    gpio_init( PTD6,GPI,1);
    gpio_init( PTD7,GPI,1);     
    gpio_init( PTD4,GPI,1);
    gpio_init( PTD5,GPI,1);
    port_init_NoALT (PTD9,  PULLUP );     
    port_init_NoALT (PTD6,  PULLUP );     
    port_init_NoALT (PTD7,  PULLUP );     
    port_init_NoALT (PTD4,  PULLUP );      //内部上拉
    port_init_NoALT (PTD5,  PULLUP );  
    key_init(KEY_U);
    key_init(KEY_D);
    key_init(KEY_L);
    key_init(KEY_R);
    ov7725_eagle_init(imgbuff_block_1)  ;
    ov7725_eagle_init_1(imgbuff_sigal_1);
    Motor_init()        ;
    Servo_Motor_init()  ;
    Tft_init()          ;
    LCD_Clear(BLUE)     ;
    OLED_init()         ;
    ftm_quad_init(FTM1) ;
    ftm_quad_init(FTM2) ;
    pit_init_ms(PIT0,10);
     /*拨码开关选档*/
        if(key_get(KEY_R)==KEY_DOWN){
         UFF=UFF1;
         Turn_Speed = 197;
         speed_level=1;
        }
        
        else if(key_get(KEY_L)==KEY_DOWN){
          UFF=UFF2;
          Turn_Speed = 210 ;
          speed_level=2;
        }
        
        else if(key_get(KEY_D)==KEY_DOWN){
         UFF=UFF3;
         Turn_Speed = 205;
         speed_level=3;
        }
        else if(key_get(KEY_U)==KEY_DOWN){
         UFF=UFF4;
         Turn_Speed = 195;
         speed_level=4;
        }
        if(key_get(KEY_U)==KEY_DOWN
           &&key_get(KEY_D)==KEY_DOWN
           &&key_get(KEY_L)==KEY_DOWN
           &&key_get(KEY_R)==KEY_DOWN)
        {
         UFF=UFF5;
         Turn_Speed = 205;
         speed_level=5;
        }
}
void Set_vector() //封装完毕
{
    set_vector_handler(PORTB_VECTORn ,PORTB_IRQHandler);    //设置PORTA的中断服务函数为 PORTA_IRQHandler
    set_vector_handler (DMA0_VECTORn ,DMA0_IRQHandler) ;    //设置DMA0的中断服务函数为 DMA0_IRQHandler  
    set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //设置PORTA的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA3_VECTORn ,DMA3_IRQHandler)  ;    //设置DMA0的中断服务函数为 DMA0_IRQHandler
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler)  ;    //设置中断服务函数    
//    set_vector_handler(PORTC_VECTORn ,PORTC_IRQHandler); 
 //   set_vector_handler(UART4_RX_TX_VECTORn ,uart4_IRQHandler);
}
void send_image() //封装完毕
{
    if(0 == img_send_flag)
    {
      if(img_switch_flag != 0)
        vcan_sendimg(imgbuff_block_1, CAMERA_SIZE);                   //发送到上位机
      else
        vcan_sendimg(imgbuff_block_2, CAMERA_SIZE);                  //发送到上位机
    }
}
void OLED_show()
{
    if(show_menu_flag==1)
    {
     
      if(speed_level==1)
         LED_P6x8Str(0,0,"Speed= UFF1");
      else if(speed_level==2)
         LED_P6x8Str(0,0,"Speed= UFF2");
      else if(speed_level==3)
         LED_P6x8Str(0,0,"Speed= UFF3");
      else if(speed_level==4)
         LED_P6x8Str(0,0,"Speed= UFF4");
      else if(speed_level==5)        
         LED_P6x8Str(0,0,"Speed= UFF5");
      LED_P6x8Str(0,1,"Turn_Speed= ");
           LED_PrintValueI(70,1,Turn_Speed);
          LED_P6x8Str(0,2,"Start= ");
           LED_PrintValueI(70,2,Staup_Begin);
    }
    if(show_process_flag==1)
    {

      if(Blo_STATE==Blo_Founded)
        LED_P6x8Str(0,0,"Block_Founded");
      else if(Blo_STATE==Blo_Missing)
        LED_P6x8Str(0,0,"Block_Missing");
      else
        LED_P6x8Str(0,0,"Block_Delaying");
        LED_P6x8Str(0,1,"Sig_chosse-25");
        LED_PrintValueI(70,1,Sig_chosse-25);
                LED_P6x8Str(0,2,"Sig_chosse+25");
        LED_PrintValueI(70,2,Sig_chosse+25);
  //  LED_PrintValueI(70,0,turn_count);
  //  LED_P6x8Str(0,1,"turn_buff[]");
  //  LED_PrintValueI(70,1,turn_buff[turn_count]);
  //  LED_P6x8Str(0,2,"back_buff[]");
  //  LED_PrintValueI(70,2,back_turn_buff[turn_count]);
      LED_P6x8Str(0,3,"Sig_row");
      LED_PrintValueI(70,3,Sig_row);
      LED_P6x8Str(0,4,"Sig_MidLine");
      LED_PrintValueI(70,4,Sig_MidLine);
      LED_P6x8Str(0,5,"Blo_row");
      LED_PrintValueI(70,5,Blo_row);
      LED_P6x8Str(0,6,"Blo_MidLine");
      LED_PrintValueI(70,6,Blo_MidLine);

      LED_P6x8Str(0,7,"motor.speed_set");
      LED_PrintValueI(70,7,motor.speed_set);
    }

    if(Spec_testing_flag){
//      if(Blo_STATE==Blo_Founded)
//        LED_P6x8Str(0,0,"Blo_Founded");
//      else if(Blo_STATE==Blo_Missing)
//        LED_P6x8Str(0,0,"Blo_Missing");
//      else
//        LED_P6x8Str(0,0,"Blo_Delaying");
//      LED_P6x8Str(0,0,"Uper_Limit");
//      LED_PrintValueI(70,0,Uper_Limit);
//      LED_P6x8Str(0,1,"Lower_Limit");
//      LED_PrintValueI(70,1,Lower_Limit);
//      LED_P6x8Str(0,2,"Sig_FuzzyRow");
//      LED_PrintValueI(70,2,Sig_FuzzyRow);
//      
////      if(Sig_STATE==Sig_Chasing)
////      LED_P6x8Str(0,1,"Sig_STATE");
////      else if(Sig_STATE==Sig_Missing)
////        LED_P6x8Str(0,1,"Sig_Missing");
////      else
////        LED_P6x8Str(0,1,"Sig_Finishing");
//     // LED_PrintValueI(70,2,Sig_STATE);
//       LED_P6x8Str(0,3,"Sig_MidLine");
//       LED_PrintValueI(70,3,Sig_MidLine);
//              LED_P6x8Str(0,4,"Rev_Vision_Row");
//       LED_PrintValueI(70,4,Rev_Vision_Row);
//                 LED_P6x8Str(0,5,"Blo_row");
//      LED_PrintValueI(70,5,Blo_row);
//                LED_P6x8Str(0,6,"Blo_Row_Limit");
//      LED_PrintValueI(70,6,Tur_AvoidBlo_flag);
//                LED_P6x8Str(0,7,"TurBlo_count");
//      LED_PrintValueI(70,7,Tur_AvoidBlo_count);
      LED_P6x8Str(0,0,"NorDirection");
      LED_PrintValueI(70,0,NorDirection);
            LED_P6x8Str(0,1,"TurDirection");
      LED_PrintValueI(70,1,TurDirection);
            LED_P6x8Str(0,2," Forced_TurRow");
      LED_PrintValueI(70,2, Forced_TurRow);
            LED_P6x8Str(0,3,"Forced_Tur");
      LED_PrintValueI(70,3,Forced_Turdirection);
            LED_P6x8Str(0,4,"Sig_FuzzyRow");
      LED_PrintValueI(70,4,Sig_FuzzyRow);
            LED_P6x8Str(0,5,"Losing_Row");
      LED_PrintValueI(70,5,Losing_Row);
            LED_P6x8Str(0,6,"Last_sigal_row");
      LED_PrintValueI(70,6,Last_sigal_row);
  }
}
void Key_using() //封装完毕
{
          
        
        
        /*以下是按钮*/
        if(KEY1==0)
        {
          LED_Fill(0x00);
          page++;
          if(page>4)
          page=1;
          DELAY_MS(200);
          if(page==1)
          {
           show_menu_flag=1;
           show_process_flag=0;
           show_OLED_flag=0;
           Spec_testing_flag=0;
          }
          else if(page==2)
          {
           show_menu_flag=0;
           show_process_flag=1;
           show_OLED_flag=0;
           Spec_testing_flag=0;
          }
          else if(page==3)
          {
           show_menu_flag=0;
           show_process_flag=0;
           show_OLED_flag=1;
           Spec_testing_flag=0;
          }
          else if(page==4)
          {
           show_menu_flag=0;
           show_process_flag=0;
           show_OLED_flag=0;
           Spec_testing_flag=1;
          }
        }
        if(KEY2==0)
        {
          
            LCD_sigal_flag =1  ;

          DELAY_MS(200);
        }
         
        
        if(KEY3==0)
        {  
            LCD_block_flag=1   ;
         
         DELAY_MS(200);

        }
       if(KEY4==0)
       {
         DELAY_MS(10);
         if(KEY4==0)
         { 
           LCD_Clear(BLUE)     ;
           LCD_block_flag=0;
           LCD_sigal_flag =0;
         }
         DELAY_MS(200);
       }
//       if(KEY5==0)
//       {
//         DELAY_MS(10);
//         if(KEY5==0)
//         {
//           Staup_Begin=0;
//         }
//         DELAY_MS(200);
//       }
         if(LCD_sigal_flag==1){
          
          LCD_img_1()        ;
        }
        else if(LCD_block_flag==1){
          
          LCD_img()          ;
        }
}