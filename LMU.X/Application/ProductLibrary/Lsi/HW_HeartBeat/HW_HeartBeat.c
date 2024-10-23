/**
 *  @file       HW_HearBeat.c
 *  @brief      Hardware HeartBeat driver
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "../../ProductLibraryInclude/Timers.h"

#include "../../ProductLibraryInclude/HW_HeartBeat.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
#define HW_HEARTBEAT_PERIOD     200     // [ms] HW HeartBeat period
#define HW_HEARTBEAT_PULSE      100     // [ms] pulse duration

HW_HEARTBEAT_STATUS_TYPE heartBeatStatus;

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static HW_HEARTBEAT_STATUS_TYPE HW_HEARTBEAT_GetStatus(void);


const struct HW_HEARTBEAT_INTRFACE_STRUCT HW_HEARTBEAT_Interf =
{
    .Initialize      = &HW_HEARTBEAT__Initialize,
    .Handler25ms     = &HW_HEARTBEAT__Handler25ms,
    .GetStatus       = &HW_HEARTBEAT_GetStatus,
};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes HW_HEARTBEAT module
   *
  * @param  None
  * @retval None
  * @note	None
  */
void HW_HEARTBEAT__Initialize(void)
{
    /* Initialized CONFIRM_MAINTENANCE pin low to stay in HW_HEARTBEAT_NORMAL_OPERATION */
    DO_CONFIRM_MAINTENANCE_SetLow();
    
    /* Initialized heartbeat status as HW_HEARTBEAT_NORMAL_OPERATION */
    heartBeatStatus = HW_HEARTBEAT_NORMAL_OPERATION;
    
    /* Initialized heartbeat period */
    TIMERS__MsSet(MS_TIMER_HW_HEARBEAT, HW_HEARTBEAT_PERIOD);
}

/**
  * @brief  Hardware HeartBeat module handler. It manages all the module functionalities
  * 
  * @param  None
  * @retval None
  * @note	call this function in the task every 25ms
  */
void HW_HEARTBEAT__Handler25ms(void)
{
    if(DI_MAINTENANCE_GetValue() == FALSE)
    {
        /* Confirm maintenance pin as low: pulse heartbeat on DO_HEARTBEAT pin ensures the NORMAL OPERATION */
        DO_CONFIRM_MAINTENANCE_SetLow();
        heartBeatStatus = HW_HEARTBEAT_NORMAL_OPERATION;
        
        /* Here we are in NORMAL OPERATION STATUS: HW HeartBeat have to be generated with a pulse on DO_HEARTBEAT pin every 200ms */
        /* Heartbeat pulse implementation: it pulses 100ms ON and 100ms OFF on a 200ms period */
        if(TIMERS__MsGetTime(MS_TIMER_HW_HEARBEAT) <= HW_HEARTBEAT_PULSE)
        {
            DO_HEARTBEAT_SetHigh();
        }
        else
        {
            DO_HEARTBEAT_SetLow();
        }
    
        if(TIMERS__MsGetStatus(MS_TIMER_HW_HEARBEAT) == TIMERS_COMPLETED)
        {
            TIMERS__MsSet(MS_TIMER_HW_HEARBEAT, HW_HEARTBEAT_PERIOD);
        }
    }
    else
    {
        /* Here we are in MAINTENANCE OPERATION STATUS: set flag to go in MAINTENANCE OPERATION */
        
        /* Confirm maintenance pin as high to pass in MAINTENANCE OPERATION */
        DO_CONFIRM_MAINTENANCE_SetHigh();
        heartBeatStatus = HW_HEARTBEAT_MAINTENANCE_OPERATION;
    }
}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  Hardware Heartbeat get status function. It gives back the Hw Heartbeat status
  * 
  * @param  None
  * @retval None
  * @note	None
  */
static HW_HEARTBEAT_STATUS_TYPE HW_HEARTBEAT_GetStatus(void)
{
    return (heartBeatStatus);
}
