/********************************************************************************************************************************************
*                                                                                                                                           *
*              ---------------------------------以下是模块的修改记录区-----------------------------------------                             *
*                                                                                                                                           *
********************************************************************************************************************************************/
/**********************************************
 * 内容：
 * 日期：2025-09-11
 * 作者：YJX
 * 版本号：V1.0（初版）
 ***********************************************
 * 修改内容：
 * 修改日期：
 * 修改作者：
 * 版本号：
 ***********************************************
*/
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------以下模块的说明区-----------------------------------------                                  *
*                                                                                                                                           *
********************************************************************************************************************************************/
/*	

*/
#include "DRI_CAN.h"
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------以下模块的对接函数区-----------------------------------------                                  *
*                                                                                                                                           *
********************************************************************************************************************************************/

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------以下是模块的变量申明和宏定义区--------------------------------                      *
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
最优配置参数表（误差=0，采样点≈80%）
波特率(Kbps)	Prescaler	BS1(TQ)	BS2(TQ)	SJW(TQ)	总TQ	采样点	实际波特率(Kbps)	  误差(%)
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
//42MHz的CAN时钟下，波特率参数
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
*               ----------------------------------以下是模块的内部函数申明区------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
static s8 CAN_CalculateCANParameters(u32 baudrate,u16 *prescaler,u8 *bs1,u8 *bs2);
static s8 CAN_SendData(u32 canx,DRI_CAN_CommunicatDataType *data);
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------以下是模块的系统函数代码区------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* 函 数 名: DRI_CANx_Config
* 功能描述：CANx配置函数
* 入口参数：
            DRI_CANCnfType *cnf:CAN配置参数
* 出口参数：
            -1:表示配置失败
            0:表示配置成功
* 注意事项:  

* 例     如:
* 修改记录 :
          
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
               //使能GPIOA时钟
               rcu_periph_clock_enable(RCU_GPIOA);               
               //使能CAN0时钟
               rcu_periph_clock_enable(RCU_CAN0); 
               //
               CanX = CAN0;
               can_filter.filter_number = 0;//0号过滤器
               can_filter.filter_fifo_number = CAN_FIFO0;//接收FIFO0
               FifoNotEmptyInterrupt = CAN_INTEN_RFNEIE0;//接收FIFO0非空中断
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
               //使能GPIOB时钟
               rcu_periph_clock_enable(RCU_GPIOB);//使能GPIOB时钟               
               //使能CAN0时钟
               rcu_periph_clock_enable(RCU_CAN0); 
               //
               CanX = CAN0;
               can_filter.filter_number = 0;//0号过滤器
               can_filter.filter_fifo_number = CAN_FIFO0;//接收FIFO0
               FifoNotEmptyInterrupt = CAN_INTEN_RFNEIE0;//接收FIFO0非空中断
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
               //使能GPIOD时钟
               rcu_periph_clock_enable(RCU_GPIOD);//使能GPIOD时钟               
               //使能CAN0时钟
               rcu_periph_clock_enable(RCU_CAN0); 
               //
               CanX = CAN0;
               can_filter.filter_number = 0;//0号过滤器
               can_filter.filter_fifo_number = CAN_FIFO0;//接收FIFO0
               FifoNotEmptyInterrupt = CAN_INTEN_RFNEIE0;//接收FIFO0非空中断
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
               //使能GPIOB时钟
               rcu_periph_clock_enable(RCU_GPIOB);//使能GPIOB时钟
               //使能CAN1时钟
               rcu_periph_clock_enable(RCU_CAN1); 
               //
               CanX = CAN1;
               can_filter.filter_number = 1;//1号过滤器
               can_filter.filter_fifo_number = CAN_FIFO1;//接收FIFO1
               FifoNotEmptyInterrupt = CAN_INTEN_RFNEIE1;//接收FIFO1非空中断
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
               //使能GPIOB时钟
               rcu_periph_clock_enable(RCU_GPIOB);//使能GPIOB时钟
               //使能CAN1时钟
               rcu_periph_clock_enable(RCU_CAN1); 
               //
               CanX = CAN1;
               can_filter.filter_number = 1;//1号过滤器
               can_filter.filter_fifo_number = CAN_FIFO1;//接收FIFO1
               FifoNotEmptyInterrupt = CAN_INTEN_RFNEIE1;//接收FIFO1非空中断
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
     can_deinit(CanX);//CAN复位
     can_parameter.time_triggered = DISABLE;//时间触发通信模式：禁用
     can_parameter.auto_bus_off_recovery = DISABLE;//自动总线关闭恢复：禁用
     can_parameter.auto_wake_up = DISABLE;//自动唤醒：禁用
     can_parameter.auto_retrans = DISABLE;//自动重传：禁用
     can_parameter.rec_fifo_overwrite = DISABLE;//接收FIFO溢出时覆盖：禁用
     can_parameter.trans_fifo_order = DISABLE;//发送FIFO优先级由ID决定：禁用
     can_parameter.working_mode = CAN_NORMAL_MODE;//正常模式
     can_parameter.resync_jump_width = CAN_BT_SJW_1TQ;//重新同步跳转宽度：1个时间单位
