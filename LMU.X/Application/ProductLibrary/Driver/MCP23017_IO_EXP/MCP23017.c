/**
 *  @file       MCP23017.c
 *  @brief      Driver for MCP23017 16 bit I/O Expander with I2C Serial Interface
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

#include "../../ProductLibraryInclude/MCP23017.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
static uint8 writeBuffer[2];
static uint8 readVariable;

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static bool  MCP23017_WriteRegister (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_REGISTER_TYPE regAddr, uint8 value);
static uint8 MCP23017_ReadRegister  (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_REGISTER_TYPE regAddr);

static void  MCP23017_InitDevice          (MCP23017_I2C_ADDR_TYPE deviceAddr, uint8 portADirection, uint8 portBDirection);
static void  MCP23017_SetPinDirection     (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin, bool direction);
static void  MCP23017_WritePin            (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin, bool value);
static bool  MCP23017_WritePort           (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, uint8_t value);
static bool  MCP23017_ReadPin             (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin);
static uint8 MCP23017_ReadPort            (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port);
static void  MCP23017_EnableInterrupt     (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin, bool compare_default);
static bool  MCP23017_GetInterruptFlag    (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin);
static bool  MCP23017_GetInterruptCapture (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin);

const struct MCP23017_INTRFACE_STRUCT MCP23017_Interf =
{
    .Initialize          = &MCP23017__Initialize,
    .Handler5ms          = &MCP23017__Handler5ms,
    .InitDevice          = &MCP23017_InitDevice,
    .SetPinDirection     = &MCP23017_SetPinDirection,
    .WritePin            = &MCP23017_WritePin,
    .WritePort           = &MCP23017_WritePort,
    .ReadPin             = &MCP23017_ReadPin,
    .ReadPort            = &MCP23017_ReadPort,
    .EnableInterrupt     = &MCP23017_EnableInterrupt,
    .GetInterruptFlag    = &MCP23017_GetInterruptFlag,
    .GetInterruptCapture = &MCP23017_GetInterruptCapture,
};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes the MCP23017 module
  *
  * @param  None
  * @retval None
  * @note	None
  */
void MCP23017__Initialize(void)
{

}

/**
  * @brief  MCP23017 module handler. It manages all the module functionalities
  *
  * @param  None
  * @retval None
  * @note	call this function in the task every 5ms
  */
void MCP23017__Handler5ms(void)
{
 
}

/**
  * @brief     Initialization of MCP23017 device. Set all pins as inputs or outputs for both GPIOA and GPIOB ports.
  *            REMEBER: GPA7 and GPB7 can be set ONLY as Output!!! 
  * 
  * @param[in] deviceAddr: Address I2C of MCP23017
  * @param[in] portADirection: Set all MCP23017_PORTA pins as input o output: 0 = Output; 1 = Input
  * @param[in] portBDirection: Set all MCP23017_PORTB pins as input o output: 0 = Output; 1 = Input
  * @retval    None
  * @note	   None
  */
static void MCP23017_InitDevice(MCP23017_I2C_ADDR_TYPE deviceAddr, uint8 portADirection, uint8 portBDirection)
{
    //MCP23017_WriteRegister(deviceAddr, MCP23017_IOCON, 0b00100000);            // INTCON = 0 (set BANK0: the registers are in the same bank, The INT pins are not connected)
                                                                                 // Settings: SEQOP = 1 (Sequential operation disabled, address pointer does not increment)
    MCP23017_WriteRegister(deviceAddr, MCP23017_IODIR_A, portADirection);        // Set all MCP23017_PORTA pins as input or output
    MCP23017_WriteRegister(deviceAddr, MCP23017_IODIR_B, portBDirection);        // Set all MCP23017_PORTB pins as input or output
}

/**
 * @brief     This function sets one pin direction (Input or Output).
 * 
 * @param[in] deviceAddr: Address I2C of MCP23017
 * @param[in] port: 'MCP23017_PORTA' or 'MCP23017_PORTB' to select GPIOA or GPIOB
 * @param[in] pin: pin number from MCP23017_PIN_TYPE enumeration
 * @param[in] direction: true = set pin as input; false = set pin as output
 * @retval    None
 * @note	  None
 */
