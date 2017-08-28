/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.0
 * @date       2013-08-28
 */
/***************************************************************************
尚未开启硬件浮点运算    别忘了开
*****************************************************************************/
#include  "Motor.h"
#include  "Filter.h"
//uint8 s=0;
motor_status motor;
uint8 Motor_Protection_Flag = 0;
float Leftchasu(int16 num);
float Rightchasu(int16 num);
void myMotor_Setspeed(int16 PWM_L,int16 PWM_R);
extern Sig_STATUS_e   Sig_STATE;// = Sig_Finished;
extern int16 direction_duty_output;
extern Blo_STATUS_e  Blo_STATE;   
extern int8 Sig_row;
extern int8 divide_servos_flag;
extern int8 start_count;   //这个是起跑的 不用管
extern int8 number_adding; //起跑的不用管
extern Blo_STATUS_e  Blo_STATE;
extern uint8 Car_Stop_flag;
//Car_STATUS_e  Car_STATE;
void speed_control2(void)
{
  
  motor.speed_p=3.5;
  motor.speed_i=1.0;//1.0
  
    
//速度滤波左 获得速度中值
    motor.speed_set_L=motor.speed_set;
//速度滤波右 获得速度中值
    motor.speed_set_R=motor.speed_set;
    
//    //根据舵机pwm来设定差速值
    if(((direction_duty_output-Servo_mid)>=20)||Blo_STATE==Blo_Founded||Sig_STATE==Sig_Finished||Sig_STATE==Sig_Missing) //向左打角   
    {
      motor.speed_set_R=(int16)(motor.speed_set_R*(2/(1+Leftchasu(direction_duty_output-Servo_mid))));//右边加
      motor.speed_set_L=(int16)(motor.speed_set_L*(2*Leftchasu(direction_duty_output-Servo_mid))/(1+Leftchasu(direction_duty_output-Servo_mid))); //左边减
    }
    else if(((direction_duty_output-Servo_mid)<=-20)||Blo_STATE==Blo_Founded||Sig_STATE==Sig_Finished||Sig_STATE==Sig_Missing) //向右打角,右轮减速,左轮加速
    {
      motor.speed_set_L=(int16)(motor.speed_set_L*(2/(1+Rightchasu((direction_duty_output-Servo_mid)))));//左边加
      motor.speed_set_R=(int16)(motor.speed_set_R*(2*Rightchasu((direction_duty_output-Servo_mid)))/(1+Rightchasu(direction_duty_output-Servo_mid))); //右边减
    } 
        motor.speed_last_error_L = motor.speed_current_error_L;        //更新每次的差值
        motor.speed_current_error_L = motor.speed_set_L-motor.speed_L;   //速度当前差值

        motor.speed_duty_output_L = motor.speed_duty_output_L+(int16)(motor.speed_p*(motor.speed_current_error_L-motor.speed_last_error_L)+motor.speed_i*motor.speed_current_error_L);
        
        motor.speed_last_error_R = motor.speed_current_error_R;        //更新每次的差值
        motor.speed_current_error_R = motor.speed_set_R-motor.speed_R;   //速度当前差值

        motor.speed_duty_output_R = motor.speed_duty_output_R+(int16)(motor.speed_p*(motor.speed_current_error_R-motor.speed_last_error_R)+motor.speed_i*motor.speed_current_error_R);

    if(motor.speed_duty_output_L>L_Speed_MAX) motor.speed_duty_output_L=L_Speed_MAX;
    if(motor.speed_duty_output_L<L_Speed_MIN) motor.speed_duty_output_L=L_Speed_MIN;
    if(motor.speed_duty_output_R>R_Speed_MAX) motor.speed_duty_output_R=R_Speed_MAX;
    if(motor.speed_duty_output_R<R_Speed_MIN) motor.speed_duty_output_R=R_Speed_MIN;

    myMotor_Setspeed(motor.speed_duty_output_R,motor.speed_duty_output_L);
}
float Rightchasu(int16 num)  //num<0 ,从-0-- -220
{
    float K_right;
    int16 i;
    i=num;
   
    float       p1;
    if(Sig_STATE==Sig_Finished||Sig_STATE == Sig_Missing){
   
      if(speed_level==1)
       p1 =  0.00190;
     else if(speed_level==2)
       p1 =  0.00177;
     else if(speed_level==3)
       p1 =  0.00177;
     else if(speed_level==4)
       p1 =  0.00168;
     else if(speed_level==5)
       p1 =  0.00188;
    }
    else if(Blo_STATE== Blo_Founded)
      p1 = 0.00110;
        else
      p1 =    0.00085;
   float        p2 =       1.015  ;

    K_right = p1*i + p2;
    return (K_right);
}

