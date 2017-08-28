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
void PORTA_IRQHandler()    //信标摄像头中断服务函数
{
    uint8  n;    //引脚号
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //清中断标志位

    n = 16;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        ov7725_eagle_vsync();
    }


}
void PORTC_IRQHandler()//摄像头1
{
    uint8  n = 17;    //引脚号  17号引脚是VSS CPU内核电源
    uint32 flag = PORTC_ISFR;
    PORTC_ISFR  = ~0;                                   //清中断标志位

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
