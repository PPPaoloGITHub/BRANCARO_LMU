/**
 *  @file       FeedbackCAN.c
 *  @brief      This file manages feedback CAN
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "../../../ProductLibrary/ProductLibraryInclude/Timers.h"
#include "../../../ProductLibrary/ProductLibraryInclude/CANRecvdMsgParser.h"
#include "../../AppSpecificInclude/CANFeedback.h"

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
static LSI_FBK_TYPE lsiFbk;

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------

static void         SetLsiFeedback (LSI_FBK_TYPE *lsiFeedback);
static LSI_FBK_TYPE GetLsiFeedback (void);

const struct FBK_INTERFACE_STRUCT CANFBK_Interf =
{
    .Initialize     = &CANFBK__Initialize,
    .Handler5ms     = &CANFBK__Handler5ms,
    .SETLsiFbk      = &SetLsiFeedback,
	.GETLsiFbk      = &GetLsiFeedback,
};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes the CAN feedback module
  *
  * @param  None
  * @retval None
  * @note	None
  */
void CANFBK__Initialize(void)
{
    uint8 k;
    
    // Initialize lsiFbk structure
    for(k = 0; k <= CAN_PAYLOAD; k++)
    {
        lsiFbk.lsiFbkArray[k] = 0;
    }
    
    TIMERS__MsSet(MS_TIMER_CANFBK_PERIOD, CAN_FEEDBACK_PERIOD);
}

/**
  * @brief  Feedback CAN handler
  *
  * @param  None
  * @retval None
  * @note	Call this function in the task every 5ms 
  */
void CANFBK__Handler5ms (void)
{
    /* Transmission of CAN HeartBeat messages on CAN_BUS */
    CAN_RMP_Interf.HeartBeat();
 
    if(TIMERS__MsGetStatus(MS_TIMER_CANFBK_PERIOD) == TIMERS_COMPLETED)
    {
        TIMERS__MsSet(MS_TIMER_CANFBK_PERIOD, CAN_FEEDBACK_PERIOD);
    
        /* Only for Test. REMOVE IT!!!*/
        LSI_FBK_TYPE lsiData;
        for(uint8 k = 0; k <= CAN_PAYLOAD; k++)
        {
            lsiData.lsiFbkArray[k] = 0;
        }
        lsiData.lsiFbkArray[0] = 0x55;
        lsiData.NotUsed8 = 1;
        lsiData.NotUsed9 = 1;
        lsiData.lsiFbkArray[4] = 0xAA;
        /* END Only for Test. REMOVE IT!!!*/

        /* Transmit LSI Feedback */
        CAN_RMP_Interf.Send(CANFBK_ID_LSI1, DLC_8, lsiData.lsiFbkArray);
    }
}

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  Set Load and Sensors for Feedback CAN
  *
  * @param  None
  * @retval Feedback CAN interface methods
  */
static void SetLsiFeedback (LSI_FBK_TYPE *lsiFeedback)
{
	uint8 k;

	for(k = 0; k < CAN_PAYLOAD; k++)
	{
		lsiFbk.lsiFbkArray[k] = lsiFeedback->lsiFbkArray[k];
	}
}

/**
  * @brief  Get Load and Sensors for Feedback CAN
  *
  * @param  None
  * @retval Feedback CAN interface methods
  */
static LSI_FBK_TYPE GetLsiFeedback (void)
{
	return (lsiFbk);
}
