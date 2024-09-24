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
static void ResponseToNameCmd1                      (uint32 msgID, uint32 length, uint8 *payload);
static void ResponseToNameCmd2                      (uint32 msgID, uint32 length, uint8 *payload);


/************************** Parser Table ***************************/
static const PARSER_TABLE_TYPE ParserTable[] =
{
    // can message ID,                     // pointer to function handler 
    {NAME_CMD1,                            &ResponseToNameCmd1              },
    {NAME_CMD2,                            &ResponseToNameCmd2              },
    
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
  * @note	call this function in interrupt task every 5ms
  */
void CAN_RMP__Handler5ms(void)
{
    /* Transmission of CAN HeartBeat messages on CAN_BUS */
    CAN_RMP_Interf.HeartBeat();
    
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
     * Payload: Byte0 ÷ Byte2 => HWNumberFromList
     *          Byte3 ÷ Byte5 => SWNumberFromList
     *          Byte6         => Version From MAJOR SW Version
     *          Byte7         => Version From MINOR SW Version
     * 
     * Second message sent:
     * MsgID:   CAN_MSG_ID_HEARTBEAT_SECOND
     * DLC:     8 Bytes
     * Payload: Byte0         => LMU Unit Number
     *          Byte1 ÷ Byte7 => not used
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
        
        VERSION_Interf.HwPartNumber(str);
        txData[3] = str[8]  - '0';              // ASCII code offset
        txData[4] = str[9]  - '0';              // ASCII code offset
        txData[5] = str[10] - '0';              // ASCII code offset
        
        txData[6] = VERSION_Interf.SwVersionGet(VERSION_MAJOR);
        txData[7] = VERSION_Interf.SwVersionGet(VERSION_MINOR);
        CAN_RMP_Interf.Send(CAN_MSG_ID_HEARTBEAT_FIRST, DLC_8, txData);

        txData[0] = 1;  // default = 1; programmable with a CAN command TODO:
        txData[1] = 0;  // 
        txData[2] = 0;  //
        txData[3] = 0;  //
        txData[4] = 0;  //
        txData[5] = 0;  //
        txData[6] = 0;  //
        txData[7] = 0;  //
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


/*********** Implementation of table-based message handlers ***********/
/**
  * @brief  This function performs the response to command 1
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void ResponseToNameCmd1(uint32 msgID, uint32 length, uint8 *payload)
{
    if(payload[0] == 1)
    {
        RGBBlue_SetHigh();
    }
    else
    {
        RGBBlue_SetLow();
    }
    
    if(payload[1] == 1)
    {
        RGBGreen_SetHigh();
    }
    else
    {
        RGBGreen_SetLow();
    }
    
    if(payload[2] == 1)
    {
        RGBRed_SetHigh();
    }
    else
    {
        RGBRed_SetLow();
    }
}


/**
  * @brief  This function performs the response to command 2
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void ResponseToNameCmd2(uint32 msgID, uint32 length, uint8 *payload)
{
    
}
