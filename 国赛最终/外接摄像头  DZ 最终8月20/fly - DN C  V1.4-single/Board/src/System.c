/********************************ϵͳ��ʼ��**********************************
*
*����   �� ɳ���Ѿ�
*�ļ��� �� System.c
*����   �� ϵͳ��ʼ��
*ʱ��   �� 2015/11/9
˵��    ��ʹ��ɽ��V5.3��
*
****************************************************************************/
#include "System.h"
#include "include.h"

void System_init()
{  
        Tft_init();//��ʾ����ʼ��
        LCD_Clear(BLUE);//����
        OLED_init();
        //��ʼ������ͷ
        camera_init(img_buffer);                                  //�����趨  imgbuff Ϊ�ɼ�������������������

//        NVIC_SetPriorityGrouping(4);//�����жϷ�����      //�������ȼ�����,4bit ��ռ���ȼ�,û�������ȼ�
//        NVIC_SetPriority(PORTA_IRQn,0);         //�������ȼ�
//        NVIC_SetPriority(DMA0_IRQn,0);           //�������ȼ�
//        NVIC_SetPriority(PORTE_IRQn,1);         //�������ȼ�
//        NVIC_SetPriority(UART0_RX_TX_IRQn,1);         //�������ȼ�
        
//        NVIC_SetPriority(PIT0_IRQn,2);          //�������ȼ�
//        NVIC_SetPriority(PIT2_IRQn,3);          //�������ȼ�
         
        set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //����PORTA���жϷ�����Ϊ PORTA_IRQHandler ����ͷ���ж� ����Ҫʹ��
        set_vector_handler(DMA0_VECTORn ,DMA0_IRQHandler);      //����DMA0���жϷ�����Ϊ DMA0_IRQHandler  ��������ͷ
        
        uart_init(UART1,115200);                               //ZigBeeͨ�Ŵ��ڳ�ʼ��        
        set_vector_handler(UART1_RX_TX_VECTORn,uart1_handler); //ZigBeeͨ�Ŵ����ж�
        uart_rx_irq_en (UART1);                                //ʹ��ZigBee�����ж�
 
        Key_init();                                            //������ʼ�� 
        
        nrf_init();
        set_vector_handler(PORTB_VECTORn ,PORTB_IRQHandler);    //NRF�ж�
        enable_irq(PORTB_IRQn); //ʹ��NRF�ж�
        
        
        Caosheng_init();
        Buzzer_init();           //��������ʼ��     
        Servo_Motor_init();       //�����ʼ��
        Motor_init();            //�����ʼ��	       
        
        ADC_init();
        BM_init();               //���뿪�س�ʼ��
        
        pit_init_ms(PIT0,13);     //��ʼ��PIT0,��ʱʱ��Ϊ�� 13ms
        set_vector_handler(PIT0_VECTORn,PIT0_IRQHandler);
        enable_irq (PIT0_IRQn);    //����PIT0��ʱ���ж�
        
        pit_init_ms(PIT2,1); 
        set_vector_handler(PIT2_VECTORn,PIT2_IRQHandler);
        enable_irq(PIT2_IRQn);
        
        RED_init();               //���Թ�
        beep();
        
        if(0==BM2)
        Turn_state=0x52;
        else
          Turn_state=0x51;
          
        Current_Turn_state = Turn_state & Texting_state;//�ж�Current_Turn_state�Ƿ�Ϊ0������ת��0��1�� 
        Texting_state = Texting_state << 1;
}

void Caosheng_init()
{
  gpio_init (PTE10, GPI,0);
  gpio_init (PTE12, GPI,0);
  port_init (PTE12, IRQ_EITHER | PF | ALT1 );
  set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler);    //�������ж�
  enable_irq(PORTE_IRQn); //ʹ�ܳ������ж�
}

void ADC_init()
{
  adc_init(ADC1_SE6a);       //power_adc   
}

void Buzzer_init()
{
  gpio_init(PTE5,GPO,0);
}

void beep()
{
  gpio_set (PTE5, 1);
  DELAY_MS(20);
  gpio_set (PTE5, 0);
}

void didi()
{
  beep();
  DELAY_MS(100);
  beep();
}

void Key_init()
{
  gpio_init (PTA10, GPI,0);
  gpio_init (PTA9, GPI,0);
  gpio_init (PTA17, GPI,0);
  gpio_init (PTA16, GPI,0);
  
  port_init(PTA10, IRQ_FALLING | PF | ALT1 |PULLUP);
  port_init(PTA9, ALT1 |PULLUP);
  port_init(PTA17, ALT1 |PULLUP);
  port_init(PTA16, ALT1 |PULLUP);
}


void BM_init()
{
  gpio_ddr (PTC11, GPI); 
  gpio_ddr (PTC10, GPI);
  gpio_ddr (PTC9, GPI);
  gpio_ddr (PTC8, GPI);
  gpio_ddr (PTC7, GPI);
  gpio_ddr (PTC6, GPI);
  gpio_ddr (PTC5, GPI);
  gpio_ddr (PTC4, GPI);
  
  
  port_init(PTC11,ALT1 |PULLUP);
  port_init(PTC10,ALT1 |PULLUP);
  port_init(PTC9,ALT1 |PULLUP);
  port_init(PTC8,ALT1 |PULLUP);
  port_init(PTC7,ALT1 |PULLUP);
  port_init(PTC6,ALT1 |PULLUP);
  port_init(PTC5,ALT1 |PULLUP);
  port_init(PTC4,ALT1 |PULLUP);
}

