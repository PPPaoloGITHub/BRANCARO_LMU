/**
 * ADC1 Generated Driver Source File
 * 
 * @file      adc1.c
 *            
 * @ingroup   adcdriver
 *            
 * @brief     This is the generated driver source file for ADC1 driver
 *            
 * @skipline @version   Firmware Driver Version 1.4.4
 *
 * @skipline @version   PLIB Version 2.4.3
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

// Section: Included Files
#include <stddef.h>
#include "../adc1.h"

// Section: File specific functions

static void (*ADC1_CommonHandler)(void) = NULL;
static void (*ADC1_ChannelHandler)(enum ADC_CHANNEL channel, uint16_t adcVal) = NULL;
static void (*ADC1_ComparatorHandler)(enum ADC_CMP comparator) = NULL;

// Section: File specific data type definitions

/**
 @ingroup  adcdriver
 @enum     ADC_PWM_TRIG_SRCS
 @brief    Defines the PWM ADC TRIGGER sources available for the module to use.
*/
enum ADC_PWM_TRIG_SRCS {
    S1_PWM8_TRIGGER2 = 0x1b, 
    S1_PWM5_TRIGGER2 = 0x1a, 
    S1_PWM3_TRIGGER2 = 0x19, 
    S1_PWM1_TRIGGER2 = 0x18, 
    PWM4_TRIGGER2 = 0xb, 
    PWM4_TRIGGER1 = 0xa, 
    PWM3_TRIGGER2 = 0x9, 
    PWM3_TRIGGER1 = 0x8, 
    PWM2_TRIGGER2 = 0x7, 
    PWM2_TRIGGER1 = 0x6, 
    PWM1_TRIGGER2 = 0x5, 
    PWM1_TRIGGER1 = 0x4, 
};

//Defines an object for ADC_MULTICORE.
const struct ADC_MULTICORE adc1Multicore = {
    .ChannelTasks                           = &ADC1_ChannelTasks, 
    .ComparatorTasks                        = NULL,
    .IndividualChannelInterruptEnable       = &ADC1_IndividualChannelInterruptEnable,
    .IndividualChannelInterruptDisable      = &ADC1_IndividualChannelInterruptDisable,
    .IndividualChannelInterruptFlagClear    = &ADC1_IndividualChannelInterruptFlagClear,
    .IndividualChannelInterruptPrioritySet  = &ADC1_IndividualChannelInterruptPrioritySet,
    .ChannelCallbackRegister                = &ADC1_ChannelCallbackRegister,
    .ComparatorCallbackRegister             = &ADC1_ComparatorCallbackRegister,
    .CorePowerEnable                        = NULL,
    .SharedCorePowerEnable                  = &ADC1_SharedCorePowerEnable,
    .PWMTriggerSourceSet                    = &ADC1_PWMTriggerSourceSet
};

//Defines an object for ADC_INTERFACE.

const struct ADC_INTERFACE ADC1 = {
    .Initialize             = &ADC1_Initialize,
    .Deinitialize           = &ADC1_Deinitialize,
    .Enable                 = &ADC1_Enable,
    .Disable                = &ADC1_Disable,
    .SoftwareTriggerEnable  = &ADC1_SoftwareTriggerEnable,
    .SoftwareTriggerDisable = &ADC1_SoftwareTriggerDisable,
    .ChannelSelect          = &ADC1_ChannelSelect, 
    .ConversionResultGet    = &ADC1_ConversionResultGet,
    .IsConversionComplete   = &ADC1_IsConversionComplete,
    .ResolutionSet          = &ADC1_ResolutionSet,
    .InterruptEnable        = &ADC1_InterruptEnable,
    .InterruptDisable       = &ADC1_InterruptDisable,
    .InterruptFlagClear     = &ADC1_InterruptFlagClear,
    .InterruptPrioritySet   = &ADC1_InterruptPrioritySet,
    .CommonCallbackRegister = &ADC1_CommonCallbackRegister,
    .Tasks                  = &ADC1_Tasks,
    .adcMulticoreInterface = &adc1Multicore,
};

// Section: Driver Interface Function Definitions

