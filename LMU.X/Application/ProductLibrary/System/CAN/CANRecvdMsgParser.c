/**
 *  @file       CANRecvdMsgParser.c
 *  @brief      CAN received messages parser module handles all CAN received messages
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <stdio.h>
#include "../../../AppSpecific/AppSpecificInclude/Version.h"
#include "../../ProductLibraryInclude/Timers.h"
#include "../../../../mcc_generated_files/system/pins.h"
#include "../../ProductLibraryInclude/ADCManager.h"
#include "../../ProductLibraryInclude/MCP23017.h"
#include "../../ProductLibraryInclude/PCA9685.h"
#include "../../ProductLibraryInclude/ADS7128.h"
#include "../../ProductLibraryInclude/ResetTest.h"

#include "../../ProductLibraryInclude/CANRecvdMsgParser.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------


//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static bool CAN_RMP_Receive(CAN_OBJ_TYPE *rxCanMsg);
static void CAN_RMP_Send(uint32 msgID, uint8 length, uint8 *data);
static void CAN_RMP_HeartBeat(void);
static void CAN_RMP_Parser(void);

#ifdef CAN_TEST_EXECUTION
    static void CAN_RMP_TestTx5ms(void);
    static void CAN_RMP_TestRx5ms(void);
#endif  /* CAN_TEST_EXECUTION */

const struct CAN_RMP_INTRFACE_STRUCT CAN_RMP_Interf =
{
    .Initialize      = &CAN_RMP__Initialize,
    .Handler5ms      = &CAN_RMP__Handler5ms,
    .Receive         = &CAN_RMP_Receive,
    .Send            = &CAN_RMP_Send,
    .HeartBeat       = &CAN_RMP_HeartBeat,
    .Parser          = &CAN_RMP_Parser,
    
#ifdef CAN_TEST_EXECUTION    
    .TestTx          = &CAN_RMP_TestTx5ms,
    .TestRx          = &CAN_RMP_TestRx5ms,
#endif  /* CAN_TEST_EXECUTION */    
};

/*********** Declaration of table-based message handlers ***********/
static void eCB1Handler             (uint32 msgID, uint32 length, uint8 *payload);
static void eCB2Handler             (uint32 msgID, uint32 length, uint8 *payload);
static void eCB3Handler             (uint32 msgID, uint32 length, uint8 *payload);
static void eCB4Handler             (uint32 msgID, uint32 length, uint8 *payload);
static void eCB5Handler             (uint32 msgID, uint32 length, uint8 *payload);
static void eCB6Handler             (uint32 msgID, uint32 length, uint8 *payload);
static void eCB7Handler             (uint32 msgID, uint32 length, uint8 *payload);
static void eCB8Handler             (uint32 msgID, uint32 length, uint8 *payload);
static void eCB9Handler             (uint32 msgID, uint32 length, uint8 *payload);
static void eCB10Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB11Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB12Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB13Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB14Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB15Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB16Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB17Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB18Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB19Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB20Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB21Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB22Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB23Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB24Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB25Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB26Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB27Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB28Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB29Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB30Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB31Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB32Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB33Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB34Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB35Handler            (uint32 msgID, uint32 length, uint8 *payload);
static void eCB36Handler            (uint32 msgID, uint32 length, uint8 *payload);

static void PgdInHandler            (uint32 msgID, uint32 length, uint8 *payload);

static void PgdOut1Handler          (uint32 msgID, uint32 length, uint8 *payload);
static void PgdOut2Handler          (uint32 msgID, uint32 length, uint8 *payload);
static void PgdOut3Handler          (uint32 msgID, uint32 length, uint8 *payload);
static void PgdOut4Handler          (uint32 msgID, uint32 length, uint8 *payload);

static void TemperatureHandler      (uint32 msgID, uint32 length, uint8 *payload);

static void ResetCommand            (uint32 msgID, uint32 length, uint8 *payload);
static void SelfTestCommand         (uint32 msgID, uint32 length, uint8 *payload);

