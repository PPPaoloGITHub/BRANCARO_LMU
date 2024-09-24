/**
 *  @file		C_extensions.h
 *  @brief      Useful Macros, simplified types
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __C_extensions_H__
#define __C_extensions_H__

/******************************************************************************
 *                    I N C L U D E    F I L E S                              *
 * ***************************************************************************/
#include <p33CH512MP506.h>

/******************************************************************************
 *                    M A C R O   &   D E F I N E S                           *
 * ***************************************************************************/

// ============================================================
// ------------------- BYTE AND WORD ACCESS -------------------
// ------------------------------------------------------------
#define LOBYTE_LONG(mem)         (unsigned char)(  (unsigned long)(mem)        & 0xFFU)
#define MIDDLELOBYTE_LONG(mem)   (unsigned char)(( (unsigned long)(mem) >>  8) & 0xFFU)
#define MIDDLEHIBYTE_LONG(mem)   (unsigned char)(( (unsigned long)(mem) >> 16) & 0xFFU)
#define HIGHBYTE_LONG(mem)       (unsigned char)(( (unsigned long)(mem) >> 24) & 0xFFU)
#define LOWORD_LONG(mem)         (unsigned short)( (unsigned long)(mem) & 0xFFFFU)
#define HIWORD_LONG(mem) 		 (unsigned short)(((unsigned long)(mem) >> 16U ) & 0xFFFFU)
#define LOBYTE_WORD(mem)         (unsigned char) ( (unsigned short)(mem) & 0xFFU)
#define HIBYTE_WORD(mem) 		 (unsigned char) (((unsigned short)(mem) >> 8U) & 0xFFU)

// ============================================================
// --------------------- BIT MANIPULATION ---------------------
// ------------------------------------------------------------
#define BIT_TEST(mem,bit)   ((mem)&(1UL<<(bit)))
#define BIT_SET(mem,bit)    ((mem)|=(1UL<<(bit)))
#define BIT_CLR(mem,bit)    ((mem)&=~(1UL<<(bit)))
#define BIT_TOGGLE(mem,bit) ((mem)^=(1UL<<(bit)))

// ============================================================
// --------------------- MAX, MIN AND ABS ---------------------
// ------------------------------------------------------------
#define MAX(a, b) ((a) > (b) ? a : b)
#define MIN(a, b) ((a) < (b) ? a : b)
#define ABS(a)    ((a < 0) ? (-a) : (a))

// ============================================================
// --------------------- LOW PASS FILTER  ---------------------
// ------------------------------------------------------------
#define LPF(y,x,f) ( y = y + f * (x-y) )

// ============================================================
// -------------------------- BOUND ---------------------------
// ------------------------------------------------------------
#define Bound(x,y,z) (z<x?x:(z>y?y:z))
#define BoundF(x,y,z) Bound(x,y,z)

// ============================================================
// ----------------------- CONCATENATE ------------------------
// Concatenate preprocessor tokens A and B after macro-expanding them.
// ------------------------------------------------------------
/*
 * Concatenate preprocessor tokens A and B without expanding macro definitions
 * (however, if invoked from a macro, macro arguments are expanded).
 */
#define PPCAT_NX(A, B) A ## B

/*
 * Concatenate preprocessor tokens A and B after macro-expanding them.
 */
#define PPCAT(A, B) PPCAT_NX(A, B)

/*
 * Turn A into a string literal without expanding macro definitions
 * (however, if invoked from a macro, macro arguments are expanded).
 */
#define STRINGIZE_NX(A) #A

/*
 * Turn A into a string literal after macro-expanding it.
 */
#define STRINGIZE(A) STRINGIZE_NX(A)


/******************************************************************************
 *             P U B L I C   T Y P E S   &   C O N S T A N T S                *
 * ***************************************************************************/

typedef unsigned char       uint8;
typedef unsigned short int  uint16;
typedef unsigned long int   uint32;
typedef unsigned long long  uint64;

typedef signed char         sint8;
typedef signed short int    sint16;
typedef signed long int     sint32;
typedef signed long long    sint64;

typedef float               float32;
typedef double              float64;

typedef enum _BOOL_TYPE
{
    FALSE		= 0,
    TRUE		= 1
} BOOL_TYPE;

typedef BOOL_TYPE T_BOOL;

typedef enum _ON_OFF_TYPE
{
    OFF			= 0,
    ON			= 1
} ON_OFF_TYPE;

typedef enum _PASS_FAIL_TYPE
{
    FAIL		= 0,
    PASS		= 1
} PASS_FAIL_TYPE;


typedef enum _COMPLETE_TYPE
{
    INCOMPLETE	= 0,
    COMPLETE	= 1
} COMPLETE_TYPE;

typedef enum _ACTIVE_TYPE
{
    INACTIVE	= 0,
    ACTIVE		= 1
} ACTIVE_TYPE;

typedef enum _LOW_HIGH_TYPE
{
    LOW			= 0,
    HIGH		= 1
} LOW_HIGH_TYPE;


#ifndef ENABLED
	#define ENABLED   		(1)
#endif

#ifndef DISABLED
	#define DISABLED  		(0)
#endif

#ifndef NULL
	#define NULL 			(0)
#endif

#ifndef UNAVAILABLE
	#define UNAVAILABLE 	(10)
#endif

#ifndef AVAILABLE
	#define AVAILABLE 		(11)
#endif

// ============================================================
// ---------------------- ALL TYPE struct ----------------------
// ------------------------------------------------------------
typedef union
{
	uint8       ch[4];
	uint16      wd[2];
	uint32  	ulong;
	uint16  	uint;
	uint8   	ubyte;
	sint32		slong;
	sint16		sint;
	sint8		sbyte;
	float		ffloat;
	struct
    {
		uint8 ch_0;
		uint8 ch_1;
		uint8 ch_2;
		uint8 ch_3;
	}strch;
}TYPE_ALL;

/******************************************************************************
 *         P U B L I C   F U N C T I O N S   P R O T O T Y P E S              *
 * ***************************************************************************/



#endif /* _C_extensions_H_ */
