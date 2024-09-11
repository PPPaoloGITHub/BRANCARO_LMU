/**
 *  @file		Timers.c
 *  @brief      Commonly used timers & counters
 *
 *  @details    This GDM (Global Design Module) contains various timers and counters.
 *  			Contents are:
 *              MS - Count down timer for miliseconds,
 *              HMS - Combined hours minutes and seconds in each counter.
 *              TOD - Time Of day counter used for systems that have a clock.
 *              Seconds - Count down timer for seconds.
 *              Minutes - Count down timer for minutes.
 *              Counter - Count up counter.
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "../../ProductLibraryInclude/C_extensions.h"
#include "../../ProductLibraryInclude/Timers.h"

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------

//!MillisecondTimer structure
typedef struct
{
	uint8 Active : 1;
	uint8 Complete : 1;
	uint8 unused : 6;
	uint16 Count;
} TYPE_MSTIMER;

//!Seconds Timer structure
typedef struct
{
	uint8 Active : 1;
	uint8 Complete : 1;
	uint8 Divisor : 6;
	uint16 Count;
} TYPE_SECONDSTIMER;

//!Minutes Timer structure
typedef struct
{
	uint8 Active : 1;
	uint8 Complete : 1;
	uint8 unused : 6;
	uint16 Divisor;
	uint16 Count;
} TYPE_MINUTESTIMER;

//! HMSTimer structure
typedef struct
{
	uint8 Active : 1;
	uint8 Complete : 1;
	uint8 unused : 6;
	HMS Time;
} TYPE_HMSTIMER;

/**
 *  MEMORY SECTIONS
 */
#if (MS_NUM > 0)
	//! if required the application specific can surround this declaration with #pragmas
	TYPE_MSTIMER Ms_Timers[MS_NUM]; //!< MillisecondsTimer array
#endif

#if (SECONDS_NUM > 0)
	//! if required the application specific can surround this declaration with #pragmas
	TYPE_SECONDSTIMER Seconds_Timers[SECONDS_NUM]; //!< Seconds array
#endif

#if (MINUTES_NUM > 0)
	//! if required the application specific can surround this declaration with #pragmas
	TYPE_MINUTESTIMER Minutes_Timers[MINUTES_NUM]; //!< Minutes array
#endif

#if (HMS_NUM > 0)
	//! if required the application specific can surround this declaration with #pragmas
	TYPE_HMSTIMER Hms_Timers[HMS_NUM]; //!< HMSTimer array
#endif

#if (MS_TICK < 1)
	#error The MS_TICK parameter must be 1 or greater!!!.
#endif

#if (SECONDS_TICK < 1)
	#error The SECONDS_TICK parameter must be 1 or greater!!!.
#endif

#if (MINUTES_TICK < 1)
	#error The MINUTES_TICK parameter must be 1 or greater!!!.
#endif

#if (HMS_TICK < 1)
	#error The HMS_TICK parameter must be 1 or greater!!!.
#endif

#if (HMS_NUM > 0) //If HMSTimer selected to compile
	uint16 Hms_Count[HMS_NUM]; //Counts ticks until 1 sec
	const uint16 Hms_Count_Max = 1000 / HMS_TICK; //# of ticks in 1 sec
#endif

static uint16 Timers_Ticks_Sec;
static uint16 Timers_Ticks_Min;
static uint16 Timers_Ticks_HMS;

static uint8 Timers_Ticks_Ms_Protection;
static uint8 Timers_Ticks_Sec_Protection;
static uint8 Timers_Ticks_Min_Protection;
static uint8 Timers_Ticks_HMS_Protection;

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------

static void ServiceMs(void);
static void ServiceSeconds(void);
static void ServiceMinutes(void);
static void ServiceHMS(void);

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

/**
 *  @brief      It Initializes the module Timers and its variables
 *
 *
 */
