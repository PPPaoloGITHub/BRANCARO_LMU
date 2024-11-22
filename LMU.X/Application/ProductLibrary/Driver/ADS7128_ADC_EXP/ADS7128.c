/**
 *  @file       MCP23017.c
 *  @brief      Driver for ADS7128 12-bit, 8-channel Sampling ADC with I2C Serial Interface
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 * 
 * 
 * !!!!*** See at the end of this file, the testing module code ***!!!!
 * 
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <stdio.h>
#include <string.h>

#include "../../ProductLibraryInclude/ADS7128.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
static uint8 numberOfEnChannels = 0;

/* OPcodes for Commands */
#define OPCODE_CMD_SINGLE_REG_READ           0x10
#define OPCODE_CMD_SINGLE_REG_WRITE          0x08
#define OPCODE_CMD_SET_BIT                   0x18
#define OPCODE_CMD_CLEAR_BIT                 0x20
#define OPCODE_CMD_READING_CONTINUOUS_BLOCK  0x30
#define OPCODE_CMD_WRITING_CONTINUOUS_BLOCK  0x28


//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static bool ADS7128_WriteRegister             (ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_REGISTER_TYPE reg, uint8 *values, uint8 length);
static bool ADS7128_ReadRegister              (ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_REGISTER_TYPE reg, uint8 *outValues, uint8 length);
static bool ADS7128_SetBits                   (ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_REGISTER_TYPE reg, uint8 bits);
static bool ADS7128_ClearBits                 (ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_REGISTER_TYPE reg, uint8 bits);

static bool ADS7128_Reset                     (ADS7128_I2C_ADDR_TYPE deviceAddr);
static bool ADS7128_StartAutoSequence         (ADS7128_I2C_ADDR_TYPE deviceAddr);
static bool ADS7128_EnableAutoSequenceChannels(ADS7128_I2C_ADDR_TYPE deviceAddr, uint8 enabledChannels);
static bool ADS7128_SetConversionMode         (ADS7128_I2C_ADDR_TYPE deviceAddr, bool automatic);
static bool ADS7128_SelectChannel             (ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_CHANNEL_TYPE channel);

/* ***************************************************************************************************************************** */

static bool ADS7128_InitDevice                (ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_MODE_SEL_TYPE mode, ADS7128_ENABLED_CHANNELS_TYPE enabledChannels);
static bool ADS7128_ReadChannel               (ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_CHANNEL_TYPE channel, uint16 *readVal);
static bool ADS7128_ReadMultiChannels         (ADS7128_I2C_ADDR_TYPE deviceAddr, uint16 *readChannels);


const struct ADS7128_INTRFACE_STRUCT ADS7128_Interf =
{
    .Initialize             = &ADS7128__Initialize,
    .Handler5ms             = &ADS7128__Handler5ms,
    .InitDevice             = &ADS7128_InitDevice,
    .ReadChannel            = &ADS7128_ReadChannel,
    .ReadMultiChannels      = &ADS7128_ReadMultiChannels,
};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes the ADS7128 module
  *
  * @param  None
  * @retval None
  * @note	None 
  */
void ADS7128__Initialize(void)
{

}

/**
  * @brief  ADS7128 module handler. It manages all the module functionalities
  *
  * @param  None
  * @retval None
  * @note	call this function in the task every 5ms
  */
void ADS7128__Handler5ms(void)
{

}

/**
  * @brief     Initialization of ADS7128 device By default, all channel are set as analog input.
  *
  * @param[in] deviceAddr: Address I2C of ADS7128
  * @param[in] mode: select the operational mode from the ADS7128_MODE_SEL_TYPE enumeration 
  * @param[in] enabledChannels: select channels for sequencing: each bit represents a channel, bit0 --> CH0, bit1 --> CH1 ...
  *                             To select all the channels, set enabledChannels = ADS7128_ENABLE_ALL_CHANNELS = 0xFF 
  * @retval    true: Initialization was successful; false: no writing 
  * @note	   None
  */
