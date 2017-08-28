#include "FuzzyGiv_DMAX.h"
#include "include.h"
#include "math.h"
const int16 PMAX_A  =  75 ;       //����440��ֵ�������� 440
const int16 PMIN_A  =  30 ;       //С��PMIN��ֵ��������      ����Խ�򵥣��ٶ�Խ�죬����Խ�Ǹ��Ӿ�Խ��
const int16 DMAX_A  =  37 ;       //���ֵ��ʾͼ���DMAX�пյĶ��٣��յ�Խ�࣬�ٶ�Խ��
const int16 DMIN_A  =  18 ;
const int16 SMAX_A  = 100 ;      //����������ͳһ��0~100��ֵ����һ����
const int16 SMIN_A  =   0 ; 
const int16 FMAX_A  = 100 ;     //����ֵ������ֵ
extern int16 Sig_FuzzyRow ;
              // 0  1   2   3   4   5   6
int16 PFF_A[7] = { 0, 16, 32, 48, 64, 80, 96 }; //ͳһ�����ֵ�� ��Сֵ��
int16 DFF_A[7] = { 0, 40, 50, 60, 70, 80, 90 };
/*�����U����ֵ������    0    1    2    3    4    5    6 */

int16 UFF1_A[7] =     {   70, 66, 62, 59, 56, 53, 50};  //�ȶ�
int16 UFF2_A[7] =     {   78, 73, 69, 64, 59, 55, 50};
//int16 UFF1[7] =     {   150, 165, 190, 235, 265, 285, 345};   
//int16 UFF1[7] =     {   165, 185, 230, 275, 305, 340, 380};//�ȶ�У��
//int16 UFF1[7] =     {   170, 185, 225, 280, 345, 370, 400};//�蹷
//int16 UFF2[7] =     {   280, 295, 310, 330, 360, 400, 460};
//int16 UFF3[7] =     {   95, 105, 210, 380, 440, 560, 700} ;
//int16 UFF3[7] =     {   110, 125, 135, 155, 250, 345, 360};//������������ʹ��
//int16 UFF3[7] =     {   180, 250, 300, 345, 390, 480 ,560};

uint16 rule_A[7][7] =
{   /*Track_complexity */  //  0,  1,  2,  3,  4,  5,  6    Prospect_See
  /* 0 */                   {  6,  5,  4,  3,  2,  1,  0,} , //U��������������±�
  /* 1 */                   {  5,  5,  4,  3,  2,  1,  0,} ,      
  /* 2 */                   {  4,  4,  3,  2,  1,  1,  0,} ,
  /* 3 */                   {  3,  3,  3,  2,  1,  1,  0,} ,
  /* 4 */                   {  2,  2,  2,  1,  1,  0,  0,} ,
  /* 5 */                   {  2,  1,  1,  0,  0,  0,  0,} , 
  /* 6 */                   {  1,  1,  0,  0,  0,  0,  0,}
};  //��D��P
//if(back_turn_buff[back_count]==1)

 int16 *UFF_A=UFF1_A; //��������ѡ���õ�U��������

//else
//  int16 *UFF=UFF2;
/* P �����������ӳ̶�
D ��ʾǰհ
ģ�������㷨ͨ���������������Լ�����������ǰӦ��������ٶ�
*/
int16 FuzzySet_DMAX(int16 P, int16 D)          //ģ���������棬�����ٶ�ֵ 
{
   int16 U;       /*ƫ��Լ����ֵ�ľ�ȷ�� */
   uint16 PF[2];
   uint16 DF[2]; 
   uint16 UF[4];  /*ƫ�ƫ��΢���Լ����ֵ��������PF[1]��P�������ȣ�PF[0]�������ȵĲ��� */
   int16 Pn = 0, Dn = 0;
   int16 Un[4];
   int32 temp1,temp2;
   
   if(P < PMIN_A)
     P = PMIN_A;
   else
     if(P > PMAX_A)
       P = PMAX_A;
   
   P = (int16)((double)(P - PMIN_A) / (PMAX_A - PMIN_A) * (SMAX_A - SMIN_A) + SMIN_A); //��һ����SMIN ~ SMAX
   
   if(D < DMIN_A)
     D = DMIN_A;
   else 
     if( D > DMAX_A)
       D = DMAX_A;
    
   D = (int16)(((double)(D - DMIN_A) )/ (DMAX_A - DMIN_A) * (SMAX_A - SMIN_A) + SMIN_A) ;    //��һ����SMIN ~ SMAX

   /*�����ȵ�ȷ��*/
   /*����PD��ָ�����Ի����Ч��������*/
   
   if(P > PFF_A[0] && P < PFF_A[6])
   {
        if (P <= PFF_A[1])
        {
          Pn = 1;
          PF[0] = (uint16)(FMAX_A * ((float)(PFF_A[1] - P) / (PFF_A[1] - PFF_A[0])));
        }
        else if (P <= PFF_A[2])
        {
          Pn = 2;
          PF[0] = (uint16)(FMAX_A * ((float)(PFF_A[2] - P) / (PFF_A[2] - PFF_A[1])));
        }
        else if (P <= PFF_A[3])
        {
          Pn = 3;
          PF[0] = (uint16)(FMAX_A * ((float)(PFF_A[3] - P) / (PFF_A[3] - PFF_A[2])));
        }
        else if (P <= PFF_A[4])
        {
          Pn = 4;
          PF[0] = (uint16)(FMAX_A * ((float)(PFF_A[4] - P) / (PFF_A[4] - PFF_A[3])));
        }
        else if (P <= PFF_A[5])
        {
          Pn = 5;
          PF[0] = (uint16)(FMAX_A * ((float)(PFF_A[5] - P) / (PFF_A[5] - PFF_A[4])));
        }
        else if (P <= PFF_A[6])
        {
          Pn = 6;
          PF[0] = (uint16)(FMAX_A * ((float)(PFF_A[6] - P) / (PFF_A[6] - PFF_A[5])));
        }
   }
   else if (P <= PFF_A[0])
   {
        Pn = 1;
        PF[0] = (uint16)(FMAX_A);
    }
   else if (P <= PFF_A[3])
   {
        Pn = 6; 
        PF[0] = 0; 
    }
   PF[1] = (uint16)(FMAX_A - PF[0]);
     
     
     if (D > DFF_A[0] && D < DFF_A[6])
      {
        if (D <= DFF_A[1])
        {
          Dn = 1; DF[0] = (uint16)(FMAX_A * ((float)(DFF_A[1] - D) / (DFF_A[1] - DFF_A[0])));
        }
        else if (D <= DFF_A[2])
        {
          Dn = 2;
          DF[0] = (uint16)(FMAX_A * ((float)(DFF_A[2] - D) / (DFF_A[2] - DFF_A[1])));
        }
        else if (D <= DFF_A[3])
        {
          Dn = 3;
          DF[0] = (uint16)(FMAX_A * ((float)(DFF_A[3] - D) / (DFF_A[3] - DFF_A[2])));
        }
        else if (D <= DFF_A[4])
        {
          Dn = 4;
          DF[0] = (uint16)(FMAX_A * ((float)(DFF_A[4] - D) / (DFF_A[4] - DFF_A[3])));
        }
        else if (D <= DFF_A[5])
        {
          Dn = 5;
          DF[0] = (uint16)(FMAX_A * ((float)(DFF_A[5] - D) / (DFF_A[5] - DFF_A[4])));
        }
        else if (D <= DFF_A[6])
        {
          Dn = 6;
          DF[0] = (uint16)(FMAX_A * ((float)(DFF_A[6] - D) / (DFF_A[6] - DFF_A[5])));
        }
      }
      else if (D <= DFF_A[0])
      {
        Dn = 1;
        DF[0] = (uint16)(FMAX_A);
      }
      else if (D >= DFF_A[6])
      {
        Dn = 6;
        DF[0] = 0;
      }
      DF[1] = (uint16)(FMAX_A - DF[0]);
    
   
       /*ʹ����Χ�Ż���Ĺ����rule[7][7]*/
      /*���ֵʹ��13����������,����ֵ��UFF[7]ָ��*/
      /*һ�㶼���ĸ�������Ч*/
      Un[0] = rule_A[Pn - 1][ Dn - 1];
      Un[1] = rule_A[Pn][ Dn - 1];
      Un[2] = rule_A[Pn - 1][ Dn];
      Un[3] = rule_A[Pn][ Dn];
      if (PF[0] <= DF[0])//����R�����������󽻼�
        UF[0] = PF[0];
      else
        UF[0] = DF[0];
      if (PF[1] <= DF[0])
        UF[1] = PF[1];
      else
        UF[1] = DF[0];
      if (PF[0] <= DF[1])
        UF[2] = PF[0];
      else
        UF[2] = DF[1];
      if (PF[1] <= DF[1])
        UF[3] = PF[1];
      else
        UF[3] = DF[1];
      /*ͬ���������������ֵ���*/
      if (Un[0] == Un[1])
      {
        if (UF[0] > UF[1])
          UF[1] = 0;
        else
          UF[0] = 0;
      }
      if (Un[0] == Un[2])
      {
        if (UF[0] > UF[2])
          UF[2] = 0;
        else
          UF[0] = 0;
      }
      if (Un[0] == Un[3])
      {
        if (UF[0] > UF[3])
          UF[3] = 0;
        else
          UF[0] = 0;
      }
      if (Un[1] == Un[2])
      {
        if (UF[1] > UF[2])
          UF[2] = 0;
        else
          UF[1] = 0;
      }
      if (Un[1] == Un[3])
      {
        if (UF[1] > UF[3])
          UF[3] = 0;
        else
          UF[1] = 0;
      }
      if (Un[2] == Un[3])
      {
        if (UF[2] > UF[3])
          UF[3] = 0;
        else
          UF[2] = 0;
      }
      /*���ķ�(�������ȼ�Ȩƽ��)��ģ��*/
      /*Un[]ԭֵΪ�������������ţ�ת��Ϊ��������ֵ*/
      // if (Un[0] >= 0)
      Un[0] = UFF_A[Un[0]];
      // else
      //     Un[0] = (int16)(-UFF[-Un[0]]);
      // if (Un[1] >= 0)
      Un[1] = UFF_A[Un[1]];
      //  else
      //    Un[1] = (int16)(-UFF[-Un[1]]);
      // if (Un[2] >= 0)
      Un[2] = UFF_A[Un[2]];
      //  else
      //     Un[2] = (int16)(-UFF[-Un[2]]);
      // if (Un[3] >= 0)
      Un[3] = UFF_A[Un[3]];
      // else
      //     Un[3] = (int16)(-UFF[-Un[3]]);
      temp1 = UF[0] * Un[0] + UF[1] * Un[1] + UF[2] * Un[2] + UF[3] * Un[3];
      temp2 = UF[0] + UF[1] + UF[2] + UF[3];
      U = (int16)(temp1 / temp2);
      return U;
}
