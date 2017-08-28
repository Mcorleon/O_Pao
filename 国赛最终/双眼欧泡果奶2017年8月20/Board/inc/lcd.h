#ifndef __LCD_H
#define __LCD_H

////������ɫ
//#define WHITE         	 0xFFFF
//#define BLACK         	 0x0000	  
//#define BLUE         	 0x001F  
//#define BRED             0XF81F
//#define GRED 		 0XFFE0
//#define GBLUE		 0X07FF
//#define RED           	 0xF800
//#define MAGENTA       	 0xF81F
//#define GREEN         	 0x07E0
//#define CYAN          	 0x7FFF
//#define YELLOW        	 0xFFE0
//#define BROWN 			 0XBC40 //��ɫ
//#define BRRED 			 0XFC07 //�غ�ɫ
//#define GRAY  			 0X8430 //��ɫ
////GUI��ɫ
//
//#define DARKBLUE      	 0X01CF	//����ɫ
//#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
//#define GRAYBLUE       	 0X5458 //����ɫ
////������ɫΪPANEL����ɫ 
//
//#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LGRAY 		 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
//
//#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
//#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

#define WHITE		0xFFFF
#define BLACK		0x0000
#define RED		0x001F
#define BLUE2		0x051F
#define BLUE		0xF800
#define Magenta		0xF81F
#define GREEN		0x07E0
#define YELLOW		0x7FFF
#define CYAN		0xFFE0

#define CS       PTE5_OUT     //Ƭѡ	**
#define LCD_DC   PTE3_OUT	  //����/�����л�**
#define SDA      PTE2_OUT	  //����  **
#define SCL      PTE1_OUT	  //ʱ��**
#define RES      PTE4_OUT	  //��λ  **

#define LCD_W  160
#define LCD_H  128

extern  uint16 BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ

void LCD_Write_Data(uint8 dat);
void LCD_Write_Data2(uint16 dat16);
void LCD_WriteCommand(uint8 c);
void Tft_init();
void TFT_Reset(void);
void LCD_Clear(uint16 Color);
void Address_set(uint16 x1,uint16 y1,uint16 x2,uint16 y2);
void LCD_DrawPoint(uint16 x,uint16 y);//����
void LCD_Fill(uint16 xsta,uint16 ysta,uint16 xend,uint16 yend,uint16 color);//��ָ�����������ָ����ɫ
void LCD_DrawPoint_big(uint16 x,uint16 y,uint16 color);//��һ�����
void LCD_DrawLine(uint16 x1, uint16 y1, uint16 x2, uint16 y2);//����//x1,y1:�������//x2,y2:�յ����� 
void LCD_DrawRectangle(uint16 x1, uint16 y1, uint16 x2, uint16 y2);//������
void Draw_Circle(uint16 x0,uint16 y0,uint8 r);//��ָ��λ�û�һ��ָ����С��Բ//(x,y):���ĵ�//r    :�뾶
void LCD_ShowChar(uint16 x,uint16 y,uint8 num,uint8 mode);//��ָ��λ����ʾһ���ַ�
uint32 mypow(uint8 m,uint8 n);//m^n����
void LCD_ShowNum(uint16 x,uint16 y,int32 num,uint8 len);//��ʾ2������
void LCD_Show2Num(uint16 x,uint16 y,uint16 num,uint8 len);//��ʾ2������
void LCD_ShowString(uint16 x,uint16 y,uint8 *p);//��ʾ�ַ���
void LCD_img(void);
void LCD_img_1(void);
void All_LCD_img(void);
#endif