void TIMERS__Initialize(void)
{
	uint8 i;

#if (HMS_NUM > 0) //If HMSTimer is compiled
	for (i = 0; i < HMS_NUM; i++)
	{
		Hms_Count[i] = 0; //Counts ticks until 1 sec
	}
#endif

//Loop through all compiled MillisecondTimers
#if (MS_NUM > 0)
	for (i = 0; i < MS_NUM; i++)
	{
		Ms_Timers[i].Active = INACTIVE;
		Ms_Timers[i].Complete = TIMERS_INIT_STATE;
		Ms_Timers[i].Count = 0;
	}
#endif

	//Loop through all compiled Seconds timers
#if (SECONDS_NUM > 0)
	for (i = 0; i < SECONDS_NUM; i++)
	{
		Seconds_Timers[i].Active = INACTIVE;
		Seconds_Timers[i].Complete = TIMERS_INIT_STATE;
		Seconds_Timers[i].Divisor = 0;
		Seconds_Timers[i].Count = 0;
	}
#endif

	//Loop through all compiled Minutes timers
#if (MINUTES_NUM > 0)
	for (i = 0; i < MINUTES_NUM; i++)
	{
		Minutes_Timers[i].Active = INACTIVE;
		Minutes_Timers[i].Complete = TIMERS_INIT_STATE;
		Minutes_Timers[i].Divisor = 0;
		Minutes_Timers[i].Count = 0;
	}
#endif

//Loop throught all compiled Hms_Timers
#if (HMS_NUM > 0)
	for (i = 0; i < HMS_NUM; i++)
	{
		Hms_Timers[i].Active = INACTIVE;
		Hms_Timers[i].Complete = TIMERS_INIT_STATE;
		Hms_Timers[i].Time.Hrs = 0;
		Hms_Timers[i].Time.Min = 0;
		Hms_Timers[i].Time.Sec = 0;
	}
#endif
	
	Timers_Ticks_Ms_Protection = MS_NUM;
	Timers_Ticks_Sec_Protection = SECONDS_NUM;
	Timers_Ticks_Min_Protection = MINUTES_NUM;
	Timers_Ticks_HMS_Protection = HMS_NUM;

	Timers_Ticks_Sec = 0;
	Timers_Ticks_Min = 0;
	Timers_Ticks_HMS = 0;
}

/**
 * @brief       Additional timer interrupt to count precisely.
 *              Bandwidth occupation:
 *                  - total execution time: min 5usec   max 20usec
 *                  - service HMS timers:   min         max
 *                  - service ms timers:    min         max
 *
 */
void TIMERS__MsTick(void)
{
	// increment 1ms tick
	Timers_Ticks_Sec++;
	Timers_Ticks_Min++;
	Timers_Ticks_HMS++;

	// every tick is a ms
	ServiceMs();

	if (Timers_Ticks_Sec >= SECONDS_TICK)
	{
		Timers_Ticks_Sec = 0;
		ServiceSeconds();
	}

	if (Timers_Ticks_Min >= MINUTES_TICK)
	{
		Timers_Ticks_Min = 0;
		ServiceMinutes();
	}

	if (Timers_Ticks_HMS >= HMS_TICK)
	{
		Timers_Ticks_HMS = 0;
		ServiceHMS();
	}

	// call hard-timed functions 1ms based
	TIMERS_TICK_FUNCTIONS()
}


//===================================== MillisecondTimers ===============================================
/**
 *  @brief      Sets MillisecondTimer specified by 'id' to count down
 *              ms_value milliseconds. Also adjust for the time base module.
 *              \Also starts the timer.
 *
 *  @param      id :MsTimer id (enum label)
 *  @param      ms_value : millisecond value to set timer
 *
 */
void TIMERS__MsSet(MS_TIMER_LABEL id, uint16 ms_value)
{
#if (MS_NUM > 0)
	unsigned long temp; // Declare long for multiplication

	if (id < MS_NUM)
	{
		Timers_Ticks_Ms_Protection = id;

		if (ms_value < MS_TICK) // Is the requested time less than defined tick size?
		{
			TIMERS__MsExpire(id); // Set requested timer to expired
		}
		else // If no error
		{
			INTERRUPTS_OFF_DEF();
			Ms_Timers[id].Active = INACTIVE;   // Signal timer is active
			Ms_Timers[id].Complete = COMPLETE; // Flag a timer timeout
			INTERRUPTS_ON_DEF();

			temp = ms_value / MS_TICK;
			INTERRUPTS_OFF_DEF();
			Ms_Timers[id].Count = (unsigned short int)temp; // of ticks needed to reach ms_value milliseconds

			if (Ms_Timers[id].Count != 0)
			{
				Ms_Timers[id].Complete = INCOMPLETE; // Make sure time out flag is cleared
				Ms_Timers[id].Active = ACTIVE;		 // Signal timer is active
			}
			INTERRUPTS_ON_DEF();
		}
		Timers_Ticks_Ms_Protection = MS_NUM;
	}
#endif
}

