/**
 *  @file		MCP23017_prm.h
 *  @brief      Configuration file for Driver MCP23017 16 bit I/O Expander with I2C Serial Interface 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __MCP23017_PRM_H__
#define __MCP23017_PRM_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/i2c_host/i2c1.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
#define MCP23017_CLOCK_FREQ                 400     // [KHz] SCL I2C Clock Frequency set as Default @400KHz
                                                    // Currently this #define is not used. It's here only for reference!

#define MCP23017_NUMBER_OF_DEVICES_ON_I2C   6       // Indicate how many MCP23017 devices are connected on the I2C


/* ***************** PORTABILITY MODULE: ***************** */
/* I2C functions to import from microcontroller I2C module  */
#define MCP23017_I2CWrite(memoryAddress, pData, dataLength)   I2C1_Host.Write(memoryAddress, pData, dataLength)
#define MCP23017_I2CRead(memoryAddress, pData, dataLengtht)   I2C1_Host.Read(memoryAddress, pData, dataLengtht)
#define MCP23017_I2CIsBusy()                                  I2C1_Host.IsBusy()        // true = Busy; false = Not Busy   

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================


#endif /* __MCP23017_PRM_H__ */