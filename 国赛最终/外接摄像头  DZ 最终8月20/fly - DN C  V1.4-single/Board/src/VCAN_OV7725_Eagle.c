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
uint8   *ov7725_eagle_img_buff_1; //  ��ov7725_eagle_img_buff  û�к����_1


volatile IMG_STATUS_e      ov7725_eagle_img_flag_1 = IMG_START;   //ͼ��״̬

//�ڲ���������
static uint8 ov7725_eagle_reg_init_1(void);
static void ov7725_eagle_port_init_1();


/*!
 *  @brief      ӥ��ov7725��ʼ��
 *  @since      v5.0
 */
uint8 ov7725_eagle_init_1(uint8 *imgaddr) //�����������  ����û�� _1
{
    ov7725_eagle_img_buff_1 = imgaddr; 
    while(ov7725_eagle_reg_init_1() == 0); //ӥ��SCCBд�Ĵ�����ʼ���ɹ�����0
    ov7725_eagle_port_init_1();  //������ų�ʼ��
  //  enable_irq(PORTB_IRQn);     //��ʼ���󿪳��жϣ� // ��Ache��������  
    return 0;
}

/*!
 *  @brief      ӥ��ov7725�ܽų�ʼ�����ڲ����ã�
 *  @since      v5.0
 */
void ov7725_eagle_port_init_1()
{
    //DMAͨ��0��ʼ����PTA27����Դ(Ĭ��������)��Դ��ַΪPTB_B0_IN��Ŀ�ĵ�ַΪ��IMG_BUFF��ÿ�δ���1Byte
    dma_portx2buff_init(OV7725_EAGLE_DMA_CH_1, (void *)&PTD_B0_IN, (void *)ov7725_eagle_img_buff_1, PTC16, DMA_BYTE1,OV7725_EAGLE_DMA_NUM_1, DADDR_KEEPON);

    DMA_DIS(OV7725_EAGLE_DMA_CH_1);
    disable_irq(PORTC_IRQn);                        //�ر�PTB���жϣ����ж�
    DMA_IRQ_CLEAN(OV7725_EAGLE_DMA_CH_1);                   //���ͨ�������жϱ�־λ
    DMA_IRQ_EN(OV7725_EAGLE_DMA_CH_1);

    port_init(PTC16, ALT1 | DMA_FALLING | PULLDOWN );         //PCLK

    port_init(PTC17, ALT1 | IRQ_RISING  | PULLUP | PF);     //���жϣ��������Ͻ��ش����жϣ����˲�

}

/*!
 *  @brief      ӥ��ov7725���жϷ�����
 *  @since      v5.0
 */
void ov7725_eagle_vsync_1(void) 
{

    //���ж���Ҫ�ж��ǳ��������ǳ���ʼ
    if(ov7725_eagle_img_flag_1 == IMG_START)                   //��Ҫ��ʼ�ɼ�ͼ��
    {
        ov7725_eagle_img_flag_1 = IMG_GATHER;                  //���ͼ��ɼ���
        disable_irq(PORTC_IRQn); //�رճ��ж�

#if 1

        PORTC_ISFR = 16 <<  PT16;            //���PCLK��־λ��PCk�ź�����

        DMA_EN(OV7725_EAGLE_DMA_CH_1);                  //ʹ��ͨ��CHn Ӳ������
        PORTC_ISFR = 16 <<  PT16;            //���PCLK��־λ
        
        DMA_DADDR(OV7725_EAGLE_DMA_CH_1) = (uint32)ov7725_eagle_img_buff_1;    //�ָ���ַ

#else
        PORTC_ISFR = 16 <<  PT16;            //���PCLK��־λ
        dma_repeat(OV7725_EAGLE_DMA_CH_1, (void *)&PTD_B0_IN, (void *)ov7725_eagle_img_buff,OV7725_EAGLE_DMA_NUM_1);
#endif
    }
    else                                        //ͼ��ɼ�����
    {
        disable_irq(PORTC_IRQn);                        //�ر�PTA���ж�
        ov7725_eagle_img_flag_1 = IMG_FAIL;                    //���ͼ��ɼ�ʧ��
    }
}

/*!
 *  @brief      ӥ��ov7725 DMA�жϷ�����
 *  @since      v5.0
 */
void ov7725_eagle_dma_1()
{
    ov7725_eagle_img_flag_1 = IMG_FINISH ;
    DMA_IRQ_CLEAN(CAMERA_DMA_CH);           //���ͨ�������жϱ�־λ
}

/*!
 *  @brief      ӥ��ov7725�ɼ�ͼ�񣨲ɼ��������ݴ洢�� ��ʼ��ʱ���õĵ�ַ�ϣ�
 *  @since      v5.0
 */