//----------------------------   
     //bps = APB1 / (prescaler * (1 + time_segment_1 + time_segment_2))
     //bps = 42 000 000 / (12 * (1 + 10 + 3)) = 250 000
//---------------------------- 
     can_parameter.time_segment_1 = (u8s1 - 1);//CAN_BT_BS1_10TQ;//时间段1
     can_parameter.time_segment_2 = (u8s2 - 1);//CAN_BT_BS2_3TQ;//时间段2
     can_parameter.prescaler = u16prescaler;//12;//波特率分频系数
     

     if(can_init(CanX, &can_parameter) != SUCCESS)//初始化CAN
     {
          return -2;
     }

     //初始化过滤器 
     //can_filter.filter_number = 0;//使用0组过滤器。//CAN0有14组过滤器？？？？CAN1从15组开始？？？       
     can_filter.filter_mode = CAN_FILTERMODE_MASK;//掩码过滤模式
     can_filter.filter_bits = CAN_FILTERBITS_32BIT;//32位过滤器(29位)
     can_filter.filter_list_high = 0x0000;//过滤值高位
     can_filter.filter_list_low = 0x0000;//过滤值低位
     can_filter.filter_mask_high = 0x0000;//过滤器掩码值高位
     can_filter.filter_mask_low = 0x0000; //过滤器掩码值低位
     //can_filter.filter_fifo_number = CAN_FIFO0;//接收FIFO0
     can_filter.filter_enable = ENABLE;//使能过滤器
     can_filter_init(&can_filter);//初始化过滤器

     //配置中断
     //nvic_irq_enable(IRQn,0,0);
     NVIC_SetPriority(IRQn, cnf->IntPri);//设置中断优先级
     NVIC_ClearPendingIRQ(IRQn);//清除中断标志
     NVIC_EnableIRQ(IRQn);//使能中断

     //使能接收FIFO非空中断
     can_interrupt_enable(CanX, FifoNotEmptyInterrupt);

     return 0;
}

