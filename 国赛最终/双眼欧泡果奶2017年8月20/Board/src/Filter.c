#include "Motor.h"
extern int16 Prospect_see;
void filter_ProspectSee() //封装完毕
{
    static float a = 0;
    float sigal_error;
    motor.sigal_filter_error[4]=motor.sigal_filter_error[3];
    motor.sigal_filter_error[3]=motor.sigal_filter_error[2];
    motor.sigal_filter_error[2]=motor.sigal_filter_error[1];
    motor.sigal_filter_error[1]=motor.sigal_filter_error[0];
    motor.sigal_filter_error[0]=Prospect_see;
    sigal_error =motor.sigal_filter_error[0] - motor.sigal_filter_error[1];
    a = sigal_error/10 ;                //分母越小越滞后
    if(a < 0)
      a = -a;
    if(a > 0.85)
      a = 0.85 ;
    if(a>0.10)
    Prospect_see = (int16)((1-a)*motor.sigal_filter_error[0]+a*motor.sigal_filter_error[1]);
}
void filter_speed() //封装完毕
{
    static float a = 0;
    float speed_error;
    motor.speed_filter_error[4] = motor.speed_filter_error[3];
    motor.speed_filter_error[3] = motor.speed_filter_error[2];
    motor.speed_filter_error[2] = motor.speed_filter_error[1];
    motor.speed_filter_error[1] =  motor.speed_filter_error[0];
    motor.speed_filter_error[0] = motor.speed_set;
    speed_error = motor.speed_filter_error[0] - motor.speed_filter_error[1];
    a = speed_error/10 ;                //分母越小越滞后
    if(a < 0)
      a = -a;
    if(a > 0.95)
      a = 0.95 ;
    motor.speed_set = (int16)((1-a)*motor.speed_filter_error[0]+a*motor.speed_filter_error[1]);
}
void filter_speed_L()//封装完毕
{
    static float a = 0;
    float speed_error ;

    speed_error = motor.speed_L - motor.speed_L_save[0];
    a = speed_error/30 ;  //a是系数   分母如何选定 每个周期减下来的速度乘以2 再加上一些
    if(a < 0)
      a = -a ;
    if(a > 0.85)
      a = 0.85 ;
  motor.speed_L = (int16)(motor.speed_L * (1-a) + (motor.speed_L_save[0]+motor.speed_L_save[1]+motor.speed_L_save[2])*a/3);//(motor.speed_L * (1-a) + (motor.speed_L_save[0]+motor.speed_L_save[1]+motor.speed_L_save[2]+motor.speed_L_save[3]+motor.speed_L_save[4]+motor.speed_L_save[5]+motor.speed_L_save[6]+motor.speed_L_save[7]+motor.speed_L_save[8]+motor.speed_L_save[9])*a/10);// car.speed_new * 0.1 +  
  
  motor.speed_L_save[2] = motor.speed_L_save[1] ;
  motor.speed_L_save[1] = motor.speed_L_save[0] ;
  motor.speed_L_save[0] = motor.speed_L ;
}

void filter_speed_R() //封装完毕
{
    static float a = 0;
    float speed_error ;
    speed_error = motor.speed_R - motor.speed_R_save[0];
    a = speed_error/30 ;                //a是系数
    if(a < 0)
      a = -a ;
    if(a > 0.85)
      a = 0.85 ;
  motor.speed_R = (int16)(motor.speed_R * (1-a) + (motor.speed_R_save[0]+motor.speed_R_save[1]+motor.speed_R_save[2])*a/3);//(motor.speed_R * (1-a) + (motor.speed_R_save[0]+motor.speed_R_save[1]+motor.speed_R_save[2]+motor.speed_R_save[3]+motor.speed_R_save[4]+motor.speed_R_save[5]+motor.speed_R_save[6]+motor.speed_R_save[7]+motor.speed_R_save[8]+motor.speed_R_save[9])*a/10);// car.speed_new * 0.1 +  
  
  motor.speed_R_save[2] = motor.speed_R_save[1] ;
  motor.speed_R_save[1] = motor.speed_R_save[0] ;
  motor.speed_R_save[0] = motor.speed_R ;
}
