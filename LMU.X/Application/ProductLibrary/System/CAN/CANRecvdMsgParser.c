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
#include <math.h>
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
#define CAN_MAX_DUTY_CYCLE     100     // Maximum PWM Duty Cycle value

typedef struct
{
    uint8 PP_OUT_17;
    uint8 PP_OUT_18;
    uint8 PP_OUT_19;
    uint8 PP_OUT_20;
    uint8 PP_OUT_21;
    uint8 PP_OUT_22;
    uint8 PP_OUT_23;
    uint8 PP_OUT_24;
    uint8 PP_OUT_25;
    uint8 PP_OUT_26;
    uint8 PP_OUT_27;
    uint8 PP_OUT_28;
    uint8 PP_OUT_29;
    uint8 PP_OUT_30;
    
    uint8 PDG_OUT_1;
    uint8 PDG_OUT_2;
} PWM_VALUES_TYPE;
static PWM_VALUES_TYPE pwmValue; 

static uint8 LMUun;     // LMU Unit Number

typedef struct
{
    MCP23017_I2C_ADDR_TYPE writeI2CDeviceAddr;      // write action on I/O EXPANDER pin
    MCP23017_PORT_TYPE writePort;                   // write action on I/O EXPANDER pin
    MCP23017_PIN_TYPE writePin;                     // write action on I/O EXPANDER pin
    
    MCP23017_I2C_ADDR_TYPE readFaultI2CDeviceAddr;  // read fault status on I/O EXPANDER pin
    MCP23017_PORT_TYPE readFaultPort;               // read fault status on I/O EXPANDER pin
    MCP23017_PIN_TYPE readFaultPin;                 // read fault status on I/O EXPANDER pin
    
    ADS7128_I2C_ADDR_TYPE readCurrentI2CDeviceAddr; // read eCB current
    ADS7128_CHANNEL_TYPE readCurrentChannel;        // read eCB current
    float readCurrentGain;                          // conversion Gain factor
    
    PCA9685_I2C_ADDR_TYPE PWMI2CDeviceAddr;         // set PWM value into eCB PWM
    PCA9685_CHANNELS_TYPE PWMChannel;               // set PWM value into eCB PWM
    uint8 *ptrPWMValue;                             // set PWM value into eCB PWM
}eCB_CONTEXT_TYPE;


//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static bool  CAN_RMP_Receive(CAN_OBJ_TYPE *rxCanMsg);
static void  CAN_RMP_Send(uint32 msgID, uint8 length, uint8 *data);
static void  CAN_RMP_HeartBeat(void);
static uint8 CAN_RMP_GetLMUun(void);

static void  CAN_RMP_Parser(void);
static void  CAN_RMP_eCBBodyHandler(uint32 msgID, uint32 length, uint8 *payload, eCB_CONTEXT_TYPE eCBContext);


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
    .GetLMUun        = &CAN_RMP_GetLMUun,
    
#ifdef CAN_TEST_EXECUTION    
    .TestTx          = &CAN_RMP_TestTx5ms,
    .TestRx          = &CAN_RMP_TestRx5ms,
#endif  /* CAN_TEST_EXECUTION */    
};

/*********** Declaration of table-based message handlers ***********/
static void eCB1Handler         (uint32 msgID, uint32 length, uint8 *payload);
static void eCB2Handler         (uint32 msgID, uint32 length, uint8 *payload);
static void eCB3Handler         (uint32 msgID, uint32 length, uint8 *payload);
static void eCB4Handler         (uint32 msgID, uint32 length, uint8 *payload);
static void eCB5Handler         (uint32 msgID, uint32 length, uint8 *payload);
static void eCB6Handler         (uint32 msgID, uint32 length, uint8 *payload);
static void eCB7Handler         (uint32 msgID, uint32 length, uint8 *payload);
static void eCB8Handler         (uint32 msgID, uint32 length, uint8 *payload);
static void eCB9Handler         (uint32 msgID, uint32 length, uint8 *payload);
static void eCB10Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB11Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB12Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB13Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB14Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB15Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB16Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB17Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB18Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB19Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB20Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB21Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB22Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB23Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB24Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB25Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB26Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB27Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB28Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB29Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB30Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB31Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB32Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB33Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB34Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB35Handler        (uint32 msgID, uint32 length, uint8 *payload);
static void eCB36Handler        (uint32 msgID, uint32 length, uint8 *payload);

static void PgdInHandler        (uint32 msgID, uint32 length, uint8 *payload);

static void PgdOut1Handler      (uint32 msgID, uint32 length, uint8 *payload);
static void PgdOut2Handler      (uint32 msgID, uint32 length, uint8 *payload);
static void PgdOut3Handler      (uint32 msgID, uint32 length, uint8 *payload);
static void PgdOut4Handler      (uint32 msgID, uint32 length, uint8 *payload);

static void TemperatureHandler  (uint32 msgID, uint32 length, uint8 *payload);

static void ResetCommand        (uint32 msgID, uint32 length, uint8 *payload);
static void SelfTestCommand     (uint32 msgID, uint32 length, uint8 *payload);

static void OringHandler        (uint32 msgID, uint32 length, uint8 *payload);

static void LMUSettingsHandler  (uint32 msgID, uint32 length, uint8 *payload);

