/**
 *  @file		SwPWM.h
 *  @brief      Software PWM functionality 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __SWPWM_H__
#define __SWPWM_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/system/pins.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================

struct SWPWM_INTRFACE_STRUCT
{
    void (*Initialize) (void);
    void (*Handler1ms) (void);

};


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct SWPWM_INTRFACE_STRUCT SWPWM_Interf;

void SWPWM__Initialize(void);
void SWPWM__Handler1ms(void);

#endif /* __SWPWM_H__ */
