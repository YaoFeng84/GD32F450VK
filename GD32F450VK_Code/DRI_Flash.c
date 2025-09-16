/********************************************************************************************************************************************
*                                                                                                                                           *
*              ---------------------------------以下是模块的修改记录区-----------------------------------------                             *
*                                                                                                                                           *
********************************************************************************************************************************************/
/**********************************************
 * 内容：
 * 日期：2025-09-01
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
特点：
     
*/
#include "DRI_Flash.h"
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
#define Flash_SpaceStartAddr  0x08000000//flash空间起始地址
#define Flash_SpaceEndAddr    0x082FFFFF//flash空间结束地址
//扇区起始地址
static const u32 FlashSectorAddr[] = {
     //Bank0----1MB
     0x08000000,//扇区0起始地址--16K
     0x08004000,//扇区1起始地址--16K
     0x08008000,//扇区2起始地址--16K
     0x0800C000,//扇区3起始地址--16K
     0x08010000,//扇区4起始地址--64K
     0x08020000,//扇区5起始地址--128K
     0x08040000,//扇区6起始地址--128K
     0x08060000,//扇区7起始地址--128K
     0x08080000,//扇区8起始地址--128K
     0x080A0000,//扇区9起始地址--128K
     0x080C0000,//扇区10起始地址--128K
     0x080E0000,//扇区11起始地址--128K
     //Bank1----2816KB
     0x08100000,//扇区12起始地址--16K
     0x08104000,//扇区13起始地址--16K
     0x08108000,//扇区14起始地址--16K
     0x0810C000,//扇区15起始地址--16K
     0x08110000,//扇区16起始地址--64K
     0x08120000,//扇区17起始地址--128K
     0x08140000,//扇区18起始地址--128K
     0x08160000,//扇区19起始地址--128K
     0x08180000,//扇区20起始地址--128K
     0x081A0000,//扇区21起始地址--128K
     0x081C0000,//扇区22起始地址--128K
     0x081E0000,//扇区23起始地址--128K
     0x08200000,//扇区24起始地址--256K
     0x08240000,//扇区25起始地址--256K
     0x08280000,//扇区26起始地址--256K
     0x082C0000//扇区27起始地址--256K
};

static const u32 FlashSectorNum[] = {//扇区号
     CTL_SECTOR_NUMBER_0,//扇区0
     CTL_SECTOR_NUMBER_1,//扇区1
     CTL_SECTOR_NUMBER_2,//扇区2
     CTL_SECTOR_NUMBER_3,//扇区3
     CTL_SECTOR_NUMBER_4,//扇区4
     CTL_SECTOR_NUMBER_5,//扇区5
     CTL_SECTOR_NUMBER_6,//扇区6
     CTL_SECTOR_NUMBER_7,//扇区7
     CTL_SECTOR_NUMBER_8,//扇区8
     CTL_SECTOR_NUMBER_9,//扇区9
     CTL_SECTOR_NUMBER_10,//扇区10
     CTL_SECTOR_NUMBER_11,//扇区11
     CTL_SECTOR_NUMBER_12,//扇区12
     CTL_SECTOR_NUMBER_13,//扇区13
     CTL_SECTOR_NUMBER_14,//扇区14
     CTL_SECTOR_NUMBER_15,//扇区15
     CTL_SECTOR_NUMBER_16,//扇区16
     CTL_SECTOR_NUMBER_17,//扇区17
     CTL_SECTOR_NUMBER_18,//扇区18
     CTL_SECTOR_NUMBER_19,//扇区19
     CTL_SECTOR_NUMBER_20,//扇区20
     CTL_SECTOR_NUMBER_21,//扇区21
     CTL_SECTOR_NUMBER_22,//扇区22
     CTL_SECTOR_NUMBER_23,//扇区23
     CTL_SECTOR_NUMBER_24,//扇区24
     CTL_SECTOR_NUMBER_25,//扇区25
     CTL_SECTOR_NUMBER_26,//扇区26
     CTL_SECTOR_NUMBER_27//扇区27
};//扇区号
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------以下是模块的内部函数申明区------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
static u16 Flash_WriteData(u32 wadd,u8 *wd,u16 wl);
// static void Flash_SectorErase(u32 secaddr);
// static void Flash_SectorProcess(u32 addr,u16 ldata,u16 mfl,u16 rdata);
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------以下是模块的系统函数代码区------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/




