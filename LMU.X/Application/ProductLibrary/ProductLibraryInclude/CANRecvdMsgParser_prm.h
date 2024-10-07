/**
 *  @file		CANRecvdMsgParser_prm.h
 *  @brief      CAN Received Messages Parser module handles all CAN received messages
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __CAN_RECVD_MSG_PARSER_PRM_H__
#define __CAN_RECVD_MSG_PARSER_PRM_H__

#include "C_Extensions.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
#define CAN_MSG_ID_LMU_START_ADDR   0x00002000                      // CAN messages ID LMU range:
#define CAN_MSG_ID_LMU_END_ADDR     0x00002200                      // [0x00002000 ÷ 0x00002200] => 512 different messages available

#define CAN_MSG_ID_HEARTBEAT_FIRST  CAN_MSG_ID_LMU_START_ADDR       // First Heartbeat CAN message ID
#define CAN_MSG_ID_HEARTBEAT_SECOND (CAN_MSG_ID_LMU_START_ADDR + 1) // Second Heartbeat CAN message ID
#define CAN_HEARTBEAT_PERIOD        1000                            // [ms] CAN HeartBeat transmit period time in ms

// #define CAN_TEST_EXECUTION                                          // if CAN_TEST_EXECUTION is defined then the CAN test functions will be executed. 

/*********************************************************/
/* ************ LMU can messages ID defines ************ */
/*********************************************************/
// can messages ID to Program internal LMU variables //

// can messages ID commands //
#define NAME_CMD1                   0x00002005
#define NAME_CMD2                   0x00002006


#endif /* __CAN_RECVD_MSG_PARSER_PRM_H__ */
