#include "common.h"
#include "VCAN_camera.h"
#include "Servo_Motor.h"
int16 Blo_MidLine         = 0;  //障碍的中线
uint8 Block_ComLeft       = 0; //障碍在左边
uint8 Block_ComRight      = 0;  //障碍在右边
int16 Sig_chosse          = 0;  //这个是怎么说我也不好说先不管
int32 CloSigal_Count      = 0;  //这个是你接近信标灯几个周期的计数  当接近信标灯三个周期就认为是接近信标灯了
 int8 Last_sigal_row      = 0; //上一场信标灯的行数
 int8 Forced_TurRow       = 0;
 int8 Blo_row             = 0; //障碍灯的行数
 int8 Sig_row             = 0;  //信标灯的行数
uint8 Sig_permit          = 0; //是否发现信标灯
uint8 Las_Sigpermit       = 0; //上一场是否发现信标灯
int32 Lost_flag           = 0; //丢失信标灯计数
int16 Sig_MidLine         = 0; //信标灯的中线
int16 Last_middle_line    = 0;  //上一场信标灯的中线
uint8 Blo_Delay_Left      = 0; //先不管
uint8 Blo_Delay_Right     = 0; //先不管
uint8 Sig_MissPeriod_flag = 0; //先不管
int16 Blo_chosse          = 0;
int8 Losing_Row             =  0;
int16 Left_line[CAMERA_H]       ;
int16 Right_line[CAMERA_H]      ;
int16 Block_left_line[CAMERA_H] ;
int16 Block_right_line[CAMERA_H];
int16 Middle_line[CAMERA_H]     ;
int16 Avoid_BloOffset     = 0   ;
int16 Blo_Delay_Count     = 0   ; 
Dis_STATUS_e Dis_STATE = Dis_Clo;
uint8 Las_Dis_STATE = 0         ;
uint8 Missing_Flag  = 1         ;
int16 Blo_LTemoporary = 0       ;
int16 Blo_RTemoporary = 0       ;
int16 Rev_Vision_Row  = 0       ;
int16 Uper_Limit      = 0       ;
int16 Lower_Limit     = 0       ;
int16 Blo_Row_Limit   = 0       ;
extern uint8 Forced_Turdirection;
extern int16 Spec_BloDev       ;
extern int16 Blo_Delay_Count   ; 
extern int8  Mov_dev           ;
extern int8  Movblo_dev        ;  
extern uint8 NorDirection      ;
extern uint8 TurDirection      ;
extern uint8 img_1[OV7725_EAGLE_H_1][OV7725_EAGLE_W_1];
extern uint8 img[OV7725_EAGLE_H][OV7725_EAGLE_W]      ;
extern uint8 Staup_Begin       ;
extern uint8 Start_flag        ;
extern int8  Block_Judmid      ;
extern Blo_STATUS_e Blo_STATE  ;
extern int16 sigal_Lline_normal[120];
extern int16 sigal_Rline_normal[120];
extern int16 Rev_Vision_Line[160]   ;
extern int16 block_Lline[120]       ;
extern int16 block_Rline[120]       ;
extern int16 FuzForced_TurDirection[120];
extern uint8 Blo_AgreeDelay         ;
extern int16 Blo_AgrDelay_Count     ;
extern int16 Las_Blo_Dev            ;
extern int16 Sig_FuzzyRow           ;
extern int16 Block_DelDev           ;
extern uint8 Tur_AvoidBlo_flag      ;
extern int16 Time                   ;
extern int16 LOST_LIMIT             ;
void LED_PrintValueI(uint8 x, uint8 y, int data)       ;
void LED_PrintsignValueF4(uint8 x, uint8 y, float data);
#define Sigal_size_initialization    0
#define Right_line_initialization  159
#define Left_line_initialization     0
#define Middle_line_initialization  80
#define B_W0 Black_to_White[0]
#define B_W1 Black_to_White[1]
#define W_B0 White_to_Black[0]
#define W_B1 White_to_Black[1]
#define B_W2 Black_to_White[2]
#define W_B2 White_to_Black[2]
#define LEFT_LINE_FOUND img_1[row][i]<img_1[row][i+1]&&img_1[row][i-1]<img_1[row][i+2]&&Left_line[row]==0
#define RIGHT_LINE_FOUND img_1[row][i-1]>img_1[row][i]&&img_1[row][i-2]>img_1[row][i+1]&&((img_1[row][i+5]==0&&i<=154)||i>154)&&Right_line[row]==159
#define LEFT_BLOCK_FOUND img[row][i]<img[row][i+1]&&img[row][i-1]<img[row][i+2]&&Block_left_line[row]==0
#define RIGHT_BLOCK_FOUND img[row][i-1]>img[row][i]&&img[row][i-2]>img[row][i+1]&&((i<154&&img[row][i+5]==0)||i>=154)&&(Block_right_line[row]==159)

