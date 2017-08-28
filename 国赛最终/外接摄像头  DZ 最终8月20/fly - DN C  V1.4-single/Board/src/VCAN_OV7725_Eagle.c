#include "common.h"
#include "MK60_gpio.h"
#include "MK60_port.h"
#include "MK60_dma.h"
#include "VCAN_camera.h"    

#define OV7725_EAGLE_Delay_ms(time)  DELAY_MS(time)
uint8   img_switch_flag   = 0;
uint8   img_switch_flag_1 = 0;
uint8   img_1[OV7725_EAGLE_H_1][OV7725_EAGLE_W_1];
uint8   img[OV7725_EAGLE_H][OV7725_EAGLE_W];
uint8   imgbuff_sigal_1[OV7725_EAGLE_SIZE_1];
uint8   imgbuff_sigal_2[OV7725_EAGLE_SIZE_1];
uint8   imgbuff_block_1[OV7725_EAGLE_SIZE]; 
uint8   imgbuff_block_2[OV7725_EAGLE_SIZE];
uint8   *ov7725_eagle_img_buff_1; //  与ov7725_eagle_img_buff  没有后面的_1


volatile IMG_STATUS_e      ov7725_eagle_img_flag_1 = IMG_START;   //图像状态

//内部函数声明
static uint8 ov7725_eagle_reg_init_1(void);
static void ov7725_eagle_port_init_1();


/*!
 *  @brief      鹰眼ov7725初始化
 *  @since      v5.0
 */
uint8 ov7725_eagle_init_1(uint8 *imgaddr) //与其第三区别  还是没有 _1
{
    ov7725_eagle_img_buff_1 = imgaddr; 
    while(ov7725_eagle_reg_init_1() == 0); //鹰眼SCCB写寄存器初始化成功返回0
    ov7725_eagle_port_init_1();  //相关引脚初始化
  //  enable_irq(PORTB_IRQn);     //初始化后开场中断， // 与Ache第四区别  
    return 0;
}

/*!
 *  @brief      鹰眼ov7725管脚初始化（内部调用）
 *  @since      v5.0
 */
void ov7725_eagle_port_init_1()
{
    //DMA通道0初始化，PTA27触发源(默认上升沿)，源地址为PTB_B0_IN，目的地址为：IMG_BUFF，每次传输1Byte
    dma_portx2buff_init(OV7725_EAGLE_DMA_CH_1, (void *)&PTD_B0_IN, (void *)ov7725_eagle_img_buff_1, PTC16, DMA_BYTE1,OV7725_EAGLE_DMA_NUM_1, DADDR_KEEPON);

    DMA_DIS(OV7725_EAGLE_DMA_CH_1);
    disable_irq(PORTC_IRQn);                        //关闭PTB的中断，场中断
    DMA_IRQ_CLEAN(OV7725_EAGLE_DMA_CH_1);                   //清除通道传输中断标志位
    DMA_IRQ_EN(OV7725_EAGLE_DMA_CH_1);

    port_init(PTC16, ALT1 | DMA_FALLING | PULLDOWN );         //PCLK

    port_init(PTC17, ALT1 | IRQ_RISING  | PULLUP | PF);     //场中断，上拉，上降沿触发中断，带滤波

}

/*!
 *  @brief      鹰眼ov7725场中断服务函数
 *  @since      v5.0
 */
void ov7725_eagle_vsync_1(void) 
{

    //场中断需要判断是场结束还是场开始
    if(ov7725_eagle_img_flag_1 == IMG_START)                   //需要开始采集图像
    {
        ov7725_eagle_img_flag_1 = IMG_GATHER;                  //标记图像采集中
        disable_irq(PORTC_IRQn); //关闭场中断

#if 1

        PORTC_ISFR = 16 <<  PT16;            //清空PCLK标志位，PCk信号来了

        DMA_EN(OV7725_EAGLE_DMA_CH_1);                  //使能通道CHn 硬件请求
        PORTC_ISFR = 16 <<  PT16;            //清空PCLK标志位
        
        DMA_DADDR(OV7725_EAGLE_DMA_CH_1) = (uint32)ov7725_eagle_img_buff_1;    //恢复地址

#else
        PORTC_ISFR = 16 <<  PT16;            //清空PCLK标志位
        dma_repeat(OV7725_EAGLE_DMA_CH_1, (void *)&PTD_B0_IN, (void *)ov7725_eagle_img_buff,OV7725_EAGLE_DMA_NUM_1);
#endif
    }
    else                                        //图像采集错误
    {
        disable_irq(PORTC_IRQn);                        //关闭PTA的中断
        ov7725_eagle_img_flag_1 = IMG_FAIL;                    //标记图像采集失败
    }
}

