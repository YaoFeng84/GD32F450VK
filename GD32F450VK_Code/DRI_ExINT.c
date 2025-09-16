/********************************************************************************************************************************************
*                                                                                                                                           *
*              ---------------------------------������ģ����޸ļ�¼��-----------------------------------------                             *
*                                                                                                                                           *
********************************************************************************************************************************************/
/**********************************************
 * ���ݣ�
 * ���ڣ�2025-09-02
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
     ��1����֧��16���ⲿ�ж�ͨ��
     ��2���������ء��½��ء�˫���ء��͵�ƽ�����ִ���
     ��3�����жϺţ�ExIntNum�����ɺ�����ģ���ظ���
     ��4�������źţ�pinn����ͬʱ�����һ��Ϊ����֮ǰ��Ч��
     

ʹ�����ӣ�PD3���ŵ��ⲿ�ж�����
     ExIntCnfType exintconfig;
     
     exintconfig.cbfp = exint3;
     exintconfig.ExIntNum = Int002_IRQn;
     exintconfig.pinn = GP03;
     exintconfig.portn = GPORTD;
     exintconfig.pri = 15;
     exintconfig.tm = ITFallEdge;
     DRI_ExINT_Config(&exintconfig);


     void exint3(void)
     {
          DRI_GPIO_OUT_Turn(GPORTB,GP09);
     }
*/
#include "DRI_ExINT.h"
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
#define GPIO_PERIPH(PortN)    (GPIOA + (PortN * 0x00000400U))
#define GPIO_PIN(PinN)        BIT(PinN)

//
static void (*ExINT_CallBackF00)(void) = NULLFP;
static void (*ExINT_CallBackF01)(void) = NULLFP;
static void (*ExINT_CallBackF02)(void) = NULLFP;
static void (*ExINT_CallBackF03)(void) = NULLFP;
static void (*ExINT_CallBackF04)(void) = NULLFP;
static void (*ExINT_CallBackF05)(void) = NULLFP;
static void (*ExINT_CallBackF06)(void) = NULLFP;
static void (*ExINT_CallBackF07)(void) = NULLFP;
static void (*ExINT_CallBackF08)(void) = NULLFP;
static void (*ExINT_CallBackF09)(void) = NULLFP;
static void (*ExINT_CallBackF10)(void) = NULLFP;
static void (*ExINT_CallBackF11)(void) = NULLFP;
static void (*ExINT_CallBackF12)(void) = NULLFP;
static void (*ExINT_CallBackF13)(void) = NULLFP;
static void (*ExINT_CallBackF14)(void) = NULLFP;
static void (*ExINT_CallBackF15)(void) = NULLFP;
//
// typedef void (*ExINT_CBFP)(void);
// static ExINT_CBFP PA_ExCBFP[] = {ExINT_CallBackFPA001,ExINT_CallBackFPA011};
/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����ڲ�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/
// static void ExINT_CBF00(void);
// static void ExINT_CBF01(void);
// static void ExINT_CBF02(void);
// static void ExINT_CBF03(void);
// static void ExINT_CBF04(void);
// static void ExINT_CBF05(void);
// static void ExINT_CBF06(void);
// static void ExINT_CBF07(void);
// static void ExINT_CBF08(void);
// static void ExINT_CBF09(void);
// static void ExINT_CBF10(void);
// static void ExINT_CBF11(void);
// static void ExINT_CBF12(void);
// static void ExINT_CBF13(void);
// static void ExINT_CBF14(void);
// static void ExINT_CBF15(void);

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
* �� �� ��: DRI_ExINT_Config
* �����������ⲿ�����ж����ú���
* ��ڲ�����
            ExIntCnfType *eict�����ýṹ��ָ��
* ���ڲ�����
            -1:��ʾ����ʧ��
            0:��ʾ���óɹ�
* ע������:  
            PA2,PB2,PC2,PD2,PE2���������ͬ�Ĳ���ͬʱ���֡�
