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

typedef enum
{
    CAN_COMMAND = 0x08,
    CAN_REQUEST = 0x0A,
    CAN_ANSWER  = 0x0E,
    CAN_STATUS  = 0x0C,   
}CAN_BYTE0_LIST_TYPE;

typedef enum
{
    CAN_ON_CMD  = 0x88,
    CAN_PWM_CMD = 0x55,
    CAN_OFF_CMD = 0xAA,
}CAN_CMDs_LIST_TYPE;

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
    void (*Initialize)     (void);
    void (*Handler5ms)     (void);
    bool (*Receive)        (CAN_OBJ_TYPE *rxCanMsg);
    void (*Send)           (uint32 msgID, uint8 length, uint8 *data);
    void (*HeartBeat)      (void);
    void (*Parser)         (); 
    
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