static bool ADS7128_InitDevice(ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_MODE_SEL_TYPE mode, ADS7128_ENABLED_CHANNELS_TYPE enabledChannels)
{
    bool retVal = TRUE;
    uint8 writeReg[2];
  
    /* Reset the device: all registers set at default value */
    retVal = ADS7128_Reset(deviceAddr);
    
    /* Configure the device with ADC Offset Calibration and 
     * All channels configurated as Analog Inputs */
    /* Register 0x01 (GENERAL_CFG) definition
    * |-------------------------------------------------------------------------------------------------------------------------------|
    * |     Bit 7     |     Bit 6     |     Bit 5     |     Bit 4     |     Bit 3     |     Bit 2     |     Bit 1     |     Bit 0     |
    * |-------------------------------------------------------------------------------------------------------------------------------|
    * |    RESERVED   |     CRC_EN    |    STATS_EN   |     DWC_EN    |     CNVST     |     CH_RST    |      CAL      |      RST      |
    * |-------------------------------------------------------------------------------------------------------------------------------|
    */
     if(retVal == TRUE)
    {
        writeReg[0] = 0x06;                                                        // Set CAL = 1: ADC Offset is calibrated. Set CH_RST = 1: All channels are configurated as analog inputs 
        ADS7128_WriteRegister(deviceAddr, ADS7128_REG_GENERAL_CFG, writeReg, 1);   // Reset STATS_EN bit: is set, it Enables the Statistics Module to update minimum,
                                                                                   // maximum, and latest output code registers.
    }
        
    /* ************************************************************************ */
    /* ************ SET CHANNELS BEHAVIOUR: sets as GPIO --> INPUTS *********** */
    /* ************************************************************************ */
//    writeReg[0] = 0xFF;
//    ADS7128_WriteRegister(deviceAddr, ADS7128_REG_PIN_CFG, writeReg, 1);         // it sets all pins GPIO
//    writeReg[0] = 0x00;
//    ADS7128_WriteRegister(deviceAddr, ADS7128_REG_GPIO_CFG, writeReg, 1);        // it sets all pins as Digital Inputs
    // End sets for GPIO --> INPUTS
 
    
    switch(mode)
    {
        default:
            // By default the default it initialized as Manual Mode
        break;
        
        case ADS7128_MANUAL_MODE:
            /* ************************************************************************ */
            /* ******************** SET CONFIGURATION: MANUAL MODE ******************** */
            /* ************************************************************************ */
            /* Enable Autonomous = TRUE or Manual = FALSE Mode for ADC */
            /* Register 0x04 (OPMODE_CFG) definition
            * |-------------------------------------------------------------------------------------------------------------------------------|
            * |     Bit 7     |     Bit 6     |     Bit 5     |     Bit 4     |     Bit 3     |     Bit 2     |     Bit 1     |     Bit 0     |
            * |-------------------------------------------------------------------------------------------------------------------------------|
            * |  CONV_ON_ERR  |         CONV_MODE[1:0]        |    OSC_SEL    |                          CLK_DIV[3:0]                         |
            * |-------------------------------------------------------------------------------------------------------------------------------|
            */
            if(retVal == TRUE)
            {
                retVal = ADS7128_SetConversionMode(deviceAddr, FALSE);                  // ADS7128_REG_OPMODE_CF --> CONV_MODE = 00b)
            }
        break;

        case ADS7128_AUTO_SEQUENCE_MODE:
            /* ************************************************************************ */
            /* ******************** SET CONFIGURATION: AUTO - SEQUENCE MODE ******************** */
            /* ************************************************************************ */
            /* Enable Analog Inputs for sequencing */
            if(retVal == TRUE)
            {                                                                          
                retVal = ADS7128_EnableAutoSequenceChannels(deviceAddr, enabledChannels);   // ADS7128_REG_AUTO_SEQ_CH_SEL = enabledChannels
            }

            /* Enable Autonomous = TRUE or Manual = FALSE Mode for ADC */
            /* Register 0x04 (OPMODE_CFG) definition
            * |-------------------------------------------------------------------------------------------------------------------------------|
            * |     Bit 7     |     Bit 6     |     Bit 5     |     Bit 4     |     Bit 3     |     Bit 2     |     Bit 1     |     Bit 0     |
            * |-------------------------------------------------------------------------------------------------------------------------------|
            * |  CONV_ON_ERR  |         CONV_MODE[1:0]        |    OSC_SEL    |                          CLK_DIV[3:0]                         |
            * |-------------------------------------------------------------------------------------------------------------------------------|
            */
            if(retVal == TRUE)
            {
                retVal = ADS7128_SetConversionMode(deviceAddr, FALSE);                  // ADS7128_REG_OPMODE_CF --> CONV_MODE = 00b)
            }

            /* Set Auto Sequence Mode and Start Channel sequencing for channels enabled in ADS7128_REG_AUTO_SEQ_CH_SEL register */
            /* Register 0x10 (SEQUENCE_CFG) definition
            * |-------------------------------------------------------------------------------------------------------------------------------|
            * |     Bit 7     |     Bit 6     |     Bit 5     |     Bit 4     |     Bit 3     |     Bit 2     |     Bit 1     |     Bit 0     |
            * |-------------------------------------------------------------------------------------------------------------------------------|
            * |                 RESERVED[2:0]                 |   SEQ_START   |         RESERVED[1:0]         |         SEQ_MODE[1:0]         |
            * |-------------------------------------------------------------------------------------------------------------------------------|
            */
             if(retVal == TRUE)
            {
                retVal = ADS7128_StartAutoSequence(deviceAddr);                         // ADS7128_REG_SEQUENCE_CFG --> SEQ_MODE = 1b; SEQ_START = 1b
            }
        break;
        
        case ADS7128_AUTONOMOUS_MODE:
            //TODO: Mode not implemented
        break;
    }
    return retVal;
}

