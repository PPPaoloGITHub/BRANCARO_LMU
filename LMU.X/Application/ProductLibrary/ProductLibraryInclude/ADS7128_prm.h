/**
 *  @file		ADS7128.h
 *  @brief      Configuration file for Driver for ADS7128 12-bit, 8-channel Sampling ADC with I2C Serial Interface 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __ADS7128_PRM_H__
#define __ADS7128_PRM_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/i2c_host/i2c1.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
#define ADS7128_CLOCK_FREQ                 400     // [KHz] SCL I2C Clock Frequency set as Default @400KHz
                                                   // Currently this #define is not used. It's here only for reference!

#define ADS7128_NUMBER_OF_DEVICES_ON_I2C     6     // Indicate how many ADS7128 devices are connected on the I2C


/* ***************** PORTABILITY MODULE: ***************** */
/* I2C functions to import from microcontroller I2C module  */
#define ADS7128_I2CWrite(memoryAddress, pData, dataLength)   I2C1_Host.Write(memoryAddress, pData, dataLength)
#define ADS7128_I2CRead(memoryAddress, pData, dataLengtht)   I2C1_Host.Read(memoryAddress, pData, dataLengtht)
#define ADS7128_I2CIsBusy()                                  I2C1_Host.IsBusy()        // true = Busy; false = Not Busy 


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================


#endif /* __ADS7128_PRM_H__ */
