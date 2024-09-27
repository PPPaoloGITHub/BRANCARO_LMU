/**
 *  @file		ADS7128.h
 *  @brief      Driver for ADS7128 12-bit, 8-channel Sampling ADC with I2C Serial Interface 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __ADS7128_H__
#define __ADS7128_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/i2c_host/i2c1.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================


struct ADS7128_INTRFACE_STRUCT
{
    void (*Initialize)     (void);
    void (*Handler5ms)     (void);

};


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct ADS7128_INTRFACE_STRUCT ADS7128_Interf;

void ADS7128__Initialize(void);
void ADS7128__Handler5ms(void);

#endif /* __ADS7128_H__ */