* ��     ��:
* �޸ļ�¼ :
*           2025-09-02 BY:YJX
***************************************************************************/
s8 DRI_ExINT_Config(ExIntCnfType *eict)
{
     u8 exit_port,exit_pin;
     exti_line_enum linex;
     exti_trig_type_enum trig_type;//�жϴ�������
     IRQn_Type nvic_irq;//�ж�������    
     // void (*icbfp)(void);//�жϻص�����ָ��
     //
     
     switch(eict->portn)
     {
          case GPORTA:
               rcu_periph_clock_enable(RCU_GPIOA);
               exit_port = EXTI_SOURCE_GPIOA;
               nvic_irq = EXTI0_IRQn;
               break;
          case GPORTB:
               rcu_periph_clock_enable(RCU_GPIOB);
               exit_port = EXTI_SOURCE_GPIOB;
               nvic_irq = EXTI1_IRQn;
               break;
          case GPORTC:
               rcu_periph_clock_enable(RCU_GPIOC);
               exit_port = EXTI_SOURCE_GPIOC;
               nvic_irq = EXTI2_IRQn;
               break;
          case GPORTD:
               rcu_periph_clock_enable(RCU_GPIOD);
               exit_port = EXTI_SOURCE_GPIOD;
               nvic_irq = EXTI3_IRQn;
               break;
          case GPORTE:
               rcu_periph_clock_enable(RCU_GPIOE);
               exit_port = EXTI_SOURCE_GPIOE;
               nvic_irq = EXTI4_IRQn;
               break;
          default:
               return -1;
     }
     
     nvic_irq = EXTI0_IRQn;//��ʱȫ��ʹ��0���жϣ���������PA��0��PB��1��PC��2��PD��3��PE��4���ж�

     switch(eict->pinn)
     {
          case GP00:
               exit_pin = EXTI_SOURCE_PIN0;
               linex = EXTI_0;
               // icbfp = ExINT_CBF00;
               ExINT_CallBackF00 = eict->cbfp;
               break;
          case GP01:
               exit_pin = EXTI_SOURCE_PIN1;
               linex = EXTI_1;
               // icbfp = ExINT_CBF01;
               ExINT_CallBackF01 = eict->cbfp;
               break;
          case GP02:
               exit_pin = EXTI_SOURCE_PIN2;
               linex = EXTI_2;
               // icbfp = ExINT_CBF02;
               ExINT_CallBackF02 = eict->cbfp;
               break;
          case GP03:
               exit_pin = EXTI_SOURCE_PIN3;
               linex = EXTI_3;
               // icbfp = ExINT_CBF03;
               ExINT_CallBackF03 = eict->cbfp;
               break;
          case GP04:
               exit_pin = EXTI_SOURCE_PIN4;
               linex = EXTI_4;
               // icbfp = ExINT_CBF04;
               ExINT_CallBackF04 = eict->cbfp;
               break;
          case GP05:
               exit_pin = EXTI_SOURCE_PIN5;
               linex = EXTI_5;
               // icbfp = ExINT_CBF05;
               ExINT_CallBackF05 = eict->cbfp;
               break;
          case GP06:
               exit_pin = EXTI_SOURCE_PIN6;
               linex = EXTI_6;
               // icbfp = ExINT_CBF06;
               ExINT_CallBackF06 = eict->cbfp;
               break;
          case GP07:
               exit_pin = EXTI_SOURCE_PIN7;
               linex = EXTI_7;
               // icbfp = ExINT_CBF07;
               ExINT_CallBackF07 = eict->cbfp;
               break;
          case GP08:
               exit_pin = EXTI_SOURCE_PIN8;
               linex = EXTI_8;
               // icbfp = ExINT_CBF08;
               ExINT_CallBackF08 = eict->cbfp;
               break;
          case GP09:
               exit_pin = EXTI_SOURCE_PIN9;
               linex = EXTI_9;
               // icbfp = ExINT_CBF09;
               ExINT_CallBackF09 = eict->cbfp;
               break;
          case GP10:
               exit_pin = EXTI_SOURCE_PIN10;
               linex = EXTI_10;
               // icbfp = ExINT_CBF10;
               ExINT_CallBackF10 = eict->cbfp;
               break;
          case GP11:
               exit_pin = EXTI_SOURCE_PIN11;
               linex = EXTI_11;
               // icbfp = ExINT_CBF11;
               ExINT_CallBackF11 = eict->cbfp;
               break;
          case GP12:
               exit_pin = EXTI_SOURCE_PIN12;
               linex = EXTI_12;
               // icbfp = ExINT_CBF12;
               ExINT_CallBackF12 = eict->cbfp;
               break;
          case GP13:
               exit_pin = EXTI_SOURCE_PIN13;
               linex = EXTI_13;
               // icbfp = ExINT_CBF13;
               ExINT_CallBackF13 = eict->cbfp;
               break;
          case GP14:
               exit_pin = EXTI_SOURCE_PIN14;
               linex = EXTI_14;
               // icbfp = ExINT_CBF14;
               ExINT_CallBackF14 = eict->cbfp;
               break;
          case GP15:
               exit_pin = EXTI_SOURCE_PIN15;
               linex = EXTI_15;
               // icbfp = ExINT_CBF15;
               ExINT_CallBackF15 = eict->cbfp;
               break;
          default:
               return -2;
     }
     //
     switch(eict->tm)
     {
          case ITFallEdge:
               trig_type = EXTI_TRIG_FALLING;
               break;
          case ITRiseEdge:
               trig_type = EXTI_TRIG_RISING;
               break;
          case ITBothEdg:
               trig_type = EXTI_TRIG_BOTH;
               break;
          default:  
               return -3;
     }
     //
     gpio_mode_set(GPIO_PERIPH(eict->portn), GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN(eict->pinn));
     //
     rcu_periph_clock_enable(RCU_SYSCFG);//ʹ��SYSCFGʱ��
     syscfg_exti_line_config(exit_port, exit_pin);
     //
     exti_init(linex, EXTI_INTERRUPT, trig_type);
     exti_interrupt_flag_clear(linex);

     // 
     NVIC_ClearPendingIRQ(nvic_irq);//��������־     
     NVIC_SetPriority(nvic_irq, eict->pri);//�����ж����ȼ�     
     NVIC_EnableIRQ(nvic_irq);//ʹ��NVIC�ж�
     //nvic_irq_enable(nvic_irq, 2U, 0U); 

     return 0;
}

