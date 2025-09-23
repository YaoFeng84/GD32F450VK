/********************************************************************************************************************************************
*                                                                                                                                           *
*              ---------------------------------������ģ����޸ļ�¼��-----------------------------------------                             *
*                                                                                                                                           *
********************************************************************************************************************************************/
/**********************************************
 * ���ݣ�
 * ���ڣ�2025-08-29
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
�ص㣺
     ��1����ʹ�õ����Ų��ǹ̶��ģ�����Ҫ���ֲ��ԭ��ͼ�ϰ��ŵ�����
            ���ԣ�����ʱ����������Ϊ��ͬ������ ��
     ��2�����жϺ�(��RecDataIntNum��RecErrIntNum)Ҫע�⣬���ܺ�����ģ��ʹ�õ��жϺ���ͬ
     ��3�������ȼ�ֵԽС��Խ�ߡ�


ʹ�����ӣ�
     UsartCnfType usartconfig;

     usartconfig.upn = Usart3;
     usartconfig.bps = 115200;
     usartconfig.rxp = GPORTE;
     usartconfig.rxn = GP04;
     usartconfig.txp = GPORTE;
     usartconfig.txn = GP05;
     usartconfig.Recfp = usar3;
     usartconfig.RecDataIntNum = Int000_IRQn;
     usartconfig.RecData_Pri = 15; 
     usartconfig.RecErrIntNum = Int001_IRQn;       
     usartconfig.RecErr_Pri = 0;        
     DRI_USARTn_Config(&usartconfig);
     DRI_USART3_SendSTR("Hello World! �������!\r\n");

     void usar3(u8 rd)
     {
          DRI_USART3_SendByte(rd);
     }
*/
#include "DRI_USARTn.h"
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
extern s8 DRI_GPIO_Config(PortNum portn, PinNum pinn, PinMode gm);
extern void DRI_GPIO_OUT_1(PortNum portn, PinNum pinn);
extern void DRI_GPIO_OUT_0(PortNum portn, PinNum pinn);

typedef void(*NULLFP1)(u8);//���庯��ָ������

#define XON    0x11
#define XOFF   0x13

static void (*ReceFunP0)(u8) = (NULLFP1)NULLFP;
// static void (*ReceFunP1)(u8) = (NULLFP1)NULLFP;//����ָ������ǿ��ת��
// static void (*ReceFunP2)(u8) = (NULLFP1)NULLFP;
// static void (*ReceFunP3)(u8) = (NULLFP1)NULLFP;
// static void (*ReceFunP4)(u8) = (NULLFP1)NULLFP;
// static void (*ReceFunP5)(u8) = (NULLFP1)NULLFP;
// static void (*ReceFunP6)(u8) = (NULLFP1)NULLFP;
// static void (*ReceFunP7)(u8) = (NULLFP1)NULLFP;

static void (*SendOKFunP0)(void) = NULLFP;
// static void (*SendOKFunP1)(void) = NULLFP;
// static void (*SendOKFunP2)(void) = NULLFP;
// static void (*SendOKFunP3)(void) = NULLFP;
// static void (*SendOKFunP4)(void) = NULLFP;
// static void (*SendOKFunP5)(void) = NULLFP;
// static void (*SendOKFunP6)(void) = NULLFP;
// static void (*SendOKFunP7)(void) = NULLFP;

static RHWFlowCrl RHWFC0;//,RHWFC1,RHWFC2,RHWFC3,RHWFC4,RHWFC5,RHWFC6,RHWFC7;//����Ӳ����
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����ڲ�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
static s8 USARTn_Config(u32 usart_periph,DRI_USARTCnfType *cnfp);

// static void USART1_ErrIrqCallback(void);
// static void USART1_RxCallback(void);
// static void USART1_TCxCallback(void);
// static void USART2_ErrIrqCallback(void);
// static void USART2_RxCallback(void);
// static void USART2_TCxCallback(void);
// static void USART3_ErrIrqCallback(void);
// static void USART3_RxCallback(void);
// static void USART3_TCxCallback(void);
// static void USART4_ErrIrqCallback(void);
// static void USART4_RxCallback(void);
// static void USART4_TCxCallback(void);
// static void USARTn_HW_Flowcontrol_ON(RHWFlowCrl *rhwfcp);
// static void USARTn_HW_Flowcontrol_OFF(RHWFlowCrl *rhwfcp);
// static s8 USARTn_12PinCheck(DRI_USARTCnfType *cnfp);
// static s8 USARTn_34PinCheck(DRI_USARTCnfType *cnfp);
//static s8 USARTn_Config(DRI_USARTCnfType *cnfp,USARTnPara *usartp);

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ���ϵͳ����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* �� �� ��: DRI_USART0_Config
* ����������USART0���ú���
* ��ڲ�����
            DRI_USARTCnfType *cnfp�����ýṹ��ָ��
* ���ڲ�����
            -1:��ʾ����ʧ��
            0:��ʾ���óɹ�
* ע������: 

* ��     ��:
* �޸ļ�¼ :
*           2025-08-29 BY:YJX
***************************************************************************/
s8 DRI_USART0_Config(DRI_USARTCnfType *cnfp)
{
     s8 s8result;
     //
     NVIC_DisableIRQ(USART0_IRQn);//��ֹ�жϣ���ֹ���ù����в����ж�
     //

     switch(cnfp->PinSelect)
     {
          case USART0_RX_PA10_TX_PA9:
               //ʹ��GPIOAʱ��
               rcu_periph_clock_enable(RCU_GPIOA);
               //ʹ��USART0ʱ��
               rcu_periph_clock_enable(RCU_USART0);

               //PA9 Tx��������
               //PA9���Ÿ��ù�������
               gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9);    
               //����USART��TXΪ���ù���
               gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_9);
               gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_9);

               //PA10 Rx��������
               //PA10���Ÿ��ù�������
               gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_10);
               //����USART��RXΪ���ù���
               gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_10);
               gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_10);
               break;
          default:
               return -1;
     }


     RHWFC0.FEnable = cnfp->rhwfc.FEnable;
     RHWFC0.RFlowcontroln = cnfp->rhwfc.RFlowcontroln;
     RHWFC0.RFlowcontrolp = cnfp->rhwfc.RFlowcontrolp;
     RHWFC0.RHWFlowDefaultLevel = cnfp->rhwfc.RHWFlowDefaultLevel;
     RHWFC0.RHWFlowXonLevel = cnfp->rhwfc.RHWFlowXonLevel;
     //����Ӳ�������� ����
     if(RHWFC0.FEnable)
     {//ʹ��Ӳ����
          //����Ӳ������������Ϊ���
          DRI_GPIO_Config(RHWFC0.RFlowcontrolp,RHWFC0.RFlowcontroln,GDOut);
          //����Ĭ�����ص�ƽ
          if(RHWFC0.RHWFlowDefaultLevel)
          {
               DRI_GPIO_OUT_1(RHWFC0.RFlowcontrolp,RHWFC0.RFlowcontroln);
          }
          else
          {
               DRI_GPIO_OUT_0(RHWFC0.RFlowcontrolp,RHWFC0.RFlowcontroln);
          }          
     }

     //����ģ������
     s8result = USARTn_Config(USART0,cnfp);
     //
     if((cnfp->IntPri < 16) && (s8result == 0))
     {//�����ж�
          NVIC_SetPriority(USART0_IRQn, cnfp->IntPri);//�����ж����ȼ�
          NVIC_ClearPendingIRQ(USART0_IRQn);//����жϱ�־
          NVIC_EnableIRQ(USART0_IRQn);//ʹ���ж�
          //nvic_irq_enable(USART0_IRQn, 2U, 0U);
     }
          
     return s8result;
}


