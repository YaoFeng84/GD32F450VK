/********************************************************************************************************************************************
*                                                                                                                                           *
*              ---------------------------------������ģ����޸ļ�¼��-----------------------------------------                             *
*                                                                                                                                           *
********************************************************************************************************************************************/
/**********************************************
 * ���ݣ�
 * ���ڣ�2025-09-05
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

#include "DRI_USB.h"
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------����ģ��ĶԽӺ�����-----------------------------------------                                  *
*                                                                                                                                           *
********************************************************************************************************************************************/
#define DEV_IN_EP                            0x81u
#define DEV_OUT_EP                           0x01u
#define DEV_INTIN_EP                         0x83u
#define DEV_MAX_PACKET                       64u
#define DEV_EP0_SIZE                         (DEV_MAX_PACKET)
#define DEV_EPIN_SIZE                        (DEV_MAX_PACKET)
#define DEV_EPOUT_SIZE                       (DEV_MAX_PACKET)
#define DEV_EPINTIN_SIZE                     (DEV_MAX_PACKET)

#define USB_TestFlags                       0//1:��ʾ�������� 0:��ʾ�رղ��ԡ�0x00u
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����ڲ�����������------------------------------------                           *
*                                                                                                                                           *
********************************************************************************************************************************************/
static u8 class_init(usb_dev *udev, u8 config_index);
static u8 class_deinit(usb_dev *udev, u8 config_index);
static u8 class_req_proc(usb_dev *udev, usb_req *req);
static u8 class_set_interface(usb_dev *udev, usb_req *req);                          /*!< device set interface callback */
static u8 class_ctlx_in(usb_dev *udev);                                         /*!< device control IN callback */
static u8 class_ctlx_out(usb_dev *udev);                                        /*!< device control OUT callback */
static u8 class_data_in(usb_dev *udev, u8 ep_num);
static u8 class_data_out(usb_dev *udev, u8 ep_num);
static u8 class_sof(usb_dev *udev);                                             /*!< start of frame handler */
static u8 class_incomplete_isoc_in(usb_dev *udev);                              /*!< incomplete synchronization IN transfer handler */
static u8 class_incomplete_isoc_out(usb_dev *udev);                             /*!< incomplete synchronization OUT transfer handler */

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ��ı��������ͺ궨����--------------------------------                      *
*                                                                                                                                           *
********************************************************************************************************************************************/

static DRI_USB_P0SetupProcessFunc P0SetupProcess;
static DRI_USB_ReceDataFunc ReceDataFunc;
static DRI_USB_P0OutProcessFunc P0OutProcess;
// static u8 UsbRxBuffer[PRT_EPOUT_SIZE];//���ջ���
static u8 StopRece = 0;//0��ʾ������� ��0��ʾֹͣ����
static s8 SendFlag = 1;//0��ʾ���Ϳ��� ��0��ʾ����æ
static s8 SendIntFlag = 1;//0��ʾ���Ϳ��� ��0��ʾ����æ

#define UsbEnumDataSendBufferMaxSize 256
static u8 UsbEnumDataSendBuffer[UsbEnumDataSendBufferMaxSize];//USBö��ʱ���ݵķ��ͻ���ר��
static u16 UsbEP0OUTDataLen = 0;//USB��EP0OUT������Ч�ֽ���
// //���豸��������Ϣ����ȡ
// static u8 MFGStrIndex = 0,MDLStrIndex = 0,SIDStrIndex = 0;//���̡��ͺ�(��Ʒ)�����к� ��ö��������
// //��������������Ϣ����ȡ
// static u8 CNFStrIndex = 0,INFStrIndex = 0;//�����ַ����ӿ��ַ� ��ö��������
// //
// static u8 StrNumber = 0;//ö��ʱ�ַ�����Ϣ�ĸ���
// //
// static u8 dev_prt_altset = 0u;

static const usb_desc_ep EP_IN_Data = 
{
     .header.bLength = 0x07,    ///�������γ��ȣ���λ�ֽ�
     .header.bDescriptorType = 0x05,    ///����������: �˵�������
     .bEndpointAddress = DEV_IN_EP,    ///�˵㷽��Ͷ˵��: ���λΪ����(�����Ƕ�)(1:IN���򣬼��豸������  0:OUT���򣬼��������豸)  ��4λΪ�˵��(������ֵ:IN����,�˵�1)
     .bmAttributes = 0x02,    ///����: ��������: ��������    0:Ϊ���ƴ�������  1:Ϊͬ����������  2:Ϊ������������  3:Ϊ�жϴ�������
     .wMaxPacketSize = DEV_EPIN_SIZE,    ///������С
     .bInterval = 0x00    ///������: 0��ʾû�м��
};