void ov7725_eagle_get_img_1()    //�ǳ��ش������  �ú�����һ�� ������ɢ��Χ
{
    ov7725_eagle_img_flag_1 = IMG_START;                   //��ʼ�ɼ�ͼ��
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
    PORTC_ISFR = ~0;                        //д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
    enable_irq(PORTC_IRQn);                         
//    while(ov7725_eagle_img_flag != IMG_FINISH)           //�ȴ�ͼ��ɼ����
//    {
//        if(ov7725_eagle_img_flag == IMG_FAIL)            //����ͼ��ɼ����������¿�ʼ�ɼ�
//        {
//            ov7725_eagle_img_flag = IMG_START;           //��ʼ�ɼ�ͼ��
//            PORTB_ISFR = ~0;                //д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
//            enable_irq(PORTB_IRQn);                 //����PTA���ж�
//        }
//    }
}


/*OV7725��ʼ�����ñ�*/
reg_s ov7725_eagle_reg_1[] =
{
    //�Ĵ������Ĵ���ֵ��
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
    {OV7725_CNST         , 0x18},//�Ϻ�����0x25 ���������ֵ0x17//����ͷ1  //�ű�����ͷ
    {OV7725_SIGN         , 0x06},
    {OV7725_UVADJ0       , 0x11},
    {OV7725_UVADJ1       , 0x02},

};

uint8 ov7725_eagle_cfgnum = ARR_SIZE( ov7725_eagle_reg_1 ) ; /*�ṹ�������Ա��Ŀ*/


/*!
 *  @brief      ӥ��ov7725�Ĵ��� ��ʼ��
 *  @return     ��ʼ�������0��ʾʧ�ܣ�1��ʾ�ɹ���
 *  @since      v5.0
 */
