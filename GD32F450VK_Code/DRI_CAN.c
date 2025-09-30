/********************************************************************************************************************************************
*                                                                                                                                           *
*              ---------------------------------������ģ����޸ļ�¼��-----------------------------------------                             *
*                                                                                                                                           *
********************************************************************************************************************************************/
/**********************************************
 * ���ݣ�
 * ���ڣ�2025-09-11
 * ���ߣ�YJX
 * �汾�ţ�V1.0�����棩
 ***********************************************
 * �޸����ݣ�
 * �޸����ڣ�
 * �޸����ߣ�
 * �汾�ţ�
 ***********************************************
*/
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------����ģ���˵����-----------------------------------------                                  *
*                                                                                                                                           *
********************************************************************************************************************************************/
/*	

*/
#include "DRI_CAN.h"
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------����ģ��ĶԽӺ�����-----------------------------------------                                  *
*                                                                                                                                           *
********************************************************************************************************************************************/

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ��ı��������ͺ궨����--------------------------------                      *
*                                                                                                                                           *
********************************************************************************************************************************************/
typedef struct 
{
     u32 bps;
     u16 prescaler;
     u8 bs1;
     u8 bs2;
}CAN_BpsParaType;
/*
�������ò��������=0���������80%��
������(Kbps)	Prescaler	BS1(TQ)	BS2(TQ)	SJW(TQ)	��TQ	������	ʵ�ʲ�����(Kbps)	  ���(%)
1000	          3	     10	     2	     1	     13	76.92%	1000	               0.00%
800	          4	     10	     2	     1	     13	76.92%	807.69	          +0.96%
500	          8	     10	     2	     1	     13	76.92%	500	               0.00%
400	          7	     15	     3	     1	     19	78.95%	400	               0.00%
250	          14	     15	     3	     1	     19	78.95%	250	               0.00%
200	          17	     15	     3	     1	     19	78.95%	200	               0.00%
125	          34	     15	     3	     1	     19	78.95%	125	               0.00%
100	          42	     15	     3	     1	     19	78.95%	100	               0.00%
50	          84	     15	     3	     1	     19	78.95%	50	               0.00%
40	          105	     15	     3	     1	     19	78.95%	40	               0.00%
25	          168	     15	     3	     1	     19	78.95%	25	               0.00%
20	          210	     15	     3	     1	     19	78.95%	20	               0.00%
15	          280	     15	     3	     1	     19	78.95%	15	               0.00%
10	          420	     15	     3	     1	     19	78.95%	10	               0.00%
5	          840	     15	     3	     1	     19	78.95%	5	               0.00%
*/
//42MHz��CANʱ���£������ʲ���
static const CAN_BpsParaType CAN_42M_BpsPara[] =
{
     {.bps = 1000000, .prescaler = 3, .bs1 = 10, .bs2 = 2}, //1Mbps
     {.bps = 800000,  .prescaler = 4, .bs1 = 10, .bs2 = 2}, //800Kbps
     {.bps = 500000,  .prescaler = 8, .bs1 = 10, .bs2 = 2}, //500Kbps
     {.bps = 400000,  .prescaler = 7, .bs1 = 15, .bs2 = 3}, //400Kbps
     //{.bps = 250000,  .prescaler = 14, .bs1 = 15, .bs2 = 3}, //250Kbps
     {.bps = 250000,  .prescaler = 12, .bs1 = 10, .bs2 = 3}, //250Kbps
     {.bps = 200000,  .prescaler = 17, .bs1 = 15, .bs2 = 3}, //200Kbps
     {.bps = 100000,  .prescaler = 42, .bs1 = 15, .bs2 = 3}, //100Kbps
     {.bps = 50000,   .prescaler = 84, .bs1 = 15, .bs2 = 3}, //50Kbps
     {.bps = 40000,   .prescaler = 105, .bs1 = 15, .bs2 = 3}, //40Kbps
     {.bps = 25000,   .prescaler = 168, .bs1 = 15, .bs2 = 3}, //25Kbps
     {.bps = 20000,   .prescaler = 210, .bs1 = 15, .bs2 = 3}, //20Kbps
     {.bps = 15000,   .prescaler = 280, .bs1 = 15, .bs2 = 3}, //15Kbps
     {.bps = 10000,   .prescaler = 420, .bs1 = 15, .bs2 = 3}, //10Kbps
     {.bps = 5000,    .prescaler = 840, .bs1 = 15, .bs2 = 3} //5Kbps
};
//
static DRI_CAN_ReceCBFType CAN0_ReceCBF = NULL;
static DRI_CAN_ReceCBFType CAN1_ReceCBF = NULL;
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����ڲ�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
static s8 CAN_CalculateCANParameters(u32 baudrate,u16 *prescaler,u8 *bs1,u8 *bs2);
static s8 CAN_SendData(u32 canx,DRI_CAN_CommunicatDataType *data);
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ���ϵͳ����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
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
s8 DRI_CANx_Config(DRI_CANCnfType *cnf)
{
     can_parameter_struct can_parameter;
     can_filter_parameter_struct can_filter;
     u8 u8s1, u8s2;
     u16 u16prescaler;
     u32 RxPinPort,RxPinNum,TxPinPort,TxPinNum;
     u32 CanX,FifoNotEmptyInterrupt;
     IRQn_Type IRQn;

     if(CAN_CalculateCANParameters(cnf->Bps, &u16prescaler, &u8s1, &u8s2))
     {
          return -1;
     }

     

//-------------- GPIO -------------------------
     switch(cnf->PinSelect)
     {
          case CAN0_RX_PA11_TX_PA12:               
               //CAN0_RX:PA11
               RxPinPort = GPIOA;
               RxPinNum = GPIO_PIN_11;
               //CAN0_TX:PA12
               TxPinPort = GPIOA;
               TxPinNum = GPIO_PIN_12;
               //ʹ��GPIOAʱ��
               rcu_periph_clock_enable(RCU_GPIOA);               
               //ʹ��CAN0ʱ��
               rcu_periph_clock_enable(RCU_CAN0); 
               //
               CanX = CAN0;
               can_filter.filter_number = 0;//0�Ź�����
               can_filter.filter_fifo_number = CAN_FIFO0;//����FIFO0
               FifoNotEmptyInterrupt = CAN_INTEN_RFNEIE0;//����FIFO0�ǿ��ж�
               IRQn = CAN0_RX0_IRQn;
               CAN0_ReceCBF = cnf->ReceCBF;
               break;
          case CAN0_RX_PB8_TX_PB9:
               //CAN0_RX:PB8
               RxPinPort = GPIOB;
               RxPinNum = GPIO_PIN_8;
               //CAN0_TX:PB9
               TxPinPort = GPIOB;
               TxPinNum = GPIO_PIN_9;
               //ʹ��GPIOBʱ��
               rcu_periph_clock_enable(RCU_GPIOB);//ʹ��GPIOBʱ��               
               //ʹ��CAN0ʱ��
               rcu_periph_clock_enable(RCU_CAN0); 
               //
               CanX = CAN0;
               can_filter.filter_number = 0;//0�Ź�����
               can_filter.filter_fifo_number = CAN_FIFO0;//����FIFO0
               FifoNotEmptyInterrupt = CAN_INTEN_RFNEIE0;//����FIFO0�ǿ��ж�
               IRQn = CAN0_RX0_IRQn;
               CAN0_ReceCBF = cnf->ReceCBF;
               break;
          case CAN0_RX_PD0_TX_PD1:
               //CAN0_RX:PD0
               RxPinPort = GPIOD;
               RxPinNum = GPIO_PIN_0;
               //CAN0_TX:PD1
               TxPinPort = GPIOD;
               TxPinNum = GPIO_PIN_1;
               //ʹ��GPIODʱ��
               rcu_periph_clock_enable(RCU_GPIOD);//ʹ��GPIODʱ��               
               //ʹ��CAN0ʱ��
               rcu_periph_clock_enable(RCU_CAN0); 
               //
               CanX = CAN0;
               can_filter.filter_number = 0;//0�Ź�����
               can_filter.filter_fifo_number = CAN_FIFO0;//����FIFO0
               FifoNotEmptyInterrupt = CAN_INTEN_RFNEIE0;//����FIFO0�ǿ��ж�
               IRQn = CAN0_RX0_IRQn;
               CAN0_ReceCBF = cnf->ReceCBF;
               break;
          case CAN1_RX_PB5_TX_PB6:
               //CAN1_RX:PB5
               RxPinPort = GPIOB;
               RxPinNum = GPIO_PIN_5;
               //CAN1_TX:PB6
               TxPinPort = GPIOB;
               TxPinNum = GPIO_PIN_6;
               //ʹ��GPIOBʱ��
               rcu_periph_clock_enable(RCU_GPIOB);//ʹ��GPIOBʱ��
               //ʹ��CAN1ʱ��
               rcu_periph_clock_enable(RCU_CAN1); 
               //
               CanX = CAN1;
               can_filter.filter_number = 1;//1�Ź�����
               can_filter.filter_fifo_number = CAN_FIFO1;//����FIFO1
               FifoNotEmptyInterrupt = CAN_INTEN_RFNEIE1;//����FIFO1�ǿ��ж�
               IRQn = CAN0_RX1_IRQn;
               CAN1_ReceCBF = cnf->ReceCBF;
               break;
          case CAN1_RX_PB12_TX_PB13:
               //CAN1_RX:PB12
               RxPinPort = GPIOB;
               RxPinNum = GPIO_PIN_12;
               //CAN1_TX:PB13
               TxPinPort = GPIOB;
               TxPinNum = GPIO_PIN_13;
               //ʹ��GPIOBʱ��
               rcu_periph_clock_enable(RCU_GPIOB);//ʹ��GPIOBʱ��
               //ʹ��CAN1ʱ��
               rcu_periph_clock_enable(RCU_CAN1); 
               //
               CanX = CAN1;
               can_filter.filter_number = 1;//1�Ź�����
               can_filter.filter_fifo_number = CAN_FIFO1;//����FIFO1
               FifoNotEmptyInterrupt = CAN_INTEN_RFNEIE1;//����FIFO1�ǿ��ж�
               IRQn = CAN0_RX1_IRQn;
               CAN1_ReceCBF = cnf->ReceCBF;
               break;
          default:
               return -2;
     }
     //
     //CAN_RX
     gpio_output_options_set(RxPinPort, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, RxPinNum);
     gpio_mode_set(RxPinPort, GPIO_MODE_AF, GPIO_PUPD_NONE, RxPinNum);
     gpio_af_set(RxPinPort, GPIO_AF_9, RxPinNum);
     //CAN_TX
     gpio_output_options_set(TxPinPort, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, TxPinNum);
     gpio_mode_set(TxPinPort, GPIO_MODE_AF, GPIO_PUPD_NONE, TxPinNum);
     gpio_af_set(TxPinPort, GPIO_AF_9, TxPinNum);

     //
     can_deinit(CanX);//CAN��λ
     can_parameter.time_triggered = DISABLE;//ʱ�䴥��ͨ��ģʽ������
     can_parameter.auto_bus_off_recovery = DISABLE;//�Զ����߹رջָ�������
     can_parameter.auto_wake_up = DISABLE;//�Զ����ѣ�����
     can_parameter.auto_retrans = DISABLE;//�Զ��ش�������
     can_parameter.rec_fifo_overwrite = DISABLE;//����FIFO���ʱ���ǣ�����
     can_parameter.trans_fifo_order = DISABLE;//����FIFO���ȼ���ID����������
     can_parameter.working_mode = CAN_NORMAL_MODE;//����ģʽ
     can_parameter.resync_jump_width = CAN_BT_SJW_1TQ;//����ͬ����ת��ȣ�1��ʱ�䵥λ
//----------------------------   
     //bps = APB1 / (prescaler * (1 + time_segment_1 + time_segment_2))
     //bps = 42 000 000 / (12 * (1 + 10 + 3)) = 250 000
//---------------------------- 
     can_parameter.time_segment_1 = (u8s1 - 1);//CAN_BT_BS1_10TQ;//ʱ���1
     can_parameter.time_segment_2 = (u8s2 - 1);//CAN_BT_BS2_3TQ;//ʱ���2
     can_parameter.prescaler = u16prescaler;//12;//�����ʷ�Ƶϵ��
     

     if(can_init(CanX, &can_parameter) != SUCCESS)//��ʼ��CAN
     {
          return -2;
     }

     //��ʼ�������� 
     //can_filter.filter_number = 0;//ʹ��0���������//CAN0��14���������������CAN1��15�鿪ʼ������       
     can_filter.filter_mode = CAN_FILTERMODE_MASK;//�������ģʽ
     can_filter.filter_bits = CAN_FILTERBITS_32BIT;//32λ������(29λ)
     can_filter.filter_list_high = 0x0000;//����ֵ��λ
     can_filter.filter_list_low = 0x0000;//����ֵ��λ
     can_filter.filter_mask_high = 0x0000;//����������ֵ��λ
     can_filter.filter_mask_low = 0x0000; //����������ֵ��λ
     //can_filter.filter_fifo_number = CAN_FIFO0;//����FIFO0
     can_filter.filter_enable = ENABLE;//ʹ�ܹ�����
     can_filter_init(&can_filter);//��ʼ��������

     //�����ж�
     //nvic_irq_enable(IRQn,0,0);
     NVIC_SetPriority(IRQn, cnf->IntPri);//�����ж����ȼ�
     NVIC_ClearPendingIRQ(IRQn);//����жϱ�־
     NVIC_EnableIRQ(IRQn);//ʹ���ж�

     //ʹ�ܽ���FIFO�ǿ��ж�
     can_interrupt_enable(CanX, FifoNotEmptyInterrupt);

     return 0;
}

