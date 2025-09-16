#ifndef DRI_ExINT_h
#define DRI_ExINT_h

#ifdef __cplusplus 
extern "C" { 
#endif 

#include "DRI_ComDriver.h"

/***************************************************************************
* �� �� ��: DRI_ExINT_Config
* �����������ⲿ�����ж����ú���
* ��ڲ�����
            ExIntCnfType *eict�����ýṹ��ָ��
* ���ڲ�����
            -1:��ʾ����ʧ��
            0:��ʾ���óɹ�
* ע������:  
            PA2,PB2,PC2,PD2,PE2���������ͬ�Ĳ���ͬʱ���֡�
* ��     ��:
* �޸ļ�¼ :
*           2025-09-02 BY:YJX
***************************************************************************/
extern s8 DRI_ExINT_Config(ExIntCnfType *eict);

#ifdef __cplusplus 
}
#endif 

#endif

