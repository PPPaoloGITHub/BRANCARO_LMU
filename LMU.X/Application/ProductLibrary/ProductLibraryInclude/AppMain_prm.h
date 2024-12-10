/**
 *  @file       Main_prm.h
 *  @brief      Parameter file for private components of the main GDM.
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

#ifndef __MAIN_PRM_H__
#define __MAIN_PRM_H__

//-------------------------------------- Include Files ----------------------------------------------------------------
//! Basic
#include "C_Extensions.h"

//! Drivers

//! Others
#include "Timers.h"
#include "LED_OnBoard.h"
#include "HW_HeartBeat.h"
#include "../../AppSpecific/AppSpecificInclude/Version.h"
#include "CANRecvdMsgParser.h"
#include "../../AppSpecific/AppSpecificInclude/CANFeedback.h"
#include "ADCManager.h"
#include "DigitalInput.h"
#include "DigitalOutput.h"
#include "EEPROM24LC512.h"
#include "MCP23017.h"
#include "PCA9685.h"
#include "ADS7128.h"
#include "ResetTest.h"


//--- include APIxxx and APIyyy diagnostic
//#include "APIxxxDebug.h"		/* TODO: @PP */
//#include "APIyyySystem.h"		/* TODO: @PP */



//=====================================================================================================================
//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
//=====================================================================================================================


//  --- Compiler Directives

#define MAIN_LOW_POWER_FEATURE			DISABLED

//! This definition should be set to one of the following:
//!     ENABLED = Reset the stack pointer in noise immunity section of main loop (Preferred)
//!     DISABLED = Do not reset the stack pointer in the main loop.
#define MAIN_RESETS_STACK_POINTER		ENABLED

//! This definition should be set to one of the following:
//!     ENABLED = Execute a set of tasks in every interrupt as a separate group.
//!     DISABLED = Any tasks that must be executed in every interrupt should be included in every
//!                 slot.  This results in less overhead.
#define EXECUTE_EVERY_INTERRUPT_TASKS	ENABLED

//! This definition should be set to one of the following:
//!     ENABLED = Execute a set of tasks in every main loop as a separate group.
//!     DISABLED = There are no tasks executed in every main loop.
#define EXECUTE_EVERY_MAIN_LOOP_TASKS	DISABLED//ENABLED


//  --- Macro Definitions

//! Add a routine to perform noise immunity tasks such as (for example):
//!     Check stack pointer
//!     Enable interrupts
//!     Refresh static registers
//!     Check critical values
//!     Background ROM check
//!     etc.
//!     Caution: Make sure the code added to the NOISE_IMMUNITY() doesn't affect the slot timing control!!
#define NOISE_IMMUNITY()


//! Add a routine to perform timing check on Main Slots
//! This routine will be called before any instruction with the slot synchronization
#define MAIN_DEBUG_BEFORE_SLOTS()      //     { Gpio__PinConfig(PORT4, 6,  OUTPUT_PUSHPULL),  Gpio__PinWrite(PORT4, 6, 1);}

//! Add a routine to perform timing check on Main Slots
//! This routine will be called after all instructions with the slot synchronization
#define MAIN_DEBUG_AFTER_SLOTS()    //  { Gpio__PinConfig(PORT4, 6,  OUTPUT_PUSHPULL),  Gpio__PinWrite(PORT4, 6, 0);}

//! Add a routine to perform timing check on Timer Interruption Slots
//! This routine will be called before any instruction in the Timer Interruption
#define MAIN_DEBUG_BEFORE_INTERRUPT_SLOTS()     // { Gpio__PinConfig(PORT4, 6,  OUTPUT_PUSHPULL),  Gpio__PinWrite(PORT4, 6, 1);}

//! Add a routine to perform timing check on Timer Interruption Slots
//! This routine will be called after all instructions in the Timer Interruption
#define MAIN_DEBUG_AFTER_INTERRUPT_SLOTS()      // { Gpio__PinConfig(PORT4, 6,  OUTPUT_PUSHPULL),  Gpio__PinWrite(PORT4, 6, 0);}


//! Add a routine to perform timing check on Timer Interruption Slots
//! This routine will be called after all instructions in the Timer Interruption
#define EXCEPTION_MAIN_SLOT_VIOLATION(actual,expected)

#if (APIxxxDEBUG_TIMING == ENABLED)

//!Add a routine to perform timing check for 5ms slots
//!This routine will be called after the execution of the code of any 5ms slot.
#define MAIN_SLOT_CHECK(time,slot)      //TimerInterrupt__CaptureMainSlotDuration(time,slot)