void CAN0_RX0_IRQHandler(void)
{
     u8 u8temp;
     can_receive_message_struct receive_message;
     DRI_CAN_CommunicatDataType cdt;
     //
     can_struct_para_init(CAN_RX_MESSAGE_STRUCT, &receive_message);//初始化
     can_message_receive(CAN0, CAN_FIFO0, &receive_message);
     //
     if(CAN0_ReceCBF != NULL)
     {
          cdt.FrameType = 0;//标准帧
          cdt.FrameID = receive_message.rx_sfid;//帧ID
          if(CAN_FF_EXTENDED == receive_message.rx_ff)
          {//是扩展帧
               cdt.FrameType = 1;//扩展帧
               cdt.FrameID = receive_message.rx_efid;//帧ID
          }
          cdt.FrameDataLen = receive_message.rx_dlen;//帧数据长度
          for(u8temp = 0;u8temp < receive_message.rx_dlen;u8temp++)
          {
               cdt.FrameData[u8temp] = receive_message.rx_data[u8temp];//读取数据
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
     can_struct_para_init(CAN_RX_MESSAGE_STRUCT, &receive_message);//初始化
     can_message_receive(CAN1, CAN_FIFO1, &receive_message);
     //
     if(CAN1_ReceCBF != NULL)
     {
          cdt.FrameType = 0;//标准帧
          cdt.FrameID = receive_message.rx_sfid;//帧ID
          if(CAN_FF_EXTENDED == receive_message.rx_ff)
          {//是扩展帧
               cdt.FrameType = 1;//扩展帧
               cdt.FrameID = receive_message.rx_efid;//帧ID
          }
          cdt.FrameDataLen = receive_message.rx_dlen;//帧数据长度
          for(u8temp = 0;u8temp < receive_message.rx_dlen;u8temp++)
          {
               cdt.FrameData[u8temp] = receive_message.rx_data[u8temp];//读取数据
          }
          CAN1_ReceCBF(&cdt);
     }
}

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------以下是模块的用户函数代码区------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* 函 数 名: DRI_CAN0_SendData
* 功能描述：CAN0发送数据函数
* 入口参数：
          DRI_CAN_CommunicatDataType *data:待发送的数据
* 出口参数：
          小于0:表示启动发送失败
             0:表示启动发送成功
* 注意事项:  

* 例     如:
* 修改记录 :
          
*           2025-09-11 BY:
***************************************************************************/
s8 DRI_CAN0_SendData(DRI_CAN_CommunicatDataType *data)
{
     return CAN_SendData(CAN0,data);
}

/***************************************************************************
* 函 数 名: DRI_CAN1_SendData
* 功能描述：CAN1发送数据函数
* 入口参数：
          DRI_CAN_CommunicatDataType *data:待发送的数据
* 出口参数：
          小于0:表示启动发送失败
             0:表示启动发送成功
* 注意事项:  

* 例     如:
* 修改记录 :
          
*           2025-09-11 BY:
***************************************************************************/
s8 DRI_CAN1_SendData(DRI_CAN_CommunicatDataType *data)
{
     return CAN_SendData(CAN1,data);
}

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------以下是模块的内部函数代码区------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
//计算CAN波特率参数
static s8 CAN_CalculateCANParameters(u32 baudrate,u16 *prescaler,u8 *bs1,u8 *bs2)
{
     u16 u16i,u16temp;
     //CAN时钟源频率为PCLK1
     if(rcu_clock_freq_get(CK_APB1) != 42000000)
     {//时钟源频率不是42M
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

//发送CAN数据
//返回值：0，成功；-1，失败
static s8 CAN_SendData(u32 canx,DRI_CAN_CommunicatDataType *data)
{
     u8 u8i;
     can_trasnmit_message_struct transmit_message;//定义发送消息结构体
     can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &transmit_message);
     /* initialize transmit message */
     transmit_message.tx_sfid = data->FrameID;//标准帧ID
     transmit_message.tx_efid = data->FrameID;//扩展帧ID
     transmit_message.tx_ft = CAN_FT_DATA;//数据帧  CAN_FT_REMOTE//远程帧
     transmit_message.tx_ff = CAN_FF_STANDARD;//标准帧格式
     if(data->FrameType)
     {
          transmit_message.tx_ff = CAN_FF_EXTENDED;//扩展帧格式
     }
     transmit_message.tx_dlen = data->FrameDataLen;//数据长度
     for(u8i = 0;u8i < data->FrameDataLen;u8i++)//数据
     {
          transmit_message.tx_data[u8i] = data->FrameData[u8i];
     }
     //
     if(can_message_transmit(CAN0, &transmit_message) == CAN_NOMAILBOX)//发送数据
     {//发送失败
          return -1;
     }
     return 0;
}