void USART0_IRQHandler(void)
{
     u8 u8temp;
     
     if(RESET != usart_flag_get(USART0, USART_FLAG_RBNE))
     {
          if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))
          {
               u8temp = usart_data_receive(USART0);//��ȡ�������ݺ���Զ������־λ(usart_data_receive(USART0) & 0x7F);
               ReceFunP0(u8temp);//
          }
          else
          {
               u8temp = usart_data_receive(USART0);//��ȡ�������ݺ���Զ������־λ(usart_data_receive(USART0) & 0x7F);
          }
     }
     
     if(RESET != usart_flag_get(USART0, USART_FLAG_TC))
     {
          usart_flag_clear(USART0, USART_FLAG_TC);
          //�����ж�
          if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_TC))
          {
               SendOKFunP0();//�������ж�
          }
     }

     //�������
     if(RESET != usart_flag_get(USART0, USART_FLAG_ORERR))
     {
          usart_flag_clear(USART0, USART_FLAG_ORERR);
          u8temp = usart_data_receive(USART0);//������������          
     }

     //��������
     if(RESET != usart_flag_get(USART0, USART_FLAG_NERR))
     {
          usart_flag_clear(USART0, USART_FLAG_NERR);
          u8temp = usart_data_receive(USART0);//������������          
     }

     //֡����
     if(RESET != usart_flag_get(USART0, USART_FLAG_FERR))
     {
          usart_flag_clear(USART0, USART_FLAG_FERR);
          u8temp = usart_data_receive(USART0);//������������          
     }

     //��ż����
     if(RESET != usart_flag_get(USART0, USART_FLAG_PERR))
     {
          usart_flag_clear(USART0, USART_FLAG_PERR);
          u8temp = usart_data_receive(USART0);//������������          
     }
}//












// /***************************************************************************
// * �� �� ��: DRI_USART2_Config
// * ����������USART2���ú���
// * ��ڲ�����
//             DRI_USARTCnfType *cnfp�����ýṹ��ָ��
// * ���ڲ�����
//             -1:��ʾ����ʧ��
//             0:��ʾ���óɹ�
// * ע������: 

// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// s8 DRI_USART2_Config(DRI_USARTCnfType *cnfp)
// {
//      USARTnPara usartpara;

//      if(USARTn_12PinCheck(cnfp))
//      {//����λ�ô���
//           return -1;
//      }  
     
//      usartpara.UsartCh = M4_USART2;               
//      usartpara.UsartRxFunc = Func_Usart2_Rx;
//      usartpara.UsartTxFunc = Func_Usart2_Tx;
//      usartpara.u32Fcg1Periph = PWC_FCG1_PERIPH_USART2;
//      usartpara.UsartRiSrc = INT_USART2_RI;
//      usartpara.UsartEiSrc = INT_USART2_EI;
//      usartpara.UsartTCiSrc = INT_USART2_TCI;
//      usartpara.TCIcbf = USART2_TCxCallback;
//      usartpara.RIcbf = USART2_RxCallback;
//      usartpara.EIcbf = USART2_ErrIrqCallback;
//      ReceFunP2 = cnfp->Recfp;
//      SendOKFunP2 = cnfp->SendOKfp;
//      RHWFC2 = cnfp->rhwfc;
//      return USARTn_Config(cnfp,&usartpara);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_Config
// * ����������USART3���ú���
// * ��ڲ�����
//             DRI_USARTCnfType *cnfp�����ýṹ��ָ��
// * ���ڲ�����
//             -1:��ʾ����ʧ��
//             0:��ʾ���óɹ�
// * ע������: 

// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// s8 DRI_USART3_Config(DRI_USARTCnfType *cnfp)
// {
//      USARTnPara usartpara;

//      if(USARTn_34PinCheck(cnfp))
//      {//����λ�ô���
//           return -1;
//      }  
     
//      usartpara.UsartCh = M4_USART3;               
//      usartpara.UsartRxFunc = Func_Usart3_Rx;
//      usartpara.UsartTxFunc = Func_Usart3_Tx;
//      usartpara.u32Fcg1Periph = PWC_FCG1_PERIPH_USART3;
//      usartpara.UsartRiSrc = INT_USART3_RI;
//      usartpara.UsartEiSrc = INT_USART3_EI;
//      usartpara.UsartTCiSrc = INT_USART3_TCI;
//      usartpara.TCIcbf = USART3_TCxCallback;
//      usartpara.RIcbf = USART3_RxCallback;
//      usartpara.EIcbf = USART3_ErrIrqCallback;
//      ReceFunP3 = cnfp->Recfp;
//      SendOKFunP3 = cnfp->SendOKfp;
//      RHWFC3 = cnfp->rhwfc;
//      return USARTn_Config(cnfp,&usartpara);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_Config
// * ����������USART4���ú���
// * ��ڲ�����
//             DRI_USARTCnfType *cnfp�����ýṹ��ָ��
// * ���ڲ�����
//             -1:��ʾ����ʧ��
//             0:��ʾ���óɹ�
// * ע������: 

// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// s8 DRI_USART4_Config(DRI_USARTCnfType *cnfp)
// {
//      USARTnPara usartpara;

//      if(USARTn_34PinCheck(cnfp))
//      {//����λ�ô���
//           return -1;
//      }  
     