/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------以下是模块的用户函数代码区------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* 函 数 名: DRI_Flash_ReadData
* 功能描述：Flash 阻塞型 读数据函数
*          支持任意地址任意大小的读取
* 入口参数：
            u32 radd:读地址
            u8 *rd:数据存放首地址
            u16 rl:读字节数
* 出口参数：
       其他值:实际读取字节数
        小于0:操作失败
* 注意事项:  
            无
* 例     如:
* 修改记录:
*           2025-09-01 BY:YJX
***************************************************************************/
s32 DRI_Flash_ReadData(u32 radd,u8 *rd,u16 rl)
{
     u8 *rp = (u8 *)radd;
     u16 u16temp;

     if(radd < Flash_SpaceStartAddr || radd > Flash_SpaceEndAddr || (radd + rl) > (Flash_SpaceEndAddr + 1))
     {//越界了
          return -1;
     }

     if(rl)
     {
          for(u16temp = 0;u16temp < rl;u16temp++)
          {
               rd[u16temp] = rp[u16temp];
          }
     }
     return rl;
}

/***************************************************************************
* 函 数 名: DRI_Flash_DirectWriteData
* 功能描述：Flash 阻塞型直写数据函数(不擦除直接写入)
*          支持任意地址任意大小的写入
* 入口参数：
            u32 wadd:写地址
            u8 *wd:数据源首地址
            u16 wl:写字节数
* 出口参数：
       其他值:实际写字节数
        小于0:操作失败
* 注意事项:  
            不擦除直接写入!!!
* 例   如:
* 修改记录:
*           2025-09-01 BY:YJX
***************************************************************************/
s32 DRI_Flash_DirectWriteData(u32 wadd,u8 *wd,u16 wl)
{//
     u8 u8temp,*rp,u8i,u8data[4];
     u16 u16temp,u16wl;

     if(wadd < Flash_SpaceStartAddr || wadd > Flash_SpaceEndAddr || (wadd + wl) > (Flash_SpaceEndAddr + 1))
     {//越界了
          return -1;
     }

     u16wl = wl;//暂存wl

     if(wl)
     {
          //处理首部非4字节对齐
          u8temp = (u8)(wadd % 4);
          if(u8temp)
          {//首部非4字节对齐
               rp = (u8 *)(wadd - u8temp);//往前u8temp个字节，读u8temp个数据
               for(u8i = 0;u8i < u8temp;u8i++)
               {
                    u8data[u8i] = rp[u8i];
               }
               for(u8i = u8temp;u8i < 4;u8i++)
               {
                    u8data[u8i] = wd[u8i - u8temp];
               }
               //对一个完整且对齐的4字节进行写操作
               Flash_WriteData((u32)rp,u8data,4);
               //更新写入地址、源数据指针、写入字节数
               u8temp = 4 - u8temp;
               wadd += u8temp;
               wd += u8temp;
               wl -= u8temp;
          }

          //写入中间部分
          u16temp = Flash_WriteData(wadd,wd,wl);
          wadd += u16temp;
          wd += u16temp;
          wl -= u16temp;

          //处理尾部非4字节对齐
          u8temp = (u8)(wl % 4);
          if(u8temp)
          {
               for(u8i = 0;u8i < u8temp;u8i++)
               {
                    u8data[u8i] = wd[u8i];
               }
               rp = (u8 *)(wadd + u8temp);
               for(u8i = u8temp;u8i < 4;u8i++)
               {
                    u8data[u8i] = rp[u8i - u8temp];
               }
               //对一个完整且对齐的4字节进行写操作
               Flash_WriteData((u32)wadd,u8data,4);
          }
     }

     return u16wl;
}

/// @brief 判断地址是否扇区头对齐 或 尾对齐
/// @param addr 待判断的地址
/// @return 小于0:表示不对齐 0:表示头对齐 大于0:表示尾对齐
s8 DRI_Flash_IsSectorAligned(u32 addr)
{
     u8 u8i,SectorNum = sizeof(FlashSectorAddr)/sizeof(FlashSectorAddr[0]);
     u32 u32temp;

     for(u8i = 0;u8i < SectorNum;u8i++)
     {
          if(addr == FlashSectorAddr[u8i])
          {//扇区头对齐
               return 0;
          }
          else 
          {//判断尾对齐
               u32temp = Flash_SpaceEndAddr;
               if(u8i < SectorNum - 1)
               {
                    u32temp = FlashSectorAddr[u8i + 1] - 1;
               }
               if(addr == u32temp)
               {//扇区尾对齐
                    return 1;
               }
          }
     }
     return -1;
}

