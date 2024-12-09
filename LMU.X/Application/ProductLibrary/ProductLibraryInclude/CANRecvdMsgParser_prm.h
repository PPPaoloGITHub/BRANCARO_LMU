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
#define CAN_MSG_ID_LMU_START_ADDR   0x02400000                      // CAN ID Structure: LMU_CAN_ID_BASE       = 0x02400000
                                                                    //                   LMU_CAN_ID_UNIT       = 0x000u0000 --> u  = LMU UNIT NUMBER [0x0 - 0xF]
                                                                    //                   LMU_CAN_ID_OBJECTSs   = 0x0000nn00 --> nn = LMU Objects ID  [0x00 - 0xFF]
                                                                    //                   LMU_CAN_ID_OPERATION  = 0x000000o0 --> o  = LMU OPERATION   [0x0 - 0xF]
                                                                    //                   LMU_CAN_ID_PARAMETERS = 0x0000000p --> p  = LMU PARAMETERS  [0x0 - 0xF]
#define CAN_MSG_ID_LMU_END_ADDR     0x024FFFFF                      // CAN messages ID LMU range: [0x02400000 ÷ 0x024FFFFF]

#define CAN_HEARTBEAT_PERIOD        1000                            // [ms] CAN HeartBeat transmit period time in ms

/* Gains for different eCB sizes for the calculation of currents */
#define CAN_ADC_EXP_VREF            5.0F                            // ADS7128 Reference Voltage
#define CAN_ADC_RESOLUTION          4096.0F                         // ADS7128 ADC 12 bit resolution
#define CAN_eCB_1A_GAIN             0.4293688278F                   // Gain = 2.329   -> 1/G = 0.4293688278
#define CAN_eCB_1A5_GAIN            0.6600660066F                   // Gain = 1.515   -> 1/G = 0.6600660066
#define CAN_eCB_2A_GAIN             0.8888888888F                   // Gain = 1.125   -> 1/G = 0.8888888888
#define CAN_eCB_2A5_GAIN            1.0619544209F                   // Gain = 0.94166 -> 1/G = 1.0619544209
#define CAN_eCB_3A_GAIN             1.3333333333F                   // Gain = 2.329   -> 1/G = 1.3333333333
#define CAN_eCB_5A_GAIN             2.2222222222F                   // Gain = 2.329   -> 1/G = 2.2222222222

// #define CAN_TEST_EXECUTION                                       // if CAN_TEST_EXECUTION is defined then the CAN test functions will be executed. 

/*********************************************************/
/* ************ LMU can messages ID defines ************ */
/*********************************************************/
// can messages ID to Program internal LMU variables //

// can messages ID commands //

#define eCB_PP_OUT1_ID               0x02400100
#define eCB_PP_OUT2_ID               0x02400200
#define eCB_PP_OUT3_ID               0x02400300
#define eCB_PP_OUT4_ID               0x02400400
#define eCB_PP_OUT5_ID               0x02400500
#define eCB_PP_OUT6_ID               0x02400600
#define eCB_PP_OUT7_ID               0x02400700
#define eCB_PP_OUT8_ID               0x02400800
#define eCB_PP_OUT9_ID               0x02400900
#define eCB_PP_OUT10_ID              0x02400A00
#define eCB_PP_OUT11_ID              0x02400B00
#define eCB_PP_OUT12_ID              0x02400C00
#define eCB_PP_OUT13_ID              0x02400D00
#define eCB_PP_OUT14_ID              0x02400E00
#define eCB_PP_OUT15_ID              0x02400F00
#define eCB_PP_OUT16_ID              0x02401000
#define eCB_PP_OUT17_ID              0x02401100
#define eCB_PP_OUT18_ID              0x02401200
#define eCB_PP_OUT19_ID              0x02401300
#define eCB_PP_OUT20_ID              0x02401400
#define eCB_PP_OUT21_ID              0x02401500
#define eCB_PP_OUT22_ID              0x02401600
#define eCB_PP_OUT23_ID              0x02401700
#define eCB_PP_OUT24_ID              0x02401800
#define eCB_PP_OUT25_ID              0x02401900
#define eCB_PP_OUT26_ID              0x02401A00
#define eCB_PP_OUT27_ID              0x02401B00
#define eCB_PP_OUT28_ID              0x02401C00
#define eCB_PP_OUT29_ID              0x02401D00
#define eCB_PP_OUT30_ID              0x02401E00
#define eCB_PP_OUT31_ID              0x02401F00
#define eCB_PP_OUT32_ID              0x02402000
#define eCB_PP_OUT33_ID              0x02402100
#define eCB_PP_OUT34_ID              0x02402200
#define eCB_PP_OUT35_ID              0x02402300
#define eCB_PP_OUT36_ID              0x02402400

#define RESET_CMD_ID                 0x02405000
#define SELF_TEST_CMD_ID             0x02405000

#define PGD_IN_ID                    0x024060AA

#define PGD_OUT1_ID                  0x02406100
#define PGD_OUT2_ID                  0x02406200
#define PGD_OUT3_ID                  0x02406300
#define PGD_OUT4_ID                  0x02406400

#define TEMPERATURE_ID               0x02407000

#define ORING_ID                     0x02408000

#define CAN_MSG_ID_HEARTBEAT_FIRST   0x0240A000                      // First Heartbeat CAN message ID
#define CAN_MSG_ID_HEARTBEAT_SECOND  0x0240A100                      // Second Heartbeat CAN message ID

#define LMU_SETTINGS_CMD_ID          0x0240A500         

#endif /* __CAN_RECVD_MSG_PARSER_PRM_H__ */