static const usb_desc_ep EP_OUT_Data = 
{
     .header.bLength = 0x07,    ///�������γ��ȣ���λ�ֽ�
     .header.bDescriptorType = 0x05,    ///����������: �˵�������
     .bEndpointAddress = DEV_OUT_EP,    ///�˵㷽��Ͷ˵��: ���λΪ����(�����Ƕ�)(1:IN���򣬼��豸������  0:OUT���򣬼��������豸)  ��4λΪ�˵��(������ֵ:IN����,�˵�1)
     .bmAttributes = 0x02,    ///����: ��������: ��������    0:Ϊ���ƴ�������  1:Ϊͬ����������  2:Ϊ������������  3:Ϊ�жϴ�������
     .wMaxPacketSize = DEV_EPOUT_SIZE,    ///������С
     .bInterval = 0x00    ///������: 0��ʾû�м��
};

static const usb_desc_ep EP_INT_Data = 
{
     .header.bLength = 0x07,    ///�������γ��ȣ���λ�ֽ�
     .header.bDescriptorType = 0x05,    ///����������: �˵�������
     .bEndpointAddress = DEV_INTIN_EP,    ///�˵㷽��Ͷ˵��: ���λΪ����(�����Ƕ�)(1:IN���򣬼��豸������  0:OUT���򣬼��������豸)  ��4λΪ�˵��(������ֵ:IN����,�˵�1)
     .bmAttributes = 0x03,    ///����: ��������: ��������    0:Ϊ���ƴ�������  1:Ϊͬ����������  2:Ϊ������������  3:Ϊ�жϴ�������
     .wMaxPacketSize = DEV_EPINTIN_SIZE,    ///������С
     .bInterval = 0xff    ///������:
};

static usb_core_driver usb_device;
static u8 usb_recedata_buf[DEV_MAX_PACKET];

static const usb_desc usbd_desc_cb = 
{//��������
     .dev_desc    = (u8 *)0,
     .config_desc = (u8 *)0,
     .bos_desc    = (u8 *)0,
     .strings     = 0
};

static usb_class_core usbd_class_cb = 
{//��ص�����
     .command            = 0xFFU,
     .alter_set          = 0U,
     //
     .init               = class_init,
     .deinit             = class_deinit,
     .req_proc           = class_req_proc,
     .set_intf           = class_set_interface,
     .ctlx_in            = class_ctlx_in,
     .ctlx_out           = class_ctlx_out,
     .data_in            = class_data_in,
     .data_out           = class_data_out,
     .SOF                = class_sof,
     .incomplete_isoc_in = class_incomplete_isoc_in,
     .incomplete_isoc_out= class_incomplete_isoc_out
};

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ���ϵͳ����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* �� �� ��: DRI_USB_Config
* ����������USB���ú���
* ��ڲ�����
            DRI_USBCnfType *cnfp:USB�ӿ����ò����ṹ��ָ��
* ���ڲ�����
            -1:��ʾ����ʧ��
            0:��ʾ���óɹ�
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
          
*           2025-09-05 BY:YJX
***************************************************************************/
s8 DRI_USB_Config(DRI_USBCnfType *cnfp)
{//�˴�Ҫ����ȷ����Ƶ�Ƿ�Ϊ168MHz��������25MHz���ⲿ�����£�USB��Ҫ��48MHzʱ���޷���ȷ����
     //if(rcu_clock_freq_get(CK_AHB) != 168000000)
     //{
     //     return -1;
     //}
//-------------- GPIO -------------------------
     //rcu_periph_clock_enable(RCU_SYSCFG);
     rcu_periph_clock_enable(RCU_GPIOA);
     /* USBFS_DM(PA11) and USBFS_DP(PA12) GPIO pin configuration */
     gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11 | GPIO_PIN_12);
     gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_11 | GPIO_PIN_12);
     gpio_af_set(GPIOA, GPIO_AF_10, GPIO_PIN_11 | GPIO_PIN_12);

//----------------- ʱ�� ------------------------------    
     rcu_pll48m_clock_config(RCU_PLL48MSRC_PLLQ);
     rcu_ck48m_clock_config(RCU_CK48MSRC_PLL48M);
     rcu_periph_clock_enable(RCU_USBFS);

