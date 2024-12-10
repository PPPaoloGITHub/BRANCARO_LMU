/**
 *  @file       SwPWM.c
 *  @brief      Software PWM functionality
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <stdbool.h>

#include "../../ProductLibraryInclude/SwPWM.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------



//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static void SWPWM_yyy(void);


const struct SWPWM_INTRFACE_STRUCT SWPWM_Interf =
{
    .Initialize  = &SWPWM__Initialize,
    .Handler1ms  = &SWPWM__Handler1ms,
 
};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes Software PWM module
   *
  * @param  None
  * @retval None
  * @note	None
  */
void SWPWM__Initialize(void)
{

}

/**
  * @brief  Software PWM module handler. It manages all the module functionalities
  * 
  * @param  None
  * @retval None
  * @note	call this function in the task every 1ms
  */
void SWPWM__Handler1ms(void)
{
 
}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  
  * 
  * @param  None
  * @retval None
  * @note	None
  */
static void SWPWM_yyy(void)
{
    
}