//      usartpara.UsartCh = M4_USART4;               
//      usartpara.UsartRxFunc = Func_Usart4_Rx;
//      usartpara.UsartTxFunc = Func_Usart4_Tx;
//      usartpara.u32Fcg1Periph = PWC_FCG1_PERIPH_USART4;
//      usartpara.UsartRiSrc = INT_USART4_RI;
//      usartpara.UsartEiSrc = INT_USART4_EI;
//      usartpara.UsartTCiSrc = INT_USART4_TCI;
//      usartpara.TCIcbf = USART4_TCxCallback;
//      usartpara.RIcbf = USART4_RxCallback;
//      usartpara.EIcbf = USART4_ErrIrqCallback;
//      ReceFunP4 = cnfp->Recfp;
//      SendOKFunP4 = cnfp->SendOKfp;
//      RHWFC4 = cnfp->rhwfc;
//      return USARTn_Config(cnfp,&usartpara);
// }


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����û�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* �� �� ��: DRI_USART0_SendByte
* ����������USART0 ������ ����1���ֽں���
* ��ڲ�����
            u8 sd���������ֽ�
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-09-01 BY:YJX
***************************************************************************/
void DRI_USART0_SendByte(u8 sd)
{
     while (RESET == usart_flag_get(USART0, USART_FLAG_TBE));
     usart_data_transmit(USART0, sd);
}

// /***************************************************************************
// * �� �� ��: DRI_USART1_SendByte
// * ����������USART1 ������ ����1���ֽں���
// * ��ڲ�����
//             u8 sd���������ֽ�
// * ���ڲ�����
//             ��
// * ע������:  
//             ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART1_SendByte(u8 sd)
// {
//      M4_USART1->DR_f.TDR = sd;//д���ݵ����ͻ���
//      while((M4_USART1->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
// }

// /***************************************************************************
// * �� �� ��: DRI_USART1_NonBlockSendByte
// * ����������USART1 �������� ����1���ֽں���
// * ��ڲ�����
//             u8 sd���������ֽ�
// * ���ڲ�����
//             ��
// * ע������:  
//             ��Ϸ�������ж�ʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART1_NonBlockSendByte(u8 sd)
// {
//      M4_USART1->DR_f.TDR = sd;//д���ݵ����ͻ���
// }


// /***************************************************************************
// * �� �� ��: DRI_USART2_SendByte
// * ����������USART2 ������ ����1���ֽں���
// * ��ڲ�����
//             u8 sd���������ֽ�
// * ���ڲ�����
//             ��
// * ע������:  
//             ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART2_SendByte(u8 sd)
// {
//      M4_USART2->DR_f.TDR = sd;//д���ݵ����ͻ���
//      while((M4_USART2->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
// }

// /***************************************************************************
// * �� �� ��: DRI_USART2_NonBlockSendByte
// * ����������USART2 �������� ����1���ֽں���
// * ��ڲ�����
//             u8 sd���������ֽ�
// * ���ڲ�����
//             ��
// * ע������:  
//             ��Ϸ�������ж�ʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART2_NonBlockSendByte(u8 sd)
// {
//      M4_USART2->DR_f.TDR = sd;//д���ݵ����ͻ���
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_SendByte
// * ����������USART3 ������ ����1���ֽں���
// * ��ڲ�����
//             u8 sd���������ֽ�
// * ���ڲ�����
//             ��
// * ע������:  
//             ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART3_SendByte(u8 sd)
// {
//      M4_USART3->DR_f.TDR = sd;//д���ݵ����ͻ���
//      while((M4_USART3->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_NonBlockSendByte
// * ����������USART3 �������� ����1���ֽں���
// * ��ڲ�����
//             u8 sd���������ֽ�
// * ���ڲ�����
//             ��
// * ע������:  
//             ��Ϸ�������ж�ʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART3_NonBlockSendByte(u8 sd)
// {
//      M4_USART3->DR_f.TDR = sd;//д���ݵ����ͻ���
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_SendByte
// * ����������USART4 ������ ����1���ֽں���
// * ��ڲ�����
//             u8 sd���������ֽ�
// * ���ڲ�����
//             ��
// * ע������:  
//             ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART4_SendByte(u8 sd)
// {
//      M4_USART4->DR_f.TDR = sd;//д���ݵ����ͻ���
//      while((M4_USART4->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_NonBlockSendByte
// * ����������USART4 �������� ����1���ֽں���
// * ��ڲ�����
//             u8 sd���������ֽ�
// * ���ڲ�����
//             ��
// * ע������:  
//             ��Ϸ�������ж�ʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART4_NonBlockSendByte(u8 sd)
// {
//      M4_USART4->DR_f.TDR = sd;//д���ݵ����ͻ���
// }

// /***************************************************************************
// * �� �� ��: DRI_USART1_SendSTR
// * ����������USART1 ������ �����ַ�������
// * ��ڲ�����
//             u8 *strp���ַ����׵�ַ
// * ���ڲ�����
//             ��
// * ע������:  
//             �ַ���Ҫ����\0
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART1_SendSTR(u8 *strp)
// {
//      u32 u32count = 0;
//      while(strp[u32count] != '\0')
//      {
//           M4_USART1->DR_f.TDR = strp[u32count++];//д���ݵ����ͻ���
//           while((M4_USART1->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
//      }
// }

// /***************************************************************************
// * �� �� ��: DRI_USART2_SendSTR
// * ����������USART2 ������ �����ַ�������
// * ��ڲ�����
//             u8 *strp���ַ����׵�ַ
// * ���ڲ�����
//             ��
// * ע������:  
//             �ַ���Ҫ����\0
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART2_SendSTR(u8 *strp)
// {
//      u32 u32count = 0;
//      while(strp[u32count] != '\0')
//      {
//           M4_USART2->DR_f.TDR = strp[u32count++];//д���ݵ����ͻ���
//           while((M4_USART2->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
//      }
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_SendSTR
// * ����������USART3 ������ �����ַ�������
// * ��ڲ�����
//             u8 *strp���ַ����׵�ַ
// * ���ڲ�����
//             ��
// * ע������:  
//             �ַ���Ҫ����\0
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART3_SendSTR(u8 *strp)
// {
//      u32 u32count = 0;
//      while(strp[u32count] != '\0')
//      {
//           M4_USART3->DR_f.TDR = strp[u32count++];//д���ݵ����ͻ���
//           while((M4_USART3->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
//      }
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_SendSTR
// * ����������USART4 ������ �����ַ�������
// * ��ڲ�����
//             u8 *strp���ַ����׵�ַ
// * ���ڲ�����
//             ��
// * ע������:  
//             �ַ���Ҫ����\0
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART4_SendSTR(u8 *strp)
// {
//      u32 u32count = 0;
//      while(strp[u32count] != '\0')
//      {
//           M4_USART4->DR_f.TDR = strp[u32count++];//д���ݵ����ͻ���
//           while((M4_USART4->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
//      }
// }


