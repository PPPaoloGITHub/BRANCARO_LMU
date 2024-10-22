/**
 *  @file		HW_HearBeat.h
 *  @brief      Hardware HeartBeat driver
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __HW_HEARTBEAT_H__
#define __HW_HEARTBEAT_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/system/pins.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
typedef enum
{
    HW_HEARTBEAT_NORMAL_OPERATION,
    HW_HEARTBEAT_MAINTENANCE_OPERATION,
} HW_HEARTBEAT_STATUS_TYPE;


struct HW_HEARTBEAT_INTRFACE_STRUCT
{
    void                     (*Initialize)  (void);
    void                     (*Handler25ms) (void);
    HW_HEARTBEAT_STATUS_TYPE (*GetStatus)   (void);
};


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct HW_HEARTBEAT_INTRFACE_STRUCT HW_HEARTBEAT_Interf;

void HW_HEARTBEAT__Initialize(void);
void HW_HEARTBEAT__Handler25ms(void);

#endif /* __HW_HEARTBEAT_H__ */