/// @brief 擦除eaddr所在的整个扇区的函数
/// @param eaddr ：要擦除的地址
/// @return ：小于0:擦除失败 其他值：实际擦除字节数 
s32 DRI_Flash_EraseSector(u32 eaddr)
{
     u8 u8i,SectorNum = sizeof(FlashSectorAddr)/sizeof(FlashSectorAddr[0]);
     u32 u32temp;
     s32 s32result = -1;

     //获取地址所在的扇区号
     for(u8i = 0;u8i < SectorNum;u8i++)
     {
          u32temp = (Flash_SpaceEndAddr + 1);
          if(u8i < SectorNum - 1)
          {
               u32temp = FlashSectorAddr[u8i + 1];               
          }    
          //
          if((eaddr >= FlashSectorAddr[u8i]) && (eaddr < u32temp))
          {             
               //计算扇区大小  
               s32result = u32temp - FlashSectorAddr[u8i];
               //擦除扇区前，先解锁
               fmc_unlock(); 
               //清除错误标志
               fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
               //开始擦除扇区
               if(FMC_READY != fmc_sector_erase(FlashSectorNum[u8i]))
               {//擦除失败
                    s32result = -2;
               }
               //擦除扇区后，再上锁
               fmc_lock();
               //退出循环
               break;
          }
     }
     return s32result;
}

/***************************************************************************
* 函 数 名: DRI_Flash_Erase
* 功能描述：Flash 阻塞型 空间擦除函数
* 入口参数：
            u32 eaddr：擦除起始地址
            u32 esize：擦除字节数
* 出口参数：
       其他值:实际擦除字节数
        小于0:擦除失败
* 注意事项:
        是整扇区擦除的，所以擦除地址和大小必须是扇区对齐的
* 例    如:
* 修改记录:
*           2025-09-01 BY:YJX
***************************************************************************/
s32 DRI_Flash_Erase(u32 eaddr,u32 esize)
{
     u32 u32temp,u32len;
     u32 secaddr;
     s32 result = esize;

     if(eaddr < Flash_SpaceStartAddr || eaddr > Flash_SpaceEndAddr || (eaddr + esize) > (Flash_SpaceEndAddr + 1))
     {//越界了
          return -1;
     }

     //由于芯片扇区大小不一样，最小的有16K，最大的有256K，且只能进行扇区擦除，所以这里需要根据地址和大小进行判断
     //【1】、判断结束地址是否为扇区对齐地址
     u32len = sizeof(FlashSectorAddr) / sizeof(u32);
     secaddr = eaddr + esize;
     for(u32temp = 0;u32temp < u32len;u32temp++)
     {
          if(secaddr == FlashSectorAddr[u32temp])
          {//起始地址为扇区对齐地址
               break;
          }
     }     
     if(u32temp >= u32len)
     {
          if(secaddr != (Flash_SpaceEndAddr + 1))
          {
               return -2;//起始地址不是扇区对齐地址
          }
     }

     //【2】、判断起始地址是否为扇区对齐地址
     u32len = sizeof(FlashSectorAddr) / sizeof(u32);
     secaddr = eaddr;
     for(u32temp = 0;u32temp < u32len;u32temp++)
     {
          if(secaddr == FlashSectorAddr[u32temp])
          {//起始地址为扇区对齐地址
               break;
          }
     }
     if(u32temp >= u32len)
     {
          return -3;//起始地址不是扇区对齐地址
     }

     //【3】、擦除扇区
     //擦除扇区前，先解锁
     fmc_unlock(); 
     //清除错误标志
     fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
     //开始擦除扇区
     if(FMC_READY != fmc_sector_erase(FlashSectorNum[u32temp]))
     {//擦除失败
          result = -4;
     }
     //擦除扇区后，再上锁
     fmc_lock();

     return result;
}

/**
 * @brief DRI_Flash_EraseWriteData
 * Flash 阻塞型擦写数据函数(先擦除再写入)
 * 由于是整扇区擦除的，所以此接口接入也是整扇区写入的。
 * @param wadd 写入地址
 * @param wd 待写入数据首地址
 * @param wl 待写入数据字节数
 * @return s32 小于0:写失败，其他值:实际写入字节数
 */