void ADC1_Initialize (void)
{
    // ADSIDL disabled; ADON enabled; 
    ADCON1L = (uint16_t)0x8000 & (uint16_t)0x7FFF; //Disabling ADON bit
    // SHRRES 12-bit resolution; FORM Integer; 
    ADCON1H = 0x60;
    // SHRADCS 2; SHREISEL Early interrupt is generated 1 TADCORE clock prior to data being ready; PTGEN disabled; EIEN disabled; REFERCIE disabled; REFCIE disabled; 
    ADCON2L = 0x0;
    // SHRSAMC 538; 
    ADCON2H = 0x21A;
    // CNVCHSEL AN0; SWCTRG disabled; SWLCTRG disabled; SHRSAMP disabled; SUSPCIE disabled; SUSPEND disabled; REFSEL disabled; 
    ADCON3L = 0x0;
    // SHREN enabled; CLKDIV 1; CLKSEL FOSC/2; 
    ADCON3H = (uint16_t)0x80 & (uint16_t)0xFF00; //Disabling C0EN, C1EN, C2EN, C3EN and SHREN bits
    // SIGN0 disabled; SIGN1 disabled; SIGN2 disabled; SIGN3 disabled; SIGN4 disabled; SIGN5 disabled; SIGN6 disabled; SIGN7 disabled; 
    ADMOD0L = 0x0;
    // SIGN8 disabled; SIGN9 disabled; SIGN10 disabled; SIGN11 disabled; SIGN12 disabled; SIGN13 disabled; SIGN14 disabled; SIGN15 disabled; 
    ADMOD0H = 0x0;
    // SIGN16 disabled; SIGN17 disabled; SIGN18 disabled; SIGN19 disabled; SIGN20 disabled; 
    ADMOD1L = 0x0;
    // IE0 disabled; IE1 disabled; IE2 disabled; IE3 disabled; IE4 enabled; IE5 disabled; IE6 disabled; IE7 enabled; IE8 disabled; IE9 enabled; IE10 enabled; IE11 enabled; IE12 enabled; IE13 enabled; IE14 disabled; IE15 enabled; 
    ADIEL = 0xBE90;
    // IE16 disabled; IE17 disabled; IE18 disabled; IE19 disabled; IE20 disabled; 
    ADIEH = 0x0;
    // 
    ADSTATL = 0x0;
    // 
    ADSTATH = 0x0;
    // CMPEN0 disabled; CMPEN1 disabled; CMPEN2 disabled; CMPEN3 disabled; CMPEN4 disabled; CMPEN5 disabled; CMPEN6 disabled; CMPEN7 disabled; CMPEN8 disabled; CMPEN9 disabled; CMPEN10 disabled; CMPEN11 disabled; CMPEN12 disabled; CMPEN13 disabled; CMPEN14 disabled; CMPEN15 disabled; 
    ADCMP0ENL = 0x0;
    // CMPEN0 disabled; CMPEN1 disabled; CMPEN2 disabled; CMPEN3 disabled; CMPEN4 disabled; CMPEN5 disabled; CMPEN6 disabled; CMPEN7 disabled; CMPEN8 disabled; CMPEN9 disabled; CMPEN10 disabled; CMPEN11 disabled; CMPEN12 disabled; CMPEN13 disabled; CMPEN14 disabled; CMPEN15 disabled; 
    ADCMP1ENL = 0x0;
    // CMPEN0 disabled; CMPEN1 disabled; CMPEN2 disabled; CMPEN3 disabled; CMPEN4 disabled; CMPEN5 disabled; CMPEN6 disabled; CMPEN7 disabled; CMPEN8 disabled; CMPEN9 disabled; CMPEN10 disabled; CMPEN11 disabled; CMPEN12 disabled; CMPEN13 disabled; CMPEN14 disabled; CMPEN15 disabled; 
    ADCMP2ENL = 0x0;
    // CMPEN0 disabled; CMPEN1 disabled; CMPEN2 disabled; CMPEN3 disabled; CMPEN4 disabled; CMPEN5 disabled; CMPEN6 disabled; CMPEN7 disabled; CMPEN8 disabled; CMPEN9 disabled; CMPEN10 disabled; CMPEN11 disabled; CMPEN12 disabled; CMPEN13 disabled; CMPEN14 disabled; CMPEN15 disabled; 
    ADCMP3ENL = 0x0;
    // CMPEN16 disabled; CMPEN17 disabled; CMPEN18 disabled; CMPEN19 disabled; CMPEN20 disabled; 
    ADCMP0ENH = 0x0;
    // CMPEN16 disabled; CMPEN17 disabled; CMPEN18 disabled; CMPEN19 disabled; CMPEN20 disabled; 
    ADCMP1ENH = 0x0;
    // CMPEN16 disabled; CMPEN17 disabled; CMPEN18 disabled; CMPEN19 disabled; CMPEN20 disabled; 
    ADCMP2ENH = 0x0;
    // CMPEN16 disabled; CMPEN17 disabled; CMPEN18 disabled; CMPEN19 disabled; CMPEN20 disabled; 
    ADCMP3ENH = 0x0;
    // CMPLO 0x0; 
    ADCMP0LO = 0x0;
    // CMPLO 0x0; 
    ADCMP1LO = 0x0;
    // CMPLO 0x0; 
    ADCMP2LO = 0x0;
    // CMPLO 0x0; 
    ADCMP3LO = 0x0;
    // CMPHI 0x0; 
    ADCMP0HI = 0x0;
    // CMPHI 0x0; 
    ADCMP1HI = 0x0;
    // CMPHI 0x0; 
    ADCMP2HI = 0x0;
    // CMPHI 0x0; 
    ADCMP3HI = 0x0;
    // 
    ADFL0DAT = 0x0;
    // 
    ADFL1DAT = 0x0;
    // 
    ADFL2DAT = 0x0;
    // 
    ADFL3DAT = 0x0;
    // FLCHSEL AN0; IE disabled; OVRSAM 4x; MODE Oversampling Mode; FLEN disabled; 
    ADFL0CON = 0x400;
    // FLCHSEL AN0; IE disabled; OVRSAM 4x; MODE Oversampling Mode; FLEN disabled; 
    ADFL1CON = 0x400;
    // FLCHSEL AN0; IE disabled; OVRSAM 4x; MODE Oversampling Mode; FLEN disabled; 
    ADFL2CON = 0x400;
    // FLCHSEL AN0; IE disabled; OVRSAM 4x; MODE Oversampling Mode; FLEN disabled; 
    ADFL3CON = 0x400;
    // LOLO disabled; LOHI disabled; HILO disabled; HIHI disabled; BTWN disabled; IE disabled; CMPEN disabled; 
    ADCMP0CON = 0x0;
    // LOLO disabled; LOHI disabled; HILO disabled; HIHI disabled; BTWN disabled; IE disabled; CMPEN disabled; 
    ADCMP1CON = 0x0;
    // LOLO disabled; LOHI disabled; HILO disabled; HIHI disabled; BTWN disabled; IE disabled; CMPEN disabled; 
    ADCMP2CON = 0x0;
    // LOLO disabled; LOHI disabled; HILO disabled; HIHI disabled; BTWN disabled; IE disabled; CMPEN disabled; 
    ADCMP3CON = 0x0;
    // LVLEN0 disabled; LVLEN1 disabled; LVLEN2 disabled; LVLEN3 disabled; LVLEN4 disabled; LVLEN5 disabled; LVLEN6 disabled; LVLEN7 disabled; LVLEN8 disabled; LVLEN9 disabled; LVLEN10 disabled; LVLEN11 disabled; LVLEN12 disabled; LVLEN13 disabled; LVLEN14 disabled; LVLEN15 disabled; 
    ADLVLTRGL = 0x0;
    // LVLEN16 disabled; LVLEN17 disabled; LVLEN18 disabled; LVLEN19 disabled; LVLEN20 disabled; 
    ADLVLTRGH = 0x0;
    // EIEN0 disabled; EIEN1 disabled; EIEN2 disabled; EIEN3 disabled; EIEN4 disabled; EIEN5 disabled; EIEN6 disabled; EIEN7 disabled; EIEN8 disabled; EIEN9 disabled; EIEN10 disabled; EIEN11 disabled; EIEN12 disabled; EIEN13 disabled; EIEN14 disabled; EIEN15 disabled; 
    ADEIEL = 0x0;
    // EIEN16 disabled; EIEN17 disabled; EIEN18 disabled; EIEN19 disabled; EIEN20 disabled; 
    ADEIEH = 0x0;
    // EISTAT0 disabled; EISTAT1 disabled; EISTAT2 disabled; EISTAT3 disabled; EISTAT4 disabled; EISTAT5 disabled; EISTAT6 disabled; EISTAT7 disabled; EISTAT8 disabled; EISTAT9 disabled; EISTAT10 disabled; EISTAT11 disabled; EISTAT12 disabled; EISTAT13 disabled; EISTAT14 disabled; EISTAT15 disabled; 
    ADEISTATL = 0x0;
    // EISTAT16 disabled; EISTAT17 disabled; EISTAT18 disabled; EISTAT19 disabled; EISTAT20 disabled; 
    ADEISTATH = 0x0;
    // SHRCIE disabled; WARMTIME 16 Source Clock Periods; 
    ADCON5H = (uint16_t)0x400 & (uint16_t)0xF0FF; //Disabling WARMTIME bit
    // 
    ADCBUF0 = 0x0;
    // 
    ADCBUF1 = 0x0;
    // 
    ADCBUF2 = 0x0;
    // 
    ADCBUF3 = 0x0;
    // 
    ADCBUF4 = 0x0;
    // 
    ADCBUF5 = 0x0;
    // 
    ADCBUF6 = 0x0;
    // 
    ADCBUF7 = 0x0;
    // 
    ADCBUF8 = 0x0;
    // 
    ADCBUF9 = 0x0;
    // 
    ADCBUF10 = 0x0;
    // 
    ADCBUF11 = 0x0;
    // 
    ADCBUF12 = 0x0;
    // 
    ADCBUF13 = 0x0;
    // 
    ADCBUF14 = 0x0;
    // 
    ADCBUF15 = 0x0;
    // 
    ADCBUF16 = 0x0;
    // 
    ADCBUF17 = 0x0;
    // 
    ADCBUF18 = 0x0;
    // 
    ADCBUF19 = 0x0;
    // 
    ADCBUF20 = 0x0;
        
    ADC1_CommonCallbackRegister(&ADC1_CommonCallback);
    ADC1_ChannelCallbackRegister(&ADC1_ChannelCallback);
    ADC1_ComparatorCallbackRegister(&ADC1_ComparatorCallback);
    
    // Clearing ADC1 interrupt.
    IFS5bits.ADCIF = 0;
    // Enabling ADC1 interrupt.
    IEC5bits.ADCIE = 1;
    // Clearing AN4_IeCB100A interrupt flag.
    IFS5bits.ADCAN4IF = 0;
    // Enabling AN4_IeCB100A interrupt.
    IEC5bits.ADCAN4IE = 1;
    // Clearing AN7_I_PWR1 interrupt flag.
    IFS6bits.ADCAN7IF = 0;
    // Enabling AN7_I_PWR1 interrupt.
    IEC6bits.ADCAN7IE = 1;
    // Clearing AN9_V_GPU interrupt flag.
    IFS6bits.ADCAN9IF = 0;
    // Enabling AN9_V_GPU interrupt.
    IEC6bits.ADCAN9IE = 1;
    // Clearing AN10_I_PWR2 interrupt flag.
    IFS6bits.ADCAN10IF = 0;
    // Enabling AN10_I_PWR2 interrupt.
    IEC6bits.ADCAN10IE = 1;
    // Clearing AN11_V_PWR2 interrupt flag.
    IFS6bits.ADCAN11IF = 0;
    // Enabling AN11_V_PWR2 interrupt.
    IEC6bits.ADCAN11IE = 1;
    // Clearing AN12_V_PWR1 interrupt flag.
    IFS6bits.ADCAN12IF = 0;
    // Enabling AN12_V_PWR1 interrupt.
    IEC6bits.ADCAN12IE = 1;
    // Clearing AN13_V_BATTERY interrupt flag.
    IFS6bits.ADCAN13IF = 0;
    // Enabling AN13_V_BATTERY interrupt.
    IEC6bits.ADCAN13IE = 1;
    // Clearing AN15_T_LOGIC_BOARD interrupt flag.
    IFS6bits.ADCAN15IF = 0;
    // Enabling AN15_T_LOGIC_BOARD interrupt.
    IEC6bits.ADCAN15IE = 1;

    // Setting WARMTIME bit
    ADCON5Hbits.WARMTIME = 0xF;
    // Enabling ADC Module
    ADCON1Lbits.ADON = 0x1;
    // Enabling Power for the Shared Core
    ADC1_SharedCorePowerEnable();

    //TRGSRC0 None; TRGSRC1 None; 
    ADTRIG0L = 0x0;
    //TRGSRC2 None; TRGSRC3 None; 
    ADTRIG0H = 0x0;
    //TRGSRC4 Common Software Trigger; TRGSRC5 None; 
    ADTRIG1L = 0x1;
    //TRGSRC6 None; TRGSRC7 Common Software Trigger; 
    ADTRIG1H = 0x100;
    //TRGSRC8 None; TRGSRC9 Common Software Trigger; 
    ADTRIG2L = 0x100;
    //TRGSRC10 Common Software Trigger; TRGSRC11 Common Software Trigger; 
    ADTRIG2H = 0x101;
    //TRGSRC12 Common Software Trigger; TRGSRC13 Common Software Trigger; 
    ADTRIG3L = 0x101;
    //TRGSRC14 None; TRGSRC15 Common Software Trigger; 
    ADTRIG3H = 0x100;
    //TRGSRC16 None; TRGSRC17 None; 
    ADTRIG4L = 0x0;
    //TRGSRC18 None; TRGSRC19 None; 
    ADTRIG4H = 0x0;
    //TRGSRC20 None; 
    ADTRIG5L = 0x0;
}

