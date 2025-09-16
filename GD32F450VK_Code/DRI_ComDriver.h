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
* ����������ʹ���������ж� ����
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
* ���������������������ж� ����
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

typedef enum
{
     ITFallEdge = 0u,//�½���
     ITRiseEdge = 1u,//������
     ITBothEdg = 2u //˫����
}INTTriggerMode;//����ģʽö��

typedef struct
{
     PortNum portn;      //�ⲿ�ж϶˿ں�
     PinNum pinn;        //�ⲿ�ж����ź�
     INTTriggerMode tm;  //����ģʽ
     u8 pri;             //�ж����ȼ�(0~15��ԽС���ȼ�Խ��)
     void (*cbfp)(void); //�жϻص�����ָ��
}ExIntCnfType;


typedef enum
{
     DataBits8 = 0u,//8λ���ݿ��
     DataBits9 = 1u,//9λ���ݿ��
}DataBitType;

typedef enum
{
     HalfStopBit = 0u,//��λֹͣλ
     OneStopBit = 1u,//1λֹͣλ
     OneAndHalfStopBit = 2u,//1.5λֹͣλ
     TwoStopBit = 3u,//2λֹͣλ
}StopBitType;

typedef enum
{
     ParityNone = 0u,//��У��
     ParityEven = 1u,//żУ��
     ParityOdd = 2u,//��У��
}ParityType;

typedef struct
{
     u8 FEnable;              //����Ӳ����ʹ��λ(0:���� ��0:ʹ��)
     u8 RHWFlowXonLevel;      //����Ӳ����XON��ƽ(0:�͵�ƽ ��0:�ߵ�ƽ)
     u8 RHWFlowDefaultLevel;  //����Ӳ����Ĭ�ϵ�ƽ(0:�͵�ƽ ��0:�ߵ�ƽ)
     PortNum RFlowcontrolp;   //����Ӳ���ض˿ں�
     PinNum RFlowcontroln;    //����Ӳ�������ź�
}RHWFlowCrl;

typedef struct
{
//---��������
     u32 bps;            //������(2400~921600)
     DataBitType DataBit;//����λ
     StopBitType StopBit;//ֹͣλ
     ParityType  Parity; //У��ģʽ
     RHWFlowCrl rhwfc;   //����Ӳ����
//---�ж�����
     u8 IntPri;        //�����ж����ȼ�(0~15��ԽС���ȼ�Խ�ߣ�������Χ��ֹ�ж�)
//---���ղ���
     void (*Recfp)(u8);  //���յ����ݻص�����ָ��
     u8 RecData_IntEnable;//���������ж�ʹ��(0:��ֹ ��0:ʹ��)
//---���Ͳ���
     void (*SendOKfp)(void);//������ɻص�����ָ��
     u8 SendOK_IntEnable;//��������ж�ʹ��(0:��ֹ ��0:ʹ��)
     u8 SendINTDefaultState;//�����ж�Ĭ��״̬(0:�ر� 1:����)
}DRI_USARTCnfType;

/**
 * @brief
 *     P0Setup���ݴ���ص�����
 * @param  u8*  �����������׵�ַ
 * @param  u16  �����������ֽ���
 * @param  u8*  ���������׵�ַ
 * @param  u16* ����(�������ݿռ��ֽ���) ���(ʵ�ʷ���/��ȡ���ֽ���)
 * @return s8   С��0:��ʾ�������
 *              ����0:��ʾ����δ����
 *                  1:��ʾ�����Ѵ�����Ҫ�����ص�����ͨ��P0�˿ڷ��͸�����
 *                  2:��ʾ�����Ѵ�����Ҫ��P0�˿ڵ�OUT���ݶ�ȡ����
 */
typedef s8(*DRI_USB_P0SetupProcessFunc)(u8*,u16,u8*,u16*);
typedef void(*DRI_USB_ReceDataFunc)(u8*,u16);
typedef s32(*DRI_USB_P0OutProcessFunc)(u8*,u16);//P0�˿�OUT���ݵĴ���ص�����ָ��(OUT�����׵�ַ,OUT�����ֽ���)����ֵ:ʵ�ʴ����ֽ���

typedef struct
{
     u8 IntPri;                    //�ж����ȼ�(0~15)
     DRI_USB_ReceDataFunc ReceDataFunc;//USB�յ����ݻص�����ָ��
     DRI_USB_P0SetupProcessFunc P0SetupProcess;//P0ö�ٴ���ص�����ָ��
     DRI_USB_P0OutProcessFunc P0OutProcess;//P0�˿�OUT���ݴ���ص�����ָ��
}DRI_USBCnfType;

typedef struct
{
     u8 OutEP_Num;               //����˵��
     u8 OutEP_Type;            //����˵�����(0:���ƶ˵� 1:�ж϶˵� 2:�����˵� 3:ͬ���˵�)
     u16 OutEP_MaxPacketSize;      //����˵������ֽ���
     //
     u8 InEP_Num;                 //����˵��
     u8 InEP_Type;             //����˵�����(0:���ƶ˵� 1:�ж϶˵� 2:�����˵� 3:ͬ���˵�)
     u16 InEP_MaxPacketSize;       //����˵������ֽ���
     //
     u8 IntInEP_Num;             //�ж�����˵��
     u8 IntInEP_Type;           //�ж�����˵�����(0:���ƶ˵� 1:�ж϶˵� 2:�����˵� 3:ͬ���˵�)
     u16 IntInEP_MaxPacketSize;    //�ж�����˵������ֽ���
     //
     u8 P0EP_MaxPacketSize;        //P0�˵������ֽ���
}DRI_USB_EPType;//USB�Ķ˵�ṹ��

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

#endif

