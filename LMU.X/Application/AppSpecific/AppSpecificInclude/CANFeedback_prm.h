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
#define CAN_FEEDBACK_PERIOD         100             // [ms] CAN Feedback transmit period time in ms


/*********************************************************/
/* ******** LMU Feedback can messages ID defines ******* */
/* * CAN Feedback Range IDs: [0x00001xxx ÷ 0x00001xxx] * */
/*********************************************************/

#define CANFBK_ID_LSI1              0x00001100      // CAN messages ID for LSI1 :







#endif /* __FEEDBACKCAN_PRM_H__ */

