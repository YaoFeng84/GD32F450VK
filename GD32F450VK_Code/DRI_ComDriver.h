#ifndef DRI_ComDriver_h
#define DRI_ComDriver_h

#include "TypeMro.h"
#include "gd32f4xx.h"
//
#include "system_gd32f4xx.h"
//外设头文件
#include "gd32f4xx_libopt.h"
//


//USB设备外设
//USB内核
#include "drv_usb_core.h"
#include "drv_usb_dev.h"
#include "drv_usb_regs.h"
//
#include "drv_usbd_int.h"
//USB设备内核
#include "usbd_core.h"
#include "usbd_enum.h"


extern void NULLFP(void);

//返回固件版本号
extern u8* DRI_ComDriver_OutVersion(void);

//返回芯片Flash空间大小，单位：字节
extern u32 DRI_ComDriver_OutFlashSize(void);

//返回芯片RAM空间大小，单位：字节
extern u32 DRI_ComDriver_OutRAMSize(void);

//uid1:(0~31)、uid2:(32~63)、uid3:(64~95)共96位
extern void DRI_ComDriver_OutUID(u32 *uid1, u32 *uid2, u32 *uid3);

extern void DRI_ComDriver_Delay1ms(void);
extern void DRI_ComDriver_Delay1us(void);

typedef void(*DRI_ComDriver_DoubleVoidFuncType)(void);//定义一个双void的函数指针类型

/***************************************************************************
* 函 数 名: DRI_ComDriver_SetHardFaultIntterrupt_FCB
* 功能描述：设置硬件错误中断回调 函数
* 入口参数：
            DRI_ComDriver_DoubleVoidFuncType fcbp：硬件错误中断回调函数指针
* 出口参数：
            无
* 注意事项:  
            
* 例     如:
* 修改记录 :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_SetHardFaultIntterrupt_FCB(DRI_ComDriver_DoubleVoidFuncType fcbp);

/***************************************************************************
* 函 数 名: DRI_ComDriver_SetSP
* 功能描述：设置栈顶指针 函数
* 入口参数：
            u32 _sp:栈顶指针值
* 出口参数：
            无
* 注意事项:  
            修改栈顶指针
* 例     如:
* 修改记录 :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_SetSP(u32 _sp);

/*-------------------------------------------------
函数名:DRI_ComDriver_DisableAllPeripheralInterrupt
功   能:关闭所有外设的各自中断
参   数:
       无
返回值:
       无
注   意:
       无
示   例:
作   者:YJX
版   本:V1.0
时   间:2025-09-08
-------------------------------------------------*/
extern void DRI_ComDriver_DisableAllPeripheralInterrupt(void);

/*-------------------------------------------------
函数名:DRI_ComDriver_ResetAllPeripheral
功   能:复位所有外设
参   数:
       无
返回值:
       无
注   意:
       无
示   例:
作   者:YJX
版   本:V1.0
时   间:2025-09-08
-------------------------------------------------*/
extern void DRI_ComDriver_ResetAllPeripheral(void);

/***************************************************************************
* 函 数 名: DRI_ComDriver_EnableAllINT
* 功能描述：使能外设总中断 函数
* 入口参数：
            无
* 出口参数：
            无
* 注意事项:  
            无
* 例     如:
* 修改记录 :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_EnableAllINT(void);

/***************************************************************************
* 函 数 名: DRI_ComDriver_DisableAllINT
* 功能描述：禁能外设总中断 函数
* 入口参数：
            无
* 出口参数：
            无
* 注意事项:  
            无
* 例     如:
* 修改记录 :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_DisableAllINT(void);

/***************************************************************************
* 函 数 名: DRI_ComDriver_EnableAllFault
* 功能描述：使能内核总异常 函数
* 入口参数：
            无
* 出口参数：
            无
* 注意事项:  
            无
* 例     如:
* 修改记录 :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_EnableAllFault(void);

/***************************************************************************
* 函 数 名: DRI_ComDriver_DisableAllFault
* 功能描述：禁能内核总异常 函数
* 入口参数：
            无
* 出口参数：
            无
* 注意事项:  
            无
* 例     如:
* 修改记录 :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_DisableAllFault(void);

/***************************************************************************
* 函 数 名: DRI_ComDriver_CoreReset
* 功能描述：内核复位 函数
* 入口参数：
            无
* 出口参数：
            无
* 注意事项:  
            无
* 例     如:
* 修改记录 :
*           2025-09-08 BY:YJX
***************************************************************************/
extern void DRI_ComDriver_CoreReset(void);

