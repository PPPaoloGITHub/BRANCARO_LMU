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
 * @brief    Sets the RC6 GPIO Pin which has a custom name of DO_Green_LED to High
 * @pre      The RC6 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define DO_Green_LED_SetHigh()          (_LATC6 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC6 GPIO Pin which has a custom name of DO_Green_LED to Low
 * @pre      The RC6 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DO_Green_LED_SetLow()           (_LATC6 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RC6 GPIO Pin which has a custom name of DO_Green_LED
 * @pre      The RC6 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DO_Green_LED_Toggle()           (_LATC6 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RC6 GPIO Pin which has a custom name of DO_Green_LED
 * @param    none
 * @return   none  
 */
#define DO_Green_LED_GetValue()         _RC6

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC6 GPIO Pin which has a custom name of DO_Green_LED as Input
 * @param    none
 * @return   none  
 */
#define DO_Green_LED_SetDigitalInput()  (_TRISC6 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC6 GPIO Pin which has a custom name of DO_Green_LED as Output
 * @param    none
 * @return   none  
 */
#define DO_Green_LED_SetDigitalOutput() (_TRISC6 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD5 GPIO Pin which has a custom name of DO_CONFIRM_MAINTENANCE to High
 * @pre      The RD5 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define DO_CONFIRM_MAINTENANCE_SetHigh()          (_LATD5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD5 GPIO Pin which has a custom name of DO_CONFIRM_MAINTENANCE to Low
 * @pre      The RD5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DO_CONFIRM_MAINTENANCE_SetLow()           (_LATD5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD5 GPIO Pin which has a custom name of DO_CONFIRM_MAINTENANCE
 * @pre      The RD5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DO_CONFIRM_MAINTENANCE_Toggle()           (_LATD5 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD5 GPIO Pin which has a custom name of DO_CONFIRM_MAINTENANCE
 * @param    none
 * @return   none  
 */
#define DO_CONFIRM_MAINTENANCE_GetValue()         _RD5

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD5 GPIO Pin which has a custom name of DO_CONFIRM_MAINTENANCE as Input
 * @param    none
 * @return   none  
 */
#define DO_CONFIRM_MAINTENANCE_SetDigitalInput()  (_TRISD5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD5 GPIO Pin which has a custom name of DO_CONFIRM_MAINTENANCE as Output
 * @param    none
 * @return   none  
 */
#define DO_CONFIRM_MAINTENANCE_SetDigitalOutput() (_TRISD5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD12 GPIO Pin which has a custom name of DO_Red_LED to High
 * @pre      The RD12 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define DO_Red_LED_SetHigh()          (_LATD12 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD12 GPIO Pin which has a custom name of DO_Red_LED to Low
 * @pre      The RD12 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DO_Red_LED_SetLow()           (_LATD12 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD12 GPIO Pin which has a custom name of DO_Red_LED
 * @pre      The RD12 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DO_Red_LED_Toggle()           (_LATD12 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD12 GPIO Pin which has a custom name of DO_Red_LED
 * @param    none
 * @return   none  
 */
#define DO_Red_LED_GetValue()         _RD12

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD12 GPIO Pin which has a custom name of DO_Red_LED as Input
 * @param    none
 * @return   none  
 */
#define DO_Red_LED_SetDigitalInput()  (_TRISD12 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD12 GPIO Pin which has a custom name of DO_Red_LED as Output
 * @param    none
 * @return   none  
 */
#define DO_Red_LED_SetDigitalOutput() (_TRISD12 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD14 GPIO Pin which has a custom name of DI_MAINTENANCE to High
 * @pre      The RD14 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define DI_MAINTENANCE_SetHigh()          (_LATD14 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD14 GPIO Pin which has a custom name of DI_MAINTENANCE to Low
 * @pre      The RD14 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DI_MAINTENANCE_SetLow()           (_LATD14 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD14 GPIO Pin which has a custom name of DI_MAINTENANCE
 * @pre      The RD14 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DI_MAINTENANCE_Toggle()           (_LATD14 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD14 GPIO Pin which has a custom name of DI_MAINTENANCE
 * @param    none
 * @return   none  
 */
#define DI_MAINTENANCE_GetValue()         _RD14

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD14 GPIO Pin which has a custom name of DI_MAINTENANCE as Input
 * @param    none
 * @return   none  
 */
#define DI_MAINTENANCE_SetDigitalInput()  (_TRISD14 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD14 GPIO Pin which has a custom name of DI_MAINTENANCE as Output
 * @param    none
 * @return   none  
 */
#define DI_MAINTENANCE_SetDigitalOutput() (_TRISD14 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD15 GPIO Pin which has a custom name of DO_HEARTBEAT to High
 * @pre      The RD15 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define DO_HEARTBEAT_SetHigh()          (_LATD15 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD15 GPIO Pin which has a custom name of DO_HEARTBEAT to Low
 * @pre      The RD15 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DO_HEARTBEAT_SetLow()           (_LATD15 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD15 GPIO Pin which has a custom name of DO_HEARTBEAT
 * @pre      The RD15 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DO_HEARTBEAT_Toggle()           (_LATD15 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD15 GPIO Pin which has a custom name of DO_HEARTBEAT
 * @param    none
 * @return   none  
 */
#define DO_HEARTBEAT_GetValue()         _RD15

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD15 GPIO Pin which has a custom name of DO_HEARTBEAT as Input
 * @param    none
 * @return   none  
 */
#define DO_HEARTBEAT_SetDigitalInput()  (_TRISD15 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD15 GPIO Pin which has a custom name of DO_HEARTBEAT as Output
 * @param    none
 * @return   none  
 */
#define DO_HEARTBEAT_SetDigitalOutput() (_TRISD15 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Initializes the PINS module
 * @param    none
 * @return   none  
 */
void PINS_Initialize(void);



#endif
