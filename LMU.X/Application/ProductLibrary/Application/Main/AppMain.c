/**
 *  @file       Main.c
 *  @brief      main() routine and primary timer ISR routine.
 *
 *  @details    This module contains the main() routine and the main interrupt service routine.
 *              The main() routine is the program's entry point.  The main interrupt service routine
 *              manages the timing for the application.
 *
 *              This module has been constructed similar to a GDM (Global Design Module). So the only
 *              required changes are to the main_prv_prm.h file.  Both main.c and main.h are not
 *              intended to be changed when used in a different application.
 *
 *              There are a series of constant arrays that are lists of routines to call at certain
 *              points in the execution of the main loop and the main interrupt service routine.
 *              Each array is described in the comments associated with that array.
 *              They are summarized here:
 *
 *              <pre>
 *              Function List               Purpose
 *              -----------------------     --------------------------------------------------------
 *              Initialization_Tasks        NULL terminated list of tasks to execute before entering
 *                                          the infinite loop.
 *              -----------------------     --------------------------------------------------------
 *              Every_Loop_Tasks            NULL terminated list of tasks to execute every pass of
 *                                          the main loop.
 *              -----------------------     --------------------------------------------------------
 *              Every_Slot_Tasks            NULL terminated list of tasks to execute at the
 *                                          beginning of every slot.
 *              -----------------------     --------------------------------------------------------
 *              Main_Slot{n}_Tasks          NULL terminated list of tasks to execute during slot(n)
 *                                          of the main routine.
 *              -----------------------     --------------------------------------------------------
 *              Main_Tasks                  Array made up of the Main_Slot{n}_Tasks[] arrays.
 *                                          Determines the sequence of slots and the number of slots.
 *              -----------------------     --------------------------------------------------------
 *              Every_Interrupt_Tasks       NULL terminated list of tasks to execute at the start of
 *                                          every main interrupt.
 *              -----------------------     --------------------------------------------------------
 *              Interrupt_Slot(n)_Tasks     NULL terminated list of tasks to execute during slot(n)
 *                                          of the main interrupt service routine.
 *              -----------------------     --------------------------------------------------------
 *              Interrupt_Tasks             Array made up of the Interrupt_Slot(n)_Tasks[] arrays.
 *                                          Determines the sequence of slots and the number of slots.
 *              -----------------------     --------------------------------------------------------
 *              </pre>
 *
 *              When configuring this module for a new application, the programmer should create a
 *              Main_Slot(n)_Tasks[] array for each of the slots desired in the main loop.  Also,
 *              create an Interrupt_Slot(n)_Tasks[] array for each of the slots desired in the main
 *              interrupt service routine.  The programmer should set the SLOT_TIME equal to the
 *              number of interrupts that make up a single slot.
 *
 *              TODO: Add text to describe the purpose of the associated Mcu module.
 *              The programmer should also define
 *              the MCU__RESETSTACKPOINTER() macro in the mcu module to reset the stack pointer back
 *              to the empty stack position.
 *
 *  $Header: ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//-------------------------------------- Include Files ----------------------------------------------------------------

#include "../../ProductLibraryInclude/AppMain.h"
#include "../../ProductLibraryInclude/Compiler_defs.h"

//A constant pointer to a function with no return value or parameters.
typedef void (* const TASK_TYPE)(void);

//A constant pointer to a list of TASK_TYPESs.
typedef void (* const * const TASK_LIST_TYPE)(void);

//A NULL pointer to use as a terminator for function lists.
#define NULL_TASK ((TASK_TYPE)0)

#include "../../ProductLibraryInclude/AppMain_prm.h"

#ifndef MAIN_LOW_POWER_FEATURE
    #define MAIN_LOW_POWER_FEATURE DISABLED
#endif

#if (MAIN_LOW_POWER_FEATURE == ENABLED)
    //#include "PowerMgr.h"
#endif
//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
//  --- Constants
#if (MAIN_LOW_POWER_FEATURE == ENABLED)
    typedef enum
    {
        MAIN_STATE_NORMAL_POWER,
        MAIN_STATE_SWITHCING_TO_LOW_POWER,
        MAIN_STATE_LOW_POWER,
        MAIN_STATE_SWITHING_TO_NORMAL_POWER
    } MAIN_POWER_STATE;
#endif

//!Number of slots in the main loop
#define MAIN_SLOT_COUNT (sizeof(Main_Tasks)/sizeof(TASK_LIST_TYPE))

//!Number of slots in the main interrupt
#define INTERRUPT_SLOT_COUNT (sizeof(Interrupt_Tasks)/sizeof(TASK_LIST_TYPE))

/** @brief      Duration of each slot in the main loop.
 *  @details    The number of interrupts per main slot in the gated slotted architecture.
 *              Example: 250 microsecond interrupt rate is 4 interrupts per millisecond.
 *                       For 5 millisecond slots: SLOT_TIME = 5 * 4.
 */
