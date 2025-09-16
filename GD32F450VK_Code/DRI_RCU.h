#ifndef DRI_RCU_h
#define DRI_RCU_h

#ifdef __cplusplus 
extern "C" { 
#endif 

#include "DRI_ComDriver.h"

extern ResetFlag DRI_RCU_GetResetFlag(void);
extern void DRI_RCU_ClearResetFlag(void);



#ifdef __cplusplus 
}
#endif 

#endif