//---------------- ��ʼ�� ----------------------
     P0SetupProcess = cnfp->P0SetupProcess;
     ReceDataFunc = cnfp->ReceDataFunc;
     P0OutProcess = cnfp->P0OutProcess;

     usbd_disconnect(&usb_device);

     usbd_init(&usb_device,USB_CORE_ENUM_FS,(usb_desc *)&usbd_desc_cb,(usb_class_core *)&usbd_class_cb);	

//--------------- �ж� ----------------------------
     //nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x00U);
     //nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
     //nvic_irq_enable((uint8_t)USBFS_IRQn, 2U, 0U);
     //
     NVIC_SetPriority(USBFS_IRQn, cnfp->IntPri);//�����ж����ȼ�
     NVIC_ClearPendingIRQ(USBFS_IRQn);//����жϱ�־
     NVIC_EnableIRQ(USBFS_IRQn);//ʹ���ж�

     usbd_connect(&usb_device);

     return 0;
}

//----------------------------------------------------------------------------------------
void usb_udelay(const u32 usec)
{
    u32 un = usec;
    do{
          DRI_ComDriver_Delay1us();
     }while(--un);
}

void usb_mdelay(const u32 msec)
{
    u32 mn = msec;
    do{
          DRI_ComDriver_Delay1ms();
     }while(--mn);
}
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����û�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* �� �� ��: DRI_USB_Disconnect
* ����������USB��Ͽ�����
* ��ڲ�����
            
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
          
*           2025-09-05 BY:YJX
***************************************************************************/
void DRI_USB_Disconnect(void)
{
     usbd_disconnect(&usb_device);
}

/***************************************************************************
* �� �� ��: DRI_USB_Connect
* ����������USB����뺯��
* ��ڲ�����
            
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
          
*           2025-09-05 BY:YJX
***************************************************************************/
void DRI_USB_Connect(void)
{
     usbd_connect(&usb_device);
}

/***************************************************************************
* �� �� ��: DRI_USB_ReConnect
* ���������������� USB�ذβ庯��
* ��ڲ�����
            ��
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
          
*           2025-09-05 BY:YJX
***************************************************************************/
void DRI_USB_ReConnect(void)
{//������״̬�£��˲������������⣬���Ų飡����
     usbd_disconnect(&usb_device);
     usb_mdelay(300);
     usbd_connect(&usb_device);
}

/***************************************************************************
* �� �� ��: DRI_USB_EnableReceive
* ����������ʹ�ܽ��պ���
* ��ڲ�����
            ��
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-09-05 BY:YJX
***************************************************************************/
void DRI_USB_EnableReceive(void)
{
     if(StopRece)
     {
          StopRece = 0; 
          //hd_usb_devepstatusset(&usb_dev,PRT_OUT_EP,USB_EP_RX_VALID);
          //printf("E\r\n");
          usbd_ep_recev(&usb_device, DEV_OUT_EP, usb_recedata_buf, DEV_EPOUT_SIZE);
     }     
}

/***************************************************************************
* �� �� ��: DRI_USB_DisableReceive
* ������������ֹ���պ���
* ��ڲ�����
            ��
* ���ڲ�����
            ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼ :
*           2025-09-05 BY:YJX
***************************************************************************/
void DRI_USB_DisableReceive(void)
{
     StopRece = 1;
     //printf("D\r\n");
     //hd_usb_devepstatusset(&usb_dev,PRT_OUT_EP,USB_EP_RX_NAK);
}

/***************************************************************************
* �� �� ��: DRI_USB_SendDataNonZPL
* ���������������ͷ�������(��ZPL����) ����
* ��ڲ�����
            u8 *sd:���������׵�ַ
            u16 sl:�����ֽ���
* ���ڲ�����
            ����ֵ:С��0:����ʧ��
                  ����ֵ:�ѷ����ֽ���
* ע������:  
            ��֧���ڽ��ջص��з�������!!!
* ��     ��:
* �޸ļ�¼ :

*           2025-09-05 BY:YJX
***************************************************************************/
s32 DRI_USB_SendDataZPL(u8 *sd,u16 sl)
{
     u32 u32count,u32time = 20000000;

     SendFlag = 1;
     usbd_ep_send(&usb_device,DEV_IN_EP,sd,sl); 

     if(((sl % DEV_EPIN_SIZE) == 0) && sl)
     {//��������ʱ
          u32count = 0;
          while((u32count++ < u32time) && (SendFlag));//�ȴ��������

          SendFlag = 1;
          usbd_ep_send(&usb_device,DEV_IN_EP,NULL,0);//���ӷ���һ��0�ֽڵĲ���             
     }

     u32count = 0;
     while((u32count++ < u32time) && (SendFlag));//�ȴ��������
     
     return sl;
}