void ADC1_Deinitialize (void)
{
    uint16_t dummy; //buffers has to be read before clearing interrupt flags
    ADCON1Lbits.ADON = 0;
    
    dummy = ADCBUF4;
    IFS5bits.ADCAN4IF = 0;
    IEC5bits.ADCAN4IE = 0;
    
    dummy = ADCBUF7;
    IFS6bits.ADCAN7IF = 0;
    IEC6bits.ADCAN7IE = 0;
    
    dummy = ADCBUF9;
    IFS6bits.ADCAN9IF = 0;
    IEC6bits.ADCAN9IE = 0;
    
    dummy = ADCBUF10;
    IFS6bits.ADCAN10IF = 0;
    IEC6bits.ADCAN10IE = 0;
    
    dummy = ADCBUF11;
    IFS6bits.ADCAN11IF = 0;
    IEC6bits.ADCAN11IE = 0;
    
    dummy = ADCBUF12;
    IFS6bits.ADCAN12IF = 0;
    IEC6bits.ADCAN12IE = 0;
    
    dummy = ADCBUF13;
    IFS6bits.ADCAN13IF = 0;
    IEC6bits.ADCAN13IE = 0;
    
    dummy = ADCBUF15;
    IFS6bits.ADCAN15IF = 0;
    IEC6bits.ADCAN15IE = 0;
    
    IFS5bits.ADCIF = 0;
    IEC5bits.ADCIE = 0;

    ADCON1L = 0x0;
    ADCON1H = 0x60;
    ADCON2L = 0x0;
    ADCON2H = 0x0;
    ADCON3L = 0x0;
    ADCON3H = 0x0;
    ADMOD0L = 0x0;
    ADMOD0H = 0x0;
    ADMOD1L = 0x0;
    ADIEL = 0x0;
    ADIEH = 0x0;
    ADSTATL = 0x0;
    ADSTATH = 0x0;
    ADCMP0ENL = 0x0;
    ADCMP1ENL = 0x0;
    ADCMP2ENL = 0x0;
    ADCMP3ENL = 0x0;
    ADCMP0ENH = 0x0;
    ADCMP1ENH = 0x0;
    ADCMP2ENH = 0x0;
    ADCMP3ENH = 0x0;
    ADCMP0LO = 0x0;
    ADCMP1LO = 0x0;
    ADCMP2LO = 0x0;
    ADCMP3LO = 0x0;
    ADCMP0HI = 0x0;
    ADCMP1HI = 0x0;
    ADCMP2HI = 0x0;
    ADCMP3HI = 0x0;
    ADFL0DAT = 0x0;
    ADFL1DAT = 0x0;
    ADFL2DAT = 0x0;
    ADFL3DAT = 0x0;
    ADFL0CON = 0x0;
    ADFL1CON = 0x0;
    ADFL2CON = 0x0;
    ADFL3CON = 0x0;
    ADTRIG0L = 0x0;
    ADTRIG0H = 0x0;
    ADTRIG1L = 0x0;
    ADTRIG1H = 0x0;
    ADTRIG2L = 0x0;
    ADTRIG2H = 0x0;
    ADTRIG3L = 0x0;
    ADTRIG3H = 0x0;
    ADTRIG4L = 0x0;
    ADTRIG4H = 0x0;
    ADTRIG5L = 0x0;
    ADCMP0CON = 0x0;
    ADCMP1CON = 0x0;
    ADCMP2CON = 0x0;
    ADCMP3CON = 0x0;
    ADLVLTRGL = 0x0;
    ADLVLTRGH = 0x0;
    ADEIEL = 0x0;
    ADEIEH = 0x0;
    ADEISTATL = 0x0;
    ADEISTATH = 0x0;
    ADCON5L = 0x0;
    ADCON5H = 0x0;
    ADCBUF0 = 0x0;
    ADCBUF1 = 0x0;
    ADCBUF2 = 0x0;
    ADCBUF3 = 0x0;
    ADCBUF4 = 0x0;
    ADCBUF5 = 0x0;
    ADCBUF6 = 0x0;
    ADCBUF7 = 0x0;
    ADCBUF8 = 0x0;
    ADCBUF9 = 0x0;
    ADCBUF10 = 0x0;
    ADCBUF11 = 0x0;
    ADCBUF12 = 0x0;
    ADCBUF13 = 0x0;
    ADCBUF14 = 0x0;
    ADCBUF15 = 0x0;
    ADCBUF16 = 0x0;
    ADCBUF17 = 0x0;
    ADCBUF18 = 0x0;
    ADCBUF19 = 0x0;
    ADCBUF20 = 0x0;
}


