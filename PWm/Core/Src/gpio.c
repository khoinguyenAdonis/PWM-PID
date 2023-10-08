/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
#define SET_START_L298() 				do{HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10, 1);}while(0);
#define OFF_DC_MOTOR()					do{HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10, 0);}while(0);
uint8_t D_Set = 0;
uint8_t V_Set = 0;
int current_mode = 0;
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pins : PCPin PC5 */
  GPIO_InitStruct.Pin = V_Set_Pin|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PE10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ON_OFF_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ON_OFF_DC_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 2 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_5) // d_set+
	{
		V_Set -= 50;
		for(int x = 500000; x>0; x--);
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
		HAL_NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
		//if (D_Set > 10) D_Set = 0;
	}
	if(GPIO_Pin == V_Set_Pin) // v_set
	{
		V_Set += 5;
		for(int x = 500000; x>0; x--);
		__HAL_GPIO_EXTI_CLEAR_IT(V_Set_Pin);
		HAL_NVIC_ClearPendingIRQ(EXTI4_IRQn);
	}
	if (GPIO_Pin == ON_OFF_DC_Pin) { // on_off dc
		int on_off;
		if(on_off = 0)on_off = 1;
		else on_off =0 ;
		for(int x = 500000; x>0; x--);
		__HAL_GPIO_EXTI_CLEAR_IT(ON_OFF_DC_Pin);
		switch (on_off){
			case 1 :
				SET_START_L298() ;
				break;
			default :
				OFF_DC_MOTOR();
				break;
		}


	}


}
/* USER CODE END 2 */
