/**
 * INTERRUPT Generated Driver Source File 
 * 
 * @file      interrupt.c
 *            
 * @ingroup   interruptdriver
 *            
 * @brief     This is the generated driver source file for INTERRUPT driver
 *            
 * @skipline @version   Firmware Driver Version 1.1.2
 *
 * @skipline @version   PLIB Version 1.3.1
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

// Section: Includes
#include <xc.h>
#include "../interrupt.h"

// Section: Driver Interface Function Definitions

void INTERRUPT_Initialize(void)
{
    // ADCAN11: ADC AN11 Convert Done
    // Priority: 1
    IPC25bits.ADCAN11IP = 1;
    
    // ADCAN13: ADC AN13 Convert Done
    // Priority: 1
    IPC26bits.ADCAN13IP = 1;
    
    // ADCAN15: ADC AN15 Convert Done
    // Priority: 1
    IPC26bits.ADCAN15IP = 1;
    
    // ADCAN8: ADC AN8 Convert Done
    // Priority: 1
    IPC24bits.ADCAN8IP = 1;
    
    // ADCAN10: ADC AN10 Convert Done
    // Priority: 1
    IPC25bits.ADCAN10IP = 1;
    
    // ADCAN12: ADC AN12 Convert Done
    // Priority: 1
    IPC25bits.ADCAN12IP = 1;
    
    // ADC: ADC Global Interrupt
    // Priority: 1
    IPC22bits.ADCIP = 1;
    
    // ADCAN7: ADC AN7 Convert Done
    // Priority: 1
    IPC24bits.ADCAN7IP = 1;
    
    // ADCAN9: ADC AN9 Convert Done
    // Priority: 1
    IPC25bits.ADCAN9IP = 1;
    
    // ADCAN4: ADC AN4 Convert Done
    // Priority: 1
    IPC23bits.ADCAN4IP = 1;
    
    // C1: CAN 1 Combined Error
    // Priority: 1
    IPC6bits.C1IP = 1;
    
    // DMT: Dead Man Timer
    // Priority: 1
    IPC11bits.DMTIP = 1;
    
    // I2C1BC: I2C1 Bus Collision
    // Priority: 1
    IPC16bits.I2C1BCIP = 1;
    
    // MI2C1: I2C1 Master Event
    // Priority: 1
    IPC4bits.MI2C1IP = 1;
    
    // T1: Timer 1
    // Priority: 1
    IPC0bits.T1IP = 1;
    
}

void INTERRUPT_Deinitialize(void)
{
    //POR default value of priority
    IPC25bits.ADCAN11IP = 4;
    IPC26bits.ADCAN13IP = 4;
    IPC26bits.ADCAN15IP = 4;
    IPC24bits.ADCAN8IP = 4;
    IPC25bits.ADCAN10IP = 4;
    IPC25bits.ADCAN12IP = 4;
    IPC22bits.ADCIP = 4;
    IPC24bits.ADCAN7IP = 4;
    IPC25bits.ADCAN9IP = 4;
    IPC23bits.ADCAN4IP = 4;
    IPC6bits.C1IP = 4;
    IPC11bits.DMTIP = 4;
    IPC16bits.I2C1BCIP = 4;
    IPC4bits.MI2C1IP = 4;
    IPC0bits.T1IP = 4;
}