static void MCP23017_SetPinDirection(MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin, bool direction)
{
    uint8 reg;
    uint8 portValue;
    
    if(port == MCP23017_PORTA)
    {
        reg = MCP23017_IODIR_A;
    }
    else
    {
        reg = MCP23017_IODIR_B;
    }
    
    portValue = MCP23017_ReadRegister(deviceAddr, reg);
    
    if(direction == 1)
    {
        if(port == MCP23017_PORTA)
        {
            portValue |= (1 << pin);            // Set to 1 for input
        }
        else
        {
            portValue |= (1 << (pin - GPB0));   // Set to 1 for input
        }
    }
    else
    {
        if(port == MCP23017_PORTA)
        {
            portValue &= ~(1 << pin);           // Set to 0 for output
        }
        else
        {
            portValue &= ~(1 << (pin - GPB0)); // Set to 0 for output
        }
    }
    
    MCP23017_WriteRegister(deviceAddr, reg, portValue);
}

/**
 * @brief     This function writes a single pin, High or Low
 * 
 * @param[in] deviceAddr: Address I2C of MCP23017
 * @param[in] port: 'MCP23017_PORTA' or 'MCP23017_PORTB' to select GPIOA or GPIOB
 * @param[in] pin: pin number from MCP23017_PIN_TYPE enumeration
 * @param[in] value: true = set pin HIGH; false: set pin LOW
 * @retval    None
 * @note	  None
 */
static void MCP23017_WritePin(MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin, bool value)
{
    uint8 reg;
    uint8 gpioValue;
    
    if(port == MCP23017_PORTA)
    {
        reg = MCP23017_OLAT_A;
    }
    else
    {
        reg = MCP23017_OLAT_B;
    }
    
    gpioValue = MCP23017_ReadRegister(deviceAddr, reg);
    
    if(value == 1)
    {
        if(port == MCP23017_PORTA)
        {
            gpioValue |= (1 << pin);            // Set to High the bit in the port
        }
        else
        {
            gpioValue |= (1 << (pin - GPB0));   // Set to High the bit in the port
        }
    }
    else
    {
        if(port == MCP23017_PORTA)
        {
            gpioValue &= ~(1 << pin);           // Set to Low the bit in the port
        }
        else
        {
            gpioValue &= ~(1 << (pin - GPB0));  // Set to Low the bit in the port
        }
    }
    
    MCP23017_WriteRegister(deviceAddr, reg, gpioValue);
}

/**
 * @brief     This function writes all 8 bits on MCP23017 port.
 * 
 * @param[in] deviceAddr: Address I2C of MCP23017
 * @param[in] port: 'MCP23017_PORTA' or 'MCP23017_PORTB' to select GPIOA or GPIOB
 * @param[in] value: 8-bit value to be written to the port
 * @retval    true: writing was successful; false: no writing
 * @note	  None
 */
static bool MCP23017_WritePort(MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, uint8_t value)
{
    bool retVal = false;
    uint8 reg;
    
    if((port == MCP23017_PORTA) || (port == MCP23017_PORTB))
    {
        if(port == MCP23017_PORTA)
        {
            reg = MCP23017_GPIO_A;
        }
        else
        {
            reg = MCP23017_GPIO_B;
        }

        retVal = MCP23017_WriteRegister(deviceAddr, reg, value);
    }
    else
    {
        // Selected wrong port  !!!
        retVal = 0;
    }
    return retVal;
}

/**
 * @brief     This function reads the single pin status.
 * 
 * @param[in] deviceAddr: Address I2C of MCP23017
 * @param[in] port: 'MCP23017_PORTA' or 'MCP23017_PORTB' to select GPIOA or GPIOB
 * @param[in] pin: pin number from MCP23017_PIN_TYPE enumeration
 * @retval    true: if the read pin is HIGH; false: if the read pin is LOW
 * @note	  None
 */
