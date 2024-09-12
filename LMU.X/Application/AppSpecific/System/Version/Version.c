/**
 *  @file		Version.c
 *  @brief      LMU version module handler
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "../../AppSpecificInclude/Version.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
const VERSION_INFO_STRUCT_TYPE VersionData =
{
     {SW_VERSION_MAJOR, SW_VERSION_MINOR, SW_VERSION_TEST},

     PROJECT_NAME,
     SW_PART_NUMBER,
     HW_PART_NUMBER,
     RELEASE_DATE
};

const struct VERSION_INTERFACE_STRUCT *VERSION_Interface = &VERSION_Interf;

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------

static uint8 VERSION__SwVersionGet (SW_VERSION_REQ_TYPE type);
static void  VERSION__ProjectName  (char *str);
static void  VERSION__SwPartNumber (char *str);
static void  VERSION__HwPartNumber (char *str);
static void  VERSION__ReleaseDate  (char *str);


const struct VERSION_INTERFACE_STRUCT VERSION_Interf =
{
    .Initialize      = &VERSION__Initialize,
    .SwVersionGet    = &VERSION__SwVersionGet,
    .ProjectName     = &VERSION__ProjectName,
    .SwPartNumber    = &VERSION__SwPartNumber,
    .HwPartNumber    = &VERSION__HwPartNumber,
    .ReleaseDate     = &VERSION__ReleaseDate,   
};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

/**
 * @brief     Getter function for Software version.
 * @param     type = {SW_VERSION_MAJOR | SW_VERSION_MINOR | SW_VERSION_TEST }.
 *
 * @return    requested software version number.
 */
void VERSION__Initialize(void)
{
    #define  MAX_USED_STRINGS_VERSION_LENGHT     MAX(PROJECT_NAME_LENGTH,        \
                                                     MAX(SW_PART_NUMBER_LENGTH,  \
                                                         MAX(HW_PART_NUMBER_LENGTH, RELEASE_DATE_LENGTH)))
    
    char tempString[MAX_USED_STRINGS_VERSION_LENGHT];
    
    printf("\r\n*** VERSION module ***\r\n");
    
    printf("Sw Version Major = %d\r\n", VERSION_Interface->SwVersionGet(VERSION_MAJOR));
    printf("Sw Version Minor = %d\r\n", VERSION_Interface->SwVersionGet(VERSION_MINOR));
    printf("Sw Version Test  = %d\r\n", VERSION_Interface->SwVersionGet(VERSION_TEST));
 

    VERSION_Interface->ProjectName(tempString);         // write PROJECT_NAME string in tempString
    printf("Project Name     = %s\r\n", tempString);
    
    VERSION_Interface->SwPartNumber(tempString);        // write SW_PART_NUMBER string in tempString
    printf("Sw Part Number   = %s\r\n", tempString);
    
    VERSION_Interface->HwPartNumber(tempString);        // write HW_PART_NUMBER string in tempString
    printf("Hw Part Number   = %s\r\n", tempString);
    
    VERSION_Interface->ReleaseDate(tempString);         // write RELEASE_DATE string in tempString
    printf("Release Date     = %s\r\n", tempString);
 }

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================

/**
 * @brief     Getter function for Software version.
 * @param     type = {SW_VERSION_MAJOR | SW_VERSION_MINOR | SW_VERSION_TEST }.
 *
 * @return    requested software version number.
 */
static uint8 VERSION__SwVersionGet(SW_VERSION_REQ_TYPE type)
{
    return VersionData.swVersion[type];
}

/**
 * @brief     This function gives back, in the str pointer, the PROJECT_NAME string
 * @param     str: pointer to array that will contain the PROJECT_NAME string
 *
 * @return    None
 */
static void VERSION__ProjectName(char *str)
{
    strcpy(str, VersionData.projectName);
}

/**
 * @brief     This function gives back, in the str pointer, the SW_PART_NUMBER string
 * @param     str: pointer to array that will contain the SW_PART_NUMBER string
 *
 * @return    None
 */
static void  VERSION__SwPartNumber (char *str)
{
    strcpy(str, VersionData.swPartNumber);
}

/**
 * @brief     This function gives back, in the str pointer, the HW_PART_NUMBER string
 * @param     str: pointer to array that will contain the HW_PART_NUMBER string
 *
 * @return    None
 */
static void  VERSION__HwPartNumber (char *str)
{
    strcpy(str, VersionData.hwPartNumber);
}

/**
 * @brief     This function gives back, in the str pointer, the RELEASE_DATE string
 * @param     str: pointer to array that will contain the RELEASE_DATE string
 *
 * @return    None
 */
static void  VERSION__ReleaseDate  (char *str)
{
    strcpy(str, VersionData.releaseDate);
}