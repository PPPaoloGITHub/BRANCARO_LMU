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
static float I_eCB100AValue;
static float I_PWR1Value;
static float T_PWR_BOARDValue;
static float V_GPUValue;
static float I_PWR2Value;
static float V_PWR2Value;
static float V_PWR1Value;
static float V_BATTERYValue;
static float T_LOGIC_BOARDValue;

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static uint16 ADCManager_GetI_eCB100A   (void);
static uint16 ADCManager_GetI_PWR1      (void);
static sint16 ADCManager_GetT_PWRBoard  (void);
static uint16 ADCManager_GetV_GPU       (void);
static uint16 ADCManager_GetI_PWR2      (void);
static uint16 ADCManager_GetV_PWR2      (void);
static uint16 ADCManager_GetV_PWR1      (void);
static uint16 ADCManager_GetV_Battery   (void);
static sint16 ADCManager_GetT_LOGICBoard(void);

const struct ADC_MANAGER_INTRFACE_STRUCT ADCManager_Interf =
{
    .Initialize      = &ADCManager__Initialize,
    .Handler25ms     = &ADCManager__Handler25ms,
    .GetI_eCB100A    = &ADCManager_GetI_eCB100A,    
    .GetI_PWR1       = &ADCManager_GetI_PWR1,      
    .GetT_PWRBoard   = &ADCManager_GetT_PWRBoard,  
    .GetV_GPU        = &ADCManager_GetV_GPU,       
    .GetI_PWR2       = &ADCManager_GetI_PWR2,      
    .GetV_PWR2       = &ADCManager_GetV_PWR2,      
    .GetV_PWR1       = &ADCManager_GetV_PWR1,      
    .GetV_Battery    = &ADCManager_GetV_Battery,   
    .GetT_LOGICBoard = &ADCManager_GetT_LOGICBoard,    
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
    I_eCB100AValue      = 0;
    I_PWR1Value         = 0;
    T_PWR_BOARDValue    = 0;
    V_GPUValue          = 0;
    I_PWR2Value         = 0;
    V_PWR2Value         = 0;
    V_PWR1Value         = 0;
    V_BATTERYValue      = 0;
    T_LOGIC_BOARDValue  = 0;
}

/**
  * @brief  ADCMAnager module handler. It manages all the module functionalities
  *
  * @param  None
  * @retval None
  * @note	call this function in the task every 25ms
  */
