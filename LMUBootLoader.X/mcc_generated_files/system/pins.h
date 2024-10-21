/**
 * PINS Generated Driver Header File 
 * 
 * @file      pins.h
 *            
 * @defgroup  pinsdriver Pins Driver
 *            
 * @brief     The Pin Driver directs the operation and function of 
 *            the selected device pins using dsPIC MCUs.
 *
 * @skipline @version   Firmware Driver Version 1.0.2
 *
 * @skipline @version   PLIB Version 1.3.0
 *
 * @skipline  Device : dsPIC33CH512MP506
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H
// Section: Includes
#include <xc.h>

// Section: Device Pin Macros

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC6 GPIO Pin which has a custom name of OUT_GreenLED to High
 * @pre      The RC6 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define OUT_GreenLED_SetHigh()          (_LATC6 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC6 GPIO Pin which has a custom name of OUT_GreenLED to Low
 * @pre      The RC6 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define OUT_GreenLED_SetLow()           (_LATC6 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RC6 GPIO Pin which has a custom name of OUT_GreenLED
 * @pre      The RC6 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define OUT_GreenLED_Toggle()           (_LATC6 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RC6 GPIO Pin which has a custom name of OUT_GreenLED
 * @param    none
 * @return   none  
 */
#define OUT_GreenLED_GetValue()         _RC6

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC6 GPIO Pin which has a custom name of OUT_GreenLED as Input
 * @param    none
 * @return   none  
 */
#define OUT_GreenLED_SetDigitalInput()  (_TRISC6 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC6 GPIO Pin which has a custom name of OUT_GreenLED as Output
 * @param    none
 * @return   none  
 */
#define OUT_GreenLED_SetDigitalOutput() (_TRISC6 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD5 GPIO Pin which has a custom name of OUT_CONFIRM_MAINTENANCE to High
 * @pre      The RD5 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define OUT_CONFIRM_MAINTENANCE_SetHigh()          (_LATD5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD5 GPIO Pin which has a custom name of OUT_CONFIRM_MAINTENANCE to Low
 * @pre      The RD5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define OUT_CONFIRM_MAINTENANCE_SetLow()           (_LATD5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD5 GPIO Pin which has a custom name of OUT_CONFIRM_MAINTENANCE
 * @pre      The RD5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define OUT_CONFIRM_MAINTENANCE_Toggle()           (_LATD5 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD5 GPIO Pin which has a custom name of OUT_CONFIRM_MAINTENANCE
 * @param    none
 * @return   none  
 */
#define OUT_CONFIRM_MAINTENANCE_GetValue()         _RD5

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD5 GPIO Pin which has a custom name of OUT_CONFIRM_MAINTENANCE as Input
 * @param    none
 * @return   none  
 */
#define OUT_CONFIRM_MAINTENANCE_SetDigitalInput()  (_TRISD5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD5 GPIO Pin which has a custom name of OUT_CONFIRM_MAINTENANCE as Output
 * @param    none
 * @return   none  
 */
#define OUT_CONFIRM_MAINTENANCE_SetDigitalOutput() (_TRISD5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD12 GPIO Pin which has a custom name of OUT_RedLED to High
 * @pre      The RD12 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define OUT_RedLED_SetHigh()          (_LATD12 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD12 GPIO Pin which has a custom name of OUT_RedLED to Low
 * @pre      The RD12 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define OUT_RedLED_SetLow()           (_LATD12 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD12 GPIO Pin which has a custom name of OUT_RedLED
 * @pre      The RD12 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define OUT_RedLED_Toggle()           (_LATD12 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD12 GPIO Pin which has a custom name of OUT_RedLED
 * @param    none
 * @return   none  
 */
#define OUT_RedLED_GetValue()         _RD12

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD12 GPIO Pin which has a custom name of OUT_RedLED as Input
 * @param    none
 * @return   none  
 */
#define OUT_RedLED_SetDigitalInput()  (_TRISD12 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD12 GPIO Pin which has a custom name of OUT_RedLED as Output
 * @param    none
 * @return   none  
 */
#define OUT_RedLED_SetDigitalOutput() (_TRISD12 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD14 GPIO Pin which has a custom name of IN_MAINTENANCE to High
 * @pre      The RD14 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define IN_MAINTENANCE_SetHigh()          (_LATD14 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD14 GPIO Pin which has a custom name of IN_MAINTENANCE to Low
 * @pre      The RD14 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IN_MAINTENANCE_SetLow()           (_LATD14 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD14 GPIO Pin which has a custom name of IN_MAINTENANCE
 * @pre      The RD14 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IN_MAINTENANCE_Toggle()           (_LATD14 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD14 GPIO Pin which has a custom name of IN_MAINTENANCE
 * @param    none
 * @return   none  
 */
#define IN_MAINTENANCE_GetValue()         _RD14

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD14 GPIO Pin which has a custom name of IN_MAINTENANCE as Input
 * @param    none
 * @return   none  
 */
#define IN_MAINTENANCE_SetDigitalInput()  (_TRISD14 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD14 GPIO Pin which has a custom name of IN_MAINTENANCE as Output
 * @param    none
 * @return   none  
 */
#define IN_MAINTENANCE_SetDigitalOutput() (_TRISD14 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Initializes the PINS module
 * @param    none
 * @return   none  
 */
void PINS_Initialize(void);



#endif