/*************************************************************************
*  函数名称：Leftchasu
*  功能说明：查表法差速
*  参数说明：uint8 load_type  道路类型
*  函数返回：无
*  修改时间：2016-4-21     
*  备    注：以内轮为目标，左内轮，向左拐弯
*************************************************************************/
float Leftchasu(int16 num)   //num>0 ,从-0--  -220
{
    float K_left;
    int16 i;
    i=num;
    float       p1;
    if(Sig_STATE==Sig_Finished||Sig_STATE == Sig_Missing)
    {
      if(speed_level==1)
       p1 = - 0.00190;
     else if(speed_level==2)
       p1 = - 0.00177;
     else if(speed_level==3)
       p1 = - 0.00177;
     else if(speed_level==4)
       p1 = - 0.00168;
     else if(speed_level==5)
       p1 = - 0.00188;
    }
    else if(Blo_STATE== Blo_Founded)
      p1 = -0.00110;
    else
      p1 =    -0.00085;
    float        p2 =       1.012  ;
    K_left = p1*i + p2;
    return (K_left);
}
void Motor_init(void)
{
    ftm_pwm_init(L_GO_FTM,L_GO_CH,MOTOR_FRE,INIT_DUTY);
    ftm_pwm_init(L_BACK_FTM,L_BACK_CH,MOTOR_FRE,INIT_DUTY);
    ftm_pwm_init(R_GO_FTM,R_GO_CH,MOTOR_FRE,INIT_DUTY);
    ftm_pwm_init(R_BACK_FTM,R_BACK_CH,MOTOR_FRE,INIT_DUTY);
}
void myMotor_Setspeed(int16 PWM_R,int16 PWM_L)//给速度
{
  if(PWM_L>=0)
    {
      ftm_pwm_duty(L_BACK_FTM,L_BACK_CH,0);
      ftm_pwm_duty(L_GO_FTM,L_GO_CH,(uint32)(PWM_L));
    }
  else
    {
      ftm_pwm_duty(L_GO_FTM,L_GO_CH,0);
      ftm_pwm_duty(L_BACK_FTM,L_BACK_CH,(uint32)(-PWM_L));
    } 

  if(PWM_R>=0)
    {
      ftm_pwm_duty(R_BACK_FTM,R_BACK_CH,0);
      ftm_pwm_duty(R_GO_FTM,R_GO_CH,(uint32)(PWM_R));
    }
  else
    {
      ftm_pwm_duty(R_GO_FTM,R_GO_CH,0);
      ftm_pwm_duty(R_BACK_FTM,R_BACK_CH,(uint32)(-PWM_R));
    }
}
void Motor_protect()
{
    if((motor.speed_L<30||motor.speed_R < 30)&&number_adding>22 )
    { 
      Motor_Protection_Flag = 1;
      ftm_pwm_duty(L_GO_FTM,L_GO_CH,0);
      ftm_pwm_duty(L_BACK_FTM,L_BACK_CH,0); 
      ftm_pwm_duty(R_GO_FTM,R_GO_CH,0);
      ftm_pwm_duty(R_BACK_FTM,R_BACK_CH,0); 
    }
      else
      Motor_Protection_Flag = 0;
}