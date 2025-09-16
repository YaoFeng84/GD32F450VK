/********************************************************************************************************************************************
*                                                                                                                                           *
*              ---------------------------------������ģ����޸ļ�¼��-----------------------------------------                             *
*                                                                                                                                           *
********************************************************************************************************************************************/
/**********************************************
 * ���ݣ�
 * ���ڣ�2025-09-01
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
     
*/
#include "DRI_Flash.h"
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
#define Flash_SpaceStartAddr  0x08000000//flash�ռ���ʼ��ַ
#define Flash_SpaceEndAddr    0x082FFFFF//flash�ռ������ַ
//������ʼ��ַ
static const u32 FlashSectorAddr[] = {
     //Bank0----1MB
     0x08000000,//����0��ʼ��ַ--16K
     0x08004000,//����1��ʼ��ַ--16K
     0x08008000,//����2��ʼ��ַ--16K
     0x0800C000,//����3��ʼ��ַ--16K
     0x08010000,//����4��ʼ��ַ--64K
     0x08020000,//����5��ʼ��ַ--128K
     0x08040000,//����6��ʼ��ַ--128K
     0x08060000,//����7��ʼ��ַ--128K
     0x08080000,//����8��ʼ��ַ--128K
     0x080A0000,//����9��ʼ��ַ--128K
     0x080C0000,//����10��ʼ��ַ--128K
     0x080E0000,//����11��ʼ��ַ--128K
     //Bank1----2816KB
     0x08100000,//����12��ʼ��ַ--16K
     0x08104000,//����13��ʼ��ַ--16K
     0x08108000,//����14��ʼ��ַ--16K
     0x0810C000,//����15��ʼ��ַ--16K
     0x08110000,//����16��ʼ��ַ--64K
     0x08120000,//����17��ʼ��ַ--128K
     0x08140000,//����18��ʼ��ַ--128K
     0x08160000,//����19��ʼ��ַ--128K
     0x08180000,//����20��ʼ��ַ--128K
     0x081A0000,//����21��ʼ��ַ--128K
     0x081C0000,//����22��ʼ��ַ--128K
     0x081E0000,//����23��ʼ��ַ--128K
     0x08200000,//����24��ʼ��ַ--256K
     0x08240000,//����25��ʼ��ַ--256K
     0x08280000,//����26��ʼ��ַ--256K
     0x082C0000//����27��ʼ��ַ--256K
};

static const u32 FlashSectorNum[] = {//������
     CTL_SECTOR_NUMBER_0,//����0
     CTL_SECTOR_NUMBER_1,//����1
     CTL_SECTOR_NUMBER_2,//����2
     CTL_SECTOR_NUMBER_3,//����3
     CTL_SECTOR_NUMBER_4,//����4
     CTL_SECTOR_NUMBER_5,//����5
     CTL_SECTOR_NUMBER_6,//����6
     CTL_SECTOR_NUMBER_7,//����7
     CTL_SECTOR_NUMBER_8,//����8
     CTL_SECTOR_NUMBER_9,//����9
     CTL_SECTOR_NUMBER_10,//����10
     CTL_SECTOR_NUMBER_11,//����11
     CTL_SECTOR_NUMBER_12,//����12
     CTL_SECTOR_NUMBER_13,//����13
     CTL_SECTOR_NUMBER_14,//����14
     CTL_SECTOR_NUMBER_15,//����15
     CTL_SECTOR_NUMBER_16,//����16
     CTL_SECTOR_NUMBER_17,//����17
     CTL_SECTOR_NUMBER_18,//����18
     CTL_SECTOR_NUMBER_19,//����19
     CTL_SECTOR_NUMBER_20,//����20
     CTL_SECTOR_NUMBER_21,//����21
     CTL_SECTOR_NUMBER_22,//����22
     CTL_SECTOR_NUMBER_23,//����23
     CTL_SECTOR_NUMBER_24,//����24
     CTL_SECTOR_NUMBER_25,//����25
     CTL_SECTOR_NUMBER_26,//����26
     CTL_SECTOR_NUMBER_27//����27
};//������
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����ڲ�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
static u16 Flash_WriteData(u32 wadd,u8 *wd,u16 wl);
// static void Flash_SectorErase(u32 secaddr);
// static void Flash_SectorProcess(u32 addr,u16 ldata,u16 mfl,u16 rdata);
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ���ϵͳ����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/




/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����û�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* �� �� ��: DRI_Flash_ReadData
* ����������Flash ������ �����ݺ���
*          ֧�������ַ�����С�Ķ�ȡ
* ��ڲ�����
            u32 radd:����ַ
            u8 *rd:���ݴ���׵�ַ
            u16 rl:���ֽ���
* ���ڲ�����
       ����ֵ:ʵ�ʶ�ȡ�ֽ���
        С��0:����ʧ��
* ע������:  
            ��
