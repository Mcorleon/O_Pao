#include "include.h"
#include "ziku.h"
#include "lcd.h"

uint16 BACK_COLOR=WHITE, POINT_COLOR=BLACK ;   //����ɫ������ɫ

void  LCD_WriteCommand(uint8 c)
{
  int i;
  CS=0;
  LCD_DC=0;
  for(i=0;i<8;i++)
  {
    if(c&0x80)
    {
      SDA=1;
    }
    else SDA=0;
    SCL=0;
    SCL=1;
    c <<=1;
  }
  CS=1;	
}

void LCD_Write_Data(uint8 dat)//д8λ����
{
  int i;
  CS=0;
  LCD_DC=1;
  for(i=0;i<8;i++)
  {
    if(dat&0x80)
    {
      SDA=1;
    }
    else SDA=0;
    SCL=0;
    SCL=1;
    dat<<=1;
  }
  CS=1;
}

void LCD_Write_Data2(uint16 dat16)//д16λ����
{
  LCD_Write_Data(dat16>>8);
  LCD_Write_Data(dat16);
}


void TFT_Reset(void)//��λ
{  
  RES = 0;
  DELAY_MS(150);
  
  RES = 1;
  DELAY_MS(150);
  //  RES=0;
}

void Tft_init()
{
  gpio_init(PTC9,GPO,0);
  gpio_init(PTC8,GPO,0);
  gpio_init(PTC7,GPO,0);
  gpio_init(PTC6,GPO,0);
  gpio_init(PTC5,GPO,0); 
  gpio_init(PTE6,GPO,0);//LED
  //gpio_init(PTD5,GPO,1);
  TFT_Reset();
  
  
  LCD_WriteCommand(0xCB);  
  LCD_Write_Data(0x39); 
  LCD_Write_Data(0x2C); 
  LCD_Write_Data(0x00); 
  LCD_Write_Data(0x34); 
  LCD_Write_Data(0x02); 
  
  LCD_WriteCommand(0xCF);  
  LCD_Write_Data(0x00); 
  LCD_Write_Data(0XC1); 
  LCD_Write_Data(0X30); 
  
  LCD_WriteCommand(0xE8);  
  LCD_Write_Data(0x85); 
  LCD_Write_Data(0x00); 
  LCD_Write_Data(0x78); 
  
  LCD_WriteCommand(0xEA);  
  LCD_Write_Data(0x00); 
  LCD_Write_Data(0x00); 
  
  LCD_WriteCommand(0xED);  
  LCD_Write_Data(0x64); 
  LCD_Write_Data(0x03); 
  LCD_Write_Data(0X12); 
  LCD_Write_Data(0X81); 
  
  LCD_WriteCommand(0xF7);  
  LCD_Write_Data(0x20); 
  
  LCD_WriteCommand(0xC0);    //Power control 
  LCD_Write_Data(0x23);   //VRH[5:0] 
  
  LCD_WriteCommand(0xC1);    //Power control 
  LCD_Write_Data(0x10);   //SAP[2:0];BT[3:0] 
  
  LCD_WriteCommand(0xC5);    //VCM control 
  LCD_Write_Data(0x3e); //�Աȶȵ���
  LCD_Write_Data(0x28); 
  
  LCD_WriteCommand(0xC7);    //VCM control2 
  LCD_Write_Data(0x86);  //--
  
  LCD_WriteCommand(0x36);    // Memory Access Control 
  LCD_Write_Data(0x68); //C8	   //48 68����//28 E8 ����
  
  LCD_WriteCommand(0x3A);    
  LCD_Write_Data(0x55); 
  
  LCD_WriteCommand(0xB1);    
  LCD_Write_Data(0x00);  
  LCD_Write_Data(0x18); 
  
  LCD_WriteCommand(0xB6);    // Display Function Control 
  LCD_Write_Data(0x08); 
  LCD_Write_Data(0x82);
  LCD_Write_Data(0x27);  
  
  LCD_WriteCommand(0xF2);    // 3Gamma Function Disable 
  LCD_Write_Data(0x00); 
  
  LCD_WriteCommand(0x26);    //Gamma curve selected 
  LCD_Write_Data(0x01); 
  
  LCD_WriteCommand(0xE0);    //Set Gamma 
  LCD_Write_Data(0x0F); 
  LCD_Write_Data(0x31); 
  LCD_Write_Data(0x2B); 
  LCD_Write_Data(0x0C); 
  LCD_Write_Data(0x0E); 
  LCD_Write_Data(0x08); 
  LCD_Write_Data(0x4E); 
  LCD_Write_Data(0xF1); 
  LCD_Write_Data(0x37); 
  LCD_Write_Data(0x07); 
  LCD_Write_Data(0x10); 
  LCD_Write_Data(0x03); 
  LCD_Write_Data(0x0E); 
  LCD_Write_Data(0x09); 
  LCD_Write_Data(0x00); 
  
  LCD_WriteCommand(0XE1);    //Set Gamma 
  LCD_Write_Data(0x00); 
  LCD_Write_Data(0x0E); 
  LCD_Write_Data(0x14); 
  LCD_Write_Data(0x03); 
  LCD_Write_Data(0x11); 
  LCD_Write_Data(0x07); 
  LCD_Write_Data(0x31); 
  LCD_Write_Data(0xC1); 
  LCD_Write_Data(0x48); 
  LCD_Write_Data(0x08); 
  LCD_Write_Data(0x0F); 
  LCD_Write_Data(0x0C); 
  LCD_Write_Data(0x31); 
  LCD_Write_Data(0x36); 
  LCD_Write_Data(0x0F); 
  
  LCD_WriteCommand(0x11);    //Exit Sleep 
  DELAY_MS(120); 
  
  LCD_WriteCommand(0x29);    //Display on 
  LCD_WriteCommand(0x2c); 
  
}


