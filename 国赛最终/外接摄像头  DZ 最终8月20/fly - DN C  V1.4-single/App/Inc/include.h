#ifndef __INCLUDE_H__
#define __INCLUDE_H__
#include  "common.h"

/*
 * Include 用户自定义的头文件
 */
#include  "MK60_wdog.h"
#include  "MK60_gpio.h"      //IO口操作
#include  "MK60_uart.h"      //串口
#include  "MK60_SysTick.h"
#include  "MK60_lptmr.h"     //低功耗定时器(延时)
#include  "MK60_pit.h"       //PIT
#include  "MK60_FLASH.h"     //FLASH
#include  "MK60_FTM.h"       //FTM
#include  "MK60_sdhc.h"      //SDHC
#include  "MK60_spi.h"       //SPI
#include  "MK60_adc.h"       //ADC
#include  "MK60_dma.h"       //DMA
#include  "MK60_i2c.h"       //I2C
#include  "MK60_it.h"        //isr


#include  "VCAN_LED.H"          //LED
#include  "VCAN_KEY.H"          //KEY
#include  "VCAN_SCCB.h"         //OV摄像头配置总线SCCB函数库
#include  "VCAN_camera.h"       
#include  "VCAN_OV7725_REG.h"   
#include  "VCAN_NRF24L0.h"           
#include  "ff.h"                //FatFs
#include  "io.h"


#include  "lcd.h"
#include  "Key.h"
//#include  "Dis.h"
#include "Screen.h"
      
#include  "VCAN_computer.h"     //多功能调试助手
//#include  "外部变量定义声明"
#include  "lcd.h"
#include  "Screen.h"
#include "Init.h"
#include "OLED.h" 

#endif
