#ifndef DRI_CAN_h
#define DRI_CAN_h

#ifdef __cplusplus 
extern "C" { 
#endif 

#include "DRI_ComDriver.h"

typedef struct 
{     
     u32 FrameID;//֡ID
     u8 FrameType;//֡����(0:��׼֡ ��0:��չ֡)
     u8 FrameDataLen;//���ݳ���
     u8 FrameData[8];//����
}DRI_CAN_CommunicatDataType;//ͨ����������

typedef enum
{
     CAN0_RX_PA11_TX_PA12 = 0,
     CAN0_RX_PB8_TX_PB9,
     CAN0_RX_PD0_TX_PD1,
     CAN1_RX_PB5_TX_PB6,
     CAN1_RX_PB12_TX_PB13
}DRI_CAN_PinSelectEnm;//CAN����ѡ��

typedef void(*DRI_CAN_ReceCBFType)(DRI_CAN_CommunicatDataType*);//���ջص���������

typedef struct 
{
     u32 Bps;//������
     u8 IntPri;//�ж����ȼ�
     DRI_CAN_PinSelectEnm PinSelect;//����ѡ��
     DRI_CAN_ReceCBFType ReceCBF;//���ջص�����
}DRI_CANCnfType;//CAN��������

/***************************************************************************
* �� �� ��: DRI_CANx_Config
* ����������CANx���ú���
* ��ڲ�����
            DRI_CANCnfType *cnf:CAN���ò���
* ���ڲ�����
            -1:��ʾ����ʧ��
            0:��ʾ���óɹ�
* ע������:  

* ��     ��:
* �޸ļ�¼ :
          
*           2025-09-11 BY:
***************************************************************************/
extern s8 DRI_CANx_Config(DRI_CANCnfType *cnf);


/***************************************************************************
* �� �� ��: DRI_CAN0_SendData
* ����������CAN0�������ݺ���
* ��ڲ�����
          DRI_CAN_CommunicatDataType *data:�����͵�����
* ���ڲ�����
          С��0:��ʾ��������ʧ��
             0:��ʾ�������ͳɹ�
* ע������:  

* ��     ��:
* �޸ļ�¼ :
          
*           2025-09-11 BY:
***************************************************************************/
extern s8 DRI_CAN0_SendData(DRI_CAN_CommunicatDataType *data);

/***************************************************************************
* �� �� ��: DRI_CAN1_SendData
* ����������CAN1�������ݺ���
* ��ڲ�����
          DRI_CAN_CommunicatDataType *data:�����͵�����
* ���ڲ�����
          С��0:��ʾ��������ʧ��
             0:��ʾ�������ͳɹ�
* ע������:  

* ��     ��:
* �޸ļ�¼ :
          
*           2025-09-11 BY:
***************************************************************************/
extern s8 DRI_CAN1_SendData(DRI_CAN_CommunicatDataType *data);


#ifdef __cplusplus 
}
#endif 

#endif