/**
 *  @brief      Resets the timer specified by 'id' to its initial default state of INCOMPLETE and INACTIVE.
 *
 *  @param      id : MsTimer id (enum label)
 *
 */
void TIMERS__MsReset(MS_TIMER_LABEL id)
{
#if (MS_NUM > 0)
	//If no error
	if (id < MS_NUM)
	{
		// Clear counter and set to inactive and incomplete
		INTERRUPTS_OFF_DEF();
		Ms_Timers[id].Active = INACTIVE;
		Ms_Timers[id].Count = 0;
		Ms_Timers[id].Complete = INCOMPLETE;
		INTERRUPTS_ON_DEF();
	}
#endif
}

/**
 *  @brief      Clears the MillisecondTimer counter specified by 'id' and
 *              sets it to INACTIVE and COMPLETE - thus making it appear as
 *              if it has timed out.
 *
 *  @param      id : MsTimer id (enum label)
 *
 */
void TIMERS__MsExpire(MS_TIMER_LABEL id)
{
#if (MS_NUM > 0)
	// If no error
	if (id < MS_NUM)
	{
		// Clear counter and set to inactive and complete
		INTERRUPTS_OFF_DEF();
		Ms_Timers[id].Active = INACTIVE;
		Ms_Timers[id].Count = 0;
		Ms_Timers[id].Complete = COMPLETE;
		INTERRUPTS_ON_DEF();
	}
#endif
}

/**
 *  @brief      Pauses the MillisecondTimer specified by 'id' by making it inactive.
 *
 *  @param      id - MsTimer id (enum label)
 *
 */
void TIMERS__MsPause(MS_TIMER_LABEL id)
{
#if (MS_NUM > 0)
	// If no error
	if (id < MS_NUM)
	{
		INTERRUPTS_OFF_DEF();
		Ms_Timers[id].Active = INACTIVE; // Deactivate timer
		INTERRUPTS_ON_DEF();
	}
#endif
}

/**
 *  @brief      Allows the MillisecondTimer specified by 'id' to resume from a pause by setting it to active.
 *
 *  @param      id - MsTimer id (enum label)
 *
 */
void TIMERS__MsResume(MS_TIMER_LABEL id)
{
#if (MS_NUM > 0)
	// If no error & time left in timer
	if ((id < MS_NUM) &&
		(Ms_Timers[id].Complete != COMPLETE))
	{
		Ms_Timers[id].Active = ACTIVE;
	}
#endif
}

/**
 *  @brief      Returns the status of the MsTimer specified by 'id'.
 *
 *  @param      id - MsTimer id (enum label)
 *
 *  @return     TIMER_STATE : TIMERS_IDLE, TIMERS_RUNNING, TIMERS_PAUSED, TIMERS_COMPLETED, TIMERS_INVALID
 */
TIMER_STATE TIMERS__MsGetStatus(MS_TIMER_LABEL id)
{
#if (MS_NUM > 0)
	TIMER_STATE state; // State to be returned
	TYPE_MSTIMER temp_ms;

	state = TIMERS_INVALID; // TIMERS_INVALID state

	if (id < MS_NUM) // If does not exist
	{
		INTERRUPTS_OFF_DEF(); // Take timer data snapshot
		temp_ms = Ms_Timers[id];
		INTERRUPTS_ON_DEF();

		if (temp_ms.Active == ACTIVE) // If timer is active
		{
			state = TIMERS_RUNNING; // must be RUNNING
		}
		else // If timer is inactive
		{
			if (temp_ms.Complete == COMPLETE) // If timer is complete
			{
				state = TIMERS_COMPLETED; // must be TIMERS_COMPLETED
			}
			else // If inactive and incomplete
			{
				if (temp_ms.Count > 0) // If time left
				{
					state = TIMERS_PAUSED; // must be TIMERS_PAUSED
				}
				else // Otherwise (inactive, incomplete, no time)
				{
					state = TIMERS_IDLE; // is TIMERS_IDLE
				}
			}
		}
	}

	return (state);

#else
	return (TIMERS_INVALID);
#endif
}

/**
 *  @brief      Returns the time (in ms) remaining the MillisecondTimer identified by 'id'.
 *
 *  @param      id - MsTimer id (enum label)
 *
 *  @return     uint16 remaining time (ms)
 */
