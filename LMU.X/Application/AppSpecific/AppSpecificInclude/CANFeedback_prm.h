/**
 *  @file       FeedbackCAN_prm.h
 *  @brief      This file manages feedback CAN
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries..  All rights reserved - CONFIDENTIAL  *****
 *
 */

#ifndef __FEEDBACKCAN_PRM_H__
#define __FEEDBACKCAN_PRM_H__

#include "../../ProductLibrary/ProductLibraryInclude/C_extensions.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
#define CAN_FEEDBACK_PERIOD     10   // [ms] CAN Feedback transmit period time in ms


/*********************************************************/
/* ******** LMU Feedback can messages ID defines ******* */
/* * CAN Feedback Range IDs: [0x00001xxx ÷ 0x00001xxx] * */
/*********************************************************/
typedef enum
{
    CANFBK_ID_LSI0 = 0x00001100,     // CAN messages ID for LSI0
    CANFBK_ID_LSI1 = 0x00001101,     // CAN messages ID for LSI1
    CANFBK_ID_LSI2 = 0x00001102,     // CAN messages ID for LSI2
    CANFBK_ID_LSI3 = 0x00001103,     // CAN messages ID for LSI3
    CANFBK_ID_LSI4 = 0x00001104,     // CAN messages ID for LSI4
    CANFBK_ID_LSI5 = 0x00001105,     // CAN messages ID for LSI5
    // If add other IDs, please update the GetIDEnumValue() function 
            
    CANFBK_MAX_LSI_IDs = 6
}CANFBK_IDs_LSI_TYPE;






#endif /* __FEEDBACKCAN_PRM_H__ */

