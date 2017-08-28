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
void PORTA_IRQHandler()    //�ű�����ͷ�жϷ�����
{
    uint8  n;    //���ź�
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 16;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        ov7725_eagle_vsync();
    }


}
void PORTC_IRQHandler()//����ͷ1
{
    uint8  n = 17;    //���ź�  17��������VSS CPU�ں˵�Դ
    uint32 flag = PORTC_ISFR;
    PORTC_ISFR  = ~0;                                   //���жϱ�־λ

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