/***************************************************************************
* �� �� ��: DRI_USB_SendData
* ���������������ͷ������� ����
* ��ڲ�����
            u8 *sd:���������׵�ַ
            u16 sl:�����ֽ���
* ���ڲ�����
            ����ֵ:С��0:����ʧ��
                  ����ֵ:�ѷ����ֽ���
* ע������:  
            ��֧���ڽ��ջص��з�������!!!
            ��������ZPL��������slΪ�˵���������������ʱ���ᷢ�Ͳ��ɹ�������
            ��Ҫ�ϲ��������ٴε��ñ���������ZPL����(ZPL������slΪ0)
            ��1����CDC�ࡢPrint�࣬��slΪ�˵���������������ʱ����Ҫ���ӵ��ñ�����������ZPL��������Ȼ��������ʱ���ᷢ�Ͳ��ɹ���������������ʱ������ZPL����
            ��2����Storage������ZPL��������Ȼ���쳣�ģ���
* ��     ��:
* �޸ļ�¼ :

*           2025-09-05 BY:YJX
***************************************************************************/
s32 DRI_USB_SendData(u8 *sd,u16 sl)
{
     u32 u32count,u32time = 20000000;

     SendFlag = 1;
     usbd_ep_send(&usb_device,DEV_IN_EP,sd,sl); 

     u32count = 0;
     while((u32count++ < u32time) && (SendFlag));//�ȴ��������
     
     return sl;
}

// {
//      u32 u32count,u32time = 20000000;

//      if(SendFlag)
//      {//δ�������
//           return -1;
//      }    

//      if(sl)
//      {
//           SendFlag = 1;
//           if((sl % DEV_EPIN_SIZE) == 0)
//           {
//                usbd_ep_send(&usb_device,DEV_IN_EP,sd,sl - 1);

//                u32count = 0;
//                while((u32count++ < u32time) && (SendFlag));//�ȴ��������
//                if(SendFlag)
//                {
//                     return sl - 1;
//                }

//                SendFlag = 1;
//                usbd_ep_send(&usb_device,DEV_IN_EP,&(sd[sl - 1]),1);
//           }
//           else
//           {
//                usbd_ep_send(&usb_device,DEV_IN_EP,sd,sl);
//           }

//           u32count = 0;
//           while((u32count++ < u32time) && (SendFlag));//�ȴ��������
//      }
     
//      return sl;
// }

// {
//      // u32 u32temp;
//      // u32 u32count,u32time = 20000000;
     
//      // if(SendFlag)
//      // {//δ�������
//      //      return -1;
//      // }

//      SendFlag = 1;
//      usbd_ep_send(&usb_device,DEV_IN_EP,sd,sl);   
//      if((sl % DEV_EPIN_SIZE == 0) && (sl > 0))
//      {
//           while(SendFlag);
//           SendFlag = 1;
//           usbd_ep_send(&usb_device,DEV_IN_EP,NULL,0); 
//      }       
//      // u32count = 0;
//      // while((u32count++ < u32time) && (SendFlag));//�ȴ��������
//      while(SendFlag);
//      return sl;

//      // u32 u32temp;
//      // u32 u32sendnum,u32count,u32time = 20000000;
     
//      // if(SendFlag)
//      // {//δ�������
//      //      return -1;
//      // }
//      // u32sendnum = 0;//�ѷ����ֽ���
//      // while(sl)
//      // {
//      //      SendFlag = 1;
//      //      u32temp = sl;
//      //      // if((u32temp % DEV_EPIN_SIZE) == 0)
//      //      // {
//      //      //      u32temp--;
//      //      // }
//      //      usbd_ep_send(&usb_device,DEV_IN_EP,&(sd[u32sendnum]),u32temp);
          
//      //      u32count = 0;
//      //      while((u32count++ < u32time) && (SendFlag));//�ȴ��������

//      //      if(SendFlag)
//      //      {//���ͳ�ʱ
//      //           SendFlag = 0;  
//      //           printf("���ͳ�ʱ\r\n");
//      //           return u32sendnum;
//      //      }
                   
//      //      u32sendnum += u32temp;
//      //      sl -= u32temp;
//      // }
//      // return (s32)u32sendnum;
// }









// {
//      u32 u32temp;
//      u32 u32sendnum,u32count,u32time = 1000000000;
     
//      if(SendFlag)
//      {//δ�������
//           return -1;
//      }

