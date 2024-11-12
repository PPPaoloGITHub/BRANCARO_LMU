/**
 *  @file		PCA9685_prm.h
 *  @brief      Configuration file for Driver for PCA9685 16 bit PWM I/O Expander with I2C Serial Interface 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __PCA9685_PRM_H__
#define __PCA9685_PRM_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/i2c_host/i2c1.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
#define PCA9685_CLOCK_FREQ                 400     // [KHz] SCL I2C Clock Frequency set as Default @400KHz
                                                   // Currently this #define is not used. It's here only for reference!

#define PCA9685_DEFAULT_PWM_FREQUENCY       24     // [Hz] Default PWM frequency value. Set it in the range [24Hz - 1526Hz]

#define PCA9685_NUMBER_OF_DEVICES_ON_I2C     1     // Indicate how many PCA9685 devices are connected on the I2C


/* ***************** PORTABILITY MODULE: ***************** */
/* I2C functions to import from microcontroller I2C module  */
#define PCA9685_I2CWrite(memoryAddress, pData, dataLength)   I2C1_Host.Write(memoryAddress, pData, dataLength)
#define PCA9685_I2CRead(memoryAddress, pData, dataLengtht)   I2C1_Host.Read(memoryAddress, pData, dataLengtht)
#define PCA9685_I2CIsBusy()                                  I2C1_Host.IsBusy()        // true = Busy; false = Not Busy   


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================


#endif /* __PCA9685_PRM_H__ */
