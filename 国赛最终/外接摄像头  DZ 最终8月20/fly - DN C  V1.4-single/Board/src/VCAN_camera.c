#include "common.h"
#include "VCAN_camera.h"
#include "Servo_Motor.h"

 int8 Sig_row_A             =   0;  //信标灯的行数
 int8 Sig_row_B             =   0;
uint8 Sig_permit_A          =   0; //是否发现信标灯
uint8 Sig_permit_B          =   0;
int16 Left_line_A[CAMERA_H]      ;
int16 Right_line_A[CAMERA_H]     ;
int16 Left_line_B[CAMERA_H]  ;
int16 Right_line_B[CAMERA_H] ;
int16 Middle_line[CAMERA_H]      ;
int16 Start_line_limit      =   4;
int16 End_line_limit        = 157;
extern uint8 img_1[OV7725_EAGLE_H_1][OV7725_EAGLE_W_1];
extern uint8 img[OV7725_EAGLE_H][OV7725_EAGLE_W]      ;

#define Sigal_size_initialization    0
#define Right_line_initialization  159
#define Left_line_initialization     0
#define Middle_line_initialization  80
#define B_W0_A Black_to_White_A[0]
#define B_W1_A Black_to_White_A[1]
#define W_B0_A White_to_Black_A[0]
#define W_B1_A White_to_Black_A[1]
#define B_W2_A Black_to_White_A[2]
#define W_B2_A White_to_Black_A[2]

#define B_W0_B Black_to_White_B[0]
#define B_W1_B Black_to_White_B[1]
#define W_B0_B White_to_Black_B[0]
#define W_B1_B White_to_Black_B[1]
#define B_W2_B Black_to_White_B[2]
#define W_B2_B White_to_Black_B[2]

