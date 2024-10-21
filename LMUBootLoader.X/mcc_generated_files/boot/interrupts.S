/**
  @Generated 16-bit Bootloader Source File

  @Company:
    Microchip Technology Inc.

  @File Name: 
    interrupts.S

  @Summary:
    This is the interrupts.S file generated using 16-bit Bootloader

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  16-bit Bootloader - 1.25.0
        Device            :  dsPIC33CH512MP506
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36B
        MPLAB             :  MPLAB X v5.15
*/
/*
Copyright (c) [2012-2024] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/
/* This file lists all of the interrupts in the system and how they will be
 * handled.  This file is use by both the hardware interrupt table and the 
 * user remap table to make sure they both stay in sync.
 *
 * IMPORTANT NOTE: Once a boot loader is deployed using this file, this file 
 * can not be modified in the end application.  Take care when selecting how to 
 * handle each interrupt at the development of the boot loader.
 *
 * Options:
 *   remap_to_application - this forwards the interrupt directly to the
 *   user application.  Each interrupt forwarded will require 2 instructions
 *   for the GOTO in the user reamapping table thus taking up 6 bytes of program
 *   memory each.  This is the safest option for all interrupts implemented in 
 *   hardware.  
 *
 *   keep_in_bootloader - this option will keep the interrupt in the boot
 *   loader.  If the interrupt function is defined, it will just to that
 *   function.  If it is not defined, it will jump to the default interrupt 
 *   handler function.
 *
 *   remap_to_application_default - this forwards the interrupt directly to the
 *   user application's default interrupt handler rather than the specified 
 *   unique interrupt vector.  This option is useful for interrupts that the
 *   application does not expect to use.  Since each interrupt forwarded by the
 *   remap_to_application option takes 2 instruction words, can get quite costly
 *   to forward all possible interrupts.  Interrupts forwarded with this option
 *   do not take any additional code space to forward.  Since multiple
 *   interrupts will be forwarded to the same vector, the user code will have to
 *   check to see which interrupt triggered to process them accordingly.  
 */
    
#ifdef REMAP_TABLE    