void Address_set(uint16 x1,uint16 y1,uint16 x2,uint16 y2)
{  
  LCD_WriteCommand(0x2a);//0x2a
  LCD_Write_Data(x1>>8);
  LCD_Write_Data(x1);
  LCD_Write_Data(x2>>8);
  LCD_Write_Data(x2);
  
  LCD_WriteCommand(0x2b);//0x2b
  LCD_Write_Data(y1>>8);
  LCD_Write_Data(y1);
  LCD_Write_Data(y2>>8);
  LCD_Write_Data(y2);
  
  LCD_WriteCommand(0x2C);
}

void LCD_Clear(uint16 Color)
{
  uint16 i,j;	
  Address_set(0,0,LCD_W-1,LCD_H-1);
  for(i=0;i<LCD_W;i++)
  {
    for (j=0;j<LCD_H;j++)
    {
      LCD_Write_Data2(Color);
    }
  }
}

//����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(uint16 x,uint16 y)
{
  Address_set(x,y,x,y);//���ù��λ�� 
  LCD_Write_Data2(POINT_COLOR); 	    
} 	 

//��ָ�����������ָ����ɫ
//�����С:
//  (xend-xsta)*(yend-ysta)
void LCD_Fill(uint16 xsta,uint16 ysta,uint16 xend,uint16 yend,uint16 color)
{          
  uint16 i,j; 
  Address_set(xsta,ysta,xend,yend);      //���ù��λ�� 
  for(i=ysta;i<=yend;i++)
  {													   	 	
    for(j=xsta;j<=xend;j++)
    LCD_Write_Data2(color);//���ù��λ�� 	    
  } 					  	    
}  