static void OringHandler            (uint32 msgID, uint32 length, uint8 *payload);

static void ChangeUnitNumberHandler (uint32 msgID, uint32 length, uint8 *payload);

/************************** Parser Table ***************************/
static const PARSER_TABLE_TYPE ParserTable[] =
{
    // can message ID,                     // pointer to function handler 
    {eCB_PP_OUT1_ID,              &eCB1Handler            },
    {eCB_PP_OUT2_ID,              &eCB2Handler            },         
    {eCB_PP_OUT3_ID,              &eCB3Handler            },         
    {eCB_PP_OUT4_ID,              &eCB4Handler            },         
    {eCB_PP_OUT5_ID,              &eCB5Handler            },         
    {eCB_PP_OUT6_ID,              &eCB6Handler            },         
    {eCB_PP_OUT7_ID,              &eCB7Handler            },         
    {eCB_PP_OUT8_ID,              &eCB8Handler            },         
    {eCB_PP_OUT9_ID,              &eCB9Handler            },         
    {eCB_PP_OUT10_ID,             &eCB10Handler           },         
    {eCB_PP_OUT11_ID,             &eCB11Handler           },         
    {eCB_PP_OUT12_ID,             &eCB12Handler           },         
    {eCB_PP_OUT13_ID,             &eCB13Handler           },         
    {eCB_PP_OUT14_ID,             &eCB14Handler           },         
    {eCB_PP_OUT15_ID,             &eCB15Handler           },         
    {eCB_PP_OUT16_ID,             &eCB16Handler           },         
    {eCB_PP_OUT17_ID,             &eCB17Handler           },         
    {eCB_PP_OUT18_ID,             &eCB18Handler           },         
    {eCB_PP_OUT19_ID,             &eCB19Handler           },         
    {eCB_PP_OUT20_ID,             &eCB20Handler           },         
    {eCB_PP_OUT21_ID,             &eCB21Handler           },         
    {eCB_PP_OUT22_ID,             &eCB22Handler           },         
    {eCB_PP_OUT23_ID,             &eCB23Handler           },         
    {eCB_PP_OUT24_ID,             &eCB24Handler           },         
    {eCB_PP_OUT25_ID,             &eCB25Handler           },         
    {eCB_PP_OUT26_ID,             &eCB26Handler           },         
    {eCB_PP_OUT27_ID,             &eCB27Handler           },         
    {eCB_PP_OUT28_ID,             &eCB28Handler           },         
    {eCB_PP_OUT29_ID,             &eCB29Handler           },         
    {eCB_PP_OUT30_ID,             &eCB30Handler           },         
    {eCB_PP_OUT31_ID,             &eCB31Handler           },         
    {eCB_PP_OUT32_ID,             &eCB32Handler           },         
    {eCB_PP_OUT33_ID,             &eCB33Handler           },         
    {eCB_PP_OUT34_ID,             &eCB34Handler           },         
    {eCB_PP_OUT35_ID,             &eCB35Handler           },         
    {eCB_PP_OUT36_ID,             &eCB36Handler           },         

    {PGD_IN_ID,                   &PgdInHandler           },         

    {PGD_OUT1_ID,                 &PgdOut1Handler         },         
    {PGD_OUT2_ID,                 &PgdOut2Handler         },         
    {PGD_OUT3_ID,                 &PgdOut3Handler         },         
    {PGD_OUT4_ID,                 &PgdOut4Handler         },         

    {TEMPERATURE_ID,              &TemperatureHandler     },         

    {RESET_CMD_ID,                &ResetCommand           },         
    {SELF_TEST_CMD_ID,            &SelfTestCommand        },         

    {ORING_ID,                    &OringHandler           },         

    {CHANGE_UNIT_NUMBER_CMD_ID,   &ChangeUnitNumberHandler},
};
#define PARSER_TABLE_SIZE (sizeof(ParserTable) / sizeof(PARSER_TABLE_TYPE))

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes the CAN received messages parser module
  *
  * @param  None
  * @retval None
  * @note	None
  */
