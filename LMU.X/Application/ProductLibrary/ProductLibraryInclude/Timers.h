/**
 *  @file		Timers.h
 *  @brief      Header file for timers module containing prototypes and enumerations for timers
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 *
 */
#ifndef __TIMERS_H__
#define __TIMERS_H__

//=====================================================================================================================
//-------------------------------------- PUBLIC (Constants & Defines) -------------------------------------------------
//=====================================================================================================================
#include "C_Extensions.h"
#include "Timers_prm.h"


typedef struct //HMS data structure
{
	uint8 Hrs;
	uint8 Min;
	uint8 Sec;
} HMS;

typedef enum //Timers states
{
	TIMERS_IDLE = 0,
	TIMERS_RUNNING = 1,
	TIMERS_PAUSED = 2,
	TIMERS_COMPLETED = 3,
	TIMERS_INVALID = 4
} TIMER_STATE;

typedef enum //Counters states
{
	COUNTERS_IDLE = 0,
	COUNTERS_RUNNING = 1,
	COUNTERS_PAUSED = 2,
	COUNTERS_LIMIT_REACHED = 3,
	COUNTERS_INVALID = 4
} COUNTERS_STATE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

void TIMERS__Initialize(void);

void TIMERS__MsTick(void);

void TIMERS__MsSet(MS_TIMER_LABEL, uint16);
void TIMERS__MsExpire(MS_TIMER_LABEL);
void TIMERS__MsReset(MS_TIMER_LABEL);
void TIMERS__MsPause(MS_TIMER_LABEL);
void TIMERS__MsResume(MS_TIMER_LABEL);
TIMER_STATE TIMERS__MsGetStatus(MS_TIMER_LABEL);
uint16 TIMERS__MsGetTime(MS_TIMER_LABEL);

void TIMERS__HMSSet(HMS_TIMER_LABEL, uint8, uint8, uint8);
void TIMERS__HMSExpire(HMS_TIMER_LABEL);
void TIMERS__HMSReset(HMS_TIMER_LABEL);
void TIMERS__HMSPause(HMS_TIMER_LABEL);
void TIMERS__HMSResume(HMS_TIMER_LABEL);
TIMER_STATE TIMERS__HMSGetStatus(HMS_TIMER_LABEL);
void TIMERS__HMSGetTime(HMS_TIMER_LABEL, HMS *);

void TIMERS__SecondsSet(SECONDS_LABEL id, uint16 seconds_value);
void TIMERS__SecondsExpire(SECONDS_LABEL);
void TIMERS__SecondsPause(SECONDS_LABEL);
void TIMERS__SecondsResume(SECONDS_LABEL);
void TIMERS__SecondsReset(SECONDS_LABEL);
TIMER_STATE TIMERS__SecondsGetStatus(SECONDS_LABEL);
uint16 TIMERS__SecondsGet(SECONDS_LABEL);

void TIMERS__MinutesSet(MINUTES_LABEL, uint16 time);
void TIMERS__MinutesExpire(MINUTES_LABEL);
void TIMERS__MinutesPause(MINUTES_LABEL);
void TIMERS__MinutesResume(MINUTES_LABEL);
void TIMERS__MinutesReset(MINUTES_LABEL);
TIMER_STATE TIMERS__MinutesGetStatus(MINUTES_LABEL);
uint16 TIMERS__MinutesGet(MINUTES_LABEL);

#endif // __TIMERS_H__
