#include "FuzzyGiv_DMAX.h"
#include "include.h"
#include "math.h"
extern int8 Sig_Fuzzy_row;
const int16 PMAX_I  =  75 ;       //大于440的值将被当成 440
const int16 PMIN_I  =  30 ;       //小于PMIN的值将被当成      赛道越简单，速度越快，否则越是复杂就越慢
const int16 DMAX_I  =  37 ;       //这个值表示图像后DMAX行空的多少，空的越多，速度越慢
const int16 DMIN_I  =  18 ;
const int16 SMAX_I  = 100 ;      //两个参数都统一到0~100的值（归一化）
const int16 SMIN_I  =   0 ;
const int16 FMAX_I  = 100 ;      //语言值的满幅值
              // 0  1   2   3   4   5   6
int16 PFF_I[7] = { 0, 16, 32, 48, 64, 80, 96 };     //统一到最大值； 最小值；
int16 DFF_I[7] = { 0, 40, 50, 60, 70, 80, 90 };
/*输出量U语言值特征点    0    1    2    3    4    5    6 */

int16 UFF1_I[7] =     {   25, 23, 21, 17, 14, 12, 10};  //稳定
int16 UFF2_I[7] =     {   28, 26, 24, 21, 16, 13, 11}; 
//int16 UFF1[7] =     {   150, 165, 190, 235, 265, 285, 345};   
//int16 UFF1[7] =     {   165, 185, 230, 275, 305, 340, 380};//稳定校赛
//int16 UFF1[7] =     {   170, 185, 225, 280, 345, 370, 400};//疯狗
//int16 UFF2[7] =     {   280, 295, 310, 330, 360, 400, 460};
//int16 UFF3[7] =     {   95, 105, 210, 380, 440, 560, 700} ;
//int16 UFF3[7] =     {   110, 125, 135, 155, 250, 345, 360};//良好赛道可以使用
//int16 UFF3[7] =     {   180, 250, 300, 345, 390, 480 ,560};

uint16 rule_I[7][7] =
{   /*Track_complexity */  //  0,  1,  2,  3,  4,  5,  6    Prospect_See
  /* 0 */                   {  6,  5,  4,  3,  2,  1,  0,} , //U语言数组里面的下标
  /* 1 */                   {  5,  5,  4,  3,  2,  1,  0,} ,      
  /* 2 */                   {  4,  4,  3,  2,  1,  1,  0,} ,
  /* 3 */                   {  3,  3,  3,  2,  1,  1,  0,} ,
  /* 4 */                   {  2,  2,  2,  1,  1,  0,  0,} ,
  /* 5 */                   {  2,  1,  1,  0,  0,  0,  0,} , 
  /* 6 */                   {  1,  1,  0,  0,  0,  0,  0,}
};  //横D竖P
//if(back_turn_buff[back_count]==1)
int16 *UFF_I= UFF1_I;

