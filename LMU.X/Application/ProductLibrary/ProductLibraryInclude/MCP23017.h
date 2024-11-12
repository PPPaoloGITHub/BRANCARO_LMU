/**
 *  @file		MCP23017.h
 *  @brief      Driver for MCP23017 16 bit I/O Expander with I2C Serial Interface 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __MCP23017_H__
#define __MCP23017_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/i2c_host/i2c1.h"

#include "MCP23017_prm.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
/* Base address of I/O EXPANDER (7 bits, shifted left by 1bit) */
typedef enum
{
    IO_EXP0_I2C_ADDR = 0x20,
    IO_EXP1_I2C_ADDR = 0x21,
    IO_EXP2_I2C_ADDR = 0x22,
    IO_EXP3_I2C_ADDR = 0x23,
    IO_EXP4_I2C_ADDR = 0x24,
    IO_EXP5_I2C_ADDR = 0x25,
    IO_EXP6_I2C_ADDR = 0x26,
    IO_EXP7_I2C_ADDR = 0x27,            
} MCP23017_I2C_ADDR_TYPE;

/* Available ports on MCP23017 driver */
typedef enum
{
    MCP23017_PORTA = 0,
    MCP23017_PORTB = 1
} MCP23017_PORT_TYPE;

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

/* Interrupt mode: IRQ on port A and port B are kept independent or mirrored */
typedef enum
{
    MCP23017_IRQ_MODE_SEPARATED = 0,   // Interrupt pins are kept independent
    MCP23017_IRQ_MODE_OR = 0b01000000  // Interrupt pins are mirrored
} MCP23017_IRQ_MODE_TYPE;


/* MCP23017 registers address definition */
typedef enum 
{
    MCP23017_IODIR_A     = 0x00,       // Controls the direction of the data I/O for port A.
    MCP23017_IODIR_B     = 0x01,       // Controls the direction of the data I/O for port B.
    MCP23017_IPOL_A      = 0x02,       // Configures the polarity on the corresponding GPIO_ port bits for port A.
    MCP23017_IPOL_B      = 0x03,       // Configures the polarity on the corresponding GPIO_ port bits for port B.
    MCP23017_GPINTEN_A   = 0x04,       // Enables the interrupt-on-change for each pin of port A.
    MCP23017_GPINTEN_B   = 0x05,       // Enables the interrupt-on-change for each pin of port B.
    MCP23017_DEFVAL_A    = 0x06,       // Controls the default comparison value for interrupt-on-change for port A.
    MCP23017_DEFVAL_B    = 0x07,       // Controls the default comparison value for interrupt-on-change for port B.
    MCP23017_INTCON_A    = 0x08,       // Configures how the associated pin value is compared for the interrupt-on-change for port A.
    MCP23017_INTCON_B    = 0x09,       // Configures how the associated pin value is compared for the interrupt-on-change for port B.
    MCP23017_IOCON       = 0x0A,       // Register to configure the device 
    MCP23017_GPPU_A      = 0x0C,       // Controls the pull-up resistors for the port A pins.
    MCP23017_GPPU_B      = 0x0D,       // Controls the pull-up resistors for the port B pins.
    MCP23017_INTF_A      = 0x0E,       // Reflects the interrupt condition on the port A pins.
    MCP23017_INTF_B      = 0x0F,       // Reflects the interrupt condition on the port B pins.
    MCP23017_INTCAP_A    = 0x10,       // Captures the port A value at the time the interrupt occurred.
    MCP23017_INTCAP_B    = 0x11,       // Captures the port B value at the time the interrupt occurred.
    MCP23017_GPIO_A      = 0x12,       // Read and Write on PortA: it reflects the value on the port A.
    MCP23017_GPIO_B      = 0x13,       // Read and Write on PortB: it reflects the value on the port B.
    MCP23017_OLAT_A      = 0x14,       // Provides access to the port A output latches.
    MCP23017_OLAT_B      = 0x15        // Provides access to the port B output latches.
} MCP23017_REGISTER_TYPE;

struct MCP23017_INTRFACE_STRUCT
{
    void  (*Initialize)          (void);
    void  (*Handler5ms)          (void);
    void  (*InitDevice)          (MCP23017_I2C_ADDR_TYPE deviceAddr, uint8 portADirection, uint8 portBDirection);
    void  (*SetPinDirection)     (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin, bool direction);   
    void  (*WritePin)            (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin, bool value);
    bool  (*WritePort)           (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, uint8_t value);
    bool  (*ReadPin)             (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin); 
    uint8 (*ReadPort)            (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port); 
    void  (*EnableInterrupt)     (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin, bool compare_default);
    bool  (*GetInterruptFlag)    (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin);
    bool  (*GetInterruptCapture) (MCP23017_I2C_ADDR_TYPE deviceAddr, MCP23017_PORT_TYPE port, MCP23017_PIN_TYPE pin);
};


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct MCP23017_INTRFACE_STRUCT MCP23017_Interf;

void MCP23017__Initialize(void);
void MCP23017__Handler5ms(void);

#endif /* __MCP23017_H__ */
