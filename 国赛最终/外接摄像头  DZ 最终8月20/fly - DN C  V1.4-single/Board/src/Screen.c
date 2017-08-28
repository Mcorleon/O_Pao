#include  "include.h"    
#include "Screen.h"
#include "LCD.h"

extern uint8 img[CAMERA_H][CAMERA_W];
extern uint8 img_1[CAMERA_H][CAMERA_W];
extern int16  Vdiffer;
extern float  Vdiff_Ratio;
extern int16 Left_line_B[CAMERA_H];
extern int16 Right_line_B[CAMERA_H];
extern int16 Left_line_A[CAMERA_H];
extern int16 Right_line_A[CAMERA_H];
extern float Middle_line[CAMERA_H];
void ScreenShow(uint8 t)
{
   
//   if(TFT_clear_flag == 1)
//   {
//      if(t == IMAGE)
//        LCD_Clear(BLUE);
//      else if(t == DATA)
//        LCD_Clear(WHITE);
//      TFT_clear_flag = 0;
//   }
  if(t == IMAGE)
  {
      LCD_img(); 
  }
   else if(t == DATA)
  {
      //LCD_data();
  }
   //LCD_ShowNum(0,121,(int32)(voltage),2);
   //LCD_ShowNum(0,123,(int32)(voltage),2);
}
void LCD_img(void)
{
//  uint8* string;
  int i,j;
  ////////在图像中画出三条线/////////////
  uint8 (*img_point)[160]=img;
  uint8* imgh_p;
  float* m=Middle_line;
  int16* l=Left_line_B;
  int16* r=Right_line_B;
  for(i=0;i<CAMERA_H;i++)
  {
    imgh_p = *(img_point);
    if(*m > -1 && *m < 160)
      *(imgh_p+(int)(*m)) = 20;
    if(*l > -1 && *l < 160)
      *(imgh_p+*l) = 10;
    if(*r > -1 && *r < 160)
      *(imgh_p+*r) = 30;
    img_point ++;
    m ++;
    l ++;
    r ++;
  }
  ////////////显示图像/////////////////////
  Address_set(0,0,CAMERA_W-1,CAMERA_H-1);
  for(i=0;i<CAMERA_H;i++)
  {
    for(j=0;j<CAMERA_W;j++)
    {
      if(j == 80)       LCD_Write_Data2(BLUE);
      else
      {
        switch(img[i][j])
        {
        case 0:
          LCD_Write_Data2(BLACK);
          break;
        case 10:
          LCD_Write_Data2(RED);
          break;
        case 20:
          LCD_Write_Data2(BLUE);
          break;
        case 30:
          LCD_Write_Data2(GREEN);
          break;
        case 255:
          LCD_Write_Data2(WHITE);
          break;
        default:
          LCD_Write_Data2(BLACK);
        }
      }
    }
  }
//  if(servos.diretion_current_error>=0)
//    LCD_ShowNum(3,3,servos.diretion_current_error,3);
//  else
//    LCD_ShowNum(3,3,-servos.diretion_current_error,3);
//  if(circle_flag)
//  {
//    switch(circle_flag)
//    {
//    case 1:
//      string = "LEFT ";break;
//    case 2:
//      string = "LEFIN";break;
//    case 3:
//      string = "LEOUT";break;
//    case 4:
//      string = "LECIR";break;
//    default:
//      break;
//    }
//      LCD_ShowString(9,0,string);
//  }
//  else
//  {
//      string = "EMPTY";
//      LCD_ShowString(9,0,string);
//  }
//  switch(track_cross)
//  {
//  case 1:
//    {
//      string = "1";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  case 2:
//    {
//      string = "2";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  case 3:
//    {
//      string = "3";
//      LCD_ShowString(45,0,string);
//      break;
//    }
//  case 4:
//    {
//      string = "4";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  case 5:
//    {
//      string = "5";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  case 6:
//    {
//      string = "6";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  case 7:
//    {
//      string = "7";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  default:
//    break;
//  }
}

void LCD_img_1(void)
{
//  uint8* string;
  int i,j;
  ////////在图像中画出三条线/////////////
  uint8 (*img_point)[160]=img_1;
  uint8* imgh_p;
  float* m=Middle_line;
  int16* l=Left_line_A;
  int16* r=Right_line_A;
  for(i=0;i<CAMERA_H;i++)
  {
    imgh_p = *(img_point);
    if(*m > -1 && *m < 160)
      *(imgh_p+(int)(*m)) = 20;
    if(*l > -1 && *l < 160)
      *(imgh_p+*l) = 10;
    if(*r > -1 && *r < 160)
      *(imgh_p+*r) = 30;
    img_point ++;
    m ++;
    l ++;
    r ++;
  }
  ////////////显示图像/////////////////////
  Address_set(0,0,CAMERA_W-1,CAMERA_H-1);
  for(i=0;i<CAMERA_H;i++)
  {
    for(j=0;j<CAMERA_W;j++)
    {
      if(j == 80)       LCD_Write_Data2(BLUE);
      else
      {
        switch(img_1[i][j])
        {
        case 0:
          LCD_Write_Data2(BLACK);
          break;
        case 10:
          LCD_Write_Data2(RED);
          break;
        case 20:
          LCD_Write_Data2(BLUE);
          break;
        case 30:
          LCD_Write_Data2(GREEN);
          break;
        case 255:
          LCD_Write_Data2(WHITE);
          break;
        default:
          LCD_Write_Data2(BLACK);
        }
      }
    }
  }
//  if(servos.diretion_current_error>=0)
//    LCD_ShowNum(3,3,servos.diretion_current_error,3);
//  else
//    LCD_ShowNum(3,3,-servos.diretion_current_error,3);
//  if(circle_flag)
//  {
//    switch(circle_flag)
//    {
//    case 1:
//      string = "LEFT ";break;
//    case 2:
//      string = "LEFIN";break;
//    case 3:
//      string = "LEOUT";break;
//    case 4:
//      string = "LECIR";break;
//    default:
//      break;
//    }
//      LCD_ShowString(9,0,string);
//  }
//  else
//  {
//      string = "EMPTY";
//      LCD_ShowString(9,0,string);
//  }
//  switch(track_cross)
//  {
//  case 1:
//    {
//      string = "1";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  case 2:
//    {
//      string = "2";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  case 3:
//    {
//      string = "3";
//      LCD_ShowString(45,0,string);
//      break;
//    }
//  case 4:
//    {
//      string = "4";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  case 5:
//    {
//      string = "5";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  case 6:
//    {
//      string = "6";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  case 7:
//    {
//      string = "7";
//      LCD_ShowString(0,0,string);
//      break;
//    }
//  default:
//    break;
//  }
}
/*************************************************************************
函数名称：void LCD_data()
入口参数：无
出口参数：无
修改时间：2017/1/16
功能说明：TFT显示数据
备注：TFT横向19个字符，纵向8字符，即每个字符为16*9
************************************************************************/