//      u32sendnum = 0;//�ѷ����ֽ���
//      while(sl)
//      {
//           SendFlag = 1;
//           u32temp = sl;
//           // if((u32temp % DEV_EPIN_SIZE) == 0)
//           // {
//           //      u32temp--;
//           // }
//           usbd_ep_send(&usb_device,DEV_IN_EP,&(sd[u32sendnum]),u32temp);
          
//           u32count = 0;
//           while((u32count++ < u32time) && (SendFlag));//�ȴ��������

//           if(SendFlag)
//           {//���ͳ�ʱ
//                SendFlag = 0;  
//                //printf("���ͳ�ʱ\r\n");
//                return u32sendnum;
//           }
                   
//           u32sendnum += u32temp;
//           sl -= u32temp;
//      }
//      return (s32)u32sendnum;
// }


/***************************************************************************
* �� �� ��: DRI_USB_NonBlockSendData
* ������������������������������ ����
* ��ڲ�����
            u8 *sd:���������׵�ַ
            u8 sl:�����ֽ���
* ���ڲ�����
            С��0:����æ �� ʧ��
           ����ֵ:���������͵��ֽ���
* ע������:  
            ��֧���ڽ��ջص��з�������!!!
            ��������ZPL��������slΪ�˵���������������ʱ���ᷢ�Ͳ��ɹ�������
            ��Ҫ�ϲ��������ٴε��ñ���������ZPL����(ZPL������slΪ0)
            ��1����CDC�ࡢPrint�࣬��slΪ�˵���������������ʱ����Ҫ���ӵ��ñ�����������ZPL��������Ȼ��������ʱ���ᷢ�Ͳ��ɹ���������������ʱ������ZPL����
            ��2����Storage������ZPL��������Ȼ���쳣�ģ���

            �����DRI_USB_CheckNonBlockSendState�������ж��Ƿ������
* ��     ��:
* �޸ļ�¼:
* ����        �汾        ����         ˵��
*           2025-09-05 BY:YJX
***************************************************************************/
s32 DRI_USB_NonBlockSendData(u8 *sd,u16 sl)
{
     if(SendFlag)
     {//δ�������
          return -1;
     }    

     SendFlag = 1;
     usbd_ep_send(&usb_device,DEV_IN_EP,sd,sl); 
     
     return sl;
}
// {
//      if(SendFlag)
//      {
//           return -1;
//      }

//      if(sl)
//      {
//           SendFlag = 1;
//           if((sl % DEV_EPIN_SIZE) == 0)
//           {
//                usbd_ep_send(&usb_device,DEV_IN_EP,sd,sl - 1);
//                return sl - 1;
//           }
//           else
//           {
//                usbd_ep_send(&usb_device,DEV_IN_EP,sd,sl);
//                return sl;
//           }
//      }     
//      return 0;
// }
// {
//      if(SendFlag)
//      {
//           return -1;
//      }

//      if(sl)
//      {
//           SendFlag = 1;          
//           usbd_ep_send(&usb_device,DEV_IN_EP,sd,sl);
//      }
//      return (s32)sl;
// }

/***************************************************************************
* �� �� ��: DRI_USB_CheckNonBlockSendState
* �����������жϷ������ͷ���״̬ ����
* ��ڲ�����
            ��
* ���ڲ�����
            0���������
          ��0������δ���
* ע������:  
            
* ��     ��:
* �޸ļ�¼ :
*           2025-09-05 BY:YJX
***************************************************************************/
s8 DRI_USB_CheckNonBlockSendState(void)
{
     if(SendFlag)
     {
          return -1;
     }
     return 0;
}

/***************************************************************************
* �� �� ��: DRI_USB_SendData_INT
* ���������������ͷ���INT���� ����
* ��ڲ�����
            u8 *sd:���������׵�ַ
            u16 sl:�����ֽ���
* ���ڲ�����
            ����ֵ:С��0:����ʧ��
                  ����ֵ:�ѷ����ֽ���
* ע������:  
            ��֧���ڽ��ջص��з�������!!!
* ��     ��:
* �޸ļ�¼ :
*           2025-09-05 BY:YJX
***************************************************************************/
s32 DRI_USB_SendData_INT(u8 *sd,u16 sl)
{     
     return -2;//ĿǰINT���ݷ���ʱ�Ῠס����ʱ�ر�
}

