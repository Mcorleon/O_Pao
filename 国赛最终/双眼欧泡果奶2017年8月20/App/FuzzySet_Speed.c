#include "FuzzySet_Speed.h"
#include "include.h"
#include "math.h"
uint8 Staup_Finish =  0  ;
int16 Turn_Speed  =           205;//ת��Ѱ�Ƶ��ٶ�  A��
extern int8 start_count ;
extern Blo_STATUS_e Blo_STATE;
extern Fuz_STATUS_e Fuz_STATE;
extern int16 Sig_FuzzyRow;
extern int8 Prospect_see;
const int16 PMAX  =  75 ;       //����440��ֵ�������� 440
const int16 PMIN  =  30 ;       //С��PMIN��ֵ��������      ����Խ�򵥣��ٶ�Խ�죬����Խ�Ǹ��Ӿ�Խ��
//const int16 DMAX=  70 ;       //���ֵ��ʾͼ���DMAX�пյĶ��٣��յ�Խ�࣬�ٶ�Խ��
extern int16 DMAX       ;
extern int16 DMIN       ;
const int16 SMAX  = 100 ;      //����������ͳһ��0~100��ֵ����һ����
const int16 SMIN  =   0 ; 
const int16 FMAX  = 100 ;     //����ֵ������ֵ
              // 0  1   2   3   4   5   6
int16 PFF[7] = { 0, 16, 32, 48, 64, 80, 96 };     //ͳһ�����ֵ�� ��Сֵ��
int16 DFF[7] = { 0, 40, 50, 60, 70, 80, 90 };
/*�����U����ֵ������    0    1    2    3    4    5    6 */
//A��������  ��A����Խ��Խ��
int16 UFF1[7] =     {   203, 218, 225, 260, 282, 330, 350}; //�������쵵 B
int16 UFF2[7] =     {   220, 230, 245, 255, 275, 315, 335}; //�������ȵ�  A
int16 UFF3[7] =     {   210, 225, 240, 253, 265, 290, 315};//�������ȵ�
int16 UFF4[7] =     {   195, 205, 220, 235, 245, 250, 265};  //��.���ٵ�λ
int16 UFF5[7] =     {   203, 215, 230, 255, 275, 330, 345};//���ε�

/*********
�������쵵B  Turn_Speed = 197 p1=+-0.00185
�������ȵ�A  Turn_Speed = 210 p1=+-0.00177
�������ȵ�   Turn_Speed = 205 p1=+-0.00177
���ε�       Turn_Speed = 205 p1=+-0.00188   UFF_A=UFF2_A  UFF_I=UFF2_I
����ٵ�     Turn_Speed = 195 p1=+-0.00168
**********/
uint16 rule[7][7] =
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

 int16 *UFF = UFF1;  //��������ѡ���õ�U��������
//else
//  int16 *UFF=UFF2;
/* P �����������ӳ̶�
D ��ʾǰհ
ģ�������㷨ͨ���������������Լ�����������ǰӦ��������ٶ�
*/
int16 FuzzySet_Speed(int16 P, int16 D)          //ģ���������棬�����ٶ�ֵ 
{
   int16 U;       /*ƫ��Լ����ֵ�ľ�ȷ�� */
   uint16 PF[2];
   uint16 DF[2]; 
   uint16 UF[4];  /*ƫ�ƫ��΢���Լ����ֵ��������PF[1]��P�������ȣ�PF[0]�������ȵĲ��� */
   int16 Pn = 0, Dn = 0;
   int16 Un[4];
   int32 temp1,temp2;
   
   if(P < PMIN)
     P = PMIN;
   else
     if(P > PMAX)
       P = PMAX;
   
   P = (int16)((double)(P - PMIN) / (PMAX - PMIN) * (SMAX - SMIN) + SMIN); //��һ����SMIN ~ SMAX
   
   if(D < DMIN)
     D = DMIN;
   else 
     if( D > DMAX)
       D = DMAX;
    
   D = (int16)(((double)(D - DMIN) )/ (DMAX - DMIN) * (SMAX - SMIN) + SMIN) ;    //��һ����SMIN ~ SMAX

   /*�����ȵ�ȷ��*/
   /*����PD��ָ�����Ի����Ч��������*/
   
   if(P > PFF[0] && P < PFF[6])
   {
        if (P <= PFF[1])
        {
          Pn = 1;
          PF[0] = (uint16)(FMAX * ((float)(PFF[1] - P) / (PFF[1] - PFF[0])));
        }
        else if (P <= PFF[2])
        {
          Pn = 2;
          PF[0] = (uint16)(FMAX * ((float)(PFF[2] - P) / (PFF[2] - PFF[1])));
        }
        else if (P <= PFF[3])
        {
          Pn = 3;
          PF[0] = (uint16)(FMAX * ((float)(PFF[3] - P) / (PFF[3] - PFF[2])));
        }
        else if (P <= PFF[4])
        {
          Pn = 4;
          PF[0] = (uint16)(FMAX * ((float)(PFF[4] - P) / (PFF[4] - PFF[3])));
        }
        else if (P <= PFF[5])
        {
          Pn = 5;
          PF[0] = (uint16)(FMAX * ((float)(PFF[5] - P) / (PFF[5] - PFF[4])));
        }
        else if (P <= PFF[6])
        {
          Pn = 6;
          PF[0] = (uint16)(FMAX * ((float)(PFF[6] - P) / (PFF[6] - PFF[5])));
        }
   }
   else if (P <= PFF[0])
   {
        Pn = 1;
        PF[0] = (uint16)(FMAX);
    }
   else if (P <= PFF[3])
   {
        Pn = 6; 
        PF[0] = 0; 
    }
   PF[1] = (uint16)(FMAX - PF[0]);
     
     
     if (D > DFF[0] && D < DFF[6])
      {
        if (D <= DFF[1])
        {
          Dn = 1; DF[0] = (uint16)(FMAX * ((float)(DFF[1] - D) / (DFF[1] - DFF[0])));
        }
        else if (D <= DFF[2])
        {
          Dn = 2;
          DF[0] = (uint16)(FMAX * ((float)(DFF[2] - D) / (DFF[2] - DFF[1])));
        }
        else if (D <= DFF[3])
        {
          Dn = 3;
          DF[0] = (uint16)(FMAX * ((float)(DFF[3] - D) / (DFF[3] - DFF[2])));
        }
        else if (D <= DFF[4])
        {
          Dn = 4;
          DF[0] = (uint16)(FMAX * ((float)(DFF[4] - D) / (DFF[4] - DFF[3])));
        }
        else if (D <= DFF[5])
        {
          Dn = 5;
          DF[0] = (uint16)(FMAX * ((float)(DFF[5] - D) / (DFF[5] - DFF[4])));
        }
        else if (D <= DFF[6])
        {
          Dn = 6;
          DF[0] = (uint16)(FMAX * ((float)(DFF[6] - D) / (DFF[6] - DFF[5])));
        }
      }
      else if (D <= DFF[0])
      {
        Dn = 1;
        DF[0] = (uint16)(FMAX);
      }
      else if (D >= DFF[6])
      {
        Dn = 6;
        DF[0] = 0;
      }
      DF[1] = (uint16)(FMAX - DF[0]);
    
   
       /*ʹ����Χ�Ż���Ĺ����rule[7][7]*/
      /*���ֵʹ��13����������,����ֵ��UFF[7]ָ��*/
      /*һ�㶼���ĸ�������Ч*/
      Un[0] = rule[Pn - 1][ Dn - 1];
      Un[1] = rule[Pn][ Dn - 1];
      Un[2] = rule[Pn - 1][ Dn];
      Un[3] = rule[Pn][ Dn];
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
      Un[0] = UFF[Un[0]];
      // else
      //     Un[0] = (int16)(-UFF[-Un[0]]);
      // if (Un[1] >= 0)
      Un[1] = UFF[Un[1]];
      //  else
      //    Un[1] = (int16)(-UFF[-Un[1]]);
      // if (Un[2] >= 0)
      Un[2] = UFF[Un[2]];
      //  else
      //     Un[2] = (int16)(-UFF[-Un[2]]);
      // if (Un[3] >= 0)
      Un[3] = UFF[Un[3]];
      // else
      //     Un[3] = (int16)(-UFF[-Un[3]]);
      temp1 = UF[0] * Un[0] + UF[1] * Un[1] + UF[2] * Un[2] + UF[3] * Un[3];
      temp2 = UF[0] + UF[1] + UF[2] + UF[3];
      U = (int16)(temp1 / temp2);
      return U;
}

void Spe_Speedset_Giv()
{
  if(!Staup_Finish){
    if(start_count<5)
      motor.speed_set=motor.speed_set/2;
    else if(start_count<10)
      motor.speed_set=motor.speed_set/(10-start_count);
    else
      Staup_Finish = 1;
  }
  if(Staup_Finish){
#if Blo_SloDown
    if(Blo_STATE==Blo_Founded)
      motor.speed_set=200;
#endif
    if(Prospect_see==120)
      motor.speed_set= Turn_Speed;
  }
  if(Fuz_STATE == Fuz_RecReady)
    motor.speed_set = Straighten_Speed;
}
void FuzzyGiv_DMAXMIN()
{
  DMIN = FuzzySet_DMIN(0, Sig_FuzzyRow);
  DMAX = FuzzySet_DMAX(0, Sig_FuzzyRow);
}