s32 DRI_Flash_EraseWriteData(u32 wadd,u8 *wd,u32 wl)
{
     s32 s32temp;

     if(wadd < Flash_SpaceStartAddr || wadd > Flash_SpaceEndAddr || (wadd + wl) > (Flash_SpaceEndAddr + 1))
     {//越界了
          return -1;
     }

     if(wl)
     {
     //先擦除
          s32temp = DRI_Flash_Erase(wadd,wl);
          if(s32temp != wl)
          {
               return s32temp;
          }
     //再写入
          return DRI_Flash_DirectWriteData(wadd,wd,wl);
     }
     return wl;
}

/**
 * @brief DRI_Flash_OutCapacity
 * 输出最大空间大小
 * @return u32 最大空间大小，单位字节数
 */
u32 DRI_Flash_OutCapacity(void)
{
     return (Flash_SpaceEndAddr - Flash_SpaceStartAddr + 1);
}

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------以下是模块的内部函数代码区------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
//待写入的地址必须是4字节对齐!!!
//返回实际写入的字节数
static u16 Flash_WriteData(u32 wadd,u8 *wd,u16 wl)
{
     u16 u16temp,u16num;

     fmc_unlock();
     fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);

     u16num = (wl >> 2);
     for(u16temp = 0;u16temp < u16num;u16temp++)
     {
          if(FMC_READY == fmc_word_program(wadd,*(u32 *)wd))
          {
               wadd += 4;
               wd += 4;
          }
          else
          {
               break;
          }
     }
     
     fmc_lock();

     return (u16num << 2);
}

// //纯扇区擦除
// //secaddr为扇区地址，必须是扇区对齐
// static void Flash_SectorErase(u32 secaddr)
// {
//      EFM_Unlock();
//      EFM_SectorErase(secaddr);
//      EFM_Lock();
// }

// /**
//  * @brief 
//  * 扇区处理，主要用于半扇区擦除时，还有半扇区数据需要在擦除后再写入
//  * @param addr 扇区起始地址(要求扇区对齐)
//  * @param ldata 扇区前部读取字节数(可以为0)
//  * @param mfl 扇区中部填充0xff字节数(不能为0)
//  * @param rdata 扇区后部读取字节数(可以为0)
//  */
// static void Flash_SectorProcess(u32 addr,u16 ldata,u16 mfl,u16 rdata)
// {
//      // u8 buff[Flash_MinSectorSize];
//      // u8 *rp = (u8*)addr;
//      // u16 u16i = 0;

//      // //整理数据
//      // for(;u16i < ldata;)
//      // {
//      //      buff[u16i++] = *(u8 *)rp;
//      //      rp++;
//      // }
//      // for(;u16i < (ldata + mfl);)
//      // {
//      //      buff[u16i++] = 0xff;
//      //      rp++;
//      // }
//      // for(;u16i < (ldata + mfl + rdata);)
//      // {
//      //      buff[u16i++] = *(u8 *)rp;
//      //      rp++;
//      // }
//      // //擦除扇区
//      // Flash_SectorErase(addr);//擦除扇区
//      // //写扇区数据
//      // Flash_WriteData(addr,buff,Flash_MinSectorSize);
// }



















// #define ADDR_FMC_SECTOR_0     ((uint32_t)0x08000000) /*!< base address of sector 0, 16 kbytes */
// #define ADDR_FMC_SECTOR_1     ((uint32_t)0x08004000) /*!< base address of sector 1, 16 kbytes */
// #define ADDR_FMC_SECTOR_2     ((uint32_t)0x08008000) /*!< base address of sector 2, 16 kbytes */
// #define ADDR_FMC_SECTOR_3     ((uint32_t)0x0800C000) /*!< base address of sector 3, 16 kbytes */
// #define ADDR_FMC_SECTOR_4     ((uint32_t)0x08010000) /*!< base address of sector 4, 64 kbytes */
// #define ADDR_FMC_SECTOR_5     ((uint32_t)0x08020000) /*!< base address of sector 5, 64 kbytes */
// #define ADDR_FMC_SECTOR_6     ((uint32_t)0x08040000) /*!< base address of sector 6, 64 kbytes */
// #define ADDR_FMC_SECTOR_7     ((uint32_t)0x08060000) /*!< base address of sector 7, 64 kbytes */
// #define ADDR_FMC_SECTOR_8     ((uint32_t)0x08080000) /*!< base address of sector 8, 64 kbytes */
// #define ADDR_FMC_SECTOR_9     ((uint32_t)0x080A0000) /*!< base address of sector 9, 64 kbytes */
// #define ADDR_FMC_SECTOR_10    ((uint32_t)0x080C0000) /*!< base address of sector 10, 64 kbytes */
// #define ADDR_FMC_SECTOR_11    ((uint32_t)0x080E0000) /*!< base address of sector 11, 64 kbytes */