// /***************************************************************************
// * �� �� ��: DRI_USART1_SendData
// * ����������USART1 ������ �������ݺ���
// * ��ڲ�����
//             u8 *sd���������������׵�ַ
//             u16 sl���������ֽ���
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART1_SendData(u8 *sd,u16 sl)
// {
//      u16 u16count = 0; 
//      while(u16count < sl)
//      {
//           M4_USART1->DR_f.TDR = sd[u16count++];//д���ݵ����ͻ���
//           while((M4_USART1->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
//      }
     
// }

// /***************************************************************************
// * �� �� ��: DRI_USART2_SendData
// * ����������USART2 ������ �������ݺ���
// * ��ڲ�����
//             u8 *sd���������������׵�ַ
//             u16 sl���������ֽ���
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART2_SendData(u8 *sd,u16 sl)
// {
//      u16 u16count = 0; 
//      while(u16count < sl)
//      {
//           M4_USART2->DR_f.TDR = sd[u16count++];//д���ݵ����ͻ���
//           while((M4_USART2->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
//      }
     
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_SendData
// * ����������USART3 ������ �������ݺ���
// * ��ڲ�����
//             u8 *sd���������������׵�ַ
//             u16 sl���������ֽ���
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART3_SendData(u8 *sd,u16 sl)
// {
//      u16 u16count = 0; 
//      while(u16count < sl)
//      {
//           M4_USART3->DR_f.TDR = sd[u16count++];//д���ݵ����ͻ���
//           while((M4_USART3->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
//      }
     
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_SendData
// * ����������USART4 ������ �������ݺ���
// * ��ڲ�����
//             u8 *sd���������������׵�ַ
//             u16 sl���������ֽ���
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-06 BY:YJX
// ***************************************************************************/
// void DRI_USART4_SendData(u8 *sd,u16 sl)
// {
//      u16 u16count = 0; 
//      while(u16count < sl)
//      {
//           M4_USART4->DR_f.TDR = sd[u16count++];//д���ݵ����ͻ���
//           while((M4_USART4->SR & UsartTxEmpty) == 0);//�ȴ��������(TXE��Ӳ����1��0)
//      }
     
// }

// /***************************************************************************
// * �� �� ��: DRI_USART1_EnableReceINT
// * ����������USART1 ʹ�ܽ����ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART1_EnableReceINT(void)
// {
//      M4_USART_TypeDef *Usartx = M4_USART1;
//      u16 u16temp = Usartx->DR_f.RDR;//���ԭ��������
//      u16temp = u16temp;
//      USART_ClearStatus(Usartx, UsartFrameErr);//���֡����
//      USART_ClearStatus(Usartx, UsartParityErr);//���У�����
//      USART_ClearStatus(Usartx, UsartOverrunErr);//��� 
//      USART_FuncCmd(Usartx, UsartRxInt, Enable);//ʹ�ܽ������ݺͽ��մ����ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART2_EnableReceINT
// * ����������USART2 ʹ�ܽ����ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART2_EnableReceINT(void)
// {
//      M4_USART_TypeDef *Usartx = M4_USART2;
//      u16 u16temp = Usartx->DR_f.RDR;//���ԭ��������
//      u16temp = u16temp;
//      USART_ClearStatus(Usartx, UsartFrameErr);//���֡����
//      USART_ClearStatus(Usartx, UsartParityErr);//���У�����
//      USART_ClearStatus(Usartx, UsartOverrunErr);//��� 
//      USART_FuncCmd(Usartx, UsartRxInt, Enable);//ʹ�ܽ������ݺͽ��մ����ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_EnableReceINT
// * ����������USART3 ʹ�ܽ����ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART3_EnableReceINT(void)
// {
//      M4_USART_TypeDef *Usartx = M4_USART3;
//      u16 u16temp = Usartx->DR_f.RDR;//���ԭ��������
//      u16temp = u16temp;
//      USART_ClearStatus(Usartx, UsartFrameErr);//���֡����
//      USART_ClearStatus(Usartx, UsartParityErr);//���У�����
//      USART_ClearStatus(Usartx, UsartOverrunErr);//��� 
//      USART_FuncCmd(Usartx, UsartRxInt, Enable);//ʹ�ܽ������ݺͽ��մ����ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_EnableReceINT
// * ����������USART4 ʹ�ܽ����ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART4_EnableReceINT(void)
// {
//      M4_USART_TypeDef *Usartx = M4_USART4;
//      u16 u16temp = Usartx->DR_f.RDR;//���ԭ��������
//      u16temp = u16temp;
//      USART_ClearStatus(Usartx, UsartFrameErr);//���֡����
//      USART_ClearStatus(Usartx, UsartParityErr);//���У�����
//      USART_ClearStatus(Usartx, UsartOverrunErr);//��� 
//      USART_FuncCmd(Usartx, UsartRxInt, Enable);//ʹ�ܽ������ݺͽ��մ����ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART1_DisableReceINT
// * ����������USART1 ��ֹ�����ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART1_DisableReceINT(void)
// {
//      USART_FuncCmd(M4_USART1, UsartRxInt, Disable);//��ֹ�������ݺͽ��մ����ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART2_DisableReceINT
// * ����������USART2 ��ֹ�����ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART2_DisableReceINT(void)
// {
//      USART_FuncCmd(M4_USART2, UsartRxInt, Disable);//��ֹ�������ݺͽ��մ����ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_DisableReceINT
// * ����������USART3 ��ֹ�����ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART3_DisableReceINT(void)
// {
//      USART_FuncCmd(M4_USART3, UsartRxInt, Disable);//��ֹ�������ݺͽ��մ����ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_DisableReceINT
// * ����������USART4 ��ֹ�����ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART4_DisableReceINT(void)
// {
//      USART_FuncCmd(M4_USART4, UsartRxInt, Disable);//��ֹ�������ݺͽ��մ����ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART1_EnableSendOKINT
// * ����������USART1 ʹ�ܷ�������ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART1_EnableSendOKINT(void)
// {
//      USART_FuncCmd(M4_USART1, UsartTxCmpltInt, Enable);//ʹ�ܷ�������ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART2_EnableSendOKINT
// * ����������USART2 ʹ�ܷ�������ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART2_EnableSendOKINT(void)
// {
//      USART_FuncCmd(M4_USART2, UsartTxCmpltInt, Enable);//ʹ�ܷ�������ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_EnableSendOKINT
// * ����������USART3 ʹ�ܷ�������ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART3_EnableSendOKINT(void)
// {
//      USART_FuncCmd(M4_USART3, UsartTxCmpltInt, Enable);//ʹ�ܷ�������ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_EnableSendOKINT
// * ����������USART4 ʹ�ܷ�������ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART4_EnableSendOKINT(void)
// {
//      USART_FuncCmd(M4_USART4, UsartTxCmpltInt, Enable);//ʹ�ܷ�������ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART1_DisableSendOKINT
// * ����������USART1 ��ֹ��������ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART1_DisableSendOKINT(void)
// {
//      USART_FuncCmd(M4_USART1, UsartTxCmpltInt, Disable);//��ֹ��������ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART2_DisableSendOKINT
// * ����������USART2 ��ֹ��������ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART2_DisableSendOKINT(void)
// {
//      USART_FuncCmd(M4_USART2, UsartTxCmpltInt, Disable);//��ֹ��������ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_DisableSendOKINT
// * ����������USART3 ��ֹ��������ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART3_DisableSendOKINT(void)
// {
//      USART_FuncCmd(M4_USART3, UsartTxCmpltInt, Disable);//��ֹ��������ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_DisableSendOKINT
// * ����������USART4 ��ֹ��������ж� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART4_DisableSendOKINT(void)
// {
//      USART_FuncCmd(M4_USART4, UsartTxCmpltInt, Disable);//��ֹ��������ж�
// }

