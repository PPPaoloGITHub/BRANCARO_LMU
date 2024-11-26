/**
 *  @file		Timers_prm.h
 *  @brief      Parameter file to configure all timers
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __TIMERS_PRM_H__
#define __TIMERS_PRM_H__

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================

/**
 * Insert here project Enable and Disable interrupt macros.
 *
 */
#ifndef INTERRUPTS_ON_DEF
	#define INTERRUPTS_ON_DEF()		{} //{__EI();}
#endif

#ifndef INTERRUPTS_OFF_DEF
	#define INTERRUPTS_OFF_DEF()	{} //{__DI();}
#endif

/**
 * Init state for counters and timers.
 *
 * This is used to set the state of the timers and counters when the TIMERS_Init() function is called.
 */
#define TIMERS_INIT_STATE INCOMPLETE
#define COUNTERS_INIT_STATE COUNTERS_IDLE

/* *************** */
/**
 * MILLISECOND TIMER
 */

/**
 * MILLISECOND TIMER LIST
 *
 * To add MS Timers, just add timer names to the list. (up to 255 timers).
 * MAKE SURE you adjust the #define MS_NUM to the appropriated number of
 * items in MS_TIMER_LABEL list.
 */
typedef enum
{
	//Add MsTimers here
	MS_TIMER_GREEN_LED_PULSE				= 0,
    MS_TIMER_CAN_HEARTBEAT_PERIOD           = 1,
    MS_TIMER_CANFBK_PERIOD                  = 2,
    MS_TIMER_HW_HEARBEAT                    = 3,
    MS_TIMER_RESET_CMD                      = 4,
    MS_TIMER_SELF_TEST_CMD                  = 5,
            
	//MS_TIMER_NAME1,		//Add here new hms_timers labels

	//MS_NUM    It was moved to a #define
} MS_TIMER_LABEL;

/**
 * Number of MS Timers
 * \ MAKE SURE you adjust the #define MS_NUM to the appropriated number of items in MS_TIMER_LABEL list.
 *
 */
#define MS_NUM 6

/**
 * MILLISECOND TIMER TICK RESOLUTION
 *
 * Resolution of MillisecondTimer service calls (in ms)
 * Recommended values: 1, 5, 20, 25, 50, or 100
 * This is how often the MsTimers service routine will be called.
 * @note i.e. if MS_TICK is 20, the TIMERS_MsService() routine should be called every 20 ms.
 * if the timers are to based off of zero-cross, the user
 * configures the timer for MS_TICK=50 (3*16.67 = 50). Thus, the
 * timer service routine would be called every 3 line cycles.
 */
#define MS_TICK 1

/* *************** */
/**
 * SECONDS_TIMERS
 *
 */

/**
 * SECONDS TIMER LIST
 *
 * To add Seconds Timers, add timer names to the list. (up to 255 timers).
 *
 * @note MAKE SURE you adjust the #define SECONDS_NUM to the appropriated number of
 * items in SECONDS_LABEL list.
 *
 */
typedef enum
{
	//Add Second Timers here
	SECONDS_TIMER_TEST					= 0,
	//SECONDS_TIMER_NAME1					= 1			//Add here new seconds_timers labels
	//SECONDS_NUM    It was moved to a #define
} SECONDS_LABEL;

/**
 * Number of Seconds Timers
 *
 * @note MAKE SURE you adjust the #define SECONDS_NUM to the appropriated number of items in SECONDS_LABEL list.
 *
 */
#define SECONDS_NUM 1

/**
 * SECONDS TIMER TICK RESOLUTION
 *
 * Resolution of SecondsTimer service calls (in ms)
 * This is how often the SecondsTimers service routine will be called.
 *
 * @note i.e. if SECONDS_TICK is 25, the ServiceSeconds() routine should be called every 25 ms. If it's called every second then set to 1000
 */

#define SECONDS_TICK 100

/* *************** */
/**
 * MINUTES_TIMERS
 *
 */

/**
 * MINUTES TIMER LIST
 *
 * To add Minutes Timers, add timer names to the list. (up to 255 timers).
 * MAKE SURE you adjust the #define MINUTES_NUM to the appropriated number of
 * items in MINUTES_LABEL list.
 */
typedef enum
{
	//Add Minutes Timers here
	MINUTES_TIMER_TEST					= 0,
	//MINUTES_TIMER_NAME1				= 1			//Add here new minutes_timers labels
	//MINUTES_NUM    It was moved to a #define
} MINUTES_LABEL;

/**
 * Number of Minutes Timers
 * @note MAKE SURE you adjust the #define MINUTES_NUM to the appropriated number of items in MINUTES_LABEL list.
 *
 */
#define MINUTES_NUM 1

/**
 * MINUTES TIMER TICK RESOLUTION
 *
 * Resolution of Minutes Timer service calls (in ms)
 * This is how often the SecondsTimers service routine will be called.
 *
 * i.e. if MINTUES_TICK is 25, the ServiceMinutes() routine should be called every 25 ms. If it's called every second then set to 1000
 */
#define MINUTES_TICK 1000

/* *************** */
/**
 * HMS_TIMERS
 *
 */

/**
 * HMS TIMER LIST
 *
 * To add hms_timers, just add timer names to the list. (up to 255 timers).
 * To eliminate the HMSTimer from compiling, remove all items
 * from the list.
 *
 * @note MAKE SURE you adjust the #define HMS_NUM to the appropriated number of items in HMS_TIMER_LABEL list.
 */
typedef enum
{
	//Add HMSTimers here
	TIMER_HMS_TEST = 0
	//TIMER_HMS_TIMER_NAME1 = 1,	//Add here new hms_timers labels
	//TIMER_HMS_TIMER_NAME2 = 2,
	
	//HMS_NUM    It was moved to a #define
} HMS_TIMER_LABEL;

/**
 * Number of HMS timers
 * MAKE SURE you adjust the #define HMS_NUM to the appropriated number of items in HMS_TIMER_LABEL list.
 */
#define HMS_NUM 1

/**
 * HMS TIMER TICK RESOLUTION
 *
 * Resolution of HMSTimer service calls (in ms)
 * Recommended values: 1, 5, 20, 25, 50, 100, or 1000
 * This is how often the HMSTimers service routine will be called.
 * i.e. if HMS_TICK is 20, the TIMERS_HMSService() routine should
 * be called every 20 ms.
 * i.e if the timers are to based off of zero-cross, the user configure the timer for MS_TICK=50(3*16.67 = 50). Thus.
 * the timer service routine would be every 3 cycles.
 */
#define HMS_TICK 100

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

/*
 * place in this define the functions that must be called in the service
 * function for hard timed purpose
 */
#define TIMERS_TICK_FUNCTIONS() {};
#endif // __TIMERS_PRM_H__