/**
  * @brief      This function read a single selected channel. Use it only in Manual Mode
  *
  * @param[in]  deviceAddr: Address I2C of ADS7128
  * @param[in]  channel: select the channel that you wan to read from the ADS7128_CHANNEL_TYPE enumeration
  * @param[out] readVal: pointer to the read variable 
  * @retval     true: The reading was successful; false: no reading
  * @note	    Use this function ONLY if the ADS7128_MANUAL_MODE was called in the initialization
  */
static bool ADS7128_ReadChannel(ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_CHANNEL_TYPE channel, uint16 *readVal)
{
    bool  retVal = TRUE;
    uint8 readVariable[2];
    
/* To use if Statistics Module is Enabled! */
//    uint8 reg;
//    reg = ADS7128_REG_RECENT_LSB_CH(channel);

    retVal = ADS7128_SelectChannel(deviceAddr, channel);

    if(retVal == TRUE)
    {
/* To use if Statistics Module is Enabled! */
//      retVal = ADS7128_ReadRegister(deviceAddr, reg, readVariable, 2);
        while(ADS7128_I2CIsBusy() == true);     // Waiting for I2C module is free
        retVal = ADS7128_I2CRead(deviceAddr, readVariable, 2);
        while(ADS7128_I2CIsBusy() == true);     // Waiting for I2C module is free
    }
    
    if(retVal == TRUE)
    {
        // return the read channel on 16 bits variable
        *readVal = (((uint16)readVariable[0] << 8) | readVariable[1]) >> 4;
    }
    else
    {
        *readVal = 0;
    }

    return retVal;
}

/**
  * @brief      This function read a Multiple Channels in accordance with the channels Enabled in the initialization.
  *             Use it only in Auto-Sequence Mode
  *
  * @param[in]  deviceAddr: Address I2C of ADS7128
  * @param[out] readChannels: pointer to the read data buffer 
  * @retval     true: The reading was successful; false: no reading
  * @note	    Use this function ONLY if the ADS7128_AUTO_SEQUENCE_MODE was called in the initialization
  */
