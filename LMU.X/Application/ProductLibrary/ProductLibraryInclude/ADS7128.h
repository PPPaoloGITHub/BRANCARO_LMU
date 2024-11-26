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

#include "ADS7128_prm.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
/* Base address of ADC EXPANDER (7 bits, shifted left by 1bit) */
typedef enum
{
    ADC_EXP0_I2C_ADDR = 0x10,   // Not Used device
    ADC_EXP1_I2C_ADDR = 0x11,
    ADC_EXP2_I2C_ADDR = 0x12,
    ADC_EXP3_I2C_ADDR = 0x13,
    ADC_EXP4_I2C_ADDR = 0x14,
    ADC_EXP5_I2C_ADDR = 0x15,
    ADC_EXP6_I2C_ADDR = 0x16,
    ADC_EXP7_I2C_ADDR = 0x17,   // Not Used device         
} ADS7128_I2C_ADDR_TYPE;

/* Enabled Channels ordered in Auto-Sequence Mode */
typedef enum
{
    ADS7128_MANUAL                  = 0x00,
    ADS7128_ENABLE_CH_0             = 0x01,
    ADS7128_ENABLE_CH_0_1           = 0x03,
    ADS7128_ENABLE_CH_0_1_2         = 0x07,
    ADS7128_ENABLE_CH_0_1_2_3       = 0x0F,
    ADS7128_ENABLE_CH_0_1_2_3_4     = 0x1F,
    ADS7128_ENABLE_CH_0_1_2_3_4_5   = 0x3F,
    ADS7128_ENABLE_CH_0_1_2_3_4_5_6 = 0x7F,
    ADS7128_ENABLE_ALL_CHANNELS     = 0xFF,
} ADS7128_ENABLED_CHANNELS_TYPE;



/* Programmable Averaging Filter: Selects the oversampling ratio (OSR) for ADC conversion result */
typedef enum
{
    OSR_NO_AVERAGE  = 0x00,    // = No averaging
    OSR_2_SAMPLES   = 0x01,    // = 2 samples
    OSR_4_SAMPLES   = 0x02,    // = 4 samples
    OSR_8_SAMPLES   = 0x03,    // = 8 samples
    OSR_16_SAMPLES  = 0x04,    // = 16 samples
    OSR_32_SAMPLES  = 0x05,    // = 32 samples
    OSR_64_SAMPLES  = 0x06,    // = 64 samples
    OSR_128_SAMPLES = 0x07,    // = 128 samples
    OSR_MAX_NUMBER  = 0x08,    // = max number of oversample items
}ADS7128_OSR_TYPE;

/* Settings operational Mode*/
typedef enum
{
    ADS7128_MANUAL_MODE         = 0,
    ADS7128_AUTO_SEQUENCE_MODE,
    ADS7128_AUTONOMOUS_MODE
}ADS7128_MODE_SEL_TYPE;


/* ADS7128 registers address definition */
typedef enum 
{
    ADS7128_REG_SYSTEM_STATUS    = 0x00,
    ADS7128_REG_GENERAL_CFG      = 0x01,
    ADS7128_REG_DATA_CFG         = 0x02,
    ADS7128_REG_OSR_CFG          = 0x03,
    ADS7128_REG_OPMODE_CFG       = 0x04,
    ADS7128_REG_PIN_CFG          = 0x05,  
    ADS7128_REG_GPIO_CFG         = 0x07,
    ADS7128_REG_GPO_DRIVE_CFG    = 0x09,
    ADS7128_REG_GPO_VALUE        = 0x0B,
    ADS7128_REG_GPI_VALUE        = 0x0D,
    ADS7128_REG_ZCD_BLANKING_CFG = 0x0F,
    ADS7128_REG_SEQUENCE_CFG     = 0x10,
    ADS7128_REG_CHANNEL_SEL      = 0x11,
    ADS7128_REG_AUTO_SEQ_CH_SEL  = 0x12,
    ADS7128_REG_ALERT_CH_SEL     = 0x14,  

    /* Registers for reading recent samples of each channel */
    ADS7128_REG_RECENT_CH0_LSB   = 0xA0,
    ADS7128_REG_RECENT_CH0_MSB   = 0xA1,
    ADS7128_REG_RECENT_CH1_LSB   = 0xA2,
    ADS7128_REG_RECENT_CH1_MSB   = 0xA3,
    ADS7128_REG_RECENT_CH2_LSB   = 0xA4,
    ADS7128_REG_RECENT_CH2_MSB   = 0xA5,
    ADS7128_REG_RECENT_CH3_LSB   = 0xA6,
    ADS7128_REG_RECENT_CH3_MSB   = 0xA7,
    ADS7128_REG_RECENT_CH4_LSB   = 0xA8,
    ADS7128_REG_RECENT_CH4_MSB   = 0xA9,
    ADS7128_REG_RECENT_CH5_LSB   = 0xAA,
    ADS7128_REG_RECENT_CH5_MSB   = 0xAB,
    ADS7128_REG_RECENT_CH6_LSB   = 0xAC,
    ADS7128_REG_RECENT_CH6_MSB   = 0xAD,
    ADS7128_REG_RECENT_CH7_LSB   = 0xAE,
    ADS7128_REG_RECENT_CH7_MSB   = 0xAF,
} ADS7128_REGISTER_TYPE;

#define ADS7128_REG_HIGH_TH_HYS_CH(x) (0x20 + (x) * 4)
#define ADS7128_REG_LOW_TH_CNT_CH(x)  (0x22 + (x) * 4)
#define ADS7128_REG_MAX_LSB_CH(x)     (0x60 + (x) * 2)
#define ADS7128_REG_MIN_LSB_CH(x)     (0x80 + (x) * 2)
#define ADS7128_REG_RECENT_LSB_CH(x)  (0xA0 + (x) * 2)

/* Configuration FLAGS and MASKS */
#define ADS7128_FLAG_GENERAL_CFG_RST          0x01
#define ADS7128_FLAG_GENERAL_CFG_DWC_EN       0x10
#define ADS7128_FLAG_GENERAL_CFG_STATS_EN     0x20
#define ADS7128_FLAG_OPMODE_CFG_CONV_MODE     0x20
#define ADS7128_FLAG_OPMODE_CFG_FREQ_MASK  	  0x1F
#define ADS7128_FLAG_SEQUENCE_CFG_SEQ_MODE    0x01
#define ADS7128_FLAG_SEQUENCE_CFG_SEQ_START   0x10
#define ADS7128_OSR_CFG_MASK  		          0x07
#define ADS7128_THRESHOLD_LSB_MASK       	  0x0F


struct ADS7128_INTRFACE_STRUCT
{
    void (*Initialize)          (void);
    void (*Handler5ms)          (void);
    bool (*InitDevice)          (ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_MODE_SEL_TYPE mode, ADS7128_ENABLED_CHANNELS_TYPE enabledChannels);
    bool (*ReadChannel)         (ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_CHANNEL_TYPE channel, uint16 *readVal); 
    bool (*ReadMultiChannels)   (ADS7128_I2C_ADDR_TYPE deviceAddr, uint16 *readChannels);
};

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct ADS7128_INTRFACE_STRUCT ADS7128_Interf;

void ADS7128__Initialize(void);
void ADS7128__Handler5ms(void);

#endif /* __ADS7128_H__ */