void ADC1_SharedCorePowerEnable (void) 
{
    ADCON5Lbits.SHRPWR = 1;   
    while(ADCON5Lbits.SHRRDY == 0)
    {
    }
    ADCON3Hbits.SHREN = 1;   
}

static uint16_t ADC1_TriggerSourceValueGet(enum ADC_PWM_INSTANCE pwmInstance, enum ADC_PWM_TRIGGERS triggerNumber)
{
    uint16_t adcTriggerSourceValue = 0x0U;
    switch(pwmInstance)
    {
        case ADC_S1_PWM_GENERATOR_8:
                if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = S1_PWM8_TRIGGER2;
                }
                break;
        case ADC_S1_PWM_GENERATOR_5:
                if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = S1_PWM5_TRIGGER2;
                }
                break;
        case ADC_S1_PWM_GENERATOR_3:
                if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = S1_PWM3_TRIGGER2;
                }
                break;
        case ADC_S1_PWM_GENERATOR_1:
                if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = S1_PWM1_TRIGGER2;
                }
                break;
        case ADC_PWM_GENERATOR_4:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM4_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM4_TRIGGER2;
                }
                break;
        case ADC_PWM_GENERATOR_3:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM3_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM3_TRIGGER2;
                }
                break;
        case ADC_PWM_GENERATOR_2:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM2_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM2_TRIGGER2;
                }
                break;
        case ADC_PWM_GENERATOR_1:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM1_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM1_TRIGGER2;
                }
                break;
         default:
                break;
    }
    return adcTriggerSourceValue;
}

