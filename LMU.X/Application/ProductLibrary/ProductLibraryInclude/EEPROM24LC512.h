/**
 *  @file		EEPROM24LC512.h
 *  @brief      Driver for 24LC512 EEPROM with I2C Serial Interface 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __EEPROM24LC512_H__
#define __EEPROM24LC512_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/i2c_host/i2c1.h"

#include "EEPROM24LC512_prm.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
struct EEPROM24LC512_INTRFACE_STRUCT
{
    void (*Initialize) (void);
    void (*Handler5ms) (void);
    bool (*WriteByte)  (uint16 memoryAddr, uint8 data);
    bool (*WritePage)  (uint16 memoryAddr, uint8 *data, uint16 length);
    bool (*ReadByte)   (uint16 memoryAddr, uint8 *data);
    bool (*ReadBytes)  (uint16 memoryAddr, uint8 *buffer, uint16 length) ;
    bool (*IsI2CBusy)  (void);
};

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct EEPROM24LC512_INTRFACE_STRUCT EEPROM24LC512_Interf;

void EEPROM24LC512__Initialize(void);
void EEPROM24LC512__Handler25ms(void);

#endif /* __EEPROM24LC512_H__ */
