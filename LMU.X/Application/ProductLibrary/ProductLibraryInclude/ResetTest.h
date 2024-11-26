/**
 *  @file		ResetTest.h
 *  @brief      Reset and Test functionality 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __RESET_TEST_H__
#define __RESET_TEST_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/system/pins.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
#define RESET_CMD_TIME_1s          1000        // [ms] Duration time for Reset impulse
#define TEST_CMD_TIME_2s           2000        // [ms] Duration time for Test impulse


struct RESET_TEST_INTRFACE_STRUCT
{
    void (*Initialize)  (void);
    void (*Handler25ms) (void);
    void (*ResetCmd)    (void);
    void (*SelfTestCmd) (void);
};


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct RESET_TEST_INTRFACE_STRUCT RESET_TEST_Interf;

void RESET_TEST__Initialize(void);
void RESET_TEST__Handler25ms(void);

#endif /* __RESET_TEST_H__ */
