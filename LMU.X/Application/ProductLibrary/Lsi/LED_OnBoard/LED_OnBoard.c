/**
 *  @file       LED_OnBoard.c
 *  @brief      On board leds driver
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "../../ProductLibraryInclude/Timers.h"

#include "../../ProductLibraryInclude/LED_OnBoard.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
#define GREEN_LED_TIME_1s       1000
#define GREEN_LED_TIME_100ms    100

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static void LED_ONB_TurnOff (LED_ONB_INSTANCE_TYPE led);
static void LED_ONB_TurnOn  (LED_ONB_INSTANCE_TYPE led);
static void LED_ONB_Toggle  (LED_ONB_INSTANCE_TYPE led);

const struct LED_ONB_INTRFACE_STRUCT LED_ONB_Interf =
{
    .Initialize      = &LED_ONB__Initialize,
    .Handler25ms     = &LED_ONB__Handler25ms,
    .TurnOff         = &LED_ONB_TurnOff,
    .TurnOn          = &LED_ONB_TurnOn,
    .Toggle          = &LED_ONB_Toggle,
};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes LED On Board module
  *
  * @param  None
  * @retval None
  * @note	None
  */
void LED_ONB__Initialize(void)
{
    DO_Green_LED_SetLow();
    DO_Red_LED_SetLow();
 
    TIMERS__MsSet(MS_TIMER_GREEN_LED_PULSE, GREEN_LED_TIME_1s);
    DO_Green_LED_SetHigh();
}

/**
  * @brief  LED On Board module handler. It manages all the module functionalities
   *
  * @param  None
  * @retval None
  * @note	call this function in the task every 25ms
  */
void LED_ONB__Handler25ms(void)
{
 	/* Heartbeat implementation for Green LED: it pulses 100ms ON and 900ms OFF */
    if(TIMERS__MsGetTime(MS_TIMER_GREEN_LED_PULSE) <= GREEN_LED_TIME_100ms)
    {
        //DO_Green_LED_SetHigh();
        DO_Red_LED_SetHigh();
    }
    else
    {
        //DO_Green_LED_SetLow();
        DO_Red_LED_SetLow();
    }
    
    if(TIMERS__MsGetStatus(MS_TIMER_GREEN_LED_PULSE) == TIMERS_COMPLETED)
    {
        TIMERS__MsSet(MS_TIMER_GREEN_LED_PULSE, GREEN_LED_TIME_1s);
    }
}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================

/**
  * @brief  This function turns OFF the selected LED 
   *
  * @param  led: On Board LED, select it from LED_ONB_INSTANCE_TYPE
  * @retval None
  * @note	None
  */
static void LED_ONB_TurnOff(LED_ONB_INSTANCE_TYPE led)
{
    if((led >= LED_ONB_GREEN) && (led < LED_ONB_MAX))
	{
		switch (led)
		{
		case LED_ONB_GREEN:

			DO_Green_LED_SetLow();
			break;

		case LED_ONB_RED:

			DO_Red_LED_SetLow();
			break;
            
		default:
			/* do nothing */
			break;
		}
	}
	else
	{
		/* TODO: @PP handle LED error not existing */
	}
}

/**
  * @brief  This function turns ON the selected LED
   *
  * @param  led: On Board LED, select it from LED_ONB_INSTANCE_TYPE
  * @retval None
  * @note	None
  */
static void LED_ONB_TurnOn(LED_ONB_INSTANCE_TYPE led)
{
    if((led >= LED_ONB_GREEN) && (led < LED_ONB_MAX))
	{
		switch (led)
		{
		case LED_ONB_GREEN:

			DO_Green_LED_SetHigh();
			break;

		case LED_ONB_RED:

			DO_Red_LED_SetHigh();
			break;
            
		default:
			/* do nothing */
			break;
		}
	}
	else
	{
		/* TODO: @PP handle LED error not existing */
	}
}


/**
  * @brief  This function toggles the selected LED
   *
  * @param  led: On Board LED, select it from LED_ONB_INSTANCE_TYPE
  * @retval None
  * @note	None
  */
static void LED_ONB_Toggle(LED_ONB_INSTANCE_TYPE led)
{
    if((led >= LED_ONB_GREEN) && (led < LED_ONB_MAX))
	{
		switch (led)
		{
		case LED_ONB_GREEN:

			DO_Green_LED_Toggle();
			break;

		case LED_ONB_RED:

			DO_Red_LED_Toggle();
			break;
            
		default:
			/* do nothing */
			break;
		}
	}
	else
	{
		/* TODO: @PP handle LED error not existing */
	}
}