/*!
 *  @brief      鹰眼ov7725 DMA中断服务函数
 *  @since      v5.0
 */
void ov7725_eagle_dma_1()
{
    ov7725_eagle_img_flag_1 = IMG_FINISH ;
    DMA_IRQ_CLEAN(CAMERA_DMA_CH);           //清除通道传输中断标志位
}

/*!
 *  @brief      鹰眼ov7725采集图像（采集到的数据存储在 初始化时配置的地址上）
 *  @since      v5.0
 */
void ov7725_eagle_get_img_1()    //非常重大的区别  好好区别一下 评估扩散范围
{
    ov7725_eagle_img_flag_1 = IMG_START;                   //开始采集图像
    if( 0 == img_switch_flag_1)
    {
       ov7725_eagle_img_buff_1 =imgbuff_sigal_2;
       img_switch_flag_1=1; 
    }
    else  
    {
       ov7725_eagle_img_buff_1 = imgbuff_sigal_1;
       img_switch_flag_1 = 0;
    }
    PORTC_ISFR = ~0;                        //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
    enable_irq(PORTC_IRQn);                         
//    while(ov7725_eagle_img_flag != IMG_FINISH)           //等待图像采集完毕
//    {
//        if(ov7725_eagle_img_flag == IMG_FAIL)            //假如图像采集错误，则重新开始采集
//        {
//            ov7725_eagle_img_flag = IMG_START;           //开始采集图像
//            PORTB_ISFR = ~0;                //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
//            enable_irq(PORTB_IRQn);                 //允许PTA的中断
//        }
//    }
}


/*OV7725初始化配置表*/
reg_s ov7725_eagle_reg_1[] =
{
    //寄存器，寄存器值次
    {OV7725_COM4         , 0x81},
    {OV7725_CLKRC        , 0x00},
    {OV7725_COM2         , 0x03},
    {OV7725_COM3         , 0xD0},
    {OV7725_COM7         , 0x40},
    {OV7725_HSTART       , 0x3F},
    {OV7725_HSIZE        , 0x50},
    {OV7725_VSTRT        , 0x03},
    {OV7725_VSIZE        , 0x78},
    {OV7725_HREF         , 0x00},
    {OV7725_SCAL0        , 0x0A},
    {OV7725_AWB_Ctrl0    , 0xE0},
    {OV7725_DSPAuto      , 0xff},
    {OV7725_DSP_Ctrl2    , 0x0C},
    {OV7725_DSP_Ctrl3    , 0x00},
    {OV7725_DSP_Ctrl4    , 0x00},

#if (CAMERA_W == 80)
    {OV7725_HOutSize     , 0x14},
#elif (CAMERA_W == 120)
    {OV7725_HOutSize     , 0x1e},
#elif (CAMERA_W == 160)
    {OV7725_HOutSize     , 0x28},    
#elif (CAMERA_W == 240)
    {OV7725_HOutSize     , 0x3c},
#elif (CAMERA_W == 320)
    {OV7725_HOutSize     , 0x50},
#else

#endif

#if (CAMERA_H == 140 )
    {OV7725_VOutSize     , 0x46},
#elif (CAMERA_H == 80 )
    {OV7725_VOutSize     , 0x28},
#elif (CAMERA_H == 100 )
    {OV7725_VOutSize     , 0x32},
#elif (CAMERA_H == 240 )
    {OV7725_VOutSize     , 0x78},
#else

#endif

    {OV7725_EXHCH        , 0x00},
    {OV7725_GAM1         , 0x0c},
    {OV7725_GAM2         , 0x16},
    {OV7725_GAM3         , 0x2a},
    {OV7725_GAM4         , 0x4e},
    {OV7725_GAM5         , 0x61},
    {OV7725_GAM6         , 0x6f},
    {OV7725_GAM7         , 0x7b},
    {OV7725_GAM8         , 0x86},
    {OV7725_GAM9         , 0x8e},
    {OV7725_GAM10        , 0x97},
    {OV7725_GAM11        , 0xa4},
    {OV7725_GAM12        , 0xaf},
    {OV7725_GAM13        , 0xc5},
    {OV7725_GAM14        , 0xd7},
    {OV7725_GAM15        , 0xe8},
    {OV7725_SLOP         , 0x20},
    {OV7725_LC_RADI      , 0x00},
    {OV7725_LC_COEF      , 0x13},
    {OV7725_LC_XC        , 0x08},
    {OV7725_LC_COEFB     , 0x14},
    {OV7725_LC_COEFR     , 0x17},
    {OV7725_LC_CTR       , 0x05},
    {OV7725_BDBase       , 0x99},
    {OV7725_BDMStep      , 0x03},
    {OV7725_SDE          , 0x04},
    {OV7725_BRIGHT       , 0x00},
    {OV7725_CNST         , 0x18},//南航赛场0x25 白天最好阈值0x17//摄像头1  //信标摄像头
    {OV7725_SIGN         , 0x06},
    {OV7725_UVADJ0       , 0x11},
    {OV7725_UVADJ1       , 0x02},

};