// /***************************************************************************
// * �� �� ��: DRI_USART1_XON
// * ����������USART1 ������ ����������XON���� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART1_XON(void)
// {
//      DRI_USART1_SendByte(XON);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART2_XON
// * ����������USART2 ������ ����������XON���� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART2_XON(void)
// {
//      DRI_USART2_SendByte(XON);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_XON
// * ����������USART3 ������ ����������XON���� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART3_XON(void)
// {
//      DRI_USART3_SendByte(XON);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_XON
// * ����������USART4 ������ ����������XON���� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART4_XON(void)
// {
//      DRI_USART4_SendByte(XON);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART1_XOFF
// * ����������USART1 ������ ����������XOFF���� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART1_XOFF(void)
// {
//      DRI_USART1_SendByte(XOFF);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART2_XOFF
// * ����������USART2 ������ ����������XOFF���� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART2_XOFF(void)
// {
//      DRI_USART2_SendByte(XOFF);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_XOFF
// * ����������USART3 ������ ����������XOFF���� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART3_XOFF(void)
// {
//      DRI_USART3_SendByte(XOFF);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_XOFF
// * ����������USART4 ������ ����������XOFF���� ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
            
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART4_XOFF(void)
// {
//      DRI_USART4_SendByte(XOFF);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART1_HW_Flowcontrol_ON
// * ����������USART1 ���ƽ���Ӳ������� XON��ƽ ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
//             ����Ӳ��������ʱ��Ҫʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART1_HW_Flowcontrol_ON(void)
// {
//      USARTn_HW_Flowcontrol_ON(&RHWFC1);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART2_HW_Flowcontrol_ON
// * ����������USART2 ���ƽ���Ӳ������� XON��ƽ ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
//             ����Ӳ��������ʱ��Ҫʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART2_HW_Flowcontrol_ON(void)
// {
//      USARTn_HW_Flowcontrol_ON(&RHWFC2);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_HW_Flowcontrol_ON
// * ����������USART3 ���ƽ���Ӳ������� XON��ƽ ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
//             ����Ӳ��������ʱ��Ҫʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART3_HW_Flowcontrol_ON(void)
// {
//      USARTn_HW_Flowcontrol_ON(&RHWFC3);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_HW_Flowcontrol_ON
// * ����������USART4 ���ƽ���Ӳ������� XON��ƽ ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
//             ����Ӳ��������ʱ��Ҫʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART4_HW_Flowcontrol_ON(void)
// {
//      USARTn_HW_Flowcontrol_ON(&RHWFC4);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART1_HW_Flowcontrol_OFF
// * ����������USART1 ���ƽ���Ӳ������� XOFF��ƽ ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
//             ����Ӳ��������ʱ��Ҫʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART1_HW_Flowcontrol_OFF(void)
// {
//      USARTn_HW_Flowcontrol_OFF(&RHWFC1);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART2_HW_Flowcontrol_OFF
// * ����������USART2 ���ƽ���Ӳ������� XOFF��ƽ ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
//             ����Ӳ��������ʱ��Ҫʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART2_HW_Flowcontrol_OFF(void)
// {
//      USARTn_HW_Flowcontrol_OFF(&RHWFC2);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART3_HW_Flowcontrol_OFF
// * ����������USART3 ���ƽ���Ӳ������� XOFF��ƽ ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
//             ����Ӳ��������ʱ��Ҫʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART3_HW_Flowcontrol_OFF(void)
// {
//      USARTn_HW_Flowcontrol_OFF(&RHWFC3);
// }

