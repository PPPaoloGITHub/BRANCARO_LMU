/**
 *  @file       PCA9685.c
 *  @brief      Driver for PCA9685 16 bit PWM I/O Expander with I2C Serial Interface
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

#include "../../ProductLibraryInclude/PCA9685.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
#define PCA9685_INTERNAL_CLOCK_FREQ     25000000.0F     // [Hz] PCA9685 internal clock frequency
#define PCA9685_PRESCALE_COSTANT            4096.0F     // PCA9685 prescale costant used to calculate PRESCALE value
#define PCA9685_PWM_STEPS                   4095        // 12 bits PWM steps used from PCA9685 to implement the duty Cycle
#define PCA9685_MAX_DUTY_CYCLE_VALUE         100        // Maximum duty cycle value


static uint8 writeBuffer[5];
static uint8 readVariable;

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static bool  PCA9685_WriteRegister (PCA9685_I2C_ADDR_TYPE deviceAddr, PCA9685_REGISTER_TYPE regAddr, uint8 value);
static uint8 PCA9685_ReadRegister  (PCA9685_I2C_ADDR_TYPE deviceAddr, PCA9685_REGISTER_TYPE regAddr);

static void PCA9685_InitDevice (PCA9685_I2C_ADDR_TYPE deviceAddr);
static void PCA9685_SetPWMFreq (PCA9685_I2C_ADDR_TYPE deviceAddr, uint16 freq);
static void PCA9685_SetPWM     (PCA9685_I2C_ADDR_TYPE deviceAddr, PCA9685_CHANNELS_TYPE channel, uint8 dutyCycle);
static void PCA9685_SetAllPWM  (PCA9685_I2C_ADDR_TYPE deviceAddr, uint8 dutyCycle);
static void PCA9685_Sleep      (PCA9685_I2C_ADDR_TYPE deviceAddr);
static void PCA9685_WakeUp     (PCA9685_I2C_ADDR_TYPE deviceAddr);


const struct PCA9685_INTRFACE_STRUCT PCA9685_Interf =
{
    .Initialize = &PCA9685__Initialize,
    .Handler5ms = &PCA9685__Handler25ms,
    .InitDevice = &PCA9685_InitDevice,
    .SetPWMFreq = &PCA9685_SetPWMFreq,
    .SetPWM     = &PCA9685_SetPWM,
    .SetAllPWM  = &PCA9685_SetAllPWM,     
    .Sleep      = &PCA9685_Sleep,
    .WakeUp     = &PCA9685_WakeUp,          
};


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes the PCA9685 module
  *
  * @param  None
  * @retval None
  * @note	None
  */
void PCA9685__Initialize(void)
{
    // Initialize PCA9685 device
    PCA9685_Interf.InitDevice(IO_EXP_PWM_I2C_ADDR);
    
    // Set PCA9685 PWM frequencyHz at 400Hz
    PCA9685_Interf.SetPWMFreq(IO_EXP_PWM_I2C_ADDR, PCA9685_PWM_FREQUENCY);
    
    // Set all output channel to 0
    PCA9685_Interf.SetAllPWM(IO_EXP_PWM_I2C_ADDR, 0);
}

/**
  * @brief  PCA9685 module handler. It manages all the module functionalities
  *
  * @param  None
  * @retval None
  * @note	call this function in the task every 25ms
  */
void PCA9685__Handler25ms(void)
{

}

/**
  * @brief     This function initializes the PCA9685 device.
  *            It sets normal mode operation, AutoIncrement register Enabled, no sleep, output with positive polarity 
  *            and the 16 channels outputs are configured with a totem pole structure. 
  *
  * @param[in] deviceAddr: Address I2C of PCA9685
  * @retval    None
  * @note	   
  */
static void PCA9685_InitDevice(PCA9685_I2C_ADDR_TYPE deviceAddr)
{
    PCA9685_WriteRegister(deviceAddr, PCA9685_MODE1, 0x20);   // Bits set as written in description
    PCA9685_WriteRegister(deviceAddr, PCA9685_MODE2, 0x04);   // Bits set as written in description
}

