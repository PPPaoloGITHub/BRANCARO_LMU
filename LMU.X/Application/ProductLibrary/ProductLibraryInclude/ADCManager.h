/**
 *  @file		ADCManager.h
 *  @brief      This module manages direct ADC acquisitions from dsPIC33 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __ADC_MANAGER_H__
#define __ADC_MANAGER_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/adc/adc1.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================


struct ADC_MANAGER_INTRFACE_STRUCT
{
    void (*Initialize)     (void);
    void (*Handler5ms)     (void);

};


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct ADC_MANAGER_INTRFACE_STRUCT ADCManager_Interf;

void ADCManager__Initialize(void);
void ADCManager__Handler5ms(void);

#endif /* __ADC_MANAGER_H__ */
