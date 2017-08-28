/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       MK60_it.c
 * @brief      ɽ��K60 ƽ̨�жϷ�����
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-06-26
 */

#include    "MK60_it.h"
#include    "include.h"
#include    "common.h"
/***********************
**����ͷ�жϷ�����
***********************/
extern uint8 TFT_sigal_flag ;
extern uint8 TFT_block_flag ;
extern uint8 TurDirection   ;
extern Dis_STATUS_e Dis_STATE;
uint8 Inf_recepFinish     = 0;
int16 Light_RecLeft       = 0;
int16 Light_RecRight      = 0;
int8  Light_SecLeft       = 0; //Sec��Second  �ڶ���  �����Ǹ��ǵڶ�������
int8  Light_SecRight      = 0;
uint8 Car_Stop_flag       = 0;
void PORTA_IRQHandler()    //�ű�����ͷ�жϷ�����
{
    uint8  n;    //���ź�
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 29;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        ov7725_eagle_vsync();
    }


}
void PORTB_IRQHandler()//����ͷ1
{
    uint8  n = 18;    //���ź�  17��������VSS CPU�ں˵�Դ
    uint32 flag = PORTB_ISFR;
    PORTB_ISFR  = ~0;                                   //���жϱ�־λ

   // n = 1;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        ov7725_eagle_vsync_1();
    }
            //ӥ��ֱ��ȫ�ٲɼ�������Ҫ���ж�
}
/************�����ж�******************/





/////////////////////////////////////////

void DMA0_IRQHandler()
{
    ov7725_eagle_dma_1();
}
void DMA3_IRQHandler()   //����ͷ0
{
    ov7725_eagle_dma();
}
void PIT0_IRQHandler(void)//PIT��ʱ
{   
    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
    motor.speed_L =-ftm_quad_get(FTM2);          //��ȡFTM �������� ��������(������ʾ������)
   ftm_quad_clean(FTM2);
   motor.speed_R = ftm_quad_get(FTM1);          //��ȡFTM �������� ��������(������ʾ������)
   ftm_quad_clean(FTM1);
}
void PIT1_IRQHandler(void)//PIT��ʱ
{   
    PIT_Flag_Clear(PIT1);       //���жϱ�־λ
}