#define SLOT_TIME (INTERRUPTS_PER_MILLISECOND * MILLISECONDS_PER_MAIN_SLOT)

//  --- Variables

#if (MAIN_LOW_POWER_FEATURE == ENABLED)
    MAIN_POWER_STATE Main_Power_State;
#endif
//!Number of the current main loop slot in the main() routine
static unsigned char Main_Slot;

//!Number of the current interrupt slot in the timer interrupt service routine
static unsigned char Interrupt_Slot;

//!Timer to measure a single slot duration
static unsigned char Main_Slot_Timer;

//!Value of Main_Slot_Timer the last time a Slot was executed
static unsigned char Main_Slot_Timer_Diff;

//!Add a routine to perform timing check for 5ms slots
//!This routine will be called after the execution of the code of any 5ms slot.
#ifndef MAIN_SLOT_CHECK
    #define MAIN_SLOT_CHECK(a,b)
#endif

//! Macro for SQC Timer interrupt slot test
#ifndef MAIN_TIMER_ISR_END
    #define MAIN_TIMER_ISR_END(slot)
#endif

//!Add a routine to perform timing check on Main Slots
//!This routine will be called before any instruction with the slot synchronization
#ifndef MAIN_DEBUG_BEFORE_SLOTS
    #define MAIN_DEBUG_BEFORE_SLOTS()
#endif

//!Add a routine to perform timing check on Main Slots
//!This routine will be called after all instructions with the slot synchronization
#ifndef MAIN_DEBUG_AFTER_SLOTS
    #define MAIN_DEBUG_AFTER_SLOTS()
#endif

//!Add a routine to perform timing check on Timer Interruption Slots
//!This routine will be called before any instruction in the Timer Interruption
#ifndef MAIN_DEBUG_BEFORE_INTERRUPT_SLOTS
    #define MAIN_DEBUG_BEFORE_INTERRUPT_SLOTS()
#endif

//!Add a routine to perform timing check on Timer Interruption Slots
//!This routine will be called after all instructions in the Timer Interruption
#ifndef MAIN_DEBUG_AFTER_INTERRUPT_SLOTS
    #define MAIN_DEBUG_AFTER_INTERRUPT_SLOTS()
#endif

#ifndef EXCEPTION_MAIN_SLOT_VIOLATION
    #define EXCEPTION_MAIN_SLOT_VIOLATION(p1,p2)
#endif

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static void ExecuteTasks(TASK_TYPE * task_list);

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      The application's main routine
 *
 *  @details    This routine implements a main loop with a gated slotted architecture.
 *              It can be configured through the parameter files.
 *
 *  @note       If the MAIN_RESETS_STACK_POINTER compiler directive is defined, then all
 *              local variables must be declared as static or they will be placed on the
 *              stack.  Since the main loop resets the stack pointer, the variables will
 *              be lost.
 */