/**
  * @brief  This function set the PWM frequency
  *
  * @param[in] deviceAddr: Address I2C of PCA9685
  * @param[in] freq: PWM frequency in the range [24Hz - 1526Hz]
  * @retval None
  * @note	
  */
static void PCA9685_SetPWMFreq(PCA9685_I2C_ADDR_TYPE deviceAddr, uint16 freq)
{
    uint8 prescale;
    uint8 oldMode;
    uint8 newMode;
   
    // datasheet equation to calculate prescale value
    prescale = (uint8)((PCA9685_INTERNAL_CLOCK_FREQ / (PCA9685_PRESCALE_COSTANT * (float)freq)) -1 );
    
    // Acquire current Mode settings
    oldMode = PCA9685_ReadRegister(deviceAddr, PCA9685_MODE1);
    
    // Set sleep Mode needed to set PRESCALE register
    newMode = (oldMode & 0x7F) | 0x10;
    PCA9685_WriteRegister(deviceAddr, PCA9685_MODE1, newMode);      // set sleep Mode
    PCA9685_WriteRegister(deviceAddr, PCA9685_PRESCALE, prescale);
    PCA9685_WriteRegister(deviceAddr, PCA9685_MODE1, oldMode);      // set normal operation Mode
    
    // Restart device with new PWM frequency
    PCA9685_WriteRegister(deviceAddr, PCA9685_MODE1, (oldMode | 0x80));     // The RESTART bit will be cleared from device after restart.
}

/**
  * @brief     This function sets the Duty Cycle of PWM on a single channel
  *
  * @param[in] deviceAddr: Address I2C of PCA9685
  * @param[in] dutyCycle: duty Cycle (Ton / (Ton + Toff)) in range [0% - 100]
  * @retval    None
  * @note	
  */
static void PCA9685_SetPWM(PCA9685_I2C_ADDR_TYPE deviceAddr, PCA9685_CHANNELS_TYPE channel, uint8 dutyCycle)
{
    uint16 timeOff;
    uint8  reg;
    
    // Check and limit duty Cycle at 100% value
    if(dutyCycle > PCA9685_MAX_DUTY_CYCLE_VALUE)
    {
        dutyCycle = PCA9685_MAX_DUTY_CYCLE_VALUE;
    }
    
    // Calculates 'Time off' value based on duty cycle input
    timeOff = (uint16)(((uint32)PCA9685_PWM_STEPS * dutyCycle) / PCA9685_MAX_DUTY_CYCLE_VALUE);
        
    // Calculates the starting register for the channel
    reg = PCA9685_LED0_ON_L + (4 * channel);
    
    writeBuffer[0] = reg;
    writeBuffer[1] = 0x00;                                  // ON_LOW               Set 'on' value to 0 so the duty cycle is completely 
                                                            //                      controlled from 'off' value (timeOff)
    if(dutyCycle == PCA9685_MAX_DUTY_CYCLE_VALUE)
    {
        // Set bit 4 of ALL_LED_ON_H to have always ON
        writeBuffer[2] = 0x00 | 0b00010000;                 // ON_HIGH register.    
    }
    else
    {
        writeBuffer[2] = 0x00;                              // ON_HIGH register.    
    }
    
    writeBuffer[3] = (uint8)(timeOff & 0x00FF);             // OFF_LOW register
    
    if(dutyCycle == PCA9685_MAX_DUTY_CYCLE_VALUE)
    {
        // Set bit 4 of ALL_LED_OFF_H to have always OFF
        writeBuffer[4] = 0x00 | 0b00010000;                 // OFF_HIGH register
    }
    else
    {
        writeBuffer[4] = (uint8)((timeOff & 0x0F00) >> 8 ); // OFF_HIGH register
    }
    
    // Waiting for I2C bus is free
    while(PCA9685_I2CIsBusy() == true);
    
    PCA9685_I2CWrite(deviceAddr, writeBuffer, 5);
    
    // Waiting for I2C bus is free
    while(PCA9685_I2CIsBusy() == true);
}