void ADC1_PWMTriggerSourceSet(enum ADC_CHANNEL channel, enum ADC_PWM_INSTANCE pwmInstance, enum ADC_PWM_TRIGGERS triggerNumber)
{
    uint16_t adcTriggerValue;
    adcTriggerValue= ADC1_TriggerSourceValueGet(pwmInstance, triggerNumber);
    switch(channel)
    {
        case AN4_IeCB100A:
                ADTRIG1Lbits.TRGSRC4 = adcTriggerValue;
                break;
        case AN7_I_PWR1:
                ADTRIG1Hbits.TRGSRC7 = adcTriggerValue;
                break;
        case AN9_V_GPU:
                ADTRIG2Lbits.TRGSRC9 = adcTriggerValue;
                break;
        case AN10_I_PWR2:
                ADTRIG2Hbits.TRGSRC10 = adcTriggerValue;
                break;
        case AN11_V_PWR2:
                ADTRIG2Hbits.TRGSRC11 = adcTriggerValue;
                break;
        case AN12_V_PWR1:
                ADTRIG3Lbits.TRGSRC12 = adcTriggerValue;
                break;
        case AN13_V_BATTERY:
                ADTRIG3Lbits.TRGSRC13 = adcTriggerValue;
                break;
        case AN15_T_LOGIC_BOARD:
                ADTRIG3Hbits.TRGSRC15 = adcTriggerValue;
                break;
        default:
                break;
    }
}

