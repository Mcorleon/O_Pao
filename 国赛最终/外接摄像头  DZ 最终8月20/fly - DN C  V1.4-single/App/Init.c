#include "include.h" 
extern uint8 imgbuff_sigal_1[OV7725_EAGLE_SIZE_1];
extern uint8 imgbuff_sigal_2[OV7725_EAGLE_SIZE_1];
extern uint8 imgbuff_block_1[OV7725_EAGLE_SIZE]; 
extern uint8 imgbuff_block_2[OV7725_EAGLE_SIZE];  
extern uint8 img_switch_flag;
extern uint8 img_send_flag  ;
extern uint8 send_image_flag;
uint8 show_OLED_flag   ;
uint8 show_process_flag;
uint8 OLED_testing_flag;
uint8 LCD_sigal_flag   ;
uint8 LCD_block_flag   ;
uint8 Spec_testing_flag;
/********************************/
void Init() //��װ���
{
    gpio_init(PTB3,GPO,0);
    gpio_init(PTB9,GPO,0);
    ov7725_eagle_init(imgbuff_block_1)  ;
    ov7725_eagle_init_1(imgbuff_sigal_1);
    Tft_init()          ;
    LCD_Clear(BLUE)     ;
}
void Set_vector() //��װ���
{
    set_vector_handler (DMA0_VECTORn ,DMA0_IRQHandler) ;    //����DMA0���жϷ�����Ϊ DMA0_IRQHandler  
    set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //����PORTA���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA3_VECTORn ,DMA3_IRQHandler)  ;    //����DMA0���жϷ�����Ϊ DMA0_IRQHandler 
    set_vector_handler(PORTC_VECTORn ,PORTC_IRQHandler); 
}
void send_image() //��װ���
{
    if(0 == img_send_flag)
    {
      if(img_switch_flag != 0)
        vcan_sendimg(imgbuff_block_1, CAMERA_SIZE);                   //���͵���λ��
      else
        vcan_sendimg(imgbuff_block_2, CAMERA_SIZE);                  //���͵���λ��
    }
}