//��һ�����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint_big(uint16 x,uint16 y,uint16 color)
{
  LCD_Fill(x-1,y-1,x+1,y+1,color);
}
//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(uint16 x1, uint16 x2 , uint16 y1 , uint16 y2)
{
  uint16 t; 
  int xerr=0,yerr=0,delta_x,delta_y,distance; 
  int incx,incy,uRow,uCol; 
  
  delta_x=x2-x1; //������������ 
  delta_y=y2-y1; 
  uRow=x1; 
  uCol=y1; 
  if(delta_x>0)incx=1; //���õ������� 
  else if(delta_x==0)incx=0;//��ֱ�� 
  else {incx=-1;delta_x=-delta_x;} 
  if(delta_y>0)incy=1; 
  else if(delta_y==0)incy=0;//ˮƽ�� 
  else{incy=-1;delta_y=-delta_y;} 
  if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
  else distance=delta_y; 
  for(t=0;t<=distance+1;t++ )//������� 
  {  
    LCD_DrawPoint(uRow,uCol);//���� 
    xerr+=delta_x ; 
    yerr+=delta_y ; 
    if(xerr>distance) 
    { 
      xerr-=distance; 
      uRow+=incx; 
    } 
    if(yerr>distance) 
    { 
      yerr-=distance; 
      uCol+=incy; 
    } 
  }  
}    
//������
void LCD_DrawRectangle(uint16 x1, uint16 y1, uint16 x2, uint16 y2)
{
  LCD_DrawLine(x1,y1,x2,y1);
  LCD_DrawLine(x1,y1,x1,y2);
  LCD_DrawLine(x1,y2,x2,y2);
  LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(uint16 x0,uint16 y0,uint8 r)
{
  int a,b;
  int di;
  a=0;b=r;	  
  di=3-(r<<1);             //�ж��¸���λ�õı�־
  while(a<=b)
  {
    LCD_DrawPoint(x0-b,y0-a);             //3           
    LCD_DrawPoint(x0+b,y0-a);             //0           
    LCD_DrawPoint(x0-a,y0+b);             //1       
    LCD_DrawPoint(x0-b,y0-a);             //7           
    LCD_DrawPoint(x0-a,y0-b);             //2             
    LCD_DrawPoint(x0+b,y0+a);             //4               
    LCD_DrawPoint(x0+a,y0-b);             //5
    LCD_DrawPoint(x0+a,y0+b);             //6 
    LCD_DrawPoint(x0-b,y0+a);             
    a++;
    //ʹ��Bresenham�㷨��Բ     
    if(di<0)di +=4*a+6;	  
    else
    {
      di+=10+4*(a-b);   
      b--;
    } 
    LCD_DrawPoint(x0+a,y0+b);
  }
} 
//��ָ��λ����ʾһ���ַ�

//num:Ҫ��ʾ���ַ�:" "--->"~"
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
//��ָ��λ����ʾһ���ַ�

//num:Ҫ��ʾ���ַ�:" "--->"~"

//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(uint16 x,uint16 y,uint8 num,uint8 mode)
{
  uint8 temp;
  uint8 pos,t;
  uint16 x0=x;
  uint16 colortemp=POINT_COLOR;      
  if(x>LCD_W-16||y>LCD_H-16)return;	    
  //���ô���		   
  num=num-' ';//�õ�ƫ�ƺ��ֵ
  Address_set(x,y,x+8-1,y+16-1);      //���ù��λ�� 
  if(!mode) //�ǵ��ӷ�ʽ
  {
    for(pos=0;pos<16;pos++)
    { 
      temp=asc2_1608[(uint16)num*16+pos];		 //����1608����
      for(t=0;t<8;t++)
      {                 
        if(temp&0x01)POINT_COLOR=colortemp;
        else POINT_COLOR=BACK_COLOR;
        LCD_Write_Data2(POINT_COLOR);	
        temp>>=1; 
        x++;
      }
      x=x0;
      y++;
    }	
  }else//���ӷ�ʽ
  {
    for(pos=0;pos<16;pos++)
    {
      temp=asc2_1608[(uint16)num*16+pos];		 //����1608����
      for(t=0;t<8;t++)
      {                 
        if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//��һ����     
        temp>>=1; 
      }
    }
  }
  POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n����
uint32 mypow(uint8 m,uint8 n)
{
  uint32 result=1;	 
  while(n--)result*=m;    
  return result;
}			 
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//color:��ɫ
//num:��ֵ(0~4294967295);	
void LCD_ShowNum(uint16 x,uint16 y,int32 num,uint8 len)
{         	
  uint8 t,temp;
  uint8 enshow=0;
  num=(uint16)num;
  for(t=0;t<len;t++)
  {
    temp=(num/mypow(10,len-t-1))%10;
    if(enshow==0&&t<(len-1))
    {
      if(temp==0)
      {
        LCD_ShowChar(x+8*t,y,' ',0);
        continue;
      }else enshow=1; 
      
    }
    LCD_ShowChar(x+8*t,y,temp+48,0); 
  }
} 
//��ʾ2������
//x,y:�������
//num:��ֵ(0~99);	 
void LCD_Show2Num(uint16 x,uint16 y,uint16 num,uint8 len)
{         	
  uint8 t,temp;						   
  for(t=0;t<len;t++)
  {
    temp=(num/mypow(10,len-t-1))%10;
    LCD_ShowChar(x+8*t,y,temp+'0',0); 
  }
} 
//��ʾ�ַ���
//x,y:�������  
//*p:�ַ�����ʼ��ַ
//��16����
void LCD_ShowString(uint16 x,uint16 y,uint8 *p)
{         
  while(*p!='\0')
  {       
    if(x>LCD_W-16){x=0;y+=16;}
    if(y>LCD_H-16){y=x=0;}
    LCD_ShowChar(x,y,*p,0);
    x+=8;
    p++;
  }  
}


