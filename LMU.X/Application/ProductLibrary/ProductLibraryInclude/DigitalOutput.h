/**
 *  @file       DigitalOutput.h
 *  @brief      This file contains Digital Output interface
 *
 *  $Header: 	ver 1.0 - Oct 16, 2020 -  Paolo Parrino
 *
 *  @copyright  *****  Copyright 2020-2025.  Rhea Vendors.  All rights reserved - CONFIDENTIAL  *****
 *
 */

#ifndef __DIGITAL_OUTPUT_H__
#define __DIGITAL_OUTPUT_H__

#include "../ProductLibraryInclude/C_extensions.h"
#include "../../../mcc_generated_files/system/pins.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
//typedef enum
//{
//	SSR1 = 0,
//	SSR2,
//	SSR_MAX,
//} SOLID_STATE_RELAY_TYPE;
//
//typedef enum
//{
//	DEV_L99_1,
//	DEV_L99_2,
//	DEV_L99_3,
//	DEV_L99_4,
//	DEV_L99_5,
//	DEV_L99_6,
//	DEV_L99_MAX,
//} DEVICE_L99_TYPE;
//
//typedef struct
//{
//	void (*CANStandBy)				(ON_OFF_TYPE status);
//	void (*DeepTraySensorEnable)	(ON_OFF_TYPE status);
//	void (*CupSensorEnable)			(ON_OFF_TYPE status);
//	void (*PumpEnable)				(ON_OFF_TYPE status);
//	void (*H2OSensorEnable)			(ON_OFF_TYPE status);
//	void (*STM8Reset)				(ON_OFF_TYPE status);
//	void (*SSREnable)				(SOLID_STATE_RELAY_TYPE relay, ON_OFF_TYPE status);
//	void (*DrvL99Activation)		(ACTIVE_TYPE status);
//	void (*DrvL99CS)				(DEVICE_L99_TYPE drv, LOW_HIGH_TYPE status);
//	void (*DrvDataFlashCS)			(LOW_HIGH_TYPE status);
//} DO_INTERFACE_TYPE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

//DO_INTERFACE_TYPE DO__Interface(void);

#endif /* __DIGITAL_OUTPUT_H__ */
