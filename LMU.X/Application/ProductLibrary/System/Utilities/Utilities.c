/**
 *  @file       Utilities.c
 *  @brief      Commonly used utility functions
 *
 *  @details    ---

 *  $Header: ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright 2020-2025.  Rhea Vendors.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "C_Extensions.h"
#include "Utilities.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

const unsigned short BYTE_SET_MASK[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
const unsigned short BYTE_CLR_MASK[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

/**
 *
 * @param array
 * @return
 */
unsigned long int Utilities__ConvertArrayTo32bits(unsigned char * array)
{
    unsigned long int retval;
    retval = ((unsigned long int)array[0]) << 24;
    retval += ((unsigned long int)array[1]) << 16;
    retval += ((unsigned long int)array[2]) << 8;
    retval += ((unsigned long int)array[3]);
    return (retval);
}

/**
 *
 * @param array
 * @return
 */
unsigned long int Utilities__ConvertArrayTo24bits(unsigned char * array)
{
    unsigned long int retval;
    retval = ((unsigned long int)array[0]) << 16;
    retval += ((unsigned long int)array[1]) << 8;
    retval += ((unsigned long int)array[2]);
    return (retval);
}



/**
 *
 * @param array
 * @return
 */
unsigned short int Utilities__Merg2BytesTo16bits(unsigned char msb, unsigned char lsb)
{
    unsigned short int retval;
    retval = ((unsigned short int)msb) << 8;
    retval += ((unsigned short int)lsb);
    return (retval);
}

/**
 *
 * @param array
 * @return
 */
unsigned short int Utilities__ConvertArrayTo16bits(unsigned char * array)
{
    return (Utilities__Merg2BytesTo16bits(array[0],array[1]));
}

/**
 *
 * @param array
 * @param bit
 * @param value
 */
void Utilities__SetBitInArray(unsigned char * array, unsigned char bit, unsigned char value)
{
    unsigned char s_byte;
    unsigned char s_bit;
    s_byte = bit / 8;
    s_bit = bit % 8;

    if (value)
    {
        array[s_byte] |= BYTE_SET_MASK[s_bit];
    }
    else
    {
        array[s_byte] &= BYTE_CLR_MASK[s_bit];
    }

}

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================


