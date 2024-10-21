/**
 *  @file       DigitalOutput.c
 *  @brief      This file contains Digital Output interface
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 - Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "../../ProductLibraryInclude/DigitalOutput.h"

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------


//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------

//static void CANStandByHandler	 		(ON_OFF_TYPE status);
//static void DeepTraySensorEnableHandler (ON_OFF_TYPE status);
//static void CupSensorEnableHandler		(ON_OFF_TYPE status);
//static void PumpEnableHandler			(ON_OFF_TYPE status);
//static void H2OSensorEnableHandler		(ON_OFF_TYPE status);
//static void STM8ResetHandler			(ON_OFF_TYPE status);
//static void SSREnableHandler		 	(SOLID_STATE_RELAY_TYPE relay, ON_OFF_TYPE status);
//static void DrvL99ActivationHandler		(ACTIVE_TYPE status);
//static void DrvL99CSHandler				(DEVICE_L99_TYPE drv, LOW_HIGH_TYPE status);
//static void DrvDataFlashCSHandler		(LOW_HIGH_TYPE status);
//
//static DO_INTERFACE_TYPE DOInterface =
//{
//	.CANStandBy 			= &CANStandByHandler,
//	.DeepTraySensorEnable	= &DeepTraySensorEnableHandler,
//	.CupSensorEnable		= &CupSensorEnableHandler,
//	.PumpEnable				= &PumpEnableHandler,
//	.H2OSensorEnable		= &H2OSensorEnableHandler,
//	.STM8Reset				= &STM8ResetHandler,
//	.SSREnable				= &SSREnableHandler,
//	.DrvL99Activation		= &DrvL99ActivationHandler,
//	.DrvL99CS				= &DrvL99CSHandler,
//	.DrvDataFlashCS			= &DrvDataFlashCSHandler,
//};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

/**
  * @brief  Digital Output interface
  * @param  None
  * @retval Digital Output interface methods
  */
//DO_INTERFACE_TYPE DO__Interface(void)
//{
//	return (DOInterface);
//}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief		This function enable or disable CAN Standby. Digital Output
  *
  * @param		status: ON => CAN_STBY_Pin = 1; OFF => CAN_STBY_Pin = 0
  * @retval		None
  */
//static void CANStandByHandler(ON_OFF_TYPE status)
//{
//	GPIO_PinState var;
//
//	if(status == ON)
//	{
//		var = GPIO_PIN_SET;
//	}
//	else
//	{
//		var = GPIO_PIN_RESET;
//	}
//	HAL_GPIO_WritePin(CAN_STBY_GPIO_Port, CAN_STBY_Pin, var);
//}

/**
  * @brief		This function enable / disable Deep Tray Sensor. Digital Output
  *
  * @param		status: ON => DO_DEEP_TRAY_SENS_ENABLE_Pin = 1; OFF => DO_DEEP_TRAY_SENS_ENABLE_Pin = 0
  * @retval		None
  */
//static void DeepTraySensorEnableHandler (ON_OFF_TYPE status)
//{
//	GPIO_PinState var;
//
//	if(status == ON)
//	{
//		var = GPIO_PIN_SET;
//	}
//	else
//	{
//		var = GPIO_PIN_RESET;
//	}
//	HAL_GPIO_WritePin(DO_DEEP_TRAY_SENS_ENABLE_GPIO_Port, DO_DEEP_TRAY_SENS_ENABLE_Pin, var);
//
//}

/**
  * @brief		This function enable / disable Cup Sensor. Digital Output
  *
  * @param		status: ON => DO_CMD_EN_CUPSENSE_Pin = 1; OFF => DO_CMD_EN_CUPSENSE_Pin = 0
  * @retval		None
  */
//static void CupSensorEnableHandler(ON_OFF_TYPE status)
//{
//	GPIO_PinState var;
//
//	if(status == ON)
//	{
//		var = GPIO_PIN_SET;
//	}
//	else
//	{
//		var = GPIO_PIN_RESET;
//	}
//	HAL_GPIO_WritePin(DO_CMD_EN_CUPSENSE_GPIO_Port, DO_CMD_EN_CUPSENSE_Pin, var);
//}

/**
  * @brief		This function enable / disable Pump. Digital Output
  *
  * @param		status: ON => DO_PUMP_EN_Pin = 1; OFF => DO_PUMP_EN_Pin = 0
  * @retval		None
  */
//static void PumpEnableHandler(ON_OFF_TYPE status)
//{
//	GPIO_PinState var;
//
//	if(status == ON)
//	{
//		var = GPIO_PIN_SET;
//	}
//	else
//	{
//		var = GPIO_PIN_RESET;
//	}
//	HAL_GPIO_WritePin(DO_PUMP_EN_GPIO_Port, DO_PUMP_EN_Pin, var);
//}

/**
  * @brief		This function enable / disable H2O Sensor. Digital Output
  *
  * @param		status: ON => DO_H20_SENS_EN_Pin = 1; OFF => DO_H20_SENS_EN_Pin = 0
  * @retval		None
  */
//static void H2OSensorEnableHandler(ON_OFF_TYPE status)
//{
//	GPIO_PinState var;
//
//	if(status == ON)
//	{
//		var = GPIO_PIN_SET;
//	}
//	else
//	{
//		var = GPIO_PIN_RESET;
//	}
//	HAL_GPIO_WritePin(DO_H20_SENS_EN_GPIO_Port, DO_H20_SENS_EN_Pin, var);
//}