/***************************************************************************
* �� �� ��: DRI_USB_NonBlockSendData_INT
* ��������������������������INT���� ����
* ��ڲ�����
            u8 *sd:���������׵�ַ
            u8 sl:�����ֽ���
* ���ڲ�����
            С��0:����æ �� ʧ��
           ����ֵ:���������͵��ֽ���
* ע������:  
            ��֧���ڽ��ջص��з�������!!!
            �����DRI_USB_CheckNonBlockSendINTState�������ж��Ƿ������
* ��     ��:
* �޸ļ�¼:
*           2025-09-05 BY:YJX
***************************************************************************/
s32 DRI_USB_NonBlockSendData_INT(u8 *sd,u16 sl)
{
     return -2;//ĿǰINT���ݷ���ʱ�Ῠס����ʱ�ر�
}

/***************************************************************************
* �� �� ��: DRI_USB_CheckNonBlockSendINTState
* �����������жϷ������ͷ���INT״̬ ����
* ��ڲ�����
            ��
* ���ڲ�����
            0���������
          ��0������δ���
* ע������:  
            
* ��     ��:
* �޸ļ�¼ : 
*           2025-09-05 BY:YJX
***************************************************************************/
s8 DRI_USB_CheckNonBlockSendINTState(void)
{
     if(SendIntFlag)
     {
          return -1;
     }
     return 0;
}

/***************************************************************************
* �� �� ��: DRI_USB_OutEndPointInfo
* ��������������˵���Ϣ ����
* ��ڲ�����
            DRI_USB_EPType *ep:��Ŷ˵���Ϣ�Ľṹ��ָ��
* ���ڲ�����
            ��
* ע������:  
            
* ��     ��:
* �޸ļ�¼ :
*           2025-09-05 BY:YJX
***************************************************************************/
void DRI_USB_OutEndPointInfo(DRI_USB_EPType *ep)
{
     
     ep->InEP_Num = (EP_IN_Data.bEndpointAddress & 0x7F);
     ep->InEP_Type = EP_IN_Data.bmAttributes;
     ep->InEP_MaxPacketSize = EP_IN_Data.wMaxPacketSize;
     //
     ep->OutEP_Num = (EP_OUT_Data.bEndpointAddress & 0x7F);
     ep->OutEP_Type = EP_OUT_Data.bmAttributes;
     ep->OutEP_MaxPacketSize = EP_OUT_Data.wMaxPacketSize;
     //
     ep->IntInEP_Num = (EP_INT_Data.bEndpointAddress & 0x7F);
     ep->IntInEP_Type = EP_INT_Data.bmAttributes;
     ep->IntInEP_MaxPacketSize = EP_INT_Data.wMaxPacketSize;
     //
     ep->P0EP_MaxPacketSize = DEV_EP0_SIZE;
}

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����ڲ�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
#if USB_TestFlags == 0
void USBFS_IRQHandler(void)
{
    usbd_isr (&usb_device);
}
#endif
//----------------------------------------------------------------------------------------
//��ȡ���豸������������
//���ء��豸������������ָ�룬u16 *lenΪ���ء��豸�������������ֽ���
u8 *DRI_USB_dev_desc_get(usb_core_driver *udev, u8 index, u16 *len)
{
#if USB_TestFlags != 0
     (void)index;
     *len = udev->dev.desc->dev_desc[0];
     return udev->dev.desc->dev_desc;
#else
     s8 s8temp;
     u16 u16temp;
     //�˴�����һ�������豸�������ı�׼����
     u8 UsbCmd[] = {0x80,//����ΪIN����׼����
                    0x06,//��ȡ����������
                    0x00,0x01,//wValue-->�豸������
                    0x00,0x00,//wIndex
                    0xff,0xff};//wLength
     //printf("�豸������:\r\n");
     *len = 0;
     u16temp = UsbEnumDataSendBufferMaxSize;
     s8temp = P0SetupProcess(UsbCmd,sizeof(UsbCmd),UsbEnumDataSendBuffer,&u16temp);     
     //printf("u16temp = %d\r\n",u16temp);
     if(s8temp == 1)
     {//�д����͵�����
          *len = u16temp;    
     }
     return UsbEnumDataSendBuffer;
#endif
}

