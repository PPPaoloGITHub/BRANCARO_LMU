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

/* Pins name */
typedef enum
{
    GPA0 = 0,
    GPA1,
    GPA2,
    GPA3,
    GPA4,
    GPA5,
    GPA6,
    GPA7,
    GPB0 = 8,
    GPB1,
    GPB2,
    GPB3,
    GPB4,
    GPB5,
    GPB6,
    GPB7
} MCP23017_PIN_TYPE;

/* I/O EXPANDER 0 PIN DECLARATION */
typedef enum
{
    DI_PP_OUT_1_FAULT  = GPB6, 
    DI_PP_OUT_10_FAULT = GPB1,
    DI_PP_OUT_13_FAULT = GPA4,
    DI_PP_OUT_14_FAULT = GPA0,
    DI_PP_OUT_15_FAULT = GPB4,
    DI_PP_OUT_16_FAULT = GPB3,
    DI_PP_OUT_22_FAULT = GPB0,
    DI_PP_OUT_3_FAULT  = GPA1,
    DI_PP_OUT_31_FAULT = GPA5,
    DI_PP_OUT_6_FAULT  = GPB2,
    DI_PP_OUT_8_FAULT  = GPB5,
} MCP23017_EXP0_PIN_NAME_TYPE;
#define MCP23017_EXP0_PORTA_DIR_CFG     0x7F
#define MCP23017_EXP0_PORTB_DIR_CFG     0x7F


/* I/O EXPANDER 1 PIN DECLARATION */
typedef enum
{
    DO_PP_OUT_1_ENABLE  = GPA2,
    DO_PP_OUT_10_ENABLE = GPA6,
    DO_PP_OUT_13_ENABLE = GPB7,
    DO_PP_OUT_14_ENABLE = GPB1,
    DO_PP_OUT_15_ENABLE = GPB3,
    DO_PP_OUT_16_ENABLE = GPA4,
    DO_PP_OUT_3_ENABLE  = GPB2,
    DO_PP_OUT_31_ENABLE = GPA5,
    DO_PP_OUT_6_ENABLE  = GPA7,
    DO_PP_OUT_8_ENABLE  = GPA1,
    DO_PP_OUT_TEST      = GPA3,
} MCP23017_EXP1_PIN_NAME_TYPE;
#define MCP23017_EXP1_PORTA_DIR_CFG     0x00
#define MCP23017_EXP1_PORTB_DIR_CFG     0x00


/* I/O EXPANDER 2 PIN DECLARATION */
typedef enum
{
    DO_PP_OUT_11_ENABLE = GPA6,
    DO_PP_OUT_12_ENABLE = GPB1,
    DO_PP_OUT_2_ENABLE  = GPB7,
    DO_PP_OUT_32_ENABLE = GPB2,
    DO_PP_OUT_33_ENABLE = GPB3,
    DO_PP_OUT_34_ENABLE = GPA1,
    DO_PP_OUT_35_ENABLE = GPA7,
    DO_PP_OUT_36_ENABLE = GPB5,
    DO_PP_OUT_7_ENABLE  = GPB6,
    DO_PP_OUT_9_ENABLE  = GPA4,
    DI_PP_OUT_9_FAULT   = GPB0,
    PP_OUT_RESET        = GPA3, 
} MCP23017_EXP2_PIN_NAME_TYPE;
#define MCP23017_EXP2_PORTA_DIR_CFG     0x00
#define MCP23017_EXP2_PORTB_DIR_CFG     0x01


/* I/O EXPANDER 3 PIN DECLARATION */
typedef enum
{
    DI_PP_OUT_11_FAULT = GPB3,
    DI_PP_OUT_12_FAULT = GPA5,
    DI_PP_OUT_2_FAULT  = GPA2,
    DI_PP_OUT_32_FAULT = GPA3,
    DI_PP_OUT_33_FAULT = GPB1,
    DI_PP_OUT_34_FAULT = GPB5,
    DI_PP_OUT_35_FAULT = GPB2,
    DI_PP_OUT_36_FAULT = GPA4,
    DO_PP_OUT_4_ENABLE = GPB7,
    DI_PP_OUT_4_FAULT  = GPA6,
    DI_PP_OUT_7_FAULT  = GPA0, 
} MCP23017_EXP3_PIN_NAME_TYPE;
#define MCP23017_EXP3_PORTA_DIR_CFG     0x7F
#define MCP23017_EXP3_PORTB_DIR_CFG     0x7F


/* I/O EXPANDER 4 PIN DECLARATION */
typedef enum
{
    DI_PP_OUT_17_FAULT = GPA0,
    DI_PP_OUT_18_FAULT = GPA1,
    DI_PP_OUT_19_FAULT = GPA4,
    DI_PP_OUT_20_FAULT = GPA5,
    DI_PP_OUT_21_FAULT = GPA6,
    DI_PP_OUT_23_FAULT = GPB0,
    DI_PP_OUT_24_FAULT = GPB1,
    DI_PP_OUT_25_FAULT = GPB4,
    DI_PP_OUT_26_FAULT = GPB5,
    DI_PP_OUT_27_FAULT = GPA2,
    DI_PP_OUT_28_FAULT = GPA3,
    DI_PP_OUT_29_FAULT = GPB2,
    DI_PP_OUT_30_FAULT = GPB3,
    DO_PP_OUT_5_ENABLE = GPB7,
    DI_PP_OUT_5_FAULT  = GPB6,
} MCP23017_EXP4_PIN_NAME_TYPE;
#define MCP23017_EXP4_PORTA_DIR_CFG     0x7F
#define MCP23017_EXP4_PORTB_DIR_CFG     0x7F


/* I/O EXPANDER 5 PIN DECLARATION */
typedef enum
{
    DI_ORING_BATT_EN_FEEDBACK = GPB5,
    DO_ORING_BATT_ENABLE      = GPA2,
    DI_ORING_GPU_EN_FEEDBACK  = GPA1,
    DO_ORING_GPU_ENABLE       = GPA0,
    DI_PGD_IN_1_STATUS        = GPA3,
    DI_PGD_IN_2_STATUS        = GPB4,
    DI_PGD_IN_3_STATUS        = GPA6,
    DI_PGD_IN_4_STATUS        = GPB2,
    DI_PGD_IN_5_STATUS        = GPA4,
    DI_PGD_IN_6_STATUS        = GPB3,
    DI_PGD_IN_7_STATUS        = GPB6,
    DI_PGD_IN_8_STATUS        = GPA5,
    DO_PGD_OUT_3_ENABLE       = GPB1,
    DO_PGD_OUT_4_ENABLE       = GPB0,
} MCP23017_EXP5_PIN_NAME_TYPE;
#define MCP23017_EXP5_PORTA_DIR_CFG     0x7A
#define MCP23017_EXP5_PORTB_DIR_CFG     0x7C

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================


#endif /* __MCP23017_PRM_H__ */