void CAN_RMP__Initialize(void)
{
    /* Initialization CAN HeartBeat period */
    TIMERS__MsSet(MS_TIMER_CAN_HEARTBEAT_PERIOD, CAN_HEARTBEAT_PERIOD);
}

/**
  * @brief  CAN received messages parser module handler. It manages all the module functionalities
  *
  * @param  None
  * @retval None
  * @note	call this function in the task every 5ms
  */
void CAN_RMP__Handler5ms(void)
{
    /* Execute CAN Parser on received message */
#ifndef CAN_TEST_EXECUTION
    /* *** ONLY ONE CANReceive FUNCTION AT A TIME CAN WORK!!! *** 
     *     CAN_RMP_Interf.Parser() and  CAN_RMP_Interf.TestRx() can not be called consecutively!
     */
    CAN_RMP_Interf.Parser();
#endif    
    
#ifdef CAN_TEST_EXECUTION    
 	CAN_RMP_Interf.TestRx();
    CAN_RMP_Interf.TestTx();
#endif  /* CAN_TEST_EXECUTION */    
}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function receives the CAN messages 
  *
  * @param  rxCanMsg: pointer to CAN_OBJ_TYPE can object. Here is returned the read can message
  * @retval true: CAN message read success; false: CAN message read fail or no CAN messages
  * @note	None
  */
static bool CAN_RMP_Receive(CAN_OBJ_TYPE *rxMsg)
{
    bool retVal = false;
    
    if(CAN1_ReceivedMessageCountGet() > 0) 
    {
        retVal = CAN1_Receive(rxMsg);
    }
    
    return (retVal);
}

/**
  * @brief  This function transmits the CAN messages on CAN_BUS
  *
  * @param  msgID:  can ID for the transmitted message
  *         length: payload data length
  *         data:   pointer to uint8 array containing the payload data
  * @retval None
  * @note	None
  */
static void CAN_RMP_Send(uint32 msgID, uint8 length, uint8 *data)
{
    static CAN_OBJ_TYPE txMsg;
    
    /* Initialization fixed fields of canTxMsg object */
    txMsg.field.formatType = CAN_2_0_FORMAT;
    txMsg.field.brs        = CAN_NON_BRS_MODE;
    txMsg.field.frameType  = CAN_FRAME_DATA;
    txMsg.field.idType     = CAN_FRAME_EXT;
    txMsg.msgId            = msgID;
    txMsg.field.dlc        = length;
    txMsg.data             = data;
    
    if(CAN_TX_FIFO_AVAILABLE == (CAN1_TransmitFIFOStatusGet(CAN1_TXQ) & CAN_TX_FIFO_AVAILABLE))
    {
        CAN1_Transmit(CAN1_TXQ, &txMsg);
    }
}