//��ȡ������������������
//���ء�����������������ָ�룬u16 *lenΪ���ء������������������ֽ���
u8 *DRI_USB_config_desc_get(usb_core_driver *udev, u8 index, u16 *len)
{
#if USB_TestFlags != 0     
     (void)index;
     *len = udev->dev.desc->config_desc[2] | (udev->dev.desc->config_desc[3] << 8);
     return udev->dev.desc->config_desc;
#else
     s8 s8temp;
     u16 u16temp;
     //�˴�����һ�������豸�������ı�׼����
     u8 UsbCmd[] = {0x80,//����ΪIN����׼����
                    0x06,//��ȡ����������
                    0x00,0x02,//wValue-->����������
                    0x00,0x00,//wIndex
                    0xff,0xff};//wLength
     *len = 0;
     //printf("configstr:\r\n");
     u16temp = UsbEnumDataSendBufferMaxSize;
     s8temp = P0SetupProcess(UsbCmd,sizeof(UsbCmd),UsbEnumDataSendBuffer,&u16temp);     
     if(s8temp == 1)
     {//�д����͵�����
          //�˴����������ַ�����������������Ϣ  
          *len = u16temp;  
     }
     return UsbEnumDataSendBuffer;
#endif     
}

//��ȡ���ַ���������
//���ء��ַ���������ָ�룬u8 indexΪ�ַ��������� u16 *lenΪ���ء��ַ����������ֽ���
u8 *DRI_USB_str_desc_get(usb_core_driver *udev, u8 index, u16 *len)
{
#if USB_TestFlags != 0
     u8 *desc = udev->dev.desc->strings[index];
     *len = desc[0];
     return desc;
#else
     s8 s8temp;
     u16 u16temp;
     //�˴�����һ�������豸�������ı�׼����
     u8 UsbCmd[] = {0x80,//����ΪIN����׼����
                    0x06,//��ȡ����������
                    index,0x03,//wValue-->0x00���Ա���,0x03�ַ���������
                    0x00,0x00,//wIndex
                    0x04,0x00};//wLength
     if(index)
     {
          UsbCmd[6] = 0xff;
          UsbCmd[7] = 0xff;
     }
     *len = 0;
     //printf("langiddesc:\r\n");
     u16temp = UsbEnumDataSendBufferMaxSize;
     s8temp = P0SetupProcess(UsbCmd,sizeof(UsbCmd),UsbEnumDataSendBuffer,&u16temp);     
     if(s8temp == 1)
     {//�д����͵�����
          //�˴����������ַ��������������Ա���          
          *len = u16temp; 
     }
     return UsbEnumDataSendBuffer;
#endif     
}

#if defined(USE_USB_HS) && defined(USE_ULPI_PHY)
u8 *DRI_USB_other_speed_config_desc_get(usb_core_driver *udev, u8 index, u16 *len)
{
#if USB_TestFlags != 0
     (void)index;
     *len = udev->dev.desc->other_speed_config_desc[2];
     return udev->dev.desc->other_speed_config_desc;
#else     
     *len = 0;
     return (u8*)0;
#endif     
}

u8 *DRI_USB_qualifier_desc_get(usb_core_driver *udev, u8 index, u16 *len)
{
#if USB_TestFlags != 0     
     (void)index;
     *len = udev->dev.desc->qualifier_desc[0];
     return udev->dev.desc->qualifier_desc;
#else     
     *len = 0;
     return (u8*)0;
#endif     
}
#endif

u8 *DRI_USB_bos_desc_get(usb_core_driver *udev, u8 index, u16 *len)
{
#if USB_TestFlags != 0
     (void)index;
     *len = udev->dev.desc->bos_desc[2];
     return udev->dev.desc->bos_desc;
#else
     *len = 0;
     return (u8*)0;
#endif
}


//-----------------------------------------------------------------------------------
static u8 class_init(usb_dev *udev, u8 config_index)
{
     /* initialize the EPIN endpoint */
     usbd_ep_setup(udev, &EP_IN_Data);
     /* initialize the EPOUT endpoint */
     usbd_ep_setup(udev, &EP_OUT_Data);
     /* initialize the EPINT endpoint */
     usbd_ep_setup(udev, &EP_INT_Data);

     /* flush the FIFO */
     usbd_fifo_flush(udev, DEV_OUT_EP);
     usbd_fifo_flush(udev, DEV_IN_EP);
     usbd_fifo_flush(udev, DEV_INTIN_EP);


     /* prepare to receive data */
     usbd_ep_recev(udev, DEV_OUT_EP, usb_recedata_buf, DEV_EPOUT_SIZE);

     SendFlag = 0;//���Ϳ���
     SendIntFlag = 0;//�����жϿ���
     StopRece = 0;//�������

     return USBD_OK;
}

