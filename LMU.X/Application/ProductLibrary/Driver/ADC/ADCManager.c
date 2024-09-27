/**
 *  @file       ADCManager.c
 *  @brief      This module manages direct ADC acquisitions from dsPIC33
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <stdio.h>
#include "../../../AppSpecific/AppSpecificInclude/CANFeedback.h"

#include "../../ProductLibraryInclude/ADCManager.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
const struct ADC_INTERFACE *adc = &ADC1;

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------



//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------


const struct ADC_MANAGER_INTRFACE_STRUCT ADCManager_Interf =
{
    .Initialize      = &ADCManager__Initialize,
    .Handler5ms      = &ADCManager__Handler5ms,
 
};



//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes the ADCManager module
  *
  * @param  None
  * @retval None
  * @note	None
  */
void ADCManager__Initialize(void)
{
    
}

/**
  * @brief  ADCMAnager module handler. It manages all the module functionalities
  *
  * @param  None
  * @retval None
  * @note	call this function in the task every 5ms
  */
void ADCManager__Handler5ms(void)
{
   LSI_FBK_TYPE lsiFbkADC;
   uint16 adcResult[ADC_MAX_CHANNELS];
   uint8  k;
   
   adc->SoftwareTriggerEnable();
   adc->Tasks();
   
   // transfer all acquired ADCs into adcResult array 
   for(k = 0; k <= ADC_MAX_CHANNELS; k++)
   {
       adcResult[k] = adc->ConversionResultGet(k);
   }
   
   // public on CAN BUS the 
   lsiFbkADC = CANFBK_Interf.GETLsiFbk(CANFBK_ID_LSI0);
   lsiFbkADC.lsiFbkArray[0] = HIBYTE_WORD(adcResult[AN4_IeCB100A]);
   lsiFbkADC.lsiFbkArray[1] = LOBYTE_WORD(adcResult[AN4_IeCB100A]);
   
//  lsiFbkADC.lsiFbkArray[4] = HIBYTE_WORD(adcResult[AN7_I_PWR1]);
//   lsiFbkADC.lsiFbkArray[5] = LOBYTE_WORD(adcResult[AN7_I_PWR1]);
   CANFBK_Interf.SETLsiFbk(CANFBK_ID_LSI0, &lsiFbkADC);
   
}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief   
  *
  * @param  
  * @retval 
  * @note	None
  */
//static void MCP23017_xxx(void)
//{
// 
//}