void ADC1_CommonCallbackRegister(void(*callback)(void))
{
    if(NULL != callback)
    {
        ADC1_CommonHandler = callback;
    }
}

void __attribute__ ((weak)) ADC1_CommonCallback (void)
{ 

} 


void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCInterrupt ( void )
{
    uint16_t adcVal;
    if(NULL != ADC1_CommonHandler)
    {
        (*ADC1_CommonHandler)();
    }
    
    if(IFS5bits.ADCAN4IF == 1)
    {
        //Read the ADC value from the ADCBUF before clearing interrupt
        adcVal = ADCBUF4;
        if(NULL != ADC1_ChannelHandler)
        {
            (*ADC1_ChannelHandler)(AN4_IeCB100A, adcVal);
        }
        IFS5bits.ADCAN4IF = 0;
    }
    if(IFS6bits.ADCAN7IF == 1)
    {
        //Read the ADC value from the ADCBUF before clearing interrupt
        adcVal = ADCBUF7;
        if(NULL != ADC1_ChannelHandler)
        {
            (*ADC1_ChannelHandler)(AN7_I_PWR1, adcVal);
        }
        IFS6bits.ADCAN7IF = 0;
    }
    if(IFS6bits.ADCAN9IF == 1)
    {
        //Read the ADC value from the ADCBUF before clearing interrupt
        adcVal = ADCBUF9;
        if(NULL != ADC1_ChannelHandler)
        {
            (*ADC1_ChannelHandler)(AN9_V_GPU, adcVal);
        }
        IFS6bits.ADCAN9IF = 0;
    }
    if(IFS6bits.ADCAN10IF == 1)
    {
        //Read the ADC value from the ADCBUF before clearing interrupt
        adcVal = ADCBUF10;
        if(NULL != ADC1_ChannelHandler)
        {
            (*ADC1_ChannelHandler)(AN10_I_PWR2, adcVal);
        }
        IFS6bits.ADCAN10IF = 0;
    }
    if(IFS6bits.ADCAN11IF == 1)
    {
        //Read the ADC value from the ADCBUF before clearing interrupt
        adcVal = ADCBUF11;
        if(NULL != ADC1_ChannelHandler)
        {
            (*ADC1_ChannelHandler)(AN11_V_PWR2, adcVal);
        }
        IFS6bits.ADCAN11IF = 0;
    }
    if(IFS6bits.ADCAN12IF == 1)
    {
        //Read the ADC value from the ADCBUF before clearing interrupt
        adcVal = ADCBUF12;
        if(NULL != ADC1_ChannelHandler)
        {
            (*ADC1_ChannelHandler)(AN12_V_PWR1, adcVal);
        }
        IFS6bits.ADCAN12IF = 0;
    }
    if(IFS6bits.ADCAN13IF == 1)
    {
        //Read the ADC value from the ADCBUF before clearing interrupt
        adcVal = ADCBUF13;
        if(NULL != ADC1_ChannelHandler)
        {
            (*ADC1_ChannelHandler)(AN13_V_BATTERY, adcVal);
        }
        IFS6bits.ADCAN13IF = 0;
    }
    if(IFS6bits.ADCAN15IF == 1)
    {
        //Read the ADC value from the ADCBUF before clearing interrupt
        adcVal = ADCBUF15;
        if(NULL != ADC1_ChannelHandler)
        {
            (*ADC1_ChannelHandler)(AN15_T_LOGIC_BOARD, adcVal);
        }
        IFS6bits.ADCAN15IF = 0;
    }
        
    // clear the ADC1 interrupt flag
    IFS5bits.ADCIF = 0;
}

