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
#include "ADCManager_prm.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
struct ADC_MANAGER_INTRFACE_STRUCT
{
    void   (*Initialize)     (void);
    void   (*Handler25ms)     (void);
    uint16 (*GetI_eCB100A)   (void);
    uint16 (*GetI_PWR1)      (void);
    sint16 (*GetT_PWRBoard)  (void);
    uint16 (*GetV_GPU)       (void);
    uint16 (*GetI_PWR2)      (void);
    uint16 (*GetV_PWR2)      (void);
    uint16 (*GetV_PWR1)      (void);
    uint16 (*GetV_Battery)   (void);
    sint16 (*GetT_LOGICBoard)(void);
};


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct ADC_MANAGER_INTRFACE_STRUCT ADCManager_Interf;

void ADCManager__Initialize(void);
void ADCManager__Handler25ms(void);

#endif /* __ADC_MANAGER_H__ */
