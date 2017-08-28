/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       VCAN_SCCB.h
 * @brief      OV����ͷ��������SCCB������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-09-01
 */


#ifndef _VCAN_SCCB_H_
#define _VCAN_SCCB_H_

//SCCB �ܽ�����
#define SCCB_SCL_1        PTB21
#define SCCB_SDA_1        PTB23

#define SCL_H_1()         PTXn_T(SCCB_SCL_1,OUT) = 1
#define SCL_L_1()         PTXn_T(SCCB_SCL_1,OUT) = 0
#define SCL_DDR_OUT_1()   PTXn_T(SCCB_SCL_1,DDR) = 1
#define SCL_DDR_IN_1()    PTXn_T(SCCB_SCL_1,DDR) = 0

#define SDA_H_1()         PTXn_T(SCCB_SDA_1,OUT) = 1
#define SDA_L_1()         PTXn_T(SCCB_SDA_1,OUT) = 0
#define SDA_IN_1()        PTXn_T(SCCB_SDA_1,IN)
#define SDA_DDR_OUT_1()   PTXn_T(SCCB_SDA_1,DDR) = 1
#define SDA_DDR_IN_1()    PTXn_T(SCCB_SDA_1,DDR) = 0

#define ADDR_OV7725   0x42
#define ADDR_OV7620   0x42

#define DEV_ADR  ADDR_OV7725             /*�豸��ַ����*/

#define SCCB_DELAY()    SCCB_delay(400)


extern void SCCB_GPIO_init_1(void);
extern int SCCB_WriteByte_1( uint16 WriteAddress , uint8 SendByte);
extern int SCCB_ReadByte_1(uint8 *pBuffer,   uint16 length,   uint8 ReadAddress);


//����Ϊ����ͷ1 SCCB��ʼ������ͷ�ļ�
/***********************************�ֽ���*******************************************************/
//����Ϊ����ͷ0 SCCB��ʼ������ͷ�ļ�

//SCCB �ܽ�����
#define SCCB_SCL        PTA26
#define SCCB_SDA        PTA25

#define SCL_H()         PTXn_T(SCCB_SCL,OUT) = 1
#define SCL_L()         PTXn_T(SCCB_SCL,OUT) = 0
#define SCL_DDR_OUT()   PTXn_T(SCCB_SCL,DDR) = 1
#define SCL_DDR_IN()    PTXn_T(SCCB_SCL,DDR) = 0

#define SDA_H()         PTXn_T(SCCB_SDA,OUT) = 1
#define SDA_L()         PTXn_T(SCCB_SDA,OUT) = 0
#define SDA_IN()        PTXn_T(SCCB_SDA,IN)
#define SDA_DDR_OUT()   PTXn_T(SCCB_SDA,DDR) = 1
#define SDA_DDR_IN()    PTXn_T(SCCB_SDA,DDR) = 0



extern void SCCB_GPIO_init(void);
extern int SCCB_WriteByte( uint16 WriteAddress , uint8 SendByte);
extern int SCCB_ReadByte(uint8 *pBuffer,   uint16 length,   uint8 ReadAddress);

#endif      //_VCAN_SCCB_H_
