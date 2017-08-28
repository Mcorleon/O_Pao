/********************************S-D�������**********************************
* @author   ��ɳ���Ѿ�
* @file �� Servo_Motor.c
* @description   �� �����������
* @date  �� 2015/10/30
* @Instructions �� 
              ��ɫ        GND
              ��ɫ        VCC
              ��ɫ        PWM
����Ƶ�ʣ�   100     ��100~130HZ   ������200HZ 
*   
***************************************************************************/
#include "Servo_Motor.h"


servos_status servos;
/*************************************************************************
*���ߣ� ɳ���Ѿ�
*�������ƣ�Servo_Motor_init
*�������ܣ������ʼ��
*��ڲ�������
*���ڲ�������
*�ⲿ���ã���
*�޸�ʱ�䣺2015/10/30
************************************************************************/

void Servo_Motor_init(void)
{
        ftm_pwm_init(Servo_ftm,Servo_CH,Servo_freq,Servo_mid);    //��ʼ�����       
}

/*********************************************************** 
*���ߣ� ɳ���Ѿ�
*�������ƣ�Servos_setAngle
*�������ܣ�������
*��ڲ�����u16 duty ռ�ձ�
*���ڲ������� 
*�ⲿ���ã���
*�޸�ʱ�䣺2015/10/30
***********************************************************/
void direction_control(void)
{
       
        servos.direction_last_error = servos.diretion_current_error;
        servos.diretion_current_error = camer.error; 
  
        servos.PID = (int16)(servos.direction_p*servos.diretion_current_error+servos.direction_d*(servos.diretion_current_error-servos.direction_last_error));
        servos.direction_duty_output = Servo_mid - servos.PID ;
        if(servos.direction_duty_output>Servo_rmax)   //�������޷�
          servos.direction_duty_output = Servo_rmax;
        else  if(servos.direction_duty_output<Servo_lmax)
          servos.direction_duty_output = Servo_lmax;
        
        servo_stop_duty = servos.direction_duty_output;       //ͣ�����ֹͣ���

//          ftm_pwm_duty(Servo_ftm, Servo_CH, Servo_mid);
//        if(Car_Stop_flag==1)
//        {
//         ftm_pwm_duty(Servo_ftm,Servo_CH,Servo_mid);  
//        }
//        else
//        {
         ftm_pwm_duty(Servo_ftm,Servo_CH,servos.direction_duty_output); 
//        }
}