uint16 TIMERS__MsGetTime(MS_TIMER_LABEL id)
{
#if (MS_NUM > 0)
	unsigned short int temp_count;
	if (id >= MS_NUM) // If error exists
	{
		return 0;
	}
	else
	{
		INTERRUPTS_OFF_DEF();
		temp_count = Ms_Timers[id].Count;
		INTERRUPTS_ON_DEF();
		return (temp_count * MS_TICK); // Convert # of ticks back to ms
	}
#else
	return (0);
#endif
}

//========================================== HMS TIMERS ===================================================


/**
 *  @brief      Set Hms_Timers specified by 'id' to time hrs:min:sec
 *
 *  @param      id - HMSTimer id (enum label)
 *  @param      hrs - hours component of HMS timer
 *  @param      min - minute component of HMS timer
 *  @param      sec - second component of HMS timer
 *
 */
void TIMERS__HMSSet(HMS_TIMER_LABEL id, unsigned char hrs, unsigned char min, unsigned char sec)
{
#if (HMS_NUM > 0)	  // Start HMSTimer block
	if (id < HMS_NUM) // If no error
	{
		Timers_Ticks_HMS_Protection = id;
		Hms_Timers[id].Active = INACTIVE; // Activate timer
		Hms_Timers[id].Time.Hrs = hrs;	  //Set time
		Hms_Timers[id].Time.Min = min;
		Hms_Timers[id].Time.Sec = sec;

		if (!(hrs | min | sec)) //Timer set to 0?
		{
			Hms_Timers[id].Complete = COMPLETE;
			Hms_Timers[id].Active = INACTIVE;
		}
		else
		{
			Hms_Timers[id].Complete = INCOMPLETE;
			Hms_Timers[id].Active = ACTIVE; // Activate timer
		}
		Hms_Count[id] = 0;

		Timers_Ticks_HMS_Protection = HMS_NUM;
	}
#endif
}

/**
 *  @brief      Clears the HMSTimer counter specified by 'id' and
 *              sets it to INACTIVE and COMPLETE - thus making it appear as
 *              \ if it has timed out.
 *
 *  @param      id - HMSTimer id (enum label)
 *
 */
void TIMERS__HMSExpire(HMS_TIMER_LABEL id)
{
#if (HMS_NUM > 0)	  // Start HMSTimer block
	if (id < HMS_NUM) // If no error
	{
		// Deactivate timer and clear time
		Hms_Timers[id].Active = INACTIVE;
		Hms_Timers[id].Time.Hrs = 0;
		Hms_Timers[id].Time.Min = 0;
		Hms_Timers[id].Time.Sec = 0;
		Hms_Timers[id].Complete = COMPLETE;
	}
#endif
}

/**
 *  @brief      Resets the timer specified by 'id' to its initial default state of INCOMPLETE and INACTIVE.
 *
 *  @param      id - HMSTimer id (enum label)
 *
 */
void TIMERS__HMSReset(HMS_TIMER_LABEL id)
{
#if (HMS_NUM > 0)	  // Start HMSTimer block
	if (id < HMS_NUM) // If no error
	{
		//! Deactivate timer and clear time
		Hms_Timers[id].Active = INACTIVE;
		Hms_Timers[id].Time.Hrs = 0;
		Hms_Timers[id].Time.Min = 0;
		Hms_Timers[id].Time.Sec = 0;
		Hms_Timers[id].Complete = INCOMPLETE;
	}
#endif
}

/**
 *  @brief      Pauses the HMSTimer specified by 'id' by setting to inactive.
 *
 *  @param      id - HMSTimer id (enum label)
 *
 */
void TIMERS__HMSPause(HMS_TIMER_LABEL id)
{
#if (HMS_NUM > 0)	  // Start HMSTimer block
	if (id < HMS_NUM) // If no error
	{
		Hms_Timers[id].Active = INACTIVE; // Deactivate timer
	}
#endif
}

/**
 *  @brief      Resumes the HMSTimer specified by 'id' by setting to active.
 *
 *  @param      id - HMSTimer id (enum label)
 *
 */
void TIMERS__HMSResume(HMS_TIMER_LABEL id)
{
#if (HMS_NUM > 0) // Start HMSTimer block
	if ((id < HMS_NUM) &&
		(Hms_Timers[id].Complete != COMPLETE)) //If no error & not complete
	{
		Hms_Timers[id].Active = ACTIVE;
	}
#endif
}

