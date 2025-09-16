#ifndef DRI_CLK_h
#define DRI_CLK_h

#ifdef __cplusplus 
extern "C" { 
#endif 

#include "DRI_ComDriver.h"


typedef struct
{
     u32 SysTickFreq;     ///< SysTick嘀嗒时钟频率
     u32 hclkFreq;       ///< Hclk 频率.(数据手册中最高200MHz)
     u32 pclk1Freq;      ///< Pclk1 频率.(数据手册中最高50MHz)
     u32 pclk2Freq;      ///< Pclk2 频率.(数据手册中最高100MHz)
     //u32 ckTimerFreq0;    //T0/T7/T8/T9/T10时钟频率
     //u32 ckTimerFreq1;    //T1/T2/T3/T4/T5/T6/T11/T12/T13时钟频率
     //u32 ckAdcFreq;        //ADC0、1、2时钟频率
}ClkFreqValue;

extern s8 DRI_CLK_Config(void);
extern void DRI_CLK_GetClockFreq(ClkFreqValue *pstcClkFreq);

#ifdef __cplusplus 
}
#endif 

#endif

