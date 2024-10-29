/**
 *  @file		EEPROM24LC512_prm.h
 *  @brief      Configuration file for Driver 24LC512 EEPROM with I2C Serial Interface 
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __EEPROM24LC512_PRM_H__
#define __EEPROM24LC512_PRM_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/i2c_host/i2c1.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
/* Base address of EEPROM 24LC512 (7 bits, shifted left by 1bit) */
#define EEPROM24LC512_I2C_ADDRESS           0x50

/* EEPROM 24LC512 has maximum 128 bytes per page */
#define EEPROM24LC512_MAX_BYTE_PER_PAGE     128         // [Bytes]

/* ***************** PORTABILITY MODULE: ***************** */
/* I2C function to import from microcontroller I2C module  */
#define EEPROM_I2CWrite(memoryAddress, pData, dataLength)   I2C1_Host.Write(memoryAddress, pData, dataLength)
#define EEPROM_I2CRead(memoryAddress, pData, dataLengtht)   I2C1_Host.Read(memoryAddress, pData, dataLengtht)
#define EEPROM_I2CIsBusy()                                  I2C1_Host.IsBusy()

#endif /* __EEPROM24LC512_PRM_H__ */
