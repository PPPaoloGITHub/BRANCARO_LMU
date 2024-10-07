/**
 *  @file		ADCManager_prm.h
 *  @brief      This module manages direct ADC acquisitions from dsPIC33 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __ADC_MANAGER_PRM_H__
#define __ADC_MANAGER_PRM_H__

#include "C_Extensions.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
/* ************** VOLTAGE DIVIDER CONVENTION **************
 *                                                        *
 * external signal ---- R1 ----------> to dsPIC33 ANx     *
 *                             |                          *
 *                            R2                          *
 *                             |                          *
 *                        GND ---                         *
 *                                                        *
 **********************************************************/
#define ADC_INFINITE_VALUE      0xFFFF
#define ADC_VOLTAGE             3.3F
#define ADC_STEPS               4096       // 12bit resolution ==> 4096 steps available

/*********************************************************/
/* ************ I_eCB100A (AN4) PARAMNETERS ************ */
/*********************************************************/
#define I_eCB100A_R1           47000.0F    // [Ohm]
#define I_eCB100A_R2           ADC_INFINITE_VALUE
#define I_eCB100A_DIVIDER      ((I_eCB100A_R1 + I_eCB100A_R2) / I_eCB100A_R2)          
#define I_eCB100A_R_SHUNT      0.0005F     // [Ohm] Shunt Resistor
#define I_eCB100A_GAIN         50          // Operational Amplifier Gain
#define I_eCB100A_LP_FT        0.2F        // Cut Frequency of Low Pass filter. Use 1.0F to not use Low Pass Filter


/*********************************************************/
/* ************* I_PWR1 (AN7) PARAMNETERS ************** */
/*********************************************************/
#define I_PWR1_R1              9400.0F     // [Ohm]
#define I_PWR1_R2              24900.0F    // [Ohm]
#define I_PWR1_DIVIDER        ((I_PWR1_R1 + I_PWR1_R2) / I_PWR1_R2) 
#define I_PWR1_SENSIVITY       0.02666F    // [V/A] Current sensor sensivity 
#define I_PWR1_LP_FT           0.2F        // Cut Frequency of Low Pass filter. Use 1.0F to not use Low Pass Filter


/*********************************************************/
/* *********** T_PWR_BOARD (AN8) PARAMNETERS *********** */
/*********************************************************/
#define T_PWR_BOARD_R1         4700.0F     // [Ohm]
#define T_PWR_BOARD_R2         ADC_INFINITE_VALUE
#define T_PWR_BOARD_DIVIDER    ((T_PWR_BOARD_R1 + T_PWR_BOARD_R2) / T_PWR_BOARD_R2) 
#define T_PWR_BOARD_VOFFS      0.5F        // [V] Offset voltage for TMP235-Q1 component
#define T_PWR_BOARD_TC         0.010F      // [V/°C] Temperature coefficient for TMP235-Q1 component
#define T_PWR_BOARD_LP_FT      0.05F       // Cut Frequency of Low Pass filter. Use 1.0F to not use Low Pass Filter


/*********************************************************/
/* ************** V_GPU (AN9) PARAMNETERS ************** */
/*********************************************************/
#define V_GPU_R1               11000.0F     // [Ohm]
#define V_GPU_R2               1000.0F      // [Ohm]
#define V_GPU_DIVIDER          ((V_GPU_R1 + V_GPU_R2) / V_GPU_R2)
#define V_GPU_LP_FT            0.2F         // Cut Frequency of Low Pass filter. Use 1.0F to not use Low Pass Filter


/*********************************************************/
/* ************* I_PWR2 (AN10) PARAMNETERS ************* */
/*********************************************************/
#define I_PWR2_R1              9400.0F     // [Ohm]
#define I_PWR2_R2              24900.0F    // [Ohm]
#define I_PWR2_DIVIDER         ((I_PWR2_R1 + I_PWR2_R2) / I_PWR2_R2)
#define I_PWR2_SENSIVITY       0.02666F    // [V/A] Current sensor sensivity 
#define I_PWR2_LP_FT           0.2F        // Cut Frequency of Low Pass filter. Use 1.0F to not use Low Pass Filter


/*********************************************************/
/* ************* V_PWR2 (AN11) PARAMNETERS ************* */
/*********************************************************/
#define V_PWR2_R1              11000.0F    // [Ohm]
#define V_PWR2_R2              1000.0F     // [Ohm]
#define V_PWR2_DIVIDER         ((V_PWR2_R1 + V_PWR2_R2) / V_PWR2_R2)
#define V_PWR2_LP_FT           0.2F        // Cut Frequency of Low Pass filter. Use 1.0F to not use Low Pass Filter


/*********************************************************/
/* ************ V_PWR1 (AN12) PARAMNETERS ************ */
/*********************************************************/
#define V_PWR1_R1              11000.0F    // [Ohm]
#define V_PWR1_R2              1000.0F     // [Ohm]
#define V_PWR1_DIVIDER         ((V_PWR1_R1 + V_PWR1_R2) / V_PWR1_R2)
#define V_PWR1_LP_FT           0.2F        // Cut Frequency of Low Pass filter. Use 1.0F to not use Low Pass Filter


/*********************************************************/
/* ************ V_BATTERY (AN13) PARAMNETERS *********** */
/*********************************************************/
#define V_BATTERY_R1           11000.0F    // [Ohm]
#define V_BATTERY_R2           1000.0F     // [Ohm]
#define V_BATTERY_DIVIDER      ((V_BATTERY_R1 + V_BATTERY_R2) / V_BATTERY_R2)
#define V_BATTERY_LP_FT        0.2F        // Cut Frequency of Low Pass filter. Use 1.0F to not use Low Pass Filter


/*********************************************************/
/* ********** T_LOGIC_BOARD (AN15) PARAMNETERS ********* */
/*********************************************************/
#define T_LOGIC_BOARD_R1       10000.0F    // [Ohm]
#define T_LOGIC_BOARD_R2       ADC_INFINITE_VALUE
#define T_LOGIC_BOARD_DIVIDER  ((T_LOGIC_BOARD_R1 + T_LOGIC_BOARD_R2) / T_LOGIC_BOARD_R2) 
#define T_LOGIC_BOARD_VOFFS    0.5F        // [V] Offset voltage for TMP235-Q1 component
#define T_LOGIC_BOARD_TC       0.010F      // [V/°C] Temperature coefficient for TMP235-Q1 component
#define T_LOGIC_BOARD_LP_FT    0.05F       // Cut Frequency of Low Pass filter. Use 1.0F to not use Low Pass Filter


#endif /* __ADC_MANAGER_PRM_H__ */