static bool MCP23017_ReadPin(MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin)
{
    bool  retVal;
    uint8 reg;
    uint8 gpioValue;
    
    if(port == MCP23017_PORTA)
    {
        reg = MCP23017_GPIO_A;
    }
    else
    {
        reg = MCP23017_GPIO_B;
    }
    
    gpioValue = MCP23017_ReadRegister(deviceAddr, reg);
    
    if(port == MCP23017_PORTA)
    {
        retVal = (gpioValue & (1 << pin)) != 0;
    }
    else
    {
        retVal = (gpioValue & (1 << (pin - GPB0))) != 0;
    }

    return retVal;
}

/**
 * @brief     This function reads the value of an entire port
 * 
 * @param[in] deviceAddr: Address I2C of MCP23017
 * @param[in] port: 'MCP23017_PORTA' or 'MCP23017_PORTB' to select GPIOA or GPIOB
 * @retval    8 bits value read from the port
 * @note	  None
 */
static uint8 MCP23017_ReadPort(MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port)
{
    uint8 retVal;
    uint8 reg;
        
    if((port == MCP23017_PORTA) || (port == MCP23017_PORTB))
    {
        if(port == MCP23017_PORTA)
        {
            reg = MCP23017_GPIO_A;
        }
        else
        {
            reg = MCP23017_GPIO_B;
        }
        
        retVal = MCP23017_ReadRegister(deviceAddr, reg);
    }
    else
    {
        // Selected wrong port  !!!
        retVal = 0;
    }

    return retVal;
}

/**
 * @brief     This function enables the Interrupt on a single pin
 * 
 * @param[in] deviceAddr: Address I2C of MCP23017
 * @param[in] port: 'MCP23017_PORTA' or 'MCP23017_PORTB' to select GPIOA or GPIOB
 * @param[in] pin: pin number from MCP23017_PIN_TYPE enumeration
 * @param[in] compare_default: true to compare with default value; false to compare with previous value
 * @retval    None
 * @note	  None
 */
static void MCP23017_EnableInterrupt(MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin, bool compare_default)
{
    uint8 regINTEN;
    uint8 regINTCON;
    uint8 regDEFVAL;
    uint8 intEnableValue;
    uint8 intConfigValue;
    uint8 defVal;
    
    if(port == MCP23017_PORTA)
    {
        regINTEN  = MCP23017_GPINTEN_A;
        regINTCON = MCP23017_INTCON_A;
        regDEFVAL = MCP23017_DEFVAL_A;
    }
    else
    {
        regINTEN  = MCP23017_GPINTEN_B;
        regINTCON = MCP23017_INTCON_B;
        regDEFVAL = MCP23017_DEFVAL_B;
    }
    
    /* Enabled Interrupt on specific pin */
    intEnableValue = MCP23017_ReadRegister(deviceAddr, regINTEN);
    if(port == MCP23017_PORTA)
    {
        intEnableValue |= (1 << pin);
    }
    else
    {
        intEnableValue |= (1 << (pin - GPB0));
    }
    MCP23017_WriteRegister(deviceAddr, regINTEN, intEnableValue);
    
    /* Configure comparison behavior */
    intConfigValue = MCP23017_ReadRegister(deviceAddr, regINTEN);
    if(compare_default == true)
    {
        // Comparison with default value
        if(port == MCP23017_PORTA)
        {
            intConfigValue |= (1 << pin);
        }
        else
        {
            intConfigValue |= (1 << (pin - GPB0));
        }
        defVal = MCP23017_ReadRegister(deviceAddr, regDEFVAL);
        
        // Set the default to High
        if(port == MCP23017_PORTA)
        {
            defVal |= (1 << pin);
        }
        else
        {
            defVal |= (1 << (pin - GPB0));
        }
        MCP23017_WriteRegister(deviceAddr, regDEFVAL, defVal);
    }
    else
    {
        // Comparison with previous value
        if(port == MCP23017_PORTA)
        {
            intConfigValue &= ~(1 << pin);
        }
        else
        {
            intConfigValue &= ~(1 << (pin - GPB0));
        }
    }
    MCP23017_WriteRegister(deviceAddr, regINTCON, intConfigValue); 
}

