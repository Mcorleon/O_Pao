/********************************�������**********************************
*
*����   �� ɳ���Ѿ�
*�ļ��� �� FuzzySet_Speed.h
*����   �� ģ���㷨�趨�ٶ�ͷ�ļ�
*ʱ��   �� 2016/4/14
˵��    ���ο�FreeCarsģ����������  ʹ��ɽ��V5.3��
*
****************************************************************************/
#ifndef _FUZZYSET_SPEED_H_
#define _FUZZYSET_SPEED_H_

#include "include.h" 

int16 FuzzySet_Speed(int16 P, int16 D,int16 E);  /*ģ����������*/

void gearshift_integral(int16 SP,int16 SD,float PS,float PX,float IS,float IX);

extern int16 *UFF ;
extern int16 UFF1[7] ;
extern int16 UFF2[7] ;
extern int16 UFF_HX[7] ;
extern int16 UFF_SLOW[7] ;


#endif