uint8 ov7725_eagle_reg_init_1(void)
{
    uint16 i = 0;
    uint8 Sensor_IDCode = 0;
    SCCB_GPIO_init_1();

    //OV7725_Delay_ms(50);
    if( 0 == SCCB_WriteByte_1 ( OV7725_COM7, 0x80 ) ) /*��λsensor */
    {
        DEBUG_PRINTF("\n����:SCCBд���ݴ���");
        return 0 ;
    }

    OV7725_EAGLE_Delay_ms(50);

    if( 0 == SCCB_ReadByte_1( &Sensor_IDCode, 1, OV7725_VER ) )    /* ��ȡsensor ID��*/
    {
        DEBUG_PRINTF("\n����:��ȡIDʧ��");
        return 0;
    }
    DEBUG_PRINTF("\nGet ID success��SENSOR ID is 0x%x", Sensor_IDCode);
    DEBUG_PRINTF("\nConfig Register Number is %d ", ov7725_eagle_cfgnum);
    if(Sensor_IDCode == OV7725_ID)
    {
        for( i = 0 ; i < ov7725_eagle_cfgnum ; i++ )
        {
            if( 0 == SCCB_WriteByte_1(ov7725_eagle_reg_1[i].addr, ov7725_eagle_reg_1[i].val) )
            {
                DEBUG_PRINTF("\n����:д�Ĵ���0x%xʧ��", ov7725_eagle_reg_1[i].addr);
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

//����Ϊ����ͷ1����ͷ��ʼ�������ļ�
/*************************�ֽ���*****************************************************************/
//����Ϊ����ͷ0����ͷ��ʼ�������ļ�

uint8   *ov7725_eagle_img_buff;


volatile IMG_STATUS_e      ov7725_eagle_img_flag = IMG_START;   //ͼ��״̬

//�ڲ���������
static uint8 ov7725_eagle_reg_init(void);
static void ov7725_eagle_port_init();


/*!
 *  @brief      ӥ��ov7725��ʼ��
 *  @since      v5.0
 */
uint8 ov7725_eagle_init(uint8 *imgaddr) 
{
    ov7725_eagle_img_buff = imgaddr; 
    while(ov7725_eagle_reg_init() == 0); //ӥ��SCCBд�Ĵ�����ʼ���ɹ�����0
    ov7725_eagle_port_init();  //������ų�ʼ��
   // enable_irq(PORTA_IRQn);     //��ʼ���󿪳��жϣ�
    return 0;
}

/*!
 *  @brief      ӥ��ov7725�ܽų�ʼ�����ڲ����ã�
 *  @since      v5.0
 */
void ov7725_eagle_port_init()
{
    //DMAͨ��0��ʼ����PTA27����Դ(Ĭ��������)��Դ��ַΪPTB_B0_IN��Ŀ�ĵ�ַΪ��IMG_BUFF��ÿ�δ���1Byte
    dma_portx2buff_init(OV7725_EAGLE_DMA_CH, (void *)&PTB_B2_IN, (void *)ov7725_eagle_img_buff, PTA15, DMA_BYTE1, OV7725_EAGLE_DMA_NUM, DADDR_KEEPON);

    DMA_DIS(OV7725_EAGLE_DMA_CH);
    disable_irq(PORTA_IRQn);                        //�ر�PTB���жϣ����ж�
    DMA_IRQ_CLEAN(OV7725_EAGLE_DMA_CH);                   //���ͨ�������жϱ�־λ
    DMA_IRQ_EN(OV7725_EAGLE_DMA_CH);

    port_init(PTA15, ALT1 | DMA_FALLING | PULLDOWN );         //PCLK

    port_init(PTA16, ALT1 | IRQ_RISING  | PULLUP | PF);     //���жϣ��������Ͻ��ش����жϣ����˲�

}

/*!
 *  @brief      ӥ��ov7725���жϷ�����
 *  @since      v5.0
 */
void ov7725_eagle_vsync(void) 
{

    //���ж���Ҫ�ж��ǳ��������ǳ���ʼ
    if(ov7725_eagle_img_flag == IMG_START)                   //��Ҫ��ʼ�ɼ�ͼ��
    {
        ov7725_eagle_img_flag = IMG_GATHER;                  //���ͼ��ɼ���
        disable_irq(PORTA_IRQn); //�رճ��ж�

#if 1

        PORTA_ISFR = 15 <<  PT1;            //���PCLK��־λ��PCk�ź�����

        DMA_EN(OV7725_EAGLE_DMA_CH);                  //ʹ��ͨ��CHn Ӳ������
        PORTA_ISFR = 15 <<  PT1;            //���PCLK��־λ
        
        DMA_DADDR(OV7725_EAGLE_DMA_CH) = (uint32)ov7725_eagle_img_buff;    //�ָ���ַ

#else
        PORTA_ISFR = 15 <<  PT1;            //���PCLK��־λ
        dma_repeat(OV7725_EAGLE_DMA_CH, (void *)&PTB_B2_IN, (void *)ov7725_eagle_img_buff,OV7725_EAGLE_DMA_NUM);
#endif
    }
    else                                        //ͼ��ɼ�����
    {
        disable_irq(PORTA_IRQn);                        //�ر�PTA���ж�
        ov7725_eagle_img_flag = IMG_FAIL;                    //���ͼ��ɼ�ʧ��
    }
}

/*!
 *  @brief      ӥ��ov7725 DMA�жϷ�����
 *  @since      v5.0
 */
void ov7725_eagle_dma()
{
    ov7725_eagle_img_flag = IMG_FINISH ;
    DMA_IRQ_CLEAN(OV7725_EAGLE_DMA_CH);           //���ͨ�������жϱ�־λ
}

/*!
 *  @brief      ӥ��ov7725�ɼ�ͼ�񣨲ɼ��������ݴ洢�� ��ʼ��ʱ���õĵ�ַ�ϣ�
 *  @since      v5.0
 */
void ov7725_eagle_get_img()
{
    ov7725_eagle_img_flag = IMG_START;                   //��ʼ�ɼ�ͼ��
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
    PORTA_ISFR = ~0;                        //д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
    enable_irq(PORTA_IRQn);                         //����PTA���ж�
    
//    while(ov7725_eagle_img_flag != IMG_FINISH)           //�ȴ�ͼ��ɼ����
//    {
//        if(ov7725_eagle_img_flag == IMG_FAIL)            //����ͼ��ɼ����������¿�ʼ�ɼ�
//        {
//            ov7725_eagle_img_flag = IMG_START;           //��ʼ�ɼ�ͼ��
//            PORTB_ISFR = ~0;                //д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
//            enable_irq(PORTB_IRQn);                 //����PTA���ж�
//        }
//    }
}


/*OV7725��ʼ�����ñ�*/
reg_s ov7725_eagle_reg[] =
{
    //�Ĵ������Ĵ���ֵ��
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
    {OV7725_CNST         , 0x18},//����ͷ0  �������19 //ƫ��Ƭ�Ӻ�����ֵ�����ų�����
    {OV7725_SIGN         , 0x06},
    {OV7725_UVADJ0       , 0x11},
    {OV7725_UVADJ1       , 0x02},

};

//uint8 ov7725_eagle_cfgnum = ARR_SIZE( ov7725_eagle_reg ) ; /*�ṹ�������Ա��Ŀ*/


/*!
 *  @brief      ӥ��ov7725�Ĵ��� ��ʼ��
 *  @return     ��ʼ�������0��ʾʧ�ܣ�1��ʾ�ɹ���
 *  @since      v5.0
 */
uint8 ov7725_eagle_reg_init(void)
{
    uint16 i = 0;
    uint8 Sensor_IDCode = 0;
    SCCB_GPIO_init();

    //OV7725_Delay_ms(50);
    if( 0 == SCCB_WriteByte ( OV7725_COM7, 0x80 ) ) /*��λsensor */
    {
        DEBUG_PRINTF("\n����:SCCBд���ݴ���");
        return 0 ;
    }

    OV7725_EAGLE_Delay_ms(50);

    if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, OV7725_VER ) )    /* ��ȡsensor ID��*/
    {
        DEBUG_PRINTF("\n����:��ȡIDʧ��");
        return 0;
    }
    DEBUG_PRINTF("\nGet ID success��SENSOR ID is 0x%x", Sensor_IDCode);
    DEBUG_PRINTF("\nConfig Register Number is %d ", ov7725_eagle_cfgnum);
    if(Sensor_IDCode == OV7725_ID)
    {
        for( i = 0 ; i < ov7725_eagle_cfgnum ; i++ )
        {
            if( 0 == SCCB_WriteByte(ov7725_eagle_reg[i].addr, ov7725_eagle_reg[i].val) )
            {
                DEBUG_PRINTF("\n����:д�Ĵ���0x%xʧ��", ov7725_eagle_reg[i].addr);
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