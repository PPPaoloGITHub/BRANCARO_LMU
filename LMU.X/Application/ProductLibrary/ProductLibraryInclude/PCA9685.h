/**
 *  @file		PCA9685.h
 *  @brief      Driver for PCA9685 16 bit PWM I/O Expander with I2C Serial Interface 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __PCA9685_H__
#define __PCA9685_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/i2c_host/i2c1.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================


struct PCA9685_INTRFACE_STRUCT
{
    void (*Initialize)     (void);
    void (*Handler5ms)     (void);

};


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct PCA9685_INTRFACE_STRUCT PCA96857_Interf;

void PCA9685__Initialize(void);
void PCA9685__Handler5ms(void);

#endif /* __PCA9685_H__ */