/**
  * @brief     This function sets the Duty Cycle of PWM on all channels
  *
  * @param[in] deviceAddr: Address I2C of PCA9685
  * @param[in] dutyCycle: duty Cycle (Ton / (Ton + Toff)) in range [0% - 100]
  * @retval    None
  * @note	
  */
static void PCA9685_SetAllPWM(PCA9685_I2C_ADDR_TYPE deviceAddr, uint8 dutyCycle)
{
    uint16 timeOff;
    
    // Check and limit duty Cycle at 100% value
    if(dutyCycle > PCA9685_MAX_DUTY_CYCLE_VALUE)
    {
        dutyCycle = PCA9685_MAX_DUTY_CYCLE_VALUE;
    }
    
    // Calculates 'Time off' value based on duty cycle input
    timeOff = (uint16)(((uint32)PCA9685_PWM_STEPS * dutyCycle) / PCA9685_MAX_DUTY_CYCLE_VALUE);
        
    writeBuffer[0] = PCA9685_ALL_LED_ON_L;
    writeBuffer[1] = 0x00;                                  // ON_LOW register.     Set 'on' value to 0 so the duty cycle is completely 
                                                            //                      controlled from 'off' value (timeOff) 
    if(dutyCycle == PCA9685_MAX_DUTY_CYCLE_VALUE)
    {
        // Set bit 4 of ALL_LED_ON_H to have always ON
        writeBuffer[2] = 0x00 | 0b00010000;                 // ON_HIGH register.    
    }
    else
    {
        writeBuffer[2] = 0x00;                              // ON_HIGH register.    
    }
    
    writeBuffer[3] = (uint8)(timeOff & 0x00FF);             // OFF_LOW register
    
    if(dutyCycle == PCA9685_MAX_DUTY_CYCLE_VALUE)
    {
        // Set bit 4 of ALL_LED_OFF_H to have always OFF
        writeBuffer[4] = 0x00 | 0b00010000;                 // OFF_HIGH register
    }
    else
    {
        writeBuffer[4] = (uint8)((timeOff & 0x0F00) >> 8 ); // OFF_HIGH register
    }
        
        
    // Waiting for I2C bus is free
    while(PCA9685_I2CIsBusy() == true);
    
    PCA9685_I2CWrite(deviceAddr, writeBuffer, 5);
    
    // Waiting for I2C bus is free
    while(PCA9685_I2CIsBusy() == true);
}

/**
  * @brief     This function sets the device in Sleep Mode
  *
  * @param[in] deviceAddr: Address I2C of PCA9685
  * @retval    None
  * @note	
  */
static void PCA9685_Sleep(PCA9685_I2C_ADDR_TYPE deviceAddr)
{
    uint8 mode;
    
    mode = PCA9685_ReadRegister(deviceAddr, PCA9685_MODE1);
    PCA9685_WriteRegister(deviceAddr, PCA9685_MODE1, (mode | 0x10));    // set the sleep bit
}

/**
  * @brief     This function sets the device in normal operation Mode wakeup from sleep mode
  *
  * @param[in] deviceAddr: Address I2C of PCA9685
  * @retval    None
  * @note	
  */
static void PCA9685_WakeUp(PCA9685_I2C_ADDR_TYPE deviceAddr)
{
    uint8 mode;
    
    mode = PCA9685_ReadRegister(deviceAddr, PCA9685_MODE1);
    PCA9685_WriteRegister(deviceAddr, PCA9685_MODE1, (mode & 0xEF));    // Reset the sleep bit   
}

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief     This function write on a PCA9685 register
  *
  * @param[in] deviceAddr: Address I2C of PCA9685
  * @param[in] regAddr: register address from PCS9685_REGISTER_TYPE enumeration
  * @param[in] value: value that you want to write in the PCA9685 register 
  * @retval    true: The request was placed successfully and the bus activity was
  *            initiated;
  *            false: The request fails, if there was already a transfer in progress
  *            when this function was called
  * @note	   None
  */
