/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    19-March-2012
  * @brief   USB host HID mouse/keyboard class demo main file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "usb_bsp.h"
#include "usbh_core.h"
#include "usbh_usr.h"
#include "usbh_hid_core.h"

/** @addtogroup USBH_USER
* @{
*/

/** @defgroup USBH_USR_MAIN
* @brief This file is the HID demo main file
* @{
*/ 

/** @defgroup USBH_USR_MAIN_Private_TypesDefinitions
* @{
*/ 
/**
* @}
*/ 

/** @defgroup USBH_USR_MAIN_Private_Defines
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_MAIN_Private_Macros
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_MAIN_Private_Variables
* @{
*/
#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE           USB_OTG_Core __ALIGN_END ;

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USBH_HOST                     USB_Host __ALIGN_END ;

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE           USB_OTG_FS_Core __ALIGN_END ;

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USBH_HOST                     USB_FS_Host __ALIGN_END ;
/**
* @}
*/ 


/** @defgroup USBH_USR_MAIN_Private_FunctionPrototypes
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_MAIN_Private_Functions
* @{
*/ 


/**
* @brief  Main routine for HID mouse / keyboard class application
* @param  None
* @retval int
*/
int main(void)
{
  __IO uint32_t i = 0;
  __IO uint32_t cc_tot = 0;
  __IO uint32_t cc_cnt = 0;
  __IO uint32_t cc_max = 0;


  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk ; // enable the cycle counter  

  /*!< At this stage the microcontroller clock setting is already configured, 
  this is done through SystemInit() function which is called from startup
  file (startup_stm32fxxx_xx.s) before to branch to application main.
  To reconfigure the default setting of SystemInit() function, refer to
  system_stm32fxxx.c file
  */  

  /* Init Host Library */
#ifdef USE_USB_OTG_HS
  USBH_Init(&USB_OTG_Core, 
            USB_OTG_HS_CORE_ID,
            &USB_Host,
            &HID_cb, 
            &USR_Callbacks);
#endif

  /* Init FS Core */
#ifdef USE_USB_OTG_FS
  USBH_Init(&USB_OTG_FS_Core, 
            USB_OTG_FS_CORE_ID,
            &USB_FS_Host,
            &HID_cb, 
            &USR_Callbacks);
#endif

  STM_EVAL_LEDOff(LED_Blue); // added by "STM32"
  STM_EVAL_LEDOff(LED_Red);  // added by "STM32"
  STM_EVAL_LEDOff(LED_Green);  // added by "STM32"
  STM_EVAL_LEDOff(LED_Orange);  // added by "STM32"
  
  /* Initialize User Button */
  	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

  while (1)
  {
    uint32_t cc = DWT->CYCCNT;
    /* Host Task handler */
    #ifdef USE_USB_OTG_HS
    USBH_Process(&USB_OTG_Core, &USB_Host);
    #endif
    #ifdef USE_USB_OTG_FS
    USBH_Process(&USB_OTG_FS_Core, &USB_FS_Host);
    #endif
    cc = DWT->CYCCNT - cc;

    // discard init routines, that is first seconds 
    if (cc_cnt > 1000) {
      if (cc > cc_max) cc_max = cc;
      cc_tot = cc_tot + cc;
    }
    cc_cnt++;

    // 3 ms delayish? copied from delay code in usb_bsp.c
   
    __IO uint32_t count = 0;
    const uint32_t utime = (168000 * 3 / 7);
    do
    {
      if ( ++count > utime )
      {
        break ;
      }
    }
    while (1);
    
    /*
    if (i++ == 0xC0000)
    {
      //STM_EVAL_LEDToggle(LED_Red);
      //STM_EVAL_LEDToggle(LED_Green);
      //STM_EVAL_LEDToggle(LED_Orange);
      i = 0;
    } 
    */     
  }
}


#ifdef USE_FULL_ASSERT
/**
* @brief  assert_failed
*         Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  File: pointer to the source file name
* @param  Line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line
  number,ex: printf("Wrong parameters value: file %s on line %d\r\n", 
  file, line) */
  
  /* Infinite loop */
  while (1)
  {}
}

#endif


/**
* @}
*/ 

/**
* @}
*/ 

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
