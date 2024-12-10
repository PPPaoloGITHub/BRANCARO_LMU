/**
 *  @file		Version_prm.h
 *  @brief      LMU version parameter handler
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef VERSION_PRM_H_
#define VERSION_PRM_H_

#include "../../ProductLibrary/ProductLibraryInclude/C_extensions.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================

//=====================================================================================================================
/**
 *    @brief  - Defines compiler family/processor type
 *
 *    @note - valid values are:
 *
 *    #define COMPILER_TYPE   XC16_VER2_10
 *    #define COMPILER_TYPE   NO_SPECIFIC_COMPILER
 *
 */
//=====================================================================================================================
#define COMPILER_TYPE  XC16_VER2_10

//=====================================================================================================================
/**
 *    @brief   project name string length
 *
 *    @details  Enter PROJECT_NAME string length, in Bytes, plus 1
 *              e.g. PROJECT_NAME = "Project" -->  PROJECT_NAME_LENGTH = 8
 *
 */
//=====================================================================================================================
#define PROJECT_NAME_LENGTH  4

//=====================================================================================================================
/**
 *    @brief   software part number string length
 *
 *    @details  Enter SW_PART_NUMBER string length, in Bytes, plus 1
 *              e.g. SW_PART_NUMBER = "BR-9074-005-yx" -->  SW_PART_NUMBER_LENGTH = 15
 *              In the SW_PART_NUMBER the yx part is the y = SW_VERSION_MAJOR and x = SW_VERSION_MINOR written on 2 bytes
 */
//=====================================================================================================================
#define SW_PART_NUMBER_LENGTH  15

//=====================================================================================================================
/**
 *    @brief   hardware part number string length
 *
 *    @details  Enter HW_PART_NUMBER string length, in Bytes, plus 1
 *              e.g. HW_PART_NUMBER = "BR-9070-013" -->  HW_PART_NUMBER_LENGTH = 12
 *
 */
//=====================================================================================================================
#define HW_PART_NUMBER_LENGTH  12

//=====================================================================================================================
/**
 *    @brief   release date string length
 *
 *    @details  Enter RELEASE_DATE_LENGTH string length in accordance with YYYYMMDDHHMM
 *              date format, in Bytes, plus 1
 *              e.g. RELEASE_DATE_LENGTH = "202409121030" -->  RELEASE_DATE_LENGTH = 13
 *
 */
//=====================================================================================================================
#define RELEASE_DATE_LENGTH 13


//=====================================================================================================================
/**
 *    @brief   project name string
 *
 *    @details  Enter project name below. This provides the
 *              ability to determine the software version by
 *              searching the executable file for the project name
 *              and viewing the subsequent bytes.
 *              Length of this string is set in PROJECT_NAME_LENGTH
 *              define
 */
//=====================================================================================================================
#define PROJECT_NAME "LMU"

//=====================================================================================================================
/**
 *    @brief   software version string
 *
 *    @details  Increment SW_Version_Major when a new production intent
 *              software has been created and checkpoint the project. Reset
 *              SW_Version_Minor and SW_Version_Test to 0 when this is
 *              incremented.
 *
 *              Increment SW_Version_Minor when software has been distributed
 *              and checkpoint the project. Reset SW_Version_Test to 0 when
 *              this is incremented.
 *
 *              Increment SW_Version_Test when software is a special version
 *              of software that deliberately deviates from the specification
 *              for testing purposes. This software may or may not be
 *              checkpointed.
 *
 *              The valid range of these variables are from 0 to 99.
 *              Hexadecimal 0x00 stands for 0 and vice versa.
 */
//=====================================================================================================================
#define SW_VERSION_MAJOR  0
#define SW_VERSION_MINOR  2
#define SW_VERSION_TEST   0

//=====================================================================================================================
/**
 *    @brief   software part number string
 *
 *    @details  This constant will describe the software part number as
 *              listed on the drawings for the software.  It allows a unique
 *              identifier for the software. During development this can be
 *              used as required by the engineer.
 *              SW_PART_NUMBER = "BR-9074-005-yx"             
 *              In the SW_PART_NUMBER the yx part is the y = SW_VERSION_MAJOR and x = SW_VERSION_MINOR written on 2 bytes
 *              Length of this string is set in SW_PART_NUMBER_LENGTH define
 */
//=====================================================================================================================
#define SW_PART_NUMBER "BR-9074-005-02"

//=====================================================================================================================
/**
 *    @brief   hardware part number string
 *
 *    @details  This constant will describe the hardware part number as
 *              listed on the drawings for the hardware.  It allows a unique
 *              identifier for the hardware.  During development this can be
 *              used as required by the engineer.
 *              Length of this string is set in HW_PART_NUMBER_LENGTH define
 */
//=====================================================================================================================
#define HW_PART_NUMBER "BR-9070-013"

//=====================================================================================================================
/**
 *    @brief   release date string
 *
 *    @details This constant will describe the software release date in a
 *             YYYYMMDDHHMM format.
 *             Length of this string is set in RELEASE_DATE_LENGTH define
 */
//=====================================================================================================================
#define RELEASE_DATE "202412101520"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

#endif // VERSION_PRM_H_
