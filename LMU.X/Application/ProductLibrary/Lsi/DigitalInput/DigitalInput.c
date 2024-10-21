/**
 *  @file       DigitalInput.c
 *  @brief      This file contains Digital Input interface
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 - Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "../../ProductLibraryInclude/DigitalInput.h"

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------


//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------

//static ON_OFF_TYPE Canister1Handler				(void);
//static ON_OFF_TYPE Canister2Handler				(void);
//static ON_OFF_TYPE Canister3Handler				(void);
//static ON_OFF_TYPE Canister4Handler				(void);
//static ON_OFF_TYPE FlowmeterHandler				(void);
//static ON_OFF_TYPE ArmSw1Handler				(void);
//static ON_OFF_TYPE ArmSW2Handler				(void);
//static ON_OFF_TYPE ArmSugar1Handler				(void);
//static ON_OFF_TYPE ArmSugar2Handler				(void);
//static ON_OFF_TYPE CoffeePresenceHandler		(void);
//static ON_OFF_TYPE Variflex1PresenceHandler		(void);
//static ON_OFF_TYPE Variflex1UpperHallHandler	(void);
//static ON_OFF_TYPE Variflex1BottomHallHandler	(void);
//static ON_OFF_TYPE Variflex1EncoderAHandler		(void);
//static ON_OFF_TYPE Variflex1EncoderBHandler		(void);
//static ON_OFF_TYPE Variflex2PresenceHandler		(void);
//static ON_OFF_TYPE Variflex2UpperHallHandler	(void);
//static ON_OFF_TYPE Variflex2BottomHallHandler	(void);
//static ON_OFF_TYPE Variflex2EncoderAHandler		(void);
//static ON_OFF_TYPE Variflex2EncoderBHandler		(void);
//static ON_OFF_TYPE DeepTrayPresenceHandler		(void);
//static ON_OFF_TYPE DeepTrayFullHandler			(void);
//static ON_OFF_TYPE DriversL99FaultHandler		(void);
//static ON_OFF_TYPE H2OLowBL1Handler				(void);
//static ON_OFF_TYPE H2OLowBL2Handler				(void);
//
//
//static DI_INTERFACE_TYPE DIInterface =
//{
//	.Canister1 			= &Canister1Handler,
//	.Canister2			= &Canister2Handler,
//	.Canister3			= &Canister3Handler,
//	.Canister4			= &Canister4Handler,
//	.Flowmeter			= &FlowmeterHandler,
//	.ArmSw1				= &ArmSw1Handler,
//	.ArmSW2				= &ArmSW2Handler,
//	.ArmSugar1			= &ArmSugar1Handler,
//	.ArmSugar2			= &ArmSugar2Handler,
//	.CoffeePresence		= &CoffeePresenceHandler,
//	.Variflex1Presence	= &Variflex1PresenceHandler,
//	.Variflex1UpperHall	= &Variflex1UpperHallHandler,
//	.Variflex1BottomHall= &Variflex1BottomHallHandler,
//	.Variflex1EncoderA	= &Variflex1EncoderAHandler,
//	.Variflex1EncoderB	= &Variflex1EncoderBHandler,
//	.Variflex2Presence	= &Variflex2PresenceHandler,
//	.Variflex2UpperHall	= &Variflex2UpperHallHandler,
//	.Variflex2BottomHall= &Variflex2BottomHallHandler,
//	.Variflex2EncoderA	= &Variflex2EncoderAHandler,
//	.Variflex2EncoderB	= &Variflex2EncoderBHandler,
//	.DeepTrayPresence	= &DeepTrayPresenceHandler,
//	.DeepTrayFull	 	= &DeepTrayFullHandler,
//	.DriversL99Fault	= &DriversL99FaultHandler,
//	.H2OLowBL1			= &H2OLowBL1Handler,
//	.H2OLowBL2			= &H2OLowBL2Handler,
//};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

/**
  * @brief  Digital Input interface
  * @param  None
  * @retval Digital Input interface methods
  */
//DI_INTERFACE_TYPE DI__Interface(void)
//{
//	return (DIInterface);
//}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief		This function manage Canister1 Digital Input
  *
  * @param		None
  * @retval		ON = Canister1 = 1; OFF = Canister1 = 0
  */