* ��     ��:
* �޸ļ�¼:
*           2025-09-01 BY:YJX
***************************************************************************/
s32 DRI_Flash_ReadData(u32 radd,u8 *rd,u16 rl)
{
     u8 *rp = (u8 *)radd;
     u16 u16temp;

     if(radd < Flash_SpaceStartAddr || radd > Flash_SpaceEndAddr || (radd + rl) > (Flash_SpaceEndAddr + 1))
     {//Խ����
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
* �� �� ��: DRI_Flash_DirectWriteData
* ����������Flash ������ֱд���ݺ���(������ֱ��д��)
*          ֧�������ַ�����С��д��
* ��ڲ�����
            u32 wadd:д��ַ
            u8 *wd:����Դ�׵�ַ
            u16 wl:д�ֽ���
* ���ڲ�����
       ����ֵ:ʵ��д�ֽ���
        С��0:����ʧ��
* ע������:  
            ������ֱ��д��!!!
* ��   ��:
* �޸ļ�¼:
*           2025-09-01 BY:YJX
***************************************************************************/
s32 DRI_Flash_DirectWriteData(u32 wadd,u8 *wd,u16 wl)
{//
     u8 u8temp,*rp,u8i,u8data[4];
     u16 u16temp,u16wl;

     if(wadd < Flash_SpaceStartAddr || wadd > Flash_SpaceEndAddr || (wadd + wl) > (Flash_SpaceEndAddr + 1))
     {//Խ����
          return -1;
     }

     u16wl = wl;//�ݴ�wl

     if(wl)
     {
          //�����ײ���4�ֽڶ���
          u8temp = (u8)(wadd % 4);
          if(u8temp)
          {//�ײ���4�ֽڶ���
               rp = (u8 *)(wadd - u8temp);//��ǰu8temp���ֽڣ���u8temp������
               for(u8i = 0;u8i < u8temp;u8i++)
               {
                    u8data[u8i] = rp[u8i];
               }
               for(u8i = u8temp;u8i < 4;u8i++)
               {
                    u8data[u8i] = wd[u8i - u8temp];
               }
               //��һ�������Ҷ����4�ֽڽ���д����
               Flash_WriteData((u32)rp,u8data,4);
               //����д���ַ��Դ����ָ�롢д���ֽ���
               u8temp = 4 - u8temp;
               wadd += u8temp;
               wd += u8temp;
               wl -= u8temp;
          }

          //д���м䲿��
          u16temp = Flash_WriteData(wadd,wd,wl);
          wadd += u16temp;
          wd += u16temp;
          wl -= u16temp;

          //����β����4�ֽڶ���
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
               //��һ�������Ҷ����4�ֽڽ���д����
               Flash_WriteData((u32)wadd,u8data,4);
          }
     }

     return u16wl;
}

/// @brief �жϵ�ַ�Ƿ�����ͷ���� �� β����
/// @param addr ���жϵĵ�ַ
/// @return С��0:��ʾ������ 0:��ʾͷ���� ����0:��ʾβ����
s8 DRI_Flash_IsSectorAligned(u32 addr)
{
     u8 u8i,SectorNum = sizeof(FlashSectorAddr)/sizeof(FlashSectorAddr[0]);
     u32 u32temp;

     for(u8i = 0;u8i < SectorNum;u8i++)
     {
          if(addr == FlashSectorAddr[u8i])
          {//����ͷ����
               return 0;
          }
          else 
          {//�ж�β����
               u32temp = Flash_SpaceEndAddr;
               if(u8i < SectorNum - 1)
               {
                    u32temp = FlashSectorAddr[u8i + 1] - 1;
               }
               if(addr == u32temp)
               {//����β����
                    return 1;
               }
          }
     }
     return -1;
}

/// @brief ����eaddr���ڵ����������ĺ���
/// @param eaddr ��Ҫ�����ĵ�ַ
/// @return ��С��0:����ʧ�� ����ֵ��ʵ�ʲ����ֽ��� 
s32 DRI_Flash_EraseSector(u32 eaddr)
{
     u8 u8i,SectorNum = sizeof(FlashSectorAddr)/sizeof(FlashSectorAddr[0]);
     u32 u32temp;
     s32 s32result = -1;

     //��ȡ��ַ���ڵ�������
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
               //����������С  
               s32result = u32temp - FlashSectorAddr[u8i];
               //��������ǰ���Ƚ���
               fmc_unlock(); 
               //��������־
               fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
               //��ʼ��������
               if(FMC_READY != fmc_sector_erase(FlashSectorNum[u8i]))
               {//����ʧ��
                    s32result = -2;
               }
               //����������������
               fmc_lock();
               //�˳�ѭ��
               break;
          }
     }
     return s32result;
}

