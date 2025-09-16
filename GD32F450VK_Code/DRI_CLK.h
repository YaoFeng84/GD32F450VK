#ifndef DRI_CLK_h
#define DRI_CLK_h

#ifdef __cplusplus 
extern "C" { 
#endif 

#include "DRI_ComDriver.h"


typedef struct
{
     u32 SysTickFreq;     ///< SysTick���ʱ��Ƶ��
     u32 hclkFreq;       ///< Hclk Ƶ��.(�����ֲ������200MHz)
     u32 pclk1Freq;      ///< Pclk1 Ƶ��.(�����ֲ������50MHz)
     u32 pclk2Freq;      ///< Pclk2 Ƶ��.(�����ֲ������100MHz)
     //u32 ckTimerFreq0;    //T0/T7/T8/T9/T10ʱ��Ƶ��
     //u32 ckTimerFreq1;    //T1/T2/T3/T4/T5/T6/T11/T12/T13ʱ��Ƶ��
     //u32 ckAdcFreq;        //ADC0��1��2ʱ��Ƶ��
}ClkFreqValue;

extern s8 DRI_CLK_Config(void);
extern void DRI_CLK_GetClockFreq(ClkFreqValue *pstcClkFreq);

#ifdef __cplusplus 
}
#endif 

#endif