/***************************************************************************
* 函 数 名: DRI_ComDriver_SysReset
* 功能描述：外设复位 函数
* 入口参数：
            无
* 出口参数：
            无
* 注意事项:  
            无
* 例     如:
* 修改记录 :
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
     GDOut = 0u,//数字输出
     GDIn = 1u  //数字输入
}PinMode;

typedef enum
{
     ITFallEdge = 0u,//下降沿
     ITRiseEdge = 1u,//上升沿
     ITBothEdg = 2u //双边沿
}INTTriggerMode;//触发模式枚举

typedef struct
{
     PortNum portn;      //外部中断端口号
     PinNum pinn;        //外部中断引脚号
     INTTriggerMode tm;  //触发模式
     u8 pri;             //中断优先级(0~15，越小优先级越高)
     void (*cbfp)(void); //中断回调函数指针
}ExIntCnfType;


typedef enum
{
     DataBits8 = 0u,//8位数据宽度
     DataBits9 = 1u,//9位数据宽度
}DataBitType;

typedef enum
{
     HalfStopBit = 0u,//半位停止位
     OneStopBit = 1u,//1位停止位
     OneAndHalfStopBit = 2u,//1.5位停止位
     TwoStopBit = 3u,//2位停止位
}StopBitType;

typedef enum
{
     ParityNone = 0u,//无校验
     ParityEven = 1u,//偶校验
     ParityOdd = 2u,//奇校验
}ParityType;

typedef struct
{
     u8 FEnable;              //接收硬流控使能位(0:禁用 非0:使用)
     u8 RHWFlowXonLevel;      //接收硬流控XON电平(0:低电平 非0:高电平)
     u8 RHWFlowDefaultLevel;  //接收硬流控默认电平(0:低电平 非0:高电平)
     PortNum RFlowcontrolp;   //接收硬流控端口号
     PinNum RFlowcontroln;    //接收硬流控引脚号
}RHWFlowCrl;

typedef struct
{
//---常规配置
     u32 bps;            //波特率(2400~921600)
     DataBitType DataBit;//数据位
     StopBitType StopBit;//停止位
     ParityType  Parity; //校验模式
     RHWFlowCrl rhwfc;   //接收硬流控
//---中断配置
     u8 IntPri;        //串口中断优先级(0~15，越小优先级越高，超过范围禁止中断)
//---接收部分
     void (*Recfp)(u8);  //接收到数据回调函数指针
     u8 RecData_IntEnable;//接收数据中断使能(0:禁止 非0:使能)
//---发送部分
     void (*SendOKfp)(void);//发送完成回调函数指针
     u8 SendOK_IntEnable;//发送完成中断使能(0:禁止 非0:使能)
     u8 SendINTDefaultState;//发送中断默认状态(0:关闭 1:开启)
}DRI_USARTCnfType;

/**
 * @brief
 *     P0Setup数据处理回调函数
 * @param  u8*  待处理数据首地址
 * @param  u16  待处理数据字节数
 * @param  u8*  返回数据首地址
 * @param  u16* 输入(返回数据空间字节数) 输出(实际返回/读取的字节数)
 * @return s8   小于0:表示处理错误
 *              等于0:表示命令未处理
 *                  1:表示命令已处理，需要将返回的数据通过P0端口发送给主机
 *                  2:表示命令已处理，需要将P0端口的OUT数据读取出来
 */
typedef s8(*DRI_USB_P0SetupProcessFunc)(u8*,u16,u8*,u16*);
typedef void(*DRI_USB_ReceDataFunc)(u8*,u16);
typedef s32(*DRI_USB_P0OutProcessFunc)(u8*,u16);//P0端口OUT数据的处理回调函数指针(OUT数据首地址,OUT数据字节数)返回值:实际处理字节数

typedef struct
{
     u8 IntPri;                    //中断优先级(0~15)
     DRI_USB_ReceDataFunc ReceDataFunc;//USB收到数据回调函数指针
     DRI_USB_P0SetupProcessFunc P0SetupProcess;//P0枚举处理回调函数指针
     DRI_USB_P0OutProcessFunc P0OutProcess;//P0端口OUT数据处理回调函数指针
}DRI_USBCnfType;

typedef struct
{
     u8 OutEP_Num;               //输出端点号
     u8 OutEP_Type;            //输出端点类型(0:控制端点 1:中断端点 2:批量端点 3:同步端点)
     u16 OutEP_MaxPacketSize;      //输出端点最大包字节数
     //
     u8 InEP_Num;                 //输入端点号
     u8 InEP_Type;             //输入端点类型(0:控制端点 1:中断端点 2:批量端点 3:同步端点)
     u16 InEP_MaxPacketSize;       //输入端点最大包字节数
     //
     u8 IntInEP_Num;             //中断输入端点号
     u8 IntInEP_Type;           //中断输入端点类型(0:控制端点 1:中断端点 2:批量端点 3:同步端点)
     u16 IntInEP_MaxPacketSize;    //中断输入端点最大包字节数
     //
     u8 P0EP_MaxPacketSize;        //P0端点最大包字节数
}DRI_USB_EPType;//USB的端点结构体

typedef enum
{
     LP_Rst    = 0u,   //深度睡眠/待机复位发生时的复位
     WWDGT_Rst = 1u,   //窗口看门狗定时器复位发生时的复位
     FWDGT_Rst = 2u,   //独立看门狗复位发生时的复位
     SW_Rst    = 3u,   //软件复位发生时的复位
     POR_Rst   = 4u,   //电源复位发生时的复位
     EP_Rst    = 5u,   //外部引脚复位发生时的复位
     BOR_Rst   = 6u,   //欠压复位复位发生时的复位     
     Multiply_Rst = 7u,   //多源复位发生时的复位
}ResetFlag;

#endif