int16 Left_line[CAMERA_H]   = {0};                //信标左右线          
int16 Right_line[CAMERA_H]  = {0};               //信标左右线
int16 Middle_line[CAMERA_H] = {0};
//////////////////////////////////////////////////////////////////////////////
void img_extract(void *dst, void *src, uint32_t srclen)
{
    uint8_t colour[2] = {255, 0}; //0 和 1 分别对应的颜色
    uint8_t * mdst = dst;
    uint8_t * msrc = src;
    //注：山外的摄像头 0 表示 白色，1表示 黑色
    uint8_t tmpsrc;
    while(srclen --)
    {
        tmpsrc = *msrc++;
        *mdst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
    }
}
/*********************************************************** 
* @author：欧泡果奶
* @fuction description：提取信标圆排除干扰
***********************************************************/
void sigal_finding(void)   //封装完毕
{
  uint8 sigal_permit      =   0;
  int8 row                =   0;
  int8 start_finding_line =   0;
  int8 sigal_down         =   0;
  int8 b_count            =   0;
  int8 w_count            =   0;
  int16 s                 =   0;
  int8 sigal_up           =   0;
  int16 temp              =   0;
  int16 i                 =   0;
  int16 Start_line_limit  =   4;
  int16 End_line_limit    = 157;
  int16 Black_to_White[5] = {0};
  int16 White_to_Black[5] = {0};
  int16 sigal_size[120]   = {0};
  int16 Start_line        =   0;
  int8 sigal_row          =   0;
            //pit_time_start(PIT1);
    for(row = 0 ; row < 120 ; row ++)
    {
       Left_line[row] = Left_line_initialization;
       Right_line[row] = Right_line_initialization;  
    }
    for(row=116;row>0;row--) 
    {
       if(row<=20){
         End_line_limit=134;
         Start_line_limit=25;
       }
       else{
         Start_line_limit=4;
         End_line_limit=157;
       }
       if(Start_line<Start_line_limit){
         Start_line=Start_line_limit;
       }
       Start_line=Start_line_limit;     
       for(i=Start_line;i<End_line_limit;i++)
       {
          if(LEFT_LINE_FOUND){
              Left_line[row] = i;
              if(start_finding_line==0){
                start_finding_line=row+3;
              }
              if(ABS(Left_line[row]-Left_line[row+1])<10){
                Start_line = i - ABS(Left_line[row+2] - Left_line[row+1])-8 ;
              }
          }
          if(RIGHT_LINE_FOUND){
              if(start_finding_line==0){
                start_finding_line=row;
              }
              if(i>154){
                Right_line[row]=i;
                break;
              }
              else if(img_1[row][i+5]==0&&i<=154){
                Right_line[row]=i;    
                break;
              }
          }
       }
       sigal_size[row]=Right_line[row]-Left_line[row]; 
       if(sigal_size[row]>40)   {
         sigal_size[row] = 0;
       }
       if(row<117){
          if(sigal_size[row]>0&&sigal_size[row+1]>0&&sigal_size[row+2]==0&&sigal_size[row+3]==0)   {
            Black_to_White[b_count++]=row+1;
          }
       }
       if(sigal_size[row]==0&&sigal_size[row+1]==0&&sigal_size[row+2]>0&&sigal_size[row+3]>0)   {
         White_to_Black[w_count++]=row+2; 
       }
    }  
    b_count--;
    w_count--;
    if(W_B0!=0&&B_W0!=0&&B_W0>W_B0){
        if(b_count==0&&w_count==0){
          sigal_up=W_B0   ;
          sigal_down=B_W0 ;
          sigal_permit=1  ;
        }
        if(b_count==1&&w_count==1){
            if(((W_B0-B_W1<=25)&&(W_B0>70))||(W_B0-B_W1<=20)){
              sigal_down=B_W1 ;
              sigal_up=W_B1   ; 
              sigal_permit=1  ;
            }
            else{
              sigal_up=B_W0  ;
              sigal_down=B_W0;
              sigal_permit=1 ;
            }
        }
        if(b_count>=2&&w_count>=2){
          if(((W_B0-B_W1<=25)&&(W_B0>70))||(W_B1-B_W2<=20)){
            sigal_down=B_W2 ;
            sigal_up=W_B2   ; 
            sigal_permit=1  ;
          }
          else if((W_B0-B_W1<=20)&&(W_B1-B_W2>20)){
            sigal_down=B_W1;
            sigal_up=W_B1  ;
            sigal_permit=1 ;
          }
          else{
            sigal_down=B_W0;
            sigal_up=W_B0  ;
            sigal_permit=1 ;
          }
        }
    }

    if(W_B0>B_W0&&W_B0>=70){
      if(b_count==0&&w_count==0){
        sigal_down=117;   
        sigal_up=W_B0 ;  
        sigal_permit=1;
      }
      if(b_count==0&&w_count==1&&(W_B0>70)&&B_W0>0){
        sigal_down=B_W0;
        sigal_up=W_B1  ;
        sigal_permit=1 ;
      }
    }
    if(sigal_permit==1)
    Last_sigal_row=Sig_row;
    if(sigal_permit){
      for(row=sigal_down;row>=sigal_up;row--)
      {
          if(sigal_size[row]>=temp){
            sigal_row=row       ;   
            temp=sigal_size[row];
          }
      }
    }
    if(sigal_permit){
       Sig_MidLine=0;
       for(s = sigal_down;s>=sigal_up;s--)
       { 
          Sig_MidLine = (Left_line[s] + Right_line[s])/2 + Sig_MidLine;
       }
       Sig_MidLine = Sig_MidLine/(sigal_down-sigal_up+1);
    }
    if(!sigal_permit){
       sigal_row  =Last_sigal_row  ; 
       Sig_MidLine=Last_middle_line;
    }
//    if(Lost_flag>3)
//      Sig_MissPeriod_flag = 1;
//    else
//      Sig_MissPeriod_flag = 0;
    if(!sigal_permit){
      Lost_flag++;
    }
    if(sigal_permit){
      Lost_flag=0;
    }
    if(Lost_flag>2)
      sigal_row=120;
    
    
    Las_Dis_STATE=Dis_STATE ;
    Dis_STATE_Judgement()   ;   //判断此时距离状态
    Las_Sigpermit=Sig_permit;
    Sig_permit=sigal_permit ;
    /*********************
    *起跑准备标志位
    *********************/
    if(Start_flag==1&&sigal_permit==1){
      Staup_Begin=1;
      Start_flag=0 ;
    }
    
    Sig_row = sigal_row;
}
void block_finding()
{
    int8 row         =   0;
    int8 block_down  =   0;
    int8 block_up    =   0;
    int16 i          =   0;
    int16 s          =   0;
    int16 block_size[120]        ={0};
    int16 Block_start_line       =  0;
    int16 Block_end_line         =  0;
    int16 Block_start_line_limit =  0;
    uint8 block_permit           =  0;


    for(row = 0 ; row < 120 ; row ++)
    {
        Block_left_line[row]=Left_line_initialization  ;
        Block_right_line[row]=Right_line_initialization;
    }
     for(row=116;row>0;row--) 
     {
        if(!block_down){
            if(row<=20){
              Block_start_line_limit=20;
              Block_end_line=139       ;
            }
            else if(row<40){
              Block_start_line_limit=40-row;
              Block_end_line=119+row       ;
            }
            else{
              Block_start_line_limit=5;
              Block_end_line=154      ;
            }
        }
        else{
              Block_start_line_limit=5 ;
              Block_end_line=154       ;
        }

        if(Block_start_line<Block_start_line_limit){
          Block_start_line=Block_start_line_limit;
        }
        for(i=Block_start_line;i<Block_end_line;i++)
        {
            if(LEFT_BLOCK_FOUND){
              Block_left_line[row]=i;
              Block_start_line = i - ABS(Block_left_line[row+2] - Block_left_line[row+1])-8 ;
            }
            if(RIGHT_BLOCK_FOUND){
              if(i<154){
                Block_right_line[row]=i;
                break;
              }
              else if(img[row][i+5]==0&&i>=154){
                Block_right_line[row]=i;  
                break;
              }
            }
        }
        block_size[row]=Block_right_line[row]-Block_left_line[row];
        if(block_size[row]>50){
          block_size[row] = 0;
        }
        if(row<117){
            if(block_size[row]>0&&block_size[row+1]>0&&block_size[row+2]==0&&block_size[row+3]==0)   {block_down=row+1;}
        }
        if(block_size[row]==0&&block_size[row+1]==0&&block_size[row+2]>0&&block_size[row+3]>0)   {
          block_up=row+2;
          break; 
        }

         if((ABS(Block_left_line[row]-Block_left_line[row+1])>10||ABS(Block_right_line[row]-Block_right_line[row+1])>10)&&block_down>0){
           block_up=row+1;Block_left_line[row]=0;
           Block_right_line[row]=159            ;
           break                                ;
         }
    }
    if(block_down>block_up && block_up!=0){
        block_permit=1;
    }
    else if(block_down==0&&block_up>85){
        block_permit=1;
    }
    if(block_up<10&&block_down>block_up&&block_down-block_up>14)
      block_permit=0;
    else if(block_up<40&&block_down>block_up&&block_down-block_up>20){
      block_permit=0;
    }
    else if(block_up>=40&&block_down>block_up)
      if(block_down-block_up>30)
        block_permit=0;
    if(block_permit){
      Blo_row=block_up;
    }
    else
      Blo_row=0;
    if(block_permit==1){
      Blo_MidLine=0;
      for(s = block_down;s>=block_up;s--)
      {
        Blo_MidLine = (Block_left_line[s]+Block_right_line[s])/2+Blo_MidLine;
      }
      Blo_MidLine = Blo_MidLine/(block_down-block_up+1);
    }
}