//else
//  int16 *UFF=UFF2;
/* P 代表赛道复杂程度
D 表示前瞻
模糊控制算法通过这两个跟定量以及规则表给出当前应该输出的速度
*/
int16 FuzzySet_DMIN(int16 P, int16 D)          //模糊运算引擎，返回速度值 
{
   int16 U;       /*偏差，以及输出值的精确量 */
   uint16 PF[2];
   uint16 DF[2]; 
   uint16 UF[4];  /*偏差，偏差微分以及输出值的隶属度PF[1]是P的隶属度，PF[0]是隶属度的补集 */
   int16 Pn = 0, Dn = 0;
   int16 Un[4];
   int32 temp1,temp2;
   
   if(P < PMIN_I)
     P = PMIN_I;
   else
     if(P > PMAX_I)
       P = PMAX_I;
   
   P = (int16)((double)(P - PMIN_I) / (PMAX_I - PMIN_I) * (SMAX_I - SMIN_I) + SMIN_I); //归一化到SMIN ~ SMAX
   
   if(D < DMIN_I)
     D = DMIN_I;
   else 
     if( D > DMAX_I)
       D = DMAX_I;
    
   D = (int16)(((double)(D - DMIN_I) )/ (DMAX_I - DMIN_I) * (SMAX_I - SMIN_I) + SMIN_I) ;    //归一化到SMIN ~ SMAX

   /*隶属度的确定*/
   /*根据PD的指定语言获得有效的隶属度*/
   
   if(P > PFF_I[0] && P < PFF_I[6])
   {
        if (P <= PFF_I[1])
        {
          Pn = 1;
          PF[0] = (uint16)(FMAX_I * ((float)(PFF_I[1] - P) / (PFF_I[1] - PFF_I[0])));
        }
        else if (P <= PFF_I[2])
        {
          Pn = 2;
          PF[0] = (uint16)(FMAX_I * ((float)(PFF_I[2] - P) / (PFF_I[2] - PFF_I[1])));
        }
        else if (P <= PFF_I[3])
        {
          Pn = 3;
          PF[0] = (uint16)(FMAX_I * ((float)(PFF_I[3] - P) / (PFF_I[3] - PFF_I[2])));
        }
        else if (P <= PFF_I[4])
        {
          Pn = 4;
          PF[0] = (uint16)(FMAX_I * ((float)(PFF_I[4] - P) / (PFF_I[4] - PFF_I[3])));
        }
        else if (P <= PFF_I[5])
        {
          Pn = 5;
          PF[0] = (uint16)(FMAX_I * ((float)(PFF_I[5] - P) / (PFF_I[5] - PFF_I[4])));
        }
        else if (P <= PFF_I[6])
        {
          Pn = 6;
          PF[0] = (uint16)(FMAX_I * ((float)(PFF_I[6] - P) / (PFF_I[6] - PFF_I[5])));
        }
   }
   else if (P <= PFF_I[0])
   {
        Pn = 1;
        PF[0] = (uint16)(FMAX_I);
    }
   else if (P <= PFF_I[3])
   {
        Pn = 6; 
        PF[0] = 0; 
    }
   PF[1] = (uint16)(FMAX_I - PF[0]);
     
     
     if (D > DFF_I[0] && D < DFF_I[6])
      {
        if (D <= DFF_I[1])
        {
          Dn = 1; DF[0] = (uint16)(FMAX_I * ((float)(DFF_I[1] - D) / (DFF_I[1] - DFF_I[0])));
        }
        else if (D <= DFF_I[2])
        {
          Dn = 2;
          DF[0] = (uint16)(FMAX_I * ((float)(DFF_I[2] - D) / (DFF_I[2] - DFF_I[1])));
        }
        else if (D <= DFF_I[3])
        {
          Dn = 3;
          DF[0] = (uint16)(FMAX_I * ((float)(DFF_I[3] - D) / (DFF_I[3] - DFF_I[2])));
        }
        else if (D <= DFF_I[4])
        {
          Dn = 4;
          DF[0] = (uint16)(FMAX_I * ((float)(DFF_I[4] - D) / (DFF_I[4] - DFF_I[3])));
        }
        else if (D <= DFF_I[5])
        {
          Dn = 5;
          DF[0] = (uint16)(FMAX_I * ((float)(DFF_I[5] - D) / (DFF_I[5] - DFF_I[4])));
        }
        else if (D <= DFF_I[6])
        {
          Dn = 6;
          DF[0] = (uint16)(FMAX_I * ((float)(DFF_I[6] - D) / (DFF_I[6] - DFF_I[5])));
        }
      }
      else if (D <= DFF_I[0])
      {
        Dn = 1;
        DF[0] = (uint16)(FMAX_I);
      }
      else if (D >= DFF_I[6])
      {
        Dn = 6;
        DF[0] = 0;
      }
      DF[1] = (uint16)(FMAX_I - DF[0]);
    
   
       /*使用误差范围优化后的规则表rule[7][7]*/
      /*输出值使用13个隶属函数,中心值由UFF[7]指定*/
      /*一般都是四个规则有效*/
      Un[0] = rule_I[Pn - 1][Dn - 1];
      Un[1] = rule_I[Pn][ Dn - 1];
      Un[2] = rule_I[Pn - 1][ Dn];
      Un[3] = rule_I[Pn][ Dn];
      if (PF[0] <= DF[0])//计算R表，隶属函数求交集
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
      /*同隶属函数输出语言值求大*/
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
      /*重心法(按隶属度加权平均)反模糊*/
      /*Un[]原值为输出隶属函数标号，转换为隶属函数值*/
      // if (Un[0] >= 0)
      Un[0] = UFF_I[Un[0]];
      // else
      //     Un[0] = (int16)(-UFF[-Un[0]]);
      // if (Un[1] >= 0)
      Un[1] = UFF_I[Un[1]];
      //  else
      //    Un[1] = (int16)(-UFF[-Un[1]]);
      // if (Un[2] >= 0)
      Un[2] = UFF_I[Un[2]];
      //  else
      //     Un[2] = (int16)(-UFF[-Un[2]]);
      // if (Un[3] >= 0)
      Un[3] = UFF_I[Un[3]];
      // else
      //     Un[3] = (int16)(-UFF[-Un[3]]);
      temp1 = UF[0] * Un[0] + UF[1] * Un[1] + UF[2] * Un[2] + UF[3] * Un[3];
      temp2 = UF[0] + UF[1] + UF[2] + UF[3];
      U = (int16)(temp1 / temp2);
      return U;
}