void __attribute__ ((weak)) ADC1_Tasks ( void )
{
    if(IFS5bits.ADCIF == 1)
    {
        if(NULL != ADC1_CommonHandler)
        {
            (*ADC1_CommonHandler)();
        }

        // clear the ADC1 interrupt flag
        IFS5bits.ADCIF = 0;
    }
}

void ADC1_ChannelCallbackRegister(void(*callback)(enum ADC_CHANNEL channel, uint16_t adcVal))
{
    if(NULL != callback)
    {
        ADC1_ChannelHandler = callback;
    }
}

void __attribute__ ((weak)) ADC1_ChannelCallback (enum ADC_CHANNEL channel, uint16_t adcVal)
{ 
    (void)channel;
    (void)adcVal;
} 


void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN4Interrupt ( void )
{
    uint16_t valAN4_IeCB100A;
    //Read the ADC value from the ADCBUF
    valAN4_IeCB100A = ADCBUF4;

    if(NULL != ADC1_ChannelHandler)
    {
        (*ADC1_ChannelHandler)(AN4_IeCB100A, valAN4_IeCB100A);
    }

    //clear the AN4_IeCB100A interrupt flag
    IFS5bits.ADCAN4IF = 0;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN7Interrupt ( void )
{
    uint16_t valAN7_I_PWR1;
    //Read the ADC value from the ADCBUF
    valAN7_I_PWR1 = ADCBUF7;

    if(NULL != ADC1_ChannelHandler)
    {
        (*ADC1_ChannelHandler)(AN7_I_PWR1, valAN7_I_PWR1);
    }

    //clear the AN7_I_PWR1 interrupt flag
    IFS6bits.ADCAN7IF = 0;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN9Interrupt ( void )
{
    uint16_t valAN9_V_GPU;
    //Read the ADC value from the ADCBUF
    valAN9_V_GPU = ADCBUF9;

    if(NULL != ADC1_ChannelHandler)
    {
        (*ADC1_ChannelHandler)(AN9_V_GPU, valAN9_V_GPU);
    }

    //clear the AN9_V_GPU interrupt flag
    IFS6bits.ADCAN9IF = 0;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN10Interrupt ( void )
{
    uint16_t valAN10_I_PWR2;
    //Read the ADC value from the ADCBUF
    valAN10_I_PWR2 = ADCBUF10;

    if(NULL != ADC1_ChannelHandler)
    {
        (*ADC1_ChannelHandler)(AN10_I_PWR2, valAN10_I_PWR2);
    }

    //clear the AN10_I_PWR2 interrupt flag
    IFS6bits.ADCAN10IF = 0;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN11Interrupt ( void )
{
    uint16_t valAN11_V_PWR2;
    //Read the ADC value from the ADCBUF
    valAN11_V_PWR2 = ADCBUF11;

    if(NULL != ADC1_ChannelHandler)
    {
        (*ADC1_ChannelHandler)(AN11_V_PWR2, valAN11_V_PWR2);
    }

    //clear the AN11_V_PWR2 interrupt flag
    IFS6bits.ADCAN11IF = 0;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN12Interrupt ( void )
{
    uint16_t valAN12_V_PWR1;
    //Read the ADC value from the ADCBUF
    valAN12_V_PWR1 = ADCBUF12;

    if(NULL != ADC1_ChannelHandler)
    {
        (*ADC1_ChannelHandler)(AN12_V_PWR1, valAN12_V_PWR1);
    }

    //clear the AN12_V_PWR1 interrupt flag
    IFS6bits.ADCAN12IF = 0;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN13Interrupt ( void )
{
    uint16_t valAN13_V_BATTERY;
    //Read the ADC value from the ADCBUF
    valAN13_V_BATTERY = ADCBUF13;

    if(NULL != ADC1_ChannelHandler)
    {
        (*ADC1_ChannelHandler)(AN13_V_BATTERY, valAN13_V_BATTERY);
    }

    //clear the AN13_V_BATTERY interrupt flag
    IFS6bits.ADCAN13IF = 0;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN15Interrupt ( void )
{
    uint16_t valAN15_T_LOGIC_BOARD;
    //Read the ADC value from the ADCBUF
    valAN15_T_LOGIC_BOARD = ADCBUF15;

    if(NULL != ADC1_ChannelHandler)
    {
        (*ADC1_ChannelHandler)(AN15_T_LOGIC_BOARD, valAN15_T_LOGIC_BOARD);
    }

    //clear the AN15_T_LOGIC_BOARD interrupt flag
    IFS6bits.ADCAN15IF = 0;
}



void __attribute__ ((weak)) ADC1_ChannelTasks (enum ADC_CHANNEL channel)
{
    uint16_t adcVal;
    
    switch(channel)
    {   
        case AN4_IeCB100A:
            if((bool)ADSTATLbits.AN4RDY == 1)
            {
                //Read the ADC value from the ADCBUF
                adcVal = ADCBUF4;

                if(NULL != ADC1_ChannelHandler)
                {
                    (*ADC1_ChannelHandler)(channel, adcVal);
                }
            }
            break;
        case AN7_I_PWR1:
            if((bool)ADSTATLbits.AN7RDY == 1)
            {
                //Read the ADC value from the ADCBUF
                adcVal = ADCBUF7;

                if(NULL != ADC1_ChannelHandler)
                {
                    (*ADC1_ChannelHandler)(channel, adcVal);
                }
            }
            break;
        case AN9_V_GPU:
            if((bool)ADSTATLbits.AN9RDY == 1)
            {
                //Read the ADC value from the ADCBUF
                adcVal = ADCBUF9;

                if(NULL != ADC1_ChannelHandler)
                {
                    (*ADC1_ChannelHandler)(channel, adcVal);
                }
            }
            break;
        case AN10_I_PWR2:
            if((bool)ADSTATLbits.AN10RDY == 1)
            {
                //Read the ADC value from the ADCBUF
                adcVal = ADCBUF10;

                if(NULL != ADC1_ChannelHandler)
                {
                    (*ADC1_ChannelHandler)(channel, adcVal);
                }
            }
            break;
        case AN11_V_PWR2:
            if((bool)ADSTATLbits.AN11RDY == 1)
            {
                //Read the ADC value from the ADCBUF
                adcVal = ADCBUF11;

                if(NULL != ADC1_ChannelHandler)
                {
                    (*ADC1_ChannelHandler)(channel, adcVal);
                }
            }
            break;
        case AN12_V_PWR1:
            if((bool)ADSTATLbits.AN12RDY == 1)
            {
                //Read the ADC value from the ADCBUF
                adcVal = ADCBUF12;

                if(NULL != ADC1_ChannelHandler)
                {
                    (*ADC1_ChannelHandler)(channel, adcVal);
                }
            }
            break;
        case AN13_V_BATTERY:
            if((bool)ADSTATLbits.AN13RDY == 1)
            {
                //Read the ADC value from the ADCBUF
                adcVal = ADCBUF13;

                if(NULL != ADC1_ChannelHandler)
                {
                    (*ADC1_ChannelHandler)(channel, adcVal);
                }
            }
            break;
        case AN15_T_LOGIC_BOARD:
            if((bool)ADSTATLbits.AN15RDY == 1)
            {
                //Read the ADC value from the ADCBUF
                adcVal = ADCBUF15;

                if(NULL != ADC1_ChannelHandler)
                {
                    (*ADC1_ChannelHandler)(channel, adcVal);
                }
            }
            break;
        default:
            break;
    }            
}

void ADC1_ComparatorCallbackRegister(void(*callback)(enum ADC_CMP comparator))
{
    if(NULL != callback)
    {
        ADC1_ComparatorHandler = callback;
    }
}

void __attribute__ ((weak)) ADC1_ComparatorCallback (enum ADC_CMP comparator)
{ 
    (void)comparator;
} 



