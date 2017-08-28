#include  "include.h"    
#include "Screen.h"
#include "LCD.h"

extern uint8 img[CAMERA_H][CAMERA_W];
extern uint8 img_1[CAMERA_H][CAMERA_W];
extern int16  Vdiffer;
extern float  Vdiff_Ratio;
extern int16 Block_left_line[CAMERA_H];
extern int16 Block_right_line[CAMERA_H];
extern int16 Left_line[CAMERA_H];
extern int16 Right_line[CAMERA_H];
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
    //  LCD_data();
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
  int16* l=Block_left_line;
  int16* r=Block_right_line;
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
  int16* l=Left_line;
  int16* r=Right_line;
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
//void LCD_data()
//{
//  uint8* string = "Kp :";
//  LCD_ShowString(0,0,string);
//  LCD_ShowNum(30,0,(int32)(servos.direction_p*100),5);
//
//  string = "err :";
//  LCD_ShowString(0,16,string);
//  LCD_ShowNum(36,16,(int32)(ABS(camer.error)),5);
//  
//  string = "angle :";
//  LCD_ShowString(0,16,string);
//  LCD_ShowNum(36,16,(int32)(ABS(camer.error)),5);
//  string = "Right:";
//  LCD_ShowString(0,16,string);
//  LCD_ShowNum(45,16,right_quanshu,5);
//  int16 duty_error = servos.direction_duty_output-Servo_mid;
//  
//  uint8* string = "L_s:";
//  LCD_ShowString(0,0,string);
//  LCD_Show2Num(36,0,motor.lspeed_set,4);
//  
//  string = "R_s:";
//  LCD_ShowString(80,0,string);
//  LCD_Show2Num(116,0,motor.rspeed_set,4);
//  
//  string = "Speed:";
//  LCD_ShowString(0,16,string);
//  LCD_Show2Num(54,16,motor.speed_set,3);
//  
//  if(camera.error[0] >= 0)
//  {
//    string = "err: ";
//    LCD_ShowString(0,32,string);
//    LCD_Show2Num(45,32,(int16)camera.error[0],3);
//  }
//  else
//  {
//    string = "err:-";
//    LCD_ShowString(0,32,string);
//    LCD_Show2Num(45,32,(int16)(-1*camera.error[0]),3);
//  }
//  
//  if(duty_error >= 0)
//  {
//    string = "duty_err: ";
//    LCD_ShowString(0,48,string);
//    LCD_Show2Num(90,48,duty_error,3);
//  }
//  else
//  {
//    string = "duty_err:-";
//    LCD_ShowString(0,48,string);
//    LCD_Show2Num(90,48,-1*duty_error,3);
//  }
//  
//  string = "Vd_Ra:";
//  LCD_ShowString(0,64,string);
//  LCD_Show2Num(54,64,(int16)Vdiff_Ratio,3);
//  
//  string = "Vdiffer:";
//  LCD_ShowString(0,80,string);
//  LCD_Show2Num(72,80,Vdiffer,3);
//  if(speed_error < 0)
//  {
//    speed_error = -1*speed_error;
//    string = "s_error:-";
//    LCD_ShowString(0,32,string);
//    LCD_Show2Num(81,32,speed_error,4);
//    LCD_ShowString(120,32,"L<R");
//  }
//  else
//  {
//    string = "s_error:";
//    LCD_ShowString(0,32,string);
//    LCD_Show2Num(81,32,speed_error,4); 
//    LCD_ShowString(120,32,"L>=R");
//  }
  
//}