static bool ADS7128_ReadMultiChannels(ADS7128_I2C_ADDR_TYPE deviceAddr, uint16 *readChannels)
{
    bool  retVal = TRUE;
    uint8 k;
    uint8 readBuff[numberOfEnChannels * 2];   

    if(retVal == TRUE)
    {
        while(ADS7128_I2CIsBusy() == true);     // Waiting for I2C module is free
        retVal = ADS7128_I2CRead(deviceAddr, readBuff, (numberOfEnChannels * 2));
        while(ADS7128_I2CIsBusy() == true);     // Waiting for I2C module is free
    }
    
    if(retVal == TRUE)
    {
        for(k = 0; k < numberOfEnChannels; k++)
        {
            readChannels[k] = ((((uint16)readBuff[k*2] << 8) | readBuff[k*2+1]) >> 4);
        }
    }
    else
    {
        for(k = 0; k < numberOfEnChannels; k++)
        {
            readChannels[k] = 0;
        }
    }

    return retVal;
}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/* This function writes the ADS7128 registers */
static bool ADS7128_WriteRegister(ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_REGISTER_TYPE reg, uint8 *values, uint8 length)
{
    bool retVal = TRUE;
    uint8 writeBuff[length + 2];
    
    writeBuff[0] = OPCODE_CMD_WRITING_CONTINUOUS_BLOCK;
    writeBuff[1] = reg;
    memcpy(&writeBuff[2], values, length);
    
    while(ADS7128_I2CIsBusy() == true);     // Waiting for I2C module is free
    retVal = ADS7128_I2CWrite(deviceAddr, writeBuff, (length + 2));
    while(ADS7128_I2CIsBusy() == true);     // Waiting for I2C module is free
    
    return retVal;
}

/* This function reads the ADS7128 registers */
static bool ADS7128_ReadRegister(ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_REGISTER_TYPE reg, uint8 *outValues, uint8 length)
{
    bool retVal = TRUE;
    uint8 readBuff[2];
    
    readBuff[0] = OPCODE_CMD_READING_CONTINUOUS_BLOCK;
    readBuff[1] = reg;
    
    while(ADS7128_I2CIsBusy() == true);     // Waiting for I2C module is free
    retVal = ADS7128_I2CWrite(deviceAddr, readBuff, 2);
    while(ADS7128_I2CIsBusy() == true);     // Waiting for I2C module is free
    
    if(retVal == TRUE)
    {
        retVal = ADS7128_I2CRead(deviceAddr, outValues, length);
        while(ADS7128_I2CIsBusy() == true);     // Waiting for I2C module is free
    }
   
    return retVal;
}

/* This function set the bit or bits of the ADS7128 register */
static bool ADS7128_SetBits(ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_REGISTER_TYPE reg, uint8 bits)
{
    bool retVal = TRUE;
    uint8 currentValue;
    
    retVal = ADS7128_ReadRegister(deviceAddr, reg, &currentValue, 1);
    
    if(retVal == TRUE)
    {
        currentValue |= bits;
        retVal = ADS7128_WriteRegister(deviceAddr, reg, &currentValue, 1);
    }
     
    return retVal;
}

/* This function reset the bit or bits of the ADS7128 register */
static bool ADS7128_ClearBits(ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_REGISTER_TYPE reg, uint8 bits)
{
    bool retVal = TRUE;
    uint8 currentValue;
    
    retVal = ADS7128_ReadRegister(deviceAddr, reg, &currentValue, 1);
    
    if(retVal == TRUE)
    {
        currentValue &= ~bits;
        retVal = ADS7128_WriteRegister(deviceAddr, reg, &currentValue, 1);
    }
    
    return retVal;
}

/* This function performs the hardware reset of the device */
static bool ADS7128_Reset(ADS7128_I2C_ADDR_TYPE deviceAddr)
{
    bool retVal;
    uint16 k;
    
    retVal = ADS7128_SetBits(deviceAddr, ADS7128_REG_GENERAL_CFG, ADS7128_FLAG_GENERAL_CFG_RST);
    
    for(k = 0 ; k <= 5000 ; k++);  // Delay after the Reset command. It's necessary to give the time to reset and became available at the device 
    
    return retVal;
}

/* This function selects the mode of scanning of analog input channels in Auto Sequence Mode and sets the automatic sequence start */
static bool ADS7128_StartAutoSequence(ADS7128_I2C_ADDR_TYPE deviceAddr)
{
    bool retVal;
    uint8 sequenceConfig;
    
    sequenceConfig = ADS7128_FLAG_SEQUENCE_CFG_SEQ_MODE | ADS7128_FLAG_SEQUENCE_CFG_SEQ_START;
    
    retVal = ADS7128_SetBits(deviceAddr, ADS7128_REG_SEQUENCE_CFG, sequenceConfig);
    
    return retVal;
}

