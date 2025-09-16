cmake_minimum_required(VERSION 3.10)
 
#=========================================== 以下工具链配置编译器信息 ==========================
 
set(ARM_TOOLCHAIN_PATH "F:/YF/MyTools/MyBin/gcc-arm-none-eabi-10.3-2021.10-win32/bin")
set(CMAKE_C_COMPILER "${ARM_TOOLCHAIN_PATH}/arm-none-eabi-gcc.exe" CACHE INTERNAL "C Compiler")
set(CMAKE_CXX_COMPILER "${ARM_TOOLCHAIN_PATH}/arm-none-eabi-g++.exe" CACHE INTERNAL "C++ Compiler")
set(CMAKE_ASM_COMPILER "${ARM_TOOLCHAIN_PATH}/arm-none-eabi-gcc.exe" CACHE INTERNAL "ASM Compiler")
set(CMAKE_OBJCOPY "${ARM_TOOLCHAIN_PATH}/arm-none-eabi-objcopy.exe")
set(CMAKE_SIZE "${ARM_TOOLCHAIN_PATH}/arm-none-eabi-size.exe")
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_ASM_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
 
#=========================================== 以下项目配置信息 ==========================
 
set(PROJECT_NAME GD32F450VK)
project(${PROJECT_NAME} LANGUAGES C ASM)
 
#----------------------------------------------- 以下配置的编译文件信息和输出路径信息有关 --------------------------------------------------------------------------------------------------
 
 
# - - - -这是设置输出路径
set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/./bin")
 
 
# - - - -这是设置头文件路径
set(INC_DIR 
"${CMAKE_CURRENT_SOURCE_DIR}/../../../MyCodeLib"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommHead"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommHead/CMSIS"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommHead/Peripherals"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommHead/USB"
)
 
 
# - - - -这是设置源文件
set(SRC_LIST 
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/DRI_CLK.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/DRI_ComDriver.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/DRI_ExINT.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/DRI_Flash.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/DRI_GPIO.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/DRI_RCU.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/DRI_Systick.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/DRI_USARTn.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/DRI_USB.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/DRI_CAN.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/system_gd32f4xx.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_adc.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_can.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_crc.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_ctc.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_dac.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_dbg.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_dci.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_dma.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_enet.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_exmc.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_exti.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_fmc.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_fwdgt.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_gpio.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_i2c.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_ipa.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_iref.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_misc.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_pmu.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_rcu.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_rtc.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_sdio.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_spi.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_syscfg.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_timer.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_tli.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_trng.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_usart.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/Peripherals/gd32f4xx_wwdgt.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/USB/drv_usb_core.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/USB/drv_usb_dev.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/USB/drv_usbd_int.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/USB/usbd_core.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/USB/usbd_enum.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../GD32F450VK_Code/CommSrc/USB/usbd_transc.c"
)
 
 
# - - - -这是设置库文件
set(LIB_LIST 
)
 
 
# - - - - - - - - - - - - - 整理编译前执行的命令 - - - - - - - - - - - - - - - - - - - -
 
set(BUILD_BEFORE 
)
 
 
## - - - - - - - - - - - - - 整理编译后执行的命令 - - - - - - - - - - - - - - - - - - - -
 
set(BUILD_AFTER 
)
 
 
#----------------------------------------------- 以下配置和芯片平台有关 --------------------------------------------------------------------------------------------------
 
set(COMMON_COMPILE_FLAGS 
-mcpu=cortex-m4
-mthumb
-specs=nosys.specs
-Wall
-DGD32F450
-DUSE_DDL_DRIVER
-DUSE_USB_FS
)
 
set(LINK_SCRIPT 
)
set(COMMON_LINK_FLAGS 
-mcpu=cortex-m4
-mthumb
-specs=nosys.specs
-Wall
-DGD32F450
-DUSE_DDL_DRIVER
-DUSE_USB_FS
-T${LINK_SCRIPT}
-Wl,-Map=${OUTPUT_DIR}/${PROJECT_NAME}.map
)
 
#----------------------------------------------- 以下配置一般都会有 --------------------------------------------------------------------------------------------------
 
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
 
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})
 
set_target_properties(${PROJECT_NAME} PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
PREFIX ""
)
 
target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_FLAGS})
 
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_LIST})
 
 
# - - - - - - - - - - - - - 开始编译前执行的命令 - - - - - - - - - - - - - - - - - - - -
 
set(STAMP_FILE "${CMAKE_CURRENT_BINARY_DIR}/before_build.stamp")
add_custom_command(
OUTPUT ${STAMP_FILE}
COMMAND ${CMAKE_COMMAND} -E touch ${STAMP_FILE}
COMMAND ${BUILD_BEFORE}
COMMAND ${CMAKE_COMMAND} -E remove -f ${STAMP_FILE}
VERBATIM
)
add_custom_target(
run_before_build
DEPENDS ${STAMP_FILE}
)
add_dependencies(${PROJECT_NAME} run_before_build)
 
# - - - - - - - - - - - - - 开始编译后执行的命令 - - - - - - - - - - - - - - - - - - - -
 
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E echo "===== Starting post-build steps ====="
COMMAND ${CMAKE_COMMAND} -E echo "Process User file... "
COMMAND "${BUILD_AFTER}"
COMMENT "Process SUCCESS !!!!!!!!!!!!!"
)
