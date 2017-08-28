/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       MK60_it.c
 * @brief      山外K60 平台中断服务函数
 * @author     山外科技
 * @version    v5.0
 * @date       2013-06-26
 */

#include    "MK60_it.h"
#include    "include.h"
#include    "common.h"
/***********************
**摄像头中断服务函数
***********************/
extern uint8 TFT_sigal_flag ;
extern uint8 TFT_block_flag ;
extern uint8 TurDirection   ;
extern Dis_STATUS_e Dis_STATE;
uint8 Inf_recepFinish     = 0;
int16 Light_RecLeft       = 0;
int16 Light_RecRight      = 0;
int8  Light_SecLeft       = 0; //Sec是Second  第二个  看看那个是第二个亮的
int8  Light_SecRight      = 0;
uint8 Car_Stop_flag       = 0;
void PORTA_IRQHandler()    //信标摄像头中断服务函数
{
    uint8  n;    //引脚号
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //清中断标志位

    n = 29;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        ov7725_eagle_vsync();
    }


}
void PORTB_IRQHandler()//摄像头1
{
    uint8  n = 18;    //引脚号  17号引脚是VSS CPU内核电源
    uint32 flag = PORTB_ISFR;
    PORTB_ISFR  = ~0;                                   //清中断标志位

   // n = 1;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        ov7725_eagle_vsync_1();
    }
            //鹰眼直接全速采集，不需要行中断
}
/************按键中断******************/





/////////////////////////////////////////

void DMA0_IRQHandler()
{
    ov7725_eagle_dma_1();
}
void DMA3_IRQHandler()   //摄像头0
{
    ov7725_eagle_dma();
}
void PIT0_IRQHandler(void)//PIT定时
{   
    PIT_Flag_Clear(PIT0);       //清中断标志位
    motor.speed_L =-ftm_quad_get(FTM2);          //获取FTM 正交解码 的脉冲数(负数表示反方向)
   ftm_quad_clean(FTM2);
   motor.speed_R = ftm_quad_get(FTM1);          //获取FTM 正交解码 的脉冲数(负数表示反方向)
   ftm_quad_clean(FTM1);
}
void PIT1_IRQHandler(void)//PIT定时
{   
    PIT_Flag_Clear(PIT1);       //清中断标志位
}