/**
 *  @brief      Returns the status of the HMSTimer specified by 'id'.
 *
 *  @param      id - HMSTimer id (enum label)
 *
 *  @return     TIMER_STATE: TIMERS_IDLE, TIMERS_RUNNING, TIMERS_PAUSED, TIMERS_COMPLETED, TIMERS_INVALID
 */
TIMER_STATE TIMERS__HMSGetStatus(HMS_TIMER_LABEL id)
{
#if (HMS_NUM > 0)	   // Start HMSTimer block
	TIMER_STATE state; // State to be returned

	state = TIMERS_INVALID; // TIMERS_INVALID state

	if (id < HMS_NUM) // If does not exist
	{
		if (Hms_Timers[id].Active == ACTIVE) // If timer is active
		{
			state = TIMERS_RUNNING; // must be RUNNING
		}
		else // If timer is inactive
		{
			if (Hms_Timers[id].Complete == COMPLETE) // If timer is complete
			{
				state = TIMERS_COMPLETED; // must be TIMERS_COMPLETED
			}
			else // If inactive and incomplete
			{
				if ((Hms_Timers[id].Time.Hrs > 0) || // If time left
					(Hms_Timers[id].Time.Min > 0) ||
					(Hms_Timers[id].Time.Sec > 0))
				{
					state = TIMERS_PAUSED; // must be TIMERS_PAUSED
				}
				else // Otherwise (inactive, incomplete, no time)
				{
					state = TIMERS_IDLE; // is TIMERS_IDLE
				}
			}
		}
	}

	return (state);
#else
	return (TIMERS_INVALID);
#endif
}

/**
 *  @brief      Returns the time remaining the HMSTimer defined by 'id'.
 *
 *  @param      id - HMSTimer id (enum label)
 *  @param      time - pointer to time structure to be filled
 *
 */
void TIMERS__HMSGetTime(HMS_TIMER_LABEL id, HMS *time)
{
#if (HMS_NUM > 0)	  // Start HMSTimer block
	if (id < HMS_NUM) // If no error
	{
		// Copy time data over
		time->Hrs = Hms_Timers[id].Time.Hrs;
		time->Min = Hms_Timers[id].Time.Min;
		time->Sec = Hms_Timers[id].Time.Sec;
	}
#endif
}

//========================================= Seconds Timer ==========================================================
/**
 *  @brief      Sets Seconds timer specified by 'id' to count down
 *              seconds_value seconds.
 *              Also starts the timer.
 *
 *  @param      id :SecondsTimer id (enum label)
 *  @param      seconds_value : seconds value to set timer
 *
 */
void TIMERS__SecondsSet(SECONDS_LABEL id, uint16 seconds_value)
{
#if (SECONDS_NUM > 0)
	if (id < SECONDS_NUM)
	{
		Timers_Ticks_Sec_Protection = id;
		INTERRUPTS_OFF_DEF();
		Seconds_Timers[id].Active = INACTIVE;	// Signal timer is active
		Seconds_Timers[id].Complete = COMPLETE; // Flag a timer timeout
		INTERRUPTS_ON_DEF();

		Seconds_Timers[id].Divisor = 1000 / SECONDS_TICK;
		INTERRUPTS_OFF_DEF();
		Seconds_Timers[id].Count = seconds_value; //Set seconds value
		if (Seconds_Timers[id].Count != 0)
		{
			Seconds_Timers[id].Complete = INCOMPLETE; // Make sure time out flag is cleared
			Seconds_Timers[id].Active = ACTIVE;		  // Signal timer is active
		}
		INTERRUPTS_ON_DEF();
		Timers_Ticks_Sec_Protection = SECONDS_NUM;
	}
#endif
}

/**
 *  @brief      Resets and sets state of specified counter to Complete.
 *
 *  @param      id - Counter to expire
 *
 */
void TIMERS__SecondsExpire(SECONDS_LABEL id)
{
#if (SECONDS_NUM > 0)
	if (id < SECONDS_NUM)
	{
		// Clear counter and set to inactive and complete
		INTERRUPTS_OFF_DEF();
		Seconds_Timers[id].Active = INACTIVE;
		Seconds_Timers[id].Count = 0;
		Seconds_Timers[id].Complete = COMPLETE;
		INTERRUPTS_ON_DEF();
	}
#endif
}

/**
 *  @brief      Resets specified counter and sets state to Incomplete.
 *
 *  @param      id - Counter to reset
 *
 */
