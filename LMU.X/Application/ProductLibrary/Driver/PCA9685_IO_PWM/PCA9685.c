/**
 *  @file       PCA9685.c
 *  @brief      Driver for PCA9685 16 bit PWM I/O Expander with I2C Serial Interface
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <stdio.h>

#include "../../ProductLibraryInclude/PCA9685.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------



//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------


const struct PCA9685_INTRFACE_STRUCT PCA9685_Interf =
{
    .Initialize      = &PCA9685__Initialize,
    .Handler5ms      = &PCA9685__Handler5ms,
 
};



//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes the PCA9685 module
  *
  * @param  None
  * @retval None
  * @note	None
  */
void PCA9685__Initialize(void)
{
    
}

/**
  * @brief  PCA9685 module handler. It manages all the module functionalities
  *
  * @param  None
  * @retval None
  * @note	call this function in the task every 5ms
  */
void PCA9685__Handler5ms(void)
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
//static void PCA9685_xxx(void)
//{
// 
//}

