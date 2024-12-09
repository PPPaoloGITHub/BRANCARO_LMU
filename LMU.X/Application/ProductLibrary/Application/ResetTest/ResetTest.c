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
#include "../../ProductLibraryInclude/CANRecvdMsgParser.h"
#include "../../ProductLibraryInclude/MCP23017.h"

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
static bool isSelfTestCmdEnabled = FALSE;


//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static void RESET_TEST_ResetCmdHandler(void);
static void RESET_TEST_SelfTestCmdHandler(void);

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
    RESET_TEST_SelfTestCmdHandler();
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
static void RESET_TEST_SelfTestCmd(void)
{
   isSelfTestCmdEnabled = TRUE; 
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
    uint8 txBuff[CAN_MAX_PAYLOAD];
    uint8 k;
    uint32 msgID;
    
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
    
    switch (rstCmdStatus)
    {
        default:
        case RST_CMD_IDLE:
            if(isResetCmdEnabled == TRUE)
            {
                isResetCmdEnabled = FALSE;
                TIMERS__MsSet(MS_TIMER_RESET_CMD, RESET_CMD_TIME_1s);
                
                //Set the I/O EXP eCB_RESET pin
                MCP23017_Interf.WritePin(IO_EXP2_I2C_ADDR, MCP23017_PORTA, PP_OUT_RESET, TRUE);
                rstCmdStatus = RST_CMD_EXECUTION;
            }
        break;
        
        case RST_CMD_EXECUTION:
            if(TIMERS__MsGetStatus(MS_TIMER_RESET_CMD) == TIMERS_COMPLETED)
            {
                //Reset the I/O EXP eCB_RESET pin
                MCP23017_Interf.WritePin(IO_EXP2_I2C_ADDR, MCP23017_PORTA, PP_OUT_RESET, FALSE);
                
                // Published Reset eCB Completed
                msgID = RESET_CMD_ID | (uint32)CAN_RMP_Interf.GetLMUun()<<16 | CAN_STATUS<<4 | CAN_ASYNC_PUBLISH;
                txBuff[BYTE0] = CAN_RESET_COMPLETED;
                
                CAN_RMP_Interf.Send(msgID, CAN_DLC_DEFAULT, txBuff);
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
static void RESET_TEST_SelfTestCmdHandler(void)
{
    
    //TIMERS__MsSet(MS_TIMER_SELF_TEST_CMD, TEST_CMD_TIME_2s);
    
}
