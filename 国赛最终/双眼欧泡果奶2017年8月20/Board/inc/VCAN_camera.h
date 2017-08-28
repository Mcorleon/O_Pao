/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       VCAN_camera.h
 * @brief      ����ͷ�����ӿ��ض���
 * @author     ɽ��Ƽ�
 * @version    v5.2.1
 * @date       2015-04-01
 */


#ifndef _VCAN_CAMERA_H_
#define _VCAN_CAMERA_H_


#define CAMERA_OV7725_EAGLE         2       //ɽ��ӥ��
#define CAMERA_OV7725_WOLF          3       //ɽ������


#define USE_CAMERA      CAMERA_OV7725_EAGLE   //ѡ��ʹ�õ� ����ͷ

typedef struct
{
    uint8 addr;                 /*�Ĵ�����ַ*/
    uint8 val;                   /*�Ĵ���ֵ*/
} reg_s;

//����ͼ��ɼ�״̬
typedef enum
{
    IMG_NOTINIT = 0,
    IMG_FINISH,             //ͼ��ɼ����
    IMG_FAIL,               //ͼ��ɼ�ʧ��(�ɼ���������)
    IMG_GATHER,             //ͼ��ɼ���
    IMG_START,              //��ʼ�ɼ�ͼ��
    IMG_STOP,               //��ֹͼ��ɼ�
} IMG_STATUS_e;
/*****************************************/

#define Data_Line 120
#define Data_Count 160 
void sigal_finding()      ;
void block_finding()      ;
void BloNor_JudAppear()   ;
void BloSpe_JudAppear()   ;
void BloSpe_JudDisappear();
void BloNor_JudDisappear();
void Blo_Delay_DevGiv()   ;
void Dis_STATE_Judgement();
void Forced_TurDirection();

typedef enum
{
  Dis_Clo = 1,
  Dis_Far = 2,
} Dis_STATUS_e;
/*****************************************/
#include  "VCAN_SCCB.h"
#include  "VCAN_OV7725_Eagle.h"

extern void img_extract(void *dst, void *src, uint32_t srclen);

#endif