// uint32_t fmc_sector_get(uint32_t address)
// {
//     uint32_t sector = 0;
//     if((address < ADDR_FMC_SECTOR_1) && (address >= ADDR_FMC_SECTOR_0)){
//         sector = CTL_SECTOR_NUMBER_0;
//     }else if((address < ADDR_FMC_SECTOR_2) && (address >= ADDR_FMC_SECTOR_1)){
//         sector = CTL_SECTOR_NUMBER_1;
//     }else if((address < ADDR_FMC_SECTOR_3) && (address >= ADDR_FMC_SECTOR_2)){
//         sector = CTL_SECTOR_NUMBER_2;
//     }else if((address < ADDR_FMC_SECTOR_4) && (address >= ADDR_FMC_SECTOR_3)){
//         sector = CTL_SECTOR_NUMBER_3;  
//     }else if((address < ADDR_FMC_SECTOR_5) && (address >= ADDR_FMC_SECTOR_4)){
//         sector = CTL_SECTOR_NUMBER_4;
//     }else if((address < ADDR_FMC_SECTOR_6) && (address >= ADDR_FMC_SECTOR_5)){
//         sector = CTL_SECTOR_NUMBER_5;
//     }else if((address < ADDR_FMC_SECTOR_7) && (address >= ADDR_FMC_SECTOR_6)){
//         sector = CTL_SECTOR_NUMBER_6;
//     }else if((address < ADDR_FMC_SECTOR_8) && (address >= ADDR_FMC_SECTOR_7)){
//         sector = CTL_SECTOR_NUMBER_7;  
//     }else if((address < ADDR_FMC_SECTOR_9) && (address >= ADDR_FMC_SECTOR_8)){
//         sector = CTL_SECTOR_NUMBER_8;
//     }else if((address < ADDR_FMC_SECTOR_10) && (address >= ADDR_FMC_SECTOR_9)){
//         sector = CTL_SECTOR_NUMBER_9;
//     }else if((address < ADDR_FMC_SECTOR_11) && (address >= ADDR_FMC_SECTOR_10)){
//         sector = CTL_SECTOR_NUMBER_10;
//     }else{
//         sector = CTL_SECTOR_NUMBER_11;
//     }
//     return sector;
// }

// /*!
//     \brief      erases the sector of a given sector number
//     \param[in]  fmc_sector: a given sector number
//       \arg        CTL_SECTOR_NUMBER_0: sector 0
//       \arg        CTL_SECTOR_NUMBER_1: sector 1
//       \arg        CTL_SECTOR_NUMBER_2: sector 2
//       \arg        CTL_SECTOR_NUMBER_3  sector 3
//       \arg        CTL_SECTOR_NUMBER_4: sector 4
//       \arg        CTL_SECTOR_NUMBER_5: sector 5
//       \arg        CTL_SECTOR_NUMBER_6: sector 6
//       \arg        CTL_SECTOR_NUMBER_7  sector 7
//       \arg        CTL_SECTOR_NUMBER_8: sector 8
//       \arg        CTL_SECTOR_NUMBER_9: sector 9
//       \arg        CTL_SECTOR_NUMBER_10: sector 10
//       \arg        CTL_SECTOR_NUMBER_11  sector 11
//     \param[out] none
//     \retval     none
// */
// void fmc_erase_sector(uint32_t fmc_sector)
// {
//     /* unlock the flash program erase controller */
//     fmc_unlock(); 
//     /* clear pending flags */
//     fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
//     /* wait the erase operation complete*/
//     if(FMC_READY != fmc_sector_erase(fmc_sector)){
//         while(1);
//     }
//     /* lock the flash program erase controller */
//     fmc_lock();
// }

// /*!
//     \brief      write 32 bit length data to a given address
//     \param[in]  address: a given address(0x08000000~0x080FFFFF)
//     \param[in]  length: data length
//     \param[in]  data_32: data pointer
//     \param[out] none
//     \retval     none
// */
// void fmc_write_32bit_data(uint32_t address, uint16_t length, int32_t* data_32)
// {
//     uint16_t StartSector, EndSector,i;
//     /* unlock the flash program erase controller */
//     fmc_unlock();
//     /* clear pending flags */
//     fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
//     /* get the number of the start and end sectors */
//     StartSector = fmc_sector_get(address);
//     EndSector = fmc_sector_get(address + 4*length);
//     /* each time the sector number increased by 8, refer to the sector definition */
//     for(i = StartSector; i < EndSector; i += 8){
//         if(FMC_READY != fmc_sector_erase(i)){
//             while(1);
//         }
//     }
//     /* write data_32 to the corresponding address */
//     for(i=0; i<length; i++){
//         if(FMC_READY == fmc_word_program(address, data_32[i])){
//             address = address + 4;
//         }else{ 
//             while(1);
//         }
//     }
//     /* lock the flash program erase controller */
//     fmc_lock();
// }

