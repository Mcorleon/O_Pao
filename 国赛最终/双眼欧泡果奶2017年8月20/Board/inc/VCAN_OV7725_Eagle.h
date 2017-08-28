/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       VCAN_OV7725_Eagle.h
 * @brief      ӥ��ov7725��������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-09-07
 */

#ifndef _VCAN_OV7725_EAGLE_H_
#define _VCAN_OV7725_EAGLE_H_

#include "VCAN_OV7725_REG.h"

#if ( USE_CAMERA == CAMERA_OV7725_EAGLE )
//��������ͷ������
#define CAMERA_USE_HREF     0               //�Ƿ�ʹ�� ���ж� (0 Ϊ ��ʹ�ã�1Ϊʹ��)
#define CAMERA_COLOR        0               //����ͷ�����ɫ �� 0 Ϊ �ڰ׶�ֵ��ͼ�� ��1 Ϊ �Ҷ� ͼ�� ��2 Ϊ RGB565 ͼ��
#define CAMERA_POWER        0               //����ͷ ��Դѡ�� 0 Ϊ 3.3V ,1 Ϊ 5V

//��������ͷ����ӿ�
#define camera_init_1(imgaddr)    ov7725_eagle_init_1(imgaddr)
#define camera_get_img_1()        ov7725_eagle_get_img_1()

#define camera_vsync_1()          ov7725_eagle_vsync_1()
#define camera_href_1()           //ov7725_eagle_href()
#define camera_dma_1()            ov7725_eagle_dma_1()

//���� ����ͷ ����
#define CAMERA_DMA_CH       OV7725_EAGLE_DMA_CH_1        //��������ͷ��DMA�ɼ�ͨ��
#define CAMERA_W            OV7725_EAGLE_W_1              //��������ͷͼ����
#define CAMERA_H            OV7725_EAGLE_H_1              //��������ͷͼ��߶�

#define CAMERA_SIZE         OV7725_EAGLE_SIZE_1           //ͼ��ռ�ÿռ��С
#define CAMERA_DMA_NUM      OV7725_EAGLE_DMA_NUM_1        //DMA�ɼ�����

#endif  //#if ( USE_CAMERA == CAMERA_OV7725_EAGLE )


//��������ͷ ����
#define OV7725_EAGLE_DMA_CH_1       DMA_CH0                               //��������ͷ��DMA�ɼ�ͨ��
#define OV7725_EAGLE_W_1            160                                    //��������ͷͼ����
#define OV7725_EAGLE_H_1            120                                    //��������ͷͼ��߶�
#define OV7725_EAGLE_SIZE_1         (OV7725_EAGLE_W_1 * OV7725_EAGLE_H_1/8 )  //ͼ��ռ�ÿռ��С
#define OV7725_EAGLE_DMA_NUM_1      (OV7725_EAGLE_SIZE_1)                  //DMA�ɼ�����


extern  uint8   ov7725_eagle_init_1(uint8 *imgaddr);
extern  void    ov7725_eagle_get_img_1(void);

extern  void    ov7725_eagle_vsync_1(void);
extern  void    ov7725_eagle_dma_1(void);

//����Ϊ����ͷ1����ͷ��ʼ�������ļ�
/*************************�ֽ���*****************************************************************/
//����Ϊ����ͷ0����ͷ��ʼ�������ļ�

//��������ͷ ����
#define OV7725_EAGLE_DMA_CH       DMA_CH3                               //��������ͷ��DMA�ɼ�ͨ��
#define OV7725_EAGLE_W            160                                    //��������ͷͼ����
#define OV7725_EAGLE_H            120                                    //��������ͷͼ��߶�
#define OV7725_EAGLE_SIZE         (OV7725_EAGLE_W * OV7725_EAGLE_H/8 )  //ͼ��ռ�ÿռ��С
#define OV7725_EAGLE_DMA_NUM      (OV7725_EAGLE_SIZE )                  //DMA�ɼ�����


extern  uint8   ov7725_eagle_init(uint8 *imgaddr);
extern  void    ov7725_eagle_get_img(void);

extern  void    ov7725_eagle_vsync(void);
extern  void    ov7725_eagle_dma(void);
extern  void    Buffer_switch(void);

#endif  //_VCAN_OV7725_EAGLE_H_