#define  LEFT_LINE_FOUND_A img_1[row][i]<img_1[row][i+1]&&img_1[row][i-1]<img_1[row][i+2]&&Left_line_A[row]==0
#define RIGHT_LINE_FOUND_A img_1[row][i-1]>img_1[row][i]&&img_1[row][i-2]>img_1[row][i+1]&&((img_1[row][i+5]==0&&i<=154)||i>154)&&Right_line_A[row]==159
#define  LEFT_LINE_FOUND_B img[row][i]<img[row][i+1]&&img[row][i-1]<img[row][i+2]&&Left_line_B[row]==0
#define RIGHT_LINE_FOUND_B img[row][i-1]>img[row][i]&&img[row][i-2]>img[row][i+1]&&((img[row][i+5]==0&&i<=154)||i>154)&&Right_line_B[row]==159
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
void sigal_finding_A(void)   //封装完毕
{
  uint8 sigal_permit        =   0;
  int8 row                  =   0;
  int8 start_finding_line   =   0;
  int8 sigal_down           =   0;
  int8 b_count              =   0;
  int8 w_count              =   0;
  int8 sigal_up             =   0;
  int16 temp                =   0;
  int16 i                   =   0;
  int16 Black_to_White_A[5] = {0};
  int16 White_to_Black_A[5] = {0};
  int16 sigal_size[120]     = {0};
  int16 Start_line          =   0;
  int8 sigal_row            =   0;
    for(row = 0 ; row < 120 ; row ++)
    {
       Left_line_A[row] = Left_line_initialization;
       Right_line_A[row] = Right_line_initialization;  
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
          if(LEFT_LINE_FOUND_A){
              Left_line_A[row] = i;
              if(start_finding_line==0){
                start_finding_line=row+3;
              }
              if(ABS(Left_line_A[row]-Left_line_A[row+1])<10){
                Start_line = i - ABS(Left_line_A[row+2] - Left_line_A[row+1])-8 ;
              }
          }
          if(RIGHT_LINE_FOUND_A){
              if(start_finding_line==0){
                start_finding_line=row;
              }
              if(i>154){
                Right_line_A[row]=i;
                break;
              }
              else if(img_1[row][i+5]==0&&i<=154){
                Right_line_A[row]=i;    
                break;
              }
          }
       }
       sigal_size[row]=Right_line_A[row]-Left_line_A[row]; 
       if(sigal_size[row]>40)   {
         sigal_size[row] = 0;
       }
       if(row<117){
          if(sigal_size[row]>0&&sigal_size[row+1]>0&&sigal_size[row+2]==0&&sigal_size[row+3]==0)   {
            Black_to_White_A[b_count++]=row+1;
          }
       }
       if(sigal_size[row]==0&&sigal_size[row+1]==0&&sigal_size[row+2]>0&&sigal_size[row+3]>0)   {
         White_to_Black_A[w_count++]=row+2; 
       }
    }  
    b_count--;
    w_count--;
    if(W_B0_A!=0&&B_W0_A!=0&&B_W0_A>W_B0_A){
        if(b_count==0&&w_count==0){
          sigal_up=W_B0_A   ;
          sigal_down=B_W0_A ;
          sigal_permit=1  ;
        }
        if(b_count==1&&w_count==1){
            if(((W_B0_A-B_W1_A<=25)&&(W_B0_A>70))||(W_B0_A-B_W1_A<=20)){
              sigal_down=B_W1_A ;
              sigal_up=W_B1_A   ; 
              sigal_permit=1    ;
            }
            else{
              sigal_up=B_W0_A   ;
              sigal_down=B_W0_A ;
              sigal_permit=1    ;
            }
        }
        if(b_count>=2&&w_count>=2){
          if(((W_B0_A-B_W1_A<=25)&&(W_B0_A>70))||(W_B1_A-B_W2_A<=20)){
            sigal_down=B_W2_A ;
            sigal_up=W_B2_A   ; 
            sigal_permit=1    ;
          }
          else if((W_B0_A-B_W1_A<=20)&&(W_B1_A-B_W2_A>20)){
            sigal_down=B_W1_A;
            sigal_up=W_B1_A  ;
            sigal_permit=1   ;
          }
          else{
            sigal_down=B_W0_A;
            sigal_up=W_B0_A  ;
            sigal_permit=1   ;
          }
        }
    }

    if(W_B0_A>B_W0_A&&W_B0_A>=70){
      if(b_count==0&&w_count==0){
        sigal_down=117;   
        sigal_up=W_B0_A ;  
        sigal_permit=1;
      }
      if(b_count==0&&w_count==1&&(W_B0_A>70)&&B_W0_A>0){
        sigal_down=B_W0_A;
        sigal_up=W_B1_A  ;
        sigal_permit=1   ;
      }
    }
    if(sigal_permit){
      for(row=sigal_down;row>=sigal_up;row--)
      {
          if(sigal_size[row]>=temp){
            sigal_row=row       ;   
            temp=sigal_size[row];
          }
      }
    }
    Sig_permit_A=sigal_permit ;
}
void sigal_finding_B(void)   //封装完毕
{
  uint8 sigal_permit        =   0;
  int8 row                  =   0;
  int8 start_finding_line   =   0;
  int8 sigal_down           =   0;
  int8 b_count              =   0;
  int8 w_count              =   0;
  int8 sigal_up             =   0;
  int16 temp                =   0;
  int16 i                   =   0;
  int16 Black_to_White_B[5] = {0};
  int16 White_to_Black_B[5] = {0};
  int16 sigal_size[120]     = {0};
  int16 Start_line          =   0;
  int8 sigal_row            =   0;
    for(row = 0 ; row < 120 ; row ++)
    {
       Left_line_B[row] = Left_line_initialization;
       Right_line_B[row] = Right_line_initialization;  
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
          if(LEFT_LINE_FOUND_B){
              Left_line_B[row] = i;
              if(start_finding_line==0){
                start_finding_line=row+3;
              }
              if(ABS(Left_line_B[row]-Left_line_B[row+1])<10){
                Start_line = i - ABS(Left_line_B[row+2] - Left_line_B[row+1])-8 ;
              }
          }
          if(RIGHT_LINE_FOUND_B){
              if(start_finding_line==0){
                start_finding_line=row;
              }
              if(i>154){
                Right_line_B[row]=i;
                break;
              }
              else if(img_1[row][i+5]==0&&i<=154){
                Right_line_B[row]=i;    
                break;
              }
          }
       }
       sigal_size[row]=Right_line_B[row]-Left_line_B[row]; 
       if(sigal_size[row]>40)   {
         sigal_size[row] = 0;
       }
       if(row<117){
          if(sigal_size[row]>0&&sigal_size[row+1]>0&&sigal_size[row+2]==0&&sigal_size[row+3]==0)   {
            Black_to_White_B[b_count++]=row+1;
          }
       }
       if(sigal_size[row]==0&&sigal_size[row+1]==0&&sigal_size[row+2]>0&&sigal_size[row+3]>0)   {
         White_to_Black_B[w_count++]=row+2; 
       }
    }  
    b_count--;
    w_count--;
    if(W_B0_B!=0&&B_W0_B!=0&&B_W0_B>W_B0_B){
        if(b_count==0&&w_count==0){
          sigal_up=W_B0_B   ;
          sigal_down=B_W0_B ;
          sigal_permit=1    ;
        }
        if(b_count==1&&w_count==1){
            if(((W_B0_B-B_W1_B<=25)&&(W_B0_B>70))||(W_B0_B-B_W1_B<=20)){
              sigal_down=B_W1_B ;
              sigal_up=W_B1_B   ; 
              sigal_permit=1    ;
            }
            else{
              sigal_up=B_W0_B   ;
              sigal_down=B_W0_B ;
              sigal_permit=1    ;
            }
        }
        if(b_count>=2&&w_count>=2){
          if(((W_B0_B-B_W1_B<=25)&&(W_B0_B>70))||(W_B1_B-B_W2_B<=20)){
            sigal_down=B_W2_B ;
            sigal_up=W_B2_B   ; 
            sigal_permit=1    ;
          }
          else if((W_B0_B-B_W1_B<=20)&&(W_B1_B-B_W2_B>20)){
            sigal_down=B_W1_B;
            sigal_up=W_B1_B  ;
            sigal_permit=1   ;
          }
          else{
            sigal_down=B_W0_B;
            sigal_up=W_B0_B  ;
            sigal_permit=1   ;
          }
        }
    }

    if(W_B0_B>B_W0_B&&W_B0_B>=70){
      if(b_count==0&&w_count==0){
        sigal_down=117  ;   
        sigal_up=W_B0_B ;  
        sigal_permit=1  ;
      }
      if(b_count==0&&w_count==1&&(W_B0_B>70)&&B_W0_B>0){
        sigal_down=B_W0_B;
        sigal_up=W_B1_B  ;
        sigal_permit=1   ;
      }
    }
    if(sigal_permit){
      for(row=sigal_down;row>=sigal_up;row--)
      {
          if(sigal_size[row]>=temp){
            sigal_row=row       ;   
            temp=sigal_size[row];
          }
      }
    }
    if(sigal_row>80)
      sigal_permit=0;
    Sig_permit_B = sigal_permit;
}