// /*!
//     \brief      read 32 bit length data from a given address
//     \param[in]  address: a given address(0x08000000~0x080FFFFF)
//     \param[in]  length: data length
//     \param[in]  data_32: data pointer
//     \param[out] none
//     \retval     none
// */
// void fmc_read_32bit_data(uint32_t address, uint16_t length, int32_t* data_32)
// {
//     uint8_t i;
//     for(i=0; i<length; i++){
//         data_32[i] = *(__IO int32_t*)address;
//         address=address + 4;
//     }
// }

// /*!
//     \brief      write 16 bit length data to a given address
//     \param[in]  address: a given address(0x08000000~0x080FFFFF)
//     \param[in]  length: data length
//     \param[in]  data_16: data pointer
//     \param[out] none
//     \retval     none
// */
// void fmc_write_16bit_data(uint32_t address, uint16_t length, int16_t* data_16)
// {
//     uint16_t StartSector, EndSector,i;
//     /* unlock the flash program erase controller */
//     fmc_unlock();
//     /* clear pending flags */
//     fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
//     /* get the number of the start and end sectors */
//     StartSector = fmc_sector_get(address);
//     EndSector = fmc_sector_get(address + 2*length);
//     /* each time the sector number increased by 8, refer to the sector definition */
//     for(i = StartSector; i < EndSector; i += 8){
//         if(FMC_READY != fmc_sector_erase(i)){
//             while(1);
//         }
//     }
//     /* write data_16 to the corresponding address */
//     for(i=0; i<length; i++){
//         if(FMC_READY == fmc_halfword_program(address, data_16[i])){
//             address = address + 2;
//         }else{ 
//             while(1);
//         }
//     }
//     /* lock the flash program erase controller */
//     fmc_lock();
// }

// /*!
//     \brief      read 16 bit length data to a given address
//     \param[in]  address: a given address(0x08000000~0x080FFFFF)
//     \param[in]  length: data length
//     \param[in]  data_16: data pointer
//     \param[out] none
//     \retval     none
// */
// void fmc_read_16bit_data(uint32_t address, uint16_t length, int16_t* data_16)
// {
//     uint8_t i;
//     for(i=0; i<length; i++){
//         data_16[i] = *(__IO int16_t*)address;
//         address = address + 2;
//     }
// }

// /*!
//     \brief      write 8 bit length data to a given address
//     \param[in]  address: a given address(0x08000000~0x080FFFFF)
//     \param[in]  length: data length
//     \param[in]  data_8: data pointer
//     \param[out] none
//     \retval     none
// */
// void fmc_write_8bit_data(uint32_t address, uint16_t length, int8_t* data_8)
// {
//     uint16_t StartSector, EndSector,i;
//     /* unlock the flash program erase controller */
//     fmc_unlock();
//     /* clear pending flags */
//     fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
//     /* get the number of the start and end sectors */
//     StartSector = fmc_sector_get(address);
//     EndSector = fmc_sector_get(address + length);
//     /* each time the sector number increased by 8, refer to the sector definition */
//     for(i = StartSector; i < EndSector; i += 8){
//         if(FMC_READY != fmc_sector_erase(i)){
//             while(1);
//         }
//     }
//     /* write data_8 to the corresponding address */
//     for(i=0; i<length; i++){
//         if(FMC_READY == fmc_byte_program(address, data_8[i])){
//             address++;
//         }else{ 
//             while(1);
//         }
//     }
//     /* lock the flash program erase controller */
//     fmc_lock();
// }

// /*!
//     \brief      read 8 bit length data to a given address
//     \param[in]  address: a given address(0x08000000~0x080FFFFF)
//     \param[in]  length: data length
//     \param[in]  data_8: data pointer
//     \param[out] none
//     \retval     none
// */
// void fmc_read_8bit_data(uint32_t address, uint16_t length, int8_t* data_8)
// {
//     uint8_t i;
//     for(i=0; i<length; i++){
//         data_8[i] = *(__IO int8_t*)address;
//         address++;
//     }
// }