REMAP_TO_APPLICATION   OscillatorFail       
REMAP_TO_APPLICATION   AddressError       
REMAP_TO_APPLICATION   HardTrapError       
REMAP_TO_APPLICATION   StackError       
REMAP_TO_APPLICATION   MathError       
REMAP_TO_APPLICATION_DEFAULT   ReservedTrap5       
REMAP_TO_APPLICATION   SoftTrapError       
REMAP_TO_APPLICATION_DEFAULT   ReservedTrap7       
REMAP_TO_APPLICATION   INT0Interrupt       
REMAP_TO_APPLICATION   T1Interrupt       
REMAP_TO_APPLICATION   CNAInterrupt       
REMAP_TO_APPLICATION   CNBInterrupt       
REMAP_TO_APPLICATION   DMA0Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt5       
REMAP_TO_APPLICATION   CCP1Interrupt       
REMAP_TO_APPLICATION   CCT1Interrupt       
REMAP_TO_APPLICATION   DMA1Interrupt       
REMAP_TO_APPLICATION   SPI1RXInterrupt       
REMAP_TO_APPLICATION   SPI1TXInterrupt       
REMAP_TO_APPLICATION   U1RXInterrupt       
REMAP_TO_APPLICATION   U1TXInterrupt       
REMAP_TO_APPLICATION   ECCSBEInterrupt       
REMAP_TO_APPLICATION   NVMInterrupt       
REMAP_TO_APPLICATION   INT1Interrupt       
REMAP_TO_APPLICATION   SI2C1Interrupt       
REMAP_TO_APPLICATION   MI2C1Interrupt       
REMAP_TO_APPLICATION   DMA2Interrupt       
REMAP_TO_APPLICATION   CNCInterrupt       
REMAP_TO_APPLICATION   INT2Interrupt       
REMAP_TO_APPLICATION   DMA3Interrupt       
REMAP_TO_APPLICATION   DMA4Interrupt       
REMAP_TO_APPLICATION   CCP2Interrupt       
REMAP_TO_APPLICATION   CCT2Interrupt       
REMAP_TO_APPLICATION   C1Interrupt       
REMAP_TO_APPLICATION   INT3Interrupt       
REMAP_TO_APPLICATION   U2RXInterrupt       
REMAP_TO_APPLICATION   U2TXInterrupt       
REMAP_TO_APPLICATION   SPI2RXInterrupt       
REMAP_TO_APPLICATION   SPI2TXInterrupt       
REMAP_TO_APPLICATION   C1RXInterrupt       
REMAP_TO_APPLICATION   C2RXInterrupt       
REMAP_TO_APPLICATION   C2Interrupt       
REMAP_TO_APPLICATION   DMA5Interrupt       
REMAP_TO_APPLICATION   CCP3Interrupt       
REMAP_TO_APPLICATION   CCT3Interrupt       
REMAP_TO_APPLICATION   SI2C2Interrupt       
REMAP_TO_APPLICATION   MI2C2Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt39       
REMAP_TO_APPLICATION   CCP4Interrupt       
REMAP_TO_APPLICATION   CCT4Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt42       
REMAP_TO_APPLICATION   CCP5Interrupt       
REMAP_TO_APPLICATION   CCT5Interrupt       
REMAP_TO_APPLICATION   DMTInterrupt       
REMAP_TO_APPLICATION   CCP6Interrupt       
REMAP_TO_APPLICATION   CCT6Interrupt       
REMAP_TO_APPLICATION   QEI1Interrupt       
REMAP_TO_APPLICATION   U1EInterrupt       
REMAP_TO_APPLICATION   U2EInterrupt       
REMAP_TO_APPLICATION   CRCInterrupt       
REMAP_TO_APPLICATION   C1TXInterrupt       
REMAP_TO_APPLICATION   C2TXInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt54       
REMAP_TO_APPLICATION_DEFAULT   Interrupt55       
REMAP_TO_APPLICATION_DEFAULT   Interrupt56       
REMAP_TO_APPLICATION_DEFAULT   Interrupt57       
REMAP_TO_APPLICATION_DEFAULT   Interrupt58       
REMAP_TO_APPLICATION_DEFAULT   Interrupt59       
REMAP_TO_APPLICATION_DEFAULT   Interrupt60       
REMAP_TO_APPLICATION   ICDInterrupt       
REMAP_TO_APPLICATION   JTAGInterrupt       
REMAP_TO_APPLICATION   PTGSTEPInterrupt       
REMAP_TO_APPLICATION   I2C1BCInterrupt       
REMAP_TO_APPLICATION   I2C2BCInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt66       
REMAP_TO_APPLICATION   PWM1Interrupt       
REMAP_TO_APPLICATION   PWM2Interrupt       
REMAP_TO_APPLICATION   PWM3Interrupt       
REMAP_TO_APPLICATION   PWM4Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt71       
REMAP_TO_APPLICATION_DEFAULT   Interrupt72       
REMAP_TO_APPLICATION_DEFAULT   Interrupt73       
REMAP_TO_APPLICATION_DEFAULT   Interrupt74       
REMAP_TO_APPLICATION   CNDInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt76       
REMAP_TO_APPLICATION   CMP1Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt78       
REMAP_TO_APPLICATION_DEFAULT   Interrupt79       
REMAP_TO_APPLICATION_DEFAULT   Interrupt80       
REMAP_TO_APPLICATION   PTGWDTInterrupt       
REMAP_TO_APPLICATION   PTG0Interrupt       
REMAP_TO_APPLICATION   PTG1Interrupt       
REMAP_TO_APPLICATION   PTG2Interrupt       
REMAP_TO_APPLICATION   PTG3Interrupt       
REMAP_TO_APPLICATION   SENT1Interrupt       
REMAP_TO_APPLICATION   SENT1EInterrupt       
REMAP_TO_APPLICATION   SENT2Interrupt       
REMAP_TO_APPLICATION   SENT2EInterrupt       
REMAP_TO_APPLICATION   ADCInterrupt       
REMAP_TO_APPLICATION   ADCAN0Interrupt       
REMAP_TO_APPLICATION   ADCAN1Interrupt       
REMAP_TO_APPLICATION   ADCAN2Interrupt       
REMAP_TO_APPLICATION   ADCAN3Interrupt       
REMAP_TO_APPLICATION   ADCAN4Interrupt       
REMAP_TO_APPLICATION   ADCAN5Interrupt       
REMAP_TO_APPLICATION   ADCAN6Interrupt       
REMAP_TO_APPLICATION   ADCAN7Interrupt       
REMAP_TO_APPLICATION   ADCAN8Interrupt       
REMAP_TO_APPLICATION   ADCAN9Interrupt       
REMAP_TO_APPLICATION   ADCAN10Interrupt       
REMAP_TO_APPLICATION   ADCAN11Interrupt       
REMAP_TO_APPLICATION   ADCAN12Interrupt       
REMAP_TO_APPLICATION   ADCAN13Interrupt       
REMAP_TO_APPLICATION   ADCAN14Interrupt       
REMAP_TO_APPLICATION   ADCAN15Interrupt       
REMAP_TO_APPLICATION   ADCAN16Interrupt       
REMAP_TO_APPLICATION   ADCAN17Interrupt       
REMAP_TO_APPLICATION   ADCAN18Interrupt       
REMAP_TO_APPLICATION   ADCAN19Interrupt       
REMAP_TO_APPLICATION   ADCAN20Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt112       
REMAP_TO_APPLICATION_DEFAULT   Interrupt113       
REMAP_TO_APPLICATION_DEFAULT   Interrupt114       
REMAP_TO_APPLICATION   ADCFLTInterrupt       
REMAP_TO_APPLICATION   ADCMP0Interrupt       
REMAP_TO_APPLICATION   ADCMP1Interrupt       
REMAP_TO_APPLICATION   ADCMP2Interrupt       
REMAP_TO_APPLICATION   ADCMP3Interrupt       
REMAP_TO_APPLICATION   ADFLTR0Interrupt       
REMAP_TO_APPLICATION   ADFLTR1Interrupt       
REMAP_TO_APPLICATION   ADFLTR2Interrupt       
REMAP_TO_APPLICATION   ADFLTR3Interrupt       
REMAP_TO_APPLICATION   CLC1PInterrupt       
REMAP_TO_APPLICATION   CLC2PInterrupt       
REMAP_TO_APPLICATION   SPI1Interrupt       
REMAP_TO_APPLICATION   SPI2Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt128       
REMAP_TO_APPLICATION   MSIS1Interrupt       
REMAP_TO_APPLICATION   MSIAInterrupt       
REMAP_TO_APPLICATION   MSIBInterrupt       
REMAP_TO_APPLICATION   MSICInterrupt       
REMAP_TO_APPLICATION   MSIDInterrupt       
REMAP_TO_APPLICATION   MSIEInterrupt       
REMAP_TO_APPLICATION   MSIFInterrupt       
REMAP_TO_APPLICATION   MSIGInterrupt       
REMAP_TO_APPLICATION   MSIHInterrupt       
REMAP_TO_APPLICATION   MSIDTInterrupt       
REMAP_TO_APPLICATION   MSIWFEInterrupt       
REMAP_TO_APPLICATION   MSIFLTInterrupt       
REMAP_TO_APPLICATION   S1RSTInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt142       
REMAP_TO_APPLICATION_DEFAULT   Interrupt143       
REMAP_TO_APPLICATION_DEFAULT   Interrupt144       
REMAP_TO_APPLICATION_DEFAULT   Interrupt145       
REMAP_TO_APPLICATION   S1BRKInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt147       
REMAP_TO_APPLICATION_DEFAULT   Interrupt148       
REMAP_TO_APPLICATION   CCP7Interrupt       
REMAP_TO_APPLICATION   CCT7Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt151       
REMAP_TO_APPLICATION   CCP8Interrupt       
REMAP_TO_APPLICATION   CCT8Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt154       
REMAP_TO_APPLICATION_DEFAULT   Interrupt155       
REMAP_TO_APPLICATION_DEFAULT   Interrupt156       
REMAP_TO_APPLICATION   S1CLKFInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt158       
REMAP_TO_APPLICATION_DEFAULT   Interrupt159       
REMAP_TO_APPLICATION_DEFAULT   Interrupt160       
REMAP_TO_APPLICATION_DEFAULT   Interrupt161       
REMAP_TO_APPLICATION_DEFAULT   Interrupt162       
REMAP_TO_APPLICATION_DEFAULT   Interrupt163       
REMAP_TO_APPLICATION_DEFAULT   Interrupt164       
REMAP_TO_APPLICATION_DEFAULT   Interrupt165       
REMAP_TO_APPLICATION_DEFAULT   Interrupt166       
REMAP_TO_APPLICATION_DEFAULT   Interrupt167       
REMAP_TO_APPLICATION   ADFIFOInterrupt       
REMAP_TO_APPLICATION   PEVTAInterrupt       
REMAP_TO_APPLICATION   PEVTBInterrupt       
REMAP_TO_APPLICATION   PEVTCInterrupt       
REMAP_TO_APPLICATION   PEVTDInterrupt       
REMAP_TO_APPLICATION   PEVTEInterrupt       
REMAP_TO_APPLICATION   PEVTFInterrupt       
REMAP_TO_APPLICATION   CLC3PInterrupt       
REMAP_TO_APPLICATION   CLC4PInterrupt       
REMAP_TO_APPLICATION   CLC1NInterrupt       
REMAP_TO_APPLICATION   CLC2NInterrupt       
REMAP_TO_APPLICATION   CLC3NInterrupt       
REMAP_TO_APPLICATION   CLC4NInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt181       
REMAP_TO_APPLICATION_DEFAULT   Interrupt182       
REMAP_TO_APPLICATION_DEFAULT   Interrupt183       
REMAP_TO_APPLICATION_DEFAULT   Interrupt184       
REMAP_TO_APPLICATION_DEFAULT   Interrupt185       
REMAP_TO_APPLICATION_DEFAULT   Interrupt186       
REMAP_TO_APPLICATION_DEFAULT   Interrupt187       
REMAP_TO_APPLICATION_DEFAULT   Interrupt188       
REMAP_TO_APPLICATION   U1EVTInterrupt       
REMAP_TO_APPLICATION   U2EVTInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt191       
REMAP_TO_APPLICATION_DEFAULT   Interrupt192       
REMAP_TO_APPLICATION_DEFAULT   Interrupt193       
REMAP_TO_APPLICATION_DEFAULT   Interrupt194       
REMAP_TO_APPLICATION_DEFAULT   Interrupt195       
REMAP_TO_APPLICATION_DEFAULT   Interrupt196       
REMAP_TO_APPLICATION_DEFAULT   Interrupt197       
REMAP_TO_APPLICATION_DEFAULT   Interrupt198       
REMAP_TO_APPLICATION_DEFAULT   Interrupt199       
REMAP_TO_APPLICATION_DEFAULT   Interrupt200       
REMAP_TO_APPLICATION_DEFAULT   Interrupt201       
REMAP_TO_APPLICATION_DEFAULT   Interrupt202       
REMAP_TO_APPLICATION_DEFAULT   Interrupt203       
REMAP_TO_APPLICATION_DEFAULT   Interrupt204       
REMAP_TO_APPLICATION_DEFAULT   Interrupt205       
REMAP_TO_APPLICATION_DEFAULT   Interrupt206       
REMAP_TO_APPLICATION_DEFAULT   Interrupt207       
REMAP_TO_APPLICATION_DEFAULT   Interrupt208       
REMAP_TO_APPLICATION_DEFAULT   Interrupt209       
REMAP_TO_APPLICATION_DEFAULT   Interrupt210       
REMAP_TO_APPLICATION_DEFAULT   Interrupt211       
REMAP_TO_APPLICATION_DEFAULT   Interrupt212       
REMAP_TO_APPLICATION_DEFAULT   Interrupt213       
REMAP_TO_APPLICATION_DEFAULT   Interrupt214       
REMAP_TO_APPLICATION_DEFAULT   Interrupt215       
REMAP_TO_APPLICATION_DEFAULT   Interrupt216       
REMAP_TO_APPLICATION_DEFAULT   Interrupt217       
REMAP_TO_APPLICATION_DEFAULT   Interrupt218       
REMAP_TO_APPLICATION_DEFAULT   Interrupt219       
REMAP_TO_APPLICATION_DEFAULT   Interrupt220       
REMAP_TO_APPLICATION_DEFAULT   Interrupt221       
REMAP_TO_APPLICATION_DEFAULT   Interrupt222       
REMAP_TO_APPLICATION_DEFAULT   Interrupt223       
REMAP_TO_APPLICATION_DEFAULT   Interrupt224       
REMAP_TO_APPLICATION_DEFAULT   Interrupt225       
REMAP_TO_APPLICATION_DEFAULT   Interrupt226       
REMAP_TO_APPLICATION_DEFAULT   Interrupt227       
REMAP_TO_APPLICATION_DEFAULT   Interrupt228       
REMAP_TO_APPLICATION_DEFAULT   Interrupt229       
REMAP_TO_APPLICATION_DEFAULT   Interrupt230       
REMAP_TO_APPLICATION_DEFAULT   Interrupt231       
REMAP_TO_APPLICATION_DEFAULT   Interrupt232       
REMAP_TO_APPLICATION_DEFAULT   Interrupt233       
REMAP_TO_APPLICATION_DEFAULT   Interrupt234       
REMAP_TO_APPLICATION_DEFAULT   Interrupt235       
REMAP_TO_APPLICATION_DEFAULT   Interrupt236       
REMAP_TO_APPLICATION_DEFAULT   Interrupt237       
REMAP_TO_APPLICATION_DEFAULT   Interrupt238       
REMAP_TO_APPLICATION_DEFAULT   Interrupt239       
REMAP_TO_APPLICATION_DEFAULT   Interrupt240       
REMAP_TO_APPLICATION_DEFAULT   Interrupt241       
REMAP_TO_APPLICATION_DEFAULT   Interrupt242       
REMAP_TO_APPLICATION_DEFAULT   Interrupt243       
REMAP_TO_APPLICATION_DEFAULT   Interrupt244       
REMAP_TO_APPLICATION_DEFAULT   Interrupt245       

#endif