/**
  * @brief		This function enable / disable STM8 Reset. Digital Output
  *
  * @param		status: ON => DO_STM8_RESET_Pin = 1; OFF => DO_STM8_RESET_Pin = 0
  * @retval		None
  */
//static void STM8ResetHandler(ON_OFF_TYPE status)
//{
//	GPIO_PinState var;
//
//	if(status == ON)
//	{
//		var = GPIO_PIN_SET;
//	}
//	else
//	{
//		var = GPIO_PIN_RESET;
//	}
//	HAL_GPIO_WritePin(DO_STM8_RESET_GPIO_Port, DO_STM8_RESET_Pin, var);
//}

/**
  * @brief		This function enable / disable Solid State Relay. Digital Output
  *
  * @param		relay: SSR1 = Solid State Relay 1; SSR2 = Solid State Relay 2
  * 			status: ON => DO_SSR1_ON_CMD_Pin or DO_SSR2_ON_CMD_Pin = 1;
  * 				    OFF => DO_SSR1_ON_CMD_Pin or DO_SSR2_ON_CMD_Pin = 0
  * @retval		None
  */
//static void SSREnableHandler(SOLID_STATE_RELAY_TYPE relay, ON_OFF_TYPE status)
//{
//	GPIO_PinState var;
//
//	if(relay < SSR_MAX)
//	{
//		if(status == ON)
//		{
//			var = GPIO_PIN_SET;
//		}
//		else
//		{
//			var = GPIO_PIN_RESET;
//		}
//
//		if(relay == SSR1)
//		{
//			HAL_GPIO_WritePin(DO_SSR1_ON_CMD_GPIO_Port, DO_SSR1_ON_CMD_Pin, var);
//		}
//		else if(relay == SSR2)
//		{
//			HAL_GPIO_WritePin(DO_SSR2_ON_CMD_GPIO_Port, DO_SSR2_ON_CMD_Pin, var);
//		}
//		else
//		{
//			/* do nothing */
//		}
//	}
//	else
//	{
//		/* do nothing */
//	}
//}

/**
  * @brief		This function  activates / deactivates all L99UDL01 drivers Digital Output
  *
  * @param		status: ACTIVE = DO_DRV_EN_Pin = 1; INACTIVE = DO_DRV_EN_Pin = 0
  * @retval		None
  */
//static void DrvL99ActivationHandler(ACTIVE_TYPE status)
//{
//	GPIO_PinState var;
//
//	if(status == ACTIVE)
//	{
//		var = GPIO_PIN_SET;
//	}
//	else
//	{
//		var = GPIO_PIN_RESET;
//	}
//	HAL_GPIO_WritePin(DO_DRV_EN_GPIO_Port, DO_DRV_EN_Pin, var);
//}

/**
  * @brief		This function puts high or low level Chip Select driver pins Digital Output
  *
  * @param		drv: 	L99UDL01 driver identifier
  * @param		status: HIGH = CS_DRV_Pin = 1; LOW = CS_DRV_Pin = 0
  * @retval		None
  */
//static void DrvL99CSHandler(DEVICE_L99_TYPE drv, LOW_HIGH_TYPE status)
//{
//	GPIO_PinState var;
//
//	if((drv >= DEV_L99_1) && (drv < DEV_L99_MAX) )
//	{
//		if(status == HIGH)
//		{
//			var = GPIO_PIN_SET;
//		}
//		else
//		{
//			var = GPIO_PIN_RESET;
//		}
//
//		switch(drv)
//		{
//		case DEV_L99_1:
//			HAL_GPIO_WritePin(DO_DRV_ACT1_CS_SPI1_CS_GPIO_Port, DO_DRV_ACT1_CS_SPI1_CS_Pin, var);
//			break;
//
//		case DEV_L99_2:
//			HAL_GPIO_WritePin(DO_DRV_ACT2_CS_GPIO_Port, DO_DRV_ACT2_CS_Pin, var);
//			break;
//
//		case DEV_L99_3:
//			HAL_GPIO_WritePin(DO_DRV_ACT3_CS_GPIO_Port, DO_DRV_ACT3_CS_Pin, var);
//			break;
//
//		case DEV_L99_4:
//			HAL_GPIO_WritePin(DO_DRV_ACT4_CS_GPIO_Port, DO_DRV_ACT4_CS_Pin, var);
//			break;
//
//		case DEV_L99_5:
//			HAL_GPIO_WritePin(DO_DRV_ACT5_CS_GPIO_Port, DO_DRV_ACT5_CS_Pin, var);
//			break;
//
//		case DEV_L99_6:
//			HAL_GPIO_WritePin(DO_DRV_ACT6_CS_GPIO_Port, DO_DRV_ACT6_CS_Pin, var);
//			break;
//
//		default:
//			/* do nothing */
//			break;
//		}
//	}
//	else
//	{
//		/* do nothing */
//	}
//}

/**
  * @brief		This function  enable / disable Data Flash Chip Select Digital Output
  *
  * @param		status: HIGH => DO_DRV_DATA_FLASH_CS_Pin = 1; LOW => DO_DRV_DATA_FLASH_CS_Pin = 0
  * @retval		None
  */
//static void DrvDataFlashCSHandler(LOW_HIGH_TYPE status)
//{
//	GPIO_PinState var;
//
//	if(status == HIGH)
//	{
//		var = GPIO_PIN_SET;
//	}
//	else
//	{
//		var = GPIO_PIN_RESET;
//	}
//	HAL_GPIO_WritePin(DO_DRV_DATA_FLASH_CS_GPIO_Port, DO_DRV_DATA_FLASH_CS_Pin, var);
//}