void App__Main(void)
{
    // NOTE: Before adding local variables see note in details above

    #if (MAIN_RESETS_STACK_POINTER == ENABLED)
        // Execute all the time that we are not executing a Slot.
        // Ensure that the stack pointer is correct.
        DISABLE_INTERRUPTS();
        RESET_STACK_POINTER();
        DISABLE_INTERRUPTS();
    #endif
    //--------------------------------------------------------------------------
    //  --- Initialize program

    // Initialize main() routine variables.
    Interrupt_Slot = INTERRUPT_SLOT_COUNT - 1;      // Execute interrupt slot 0 first
    Main_Slot = MAIN_SLOT_COUNT - 1;                // Execute main slot 0 first
    Main_Slot_Timer = SLOT_TIME;                    // Timer for main slots
    Main_Slot_Timer_Diff = 0;                       // Provides mutual exclusion with the timer interrupt


    #if (MAIN_LOW_POWER_FEATURE == ENABLED)
        Main_Power_State = MAIN_STATE_NORMAL_POWER;
        PowerMgr__Initialize();
    #endif

    //Initialize the Micro-controller and application modules
    ExecuteTasks(Initialization_Tasks);

    //--------------------------------------------------------------------------
    //  --- Begin Main (Infinite) Loop

    for (;;)
    {
        #if (MAIN_LOW_POWER_FEATURE == ENABLED)


            switch (Main_Power_State)
            {
                case MAIN_STATE_NORMAL_POWER:
        #endif
                    #if (EXECUTE_EVERY_MAIN_LOOP_TASKS == ENABLED)
                        // Execute tasks that run every main loop
                        ExecuteTasks(Every_Loop_Tasks);
                    #endif

                    // Time Gate for Slotted Architecture
                    // Implementation catches up if it falls behind
                    if ((unsigned char)(Main_Slot_Timer - Main_Slot_Timer_Diff) >= SLOT_TIME)
                    {
                        // '+=' operator used here so that overruns are eventually caught up
                        Main_Slot_Timer_Diff += SLOT_TIME;

                        // Macro for timing analyzes
                        MAIN_DEBUG_BEFORE_SLOTS();

                        // Placement here insures that both the main loop and the main timer interrupt are running.
                        // Ideally, this would be the only call anywhere in the code.
                        //Micro__ServiceWatchdog();	/* TODO: @PP */

                        // Execute tasks that run every slot
                        ExecuteTasks(Every_Slot_Tasks);

                        // Move to the next main loop Slot.  Roll back to zero if necessary.
                        Main_Slot++;
                        if (Main_Slot >= MAIN_SLOT_COUNT)
                        {
                            Main_Slot = 0;
                        }

                        // Execute tasks that only run during a specific slot
                        ExecuteTasks(Main_Tasks[Main_Slot]);

                        // Tests if the Slot Time was respected
                        if ((unsigned char)(Main_Slot_Timer - Main_Slot_Timer_Diff) >= SLOT_TIME)
                        {
                            // Exception: Main Slot Time Violation
                            EXCEPTION_MAIN_SLOT_VIOLATION((Main_Slot_Timer - Main_Slot_Timer_Diff),SLOT_TIME);

                        }

                        MAIN_SLOT_CHECK((Main_Slot_Timer - Main_Slot_Timer_Diff),Main_Slot);

                        // Macro for timing analyzes
                        MAIN_DEBUG_AFTER_SLOTS();

                    }                                           //End 5 millisecond gate
                    else
                    {
                        #if (MAIN_RESETS_STACK_POINTER == ENABLED)
                            //Execute all the time that we are not executing a Slot.
                            //Ensure that the stack pointer is correct.
                            DISABLE_INTERRUPTS();
                            RESET_STACK_POINTER();
                            ENABLE_INTERRUPTS();

                        #endif
                        //The code associated to NOISE_IMMUNITY runs between slots.
                        //Ensure that the code is not too long that could cause problems to the slots.
                        NOISE_IMMUNITY();
                    }
            #if (MAIN_LOW_POWER_FEATURE == ENABLED)
                    if (PowerMgr__GetPowerModeState() == POWERMGR_STATE_LOW_POWER)
                    {
                        Main_Power_State = MAIN_STATE_SWITHCING_TO_LOW_POWER;
                    }
                    break;
                case MAIN_STATE_SWITHCING_TO_LOW_POWER:
                    PowerMgr__SwitchToLowPowerTasks();
                    Main_Power_State = MAIN_STATE_LOW_POWER;
                    break;
                case MAIN_STATE_LOW_POWER:
                    // Placement here insures that both the main loop and the main timer interrupt are running.
                    // Ideally, this would be the only call anywhere in the code.
                    Micro__ServiceWatchdog();


                    // Execute tasks that run every slot
                    ExecuteTasks(LowPower_Tasks);

                    if (PowerMgr__GetPowerModeState() == POWERMGR_STATE_NORMAL_POWER)
                    {
                        Main_Power_State = MAIN_STATE_SWITHING_TO_NORMAL_POWER;
                    }
                    else
                    {
                        PowerMgr__GoSleep();
                    }

                    break;
                case MAIN_STATE_SWITHING_TO_NORMAL_POWER:

                    // Actions to be taken when switching to the Normal Power Mode.
                    // tasks that must be initializes should be included within SRPowerMgr__SwitchToNormalPowerTasks
                    PowerMgr__SwitchToNormalPowerTasks();


                    Main_Slot = 0;

                    Interrupt_Slot = 0;


                    // There's no Break in this state, it falls down to the default case
                default:
                    Main_Power_State = MAIN_STATE_NORMAL_POWER;
                    break;
            }
            #endif
    }                                               //End forever loop
}                                                   //End main


