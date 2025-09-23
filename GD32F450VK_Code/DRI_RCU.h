#ifndef DRI_RCU_h
#define DRI_RCU_h

#ifdef __cplusplus 
extern "C" { 
#endif 

#include "DRI_ComDriver.h"

typedef enum
{
     LP_Rst    = 0u,   //���˯��/������λ����ʱ�ĸ�λ
     WWDGT_Rst = 1u,   //���ڿ��Ź���ʱ����λ����ʱ�ĸ�λ
     FWDGT_Rst = 2u,   //�������Ź���λ����ʱ�ĸ�λ
     SW_Rst    = 3u,   //�����λ����ʱ�ĸ�λ
     POR_Rst   = 4u,   //��Դ��λ����ʱ�ĸ�λ
     EP_Rst    = 5u,   //�ⲿ���Ÿ�λ����ʱ�ĸ�λ
     BOR_Rst   = 6u,   //Ƿѹ��λ��λ����ʱ�ĸ�λ     
     Multiply_Rst = 7u,   //��Դ��λ����ʱ�ĸ�λ
}ResetFlag;

extern ResetFlag DRI_RCU_GetResetFlag(void);
extern void DRI_RCU_ClearResetFlag(void);



#ifdef __cplusplus 
}
#endif 

#endif