// /***************************************************************************
// * �� �� ��: DRI_USART4_HW_Flowcontrol_OFF
// * ����������USART4 ���ƽ���Ӳ������� XOFF��ƽ ����
// * ��ڲ�����
//             ��
// * ���ڲ�����
//             ��
// * ע������:  
//             ����Ӳ��������ʱ��Ҫʹ��
// * ��     ��:
// * �޸ļ�¼ :
// *           2022-06-23 BY:YJX
// ***************************************************************************/
// void DRI_USART4_HW_Flowcontrol_OFF(void)
// {
//      USARTn_HW_Flowcontrol_OFF(&RHWFC4);
// }


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����ڲ�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
static s8 USARTn_Config(u32 usart_periph,DRI_USARTCnfType *cnfp)
{
     /* USART configure */
     usart_deinit(usart_periph);//�ر�USART
     //���ò�����
     usart_baudrate_set(usart_periph,cnfp->bps);//���ò�����
     //����У��λ
     if(cnfp->Parity == ParityNone)
     {
         usart_parity_config(usart_periph,USART_PM_NONE);//��У��
     }
     else if(cnfp->Parity == ParityOdd)
     {
         usart_parity_config(usart_periph,USART_PM_ODD);//��У��
     }
     else if(cnfp->Parity == ParityEven)
     {
         usart_parity_config(usart_periph,USART_PM_EVEN);//żУ��
     }
     else
     {
         return -1;
     }
     //��������λ
     if(cnfp->DataBit == DataBits8)
     {
         usart_word_length_set(usart_periph,USART_WL_8BIT);//8λ����λ
     }
     else if(cnfp->DataBit == DataBits9)
     {
         usart_word_length_set(usart_periph,USART_WL_9BIT);//9λ����λ
     }
     else
     {
         return -1;
     }
     //����ֹͣλ
     if(cnfp->StopBit == HalfStopBit)
     {
         usart_stop_bit_set(usart_periph,USART_STB_0_5BIT);//0.5λֹͣλ
     }
     else if(cnfp->StopBit == OneStopBit)
     {
         usart_stop_bit_set(usart_periph,USART_STB_1BIT);//1λֹͣλ
     }
     else if(cnfp->StopBit == OneAndHalfStopBit)
     {
         usart_stop_bit_set(usart_periph,USART_STB_1_5BIT);//1.5λֹͣλ
     }
     else if(cnfp->StopBit == TwoStopBit)
     {
         usart_stop_bit_set(usart_periph,USART_STB_2BIT);//2λֹͣλ
     }
     else
     {
         return -1;
     }
     //��������λ����˳��
     usart_data_first_config(usart_periph, USART_MSBF_LSB);//����λ��LSB��ʼ����
     //
     usart_receive_config(usart_periph, USART_RECEIVE_ENABLE);//���ý���ģ��
     usart_transmit_config(usart_periph, USART_TRANSMIT_ENABLE);//���÷���ģ��
     usart_enable(usart_periph);//ʹ��

     //---------------------------------- ���ý����ж� ----------------------------------
     if(cnfp->RecData_IntEnable)
     {//�����ж�ʹ��          
          switch(usart_periph)
          {
               case USART0:
                    ReceFunP0 = cnfp->Recfp;//���ý��ջص�����
                    break;
               default:
                    return -1;
          }
          usart_flag_clear(usart_periph, USART_FLAG_RBNE);
          usart_interrupt_enable(usart_periph, USART_INT_RBNE);
     }
     else
     {//�����жϽ�ֹ
          usart_interrupt_disable(usart_periph, USART_INT_RBNE);
          switch(usart_periph)
          {
               case USART0:
                    ReceFunP0 = (NULLFP1)NULLFP;
                    break;
               default:
                    return -1;
          }
     }

     //---------------------------------- ���ý��մ����ж� ----------------------------------
     usart_flag_clear(usart_periph, USART_FLAG_ORERR);//����������
     usart_flag_clear(usart_periph, USART_FLAG_NERR);//�����������
     usart_flag_clear(usart_periph, USART_FLAG_FERR);//���֡����
     usart_flag_clear(usart_periph, USART_FLAG_PERR);//���У����� 

     //---------------------------------- ���÷����ж� ----------------------------------
     if(cnfp->SendOK_IntEnable)
     {//��������ж�ʹ��
          switch(usart_periph)
          {
               case USART0:
                    SendOKFunP0 = cnfp->SendOKfp;//���÷�����ɻص�����
                    break;
               default:
                    return -1;
          }
          usart_flag_clear(usart_periph, USART_FLAG_TC);
          if(cnfp->SendINTDefaultState)
          {
               usart_interrupt_enable(usart_periph, USART_INT_TC);
          }
     }
     else
     {//��������жϽ�ֹ
          usart_interrupt_disable(usart_periph, USART_INT_TC);
          switch(usart_periph)
          {
               case USART0:
                    SendOKFunP0 = NULLFP;
                    break;
               default:
                    return -1;
          }
     }

     return 0;
}

// //Usart1����ص�������
// static void USART1_ErrIrqCallback(void)
// {
//      M4_USART_TypeDef *USARTx = M4_USART1;
//      if(USART_GetStatus(USARTx, UsartFrameErr))
//      {
//           USART_ClearStatus(USARTx, UsartFrameErr);
//      }

//      if(USART_GetStatus(USARTx, UsartParityErr))
//      {
//           USART_ClearStatus(USARTx, UsartParityErr);
//      }

//      if(USART_GetStatus(USARTx, UsartOverrunErr))
//      {
//           USART_ClearStatus(USARTx, UsartOverrunErr);
//      }
// }

// //Usart1���ݽ��ջص�������
// static void USART1_RxCallback(void)
// {
//      u16 u16rd = M4_USART1->DR_f.RDR;//USART_RecData(M4_USART1);//��ȡ�յ�������
//      //RXNE��Ӳ����1����ȡ���ݺ���Ӳ����0
//      ReceFunP1((u8)u16rd);     
// }

// //Usart1������ɻص�������
// static void USART1_TCxCallback(void)
// {
//      //�˴���־�Ĵ�����Ӳ��������λ�Ĵ������(�����¿�ʼ����ʱ��Ӳ�����Զ���0)
//      SendOKFunP1();
// }

// //Usart2����ص�������
// static void USART2_ErrIrqCallback(void)
// {
//      M4_USART_TypeDef *USARTx = M4_USART2;
//      if(USART_GetStatus(USARTx, UsartFrameErr))
//      {
//           USART_ClearStatus(USARTx, UsartFrameErr);
//      }

//      if(USART_GetStatus(USARTx, UsartParityErr))
//      {
//           USART_ClearStatus(USARTx, UsartParityErr);
//      }

//      if(USART_GetStatus(USARTx, UsartOverrunErr))
//      {
//           USART_ClearStatus(USARTx, UsartOverrunErr);
//      }
// }

// //Usart2���ݽ��ջص�������
// static void USART2_RxCallback(void)
// {
//      u16 u16rd = M4_USART2->DR_f.RDR;//USART_RecData(M4_USART2);//��ȡ�յ�������
//      //RXNE��Ӳ����1����ȡ���ݺ���Ӳ����0
//      ReceFunP2((u8)u16rd);     
// }

// //Usart2������ɻص�������
// static void USART2_TCxCallback(void)
// {
//      //�˴���־�Ĵ�����Ӳ��������λ�Ĵ������(�����¿�ʼ����ʱ��Ӳ�����Զ���0)
//      SendOKFunP2();
// }

// //Usart3����ص�������
// static void USART3_ErrIrqCallback(void)
// {
//      M4_USART_TypeDef *USARTx = M4_USART3;
//      if(USART_GetStatus(USARTx, UsartFrameErr))
//      {
//           USART_ClearStatus(USARTx, UsartFrameErr);
//      }