//! Macro for SQC Timer interrupt slot test
#define MAIN_TIMER_ISR_END(slot)        //TimerInterrupt__CaptureIntSlotDuration(slot)

#else

//!Add a routine to perform timing check for 5ms slots
//!This routine will be called after the execution of the code of any 5ms slot.
#define MAIN_SLOT_CHECK(time,slot)      //TimerInterrupt__CaptureMainSlotDuration(time,slot)


//! Macro for SQC Timer interrupt slot test
#define MAIN_TIMER_ISR_END(slot)        //TimerInterrupt__CaptureIntSlotDuration(slot)

#endif


//  --- Constants

//! Number of interrupts per millisecond.  This value should be a whole number.
//! Example: If interrupt period is 250 microseconds, then this value should be 4.
#define INTERRUPTS_PER_MILLISECOND 4

//! Number of milliseconds per main slot.  This value should be a whole number.
//! Example: If each main slot takes 5 milliseconds, then this value should be 5.
#define MILLISECONDS_PER_MAIN_SLOT 5


//  --- Variables



/** @brief      List of tasks executed before entering the main loop.
 *  @details    Add pointers to routines that should be called during initialization.  These
 *              routines are intended to initialize or begin the initialization process for all the
 *              modules in the application.
 */
TASK_TYPE Initialization_Tasks[] =
{
    //ModuleName__Initialize,
	TIMERS__Initialize,
	LED_ONB__Initialize,
    HW_HEARTBEAT__Initialize,
    VERSION__Initialize,
    CAN_RMP__Initialize,
    CANFBK__Initialize,
    ADCManager__Initialize,
    EEPROM24LC512__Initialize,
    MCP23017__Initialize,
    PCA9685__Initialize,
    ADS7128__Initialize,
    RESET_TEST__Initialize,
    
    //APIyyySystem__Initialize,
#if (APIxxxDEBUG_TIMING == ENABLED)
    //APIxxxDebug__Initialize,
#endif

    //StackIntegrity__Initialize,

	//Application__Initialize,

	//TimerInterrupt__Initialize,  //it has to be the last one !

    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};

#if (EXECUTE_EVERY_MAIN_LOOP_TASKS == ENABLED)
/** @brief      List of tasks executed at the start of every pass of the main loop.
 *  @details    Add pointers to routines that should run every main loop.
 */
