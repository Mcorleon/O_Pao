#ifndef _FUZZYSET_SPEED_H_
#define _FUZZYSET_SPEED_H_

#include "include.h" 

int16 FuzzySet_Speed(int16 P, int16 D);  /*Ä£ºýÔËËãÒýÇæ*/
extern int16 Turn_Speed ;
void Rev_PerCorrection(int8 row)      ;
void Spe_Speedset_Giv()               ;
void FuzzyGiv_DMAXMIN()               ;
extern int16 *UFF    ;
extern int16 UFF1[7] ;
extern int16 UFF2[7] ;
extern int16 UFF3[7] ;
extern int16 UFF4[7] ;
extern int16 UFF5[7] ;
typedef enum
{
  Fuz_RecReady = 1,
  Fuz_RecFinished = 2,
}Fuz_STATUS_e;

#endif