//      if(USART_GetStatus(USARTx, UsartParityErr))
//      {
//           USART_ClearStatus(USARTx, UsartParityErr);
//      }

//      if(USART_GetStatus(USARTx, UsartOverrunErr))
//      {
//           USART_ClearStatus(USARTx, UsartOverrunErr);
//      }
// }

// //Usart3���ݽ��ջص�������
// static void USART3_RxCallback(void)
// {
//      u16 u16rd = M4_USART3->DR_f.RDR;//USART_RecData(M4_USART3);//��ȡ�յ�������
//      //RXNE��Ӳ����1����ȡ���ݺ���Ӳ����0
//      ReceFunP3((u8)u16rd);     
// }

// //Usart3������ɻص�������
// static void USART3_TCxCallback(void)
// {
//      //�˴���־�Ĵ�����Ӳ��������λ�Ĵ������(�����¿�ʼ����ʱ��Ӳ�����Զ���0)
//      SendOKFunP3();
// }

// //Usart4����ص�������
// static void USART4_ErrIrqCallback(void)
// {
//      M4_USART_TypeDef *USARTx = M4_USART4;
//      if(USART_GetStatus(USARTx, UsartFrameErr))
//      {
//           USART_ClearStatus(USARTx, UsartFrameErr);
//      }

//      if(USART_GetStatus(USARTx, UsartParityErr))
//      {
//           USART_ClearStatus(USARTx, UsartParityErr);
//      }

//      if(USART_GetStatus(USARTx, UsartOverrunErr))
//      {
//           USART_ClearStatus(USARTx, UsartOverrunErr);
//      }
// }

// //Usart4���ݽ��ջص�������
// static void USART4_RxCallback(void)
// {
//      u16 u16rd = M4_USART4->DR_f.RDR;//USART_RecData(M4_USART4);//��ȡ�յ�������
//      //RXNE��Ӳ����1����ȡ���ݺ���Ӳ����0
//      ReceFunP4((u8)u16rd);     
// }

// //Usart4������ɻص�������
// static void USART4_TCxCallback(void)
// {
//      //�˴���־�Ĵ�����Ӳ��������λ�Ĵ������(�����¿�ʼ����ʱ��Ӳ�����Զ���0)
//      SendOKFunP4();
// }

// //����Ӳ�������XON
// static void USARTn_HW_Flowcontrol_ON(RHWFlowCrl *rhwfcp)
// {
//      if(rhwfcp->FEnable)
//      {
//           if(rhwfcp->RHWFlowXonLevel)
//           {
//                PORT_SetBits((en_port_t)(rhwfcp->RFlowcontrolp),(en_pin_t)((u16)1 << (rhwfcp->RFlowcontroln)));
//           }
//           else
//           {
//                PORT_ResetBits((en_port_t)(rhwfcp->RFlowcontrolp),(en_pin_t)((u16)1 << (rhwfcp->RFlowcontroln)));
//           }
//      }
// }

// //����Ӳ�������XOFF
// static void USARTn_HW_Flowcontrol_OFF(RHWFlowCrl *rhwfcp)
// {
//      if(rhwfcp->FEnable)
//      {
//           if(rhwfcp->RHWFlowXonLevel)
//           {
//                PORT_ResetBits((en_port_t)(rhwfcp->RFlowcontrolp),(en_pin_t)((u16)1 << (rhwfcp->RFlowcontroln)));
//           }
//           else
//           {
//                PORT_SetBits((en_port_t)(rhwfcp->RFlowcontrolp),(en_pin_t)((u16)1 << (rhwfcp->RFlowcontroln)));
//           }
//      }
// }


// //USART1��USART2�����ж�
// //����С��0ʧ�� ����0�ɹ�
// static s8 USARTn_12PinCheck(DRI_USARTCnfType *cnfp)
// {//�������ų�ͻ�ж�
//      u8 USART12[6][16] = {//USART1��USART2ģ��Group1������������
//                         //0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
//                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//PA
//                          {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},//PB
//                          {1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0},//PC
//                          {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},//PD
//                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//PE
//                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //PH
//                           };
//      if(USART12[cnfp->txp][cnfp->txn] && 
//         USART12[cnfp->rxp][cnfp->rxn])
//      {
//           return 0;
//      }
//      return -1;
// }

// //USART3��USART4�����ж�
// //����С��0ʧ�� ����0�ɹ�
// static s8 USARTn_34PinCheck(DRI_USARTCnfType *cnfp)
// {//�������ų�ͻ�ж�
//      u8 USART34[6][16] = {//USART3��USART4ģ��Group2������������
//                         //0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
//                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//PA
//                          {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},//PB
//                          {0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0},//PC
//                          {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},//PD
//                          {1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1},//PE
//                          {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0} //PH
//                           };
//      if(USART34[cnfp->txp][cnfp->txn] && 
//         USART34[cnfp->rxp][cnfp->rxn])
//      {
//           return 0;
//      }
//      return -1;
// }

// //USART���ú���
// //����С��0ʧ�� ����0�ɹ�
// static s8 USARTn_Config(DRI_USARTCnfType *cnfp,USARTnPara *usartp)
// {
//      stc_port_init_t pstcPortInit;
//      stc_irq_regi_conf_t stcIrqRegiCfg;
//      stc_usart_uart_init_t m_stcInitCfg;
//      u8 u8temp;                  

//      //Ӳ�������ų�ʼ��
//      if(cnfp->rhwfc.FEnable)
//      {
//           MEM_ZERO_STRUCT(pstcPortInit); 
//           pstcPortInit.enPinMode = Pin_Mode_Out;
//           pstcPortInit.enExInt = Disable;
//           pstcPortInit.enPullUp = Enable; 
//           if(PORT_Init((en_port_t)(cnfp->rhwfc.RFlowcontrolp),(en_pin_t)((u16)1 << (cnfp->rhwfc.RFlowcontroln)),&pstcPortInit))
//           {
//                return -2;
//           }
//           DRI_ComDriver_UserPin((cnfp->rhwfc.RFlowcontrolp),(cnfp->rhwfc.RFlowcontroln));
//           if(cnfp->rhwfc.RHWFlowDefaultLevel)
//           {//Ĭ�ϸߵ�ƽ
//                PORT_SetBits((en_port_t)(cnfp->rhwfc.RFlowcontrolp),(en_pin_t)((u16)1 << (cnfp->rhwfc.RFlowcontroln)));
//           }
//           else
//           {//Ĭ�ϵ͵�ƽ
//                PORT_ResetBits((en_port_t)(cnfp->rhwfc.RFlowcontrolp),(en_pin_t)((u16)1 << (cnfp->rhwfc.RFlowcontroln)));
//           }
//      }     
     