void ADCManager__Handler25ms(void)
{
   LSI_FBK_TYPE lsiFbkADC;
 
   // Acquire analog values
   adc->SoftwareTriggerEnable();
   adc->Tasks();
 
   /* Application of LowPass Filter to all acquired analog values
   *  Set respective parameters in the ADCManager_prm.h file
   *
   *  Low Pass filter Parameters: output value, input value, cut frequency
   */
   LPF(I_eCB100AValue,     adc->ConversionResultGet(AN4_IeCB100A),       I_eCB100A_LP_FT);
   LPF(I_PWR1Value,        adc->ConversionResultGet(AN7_I_PWR1),         I_PWR1_LP_FT);
   //LPF(T_PWR_BOARDValue, adc->ConversionResultGet(AN8_T_PWR_BOARD),    T_PWR_BOARD_LP_FT);
   LPF(V_GPUValue,         adc->ConversionResultGet(AN9_V_GPU),          V_GPU_LP_FT);
   LPF(I_PWR2Value,        adc->ConversionResultGet(AN10_I_PWR2),        I_PWR2_LP_FT);
   LPF(V_PWR2Value,        adc->ConversionResultGet(AN11_V_PWR2),        V_PWR2_LP_FT);
   LPF(V_PWR1Value,        adc->ConversionResultGet(AN12_V_PWR1),        V_PWR1_LP_FT);
   LPF(V_BATTERYValue,     adc->ConversionResultGet(AN13_V_BATTERY),     V_BATTERY_LP_FT);
   LPF(T_LOGIC_BOARDValue, adc->ConversionResultGet(AN15_T_LOGIC_BOARD), T_LOGIC_BOARD_LP_FT);
      
   
   /* TODO: Rimuovere questa parte di codice. Le grandezze sono pubblicate su richiesta */
   // public on CAN BUS 
   uint16 tempVar;
   
   lsiFbkADC = CANFBK_Interf.GetLsiFbk(CANFBK_ID_LSI0);
   tempVar = ADCManager_Interf.GetI_eCB100A();
   lsiFbkADC.lsiFbkArray[0] = HIBYTE_WORD(tempVar);
   lsiFbkADC.lsiFbkArray[1] = LOBYTE_WORD(tempVar);
   tempVar = ADCManager_Interf.GetI_PWR1();
   lsiFbkADC.lsiFbkArray[4] = HIBYTE_WORD(tempVar);
   lsiFbkADC.lsiFbkArray[5] = LOBYTE_WORD(tempVar);
   CANFBK_Interf.SetLsiFbk(CANFBK_ID_LSI0, &lsiFbkADC);
   
   lsiFbkADC = CANFBK_Interf.GetLsiFbk(CANFBK_ID_LSI1);
   tempVar = ADCManager_Interf.GetV_GPU();
   lsiFbkADC.lsiFbkArray[2] = HIBYTE_WORD(tempVar);
   lsiFbkADC.lsiFbkArray[3] = LOBYTE_WORD(tempVar);
   tempVar = ADCManager_Interf.GetI_PWR2();
   lsiFbkADC.lsiFbkArray[6] = HIBYTE_WORD(tempVar);
   lsiFbkADC.lsiFbkArray[7] = LOBYTE_WORD(tempVar);
   CANFBK_Interf.SetLsiFbk(CANFBK_ID_LSI1, &lsiFbkADC);
   
   lsiFbkADC = CANFBK_Interf.GetLsiFbk(CANFBK_ID_LSI2);
   tempVar = ADCManager_Interf.GetV_PWR2();
   lsiFbkADC.lsiFbkArray[0] = HIBYTE_WORD(tempVar);
   lsiFbkADC.lsiFbkArray[1] = LOBYTE_WORD((tempVar));
   tempVar = ADCManager_Interf.GetV_PWR1();
   lsiFbkADC.lsiFbkArray[4] = HIBYTE_WORD(tempVar);
   lsiFbkADC.lsiFbkArray[5] = LOBYTE_WORD(tempVar);
   CANFBK_Interf.SetLsiFbk(CANFBK_ID_LSI2, &lsiFbkADC);
   
   lsiFbkADC = CANFBK_Interf.GetLsiFbk(CANFBK_ID_LSI3);
   tempVar = ADCManager_Interf.GetV_Battery();
   lsiFbkADC.lsiFbkArray[2] = HIBYTE_WORD(tempVar);
   lsiFbkADC.lsiFbkArray[3] = LOBYTE_WORD(tempVar);
   tempVar = ADCManager_Interf.GetT_LOGICBoard();
   lsiFbkADC.lsiFbkArray[6] = HIBYTE_WORD(tempVar);
   lsiFbkADC.lsiFbkArray[7] = LOBYTE_WORD(tempVar);
   CANFBK_Interf.SetLsiFbk(CANFBK_ID_LSI3, &lsiFbkADC); 
}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function returns the acquired eCB100A Current value in [A]
  *
  * @param  None
  * @retval eCB100A current in [A]
  * @note	None
  */
static uint16 ADCManager_GetI_eCB100A(void)
{
    uint16 retVal;
    
    if(I_eCB100A_R2 == ADC_INFINITE_VALUE)
    {
        retVal = (uint16)((((I_eCB100AValue * ADC_VOLTAGE) / ADC_STEPS) / I_eCB100A_R_SHUNT) / I_eCB100A_GAIN);
    }
    else
    {
        retVal = (uint16)((((I_eCB100AValue * ADC_VOLTAGE) / ADC_STEPS) * I_eCB100A_DIVIDER / I_eCB100A_R_SHUNT) / I_eCB100A_GAIN);
    }
    
    return (retVal);
}

/**
  * @brief  This function returns the acquired Power1 current value in [A]
  *
  * @param  None
  * @retval Power1 current in [A]
  * @note	None
  */
static uint16 ADCManager_GetI_PWR1(void)
{
    sint16 retVal;
    
    if(I_PWR1_R2 == ADC_INFINITE_VALUE)
    {
        retVal = (uint16)(((I_PWR1Value * ADC_VOLTAGE) / ADC_STEPS - I_PWR1_OFFSET) / I_PWR1_SENSIVITY);
    }
    else
    {
        retVal = (uint16)((((I_PWR1Value * ADC_VOLTAGE) / ADC_STEPS) * I_PWR1_DIVIDER - I_PWR1_OFFSET) / I_PWR1_SENSIVITY);
    }
    
    if(retVal < 0)
    {
        retVal = 0;
    }    
    
    return ((uint16)retVal);   
}

/**
  * @brief  This function returns the acquired Power Board Temperature value in the range [-40 ~ 150°C]
  *
  * @param  None
  * @retval Power Board Temperature in [°C] is multiplied by 10
  * @note	None
  */
static sint16 ADCManager_GetT_PWRBoard(void)
{
    sint16 retVal;
    
    if(T_PWR_BOARD_R2 == ADC_INFINITE_VALUE)
    {
        retVal = (sint16)(((((T_PWR_BOARDValue * ADC_VOLTAGE) / ADC_STEPS) - T_PWR_BOARD_VOFFS) / T_PWR_BOARD_TC) * 10);
    }
    else
    {
        retVal = (sint16)(((((T_PWR_BOARDValue * ADC_VOLTAGE) / ADC_STEPS) * T_PWR_BOARD_DIVIDER  - T_PWR_BOARD_VOFFS) / T_PWR_BOARD_TC) * 10);
    }
    
    return (retVal);
}

