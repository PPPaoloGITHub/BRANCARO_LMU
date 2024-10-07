/**
 *  @file       FeedbackCAN.h
 *  @brief      This file manages feedback CAN
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries..  All rights reserved - CONFIDENTIAL  *****
 *
 */

#ifndef __FEEDBACKCAN_H__
#define __FEEDBACKCAN_H__

#include "../../ProductLibrary/ProductLibraryInclude/C_extensions.h"
#include "CANFeedback_prm.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
#define CAN_PAYLOAD     8       // Max number of bytes in a single CAN message

/* LSI feedbacks; LSI = Loads and Sensors Interface*/
typedef union
{
    struct
	{
    	/* B0: description for B0 byte */
    	uint8 Byte0bit0		: 1;
    	uint8 Byte0bit1		: 1;
        uint8 Byte0bit2		: 1;
        uint8 Byte0bit3		: 1;
        uint8 Byte0bit4		: 1;
        uint8 Byte0bit5		: 1;
		uint8 Byte0bit6		: 1;
		uint8 Byte0bit7		: 1;

		/* B1: description for B1 byte */
		uint8 Byte1bit0	    : 1;
		uint8 Byte1bit1	    : 1;
		uint8 Byte1bit2	    : 1;
		uint8 Byte1bit3	    : 1;
		uint8 Byte1bit4	    : 1;
		uint8 Byte1bit5	    : 1;
		uint8 Byte1bit6	    : 1;
		uint8 Byte1bit7	    : 1;

		/* B2: description for B2 byte */
    	uint8 Byte2bit0  	: 1;
		uint8 Byte2bit1  	: 1;
		uint8 Byte2bit2  	: 1;
		uint8 Byte2bit3  	: 1;
		uint8 Byte2bit4  	: 1;
		uint8 Byte2bit5  	: 1;
		uint8 Byte2bit6  	: 1;
		uint8 Byte2bit7  	: 1;

		/* B3: description for B3 byte */
		uint8 Byte3bit0		: 1;
		uint8 Byte3bit1		: 1;
		uint8 Byte3bit2		: 1;
		uint8 Byte3bit3		: 1;
		uint8 Byte3bit4		: 1;
		uint8 Byte3bit5		: 1;
		uint8 Byte3bit6		: 1;
		uint8 Byte3bit7		: 1;

		/* B4: description for B4 byte */
		uint8 Byte4bit0     : 1;
		uint8 Byte4bit1     : 1;
		uint8 Byte4bit2     : 1;
		uint8 Byte4bit3     : 1;
		uint8 Byte4bit4     : 1;
		uint8 Byte4bit5     : 1;
		uint8 Byte4bit6     : 1;
		uint8 Byte4bit7     : 1;

		/* B5: description for B5 byte */
		uint8 Byte5bit0     : 1;
		uint8 Byte5bit1     : 1;
		uint8 Byte5bit2     : 1;
		uint8 Byte5bit3     : 1;
		uint8 Byte5bit4     : 1;
		uint8 Byte5bit5     : 1;
		uint8 Byte5bit6     : 1;
		uint8 Byte5bit7     : 1;

		/* B6: description for B6 byte */
		uint8 Byte6bit0     : 1;
		uint8 Byte6bit1     : 1;
		uint8 Byte6bit2     : 1;
		uint8 Byte6bit3     : 1;
		uint8 Byte6bit4     : 1;
		uint8 Byte6bit5     : 1;
		uint8 Byte6bit6     : 1;
		uint8 Byte6bit7     : 1;
        
        /* B7: description for B7 byte */
        uint8 Byte7bit0     : 1;
		uint8 Byte7bit1     : 1;
		uint8 Byte7bit2     : 1;
		uint8 Byte7bit3     : 1;
		uint8 Byte7bit4     : 1;
		uint8 Byte7bit5     : 1;
		uint8 Byte7bit6     : 1;
		uint8 Byte7bit7     : 1;
	};
	uint8 lsiFbkArray[CAN_PAYLOAD]; /* union as a bytes array */

} LSI_FBK_TYPE;		/* LSI = Loads and Sensors Interface */



struct FBK_INTERFACE_STRUCT
{
    void         (*Initialize) (void);
    void         (*Handler5ms) (void);
    void 		 (*SetLsiFbk)  (CANFBK_IDs_LSI_TYPE lsiID, LSI_FBK_TYPE *lsiFeedback);
    LSI_FBK_TYPE (*GetLsiFbk)  (CANFBK_IDs_LSI_TYPE lsiID);
};

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct FBK_INTERFACE_STRUCT CANFBK_Interf;

void CANFBK__Initialize(void);
void CANFBK__Handler5ms (void);

#endif /* __FEEDBACKCAN_H__ */