TASK_TYPE Every_Loop_Tasks[] =
{

    //-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};
#endif  // EXECUTE_EVERY_MAIN_LOOP_TASKS

/** @brief      List of tasks executed at the start of every main loop slot.
 *  @details    Add pointers to routines that should be called every main loop slot.
 */
TASK_TYPE Every_Slot_Tasks[] =
{
	//ModuleName__Handler,
    CAN_RMP__Handler5ms,
    CANFBK__Handler5ms,
    MCP23017__Handler5ms,
    ADS7128__Handler5ms,
    
    //Application__Handler5ms,


    //-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};

/** @brief      List of tasks executed in SLOT #0 of the main loop.
 *  @details    Add pointers to routines that should run during this slot in the main loop.
 */
TASK_TYPE Main_Slot0_Tasks[] =
{
	//ModuleName__Handler25ms,
	//StackIntegrity__Handler25ms,
    PCA9685__Handler25ms,


	

	//-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};

/** @brief      List of tasks executed in SLOT #1 of the main loop.
 *  @details    Add pointers to routines that should run during this slot in the main loop.
 */
TASK_TYPE Main_Slot1_Tasks[] =
{
	//ModuleName__Handler25ms,
    //Application__Handler25ms,
	//FBKCAN__FbkCANHandler25ms,

#if (APIxxxDEBUG_TIMING == ENABLED)
    //APIxxxDebug__Handler25ms,
#endif


	//-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};

/** @brief      List of tasks executed in SLOT #2 of the main loop.
 *  @details    Add pointers to routines that should run during this slot in the main loop.
 */
TASK_TYPE Main_Slot2_Tasks[] =
{
	//ModuleName__Handler25ms,
    //APIxxx_Message_Background25ms,
    EEPROM24LC512__Handler25ms,
	
    
    //-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};

/** @brief      List of tasks executed in SLOT #3 of the main loop.
 *  @details    Add pointers to routines that should run during this slot in the main loop.
 */
TASK_TYPE Main_Slot3_Tasks[] =
{
	//ModuleName__Handler25ms,
    //APIxxx_SMU_ACU__BackGround25ms,
    ADCManager__Handler25ms,

	//-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};

/** @brief      List of tasks executed in SLOT #4 of the main loop.
 *  @details    Add pointers to routines that should run during this slot in the main loop.
 */
TASK_TYPE Main_Slot4_Tasks[] =
{
	//ModuleName__Handler25ms,
	LED_ONB__Handler25ms,
    HW_HEARTBEAT__Handler25ms,
    RESET_TEST__Handler25ms,

	//-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};

/** @brief      Collection of arrays of function pointers.  Each element represents a single slot
 *              in the main loop.
 *  @details    Each element of this array represents a slot in the main loop.  Each element is a
 *              list of tasks to execute in the main loop slot.  Add all the arrays of tasks that
 *              make up each slot in the application.  The size of this array determines the number
 *              of slots in the main loop.
 */
TASK_LIST_TYPE Main_Tasks[] =
{
    Main_Slot0_Tasks,
    Main_Slot1_Tasks,
    Main_Slot2_Tasks,
    Main_Slot3_Tasks,
    Main_Slot4_Tasks

    //-------------------------------------------------------------------------
    // Do not place a terminating NULL_TASK in this list.
};

#if (EXECUTE_EVERY_INTERRUPT_TASKS == ENABLED)
/** @brief      List of tasks executed at the start of every timer interrupt.
 *  @details    Add pointers to routines that should run every timer interrupt.
 */
TASK_TYPE Every_Interrupt_Tasks[] =
{
    //NameFunction__FastHandler250us,
	//Lsi__FastHandler,
    

    //-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};
#endif                                              // EXECUTE_EVERY_INTERRUPT_TASKS

/** @brief      List of tasks executed in SLOT #0 of the timer interrupt.
 *  @details    Add pointers to routines that should run during this slot in the timer interrupt.
 *              Tasks that should be executed in every interrupt slot should be included here if
 *              EVERY_INTERRUPT_TASKS_ENABLED is not defined.
 */
TASK_TYPE Interrupt_Slot0_Tasks[] =
{
	//NameFunction__FastHandler1ms,
	TIMERS__MsTick,
	//CAN__TX_Handler1ms,
    
    

    //-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};

/** @brief      List of tasks executed in SLOT #1 of the timer interrupt.
 *  @details    Add pointers to routines that should run during this slot in the timer interrupt.
 *              Tasks that should be executed in every interrupt slot should be included here if
 *              EVERY_INTERRUPT_TASKS_ENABLED is not defined.
 */
TASK_TYPE Interrupt_Slot1_Tasks[] =
{
	//NameFunction__FastHandler1ms,


    //-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};

/** @brief      List of tasks executed in SLOT #2 of the timer interrupt.
 *  @details    Add pointers to routines that should run during this slot in the timer interrupt.
 *              Tasks that should be executed in every interrupt slot should be included here if
 *              EVERY_INTERRUPT_TASKS_ENABLED is not defined.
 */
TASK_TYPE Interrupt_Slot2_Tasks[] =
{
	//NameFunction__FastHandler1ms,
    //CAN__HandlerProtocol,
     

    //-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};

/** @brief      List of tasks executed in SLOT #3 of the timer interrupt.
 *  @details    Add pointers to routines that should run during this slot in the timer interrupt.
 *              Tasks that should be executed in every interrupt slot should be included here if
 *              EVERY_INTERRUPT_TASKS_ENABLED is not defined.
 */
TASK_TYPE Interrupt_Slot3_Tasks[] =
{
	//NameFunction__FastHandler1ms,


	//-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};

/** @brief      Collection of array of function pointers to execute in the interrupt slots.
 *  @details    Each element of this array represents a slot in the interrupt service routine.
 *              Each element is a list of tasks to execute in the interrupt slot.  Add all the
 *              arrays of tasks that make up each slot in the interrupt.  The size of this array
 *              determines the number of slots in the interrupt service routine.
 */
TASK_LIST_TYPE Interrupt_Tasks[] =
{
    Interrupt_Slot0_Tasks,
    Interrupt_Slot1_Tasks,
    Interrupt_Slot2_Tasks,
    Interrupt_Slot3_Tasks

    //-------------------------------------------------------------------------
    // Do not place a terminating NULL_TASK in this list.
};

/** @brief      List of tasks to be execute when in Low Power Mode
 *  @details    Add pointers to routines that should run during this slot in the timer interrupt.
 *
 */
TASK_TYPE LowPower_Tasks[] =
{

    //-------------------------------------------------------------------------
    // Mandatory NULL_TASK must be at the end of the list
    NULL_TASK
};


#endif  // __MAIN_PRV_PRM_H__
