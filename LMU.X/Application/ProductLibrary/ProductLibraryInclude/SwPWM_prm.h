/**
 *  @file		SwPWM_prm.h
 *  @brief      Configuration file for Software PWMmodule
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __SWPWM_PRM_H__
#define __SWPWM_PRM_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/system/pins.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
#define SWPWM_MAX_DUTY_CYCLE   100            // Maximum Duty Cycle value 
#define SWPWM_MIN_PWM_FREQ       1            // [Hz] Minimum frequeency value
#define SWPWM_MAX_PWM_FREQ     100            // [Hz] Maximum frequeency value

typedef enum
{
    SWPWM_PGD_OUT1  = 0,
    SWPWM_PGD_OUT2,        
    SWPWM_MAX_CHANNELS = 2,                   // Maxium PWM channels
}SWPWM_CHS_ENUM_TYPE;

#define SWPWM_WRITE_HIGH_CH0   DO_PGD_OUT1_SetHigh()
#define SWPWM_WRITE_LOW_CH0    DO_PGD_OUT1_SetLow()

#define SWPWM_WRITE_HIGH_CH1   DO_PGD_OUT2_SetHigh()
#define SWPWM_WRITE_LOW_CH1    DO_PGD_OUT2_SetLow()

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================


#endif /* __SWPWM_PRM_H__ */
