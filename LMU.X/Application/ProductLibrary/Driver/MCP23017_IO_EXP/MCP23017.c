/**
 *  @file       MCP23017.c
 *  @brief      Driver for MCP23017 16 bit I/O Expander with I2C Serial Interface
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <stdio.h>

#include "../../ProductLibraryInclude/MCP23017.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------



//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------


const struct MCP23017_INTRFACE_STRUCT MCP23017_Interf =
{
    .Initialize      = &MCP23017__Initialize,
    .Handler5ms      = &MCP23017__Handler5ms,
 
};



//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes the MCP23017 module
  *
  * @param  None
  * @retval None
  * @note	None
  */
void MCP23017__Initialize(void)
{
    
}

/**
  * @brief  MCP23017 module handler. It manages all the module functionalities
  *
  * @param  None
  * @retval None
  * @note	call this function in the task every 5ms
  */
void MCP23017__Handler5ms(void)
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
//static void MCP23017_xxx(void)
//{
// 
//}