void TIMERS__SecondsReset(SECONDS_LABEL id)
{
#if (SECONDS_NUM > 0)
	if (id < SECONDS_NUM)
	{
		// Clear counter and set to inactive and incomplete
		INTERRUPTS_OFF_DEF();
		Seconds_Timers[id].Active = INACTIVE;
		Seconds_Timers[id].Count = 0;
		Seconds_Timers[id].Complete = INCOMPLETE;
		INTERRUPTS_ON_DEF();
	}
#endif
}

/**
 *  @brief      Pauses specified counter.
 *
 *  @param      id - Counter to expire
 *
 */
void TIMERS__SecondsPause(SECONDS_LABEL id)
{
#if (SECONDS_NUM > 0)
	if (id < SECONDS_NUM)
	{
		INTERRUPTS_OFF_DEF();
		Seconds_Timers[id].Active = INACTIVE; // Deactivate timer
		INTERRUPTS_ON_DEF();
	}
#endif
}

/**
 *  @brief      Resumes specified counter.
 *
 *  @param      id - Counter to resume
 *
 */
void TIMERS__SecondsResume(SECONDS_LABEL id)
{
#if (SECONDS_NUM > 0)
	if ((id < SECONDS_NUM) &&
		(Seconds_Timers[id].Complete != COMPLETE))
	{
		Seconds_Timers[id].Active = ACTIVE;
	}
#endif
}

/**
 *  @brief      Returns status of specified counter.
 *
 *  @param      id - Counter to return status of
 *
 *  @return     State of counter using TIMER_STATE enum.
 *
 */
TIMER_STATE TIMERS__SecondsGetStatus(SECONDS_LABEL id)
{
#if (SECONDS_NUM > 0)
	TIMER_STATE state; // State to be returned
	TYPE_SECONDSTIMER temp;

	state = TIMERS_INVALID; // TIMERS_INVALID state

	if (id < SECONDS_NUM) // If does not exist
	{
		INTERRUPTS_OFF_DEF(); // Take timer data snapshot
		temp = Seconds_Timers[id];
		INTERRUPTS_ON_DEF();

		if (temp.Active == ACTIVE) // If timer is active
		{
			state = TIMERS_RUNNING; // must be RUNNING
		}
		else // If timer is inactive
		{
			if (temp.Complete == COMPLETE) // If timer is complete
			{
				state = TIMERS_COMPLETED; // must be TIMERS_COMPLETED
			}
			else // If inactive and incomplete
			{
				if (temp.Count > 0) // If time left
				{
					state = TIMERS_PAUSED; // must be TIMERS_PAUSED
				}
				else // Otherwise (inactive, incomplete, no time)
				{
					state = TIMERS_IDLE; // is TIMERS_IDLE
				}
			}
		}
	}

	return (state);

#else
	return (TIMERS_INVALID);
#endif
}

/**
 *  @brief      Returns seconds for specified counter.
 *
 *  @param      id - Counter to return value of
 *
 *  @return     Seconds for specified timer
 */
uint16 TIMERS__SecondsGet(SECONDS_LABEL id)
{
#if (SECONDS_NUM > 0)
	if (id >= SECONDS_NUM) // If error exists
	{
		return 0;
	}
	else
	{
		return (Seconds_Timers[id].Count);
	}
#else
	return (0);
#endif
}

//========================================= Minutes Timer ==========================================================
/**
 *  @brief      Sets Minutes timer specified by 'id' to count down
 *              minutes_value minutes.
 *              Also starts the timer.
 *
 *  @param      id :SecondsTimer id (enum label)
 *  @param      seconds_value : seconds value to set timer
 *
 */

void TIMERS__MinutesSet(MINUTES_LABEL id, unsigned short int time)
{
#if (MINUTES_NUM > 0)
	if (id < MINUTES_NUM)
	{
		Timers_Ticks_Min_Protection = id;
		INTERRUPTS_OFF_DEF();
		Minutes_Timers[id].Active = INACTIVE;	// Signal timer is active
		Minutes_Timers[id].Complete = COMPLETE; // Flag a timer timeout
		INTERRUPTS_ON_DEF();

		Minutes_Timers[id].Divisor = 60000 / MINUTES_TICK;
		INTERRUPTS_OFF_DEF();
		Minutes_Timers[id].Count = time; //Set minutes value
		if (Minutes_Timers[id].Count != 0)
		{
			Minutes_Timers[id].Complete = INCOMPLETE; // Make sure time out flag is cleared
			Minutes_Timers[id].Active = ACTIVE;		  // Signal timer is active
		}
		INTERRUPTS_ON_DEF();
		Timers_Ticks_Min_Protection = MINUTES_NUM;
	}
#endif
}