/**
  * @brief  This function transmits CAN HeartBeat messages on CAN_BUS
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void CAN_RMP_HeartBeat(void)
{
    /* CAN Message HeartBeat structure */
    /*
     * P/N HW: BR-9070-HWNumberFromList[3 digit]
     * P/N SW: BR-9074-SWNumberFromList[3 digit]-VersionFromMAJORSWVersion[2 digit]
     * 
     * First message sent:
     * MsgID:   CAN_MSG_ID_HEARTBEAT_FIRST
     * DLC:     8 Bytes
     * Payload: Byte0 ÷ Byte2 => Last 3 digit from the LMU HW Part Number BR-9070-013
     *          Byte3 ÷ Byte5 => Last 3 digit from the LMU SW Part Number BR-9074-002
     *          Byte6         => Version From MAJOR SW Version
     *          Byte7         => Version From MINOR SW Version
     * 
     * Second message sent:
     * MsgID:   CAN_MSG_ID_HEARTBEAT_SECOND
     * DLC:     8 Bytes
     * Payload: Byte0         => LMU Unit Number
     *          Byte1 ÷ Byte3 => not used
     *          Byte4 ÷ Byte5 => Logic Board Temperature
     *          Byte6 ÷ Byte7 => Power Board Temperature
     *    
     * NOTE: LMU Unit Number is external programmable with external CAN message
     * 
     */
    
    uint8 txData[DLC_8];
    char str[30];  
     
    if(TIMERS__MsGetStatus(MS_TIMER_CAN_HEARTBEAT_PERIOD) == TIMERS_COMPLETED)
    {
        TIMERS__MsSet(MS_TIMER_CAN_HEARTBEAT_PERIOD, CAN_HEARTBEAT_PERIOD);
        
        VERSION_Interf.HwPartNumber(str);
        txData[0] = str[8]  - '0';              // ASCII code offset
        txData[1] = str[9]  - '0';              // ASCII code offset
        txData[2] = str[10] - '0';              // ASCII code offset
        
        VERSION_Interf.SwPartNumber(str);
        txData[3] = str[8]  - '0';              // ASCII code offset
        txData[4] = str[9]  - '0';              // ASCII code offset
        txData[5] = str[10] - '0';              // ASCII code offset
        
        txData[6] = VERSION_Interf.SwVersionGet(VERSION_MAJOR);
        txData[7] = VERSION_Interf.SwVersionGet(VERSION_MINOR);
        CAN_RMP_Interf.Send(CAN_MSG_ID_HEARTBEAT_FIRST, DLC_8, txData);

        txData[0] = 0;  // default = 0; programmable with a CAN command TODO:
        txData[1] = 0;  // 
        txData[2] = 0;  //
        txData[3] = 0;  //
        txData[4] = HIBYTE_WORD(ADCManager_Interf.GetT_LOGICBoard());  //
        txData[5] = LOBYTE_WORD(ADCManager_Interf.GetT_LOGICBoard());  //
        txData[6] = HIBYTE_WORD(ADCManager_Interf.GetT_PWRBoard());  //
        txData[7] = LOBYTE_WORD(ADCManager_Interf.GetT_PWRBoard());  //
        CAN_RMP_Interf.Send(CAN_MSG_ID_HEARTBEAT_SECOND, DLC_8, txData);
    }
}


/**
  * @brief  This function performs the entry point for polling or interrupt
  *         based CAN Received Messages Parser
  *
  * @param  None
  * @retval None
  * @note	Call this function every 5ms
  */
static void CAN_RMP_Parser(void)
{
    static CAN_OBJ_TYPE rxMsg;
    MsgHandler_TYPE handlerFunction;
    uint16 k;
     
    rxMsg.msgId = 0;
    if(CAN_RMP_Interf.Receive(&rxMsg) == true)
    {
        handlerFunction = (void *)0;

        // I search in the ParserTable table for the received canID
        for(k=0; k < PARSER_TABLE_SIZE; k++)
        {
            if(rxMsg.msgId == ParserTable[k].msgID)
            {
                // message receive identified 
                handlerFunction = ParserTable[k].Handler;
                break;
            }
        }

        if(handlerFunction != (void *)0)
        {
            // Execution of the function associated with the received CAN message
            handlerFunction(rxMsg.msgId, rxMsg.field.dlc, rxMsg.data);
        }
    }
}


#ifdef CAN_TEST_EXECUTION
void CAN_RMP_TestTx5ms(void)
{
    uint8 dataTest[8] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48};
    
    CAN_RMP_Interf.Send(0x10A, 8, dataTest);
    CAN_RMP_Interf.Send(0x10B, 8, dataTest);
    CAN_RMP_Interf.Send(0x10C, 8, dataTest);
    CAN_RMP_Interf.Send(0x10D, 8, dataTest);
}