//      //ʹ������ʱ��
//      PWC_Fcg1PeriphClockCmd(usartp->u32Fcg1Periph, Enable);
//      //��ʼ��USART��IO
//      PORT_SetFunc((en_port_t)cnfp->rxp, (en_pin_t)(1 << cnfp->rxn), usartp->UsartRxFunc, Disable);
//      PORT_SetFunc((en_port_t)cnfp->txp, (en_pin_t)(1 << cnfp->txn), usartp->UsartTxFunc, Disable);
//      DRI_ComDriver_UserPin(cnfp->rxp,cnfp->rxn);
//      DRI_ComDriver_UserPin(cnfp->txp,cnfp->txn);
//      //��ʼ��USART
//      for(u8temp = 0;u8temp < 4;u8temp++)
//      {
//           MEM_ZERO_STRUCT(m_stcInitCfg);
//           m_stcInitCfg.enDataLength = (en_usart_data_len_t)cnfp->DataBit;//����λ
//           m_stcInitCfg.enStopBit = (en_usart_stop_bit_t)cnfp->StopBit;//ֹͣλ
//           m_stcInitCfg.enParity = (en_usart_parity_t)cnfp->Parity;//У�鷽ʽ
//           m_stcInitCfg.enClkMode = UsartIntClkCkNoOutput;//ѡ���ڲ�ʱ��Դ �� �����     
//           m_stcInitCfg.enDetectMode = UsartStartBitFallEdge;//��ʼλ���ģʽΪ�½���
//           m_stcInitCfg.enDirection = UsartDataLsbFirst;//��λ��ǰ
//           m_stcInitCfg.enSampleMode = UsartSampleBit8;//Usart������ʽ
//           //m_stcInitCfg.enHwFlow = UsartRtsEnable;//Ӳ���� 
//           m_stcInitCfg.enClkDiv = (en_usart_clk_div_t)u8temp;  
//           USART_DeInit(usartp->UsartCh);
//           if(USART_UART_Init(usartp->UsartCh, &m_stcInitCfg) != Ok)
//           {
//                return -3;
//           }    
//           //���ò�����
//           if(USART_SetBaudrate(usartp->UsartCh, cnfp->bps) == Ok)
//           {
//                break;
//           }
//      }
//      if(u8temp >= 4)
//      {//�������쳣
//           return -4;
//      }
    
//      //���ý��������ж� �� ���մ����ж�
//      if((cnfp->RecData_Pri < 16) && (cnfp->RecErr_Pri < 16))
//      {
//      //----���������ж�
//           //DRI_ComDriver_EnableINT_IER(cnfp->RecDataIntNum);
//           //DRI_ComDriver_IntSelReset(cnfp->RecDataIntNum);
//           DRI_ComDriver_UserInt(cnfp->RecDataIntNum);
          
//           stcIrqRegiCfg.enIRQn = cnfp->RecDataIntNum;//����rx�жϷ���0�жϺ�
//           stcIrqRegiCfg.pfnCallback = usartp->RIcbf;//���ջص�����
//           stcIrqRegiCfg.enIntSrc = usartp->UsartRiSrc;
//           enIrqRegistration(&stcIrqRegiCfg);
//           NVIC_SetPriority(stcIrqRegiCfg.enIRQn, cnfp->RecData_Pri);
//           NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
//           NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);
          
//      //----���մ����ж�
//           //DRI_ComDriver_EnableINT_IER(cnfp->RecErrIntNum);
//           //DRI_ComDriver_IntSelReset(cnfp->RecErrIntNum);
//           DRI_ComDriver_UserInt(cnfp->RecErrIntNum);
          
//           stcIrqRegiCfg.enIRQn = cnfp->RecErrIntNum;
//           stcIrqRegiCfg.pfnCallback = usartp->EIcbf;//���մ���ص�����
//           stcIrqRegiCfg.enIntSrc = usartp->UsartEiSrc;
//           enIrqRegistration(&stcIrqRegiCfg);
//           USART_ClearStatus(usartp->UsartCh, UsartFrameErr);//���֡����
//           USART_ClearStatus(usartp->UsartCh, UsartParityErr);//���У�����
//           USART_ClearStatus(usartp->UsartCh, UsartOverrunErr);//���          
//           NVIC_SetPriority(stcIrqRegiCfg.enIRQn, cnfp->RecErr_Pri);//�����ȼ��Ľ��մ�����
//           NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
//           NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);
          
//      //-----ʹ���ж�(���������ж� �� ���մ����ж� ʹ�õ���ͬһ���жϿ���ʹ��λ������ֲ�P683)
//           USART_FuncCmd(usartp->UsartCh, UsartRxInt, Enable);//ʹ�ܽ������ݺͽ��մ����ж�
//      }


//      //���÷����ж�
//      if(cnfp->SendOK_Pri < 16)
//      {
//           //DRI_ComDriver_EnableINT_IER(cnfp->SendOKIntNum);
//           //DRI_ComDriver_IntSelReset(cnfp->SendOKIntNum);
//           DRI_ComDriver_UserInt(cnfp->SendOKIntNum);
          
//           stcIrqRegiCfg.enIRQn = cnfp->SendOKIntNum;
//           stcIrqRegiCfg.pfnCallback = usartp->TCIcbf;//��������жϻص�����
//           stcIrqRegiCfg.enIntSrc = usartp->UsartTCiSrc;
//           enIrqRegistration(&stcIrqRegiCfg);
//           USART_ClearStatus(usartp->UsartCh, UsartTxComplete);//���������ɱ�־
//           NVIC_SetPriority(stcIrqRegiCfg.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
//           NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
//           NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);
//           if(cnfp->SendINTDefaultState)
//           {
//                USART_FuncCmd(usartp->UsartCh, UsartTxCmpltInt, Enable);//ʹ�ܷ�������ж�
//           }
//      }
     
//      //ʹ�ܷ���ģ�鹦��     
//      USART_FuncCmd(usartp->UsartCh, UsartTx, Enable);//ʹ�ܷ���ģ��
//      //ʹ�ܽ���ģ��
//      USART_FuncCmd(usartp->UsartCh, UsartRx, Enable);//ʹ�ܽ���ģ�� 
    
//      return 0;
// }








