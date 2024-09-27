/**
 *  @file       MCP23017.c
 *  @brief      Driver for ADS7128 12-bit, 8-channel Sampling ADC with I2C Serial Interface
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <stdio.h>

#include "../../ProductLibraryInclude/ADS7128.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------



//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------


const struct ADS7128_INTRFACE_STRUCT ADS7128_Interf =
{
    .Initialize      = &ADS7128__Initialize,
    .Handler5ms      = &ADS7128__Handler5ms,
 
};



//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes the ADS7128 module
  *
  * @param  None
  * @retval None
  * @note	None
  */
void ADS7128__Initialize(void)
{
    
}

/**
  * @brief  ADS7128 module handler. It manages all the module functionalities
  *
  * @param  None
  * @retval None
  * @note	call this function in the task every 5ms
  */
void ADS7128__Handler5ms(void)
{
   
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
//static void ADS7128_xxx(void)
//{
// 
//}