/**
 * @brief     This function reads the pin Interrupt flag
 * 
 * @param[in] deviceAddr: Address I2C of MCP23017
 * @param[in] port: 'MCP23017_PORTA' or 'MCP23017_PORTB' to select GPIOA or GPIOB
 * @param[in] pin: pin number from MCP23017_PIN_TYPE enumeration
 * @retval    true: if the Interrupt is active; false: if the Interrupt is not active
 * @note	  None
 */
static bool MCP23017_GetInterruptFlag(MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin)
{
    bool  retVal;
    uint8 reg;
    uint8 intfValue;
        
    if(port == MCP23017_PORTA)
    {
        reg = MCP23017_INTF_A;
    }
    else
    {
        reg = MCP23017_INTF_B;
    }
    
    intfValue = MCP23017_ReadRegister(deviceAddr, reg);
    
    if(port == MCP23017_PORTA)
    {
        retVal = (intfValue & (1 << pin)) != 0;
    }
    else
    {
        retVal = (intfValue & (1 << (pin - GPB0))) != 0;
    }
    
    return retVal;
}

/**
 * @brief     This function reads the captured value at the Interrupt on a pin
 * 
 * @param[in] deviceAddr: Address I2C of MCP23017
 * @param[in] port: 'MCP23017_PORTA' or 'MCP23017_PORTB' to select GPIOA or GPIOB
 * @param[in] pin: pin number from MCP23017_PIN_TYPE enumeration
 * @retval    true: if the pin was HIGH at the Interrupt event; false: if the pin was LOW at the Interrupt event
 * @note	  None
 */
static bool MCP23017_GetInterruptCapture(MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin)
{
    bool  retVal;
    uint8 reg;
    uint8 captValue;
        
    if(port == MCP23017_PORTA)
    {
        reg = MCP23017_INTCAP_A;
    }
    else
    {
        reg = MCP23017_INTCAP_B;
    }
    
    captValue = MCP23017_ReadRegister(deviceAddr, reg);
    
    if(port == MCP23017_PORTA)
    {
        retVal = (captValue & (1 << pin)) != 0;
    }
    else
    {
        retVal = (captValue & (1 << (pin - GPB0))) != 0;
    }
    
    return retVal;
}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief     This function write on a MCP23017 register
  *
  * @param[in] deviceAddr: Address I2C of MCP23017
  * @param[in] regAddr: register address from MCP23017_REGISTER_TYPE enumeration
  * @param[in] value: value that you want to write in the MCP23017 register 
  * @retval    true: The request was placed successfully and the bus activity was
  *            initiated;
  *            false: The request fails, if there was already a transfer in progress
  *            when this function was called
  * @note	   None
  */
static bool MCP23017_WriteRegister(MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_REGISTER_TYPE regAddr, uint8 value)
{
    bool retVal;
    // Waiting for I2C bus is free
    while(MCP23017_I2CIsBusy() == true);
      
    writeBuffer[0] = (uint8)regAddr;
    writeBuffer[1] = value;
    retVal = MCP23017_I2CWrite(deviceAddr, writeBuffer, 2);
    
    // Waiting for I2C bus is free
    while(MCP23017_I2CIsBusy() == true);
    
    return retVal;
}

/**
  * @brief     This function read a MCP23017 register
  *
  * @param[in] deviceAddr: Address I2C of MCP23017
  * @param[in] regAddr: register address from MCP23017_REGISTER_TYPE enumeration 
  * @retval    MCP23017 register read
  * @note	   None
  */
static uint8 MCP23017_ReadRegister(MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_REGISTER_TYPE regAddr)
{
    readVariable = 0;
    
    // Waiting for I2C module is free
    while(MCP23017_I2CIsBusy() == true);
    
    writeBuffer[0] = (uint8)regAddr;
    // Sending the MCP23017 address from which you want to read 
    MCP23017_I2CWrite(deviceAddr, writeBuffer, 1);
    
    // Waiting for I2C module is free
    while(MCP23017_I2CIsBusy() == true);
      
    // Reads the byte at the memory address requested before
    MCP23017_I2CRead(deviceAddr, &readVariable, 1);
    
    // Waiting for I2C module is free
    while(MCP23017_I2CIsBusy() == true);
    
    return readVariable;
}