void EXTI0_IRQHandler(void)
{
     if(RESET != exti_interrupt_flag_get(EXTI_0)) 
     {
          ExINT_CallBackF00();
          exti_interrupt_flag_clear(EXTI_0);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_1)) 
     {
          ExINT_CallBackF01();
          exti_interrupt_flag_clear(EXTI_1);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_2)) 
     {
          ExINT_CallBackF02();
          exti_interrupt_flag_clear(EXTI_2);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_3)) 
     {
          ExINT_CallBackF03();
          exti_interrupt_flag_clear(EXTI_3);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_4)) 
     {
          ExINT_CallBackF04();
          exti_interrupt_flag_clear(EXTI_4);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_5)) 
     {
          ExINT_CallBackF05();
          exti_interrupt_flag_clear(EXTI_5);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_6)) 
     {
          ExINT_CallBackF06();
          exti_interrupt_flag_clear(EXTI_6);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_7)) 
     {
          ExINT_CallBackF07();
          exti_interrupt_flag_clear(EXTI_7);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_8)) 
     {
          ExINT_CallBackF08();
          exti_interrupt_flag_clear(EXTI_8);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_9)) 
     {
          ExINT_CallBackF09();
          exti_interrupt_flag_clear(EXTI_9);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_10)) 
     {
          ExINT_CallBackF10();
          exti_interrupt_flag_clear(EXTI_10);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_11)) 
     {
          ExINT_CallBackF11();
          exti_interrupt_flag_clear(EXTI_11);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_12)) 
     {
          ExINT_CallBackF12();
          exti_interrupt_flag_clear(EXTI_12);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_13)) 
     {
          ExINT_CallBackF13();
          exti_interrupt_flag_clear(EXTI_13);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_14)) 
     {
          ExINT_CallBackF14();
          exti_interrupt_flag_clear(EXTI_14);
     }
     if(RESET != exti_interrupt_flag_get(EXTI_15)) 
     {
          ExINT_CallBackF15();
          exti_interrupt_flag_clear(EXTI_15);
     }
}

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ----------------------------------������ģ����ڲ�����������------------------------------------                          *
*                                                                                                                                           *
********************************************************************************************************************************************/