/***************************************************************************
* �� �� ��: DRI_Flash_Erase
* ����������Flash ������ �ռ��������
* ��ڲ�����
            u32 eaddr��������ʼ��ַ
            u32 esize�������ֽ���
* ���ڲ�����
       ����ֵ:ʵ�ʲ����ֽ���
        С��0:����ʧ��
* ע������:
        �������������ģ����Բ�����ַ�ʹ�С���������������
* ��    ��:
* �޸ļ�¼:
*           2025-09-01 BY:YJX
***************************************************************************/
s32 DRI_Flash_Erase(u32 eaddr,u32 esize)
{
     u32 u32temp,u32len;
     u32 secaddr;
     s32 result = esize;

     if(eaddr < Flash_SpaceStartAddr || eaddr > Flash_SpaceEndAddr || (eaddr + esize) > (Flash_SpaceEndAddr + 1))
     {//Խ����
          return -1;
     }

     //����оƬ������С��һ������С����16K��������256K����ֻ�ܽ�����������������������Ҫ���ݵ�ַ�ʹ�С�����ж�
     //��1�����жϽ�����ַ�Ƿ�Ϊ���������ַ
     u32len = sizeof(FlashSectorAddr) / sizeof(u32);
     secaddr = eaddr + esize;
     for(u32temp = 0;u32temp < u32len;u32temp++)
     {
          if(secaddr == FlashSectorAddr[u32temp])
          {//��ʼ��ַΪ���������ַ
               break;
          }
     }     
     if(u32temp >= u32len)
     {
          if(secaddr != (Flash_SpaceEndAddr + 1))
          {
               return -2;//��ʼ��ַ�������������ַ
          }
     }

     //��2�����ж���ʼ��ַ�Ƿ�Ϊ���������ַ
     u32len = sizeof(FlashSectorAddr) / sizeof(u32);
     secaddr = eaddr;
     for(u32temp = 0;u32temp < u32len;u32temp++)
     {
          if(secaddr == FlashSectorAddr[u32temp])
          {//��ʼ��ַΪ���������ַ
               break;
          }
     }
     if(u32temp >= u32len)
     {
          return -3;//��ʼ��ַ�������������ַ
     }

     //��3������������
     //��������ǰ���Ƚ���
     fmc_unlock(); 
     //��������־
     fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
     //��ʼ��������
     if(FMC_READY != fmc_sector_erase(FlashSectorNum[u32temp]))
     {//����ʧ��
          result = -4;
     }
     //����������������
     fmc_lock();

     return result;
}

/**
 * @brief DRI_Flash_EraseWriteData
 * Flash �����Ͳ�д���ݺ���(�Ȳ�����д��)
 * �����������������ģ����Դ˽ӿڽ���Ҳ��������д��ġ�
 * @param wadd д���ַ
 * @param wd ��д�������׵�ַ
 * @param wl ��д�������ֽ���
 * @return s32 С��0:дʧ�ܣ�����ֵ:ʵ��д���ֽ���
 */
s32 DRI_Flash_EraseWriteData(u32 wadd,u8 *wd,u32 wl)
{
     s32 s32temp;

     if(wadd < Flash_SpaceStartAddr || wadd > Flash_SpaceEndAddr || (wadd + wl) > (Flash_SpaceEndAddr + 1))
     {//Խ����
          return -1;
     }

     if(wl)
     {
     //�Ȳ���
          s32temp = DRI_Flash_Erase(wadd,wl);
          if(s32temp != wl)
          {
               return s32temp;
          }
     //��д��
          return DRI_Flash_DirectWriteData(wadd,wd,wl);
     }
     return wl;
}

/**
 * @brief DRI_Flash_OutCapacity
 * ������ռ��С
 * @return u32 ���ռ��С����λ�ֽ���
 */
u32 DRI_Flash_OutCapacity(void)
{
     return (Flash_SpaceEndAddr - Flash_SpaceStartAddr + 1);
}

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����ڲ�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
//��д��ĵ�ַ������4�ֽڶ���!!!
//����ʵ��д����ֽ���
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

// //����������
// //secaddrΪ������ַ����������������
// static void Flash_SectorErase(u32 secaddr)
// {
//      EFM_Unlock();
//      EFM_SectorErase(secaddr);
//      EFM_Lock();
// }

// /**
//  * @brief 
//  * ����������Ҫ���ڰ���������ʱ�����а�����������Ҫ�ڲ�������д��
//  * @param addr ������ʼ��ַ(Ҫ����������)
//  * @param ldata ����ǰ����ȡ�ֽ���(����Ϊ0)
//  * @param mfl �����в����0xff�ֽ���(����Ϊ0)
//  * @param rdata �����󲿶�ȡ�ֽ���(����Ϊ0)
//  */
// static void Flash_SectorProcess(u32 addr,u16 ldata,u16 mfl,u16 rdata)
// {
//      // u8 buff[Flash_MinSectorSize];
//      // u8 *rp = (u8*)addr;
//      // u16 u16i = 0;

//      // //��������
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
//      // //��������
//      // Flash_SectorErase(addr);//��������
//      // //д��������
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



