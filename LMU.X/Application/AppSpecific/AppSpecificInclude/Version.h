/**
 *  @file		Version.h
 *  @brief      LMU version module header
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */

#ifndef VERSION_H_
#define VERSION_H_

#include "../../ProductLibrary/ProductLibraryInclude/C_extensions.h"
#include "Version_prm.h"
//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================
typedef enum
{
    VERSION_MAJOR = 0,
    VERSION_MINOR = 1,
    VERSION_TEST = 2,
    NUM_OF_SW_VERSION_REQ_ELEMENTS = 3
}SW_VERSION_REQ_TYPE;

typedef struct
{
    uint8 swVersion   [NUM_OF_SW_VERSION_REQ_ELEMENTS];
    
    char projectName  [PROJECT_NAME_LENGTH];
    char swPartNumber [SW_PART_NUMBER_LENGTH];
    char hwPartNumber [HW_PART_NUMBER_LENGTH];
    char releaseDate  [RELEASE_DATE_LENGTH];
}VERSION_INFO_STRUCT_TYPE;

struct VERSION_INTERFACE_STRUCT
{
    void  (*Initialize)   (void);
    uint8 (*SwVersionGet) (SW_VERSION_REQ_TYPE type);
    void  (*ProjectName)  (char* string);
    void  (*SwPartNumber) (char* string);
    void  (*HwPartNumber) (char* string);
    void  (*ReleaseDate)  (char* string); 
};

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct VERSION_INTERFACE_STRUCT VERSION_Interf;

void VERSION__Initialize(void);

#endif // VERSION_H_