uint8 ov7725_eagle_cfgnum = ARR_SIZE( ov7725_eagle_reg_1 ) ; /*结构体数组成员数目*/


/*!
 *  @brief      鹰眼ov7725寄存器 初始化
 *  @return     初始化结果（0表示失败，1表示成功）
 *  @since      v5.0
 */
uint8 ov7725_eagle_reg_init_1(void)
{
    uint16 i = 0;
    uint8 Sensor_IDCode = 0;
    SCCB_GPIO_init_1();

    //OV7725_Delay_ms(50);
    if( 0 == SCCB_WriteByte_1 ( OV7725_COM7, 0x80 ) ) /*复位sensor */
    {
        DEBUG_PRINTF("\n警告:SCCB写数据错误");
        return 0 ;
    }

    OV7725_EAGLE_Delay_ms(50);

    if( 0 == SCCB_ReadByte_1( &Sensor_IDCode, 1, OV7725_VER ) )    /* 读取sensor ID号*/
    {
        DEBUG_PRINTF("\n警告:读取ID失败");
        return 0;
    }
    DEBUG_PRINTF("\nGet ID success，SENSOR ID is 0x%x", Sensor_IDCode);
    DEBUG_PRINTF("\nConfig Register Number is %d ", ov7725_eagle_cfgnum);
    if(Sensor_IDCode == OV7725_ID)
    {
        for( i = 0 ; i < ov7725_eagle_cfgnum ; i++ )
        {
            if( 0 == SCCB_WriteByte_1(ov7725_eagle_reg_1[i].addr, ov7725_eagle_reg_1[i].val) )
            {
                DEBUG_PRINTF("\n警告:写寄存器0x%x失败", ov7725_eagle_reg_1[i].addr);
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    DEBUG_PRINTF("\nOV7725 Register Config Success!");
    return 1;
}

//以上为摄像头1摄像头初始化函数文件
/*************************分界线*****************************************************************/
//以下为摄像头0摄像头初始化函数文件

uint8   *ov7725_eagle_img_buff;


volatile IMG_STATUS_e      ov7725_eagle_img_flag = IMG_START;   //图像状态

//内部函数声明
static uint8 ov7725_eagle_reg_init(void);
static void ov7725_eagle_port_init();


/*!
 *  @brief      鹰眼ov7725初始化
 *  @since      v5.0
 */
uint8 ov7725_eagle_init(uint8 *imgaddr) 
{
    ov7725_eagle_img_buff = imgaddr; 
    while(ov7725_eagle_reg_init() == 0); //鹰眼SCCB写寄存器初始化成功返回0
    ov7725_eagle_port_init();  //相关引脚初始化
   // enable_irq(PORTA_IRQn);     //初始化后开场中断，
    return 0;
}

/*!
 *  @brief      鹰眼ov7725管脚初始化（内部调用）
 *  @since      v5.0
 */
void ov7725_eagle_port_init()
{
    //DMA通道0初始化，PTA27触发源(默认上升沿)，源地址为PTB_B0_IN，目的地址为：IMG_BUFF，每次传输1Byte
    dma_portx2buff_init(OV7725_EAGLE_DMA_CH, (void *)&PTB_B2_IN, (void *)ov7725_eagle_img_buff, PTA15, DMA_BYTE1, OV7725_EAGLE_DMA_NUM, DADDR_KEEPON);

    DMA_DIS(OV7725_EAGLE_DMA_CH);
    disable_irq(PORTA_IRQn);                        //关闭PTB的中断，场中断
    DMA_IRQ_CLEAN(OV7725_EAGLE_DMA_CH);                   //清除通道传输中断标志位
    DMA_IRQ_EN(OV7725_EAGLE_DMA_CH);

    port_init(PTA15, ALT1 | DMA_FALLING | PULLDOWN );         //PCLK

    port_init(PTA16, ALT1 | IRQ_RISING  | PULLUP | PF);     //场中断，上拉，上降沿触发中断，带滤波

}

/*!
 *  @brief      鹰眼ov7725场中断服务函数
 *  @since      v5.0
 */
void ov7725_eagle_vsync(void) 
{

    //场中断需要判断是场结束还是场开始
    if(ov7725_eagle_img_flag == IMG_START)                   //需要开始采集图像
    {
        ov7725_eagle_img_flag = IMG_GATHER;                  //标记图像采集中
        disable_irq(PORTA_IRQn); //关闭场中断

#if 1

        PORTA_ISFR = 15 <<  PT1;            //清空PCLK标志位，PCk信号来了

        DMA_EN(OV7725_EAGLE_DMA_CH);                  //使能通道CHn 硬件请求
        PORTA_ISFR = 15 <<  PT1;            //清空PCLK标志位
        
        DMA_DADDR(OV7725_EAGLE_DMA_CH) = (uint32)ov7725_eagle_img_buff;    //恢复地址

#else
        PORTA_ISFR = 15 <<  PT1;            //清空PCLK标志位
        dma_repeat(OV7725_EAGLE_DMA_CH, (void *)&PTB_B2_IN, (void *)ov7725_eagle_img_buff,OV7725_EAGLE_DMA_NUM);
#endif
    }
    else                                        //图像采集错误
    {
        disable_irq(PORTA_IRQn);                        //关闭PTA的中断
        ov7725_eagle_img_flag = IMG_FAIL;                    //标记图像采集失败
    }
}

/*!
 *  @brief      鹰眼ov7725 DMA中断服务函数
 *  @since      v5.0
 */
void ov7725_eagle_dma()
{
    ov7725_eagle_img_flag = IMG_FINISH ;
    DMA_IRQ_CLEAN(OV7725_EAGLE_DMA_CH);           //清除通道传输中断标志位
}

/*!
 *  @brief      鹰眼ov7725采集图像（采集到的数据存储在 初始化时配置的地址上）
 *  @since      v5.0
 */
void ov7725_eagle_get_img()
{
    ov7725_eagle_img_flag = IMG_START;                   //开始采集图像
    if( 0 == img_switch_flag)
    {
       ov7725_eagle_img_buff =imgbuff_block_2;
       img_switch_flag=1;
    }
    else  
    {
       ov7725_eagle_img_buff = imgbuff_block_1;
       img_switch_flag = 0;
    }
    PORTA_ISFR = ~0;                        //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
    enable_irq(PORTA_IRQn);                         //允许PTA的中断
    
//    while(ov7725_eagle_img_flag != IMG_FINISH)           //等待图像采集完毕
//    {
//        if(ov7725_eagle_img_flag == IMG_FAIL)            //假如图像采集错误，则重新开始采集
//        {
//            ov7725_eagle_img_flag = IMG_START;           //开始采集图像
//            PORTB_ISFR = ~0;                //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
//            enable_irq(PORTB_IRQn);                 //允许PTA的中断
//        }
//    }
}


/*OV7725初始化配置表*/
reg_s ov7725_eagle_reg[] =
{
    //寄存器，寄存器值次
    {OV7725_COM4         , 0x81},
    {OV7725_CLKRC        , 0x00},
    {OV7725_COM2         , 0x03},
    {OV7725_COM3         , 0xD0},
    {OV7725_COM7         , 0x40},
    {OV7725_HSTART       , 0x3F},
    {OV7725_HSIZE        , 0x50},
    {OV7725_VSTRT        , 0x03},
    {OV7725_VSIZE        , 0x78},
    {OV7725_HREF         , 0x00},
    {OV7725_SCAL0        , 0x0A},
    {OV7725_AWB_Ctrl0    , 0xE0},
    {OV7725_DSPAuto      , 0xff},
    {OV7725_DSP_Ctrl2    , 0x0C},
    {OV7725_DSP_Ctrl3    , 0x00},
    {OV7725_DSP_Ctrl4    , 0x00},

#if (CAMERA_W == 80)
    {OV7725_HOutSize     , 0x14},
#elif (CAMERA_W == 120)
    {OV7725_HOutSize     , 0x1e},
#elif (CAMERA_W == 160)
    {OV7725_HOutSize     , 0x28},    
#elif (CAMERA_W == 240)
    {OV7725_HOutSize     , 0x3c},
#elif (CAMERA_W == 320)
    {OV7725_HOutSize     , 0x50},
#else

#endif

#if (CAMERA_H == 80 )
    {OV7725_VOutSize     , 0x28},
#elif (CAMERA_H == 40 )
    {OV7725_VOutSize     , 0x14},
#elif (CAMERA_H == 60 )
    {OV7725_VOutSize     , 0x1e},
#elif (CAMERA_H == 50 )
    {OV7725_VOutSize     , 0x19},
#else

#endif

    {OV7725_EXHCH        , 0x00},
    {OV7725_GAM1         , 0x0c},
    {OV7725_GAM2         , 0x16},
    {OV7725_GAM3         , 0x2a},
    {OV7725_GAM4         , 0x4e},
    {OV7725_GAM5         , 0x61},
    {OV7725_GAM6         , 0x6f},
    {OV7725_GAM7         , 0x7b},
    {OV7725_GAM8         , 0x86},
    {OV7725_GAM9         , 0x8e},
    {OV7725_GAM10        , 0x97},
    {OV7725_GAM11        , 0xa4},
    {OV7725_GAM12        , 0xaf},
    {OV7725_GAM13        , 0xc5},
    {OV7725_GAM14        , 0xd7},
    {OV7725_GAM15        , 0xe8},
    {OV7725_SLOP         , 0x20},
    {OV7725_LC_RADI      , 0x00},
    {OV7725_LC_COEF      , 0x13},
    {OV7725_LC_XC        , 0x08},
    {OV7725_LC_COEFB     , 0x14},
    {OV7725_LC_COEFR     , 0x17},
    {OV7725_LC_CTR       , 0x05},
    {OV7725_BDBase       , 0x99},
    {OV7725_BDMStep      , 0x03},
    {OV7725_SDE          , 0x04},
    {OV7725_BRIGHT       , 0x00},
    {OV7725_CNST         , 0x18},//摄像头0  晚上最好19 //偏振片加合适阈值可以排除黄线
    {OV7725_SIGN         , 0x06},
    {OV7725_UVADJ0       , 0x11},
    {OV7725_UVADJ1       , 0x02},

};

//uint8 ov7725_eagle_cfgnum = ARR_SIZE( ov7725_eagle_reg ) ; /*结构体数组成员数目*/


/*!
 *  @brief      鹰眼ov7725寄存器 初始化
 *  @return     初始化结果（0表示失败，1表示成功）
 *  @since      v5.0
 */
uint8 ov7725_eagle_reg_init(void)
{
    uint16 i = 0;
    uint8 Sensor_IDCode = 0;
    SCCB_GPIO_init();

    //OV7725_Delay_ms(50);
    if( 0 == SCCB_WriteByte ( OV7725_COM7, 0x80 ) ) /*复位sensor */
    {
        DEBUG_PRINTF("\n警告:SCCB写数据错误");
        return 0 ;
    }

    OV7725_EAGLE_Delay_ms(50);

    if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, OV7725_VER ) )    /* 读取sensor ID号*/
    {
        DEBUG_PRINTF("\n警告:读取ID失败");
        return 0;
    }
    DEBUG_PRINTF("\nGet ID success，SENSOR ID is 0x%x", Sensor_IDCode);
    DEBUG_PRINTF("\nConfig Register Number is %d ", ov7725_eagle_cfgnum);
    if(Sensor_IDCode == OV7725_ID)
    {
        for( i = 0 ; i < ov7725_eagle_cfgnum ; i++ )
        {
            if( 0 == SCCB_WriteByte(ov7725_eagle_reg[i].addr, ov7725_eagle_reg[i].val) )
            {
                DEBUG_PRINTF("\n警告:写寄存器0x%x失败", ov7725_eagle_reg[i].addr);
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    DEBUG_PRINTF("\nOV7725 Register Config Success!");
    return 1;
}
void Buffer_switch()
{
    if(0 != img_switch_flag_1){
      img_extract(img_1,imgbuff_sigal_1,OV7725_EAGLE_SIZE_1); 
    }
    else{
      img_extract(img_1,imgbuff_sigal_2,OV7725_EAGLE_SIZE_1);
    }

    if(0 != img_switch_flag){
      img_extract(img,imgbuff_block_1,OV7725_EAGLE_SIZE); 
    }
    else{
      img_extract(img,imgbuff_block_2,OV7725_EAGLE_SIZE);
    }
}