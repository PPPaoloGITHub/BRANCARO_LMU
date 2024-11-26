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
#define CAN_MSG_ID_LMU_START_ADDR   0x00240000                      // CAN ID Structure: LMU_CAN_ID_BASE = 0x00240000
                                                                    //                   LMU_CAN_ID_UNIT = 0x0000uu00 --> uu = LMU UNIT NUMBER [0x00 - 0xFF]
                                                                    //                   LMU_CAN_ID_MSGs = 0x000000nn --> nn = LMU messages ID [0x00 - 0xFF]
#define CAN_MSG_ID_LMU_END_ADDR     0x0024FFFF                      // CAN messages ID LMU range: [0x00240000 ÷ 0x0024FFFF] => 255 different messages available for each LMU



#define CAN_MSG_ID_HEARTBEAT_FIRST  0x002400A0                      // First Heartbeat CAN message ID
#define CAN_MSG_ID_HEARTBEAT_SECOND 0x002400A1                      // Second Heartbeat CAN message ID
#define CAN_HEARTBEAT_PERIOD        1000                            // [ms] CAN HeartBeat transmit period time in ms

// #define CAN_TEST_EXECUTION                                          // if CAN_TEST_EXECUTION is defined then the CAN test functions will be executed. 

/*********************************************************/
/* ************ LMU can messages ID defines ************ */
/*********************************************************/
// can messages ID to Program internal LMU variables //

// can messages ID commands //

#define eCB_PP_OUT1_ID               0x00240001
#define eCB_PP_OUT2_ID               0x00240002
#define eCB_PP_OUT3_ID               0x00240003
#define eCB_PP_OUT4_ID               0x00240004
#define eCB_PP_OUT5_ID               0x00240005
#define eCB_PP_OUT6_ID               0x00240006
#define eCB_PP_OUT7_ID               0x00240007
#define eCB_PP_OUT8_ID               0x00240008
#define eCB_PP_OUT9_ID               0x00240009
#define eCB_PP_OUT10_ID              0x0024000A
#define eCB_PP_OUT11_ID              0x0024000B
#define eCB_PP_OUT12_ID              0x0024000C
#define eCB_PP_OUT13_ID              0x0024000D
#define eCB_PP_OUT14_ID              0x0024000E
#define eCB_PP_OUT15_ID              0x0024000F
#define eCB_PP_OUT16_ID              0x00240010
#define eCB_PP_OUT17_ID              0x00240011
#define eCB_PP_OUT18_ID              0x00240012
#define eCB_PP_OUT19_ID              0x00240013
#define eCB_PP_OUT20_ID              0x00240014
#define eCB_PP_OUT21_ID              0x00240015
#define eCB_PP_OUT22_ID              0x00240016
#define eCB_PP_OUT23_ID              0x00240017
#define eCB_PP_OUT24_ID              0x00240018
#define eCB_PP_OUT25_ID              0x00240019
#define eCB_PP_OUT26_ID              0x0024001A
#define eCB_PP_OUT27_ID              0x0024001B
#define eCB_PP_OUT28_ID              0x0024001C
#define eCB_PP_OUT29_ID              0x0024001D
#define eCB_PP_OUT30_ID              0x0024001E
#define eCB_PP_OUT31_ID              0x0024001F
#define eCB_PP_OUT32_ID              0x00240020
#define eCB_PP_OUT33_ID              0x00240021
#define eCB_PP_OUT34_ID              0x00240022
#define eCB_PP_OUT35_ID              0x00240023
#define eCB_PP_OUT36_ID              0x00240024

#define PGD_IN_ID                    0x00240065

#define PGD_OUT1_ID                  0x00240066
#define PGD_OUT2_ID                  0x00240067
#define PGD_OUT3_ID                  0x00240068
#define PGD_OUT4_ID                  0x00240069

#define TEMPERATURE_ID               0x00240070

#define RESET_CMD_ID                 0x00240080
#define SELF_TEST_CMD_ID             0x00240082

#define ORING_ID                     0x00240090

#define CHANGE_UNIT_NUMBER_CMD_ID    0x002400A5         

#endif /* __CAN_RECVD_MSG_PARSER_PRM_H__ */
