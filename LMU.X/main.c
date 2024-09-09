/* 
 * File:   main.c
 * Author: p.parrino
 *
 * Created on September 6, 2024, 5:05 PM
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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"



/* Pointer of type TIMER_INTERFACE and assigned it to the address of the Timer1 TIMER_INTERFACE address */
const struct TIMER_INTERFACE *Timer = &Timer1;

/* Pointer of type UART_INTERFACE and assigned it to the address of the UART1_Drv UART_INTERFACE address */
const struct UART_INTERFACE *UartSerial = &UART1_Drv;


/* Prototype definitions */
void TimerCallback250us(void);

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();
    Timer->TimeoutCallbackRegister(TimerCallback250us);

    /* CLOCK SETUP: 180MHz with external ceramic 8MHz oscillator with PLL */
    int fpValue, fcyValue;
    fpValue  = CLOCK_PeripheralFrequencyGet() / (uint32_t)1000000;
    fcyValue = CLOCK_InstructionFrequencyGet() / (uint32_t)1000000;

    printf("Start Program!\r\n");
    printf("Peripheral Clock (FP) Frequency = %dMHz\r\n", fpValue);
    printf("Instruction Clock (FCY) Frequency = %dMHz\r\n", fcyValue);
    
    while(1)
    {
    }    
}


/* 250us handler generate from Timer1 ISR */
void TimerCallback250us(void)
{
    /* Here every 250us */
    
    #define TIMER_CNT_1S    4000
    #define TIMER_CNT_01S   400
    #define TIMER_CNT_09S   3600
    
    static uint16_t timerCnt;
     
    /* Heart beat board signal on Green_LED */
    /* Toggle LED1: 0.1s ON, 0.9s OFF */
    if(timerCnt++ < TIMER_CNT_09S)
    {
        Green_LED_SetLow();
    }
    else
    {
        Green_LED_SetHigh();
        if(timerCnt >= TIMER_CNT_1S)
        {
            /* Here every 1s */
            timerCnt = 0;
            
            //adc->SoftwareTriggerEnable();   //Trigger the ADC conversion via software
            //AN0Value = adc->ConversionResultGet(AN0_Pot);
            //printf("ADC acquired: %d\r\n", AN0Value);
        }
    }
}