void BloNor_JudAppear()
{
    if(NorDirection==LEFT){
      Sig_chosse=sigal_Rline_normal[Sig_row]+Mov_dev;
    }
    else{
      Sig_chosse=sigal_Lline_normal[Sig_row]-Mov_dev;
    }
    if(NorDirection==LEFT){
      Block_Judmid=70;
    }
    else{
      Block_Judmid=87;
    }
    if(Tur_AvoidBlo_flag==1)
      Blo_Row_Limit = 40;
    else
      Blo_Row_Limit = 25;
    if(Blo_row<Blo_Row_Limit){
      /*********************2017年8月18日14:11:09注释**********
      if((Sig_row<25)&&(Sig_row>5)&&(Blo_row>0)&&//障碍在右
         (Blo_MidLine>Block_Judmid)&&(Blo_MidLine<115)&&
         (Sig_MidLine>MAX((Sig_chosse-25),0))&&
           (Sig_MidLine<Sig_chosse+25)){
         Blo_STATE = Blo_Founded;
      }
       if((Sig_row<25)&&(Sig_row>5)&&(Blo_row>0)&&  //障碍在左
       (Blo_MidLine<=Block_Judmid)&&(Blo_MidLine>41)&&
       (Sig_MidLine>MAX((Sig_chosse-25),0))&&
         (Sig_MidLine<Sig_chosse+25)){
       Blo_STATE = Blo_Founded;
     }
      *******************2017年8月18日14:11:20*******************/
      Rev_Vision_Row = Rev_Vision_Line[Sig_MidLine];
      if(Tur_AvoidBlo_flag==1){
        Uper_Limit = Sig_chosse+55;
        Lower_Limit= Sig_chosse-55;
      }
      else{
        Uper_Limit = Sig_chosse+25;
        Lower_Limit = Sig_chosse-25;
      }
      if((Sig_row<Rev_Vision_Row)&&(Sig_row>5)&&(Blo_row>0)&&//障碍在右
         (Blo_MidLine>Block_Judmid)&&(Blo_MidLine<115)&&
         (Sig_MidLine>MAX(Lower_Limit,0))&&
           (Sig_MidLine<Uper_Limit)){
         Blo_STATE = Blo_Founded;
      }
       if((Sig_row<Rev_Vision_Row)&&(Sig_row>5)&&(Blo_row>0)&&  //障碍在左
       (Blo_MidLine<=Block_Judmid)&&(Blo_MidLine>41)&&
       (Sig_MidLine>MAX(Lower_Limit,0))&&
         (Sig_MidLine<Uper_Limit)){
       Blo_STATE = Blo_Founded;
     }
     if(Blo_STATE==Blo_Founded){
       Blo_RTemoporary = (block_Lline[Blo_row]-Blo_MidLine+Movblo_dev);
       Blo_LTemoporary = (block_Rline[Blo_row]-Blo_MidLine+Movblo_dev);
       if(ABS(Sig_MidLine+Blo_LTemoporary-79)>ABS(Sig_MidLine+Blo_RTemoporary-79)){
         Block_ComLeft = 1;
         Block_ComRight= 0;
       }
       else{
         Block_ComRight  = 1;
         Block_ComLeft   = 0;
      }
    }
 }
}
void BloSpe_JudAppear()
{
    if(NorDirection==LEFT)
    Avoid_BloOffset = sigal_Rline_normal[Sig_row]-Sig_MidLine+Mov_dev;
  else
    Avoid_BloOffset = sigal_Lline_normal[Sig_row]-Sig_MidLine-Mov_dev;
  if(Blo_MidLine<=(79-Avoid_BloOffset))
    Blo_chosse = block_Lline[Blo_row]-Movblo_dev;
  else
    Blo_chosse = block_Rline[Blo_row]+Movblo_dev;
  if(Blo_row>50&&((Blo_AgreeDelay&&Blo_AgrDelay_Count<=50)||Blo_STATE==Blo_Delaying)){
    if((Sig_row<50)&&(Sig_row>5)&&(Blo_MidLine>(79-Avoid_BloOffset))  //障碍在右
        &&(Blo_MidLine<Blo_chosse)){//①
       Blo_Delay_Right=1;
     }
     if((Sig_row<50)&&(Sig_row>5)&&(Blo_MidLine<=(79-Avoid_BloOffset)) //障碍在左
        &&(Blo_MidLine>Blo_chosse)){//①
       Blo_Delay_Left=1;
       }
    }
}
void BloNor_JudDisappear()
{
    if(((Block_ComRight==1)&&(Blo_MidLine>=150))
       ||
         ((Block_ComLeft==1)&&(Blo_MidLine<=10))
           ||(((Sig_MidLine>140)||(Sig_MidLine<20))&&((Block_ComRight)||(Block_ComLeft)))
             ||
               (Blo_row>=90)){
       Block_ComLeft    =0;
       Block_ComRight   =0;
        Blo_STATE = Blo_Missing;
    }
}
void BloSpe_JudDisappear()
{
    if((((Blo_Delay_Right==1)&&(Blo_MidLine<=4))||((Blo_Delay_Left==1)&&
    (Blo_MidLine>=155))||((!Sig_permit)&&
    ((Blo_Delay_Right)||(Blo_Delay_Left)))||(Blo_row>=115))){
      Las_Blo_Dev = Block_DelDev;
      Missing_Flag =1;
    }
}
void Blo_Delay_DevGiv()
{
  Las_Blo_Dev=Block_DelDev;
   if(NorDirection==LEFT)
    Avoid_BloOffset = sigal_Rline_normal[Sig_row]-Sig_MidLine+Mov_dev;
  else
    Avoid_BloOffset = sigal_Lline_normal[Sig_row]-Sig_MidLine-Mov_dev;
  if(Blo_MidLine<=(79-Avoid_BloOffset))
    Blo_chosse = block_Lline[Blo_row]-Movblo_dev;
  else
    Blo_chosse = block_Rline[Blo_row]+Movblo_dev;
  if(Blo_row>50&&((Blo_AgreeDelay&&Blo_AgrDelay_Count<=50)||Blo_STATE==Blo_Delaying)){
    if((Sig_row<50)&&(Sig_row>5)  //障碍在右
        &&(Blo_MidLine<Blo_chosse+10)&&Blo_Delay_Right){//①
       Block_DelDev= (block_Rline[Blo_row]-Blo_MidLine-Spec_BloDev);
     }
    else if(Blo_Delay_Right){
      Block_DelDev =Las_Blo_Dev;
    }
     if((Sig_row<50)&&(Sig_row>5) //障碍在左
        &&(Blo_MidLine>Blo_chosse-10)&&Blo_Delay_Left){//①
       Block_DelDev= (block_Lline[Blo_row]-Blo_MidLine+Spec_BloDev);
       }
    else if(Blo_Delay_Left)
      Block_DelDev = Las_Blo_Dev;
    }
}

void Dis_STATE_Judgement()
{
    if(Sig_row>65&&Sig_row!=120){
      CloSigal_Count++;
      if(CloSigal_Count>2){
        Dis_STATE=Dis_Clo;
      }
    }
    else if(Sig_row&&Sig_row<=65){
      CloSigal_Count=0;
      Dis_STATE=Dis_Far;
    }
}
void Forced_TurDirection()
{
  if(Las_Sigpermit==1&&Sig_permit==0){
    Losing_Row = Last_sigal_row;
  }
  Forced_TurRow = FuzForced_TurDirection[Sig_FuzzyRow];
  if(Lost_flag>=LOST_LIMIT)
  {
    if(Losing_Row > Forced_TurRow&&Losing_Row<90)
      Forced_Turdirection = 1;
    else
      Forced_Turdirection = 0;
  }
  else
    Forced_Turdirection = 0;
}