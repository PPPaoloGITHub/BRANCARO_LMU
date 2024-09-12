/**
 *  @file		LED_OnBoard.h
 *  @brief      On board leds driver
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __LED_ONBOARD_H__
#define __LED_ONBOARD_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/system/pins.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================

typedef enum
{
	LED_ONB_GREEN = 1,
	LED_ONB_RED = 2,
	LED_ONB_MAX,
} LED_ONB_INSTANCE_TYPE;

struct LED_ONB_INTRFACE_STRUCT
{
    void (*Initialize)      (void);
    void (*Handler25ms)     (void);
    void (*TurnOff)         (LED_ONB_INSTANCE_TYPE led);
    void (*TurnOn)          (LED_ONB_INSTANCE_TYPE led);
    void (*Toggle)          (LED_ONB_INSTANCE_TYPE led);
};


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct LED_ONB_INTRFACE_STRUCT LED_ONB_Interf;
// Use the following line in the module that use this interface:
// const struct LED_ONB_INTRFACE_STRUCT *LED_ONB_Interface = &LED_ONB_Interf;

void LED_ONB__Initialize(void);
void LED_ONB__Handler25ms(void);

#endif /* __LED_ONBOARD_H__ */
