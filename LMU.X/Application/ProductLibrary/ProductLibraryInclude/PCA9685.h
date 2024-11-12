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

#include "PCA9685_prm.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
/* Base address of I/O EXPANDER PWM (7 bits, shifted left by 1bit) */
/* There are 6 configurable pins, A5, A4, A3, A2, A1, A0 with 2 reserved addresses, so can be connected 62 devices on I2C bus */
/* In our project there is only 1 device PCA9685 configured as: FixedBit=1, A5=0, A4=1, A3=0, A2=1, A1=1, A0=0 => 0b1010110R/W => */
/* => device I2C address = 0x56 (obtained without R/W bit) */
typedef enum
{
     IO_EXP_PWM_I2C_ADDR = 0x56,    // 0x40 for Demo Board      
} PCA9685_I2C_ADDR_TYPE;

/* Channels name */
typedef enum
{
    CH0 = 0,
    CH1,
    CH2,
    CH3,
    CH4,
    CH5,
    CH6,
    CH7,
    CH8,
    CH9,
    CH10,
    CH11,
    CH12,
    CH13,
    CH14,
    CH15
} PCA9685_CHANNELS_TYPE;

/* PCA9685 registers address definition */
typedef enum
{
    PCA9685_MODE1         = 0x00,       // Operation mode control
    PCA9685_MODE2         = 0x01,       // Other operation mode control
    PCA9685_LED0_ON_L     = 0x06,       // PWM control registers for each channel (16 channels)
    PCA9685_LED0_ON_H     = 0x07,       // PWM control registers for each channel (16 channels)
    PCA9685_LED0_OFF_L    = 0x08,       // PWM control registers for each channel (16 channels)
    PCA9685_LED0_OFF_H    = 0x09,       // PWM control registers for each channel (16 channels)
    PCA9685_ALL_LED_ON_L  = 0xFA,       // PWM control for all channels simultaneously
    PCA9685_ALL_LED_ON_H  = 0xFB,       // PWM control for all channels simultaneously
    PCA9685_ALL_LED_OFF_L = 0xFC,       // PWM control for all channels simultaneously
    PCA9685_ALL_LED_OFF_H = 0xFD,       // PWM control for all channels simultaneously
    PCA9685_PRESCALE      = 0xFE,       //  
} PCA9685_REGISTER_TYPE;

struct PCA9685_INTRFACE_STRUCT
{
    void (*Initialize) (void);
    void (*Handler5ms) (void);
    void (*InitDevice) (PCA9685_I2C_ADDR_TYPE deviceAddr);
    void (*SetPWMFreq) (PCA9685_I2C_ADDR_TYPE deviceAddr, uint16 freq);
    void (*SetPWM)     (PCA9685_I2C_ADDR_TYPE deviceAddr, PCA9685_CHANNELS_TYPE channel, uint8 dutyCycle);
    void (*SetAllPWM)  (PCA9685_I2C_ADDR_TYPE deviceAddr, uint8 dutyCycle);
    void (*Sleep)      (PCA9685_I2C_ADDR_TYPE deviceAddr);
    void (*WakeUp)     (PCA9685_I2C_ADDR_TYPE deviceAddr);
};

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct PCA9685_INTRFACE_STRUCT PCA96857_Interf;

void PCA9685__Initialize(void);
void PCA9685__Handler25ms(void);

#endif /* __PCA9685_H__ */