/**
  * @brief  This function returns the acquired GPU Voltage value in [V]
  *
  * @param  None
  * @retval GPU Voltage in [V] is multiplied by 10
  * @note	None
  */
static uint16 ADCManager_GetV_GPU(void)
{
    uint16 retVal;
    
    if( V_GPU_R2 == ADC_INFINITE_VALUE)
    {
        retVal = (uint16)(((V_GPUValue * ADC_VOLTAGE) / ADC_STEPS) * 10);
    }
    else
    {
        retVal = (uint16)(((V_GPUValue * ADC_VOLTAGE) / ADC_STEPS) * V_GPU_DIVIDER * 10);
    }
    
    return (retVal);
}

/**
  * @brief  This function returns the acquired Power2 Current value in [A]
  *
  * @param  None
  * @retval Power2 current in [A]
  * @note	None
  */
static uint16 ADCManager_GetI_PWR2(void)
{
    sint16 retVal;
    
    if(I_PWR2_R2 == ADC_INFINITE_VALUE)
    {
        retVal = (uint16)(((I_PWR2Value * ADC_VOLTAGE) / ADC_STEPS - I_PWR2_OFFSET) / I_PWR2_SENSIVITY);
    }
    else
    {
        retVal = (uint16)((((I_PWR2Value * ADC_VOLTAGE) / ADC_STEPS) * I_PWR2_DIVIDER - I_PWR2_OFFSET)/ I_PWR2_SENSIVITY);
    }
    
    if(retVal < 0)
    {
        retVal = 0;
    } 
    
    return ((uint16)retVal);
}

/**
  * @brief  This function returns the acquired Power2 voltage value in [V]
  *
  * @param  None
  * @retval Power2 voltage in [V] multiplied by 10
  * @note	None
  */
static uint16 ADCManager_GetV_PWR2(void)
{
    uint16 retVal;
    
    if( V_PWR2_R2 == ADC_INFINITE_VALUE)
    {
        retVal = (uint16)(((V_PWR2Value * ADC_VOLTAGE) / ADC_STEPS) * 10);
    }
    else
    {
        retVal = (uint16)(((V_PWR2Value * ADC_VOLTAGE) / ADC_STEPS) * V_PWR2_DIVIDER * 10);
    }
    
    return (retVal);
}

/**
  * @brief  This function returns the acquired Power1 voltage value in [V]
  *
  * @param  None
  * @retval Power1 voltage in [V] multiplied by 10
  * @note	None
  */
static uint16 ADCManager_GetV_PWR1(void)
{
    uint16 retVal;
    
    if( V_PWR1_R2 == ADC_INFINITE_VALUE)
    {
        retVal = (uint16)(((V_PWR1Value * ADC_VOLTAGE) / ADC_STEPS) * 10);
    }
    else
    {
        retVal = (uint16)(((V_PWR1Value * ADC_VOLTAGE) / ADC_STEPS) * V_PWR1_DIVIDER * 10);
    }
    
    return (retVal);
}

/**
  * @brief  This function returns the acquired Power1 voltage value in [V] 
  *
  * @param  None
  * @retval Power1 voltage in [V] multiplied by 10
  * @note	None
  */
static uint16 ADCManager_GetV_Battery(void)
{
    uint16 retVal;
    
    if( V_BATTERY_R2 == ADC_INFINITE_VALUE)
    {
        retVal = (uint16)(((V_BATTERYValue * ADC_VOLTAGE) / ADC_STEPS) * 10);
    }
    else
    {
        retVal = (uint16)(((V_BATTERYValue * ADC_VOLTAGE) / ADC_STEPS) * V_BATTERY_DIVIDER * 10);
    }
    
    return (retVal);
}

/**
  * @brief  This function returns the acquired Logic Board Temperature value in the range [-40 ~ 150°C] 
  *
  * @param  None
  * @retval Logic Board Temperature in [°C] multiplied by 10
  * @note	None
  */
static sint16 ADCManager_GetT_LOGICBoard(void)
{
    sint16 retVal;
    
    if(T_LOGIC_BOARD_R2 == ADC_INFINITE_VALUE)
    {
        retVal = (sint16)(((((T_LOGIC_BOARDValue * ADC_VOLTAGE) / ADC_STEPS) - T_LOGIC_BOARD_VOFFS) / T_LOGIC_BOARD_TC) * 10);
    }
    else
    {
        retVal = (sint16)(((((T_LOGIC_BOARDValue * ADC_VOLTAGE) / ADC_STEPS) * T_LOGIC_BOARD_DIVIDER  - T_LOGIC_BOARD_VOFFS) / T_LOGIC_BOARD_TC) * 10);
    }
    
    return (retVal);
}

