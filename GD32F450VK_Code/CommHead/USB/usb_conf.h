#ifndef __USB_CONF_H
#define __USB_CONF_H

//#include "stdlib.h"
#include "gd32f4xx.h"
//#include "gd32f450v_start.h"

/* USB Core and PHY interface configuration */

/* USB FS/HS PHY CONFIGURATION */

#ifdef USE_USB_FS
    #define USB_FS_CORE
#endif /* USE_USB_FS */

#ifdef USE_USB_HS
    #define USB_HS_CORE
#endif /* USE_USB_HS */

/* USB FIFO size config */

#ifdef USB_FS_CORE
    #define RX_FIFO_FS_SIZE                         128
    #define TX0_FIFO_FS_SIZE                        64
    #define TX1_FIFO_FS_SIZE                        128
    #define TX2_FIFO_FS_SIZE                        0
    #define TX3_FIFO_FS_SIZE                        0

    #define USBFS_SOF_OUTPUT                        0
    #define USBFS_LOW_POWER                         0
#endif /* USB_FS_CORE */

#ifdef USB_HS_CORE
    #define RX_FIFO_HS_SIZE                          512
    #define TX0_FIFO_HS_SIZE                         128
    #define TX1_FIFO_HS_SIZE                         384
    #define TX2_FIFO_HS_SIZE                         0
    #define TX3_FIFO_HS_SIZE                         0
    #define TX4_FIFO_HS_SIZE                         0
    #define TX5_FIFO_HS_SIZE                         0

    #ifdef USE_ULPI_PHY
        #define USB_ULPI_PHY_ENABLED
    #endif

    #ifdef USE_EMBEDDED_PHY
        #define USB_EMBEDDED_PHY_ENABLED
    #endif

//    #define USB_HS_INTERNAL_DMA_ENABLED
//    #define USB_HS_DEDICATED_EP1_ENABLED

    #define USBHS_SOF_OUTPUT                        0
    #define USBHS_LOW_POWER                         0
#endif /* USB_HS_CORE */

//#define VBUS_SENSING_ENABLED

//#define USE_HOST_MODE
#define USE_DEVICE_MODE
//#define USE_OTG_MODE

#ifndef USB_FS_CORE
    #ifndef USB_HS_CORE
        #error  "USB_HS_CORE or USB_FS_CORE should be defined!"
    #endif
#endif

#ifndef USE_DEVICE_MODE
    #ifndef USE_HOST_MODE
        #error  "USE_DEVICE_MODE or USE_HOST_MODE should be defined!"
    #endif
#endif

#ifndef USE_USB_HS
    #ifndef USE_USB_FS
        #error  "USE_USB_HS or USE_USB_FS should be defined!"
    #endif
#endif

/* all variables and data structures during the transaction process should be 4-bytes aligned */

#ifdef USB_HS_INTERNAL_DMA_ENABLED
    #if defined (__GNUC__)         /* GNU Compiler */
        #define __ALIGN_END __attribute__ ((aligned (4)))
        #define __ALIGN_BEGIN
    #else
        #define __ALIGN_END

        #if defined (__CC_ARM)     /* ARM Compiler */
            #define __ALIGN_BEGIN __align(4)  
        #elif defined (__ICCARM__) /* IAR Compiler */
            #define __ALIGN_BEGIN
        #elif defined (__TASKING__)/* TASKING Compiler */
            #define __ALIGN_BEGIN __align(4) 
        #endif /* __CC_ARM */  
    #endif /* __GNUC__ */ 
#else
    #define __ALIGN_BEGIN
    #define __ALIGN_END
#endif /* USB_HS_INTERNAL_DMA_ENABLED */

/* __packed keyword used to decrease the data type alignment to 1-byte */
#if defined (__GNUC__)       /* GNU Compiler */
    #ifndef __packed
        #define __packed __attribute__ ((__packed__))
    #endif
#elif defined (__TASKING__)    /* TASKING Compiler */
    #define __packed __unaligned
#endif /* __CC_ARM */

#endif /* __USB_CONF_H */
