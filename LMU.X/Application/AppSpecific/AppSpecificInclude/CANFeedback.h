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
    	uint8 NotUsed0		: 1;
    	uint8 NotUsed1		: 1;
        uint8 NotUsed2		: 1;
        uint8 NotUsed3		: 1;
        uint8 NotUsed4		: 1;
        uint8 NotUsed5		: 1;
		uint8 NotUsed6		: 1;
		uint8 NotUsed7		: 1;

		/* B1: description for B1 byte */
		uint8 NotUsed8	    : 1;
		uint8 NotUsed9	    : 1;
		uint8 NotUsed10	    : 1;
		uint8 NotUsed11	    : 1;
		uint8 NotUsed12	    : 1;
		uint8 NotUsed13	    : 1;
		uint8 NotUsed14	    : 1;
		uint8 NotUsed15	    : 1;

		/* B2: description for B2 byte */
    	uint8 NotUsed16  	: 1;
		uint8 NotUsed17  	: 1;
		uint8 NotUsed18  	: 1;
		uint8 NotUsed19  	: 1;
		uint8 NotUsed20  	: 1;
		uint8 NotUsed21  	: 1;
		uint8 NotUsed22  	: 1;
		uint8 NotUsed23  	: 1;

		/* B3: description for B3 byte */
		uint8 NotUsed24		: 1;
		uint8 NotUsed25		: 1;
		uint8 NotUsed26		: 1;
		uint8 NotUsed27		: 1;
		uint8 NotUsed28		: 1;
		uint8 NotUsed29		: 1;
		uint8 NotUsed30		: 1;
		uint8 NotUsed31		: 1;

		/* B4: description for B4 byte */
		uint8 NotUsed32     : 1;
		uint8 NotUsed33     : 1;
		uint8 NotUsed34     : 1;
		uint8 NotUsed35     : 1;
		uint8 NotUsed36     : 1;
		uint8 NotUsed37     : 1;
		uint8 NotUsed38     : 1;
		uint8 NotUsed39     : 1;


		/* B5: description for B5 byte */
		uint8 NotUsed40	    : 8;

		/* B6,B7: description for B6 and B7 bytes */
		uint8 NotUsed41MSB	: 8;
		uint8 NotUsed42LSB	: 8;
	};
	uint8 lsiFbkArray[CAN_PAYLOAD]; /* union as a byte array */

} LSI_FBK_TYPE;		/* LSI = Loads and Sensors Interface */



struct FBK_INTERFACE_STRUCT
{
    void         (*Initialize) (void);
    void         (*Handler5ms) (void);
    void 		 (*SETLsiFbk)  (LSI_FBK_TYPE *lsiFeedback);
    LSI_FBK_TYPE (*GETLsiFbk)  (void);
};

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
extern const struct FBK_INTERFACE_STRUCT CANFBK_Interf;

void CANFBK__Initialize(void);
void CANFBK__Handler5ms (void);

#endif /* __FEEDBACKCAN_H__ */