/**
 *  @brief      Resets and sets state of specified counter to Complete.
 *
 *  @param      id - Counter to expire
 *
 */
void TIMERS__MinutesExpire(MINUTES_LABEL id)
{
#if (MINUTES_NUM > 0)
	if (id < MINUTES_NUM)
	{
		// Clear counter and set to inactive and complete
		INTERRUPTS_OFF_DEF();
		Minutes_Timers[id].Active = INACTIVE;
		Minutes_Timers[id].Count = 0;
		Minutes_Timers[id].Complete = COMPLETE;
		INTERRUPTS_ON_DEF();
	}
#endif
}

/**
 *  @brief      Resets specified counter and sets state to Incomplete.
 *
 *  @param      id - Counter to reset
 *
 */
void TIMERS__MinutesReset(MINUTES_LABEL id)
{
#if (MINUTES_NUM > 0)
	if (id < MINUTES_NUM)
	{
		// Clear counter and set to inactive and incomplete
		INTERRUPTS_OFF_DEF();
		Minutes_Timers[id].Active = INACTIVE;
		Minutes_Timers[id].Count = 0;
		Minutes_Timers[id].Complete = INCOMPLETE;
		INTERRUPTS_ON_DEF();
	}
#endif
}

/**
 *  @brief      Pauses specified counter.
 *
 *  @param      id - Counter to expire
 *
 */
void TIMERS__MinutesPause(MINUTES_LABEL id)
{
#if (MINUTES_NUM > 0)
	if (id < MINUTES_NUM)
	{
		INTERRUPTS_OFF_DEF();
		Minutes_Timers[id].Active = INACTIVE; // Deactivate timer
		INTERRUPTS_ON_DEF();
	}
#endif
}

/**
 *  @brief      Resumes specified counter.
 *
 *  @param      id - Counter to resume
 *
 */
void TIMERS__MinutesResume(MINUTES_LABEL id)
{
#if (MINUTES_NUM > 0)
	if ((id < MINUTES_NUM) &&
		(Minutes_Timers[id].Complete != COMPLETE))
	{
		Minutes_Timers[id].Active = ACTIVE;
	}
#endif
}

/**
 *  @brief      Returns status of specified counter.
 *
 *  @param      id - Counter to return status of
 *
 *  @return     State of counter using TIMER_STATE enum.
 *
 */
TIMER_STATE TIMERS__MinutesGetStatus(MINUTES_LABEL id)
{
#if (MINUTES_NUM > 0)
	TIMER_STATE state; // State to be returned
	TYPE_MINUTESTIMER temp;

	state = TIMERS_INVALID; // TIMERS_INVALID state

	if (id < MINUTES_NUM) // If does not exist
	{
		INTERRUPTS_OFF_DEF(); // Take timer data snapshot
		temp = Minutes_Timers[id];
		INTERRUPTS_ON_DEF();

		if (temp.Active == ACTIVE) // If timer is active
		{
			state = TIMERS_RUNNING; // must be RUNNING
		}
		else // If timer is inactive
		{
			if (temp.Complete == COMPLETE) // If timer is complete
			{
				state = TIMERS_COMPLETED; // must be TIMERS_COMPLETED
			}
			else // If inactive and incomplete
			{
				if (temp.Count > 0) // If time left
				{
					state = TIMERS_PAUSED; // must be TIMERS_PAUSED
				}
				else // Otherwise (inactive, incomplete, no time)
				{
					state = TIMERS_IDLE; // is TIMERS_IDLE
				}
			}
		}
	}

	return (state);

#else
	return (TIMERS_INVALID);
#endif
}

/**
 *  @brief      Returns minutes for specified counter.
 *
 *  @param      id - Counter to return value of
 *
 *  @return     Minutes for specified timer
 */
uint16 TIMERS__MinutesGet(MINUTES_LABEL id)
{
#if (MINUTES_NUM > 0)
	if (id >= MINUTES_NUM) // If error exists
	{
		return 0;
	}
	else
	{
		return (Minutes_Timers[id].Count);
	}
#else
	return (0);
#endif
}

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================

/**
 *  @brief      Services all compiled MillisecondTimers
 *
 */