//static ON_OFF_TYPE Canister1Handler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_CNS1_GPIO_Port, DI_CNS1_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Canister2 Digital Input
  *
  * @param		None
  * @retval		ON: Canister2 = 1; OFF: Canister2 = 0
  */
//static ON_OFF_TYPE Canister2Handler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_CNS2_GPIO_Port, DI_CNS2_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Canister3 Digital Input
  *
  * @param		None
  * @retval		ON: Canister3 = 1; OFF: Canister3 = 0
  */
//static ON_OFF_TYPE Canister3Handler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_CNS3_GPIO_Port, DI_CNS3_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Canister4 Digital Input
  *
  * @param		None
  * @retval		ON: Canister4 pin = 1; OFF: Canister4 pin = 0
  */
//static ON_OFF_TYPE Canister4Handler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_CNS4_GPIO_Port, DI_CNS4_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Flowmeter Digital Input
  *
  * @param		None
  * @retval		ON: Flowmeter pin = 1; OFF: Flowmeter pin = 0
  */
//static ON_OFF_TYPE FlowmeterHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_EXTI7_FLOWMETER_GPIO_Port, DI_EXTI7_FLOWMETER_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Arm Switch1 Digital Input
  *
  * @param		None
  * @retval		ON: Arm Switch1 pin = 1; OFF: Arm Switch1 pin = 0
  */
//static ON_OFF_TYPE ArmSw1Handler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_ARM_SW1_GPIO_Port, DI_ARM_SW1_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Arm Switch2 Digital Input
  *
  * @param		None
  * @retval		ON: Arm Switch2 pin = 1; OFF: Arm Switch2 pin = 0
  */
//static ON_OFF_TYPE ArmSW2Handler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_ARM_SW2_GPIO_Port, DI_ARM_SW2_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Arm Sugar1 Digital Input
  *
  * @param		None
  * @retval		ON: Arm Sugar1 pin = 1; OFF: Arm Sugar1 pin = 0
  */
//static ON_OFF_TYPE ArmSugar1Handler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_ARM_SUGAR1_GPIO_Port, DI_ARM_SUGAR1_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Arm Sugar2 Digital Input
  *
  * @param		None
  * @retval		ON: Arm Sugar2 pin = 1; OFF: Arm Sugar2 pin = 0
  */
//static ON_OFF_TYPE ArmSugar2Handler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_ARM_SUGAR2_GPIO_Port, DI_ARM_SUGAR2_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Coffee Presence Digital Input
  *
  * @param		None
  * @retval		ON: Coffee Presence pin = 1; OFF: Coffee Presence pin = 0
  */
//static ON_OFF_TYPE CoffeePresenceHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_CF1_PRES_GPIO_Port, DI_CF1_PRES_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Variflex1 Presence Digital Input
  *
  * @param		None
  * @retval		ON: Variflex1 Presence pin = 1; OFF: Variflex1 Presence pin = 0
  */
//static ON_OFF_TYPE Variflex1PresenceHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_VF1_PRES_GPIO_Port, DI_VF1_PRES_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Variflex1 upper Hall sensor Digital Input
  *
  * @param		None
  * @retval		ON: Variflex1 upper Hall sensor pin = 1; OFF: Variflex1 upper Hall sensor pin = 0
  */
//static ON_OFF_TYPE Variflex1UpperHallHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_VF1_UPPER_HALL_GPIO_Port, DI_VF1_UPPER_HALL_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Variflex1 bottom Hall sensor Digital Input
  *
  * @param		None
  * @retval		ON: Variflex1 bottom Hall sensor pin = 1; OFF: Variflex1 bottom Hall sensor pin = 0
  */
//static ON_OFF_TYPE Variflex1BottomHallHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_VF1_BOTTOM_HALL_GPIO_Port, DI_VF1_BOTTOM_HALL_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Variflex1 Encoder A Digital Input
  *
  * @param		None
  * @retval		ON: Variflex1 Encoder A pin = 1; OFF: Variflex1 Encoder A pin = 0
  */
//static ON_OFF_TYPE Variflex1EncoderAHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(ENC1_VF1_TIM3_CH1_GPIO_Port, ENC1_VF1_TIM3_CH1_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Variflex1 Encoder B Digital Input
  *
  * @param		None
  * @retval		ON: Variflex1 Encoder B pin = 1; OFF: Variflex1 Encoder B pin = 0
  */
