#ifndef DRI_ComDriver_h
#define DRI_ComDriver_h

#include "TypeMro.h"
#include "gd32f4xx.h"
//
#include "system_gd32f4xx.h"
//����ͷ�ļ�
#include "gd32f4xx_libopt.h"
//


//USB�豸����
//USB�ں�
#include "drv_usb_core.h"
#include "drv_usb_dev.h"
#include "drv_usb_regs.h"
//
#include "drv_usbd_int.h"
//USB�豸�ں�
#include "usbd_core.h"
#include "usbd_enum.h"


extern void NULLFP(void);

//���ع̼��汾��
extern u8* DRI_ComDriver_OutVersion(void);

//����оƬFlash�ռ��С����λ���ֽ�
extern u32 DRI_ComDriver_OutFlashSize(void);

//����оƬRAM�ռ��С����λ���ֽ�
extern u32 DRI_ComDriver_OutRAMSize(void);

//uid1:(0~31)��uid2:(32~63)��uid3:(64~95)��96λ
extern void DRI_ComDriver_OutUID(u32 *uid1, u32 *uid2, u32 *uid3);

extern void DRI_ComDriver_Delay1ms(void);
extern void DRI_ComDriver_Delay1us(void);

typedef void(*DRI_ComDriver_DoubleVoidFuncType)(void);//����һ��˫void�ĺ���ָ������

/***************************************************************************
* �� �� ��: DRI_ComDriver_SetHardFaultIntterrupt_FCB
* ��������������Ӳ�������жϻص� ����
* ��ڲ�����
            DRI_ComDriver_DoubleVoidFuncType fcbp��Ӳ�������жϻص�����ָ��
* ���ڲ�����
            ��
* ע������:  
            
* ��     ��:
* �޸ļ�¼ :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_SetHardFaultIntterrupt_FCB(DRI_ComDriver_DoubleVoidFuncType fcbp);

/***************************************************************************
* �� �� ��: DRI_ComDriver_SetSP
* ��������������ջ��ָ�� ����
* ��ڲ�����
            u32 _sp:ջ��ָ��ֵ
* ���ڲ�����
            ��
* ע������:  
            �޸�ջ��ָ��
* ��     ��:
* �޸ļ�¼ :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_SetSP(u32 _sp);

/*-------------------------------------------------
������:DRI_ComDriver_DisableAllPeripheralInterrupt
��   ��:�ر���������ĸ����ж�
��   ��:
       ��
����ֵ:
       ��
ע   ��:
       ��
ʾ   ��:
��   ��:YJX
��   ��:V1.0
ʱ   ��:2025-09-08
-------------------------------------------------*/
extern void DRI_ComDriver_DisableAllPeripheralInterrupt(void);

/*-------------------------------------------------
������:DRI_ComDriver_ResetAllPeripheral
��   ��:��λ��������
��   ��:
       ��
����ֵ:
       ��
ע   ��:
       ��
ʾ   ��:
��   ��:YJX
��   ��:V1.0
ʱ   ��:2025-09-08
-------------------------------------------------*/
extern void DRI_ComDriver_ResetAllPeripheral(void);

/***************************************************************************
* �� �� ��: DRI_ComDriver_EnableAllINT
* ����������ʹ�����ж� ����
           ���������жϣ�����������ں��жϣ���SysTick��PendSV����������Ӧ��
* ��ڲ�����
            ��
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_EnableAllINT(void);

/***************************************************************************
* �� �� ��: DRI_ComDriver_DisableAllINT
* �����������������ж� ����
           �������п������жϣ����������жϺ��ں��жϣ���SysTick��PendSV������������NMI�����������жϣ���ϵͳ�쳣����HardFault����Ӧ��
* ��ڲ�����
            ��
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_DisableAllINT(void);

/***************************************************************************
* �� �� ��: DRI_ComDriver_EnableAllFault
* ����������ʹ���ں����쳣 ����
* ��ڲ�����
            ��
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_EnableAllFault(void);

/***************************************************************************
* �� �� ��: DRI_ComDriver_DisableAllFault
* ���������������ں����쳣 ����
* ��ڲ�����
            ��
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_DisableAllFault(void);

/***************************************************************************
* �� �� ��: DRI_ComDriver_CoreReset
* �����������ں˸�λ ����
* ��ڲ�����
            ��
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_CoreReset(void);

/***************************************************************************
* �� �� ��: DRI_ComDriver_SysReset
* �������������踴λ ����
          �൱�� NVIC_SystemReset();
* ��ڲ�����
            ��
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_SysReset(void);

typedef enum
{
     GPORTA = 0u,
     GPORTB = 1u,
     GPORTC = 2u,
     GPORTD = 3u,
     GPORTE = 4u
}PortNum;

typedef enum
{
     GP00 = 0u,
     GP01 = 1u,
     GP02 = 2u,
     GP03 = 3u,
     GP04 = 4u,
     GP05 = 5u,
     GP06 = 6u,
     GP07 = 7u,
     GP08 = 8u,
     GP09 = 9u,
     GP10 = 10u,
     GP11 = 11u,
     GP12 = 12u,
     GP13 = 13u,
     GP14 = 14u,
     GP15 = 15u
}PinNum;

typedef enum
{
     GDOut = 0u,//�������
     GDIn = 1u  //��������
}PinMode;

#endif