/************************** Parser Table ***************************/
//const uint32 LMUunVal = 5; //(uint32)LMUun << 16;
//const uint32 can_cmd  = (uint32)CAN_CMD << 4;
//const uint32 can_rqst = (uint32)CAN_RQST << 4;
static const PARSER_TABLE_TYPE ParserTable[] =
{
    // can message ID,                     // pointer to function handler 
    {(eCB_PP_OUT1_ID    | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB1Handler       },
    {(eCB_PP_OUT1_ID    | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB1Handler       },
     
//    {(eCB_PP_OUT2_ID    | LMUun<<16 | CAN_CMD<<4  | CAN_eCB_ON_CMD),  &eCB2Handler       },
//    {(eCB_PP_OUT2_ID    | LMUun<<16 | CAN_CMD<<4  | CAN_eCB_OFF_CMD), &eCB2Handler       },
//    {(eCB_PP_OUT2_ID    | LMUun<<16 | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB2Handler       },
    {(eCB_PP_OUT2_ID    | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB2Handler       },
    {(eCB_PP_OUT2_ID    | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB2Handler       },  
    
    {(eCB_PP_OUT3_ID    | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB3Handler       },
    {(eCB_PP_OUT3_ID    | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB3Handler       },
     
    {(eCB_PP_OUT4_ID    | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB4Handler       },
    {(eCB_PP_OUT4_ID    | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB4Handler       },
             
    {(eCB_PP_OUT5_ID    | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB5Handler       },
    {(eCB_PP_OUT5_ID    | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB5Handler       },
       
    {(eCB_PP_OUT6_ID    | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB6Handler       },
    {(eCB_PP_OUT6_ID    | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB6Handler       },
              
    {(eCB_PP_OUT7_ID    | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB7Handler       },
    {(eCB_PP_OUT7_ID    | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB7Handler       },
              
    {(eCB_PP_OUT8_ID    | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB8Handler       },
    {(eCB_PP_OUT8_ID    | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB8Handler       },
         
    {(eCB_PP_OUT9_ID    | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB9Handler       },
    {(eCB_PP_OUT9_ID    | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB9Handler       },
              
    {(eCB_PP_OUT10_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB10Handler      },
    {(eCB_PP_OUT10_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB10Handler      },
         
    {(eCB_PP_OUT11_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB11Handler      },
    {(eCB_PP_OUT11_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB11Handler      },
            
    {(eCB_PP_OUT12_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB12Handler      },
     {(eCB_PP_OUT12_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),    &eCB12Handler      },
           
    {(eCB_PP_OUT13_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB13Handler      },
    {(eCB_PP_OUT13_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB13Handler      },
            
    {(eCB_PP_OUT14_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB14Handler      },
    {(eCB_PP_OUT14_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB14Handler      },
            
    {(eCB_PP_OUT15_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB15Handler      },
    {(eCB_PP_OUT15_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB15Handler      },
         
    {(eCB_PP_OUT16_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB16Handler      },
    {(eCB_PP_OUT16_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB16Handler      },
    
    {(eCB_PP_OUT17_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB17Handler      },
    {(eCB_PP_OUT17_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB17Handler      },
            
    {(eCB_PP_OUT18_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB18Handler      },
    {(eCB_PP_OUT18_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB18Handler      },
        
    {(eCB_PP_OUT19_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB19Handler      },
    {(eCB_PP_OUT19_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB19Handler      },
            
    {(eCB_PP_OUT20_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB20Handler      },
    {(eCB_PP_OUT20_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB20Handler      },
            
    {(eCB_PP_OUT21_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB21Handler      },
    {(eCB_PP_OUT21_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB21Handler      },
            
    {(eCB_PP_OUT22_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB22Handler      },
    {(eCB_PP_OUT22_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB22Handler      },
           
    {(eCB_PP_OUT23_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB23Handler      },
    {(eCB_PP_OUT23_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB23Handler      },
            
    {(eCB_PP_OUT24_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB24Handler      },
    {(eCB_PP_OUT24_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB24Handler      },
          
    {(eCB_PP_OUT25_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB25Handler      },
    {(eCB_PP_OUT25_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB25Handler      },
           
    {(eCB_PP_OUT26_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB26Handler      },
    {(eCB_PP_OUT26_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB26Handler      },
             
    {(eCB_PP_OUT27_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB27Handler      },
    {(eCB_PP_OUT27_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB27Handler      },
            
    {(eCB_PP_OUT28_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB28Handler      },
    {(eCB_PP_OUT28_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB28Handler      },
           
    {(eCB_PP_OUT29_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB29Handler      },
    {(eCB_PP_OUT29_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB29Handler      },
            
    {(eCB_PP_OUT30_ID   | CAN_CMD<<4  | CAN_eCB_PWM_CMD), &eCB30Handler      },
    {(eCB_PP_OUT30_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST), &eCB30Handler      },
            
    {(eCB_PP_OUT31_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB31Handler      },
    {(eCB_PP_OUT31_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB31Handler      },
            
    {(eCB_PP_OUT32_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB32Handler      },
    {(eCB_PP_OUT32_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB32Handler      },
           
    {(eCB_PP_OUT33_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB33Handler      },
    {(eCB_PP_OUT33_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB33Handler      },
            
    {(eCB_PP_OUT34_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB34Handler      },
    {(eCB_PP_OUT34_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB34Handler      },
            
    {(eCB_PP_OUT35_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB35Handler      },
    {(eCB_PP_OUT35_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB35Handler      },
           
    {(eCB_PP_OUT36_ID   | CAN_CMD<<4  | CAN_eCB_NORMAL_CMD),  &eCB36Handler      },
    {(eCB_PP_OUT36_ID   | CAN_RQST<<4 | CAN_eCB_REQUEST),     &eCB36Handler      },
   
    {(PGD_IN_ID         | CAN_RQST<<4 | CAN_eCB_REQUEST),     &PgdInHandler      },         
       
    {(PGD_OUT1_ID       | CAN_CMD<<4  | CAN_PGD_OUT_PWM_CMD), &PgdOut1Handler    },
    {(PGD_OUT1_ID       | CAN_RQST<<4 | CAN_eCB_REQUEST),     &PgdOut1Handler    },
              
    {(PGD_OUT2_ID       | CAN_CMD<<4  | CAN_PGD_OUT_PWM_CMD), &PgdOut2Handler    },
    {(PGD_OUT2_ID       | CAN_RQST<<4 | CAN_eCB_REQUEST),     &PgdOut2Handler    },
             
    {(PGD_OUT3_ID       | CAN_CMD<<4  | CAN_PGD_OUT_NORMAL_CMD), &PgdOut3Handler    },
    {(PGD_OUT3_ID       | CAN_RQST<<4 | CAN_eCB_REQUEST),        &PgdOut3Handler    },
          
    {(PGD_OUT4_ID       | CAN_CMD<<4  | CAN_PGD_OUT_NORMAL_CMD), &PgdOut4Handler    },
     {(PGD_OUT4_ID       | CAN_RQST<<4 | CAN_eCB_REQUEST),       &PgdOut4Handler    },
   
    
    {(TEMPERATURE_ID   | CAN_RQST<<4 | CAN_TEMP_RQST),        &TemperatureHandler},         

    {(RESET_CMD_ID     | CAN_CMD<<4  | CAN_eCB_RESET),        &ResetCommand      },         
    {(SELF_TEST_CMD_ID | CAN_CMD<<4  | CAN_eCB_SELFTEST),     &SelfTestCommand   },         

    {(ORING_ID         | CAN_CMD<<4  | CAN_ORING_GPU_EN),             &OringHandler      },
    {(ORING_ID         | CAN_CMD<<4  | CAN_ORING_BATT_EN),            &OringHandler      },
    {(ORING_ID         | CAN_RQST<<4 | CAN_ORING_VOLTAGES_RQST),      &OringHandler      },
    {(ORING_ID         | CAN_RQST<<4 | CAN_ORING_BUS_CURRENT_RQST),   &OringHandler      },
    {(ORING_ID         | CAN_RQST<<4 | CAN_ORING_ENABLE_STATUS_RQST), &OringHandler      },
    
    {(LMU_SETTINGS_CMD_ID | CAN_CMD<<4  | CAN_SET_UNIT_NUMBER),       &LMUSettingsHandler},
    {(LMU_SETTINGS_CMD_ID | CAN_CMD<<4  | CAN_SET_CAN_BITRATE),       &LMUSettingsHandler},
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
    
    // TODO: load LMUun from the EEPROM
    LMUun = 0;
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
    CAN_RMP_Parser();
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
     *          Byte3         => LMU Unit Number
     *          Byte4 ÷ Byte7 => not used
     * 
     * Second message sent:
     * MsgID:   CAN_MSG_ID_HEARTBEAT_SECOND
     * DLC:     8 Bytes
     * Payload: Byte0 ÷ Byte2 => Last 3 digit from the LMU SW Part Number BR-9074-005
     *          Byte3         => Version From MAJOR SW Version
     *          Byte4         => Version From MINOR SW Version
     *          Byte5 ÷ Byte7 => not used
     *    
     * NOTE: LMU Unit Number is external programmable with external CAN message
     * 
     */
    
    uint8 txData[DLC_8];
    char str[30];
    uint32 msgID;
     
    if(TIMERS__MsGetStatus(MS_TIMER_CAN_HEARTBEAT_PERIOD) == TIMERS_COMPLETED)
    {
        TIMERS__MsSet(MS_TIMER_CAN_HEARTBEAT_PERIOD, CAN_HEARTBEAT_PERIOD);
        
        VERSION_Interf.HwPartNumber(str);
        txData[0] = str[8]  - '0';              // ASCII code offset
        txData[1] = str[9]  - '0';              // ASCII code offset
        txData[2] = str[10] - '0';              // ASCII code offset
        txData[3] = LMUun;                      // LMU Unit Number: default = 0; programmable with a CAN command
        txData[4] = 0;
        txData[5] = 0;
        txData[6] = 0;
        txData[7] = 0;
        msgID = CAN_MSG_ID_HEARTBEAT_FIRST | CAN_STATUS<<4 | CAN_PERIODIC_PUBLISH;
        CAN_RMP_Interf.Send(msgID, DLC_8, txData);

        
        VERSION_Interf.SwPartNumber(str);
        txData[0] = str[8]  - '0';              // ASCII code offset
        txData[1] = str[9]  - '0';              // ASCII code offset
        txData[2] = str[10] - '0';              // ASCII code offset
        txData[3] = VERSION_Interf.SwVersionGet(VERSION_MAJOR);
        txData[4] = VERSION_Interf.SwVersionGet(VERSION_MINOR);
        txData[5] = 0;
        txData[6] = 0;
        txData[7] = 0;
        msgID = CAN_MSG_ID_HEARTBEAT_SECOND | CAN_STATUS<<4 | CAN_PERIODIC_PUBLISH;
        CAN_RMP_Interf.Send(msgID, DLC_8, txData);
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

/**
  * @brief  This function returns the LMU Unit Number
  *
  * @param  None
  * @retval LMU Unit Number
  * @note	None
  */
static uint8 CAN_RMP_GetLMUun(void)
{
    return (LMUun);
}

/**
  * @brief  This function manages the eCB behavior when it receive the ON/OFF command
  *
  * @param[in]  eCBContex
  * @retval     None
  * @note	    None
  */
static void  CAN_RMP_eCBBodyHandler(uint32 msgID, uint32 length, uint8 *payload, eCB_CONTEXT_TYPE eCBContext)
{
    uint8  txBuff[CAN_MAX_PAYLOAD];
    uint16 readValue;
    bool   pinValue;
    uint8  k;
    uint32 txMsgID;
    float  currentValue;
    CAN_eCB_PARAMETERS_TYPE selectedAction;
    
    
    txMsgID = (msgID & CAN_OPERATIONS_MASK) | CAN_ANSWER<<4;
     
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
    
    selectedAction = msgID & 0x0000000F;
    
    switch(selectedAction)
    {
        default:
        case CAN_eCB_SELFTEST:
        case CAN_eCB_RESET:
            txBuff[BYTE0] = CAN_ERROR_ANSWER;
        break;
        
        case CAN_eCB_NORMAL_CMD:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_ON_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(eCBContext.writeI2CDeviceAddr, eCBContext.writePort, eCBContext.writePin, TRUE);
            }
            else if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_OFF_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(eCBContext.writeI2CDeviceAddr, eCBContext.writePort, eCBContext.writePin, FALSE);
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
         
        case CAN_eCB_PWM_CMD:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] <= CAN_MAX_DUTY_CYCLE))
            {
                // CAN PWM Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                
                *eCBContext.ptrPWMValue = payload[BYTE0];
                PCA9685_Interf.SetPWM(eCBContext.PWMI2CDeviceAddr, eCBContext.PWMChannel, payload[BYTE0]);
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
        
        case CAN_eCB_REQUEST:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_eCB_REQUEST))
            {
                // CAN Request OK:
 
                // Read pin value
                if(eCBContext.ptrPWMValue == NULL)
                {
                    pinValue = MCP23017_Interf.ReadPin(eCBContext.writeI2CDeviceAddr, eCBContext.writePort, eCBContext.writePin);
                    if(pinValue == TRUE)
                    {
                        txBuff[BYTE0] = CAN_ON_CMD;       //  PP_OUT value (ON or OFF)
                    }
                    else
                    {
                        txBuff[BYTE0] = CAN_OFF_CMD;      // PP_OUT value (ON or OFF)
                    }
                }
                else
                {
                    // Request in case of eCB PWM
                    txBuff[BYTE0] = *eCBContext.ptrPWMValue;
                }
                
                // Read eCB Fault pin: PP_OUT fault (0 = OK or 1 = FAULT)
                txBuff[BYTE1] = MCP23017_Interf.ReadPin(eCBContext.readFaultI2CDeviceAddr, eCBContext.readFaultPort, eCBContext.readFaultPin);

                // Read eCB Current
                ADS7128_Interf.ReadChannel(eCBContext.readCurrentI2CDeviceAddr, eCBContext.readCurrentChannel, &readValue);
                currentValue = ((float)readValue * CAN_ADC_EXP_VREF / CAN_ADC_RESOLUTION) * eCBContext.readCurrentGain; 
                currentValue = round(currentValue * 10);
                
                txBuff[BYTE2] = (uint8)currentValue;       // PP_OUT current value 
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
    }
    CAN_RMP_Send(txMsgID, CAN_DLC_DEFAULT, txBuff);
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
  * @brief  This function performs the response to eCB1 2,5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB1Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP1_I2C_ADDR;
    var.writePort                = MCP23017_PORTA;
    var.writePin                 = DO_PP_OUT_1_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP0_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_1_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP3_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_1_SENSE;
    var.readCurrentGain          = CAN_eCB_2A5_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB2 1A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB2Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP2_I2C_ADDR;
    var.writePort                = MCP23017_PORTB;
    var.writePin                 = DO_PP_OUT_2_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP3_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_2_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP6_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_2_SENSE;
    var.readCurrentGain          = CAN_eCB_1A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB3 2,5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB3Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP1_I2C_ADDR;
    var.writePort                = MCP23017_PORTB;
    var.writePin                 = DO_PP_OUT_3_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP0_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_3_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP4_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_3_SENSE;
    var.readCurrentGain          = CAN_eCB_2A5_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB4 2,5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB4Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP3_I2C_ADDR;
    var.writePort                = MCP23017_PORTB;
    var.writePin                 = DO_PP_OUT_4_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP3_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_4_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP6_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_4_SENSE;
    var.readCurrentGain          = CAN_eCB_2A5_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB5 100A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB5Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    uint8  txBuff[CAN_MAX_PAYLOAD];
    uint16 readValue;
    bool   pinValue;
    uint8  k;
    uint32 txMsgID;
    CAN_eCB_PARAMETERS_TYPE selectedAction;
 
    txMsgID = (msgID & CAN_OPERATIONS_MASK) | CAN_ANSWER<<4;
     
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
    
    selectedAction = msgID & 0x0000000F;
    
    switch(selectedAction)
    {
        default:
        case CAN_eCB_PWM_CMD:
        case CAN_eCB_SELFTEST:
        case CAN_eCB_RESET:
            txBuff[BYTE0] = CAN_ERROR_ANSWER;
        break;
        
        case CAN_eCB_NORMAL_CMD:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_ON_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(IO_EXP4_I2C_ADDR, MCP23017_PORTB, DO_PP_OUT_5_ENABLE, TRUE);
             }
            else if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_OFF_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(IO_EXP4_I2C_ADDR, MCP23017_PORTB, DO_PP_OUT_5_ENABLE, FALSE);
             }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
        
        case CAN_eCB_REQUEST:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_eCB_REQUEST))
            {
                // CAN Request OK:
 
                // Read pin value
                pinValue = MCP23017_Interf.ReadPin(IO_EXP4_I2C_ADDR, MCP23017_PORTB, DO_PP_OUT_5_ENABLE);
                if(pinValue == TRUE)
                {
                    txBuff[BYTE0] = CAN_ON_CMD;       //  PP_OUT value (ON or OFF)
                }
                else
                {
                    txBuff[BYTE0] = CAN_OFF_CMD;      // PP_OUT value (ON or OFF)
                }
                
                // Read eCB Fault pin: PP_OUT fault (0 = OK or 1 = FAULT)
                txBuff[BYTE1] = MCP23017_Interf.ReadPin(IO_EXP4_I2C_ADDR, MCP23017_PORTB, DI_PP_OUT_5_FAULT);

                // Read eCB Current
                readValue = ADCManager_Interf.GetI_eCB100A();
                txBuff[BYTE2] = (uint8)(readValue & 0x00FF);       // PP_OUT current value
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
    }
    CAN_RMP_Send(txMsgID, CAN_DLC_DEFAULT, txBuff);
}

/**
  * @brief  This function performs the response to eCB6 1,5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB6Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP1_I2C_ADDR;
    var.writePort                = MCP23017_PORTA;
    var.writePin                 = DO_PP_OUT_6_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP0_I2C_ADDR ;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_6_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP4_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_6_SENSE;
    var.readCurrentGain          = CAN_eCB_1A5_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB7 1,5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB7Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP2_I2C_ADDR;
    var.writePort                = MCP23017_PORTB;
    var.writePin                 = DO_PP_OUT_7_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP3_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_7_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP6_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_7_SENSE;
    var.readCurrentGain          = CAN_eCB_1A5_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB8 1,5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB8Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP1_I2C_ADDR;
    var.writePort                = MCP23017_PORTA;
    var.writePin                 = DO_PP_OUT_8_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP0_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_8_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP3_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_8_SENSE;
    var.readCurrentGain          = CAN_eCB_1A5_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB9 1,5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB9Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP2_I2C_ADDR;
    var.writePort                = MCP23017_PORTA;
    var.writePin                 = DO_PP_OUT_9_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP2_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_9_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP5_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_9_SENSE;
    var.readCurrentGain          = CAN_eCB_1A5_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB10 1,5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB10Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP1_I2C_ADDR;
    var.writePort                = MCP23017_PORTA;
    var.writePin                 = DO_PP_OUT_10_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP0_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_10_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP4_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_10_SENSE;
    var.readCurrentGain          = CAN_eCB_1A5_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB11 2A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB11Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP2_I2C_ADDR;
    var.writePort                = MCP23017_PORTA;
    var.writePin                 = DO_PP_OUT_11_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP3_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_11_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP6_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_11_SENSE;
    var.readCurrentGain          = CAN_eCB_2A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB12 3A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB12Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP2_I2C_ADDR;
    var.writePort                = MCP23017_PORTB;
    var.writePin                 = DO_PP_OUT_12_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP3_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_12_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP5_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_12_SENSE;
    var.readCurrentGain          = CAN_eCB_3A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB13 5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB13Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP1_I2C_ADDR;
    var.writePort                = MCP23017_PORTB;
    var.writePin                 = DO_PP_OUT_13_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP0_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_13_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP3_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_13_SENSE;
    var.readCurrentGain          = CAN_eCB_5A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB14 5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB14Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP1_I2C_ADDR;
    var.writePort                = MCP23017_PORTB;
    var.writePin                 = DO_PP_OUT_14_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP0_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_14_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP3_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_14_SENSE;
    var.readCurrentGain          = CAN_eCB_5A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB15 5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB15Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP1_I2C_ADDR;
    var.writePort                = MCP23017_PORTB;
    var.writePin                 = DO_PP_OUT_15_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP0_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_15_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP4_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_15_SENSE;
    var.readCurrentGain          = CAN_eCB_5A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB16 5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB16Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP1_I2C_ADDR;
    var.writePort                = MCP23017_PORTA;
    var.writePin                 = DO_PP_OUT_16_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP0_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_16_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP4_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_16_SENSE;
    var.readCurrentGain          = CAN_eCB_5A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB17 1A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB17 has PWM
  */
static void eCB17Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_17_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP1_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_17_SENSE;
    var.readCurrentGain          = CAN_eCB_1A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_17;
    var.ptrPWMValue              = &pwmValue.PP_OUT_17;
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB18 1A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB18 has PWM
  */
static void eCB18Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_18_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP2_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_18_SENSE;
    var.readCurrentGain          = CAN_eCB_1A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_18;
    var.ptrPWMValue              = &pwmValue.PP_OUT_18;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB19 1A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB19 has PWM
  */
static void eCB19Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_19_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP2_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_19_SENSE;
    var.readCurrentGain          = CAN_eCB_1A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_19;
    var.ptrPWMValue              = &pwmValue.PP_OUT_19;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB20 1A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB20 has PWM
  */
static void eCB20Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_20_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP1_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_20_SENSE;
    var.readCurrentGain          = CAN_eCB_1A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_20;
    var.ptrPWMValue              = &pwmValue.PP_OUT_20;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB21 1A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB21 has PWM
  */
static void eCB21Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_21_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP1_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_21_SENSE;
    var.readCurrentGain          = CAN_eCB_1A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_21;
    var.ptrPWMValue              = &pwmValue.PP_OUT_21;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB22 1A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB22 has PWM
  */
static void eCB22Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP0_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_22_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP1_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_22_SENSE;
    var.readCurrentGain          = CAN_eCB_1A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_22;
    var.ptrPWMValue              = &pwmValue.PP_OUT_22;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB23 1A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB23 has PWM
  */
static void eCB23Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_23_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP2_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_23_SENSE;
    var.readCurrentGain          = CAN_eCB_1A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_23;
    var.ptrPWMValue              = &pwmValue.PP_OUT_23;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB24 1A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB24 has PWM
  */
static void eCB24Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_24_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP2_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_24_SENSE;
    var.readCurrentGain          = CAN_eCB_1A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_24;
    var.ptrPWMValue              = &pwmValue.PP_OUT_24;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB25 1A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB25 has PWM
  */
static void eCB25Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_25_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP1_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_25_SENSE;
    var.readCurrentGain          = CAN_eCB_1A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_25;
    var.ptrPWMValue              = &pwmValue.PP_OUT_25;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB26 1A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB26 has PWM
  */
static void eCB26Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_26_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP2_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_26_SENSE;
    var.readCurrentGain          = CAN_eCB_1A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_26;
    var.ptrPWMValue              = &pwmValue.PP_OUT_26;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var); 
}

/**
  * @brief  This function performs the response to eCB27 2A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB27 has PWM
  */
static void eCB27Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_27_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP2_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_27_SENSE;
    var.readCurrentGain          = CAN_eCB_2A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_27;
    var.ptrPWMValue              = &pwmValue.PP_OUT_27;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB28 2A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB28 has PWM
  */
static void eCB28Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_28_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP2_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_28_SENSE;
    var.readCurrentGain          = CAN_eCB_2A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_28;
    var.ptrPWMValue              = &pwmValue.PP_OUT_28;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB29 2A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB29 has PWM
  */
static void eCB29Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_29_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP1_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_29_SENSE;
    var.readCurrentGain          = CAN_eCB_2A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_29;
    var.ptrPWMValue              = &pwmValue.PP_OUT_29;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB30 2A Command and Request
  *
  * @param  None
  * @retval None
  * @note	eCB30 has PWM
  */
static void eCB30Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = 0;
    var.writePort                = 0;
    var.writePin                 = 0;
    
    var.readFaultI2CDeviceAddr   = IO_EXP4_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_30_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP1_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_30_SENSE;
    var.readCurrentGain          = CAN_eCB_2A_GAIN;
    
    var.PWMI2CDeviceAddr         = IO_EXP_PWM_I2C_ADDR;
    var.PWMChannel               = DO_PWM_PP_OUT_30;
    var.ptrPWMValue              = &pwmValue.PP_OUT_30;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB31 5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB31Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP1_I2C_ADDR;
    var.writePort                = MCP23017_PORTA;
    var.writePin                 = DO_PP_OUT_31_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP0_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_31_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP3_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_31_SENSE;
    var.readCurrentGain          = CAN_eCB_5A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB32 5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB32Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP2_I2C_ADDR;
    var.writePort                = MCP23017_PORTB;
    var.writePin                 = DO_PP_OUT_32_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP3_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_32_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP5_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_32_SENSE;
    var.readCurrentGain          = CAN_eCB_5A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB33 5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB33Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP2_I2C_ADDR;
    var.writePort                = MCP23017_PORTB;
    var.writePin                 = DO_PP_OUT_33_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP3_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_33_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP5_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_33_SENSE;
    var.readCurrentGain          = CAN_eCB_5A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB34 5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB34Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP2_I2C_ADDR;
    var.writePort                = MCP23017_PORTA;
    var.writePin                 = DO_PP_OUT_34_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP3_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_34_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP6_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_34_SENSE;
    var.readCurrentGain          = CAN_eCB_5A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB35 5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB35Handler(uint32 msgID, uint32 length, uint8 *payload)
{
        eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP2_I2C_ADDR;
    var.writePort                = MCP23017_PORTA;
    var.writePin                 = DO_PP_OUT_35_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP3_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTB;
    var.readFaultPin             = DI_PP_OUT_35_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP6_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_35_SENSE;
    var.readCurrentGain          = CAN_eCB_5A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
}

/**
  * @brief  This function performs the response to eCB36 5A Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void eCB36Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    eCB_CONTEXT_TYPE var;
    
    var.writeI2CDeviceAddr       = IO_EXP2_I2C_ADDR;
    var.writePort                = MCP23017_PORTB;
    var.writePin                 = DO_PP_OUT_36_ENABLE;
    
    var.readFaultI2CDeviceAddr   = IO_EXP3_I2C_ADDR;
    var.readFaultPort            = MCP23017_PORTA;
    var.readFaultPin             = DI_PP_OUT_36_FAULT;
    
    var.readCurrentI2CDeviceAddr = ADC_EXP5_I2C_ADDR;
    var.readCurrentChannel       = AIN_PP_OUT_36_SENSE;
    var.readCurrentGain          = CAN_eCB_5A_GAIN;
    
    var.PWMI2CDeviceAddr         = 0;
    var.PWMChannel               = 0;
    var.ptrPWMValue              = NULL;       
   
    CAN_RMP_eCBBodyHandler(msgID, length, payload, var);
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
    uint8 txBuff[CAN_MAX_PAYLOAD];
    uint8 k;
    uint32 txMsgID;
    
    txMsgID = (msgID & CAN_OPERATIONS_MASK) | CAN_ANSWER<<4;
    
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
    
    if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_PGD_RQST))
    {
         // CAN Request OK:
        txBuff[BYTE0]  =  MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTA, DI_PGD_IN_1_STATUS);
        txBuff[BYTE0] |= (MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTB, DI_PGD_IN_2_STATUS) << 1);
        txBuff[BYTE0] |= (MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTA, DI_PGD_IN_3_STATUS) << 2);
        txBuff[BYTE0] |= (MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTB, DI_PGD_IN_4_STATUS) << 3);
        txBuff[BYTE0] |= (MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTA, DI_PGD_IN_5_STATUS) << 4);
        txBuff[BYTE0] |= (MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTB, DI_PGD_IN_6_STATUS) << 5);
        txBuff[BYTE0] |= (MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTB, DI_PGD_IN_7_STATUS) << 6);
        txBuff[BYTE0] |= (MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTA, DI_PGD_IN_8_STATUS) << 7);
    }
    else
    {
        txBuff[BYTE0] = CAN_ERROR_ANSWER;
    }
    CAN_RMP_Send(txMsgID, CAN_DLC_DEFAULT, txBuff);
}

/**
  * @brief  This function performs the response to PDG_OUT1 PWM Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void PgdOut1Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    uint8  txBuff[CAN_MAX_PAYLOAD];
    uint8  k;
    uint32 txMsgID;
    CAN_PGD_PARAMETERS_TYPE selectedAction;
    
    txMsgID = (msgID & CAN_OPERATIONS_MASK) | CAN_ANSWER<<4;
     
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
      
    selectedAction = msgID & 0x0000000F;
    
    switch(selectedAction)
    {
        default:
        case CAN_PGD_OUT_NORMAL_CMD:
             txBuff[BYTE0] = CAN_ERROR_ANSWER;
        break;
        
        case CAN_PGD_OUT_PWM_CMD:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] <= CAN_MAX_DUTY_CYCLE))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                
                // Set Duty Cycle value
                // TODO: chiamare funzione per impostare Duty Cycle su PDG_OUT1 --> DO_PGD_OUT1_SetHigh();
                pwmValue.PDG_OUT_1 = payload[BYTE0];
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
        
        case CAN_PGD_RQST:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_PGD_RQST))
            {
                // CAN Request OK: Read Duty Cycle value
                txBuff[BYTE0] = pwmValue.PDG_OUT_1;        
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
    }
    CAN_RMP_Send(txMsgID, CAN_DLC_DEFAULT, txBuff);
}

/**
  * @brief  This function performs the response to PDG_OUT2 PWM Command and Request
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void PgdOut2Handler(uint32 msgID, uint32 length, uint8 *payload)
{
    uint8  txBuff[CAN_MAX_PAYLOAD];
    uint8  k;
    uint32 txMsgID;
    CAN_PGD_PARAMETERS_TYPE selectedAction;
    
    txMsgID = (msgID & CAN_OPERATIONS_MASK) | CAN_ANSWER<<4;
     
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
      
    selectedAction = msgID & 0x0000000F;
    
    switch(selectedAction)
    {
        default:
        case CAN_PGD_OUT_NORMAL_CMD:
             txBuff[BYTE0] = CAN_ERROR_ANSWER;
        break;
        
        case CAN_PGD_OUT_PWM_CMD:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] <= CAN_MAX_DUTY_CYCLE))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                
                // Set Duty Cycle value
                // TODO: chiamare funzione per impostare Duty Cycle su PDG_OUT2 --> DO_PGD_OUT2_SetHigh();
                pwmValue.PDG_OUT_2 = payload[BYTE0];
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
        
        case CAN_PGD_RQST:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_PGD_RQST))
            {
                // CAN Request OK: Read Duty Cycle value
                txBuff[BYTE0] = pwmValue.PDG_OUT_2;        
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
    }
    CAN_RMP_Send(txMsgID, CAN_DLC_DEFAULT, txBuff);
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
    uint8  txBuff[CAN_MAX_PAYLOAD];
    bool   pinValue;
    uint8  k;
    uint32 txMsgID;
    CAN_eCB_PARAMETERS_TYPE selectedAction;
    
    txMsgID = (msgID & CAN_OPERATIONS_MASK) | CAN_ANSWER<<4;
     
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
      
    selectedAction = msgID & 0x0000000F;
    
    switch(selectedAction)
    {
        default:
        case CAN_PGD_OUT_PWM_CMD: 
            txBuff[BYTE0] = CAN_ERROR_ANSWER;
        break;
        
        case CAN_PGD_OUT_NORMAL_CMD:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_ON_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(IO_EXP5_I2C_ADDR, MCP23017_PORTB, DO_PGD_OUT_3_ENABLE, TRUE);
            }
            else if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_OFF_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(IO_EXP5_I2C_ADDR, MCP23017_PORTB, DO_PGD_OUT_3_ENABLE, FALSE);
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
        
        case CAN_PGD_RQST:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_PGD_RQST))
            {
                // CAN Request OK: Read pin value
                pinValue = MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTB, DO_PGD_OUT_3_ENABLE);
                if(pinValue == TRUE)
                {
                    txBuff[BYTE0] = CAN_ON_CMD;       //  PGD_OUT value (ON or OFF)
                }
                else
                {
                    txBuff[BYTE0] = CAN_OFF_CMD;      // PGD_OUT value (ON or OFF)
                }
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
    }
    CAN_RMP_Send(txMsgID, CAN_DLC_DEFAULT, txBuff);
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
    uint8  txBuff[CAN_MAX_PAYLOAD];
    bool   pinValue;
    uint8  k;
    uint32 txMsgID;
    CAN_eCB_PARAMETERS_TYPE selectedAction;
    
    txMsgID = (msgID & CAN_OPERATIONS_MASK) | CAN_ANSWER<<4;
     
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
      
    selectedAction = msgID & 0x0000000F;
    
    switch(selectedAction)
    {
        default:
        case CAN_PGD_OUT_PWM_CMD: 
            txBuff[BYTE0] = CAN_ERROR_ANSWER;
        break;
        
        case CAN_PGD_OUT_NORMAL_CMD:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_ON_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(IO_EXP5_I2C_ADDR, MCP23017_PORTB, DO_PGD_OUT_4_ENABLE, TRUE);
            }
            else if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_OFF_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(IO_EXP5_I2C_ADDR, MCP23017_PORTB, DO_PGD_OUT_4_ENABLE, FALSE);
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
        
        case CAN_PGD_RQST:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_PGD_RQST))
            {
                // CAN Request OK:
 
                // Read pin value
                pinValue = MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTB, DO_PGD_OUT_4_ENABLE);
                if(pinValue == TRUE)
                {
                    txBuff[BYTE0] = CAN_ON_CMD;       //  PGD_OUT value (ON or OFF)
                }
                else
                {
                    txBuff[BYTE0] = CAN_OFF_CMD;      // PGD_OUT value (ON or OFF)
                }
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
    }
    CAN_RMP_Send(txMsgID, CAN_DLC_DEFAULT, txBuff);
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
    uint8  txBuff[CAN_MAX_PAYLOAD];
    uint8  k;
    uint32 txMsgID;
    sint16 tempVar;
    
    txMsgID = (msgID & CAN_OPERATIONS_MASK) | CAN_ANSWER<<4;
    
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
    
    if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == (0x00 | CAN_TEMP_RQST)))
    {
        // CAN Request OK:
        tempVar = ADCManager_Interf.GetT_LOGICBoard();
        txBuff[BYTE0] = HIBYTE_WORD(tempVar);
        txBuff[BYTE1] = LOBYTE_WORD(tempVar);
        tempVar = ADCManager_Interf.GetT_PWRBoard();
        txBuff[BYTE2] = HIBYTE_WORD(tempVar);
        txBuff[BYTE3] = LOBYTE_WORD(tempVar);
    }
    else
    {
        for(k=0; k < CAN_MAX_PAYLOAD; k++)
        {
            txBuff[k] = CAN_ERROR_ANSWER;
        }
    }
    CAN_RMP_Send(txMsgID, CAN_DLC_DEFAULT, txBuff);
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
    uint8  txBuff[CAN_MAX_PAYLOAD];
    uint8  k;
    uint32 txMsgID;
    
    txMsgID = (msgID & CAN_OPERATIONS_MASK) | CAN_ANSWER<<4;
    
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
    
    if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == (0x00 | CAN_eCB_RESET)))
    {
        // CAN Command OK:
        RESET_TEST_Interf.ResetCmd();
        txBuff[0] = 0x00 | CAN_eCB_RESET;
    }
    else
    {
        for(k=0; k < CAN_MAX_PAYLOAD; k++)
        {
            txBuff[k] = CAN_ERROR_ANSWER;
        }
    }
    CAN_RMP_Send(txMsgID, CAN_DLC_DEFAULT, txBuff);
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
    uint8  txBuff[CAN_MAX_PAYLOAD];
    uint8  k;
    uint32 txMsgID;
    
    txMsgID = (msgID & CAN_OPERATIONS_MASK) | CAN_ANSWER<<4;
    
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
    
    if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == (0x00 | CAN_eCB_SELFTEST)))
    {
        // CAN Command OK:
        RESET_TEST_Interf.SelfTestCmd();
        txBuff[0] = 0x00 | CAN_eCB_SELFTEST;
    }
    else
    {
        for(k=0; k < CAN_MAX_PAYLOAD; k++)
        {
            txBuff[k] = CAN_ERROR_ANSWER;
        }
    }
    CAN_RMP_Send(txMsgID, CAN_DLC_DEFAULT, txBuff);
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
    uint8  txBuff[CAN_MAX_PAYLOAD];
    uint16 readValue;
    uint16 readValue1;
    bool   pinValue;
    uint8  k;
    uint32 txMsgID;
    CAN_ORING_PARAMETERS_TYPE selectedAction;
    
    
    txMsgID = (msgID & CAN_OPERATIONS_MASK) | CAN_ANSWER<<4;
     
    for(k=0; k < CAN_MAX_PAYLOAD; k++)
    {
        txBuff[k] = 0;
    }
    
    selectedAction = msgID & 0x0000000F;
    
    switch(selectedAction)
    {
        default:
            txBuff[BYTE0] = CAN_ERROR_ANSWER;
        break;
        
        case CAN_ORING_GPU_EN:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_ON_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(IO_EXP5_I2C_ADDR, MCP23017_PORTA, DO_ORING_GPU_ENABLE, TRUE);
            }
            else if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_OFF_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(IO_EXP5_I2C_ADDR, MCP23017_PORTA, DO_ORING_GPU_ENABLE, FALSE);
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
         
        case CAN_ORING_BATT_EN:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_ON_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(IO_EXP5_I2C_ADDR, MCP23017_PORTA, DO_ORING_BATT_ENABLE, TRUE);
            }
            else if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_OFF_CMD))
            {
                // CAN Command OK:
                txBuff[BYTE0] = payload[BYTE0];
                MCP23017_Interf.WritePin(IO_EXP5_I2C_ADDR, MCP23017_PORTA, DO_ORING_BATT_ENABLE, FALSE);
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;

        case CAN_ORING_VOLTAGES_RQST:
        if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_ORING_VOLTAGES_RQST))
            {
                // CAN Request OK:
                 
                // Read Battery Voltage
                readValue = ADCManager_Interf.GetV_Battery();
                txBuff[BYTE0] = HIBYTE_WORD(readValue);     // MSB Battery Voltage value
                txBuff[BYTE1] = LOBYTE_WORD(readValue);     // LSB Battery Voltage value
                
                // Read Bus Voltage
                readValue = ADCManager_Interf.GetV_PWR1();
                txBuff[BYTE2] = HIBYTE_WORD(readValue);     // MSB Bus Voltage value
                txBuff[BYTE3] = LOBYTE_WORD(readValue);     // LSB Bus Voltage value
                
                // Read Battery Voltage
                readValue = ADCManager_Interf.GetV_GPU();
                txBuff[BYTE4] = HIBYTE_WORD(readValue);     // MSB GPU Voltage value
                txBuff[BYTE5] = LOBYTE_WORD(readValue);     // LSB GPU Voltage value
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
            
        case CAN_ORING_BUS_CURRENT_RQST:
        if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_ORING_BUS_CURRENT_RQST))
            {
                // CAN Request OK:
                 
                // Read Bus Current
                readValue  = ADCManager_Interf.GetI_PWR1();
                readValue1 = ADCManager_Interf.GetI_PWR2();
                txBuff[BYTE0] = HIBYTE_WORD(readValue + readValue1);     // MSB Bus Current value
                txBuff[BYTE1] = LOBYTE_WORD(readValue + readValue1);     // LSB Bus Current value
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
        break;
            
        case CAN_ORING_ENABLE_STATUS_RQST:
            if((length == CAN_DLC_DEFAULT) && (payload[BYTE0] == CAN_ORING_ENABLE_STATUS_RQST))
            {
                // CAN Request OK:
                 
                // Read GPU_ENABLE Pin
                pinValue = MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTA, DO_ORING_GPU_ENABLE);
                if(pinValue == TRUE)
                {
                    txBuff[BYTE0] = CAN_ON_CMD;       // GPU_ENABLE value (ON or OFF)
                }
                else
                {
                    txBuff[BYTE0] = CAN_OFF_CMD;      // GPU_ENABLE value (ON or OFF)
                }
                
                // Read GPU_EN_FEEDBACK Pin
                pinValue = MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTA, DI_ORING_GPU_EN_FEEDBACK);
                if(pinValue == TRUE)
                {
                    txBuff[BYTE1] = CAN_ON_CMD;       // GPU_EN_FEEDBACK value (ON or OFF)
                }
                else
                {
                    txBuff[BYTE1] = CAN_OFF_CMD;      // GPU_EN_FEEDBACK value (ON or OFF)
                }
                
                // Read BATT_ENABLE Pin
                pinValue = MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTA, DO_ORING_BATT_ENABLE);
                if(pinValue == TRUE)
                {
                    txBuff[BYTE2] = CAN_ON_CMD;       // BATT_ENABLE value (ON or OFF)
                }
                else
                {
                    txBuff[BYTE2] = CAN_OFF_CMD;      // BATT_ENABLE value (ON or OFF)
                }
                
                // Read BATT_FEEDBACK Pin
                pinValue = MCP23017_Interf.ReadPin(IO_EXP5_I2C_ADDR, MCP23017_PORTB, DI_ORING_BATT_EN_FEEDBACK);
                if(pinValue == TRUE)
                {
                    txBuff[BYTE3] = CAN_ON_CMD;       // BATT_FEEDBACK value (ON or OFF)
                }
                else
                {
                    txBuff[BYTE3] = CAN_OFF_CMD;      // BATT_FEEDBACK value (ON or OFF)
                }
            }
            else
            {
                txBuff[BYTE0] = CAN_ERROR_ANSWER;
            }
            
        break;
    }
    CAN_RMP_Send(txMsgID, CAN_DLC_DEFAULT, txBuff);
}

/**
  * @brief  This function performs the response to Change LMU Unit Number
  *
  * @param  None
  * @retval None
  * @note	None
  */
static void LMUSettingsHandler(uint32 msgID, uint32 length, uint8 *payload)
{
    
}