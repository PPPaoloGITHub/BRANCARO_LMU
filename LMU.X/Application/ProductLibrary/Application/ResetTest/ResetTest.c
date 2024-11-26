/**
 *  @file       ResetTest.c
 *  @brief      Reset and Test functionality
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <stdbool.h>
#include "../../ProductLibraryInclude/Timers.h"

#include "../../ProductLibraryInclude/ResetTest.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
typedef enum
{
    RST_CMD_IDLE        = 0,
    RST_CMD_EXECUTION,        
    RST_CMD_END,
}RST_CMD_STATUS_TYPE;

static bool isResetCmdEnabled = FALSE;



//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static void RESET_TEST_ResetCmdHandler(void);

static void RESET_TEST_ResetCmd(void);
static void RESET_TEST_SelfTestCmd(void);

const struct RESET_TEST_INTRFACE_STRUCT RESET_TEST_Interf =
{
    .Initialize  = &RESET_TEST__Initialize,
    .Handler25ms = &RESET_TEST__Handler25ms,
    .ResetCmd    = &RESET_TEST_ResetCmd,
    .SelfTestCmd = &RESET_TEST_SelfTestCmd,
};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes Reset_Test module
   *
  * @param  None
  * @retval None
  * @note	None
  */
void RESET_TEST__Initialize(void)
{
    /* HW Reset pin for I/O EXPANDER and I/O PWM EXPANDER */
    DO_RESET_SetLow();
    
    TIMERS__MsSet(MS_TIMER_RESET_CMD, RESET_CMD_TIME_1s);
    TIMERS__MsSet(MS_TIMER_SELF_TEST_CMD, TEST_CMD_TIME_2s);
    
    
}

/**
  * @brief  Reset_Test module handler. It manages all the module functionalities
  * 
  * @param  None
  * @retval None
  * @note	call this function in the task every 25ms
  */
void RESET_TEST__Handler25ms(void)
{
    RESET_TEST_ResetCmdHandler();
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
static void RESET_TEST_ResetCmd(void)
{
    isResetCmdEnabled = TRUE;
}

/**
  * @brief  
  * 
  * @param  None
  * @retval None
  * @note	None
  */
static void RESET_TEST_ResetCmdHandler(void)
{
    static RST_CMD_STATUS_TYPE rstCmdStatus = RST_CMD_IDLE;
    
    switch (rstCmdStatus)
    {
        default:
        case RST_CMD_IDLE:
            if(isResetCmdEnabled == TRUE)
            {
                isResetCmdEnabled = FALSE;
                TIMERS__MsSet(MS_TIMER_RESET_CMD, RESET_CMD_TIME_1s);
                
                //Imposto a 1 il pin I/O EXP eCB_RESET
                rstCmdStatus = RST_CMD_EXECUTION;
            }
        break;
        
        case RST_CMD_EXECUTION:
            if(TIMERS__MsGetStatus(MS_TIMER_RESET_CMD) == TIMERS_COMPLETED)
            {
                //Imposto a 0 il pin I/O EXP eCB_RESET
                
                // Notifico che il RestCmd è finito per inviare CAN feedback...
                rstCmdStatus = RST_CMD_END;
            }
        break;
        
        case RST_CMD_END:
            rstCmdStatus = RST_CMD_IDLE;
        break;
            
    }
}

/**
  * @brief  
  * 
  * @param  None
  * @retval None
  * @note	None
  */
static void RESET_TEST_SelfTestCmd(void)
{
    
}