//*******************************************************************************
// !!!!*** Testing module code ***!!!!
//*******************************************************************************
//void MCP23017__Handler5ms(void)
//{
//    static bool oneTimeVar = false;
//    static uint8 counter;
//    static uint8 readVar = 0;  
//    bool pinReadVar;
//     
//    if(oneTimeVar == false)
//    {
//        oneTimeVar = true;
//         
//        // IO_EXP0:Set PORTA as Input, set PORTB as Output
//        MCP23017_Interf.InitDevice(IO_EXP0_I2C_ADDR, 0xFF, 0x00);
//        
//        // IO_EXP4:Set PORTA as Output, set PORTB as Output
//        MCP23017_Interf.InitDevice(IO_EXP4_I2C_ADDR, 0x00, 0x00);
//        
//        // IO_EXP5:Set PORTA as Input, set PORTB as Input GPA7 and GPB7 as Output
//        MCP23017_Interf.InitDevice(IO_EXP5_I2C_ADDR, 0x7F, 0x7F);
//        
//        printf("I/O Expander Initialized! \r\n");
//    }
//    
//    //Write PORTB 0x82
//    if(counter == 50)
//    {
//        MCP23017_Interf.WritePort(IO_EXP0_I2C_ADDR, MCP23017_PORTB, 0x82);
//        printf("I/O_EXP0, Write PORTB = 0x82: \r\n ");
//        
//        MCP23017_Interf.WritePort(IO_EXP4_I2C_ADDR, MCP23017_PORTA, 0xA5);
//        printf("I/O_EXP4, Write PORTA = 0xA5: \r\n ");
//        MCP23017_Interf.WritePort(IO_EXP4_I2C_ADDR, MCP23017_PORTB, 0x5A);
//        printf("I/O_EXP4, Write PORTB = 0x5A: \r\n ");
//         
//    }
//    
//    // Read PORTA
//    if(counter == 55)
//    {
//        readVar = MCP23017_Interf.ReadPort(IO_EXP0_I2C_ADDR, MCP23017_PORTB);
//        printf("I/O_EXP0, PORTB value = %d\r\n ", readVar);
//        
//        readVar = MCP23017_Interf.ReadPort(IO_EXP4_I2C_ADDR, MCP23017_PORTA);
//        printf("I/O_EXP4, PORTA value = %d\r\n ", readVar);
//        readVar = MCP23017_Interf.ReadPort(IO_EXP4_I2C_ADDR, MCP23017_PORTB);
//        printf("I/O_EXP4, PORTB value = %d\r\n ", readVar);
//    }
//    
//    // Read PORTA
//    if(counter == 100)
//    {
//        readVar = MCP23017_Interf.ReadPort(IO_EXP0_I2C_ADDR, MCP23017_PORTA);
//        printf("I/O_EXP0, Read PORTA = %d\r\n ", readVar);
//        
//        readVar = MCP23017_Interf.ReadPort(IO_EXP5_I2C_ADDR, MCP23017_PORTA);
//        printf("I/O_EXP5, Read PORTA = %d\r\n ", readVar);
//        readVar = MCP23017_Interf.ReadPort(IO_EXP5_I2C_ADDR, MCP23017_PORTB);
//        printf("I/O_EXP5, Read PORTB = %d\r\n ", readVar);
//    }
//    
//    if(counter == 120)
//    {
//        // Write and set Pin 4, PORTB
//        MCP23017_Interf.WritePin(IO_EXP0_I2C_ADDR, MCP23017_PORTB, GPB4, 1);
//        printf("I/O_EXP0, Write and set Pin 4, PORTB\r\n");
//    }
//    
//    if(counter == 125)
//    {
//        // Read Pin 4, PORTB
//        pinReadVar = MCP23017_Interf.ReadPin(IO_EXP0_I2C_ADDR, MCP23017_PORTB, GPB4);
//        printf("I/O_EXP0, Read Pin 4, PORTB: %d\r\n\r\n", pinReadVar);
//    }
//    
//    
//    counter++;
//}