//static ON_OFF_TYPE Variflex1EncoderBHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(ENC2_VF1_TIM3_CH2_GPIO_Port, ENC2_VF1_TIM3_CH2_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Variflex2 Presence Digital Input
  *
  * @param		None
  * @retval		ON: Variflex2 Presence pin = 1; OFF: Variflex2 Presence pin = 0
  */
//static ON_OFF_TYPE Variflex2PresenceHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_VF2_PRES_GPIO_Port, DI_VF2_PRES_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Variflex2 upper Hall sensor Digital Input
  *
  * @param		None
  * @retval		ON: Variflex2 upper Hall sensor pin = 1; OFF: Variflex2 upper Hall sensor pin = 0
  */
//static ON_OFF_TYPE Variflex2UpperHallHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_VF2_UPPER_HALL_GPIO_Port, DI_VF2_UPPER_HALL_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Variflex2 bottom Hall sensor Digital Input
  *
  * @param		None
  * @retval		ON: Variflex2 bottom Hall sensor pin = 1; OFF: Variflex2 bottom Hall sensor pin = 0
  */
//static ON_OFF_TYPE Variflex2BottomHallHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_VF2_BOTTOM_HALL_GPIO_Port, DI_VF2_BOTTOM_HALL_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage  Variflex2 Encoder A Digital Input
  *
  * @param		None
  * @retval		ON: Variflex2 Encoder A pin = 1; OFF: Variflex2 Encoder A pin = 0
  */
//static ON_OFF_TYPE Variflex2EncoderAHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(ENC1_VF2_TIM2_CH1_GPIO_Port, ENC1_VF2_TIM2_CH1_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Variflex2 Encoder B Digital Input
  *
  * @param		None
  * @retval		ON: Variflex2 Encoder B pin = 1; OFF: Variflex2 Encoder B pin = 0
  */
//static ON_OFF_TYPE Variflex2EncoderBHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(ENC2_VF2_TIM2_CH2_GPIO_Port, ENC2_VF2_TIM2_CH2_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage DeepTray Presence Digital Input
  *
  * @param		None
  * @retval		ON: DeepTray Presence pin = 1; OFF: DeepTray Presence pin = 0
  */
//static ON_OFF_TYPE DeepTrayPresenceHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_DEEP_TRAY_PRESENCE_GPIO_Port, DI_DEEP_TRAY_PRESENCE_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage DeepTray Full Digital Input
  *
  * @param		None
  * @retval		ON: DeepTray Full pin = 1; OFF: DeepTray Full pin = 0
  */
//static ON_OFF_TYPE DeepTrayFullHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_DEEP_TRAY_FULL_GPIO_Port, DI_DEEP_TRAY_FULL_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage Drivers L99 Fault Digital Input
  *
  * @param		None
  * @retval		ON: Drivers L99 Fault pin = 1; OFF: Drivers L99 Fault pin = 0
  */
//static ON_OFF_TYPE DriversL99FaultHandler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_EXTI8_DRV_FLTn_GPIO_Port, DI_EXTI8_DRV_FLTn_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage H2O Low Level in Boiler1 Digital Input
  *
  * @param		None
  * @retval		ON: H2O Low Level in Boiler1 pin = 1; OFF: H2O Low Level in Boiler1 pin = 0
  */
//static ON_OFF_TYPE H2OLowBL1Handler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_H2O_LOW_BL1_GPIO_Port, DI_H2O_LOW_BL1_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}

/**
  * @brief		This function manage H2O Low Level in Boiler2 Digital Input
  *
  * @param		None
  * @retval		ON: H2O Low Level in Boiler2 pin = 1; OFF: H2O Low Level in Boiler2 pin = 0
  */
//static ON_OFF_TYPE H2OLowBL2Handler(void)
//{
//	ON_OFF_TYPE retVal;
//
//	if(HAL_GPIO_ReadPin(DI_H2O_LOW_BL2_GPIO_Port, DI_H2O_LOW_BL2_Pin) == GPIO_PIN_SET)
//	{
//		retVal = ON;
//	}
//	else
//	{
//		retVal = OFF;
//	}
//
//	return (retVal);
//}
