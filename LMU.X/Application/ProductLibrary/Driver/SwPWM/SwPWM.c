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
typedef struct
{
    uint8  dutyCycle;       // [0 - 100] Duty cycle in percentage
    uint16 frequency;       // [1 - 100Hz] Frequency in Hz
    uint16 period;          // [250us] Calculated period
    uint16 onTime;          // Calculated ON time in the duty cycle
    uint16 counter;         // actual counter 
//    ACTIVE_TYPE active;     // Channel status: ACTIVE / INACTIVE
} SWPWM_CHANNEL_TYPE;
static SWPWM_CHANNEL_TYPE pwmChs[SWPWM_MAX_CHANNELS];          // PWM channels array


//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static bool SWPWM_SetChannel      (SWPWM_CHS_ENUM_TYPE channel, uint8 dutyCycle, uint16 frequency);
static bool SWPWM_UpdateDutyCycle (SWPWM_CHS_ENUM_TYPE channel, uint8 dutyCycle);
static bool SWPWM_UpdateFrequency (SWPWM_CHS_ENUM_TYPE channel, uint16 frequency);

const struct SWPWM_INTRFACE_STRUCT SWPWM_Interf =
{
    .Initialize      = &SWPWM__Initialize,
    .Handler250us    = &SWPWM__Handler250us,
    .SetChannel      = &SWPWM_SetChannel ,
    .UpdateDutyCycle = &SWPWM_UpdateDutyCycle,
    .UpdateFrequency = &SWPWM_UpdateFrequency,
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
    uint8 k;
    
    for (k = 0; k < SWPWM_MAX_CHANNELS; k++)
    {
        pwmChs[k].dutyCycle = 0;
        pwmChs[k].frequency = 0;
        pwmChs[k].period    = 0;
        pwmChs[k].onTime    = 0;
        pwmChs[k].counter   = 0;
//        pwmChs[k].active    = INACTIVE;
    }
}

/**
  * @brief  Software PWM module handler. It manages all the module functionalities
  * 
  * @param  None
  * @retval None
  * @note	call this function in the task every 250us
  */
void SWPWM__Handler250us(void)
{
    uint8  k;
    
    for(k = 0; k < SWPWM_MAX_CHANNELS; k++)
    {
//        if(pwmChs[k].active ==  ACTIVE)
//        {
            pwmChs[k].counter++;
            if(pwmChs[k].counter >= pwmChs[k].period)
            {
                pwmChs[k].counter = 0;          // restart the cycle
            }

            // Update pin status
            if (pwmChs[k].counter < pwmChs[k].onTime)
            {
                // Set pin high
                switch(k)
                {
                    default:
                    break;
                    
                    case 0:
                        SWPWM_WRITE_HIGH_CH0;
                    break;
                    
                    case 1:
                        SWPWM_WRITE_HIGH_CH1;
                    break;
                }
            }
            else
            {
                // Set pin low
                switch(k)
                {
                    default:
                    break;
                    
                    case 0:
                        SWPWM_WRITE_LOW_CH0;
                    break;
                    
                    case 1:
                        SWPWM_WRITE_LOW_CH1;
                    break;
                }
             }
//        }
    }
}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief     This function sets a PWM channel
  * 
  * @param[in] channel:   [0 - SWPWM_MAX_CHANNELS-1] PWM channel number
  * @param[in] dutyCycle: duty cycle value in range [0 - 100]
  * @param[in] frequency: frequency value in range [1 - 100Hz] 
  * @retval    TRUE: valid parameters insertion; FALSE: invalid parameters 
  * @note	   None
  */
static bool SWPWM_SetChannel(SWPWM_CHS_ENUM_TYPE channel, uint8 dutyCycle, uint16 frequency)
{
    bool retVal = TRUE;
    
    if( (channel   >= SWPWM_MAX_CHANNELS) ||
        (dutyCycle >  SWPWM_MAX_DUTY_CYCLE) ||
        (frequency <  SWPWM_MIN_PWM_FREQ) ||
        (frequency >  SWPWM_MAX_PWM_FREQ) )
    {
        retVal = FALSE;      // Invalid parameters
    }

    pwmChs[channel].dutyCycle = dutyCycle;
    pwmChs[channel].frequency = frequency;
    pwmChs[channel].period    = 4000 / frequency;     // period in 250us
    pwmChs[channel].counter   = 0;
//    pwmChs[channel].active    = ACTIVE;
     
    pwmChs[channel].onTime = (pwmChs[channel].period * dutyCycle) / 100;        // Calculate On time in the Duty Cycle
    
    return (retVal);
}

/**
  * @brief     This function updates the duty cycle for a PWM channel
  * 
  * @param[in] channel:   [0 - SWPWM_MAX_CHANNELS-1] PWM channel number
  * @param[in] dutyCycle: duty cycle value in range [0 - 100]
  * @retval    TRUE: valid parameters insertion; FALSE: invalid parameters
  * @note	   None
  */
static bool SWPWM_UpdateDutyCycle(SWPWM_CHS_ENUM_TYPE channel, uint8 dutyCycle)
{
    bool retVal = TRUE;
    
    if( (channel >= SWPWM_MAX_CHANNELS) ||
        (dutyCycle > SWPWM_MAX_DUTY_CYCLE) )
    {
        retVal = FALSE;
    }
    
    pwmChs[channel].dutyCycle = dutyCycle;
    pwmChs[channel].onTime = (pwmChs[channel].period * dutyCycle) / 100;        // Calculate On time in the Duty Cycle
    
    
    return (retVal);
}

/**
  * @brief     This function updates the frequency for a PWM channel
  * 
  * @param[in] channel:   [0 - SWPWM_MAX_CHANNELS-1] PWM channel number
  * @param[in] frequency: frequency value in range [1 - 100Hz] 
  * @retval    TRUE: valid parameters insertion; FALSE: invalid parameters
  * @note	   None
  */
static bool SWPWM_UpdateFrequency(SWPWM_CHS_ENUM_TYPE channel, uint16 frequency)
{
    bool retVal = TRUE;
    
    if (channel >= SWPWM_MAX_CHANNELS || frequency == 0)
    {
        retVal = FALSE;
    }
    pwmChs[channel].frequency = frequency;
    pwmChs[channel].period    = 4000 / frequency;    // calculation of the period
    pwmChs[channel].counter   = 0; 
    pwmChs[channel].onTime = (pwmChs[channel].period * pwmChs[channel].dutyCycle) / 100;        // Calculate On time in the Duty Cycle 
     
    return (retVal);
}