static u8 class_deinit(usb_dev *udev, u8 config_index)
{
     /* deinitialize the data TX/RX endpoint */
     usbd_ep_clear(udev, DEV_IN_EP);
     usbd_ep_clear(udev, DEV_OUT_EP);
     usbd_ep_clear(udev, DEV_INTIN_EP);

     SendFlag = 0;//���Ϳ���
     SendIntFlag = 0;//�����жϿ���
     StopRece = 0;//�������
    return USBD_OK;
}

static u8 class_req_proc(usb_dev *udev, usb_req *req)
{
     usb_transc *transc = &udev->dev.transc_in[0];
     s8 s8temp;
     u16 u16temp;
     //�˴�����һ����׼����
     u8 UsbCmd[] = {req->bmRequestType,//
                    req->bRequest,//
                    (u8)(req->wValue),(u8)((req->wValue)>>8),//wValue
                    (u8)(req->wIndex),(u8)((req->wIndex)>>8),//wIndex
                    (u8)(req->wLength),(u8)((req->wLength)>>8)};//wLength
     //printf("Setup\r\n");//
     u16temp = UsbEnumDataSendBufferMaxSize;
     s8temp = P0SetupProcess(UsbCmd,sizeof(UsbCmd),UsbEnumDataSendBuffer,&u16temp); 
     if(s8temp > 0)
     {//�Ѵ���
          if((u16temp) && (s8temp == 1))
          {//�д���������
               transc->xfer_buf = UsbEnumDataSendBuffer;
               transc->remain_len = u16temp;
          }
          else if((u16temp) && (s8temp == 2))
          {//EP0�д���������               
               UsbEP0OUTDataLen = u16temp;
               if(UsbEP0OUTDataLen > UsbEnumDataSendBufferMaxSize)
               {//��ֹԽ��
                    UsbEP0OUTDataLen = UsbEnumDataSendBufferMaxSize;
               }
               //ʹ��EP0׼�������������ݰ�
               //usbd_class_cb.alter_set = req->bRequest;
               transc = &udev->dev.transc_out[0];//���ô���ṹ��ָ��
               transc->remain_len = UsbEP0OUTDataLen;//req->wLength;//���ô��䳤��
               transc->xfer_buf = UsbEnumDataSendBuffer;//���ô��仺����
          }          
     }
     return USBD_OK;    
}

static u8 class_set_interface(usb_dev *udev, usb_req *req)
{
     return USBD_OK;
}

//���ƶ˵���������
static u8 class_ctlx_in(usb_dev *udev)
{
     return USBD_OK;
}

//���ƶ˵��������
static u8 class_ctlx_out(usb_dev *udev)
{//EP0�յ����ݺ�Ļص�����
     if((P0OutProcess))// && (usbd_class_cb.alter_set != 0xFFU))
     {
          //usbd_class_cb.alter_set = 0xFFU;
          P0OutProcess(UsbEnumDataSendBuffer,UsbEP0OUTDataLen);
     }
     return USBD_OK;
}

static u8 class_data_in(usb_dev *udev, u8 ep_num)
{//���ݷ�����ɵĻص�����
     SendFlag = 0;    
     SendIntFlag = 0;
     return USBD_OK;
}

static u8 class_data_out(usb_dev *udev, u8 ep_num)
{//�յ����ݺ�Ļص�����
     //u32 u32i;
     if(ep_num == DEV_OUT_EP)
     {
          u8 rdata[128]; 
          u32 rl = ((usb_core_driver *)udev)->dev.transc_out[ep_num].xfer_count;
          u32 u32temp;
          if(rl)
          {               
               if(rl > 128)
               {
                    rl = 128;//��ֹ���Խ��
               }
               for(u32temp = 0;u32temp < rl;u32temp++)
               {
                    rdata[u32temp] = usb_recedata_buf[u32temp];
               }
          }

          if(StopRece)
          {//���ֹͣ���գ����ö˿�Ҫ��ӦNAK----��һ֡���Ͼ��ղ�������
               //hd_usb_devepstatusset(pdev,PRT_OUT_EP,USB_EP_RX_NAK);
               //printf("ֹͣ����\r\n");
          }
          else
          {
               usbd_ep_recev(udev, DEV_OUT_EP, usb_recedata_buf, DEV_EPOUT_SIZE);
          }

          if(rl)
          {
               ReceDataFunc(rdata,rl);//
          }         
     }
     return USBD_OK;
}

static u8 class_sof(usb_dev *udev)
{
     return USBD_OK;
}

static u8 class_incomplete_isoc_in(usb_dev *udev)
{
     return USBD_OK;
}

static u8 class_incomplete_isoc_out(usb_dev *udev)
{
     return USBD_OK;
}


