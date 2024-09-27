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
static LSI_FBK_TYPE lsiFbk[CANFBK_MAX_LSI_IDs];


//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------

static void         SetLsiFeedback (CANFBK_IDs_LSI_TYPE lsiID, LSI_FBK_TYPE *lsiFeedback);
static LSI_FBK_TYPE GetLsiFeedback (CANFBK_IDs_LSI_TYPE lsiID);

const struct FBK_INTERFACE_STRUCT CANFBK_Interf =
{
    .Initialize     = &CANFBK__Initialize,
    .Handler5ms     = &CANFBK__Handler5ms,
    .SETLsiFbk      = &SetLsiFeedback,
	.GETLsiFbk      = &GetLsiFeedback,
};

static uint8        GetIDEnumValue(CANFBK_IDs_LSI_TYPE lsiID);

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
    uint8 k, n;
    
    // Initialize lsiFbk structure for each LSI message
    for(n = 0; n <= CANFBK_MAX_LSI_IDs; n++)
    {
        for(k = 0; k <= CAN_PAYLOAD; k++)
        {
            lsiFbk[n].lsiFbkArray[k] = 0;
        }
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
    uint8 k;
    
    /* Transmission of CAN HeartBeat messages on CAN_BUS */
    CAN_RMP_Interf.HeartBeat();
 
    if(TIMERS__MsGetStatus(MS_TIMER_CANFBK_PERIOD) == TIMERS_COMPLETED)
    {
        TIMERS__MsSet(MS_TIMER_CANFBK_PERIOD, CAN_FEEDBACK_PERIOD);

        // TODO: implement functionality to transmitt more different CAN messages with a list of CAN ID...
        /* Transmit LSI Feedback */
        for(k = 0; k <= CANFBK_MAX_LSI_IDs; k++)
        {    
            CAN_RMP_Interf.Send(CANFBK_ID_LSI1, DLC_8, lsiFbk[k].lsiFbkArray);
        }
    }
}

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  Set Load and Sensors for Feedback CAN
  *
  * @param  None
  * @retval None
  */
static void SetLsiFeedback(CANFBK_IDs_LSI_TYPE lsiID, LSI_FBK_TYPE *lsiFeedback)
{
	uint8 k;
    uint8 lsiEnumValue;
    
    lsiEnumValue = GetIDEnumValue(lsiID);
    
	for(k = 0; k < CAN_PAYLOAD; k++)
	{
		lsiFbk[lsiEnumValue].lsiFbkArray[k] = lsiFeedback->lsiFbkArray[k];
	}
}

/**
  * @brief  Get Load and Sensors from Feedback CAN
  *
  * @param  lsiID: LSI ID value from enum CANFBK_IDs_LSI_TYPE
  * @retval Request Load and Sensors Feedback CAN
  */
static LSI_FBK_TYPE GetLsiFeedback(CANFBK_IDs_LSI_TYPE lsiID)
{
    uint8 lsiEnumValue;
    
    lsiEnumValue = GetIDEnumValue(lsiID);
    
	return (lsiFbk[lsiEnumValue]);
}


/**
  * @brief  Get numerical value of LSI IDs available
  *
  * @param  lsiID: LSI ID value from enum CANFBK_IDs_LSI_TYPE
  * @retval progressive numerical value of the LSI ID in the enum CANFBK_IDs_LSI_TYPE
  */
static uint8 GetIDEnumValue(CANFBK_IDs_LSI_TYPE lsiID)
{
    uint8 retVal;
    
    switch(lsiID)
    {
        default:
            retVal = 0xFF;      // If invalid LSI ID returns invalid progressive numerical value
            break;
        
        case CANFBK_ID_LSI0:
            retVal = 0;
            break;
            
        case CANFBK_ID_LSI1:
            retVal = 1;
            break;
            
        case CANFBK_ID_LSI2:
            retVal = 2;
            break;
            
        case CANFBK_ID_LSI3:
            retVal = 3;
            break;
            
        case CANFBK_ID_LSI4:
            retVal = 4;
            break;
            
        case CANFBK_ID_LSI5:
            retVal = 5;
            break;
    }
    
    return (retVal);
}
