/**
 *  @file		CANRecvdMsgParser.h
 *  @brief      CAN Received Messages Parser module handles all CAN received messages
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __CAN_RECVD_MSG_PARSER_H__
#define __CAN_RECVD_MSG_PARSER_H__

#include "C_Extensions.h"
#include "../../../mcc_generated_files/can/can1.h"

#include "../ProductLibraryInclude/CANRecvdMsgParser_prm.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
#define CAN_DLC_DEFAULT     8
#define CAN_ERROR_ANSWER    0xFF
#define CAN_OPERATIONS_MASK  0xFFFFFF0F
#define CAN_PARAMETERS_MASK  0xFFFFFFF0

typedef enum
{
    CAN_CMD     = 0x8,
    CAN_RQST    = 0xA,
    CAN_ANSWER  = 0xC,
    CAN_STATUS  = 0xE,   
}CAN_OPERATIONS_TYPE;

typedef enum
{
    CAN_eCB_ON_CMD   = 0x3,
    CAN_eCB_OFF_CMD  = 0x4,
    CAN_eCB_PWM_CMD  = 0x5,
    CAN_eCB_RESET    = 0x6,
    CAN_eCB_SELFTEST = 0x7,
    CAN_eCB_REQUEST  = 0xA,
}CAN_eCB_PARAMETERS_TYPE;

typedef enum
{
    CAN_PGD_ON_CMD   = 0x3,
    CAN_PGD_OFF_CMD  = 0x4,
    CAN_PGD_PWM_CMD  = 0x5,
    CAN_PGD_RQST     = 0xA,
}CAN_PGD_PARAMETERS_TYPE;

typedef enum
{
    CAN_ASYNC_PUBLISH    = 0x0,
    CAN_PERIODIC_PUBLISH = 0x1,
}CAN_STATUS_PARAMETERS_TYPE;

typedef enum
{
    CAN_eCB_ALARM          = 0x0F,
    CAN_RESET_COMPLETED    = 0x60,
    CAN_SELFTEST_COMPLETED = 0x70,
}CAN_BYTE0_STATUS_TYPE;

typedef enum
{
    CAN_TEMP_RQST = 0xA,
}CAN_TEMPERATURE_PARAMETERS_TYPE;

typedef enum
{
    CAN_ORING_GPU_EN             = 0x1,
    CAN_ORING_BATT_EN            = 0x2,
    CAN_ORING_VOLTAGES_RQST      = 0x5,         
    CAN_ORING_BUS_CURRENT_RQST   = 0x6,
    CAN_ORING_ENABLE_STATUS_RQST = 0x7,
}CAN_ORING_PARAMETERS_TYPE;

typedef enum
{
    CAN_ORING_ON_CMD  = 0x03,
    CAN_ORING_OFF_CMD = 0x04,
}CAN_BYTE0_ORING_CMD_TYPE;

typedef enum
{
    CAN_SET_UNIT_NUMBER = 0x1,
    CAN_SET_CAN_BITRATE = 0x2,
}CAN_LMU_SETTINGS_PARAMETERS_TYPE;

typedef enum
{
    CAN_SET_125KBPS = 0x01,
    CAN_SET_250KBPS = 0x02,
    CAN_SET_500KBPS = 0x03,
    CAN_SET_1MBPS   = 0x04        
}CAN_BYTE0_CAN_BITRATE_TYPE;

typedef enum
{
    BYTE0   = 0,
    BYTE1,
    BYTE2,
    BYTE3,
    BYTE4,
    BYTE5,
    BYTE6,
    BYTE7,
    CAN_MAX_PAYLOAD = 8,
}CAN_BYTES_NAME_LIST_TYPE;


typedef struct CAN_MSG_OBJ CAN_OBJ_TYPE;    // Redefinition of 'struct CAN_MSG_OBJ' with 'CAN_OBJ_TYPE' 

typedef void (*MsgHandler_TYPE)(uint32 msgID, uint32 length, uint8 *payload);

typedef struct
{
	uint32 msgID;                /* can message ID  */
	MsgHandler_TYPE Handler;     /* handler routine */
} PARSER_TABLE_TYPE;

struct CAN_RMP_INTRFACE_STRUCT
{
    void  (*Initialize)     (void);
    void  (*Handler5ms)     (void);
    bool  (*Receive)        (CAN_OBJ_TYPE *rxCanMsg);
    void  (*Send)           (uint32 msgID, uint8 length, uint8 *data);
    void  (*HeartBeat)      (void);
    uint8 (*GetLMUun)       (void);
    
#ifdef CAN_TEST_EXECUTION
    void (*TestTx)         (void);
    void (*TestRx)         (void);
#endif  /* CAN_TEST_EXECUTION */  
};


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct CAN_RMP_INTRFACE_STRUCT CAN_RMP_Interf;

void CAN_RMP__Initialize(void);
void CAN_RMP__Handler5ms(void);

#endif /* __CAN_RECVD_MSG_PARSER_H__ */