static void ServiceMs(void)
{
#if (MS_NUM > 0)
	unsigned char i; //Loop count

	for (i = 0; i < MS_NUM; i++) //Loop through all compiled Ms_Timers
	{
		if (Ms_Timers[i].Active) //Timer running?
		{
			if (i != Timers_Ticks_Ms_Protection)
			{
				Ms_Timers[i].Count--;	   //Decrement counter
				if (!(Ms_Timers[i].Count)) //Test if expired
				{
					Ms_Timers[i].Active = INACTIVE;	  //Deactivate timer
					Ms_Timers[i].Complete = COMPLETE; //Flag a timer timeout
				}
			}
		}
	}
#endif
}

/**
 *  @Brief   Handler for the Seconds timers
 *
 */
static void ServiceSeconds(void)
{
#if (SECONDS_NUM > 0)
	unsigned char i; //Loop count

	for (i = 0; i < SECONDS_NUM; i++) //Loop through all compiled seconds timers
	{
		if (Seconds_Timers[i].Active) //Timer running?
		{
			if (i != Timers_Ticks_Sec_Protection)
			{
				Seconds_Timers[i].Divisor--; //Decrement to manage divisor

				if (!Seconds_Timers[i].Divisor) //Has divisor timed out?
				{
					Seconds_Timers[i].Divisor = 1000 / SECONDS_TICK; //One second has expired. Reset divisor
					Seconds_Timers[i].Count--;						 //Decrement counter
				}
				if (!(Seconds_Timers[i].Count)) //Test if expired
				{
					Seconds_Timers[i].Active = INACTIVE;   //Deactivate timer
					Seconds_Timers[i].Complete = COMPLETE; //Flag a timer timeout
				}
			}
		}
	}
#endif
}

/**
 *  @Brief   Handler for the Minutes timers
 *
 */
static void ServiceMinutes(void)
{
#if (MINUTES_NUM > 0)
	unsigned char i; //Loop count

	for (i = 0; i < MINUTES_NUM; i++) //Loop through all compiled minutes timers
	{
		if (Minutes_Timers[i].Active) //Timer running?
		{
			if (i != Timers_Ticks_Min_Protection)
			{
				Minutes_Timers[i].Divisor--; //Decrement to manage divisor

				if (!Minutes_Timers[i].Divisor) //Has divisor timed out?
				{
					Minutes_Timers[i].Divisor = 60000 / MINUTES_TICK; //One minute has expired. Reset divisor
					Minutes_Timers[i].Count--;						  //Decrement counter
				}
				if (!(Minutes_Timers[i].Count)) //Test if expired
				{
					Minutes_Timers[i].Active = INACTIVE;   //Deactivate timer
					Minutes_Timers[i].Complete = COMPLETE; //Flag a timer timeout
				}
			}
		}
	}
#endif
}

/**
 *  @brief      Services all compiled HMSimers and the TOD clock
 *
 */
static void ServiceHMS(void)
{
#if (HMS_NUM > 0) //HMS service routine block
	unsigned char i;				// Loop counter

	for (i = 0; i < HMS_NUM; i++) // Loop through all compiled HMStimers
	{
		if (Hms_Timers[i].Active) // Timer running?
		{
			if (i != Timers_Ticks_HMS_Protection)
			{
				Hms_Count[i]++;
				if (Hms_Count[i] >= Hms_Count_Max)
				{
					Hms_Count[i] = 0;

					if (Hms_Timers[i].Time.Sec) // Any secs left?
					{
						Hms_Timers[i].Time.Sec--;
						if (!((Hms_Timers[i].Time.Sec) |
							  (Hms_Timers[i].Time.Min) |
							  (Hms_Timers[i].Time.Hrs))) //Timer finished?
						{
							Hms_Timers[i].Complete = COMPLETE;
							Hms_Timers[i].Active = INACTIVE;
						}
					}
					else if (Hms_Timers[i].Time.Min) // Any min left?
					{
						Hms_Timers[i].Time.Min--;
						Hms_Timers[i].Time.Sec = 59;
					}
					else if (Hms_Timers[i].Time.Hrs) // Any hrs left?
					{
						Hms_Timers[i].Time.Hrs--;
						Hms_Timers[i].Time.Min = 59;
						Hms_Timers[i].Time.Sec = 59;
					}
				}
			}
		}
	}

#endif // End HMS service routine block
}
