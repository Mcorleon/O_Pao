#include "include.h"
#include "overtake.h"

void overtake()
{
//  if( Front_flag == 255 && Car_Stop_flag == 1 && Ultrasonic_flag == 1)
//  {
//    Car_Stop_flag=0;
//    Ultrasonic_flag = 0;
//  }
//  Ultrasonic_flag = 0;
  last_ring_state = current_ring_state;
  current_ring_state = HX_STATE;  //HX_OUT=1     HX_BFFORE=2     HX_ON=3
//  if(current_ring_state == HX_BEFORE && last_ring_state == HX_NORMAL)
//  {
//    start_up = 0;
//    
//  }
//  if(current_ring_state == HX_ON && last_ring_state == HX_BEFORE && Front_flag == 255)
//  {
//    nrf_txbuff1[0] = 46;
//    nrf_txbuff1[1] = 64;
//    nrf_txbuff1[2] = 1;
//    uart_putstr (UART1 ,nrf_txbuff1); //发送字符串
//  }
  if(current_ring_state == HX_NORMAL && last_ring_state == HX_OUT )
  {
    Current_Turn_state = Turn_state & Texting_state;//判定Current_Turn_state是否为0来左右转；0左1右 
    Texting_state = Texting_state << 1;
    if(Texting_state == 0x20)//0010 0000
    {
      Texting_state = 0x01;
    } 
    HX_text = 0;
//    Front_flag = ~Front_flag;
  }  
  
}