void CAN0_RX0_IRQHandler(void)
{
     u8 u8temp;
     can_receive_message_struct receive_message;
     DRI_CAN_CommunicatDataType cdt;
     //
     can_struct_para_init(CAN_RX_MESSAGE_STRUCT, &receive_message);//��ʼ��
     can_message_receive(CAN0, CAN_FIFO0, &receive_message);
     //
     if(CAN0_ReceCBF != NULL)
     {
          cdt.FrameType = 0;//��׼֡
          cdt.FrameID = receive_message.rx_sfid;//֡ID
          if(CAN_FF_EXTENDED == receive_message.rx_ff)
          {//����չ֡
               cdt.FrameType = 1;//��չ֡
               cdt.FrameID = receive_message.rx_efid;//֡ID
          }
          cdt.FrameDataLen = receive_message.rx_dlen;//֡���ݳ���
          for(u8temp = 0;u8temp < receive_message.rx_dlen;u8temp++)
          {
               cdt.FrameData[u8temp] = receive_message.rx_data[u8temp];//��ȡ����
          }
          CAN0_ReceCBF(&cdt);
     }
}

void CAN1_RX1_IRQHandler(void)
{
     u8 u8temp;
     can_receive_message_struct receive_message;
     DRI_CAN_CommunicatDataType cdt;
     //
     can_struct_para_init(CAN_RX_MESSAGE_STRUCT, &receive_message);//��ʼ��
     can_message_receive(CAN1, CAN_FIFO1, &receive_message);
     //
     if(CAN1_ReceCBF != NULL)
     {
          cdt.FrameType = 0;//��׼֡
          cdt.FrameID = receive_message.rx_sfid;//֡ID
          if(CAN_FF_EXTENDED == receive_message.rx_ff)
          {//����չ֡
               cdt.FrameType = 1;//��չ֡
               cdt.FrameID = receive_message.rx_efid;//֡ID
          }
          cdt.FrameDataLen = receive_message.rx_dlen;//֡���ݳ���
          for(u8temp = 0;u8temp < receive_message.rx_dlen;u8temp++)
          {
               cdt.FrameData[u8temp] = receive_message.rx_data[u8temp];//��ȡ����
          }
          CAN1_ReceCBF(&cdt);
     }
}

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����û�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
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
s8 DRI_CAN0_SendData(DRI_CAN_CommunicatDataType *data)
{
     return CAN_SendData(CAN0,data);
}

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
s8 DRI_CAN1_SendData(DRI_CAN_CommunicatDataType *data)
{
     return CAN_SendData(CAN1,data);
}

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����ڲ�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
//����CAN�����ʲ���
static s8 CAN_CalculateCANParameters(u32 baudrate,u16 *prescaler,u8 *bs1,u8 *bs2)
{
     u16 u16i,u16temp;
     //CANʱ��ԴƵ��ΪPCLK1
     if(rcu_clock_freq_get(CK_APB1) != 42000000)
     {//ʱ��ԴƵ�ʲ���42M
          return -1;
     }
     u16temp = sizeof(CAN_42M_BpsPara)/sizeof(CAN_42M_BpsPara[0]);
     for(u16i = 0;u16i < u16temp;u16i++)
     {
          if(baudrate == CAN_42M_BpsPara[u16i].bps)
          {
               *prescaler = CAN_42M_BpsPara[u16i].prescaler;
               *bs1 = CAN_42M_BpsPara[u16i].bs1;
               *bs2 = CAN_42M_BpsPara[u16i].bs2;
               return 0;
          }
     }
     return -2;
}

//����CAN����
//����ֵ��0���ɹ���-1��ʧ��
static s8 CAN_SendData(u32 canx,DRI_CAN_CommunicatDataType *data)
{
     u8 u8i;
     can_trasnmit_message_struct transmit_message;//���巢����Ϣ�ṹ��
     can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &transmit_message);
     /* initialize transmit message */
     transmit_message.tx_sfid = data->FrameID;//��׼֡ID
     transmit_message.tx_efid = data->FrameID;//��չ֡ID
     transmit_message.tx_ft = CAN_FT_DATA;//����֡  CAN_FT_REMOTE//Զ��֡
     transmit_message.tx_ff = CAN_FF_STANDARD;//��׼֡��ʽ
     if(data->FrameType)
     {
          transmit_message.tx_ff = CAN_FF_EXTENDED;//��չ֡��ʽ
     }
     transmit_message.tx_dlen = data->FrameDataLen;//���ݳ���
     for(u8i = 0;u8i < data->FrameDataLen;u8i++)//����
     {
          transmit_message.tx_data[u8i] = data->FrameData[u8i];
     }
     //
     if(can_message_transmit(CAN0, &transmit_message) == CAN_NOMAILBOX)//��������
     {//����ʧ��
          return -1;
     }
     return 0;
}