float Battery_voltage()
{
        uint16 ad_value;    
        uint16 value[15];
        float  voltage;
        value[0] = adc_once(ADC1_SE6a,ADC_12bit);
        value[1] = adc_once(ADC1_SE6a,ADC_12bit);
        value[2] = adc_once(ADC1_SE6a,ADC_12bit);
        value[3] = adc_once(ADC1_SE6a,ADC_12bit);
        value[4] = adc_once(ADC1_SE6a,ADC_12bit);
        value[5] = adc_once(ADC1_SE6a,ADC_12bit);
        value[6] = adc_once(ADC1_SE6a,ADC_12bit);
        value[7] = adc_once(ADC1_SE6a,ADC_12bit);
        value[8] = adc_once(ADC1_SE6a,ADC_12bit);
        value[9] = adc_once(ADC1_SE6a,ADC_12bit);
        value[10] = adc_once(ADC1_SE6a,ADC_12bit);
        value[11] = adc_once(ADC1_SE6a,ADC_12bit);
        value[12] = adc_once(ADC1_SE6a,ADC_12bit);
        value[13] = adc_once(ADC1_SE6a,ADC_12bit);
        value[14] = adc_once(ADC1_SE6a,ADC_12bit);
        ad_value=(value[0]+value[1]+value[2]+value[3]+value[4]+value[5]+value[6]+value[7]+value[8]+value[9]+value[10]+value[11]+value[12]+value[13]+value[14])/15;
//        LED_PrintValueI4(0,7,ad_value);
        voltage = (float)(ad_value)*0.002384175; // 0.002360 = (3.3/2^12)*(300/100) 
        adc_stop(ADC1);
        return(voltage);              
}
//void beepms(uint8 ms)//ʹ���ж�
//{
//    if(beep_flag==1)
//    { 
//        BEEP = 1;
//      //  stop++;
//        beep_flag=0;   
//        pit_init_ms(PIT3,150);
//        enable_irq (PIT3_IRQn);
//    }
//}
void RED_init()
{
  gpio_init(PTD2,GPI,0); //���ܺ���
  gpio_init(PTD3,GPI,0);
  gpio_init(PTD0,GPI,0);
  gpio_init(PTD11,GPI,0);
  gpio_init(PTD12,GPI,0);
  gpio_init(PTD13,GPI,0);
}
/******************************************************
* @author : WWW
* @function name : OLED_Show_Road
* @ data : 2016/1/28
* @function description : oled��ʾ����
******************************************************/
void OLED_Show_Road()
{
    uint8 i,j;
    uint8 left,right;
    uint8 mid;
    uint8 TLline[CAMERA_H];
    uint8 TRline[CAMERA_H];
    uint8 TMline[CAMERA_H]; 
      
    for(i=0;i<60;i++)
    {
        TLline[i]=(uint8)(Lline[i*2]/2);
        TRline[i]=(uint8)(Rline[i*2]/2);
        if( Mline[i*2] < 0)
         TMline[i] = 0 ;
        else if( Mline[i*2] > 159)
          TMline[i] = 79;
        else if( Mline[i*2] > 0 && Mline[i*2] <159 )
          TMline[i] = (uint8)(Mline[i*2]/2);
    }     
    //���������߽�
   for(i=0;i<8;i++)
   {
     LED_Set_Pos(4,i);	     
     LED_WrDat(0xff);	
   }
   for(i=0;i<8;i++)
   {
     LED_Set_Pos(92,i);	     
     LED_WrDat(0xff);	
   }
   //�����ʾ��
   for(i=0;i<8;i++)
   {
     for(j=0;j<80;j++)
     {
       LCDRAM[i][j]=0;
     }
   }
 
   for(i=0;i<60;i++)
   {
     left=TLline[i];
     LCDRAM[i/8][left]=LCDRAM[i/8][left]|(0x01<<(i%8));
   }

   for(i=0;i<60;i++)
   {
     right=TRline[i];
     LCDRAM[i/8][right]=LCDRAM[i/8][right]|(0x01<<(i%8));
   }
   //������
     for(i=0;i<60;i++)
     {
      mid=TMline[i];
       LCDRAM[i/8][mid]=LCDRAM[i/8][mid]|(0x01<<(i%8));
     }   
   for(i=8;i>0;i--)
   {
     LED_Set_Pos(9,i-1);				
     for(j=0;j<80;j++)
     {      
         LED_WrDat(LCDRAM[i-1][j]);	    	
     }
   }
   LED_PrintValueF(96,0,camer.speed_control_error, 0);
}

void show_img()//120*160
{
    uint8 i,j;
     //�����ʾ��
   for(i=0;i<8;i++)
   {
     for(j=0;j<80;j++)
     {
       LCDRAM[i][j]=0;
     }
   }
  for(j=0;j<80;j++)
  {
    for(i=0;i<60;i++)
    {
        if(img_handle[i*2][j*2]==255)
           LCDRAM[i/8][j]=LCDRAM[i/8][j]|(0x01<<(i%8));
    }  
  }
     //��ʾ
   for(i=8;i>0;i--)
   {
     LED_Set_Pos(9,i-1);				
     for(j=0;j<80;j++)
     {      
         LED_WrDat(LCDRAM[i-1][j]);	    	
     }
   }

}