//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Interrupt handler for the timer interrupt.
 *
 *  @details    This routine implements an interrupt service routine with a gated slotted
 *              architecture.  Each interrupt calls the routines for the next interrupt slot.
 *              It can be configured through the parameter files.
 */
void AppMain__TimerISR( void )
{
    //Macro for timing analyzes
    MAIN_DEBUG_BEFORE_INTERRUPT_SLOTS();
    #if (MAIN_LOW_POWER_FEATURE == ENABLED)
        if (Main_Power_State == MAIN_STATE_NORMAL_POWER)
        {
    #endif
            #if (EXECUTE_EVERY_INTERRUPT_TASKS == ENABLED)
                ExecuteTasks(Every_Interrupt_Tasks);
            #endif                                          // EVERY_INTERRUPT_TASKS_ENABLED

            // Move to the next interrupt Slot.  Roll back to zero if necessary.
            Interrupt_Slot++;
            if (Interrupt_Slot >= INTERRUPT_SLOT_COUNT)
            {
                Interrupt_Slot = 0;
            }

            ExecuteTasks(Interrupt_Tasks[Interrupt_Slot]);
            MAIN_TIMER_ISR_END(Interrupt_Slot);

            Main_Slot_Timer++;
    #if (MAIN_LOW_POWER_FEATURE == ENABLED)
        }
    #endif
    //Macro for timing analyzes
    MAIN_DEBUG_AFTER_INTERRUPT_SLOTS();
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief  This method reinitializes all the counters for the slots.
 * @details This method is required to resynchronize the system if it's needed.
 */
void AppMain__TimeSlotInitialize(void)
{
    Interrupt_Slot = INTERRUPT_SLOT_COUNT - 1;      // Execute interrupt slot 0 first
    Main_Slot = MAIN_SLOT_COUNT - 1;                // Execute main slot 0 first
    Main_Slot_Timer = SLOT_TIME;                    // Timer for main slots
    Main_Slot_Timer_Diff = 0;                       // Provides mutual exclusion with the timer interrupt
}

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Execute the list of tasks pointed to by task_list.
 *  @details    This code is approximately a 33% improvement in execution time and a 44%
 *              improvement in code size over a version that uses an index into the task_list
 *              array.  Former code shown here.
 *              <pre>
 *                  void ExecuteTasks(TASK_TYPE task_list[])
 *                  {
 *                      unsigned char task;
 *
 *                      for (task=0; task_list[task] != NULL_TASK; task++)
 *                      {
 *                          task_list[task]();
 *                      }
 *                  }
 *              </pre>
 *
 *  @param      task_list = Null-terminated list of tasks to execute.
 *                          Each task must have the prototype: void Task(void)
 */
static void ExecuteTasks(TASK_TYPE * task_list)
{
    while (*task_list != NULL_TASK)
    {
        (*task_list)();
        task_list++;
    }
}