static bool PCA9685_WriteRegister(PCA9685_I2C_ADDR_TYPE deviceAddr, PCA9685_REGISTER_TYPE regAddr, uint8 value)
{
    bool retVal;
    
    // Waiting for I2C bus is free
    while(PCA9685_I2CIsBusy() == true);
      
    writeBuffer[0] = (uint8)regAddr;
    writeBuffer[1] = value;
    retVal = PCA9685_I2CWrite(deviceAddr, writeBuffer, 2);
    
    // Waiting for I2C bus is free
    while(PCA9685_I2CIsBusy() == true);
    
    return retVal;
}

/**
  * @brief     This function read a PCA9685 register
  *
  * @param[in] deviceAddr: Address I2C of PCA9685
  * @param[in] regAddr: register address from PCA9685_REGISTER_TYPE enumeration 
  * @retval    PCA9685 register read
  * @note	   None
  */
static uint8 PCA9685_ReadRegister(PCA9685_I2C_ADDR_TYPE deviceAddr, PCA9685_REGISTER_TYPE regAddr)
{
    readVariable = 0;
    
    // Waiting for I2C module is free
    while(PCA9685_I2CIsBusy() == true);
    
    writeBuffer[0] = (uint8)regAddr;
    // Sending the PCA9685 address from which you want to read 
    PCA9685_I2CWrite(deviceAddr, writeBuffer, 1);
    
    // Waiting for I2C module is free
    while(PCA9685_I2CIsBusy() == true);
      
    // Reads the byte at the memory address requested before
    PCA9685_I2CRead(deviceAddr, &readVariable, 1);
    
    // Waiting for I2C module is free
    while(PCA9685_I2CIsBusy() == true);
    
    return readVariable;
}



/* ****************** TEST CODE *************** */
 
//void PCA9685__Initialize(void)
//{
//    // Initialize PCA9685 device
//    PCA9685_Interf.InitDevice(IO_EXP_PWM_I2C_ADDR);
//    
//    // Set default PCA9685 PWM frequency at 200Hz
//    PCA9685_Interf.SetPWMFreq(IO_EXP_PWM_I2C_ADDR, PCA9685_PWM_FREQUENCY);
//    
//    // Set all output channel to 0
//    PCA9685_Interf.SetAllPWM(IO_EXP_PWM_I2C_ADDR, 0);
//}
//
///**
//  * @brief  PCA9685 module handler. It manages all the module functionalities
//  *
//  * @param  None
//  * @retval None
//  * @note	call this function in the task every 25ms
//  */
//void PCA9685__Handler25ms(void)
//{
//    static uint8 counter;
// //   static uint8 dutyCycle = 0;
//
//    
//    if(counter == 10 || counter == 141)
//    {
//        // Set CH2 @PWM with D = 50%
//        PCA9685_Interf.SetPWM(IO_EXP_PWM_I2C_ADDR, CH2, 100);
//        
////        PCA9685_Interf.SetAllPWM(IO_EXP_PWM_I2C_ADDR, dutyCycle);
////        
////        dutyCycle++;
////        if(dutyCycle >= PCA9685_MAX_DUTY_CYCLE_VALUE)
////        {
////            dutyCycle = 0;
////        }
////        
////        printf("D= %d\r\n", dutyCycle);
//    }
// 
//    //Turn OFF the outputs for 25ms * 40 = 1s
//    if(counter >= 100 && counter <= 140)
//    {
//        PCA9685_Interf.SetPWM(IO_EXP_PWM_I2C_ADDR, CH2, 50);
//        
////       PCA9685_Interf.SetAllPWM(IO_EXP_PWM_I2C_ADDR, 0x00); 
//    }
// 
//    counter++;
//}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 