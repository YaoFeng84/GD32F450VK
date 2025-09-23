#ifndef DRI_GPIO_h
#define DRI_GPIO_h

#ifdef __cplusplus 
extern "C" { 
#endif 

#include "DRI_ComDriver.h"



/***************************************************************************
* �� �� ��: DRI_GPIO_Config
* ����������GPIO�������ú���
* ��ڲ�����
            PortNum enPort���˿ں�(ȡGPORTA,GPORTB,GPORTC,GPORTD,GPORTE,GPORTH)
            PinNum u16Pin�����ź�(ȡGP00~GP15)
            PinMode gm��GDOut��ʾ������� GDIn��ʾ��������
* ���ڲ�����
            -1:��ʾ����ʧ��
            0:��ʾ���óɹ�
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-08-29 BY:YJX
***************************************************************************/
extern s8 DRI_GPIO_Config(PortNum portn, PinNum pinn, PinMode gm);

/***************************************************************************
* �� �� ��: DRI_GPIO_OUT_1
* ����������GPIO��������ߵ�ƽ����
* ��ڲ�����
            PortNum portn���˿ں�(ȡGPORTA,GPORTB,GPORTC,GPORTD,GPORTE,GPORTH)
            PinNum pinn�����ź�(ȡGP00~GP15)
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-08-29 BY:YJX
***************************************************************************/
extern void DRI_GPIO_OUT_1(PortNum portn, PinNum pinn);

/***************************************************************************
* �� �� ��: DRI_GPIO_OUT_0
* ����������GPIO��������͵�ƽ����
* ��ڲ�����
            PortNum enPort���˿ں�(ȡGPORTA,GPORTB,GPORTC,GPORTD,GPORTE,GPORTH)
            PinNum u16Pin�����ź�(ȡGP00~GP15)
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-08-29 BY:YJX
***************************************************************************/
extern void DRI_GPIO_OUT_0(PortNum portn, PinNum pinn);

/***************************************************************************
* �� �� ��: DRI_GPIO_OUT_Turn
* ����������GPIO���������ת����
* ��ڲ�����
            PortNum enPort���˿ں�(ȡGPORTA,GPORTB,GPORTC,GPORTD,GPORTE,GPORTH)
            PinNum u16Pin�����ź�(ȡGP00~GP15)
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-08-29 BY:YJX
***************************************************************************/
extern void DRI_GPIO_OUT_Turn(PortNum portn, PinNum pinn);

/***************************************************************************
* �� �� ��: DRI_GPIO_Read
* ����������GPIO���Ŷ�����
* ��ڲ�����
            PortNum enPort���˿ں�(ȡGPORTA,GPORTB,GPORTC,GPORTD,GPORTE,GPORTH)
            PinNum u16Pin�����ź�(ȡGP00~GP15)
* ���ڲ�����
            0:��ʾ�͵�ƽ
          ��0:��ʾ�ߵ�ƽ
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-08-29 BY:YJX
***************************************************************************/
extern u8 DRI_GPIO_Read(PortNum portn, PinNum pinn);


#ifdef __cplusplus 
}
#endif 

#endif