void CAN_RMP_TestRx5ms(void)
{
    #define TEST_CAN_RECEIVED_MSG_ID     0x00020000
    #define TEST_CAN_PAYLOAD_B0          0x66
    #define TEST_CAN_PAYLOAD_B1          0x68
    #define TEST_CAN_PAYLOAD_B2          0x70

    static CAN_OBJ_TYPE rxMsg;
    static uint8 txData[DLC_8];
    
    rxMsg.msgId = 0;
    if(CAN_RMP_Interf.Receive(&rxMsg) == true)
    {
        if((rxMsg.msgId == TEST_CAN_RECEIVED_MSG_ID) && 
           (rxMsg.data[0] == TEST_CAN_PAYLOAD_B0) &&
           (rxMsg.data[1] == TEST_CAN_PAYLOAD_B1) &&
           (rxMsg.data[2] == TEST_CAN_PAYLOAD_B2) )
        {
            txData[0] += 1;
            txData[1] += 1;
            txData[2] += 1;
            txData[3] += 1;
            txData[4] += 1;
            txData[5] += 1;
            txData[6] += 1;
            txData[7] += 1;

            CAN_RMP_Interf.Send(rxMsg.msgId, rxMsg.field.dlc, txData);
        }
    }
}
#endif  /* CAN_TEST_EXECUTION */

/**********************************************************************/
/*********** Implementation of table-based message handlers ***********/
/**********************************************************************/
/**
  * @brief  This function performs the response to eCB1 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB1Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB2 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB2Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB3 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB3Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB4 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB4Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB5 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB5Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB6 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB6Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB7 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB7Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB8 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB8Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB9 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB9Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB10 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB10Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB11 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB11Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB12 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB12Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB13 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB13Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB14 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB14Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB15 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB15Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB16 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB16Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB17 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB17 has PWM
  */
static void eCB17Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}


/**
  * @brief  This function performs the response to eCB18 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB18 has PWM
  */
static void eCB18Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB19 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB19 has PWM
  */
static void eCB19Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB20 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB20 has PWM
  */
static void eCB20Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB21 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB21 has PWM
  */
static void eCB21Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB22 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB22 has PWM
  */
static void eCB22Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB23 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB23 has PWM
  */
static void eCB23Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB24 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB24 has PWM
  */
static void eCB24Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB25 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB25 has PWM
  */
static void eCB25Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB26 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB26 has PWM
  */
static void eCB26Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB27 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB27 has PWM
  */
static void eCB27Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB28 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB28 has PWM
  */
static void eCB28Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB29 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB29 has PWM
  */
static void eCB29Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB30 Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB30 has PWM
  */
static void eCB30Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB31 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB31Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB32 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB32Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB33 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB33Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB34 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB34Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB35 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB35Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to eCB36 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB36Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to PDG_IN Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void PgdInHandler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to PDG_OUT1 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void PgdOut1Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to PDG_OUT2 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void PgdOut2Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to PDG_OUT3 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void PgdOut3Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to PDG_OUT4 Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void PgdOut4Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to Temperature Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void TemperatureHandler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to Reset Command
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void ResetCommand(uint32 msgID, uint32 length, uint8 *payload)
{
    uint8 txBuff[CAN_MAX_PAYLOAD];
    uint8 k;
    
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
    
    txBuff[BYTE0] = CAN_ANSWER;
    if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_COMMAND))
    {
        if(payload[BYTE1] == CAN_ON_CMD)
        {
            // CAN Command OK:
            txBuff[BYTE1] = CAN_ON_CMD;
            RESET_TEST_Interf.ResetCmd();
        }
        else
        {
            txBuff[BYTE1] = CAN_ERROR_ANSWER;
        }    
    }
    else
    {
        txBuff[BYTE1] = CAN_ERROR_ANSWER;
    }
    CAN_RMP_Send(msgID, CAN_DLC_DEFAULT, txBuff);
}

/**
  * @brief  This function performs the response to Self Test Command
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void SelfTestCommand(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to Oring Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void OringHandler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}

/**
  * @brief  This function performs the response to Change LMU Unit Number
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void ChangeUnitNumberHandler (uint32 msgID, uint32 length, uint8 *payload)
{
    
}