/* This function enables the selected channels. To enable all the channels, set enabledChannels = 0xFF */
static bool ADS7128_EnableAutoSequenceChannels(ADS7128_I2C_ADDR_TYPE deviceAddr, uint8 enabledChannels)
{
    bool retVal;
    uint8 k;
    uint8 writeBuff[1];
    
    writeBuff[0] = enabledChannels;
    /* Count how channels are enabled */
    for(k = 0; k < 8; k++)
    {
        numberOfEnChannels += enabledChannels & 1;
        enabledChannels >>= 1;
    }

    retVal = ADS7128_WriteRegister(deviceAddr, ADS7128_REG_AUTO_SEQ_CH_SEL, writeBuff, 1);
     
    return retVal;
}

/* This function configures the conversion mode. Set automatic = TRUE to enable Autonomous mode; automatic = FALSE to enable Manual mode */
static bool ADS7128_SetConversionMode(ADS7128_I2C_ADDR_TYPE deviceAddr, bool automatic)
{
    bool retVal;
    
    if(automatic == TRUE)
    {
        retVal = ADS7128_SetBits(deviceAddr, ADS7128_REG_OPMODE_CFG, ADS7128_FLAG_OPMODE_CFG_CONV_MODE);
    }
    else
    {
        retVal = ADS7128_ClearBits(deviceAddr, ADS7128_REG_OPMODE_CFG, ADS7128_FLAG_OPMODE_CFG_CONV_MODE);
    }
    
    return retVal;
}

/* This function writes the channel number into ADS7128_REG_CHANNEL_SEL register */
static bool ADS7128_SelectChannel(ADS7128_I2C_ADDR_TYPE deviceAddr, ADS7128_CHANNEL_TYPE channel)
{
    bool retVal;
    uint8 writeBuff[1];
    
    if(channel < ADS7128_MAX_CHANNELS)
    {
        writeBuff[0] = channel &0x07;
        
        retVal = ADS7128_WriteRegister(deviceAddr, ADS7128_REG_CHANNEL_SEL, writeBuff, 1);
    }
    else
    {
        retVal = FALSE;
    }
        
    return retVal;
}



/* ****************** TEST CODE *************** */


//void ADS7128__Initialize(void)
//{
//    /* Manual Mode - Read Single Channel */ 
////    ADS7128_Interf.InitDevice(ADC_EXP1_I2C_ADDR, ADS7128_MANUAL_MODE, ADS7128_MANUAL);
//    
//    /* Auto-Sequence Mode - Read Multi Channel */
//    ADS7128_Interf.InitDevice(ADC_EXP3_I2C_ADDR, ADS7128_AUTO_SEQUENCE_MODE, ADS7128_ENABLE_CH_0_1_2_3_4_5);
//}
//
///**
//  * @brief  ADS7128 module handler. It manages all the module functionalities
//  *
//  * @param  None
//  * @retval None
//  * @note	call this function in the task every 5ms
//  */
//void ADS7128__Handler5ms(void)
//{
//    static uint8 counter;
///* Manual Mode - Read Single Channel */ 
////    static uint16 channelValue;
//
///* Auto-Sequence Mode - Read Multi Channel */ 
//    static uint16 channelValue[16];
// 
//    
//    if((counter % 10) == 0)
//    {
//        /* Manual Mode - Read Single Channel */         
////        ADS7128_Interf.ReadChannel(ADC_EXP1_I2C_ADDR, ADS7128_CH1, &channelValue);
////        printf("CH1 = %d\r\n", channelValue);
////        
////        ADS7128_Interf.ReadChannel(ADC_EXP1_I2C_ADDR, ADS7128_CH5, &channelValue);
////        printf("CH5 = %d\r\n", channelValue);
//        
// 
//          /* Auto-Sequence Mode - Read Multi Channel */        
//        ADS7128_Interf.ReadMultiChannels(ADC_EXP3_I2C_ADDR, channelValue);
//        for(uint8 k = 0; k < 7; k++)
//        {
//            printf("CH%d = 0x%x\r\n", k, channelValue[k]);
//        }
//    }
// 
//    counter++;
//}
