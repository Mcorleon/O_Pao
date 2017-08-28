/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       VCAN_OV7725_Eagle.h
 * @brief      鹰眼ov7725驱动代码
 * @author     山外科技
 * @version    v5.0
 * @date       2013-09-07
 */

#ifndef _VCAN_OV7725_EAGLE_H_
#define _VCAN_OV7725_EAGLE_H_

#include "VCAN_OV7725_REG.h"

#if ( USE_CAMERA == CAMERA_OV7725_EAGLE )
//配置摄像头的特性
#define CAMERA_USE_HREF     0               //是否使用 行中断 (0 为 不使用，1为使用)
#define CAMERA_COLOR        0               //摄像头输出颜色 ， 0 为 黑白二值化图像 ，1 为 灰度 图像 ，2 为 RGB565 图像
#define CAMERA_POWER        0               //摄像头 电源选择， 0 为 3.3V ,1 为 5V

//配置摄像头顶层接口
#define camera_init_1(imgaddr)    ov7725_eagle_init_1(imgaddr)
#define camera_get_img_1()        ov7725_eagle_get_img_1()

#define camera_vsync_1()          ov7725_eagle_vsync_1()
#define camera_href_1()           //ov7725_eagle_href()
#define camera_dma_1()            ov7725_eagle_dma_1()

//配置 摄像头 参数
#define CAMERA_DMA_CH       OV7725_EAGLE_DMA_CH_1        //定义摄像头的DMA采集通道
#define CAMERA_W            OV7725_EAGLE_W_1              //定义摄像头图像宽度
#define CAMERA_H            OV7725_EAGLE_H_1              //定义摄像头图像高度

#define CAMERA_SIZE         OV7725_EAGLE_SIZE_1           //图像占用空间大小
#define CAMERA_DMA_NUM      OV7725_EAGLE_DMA_NUM_1        //DMA采集次数

#endif  //#if ( USE_CAMERA == CAMERA_OV7725_EAGLE )


//配置摄像头 属性
#define OV7725_EAGLE_DMA_CH_1       DMA_CH0                               //定义摄像头的DMA采集通道
#define OV7725_EAGLE_W_1            160                                    //定义摄像头图像宽度
#define OV7725_EAGLE_H_1            120                                    //定义摄像头图像高度
#define OV7725_EAGLE_SIZE_1         (OV7725_EAGLE_W_1 * OV7725_EAGLE_H_1/8 )  //图像占用空间大小
#define OV7725_EAGLE_DMA_NUM_1      (OV7725_EAGLE_SIZE_1)                  //DMA采集次数


extern  uint8   ov7725_eagle_init_1(uint8 *imgaddr);
extern  void    ov7725_eagle_get_img_1(void);

extern  void    ov7725_eagle_vsync_1(void);
extern  void    ov7725_eagle_dma_1(void);

//以上为摄像头1摄像头初始化函数文件
/*************************分界线*****************************************************************/
//以下为摄像头0摄像头初始化函数文件

//配置摄像头 属性
#define OV7725_EAGLE_DMA_CH       DMA_CH3                               //定义摄像头的DMA采集通道
#define OV7725_EAGLE_W            160                                    //定义摄像头图像宽度
#define OV7725_EAGLE_H            120                                    //定义摄像头图像高度
#define OV7725_EAGLE_SIZE         (OV7725_EAGLE_W * OV7725_EAGLE_H/8 )  //图像占用空间大小
#define OV7725_EAGLE_DMA_NUM      (OV7725_EAGLE_SIZE )                  //DMA采集次数


extern  uint8   ov7725_eagle_init(uint8 *imgaddr);
extern  void    ov7725_eagle_get_img(void);

extern  void    ov7725_eagle_vsync(void);
extern  void    ov7725_eagle_dma(void);
extern  void    Buffer_switch(void);

#endif  //_VCAN_OV7725_EAGLE_H_


