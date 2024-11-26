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


/* Pins name */
typedef enum
{
    ADS7128_CH0 = 0,
    ADS7128_CH1,
    ADS7128_CH2,
    ADS7128_CH3,
    ADS7128_CH4,
    ADS7128_CH5,
    ADS7128_CH6,
    ADS7128_CH7,
    ADS7128_MAX_CHANNELS = 8,        
} ADS7128_CHANNEL_TYPE;

/* ADC EXPANDER 1 PIN DECLARATION */
typedef enum
{
    AIN_PP_OUT_17_SENSE = ADS7128_CH3,
    AIN_PP_OUT_20_SENSE = ADS7128_CH0,
    AIN_PP_OUT_21_SENSE = ADS7128_CH1,
    AIN_PP_OUT_22_SENSE = ADS7128_CH2,
    AIN_PP_OUT_25_SENSE = ADS7128_CH4,
    AIN_PP_OUT_29_SENSE = ADS7128_CH5,
    AIN_PP_OUT_30_SENSE = ADS7128_CH6,    
} ADS7128_ADC_EXP1_PIN_NAME_TYPE;

/* ADC EXPANDER 2 PIN DECLARATION */
typedef enum
{
    AIN_PP_OUT_18_SENSE = ADS7128_CH3,
    AIN_PP_OUT_19_SENSE = ADS7128_CH0,
    AIN_PP_OUT_23_SENSE = ADS7128_CH5,
    AIN_PP_OUT_24_SENSE = ADS7128_CH4,
    AIN_PP_OUT_26_SENSE = ADS7128_CH6,
    AIN_PP_OUT_27_SENSE = ADS7128_CH2,
    AIN_PP_OUT_28_SENSE = ADS7128_CH1,
} ADS7128_ADC_EXP2_PIN_NAME_TYPE;

/* ADC EXPANDER 3 PIN DECLARATION */
typedef enum
{
    AIN_PP_OUT_1_SENSE  = ADS7128_CH4,
    AIN_PP_OUT_13_SENSE = ADS7128_CH0,
    AIN_PP_OUT_14_SENSE = ADS7128_CH1,
    AIN_PP_OUT_31_SENSE = ADS7128_CH2,
    AIN_PP_OUT_8_SENSE  = ADS7128_CH5,  
} ADS7128_ADC_EXP3_PIN_NAME_TYPE;

/* ADC EXPANDER 4 PIN DECLARATION */
typedef enum
{
    AIN_PP_OUT_10_SENSE = ADS7128_CH5,
    AIN_PP_OUT_15_SENSE = ADS7128_CH1,
    AIN_PP_OUT_16_SENSE = ADS7128_CH0,
    AIN_PP_OUT_3_SENSE  = ADS7128_CH3,
    AIN_PP_OUT_6_SENSE  = ADS7128_CH2,
} ADS7128_ADC_EXP4_PIN_NAME_TYPE;

/* ADC EXPANDER 5 PIN DECLARATION */
typedef enum
{
    AIN_PP_OUT_12_SENSE = ADS7128_CH4,
    AIN_PP_OUT_32_SENSE = ADS7128_CH0,
    AIN_PP_OUT_33_SENSE = ADS7128_CH1,
    AIN_PP_OUT_36_SENSE = ADS7128_CH2,
    AIN_PP_OUT_9_SENSE  = ADS7128_CH5,    
} ADS7128_ADC_EXP5_PIN_NAME_TYPE;

/* ADC EXPANDER 6 PIN DECLARATION */
typedef enum
{
    AIN_PP_OUT_11_SENSE = ADS7128_CH5,
    AIN_PP_OUT_2_SENSE  = ADS7128_CH4,
    AIN_PP_OUT_34_SENSE = ADS7128_CH1,
    AIN_PP_OUT_35_SENSE = ADS7128_CH0,
    AIN_PP_OUT_4_SENSE  = ADS7128_CH3,
    AIN_PP_OUT_7_SENSE  = ADS7128_CH2,
} ADS7128_ADC_EXP6_PIN_NAME_TYPE;


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================


#endif /* __ADS7128_PRM_H__ */
