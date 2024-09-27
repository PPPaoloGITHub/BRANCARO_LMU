/**
 *  @file		MCP23017.h
 *  @brief      Driver for MCP23017 16 bit I/O Expander with I2C Serial Interface 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __MCP23017_H__
#define __MCP23017_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/i2c_host/i2c1.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================


struct MCP23017_INTRFACE_STRUCT
{
    void (*Initialize)     (void);
    void (*Handler5ms)     (void);

};


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct MCP23017_INTRFACE_STRUCT MCP23017_Interf;

void MCP23017__Initialize(void);
void MCP23017__Handler5ms(void);

#endif /* __MCP23017_H__ */
