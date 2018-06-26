/*
 * debug.c
 *
 *  Created on: 13 Jun 2018
 *      Author: Lee Theng Chun
 */
#include "debug.h"
#include "main.h"
#include <stdint.h>

void swdClock(uint16_t pin2){
	// pin2 stands for SWCLK pin (pin 14 port B)
	HAL_GPIO_WritePin(GPIOB, pin2, 0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB, pin2, 1);
	HAL_Delay(100);
}

void swdLineReset(uint16_t pin1,uint16_t pin2){
	// pin1 stands for SWDIO pin (pin 8 port A)
	// pin2 stands for SWCLK pin (pin 14 port B)
	int i;
	HAL_GPIO_WritePin(GPIOA, pin1, 1);
	for(i=0;i<56;i++)
	{
		HAL_GPIO_WritePin(GPIOB, pin2, 0);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOB, pin2, 1);
		HAL_Delay(100);
	}
}

void jtagToSWDSwSeq(GPIO_TypeDef *GPIOx,uint16_t pin1,uint16_t pin2){
	// pin1 stands for SWDIO pin (pin 8 port A)
	// pin2 stands for SWCLK pin (pin 14 port B)
	//GPIOA->ODR = 0xe79e;
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);

	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,1);

	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);

	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);
}

void swdSendBit(uint16_t pin1,uint16_t pin2,int highOrLow){
	// pin1 stands for SWDIO pin (pin 8 port A)
	// pin2 stands for SWCLK pin (pin 14 port B)
	int counter =0;
	for(int i =0 ; i <2 ; i++)
	{
	if(counter == 1)
	{
		HAL_GPIO_WritePin(GPIOA, pin1, highOrLow);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, pin2, 0);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOB, pin2, 1);
		HAL_Delay(100);
		counter = 1;
	}
	}

}

void turnAround(){
	GPIO_InitTypeDef GPIO_InitStruct;
	int i;

	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
	HAL_Delay(100);

	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	for(i=0;i<1;i++)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
			HAL_Delay(100);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
			HAL_Delay(100);
		}

	returnIDcode(GPIOA,GPIO_PIN_8,GPIO_PIN_14);

}

void returnIDcode(GPIO_TypeDef *GPIOx,uint16_t pin1,uint16_t pin2){
	int i;
	GPIO_InitTypeDef GPIO_InitStruct;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,0);

	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);

	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);

	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);

	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,0);

	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,0);

	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,1);

	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,1);

	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,0);
}

void readIDCode(GPIO_TypeDef *GPIOx,uint16_t pin1,uint16_t pin2){
	// pin1 stands for SWDIO pin (pin 8 port A)
	// pin2 stands for SWCLK pin (pin 14 port B)
	//GPIOA->ODR = 0xA5;
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);

	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,1);
	swdSendBit(pin1,pin2,0);
	swdSendBit(pin1,pin2,1);
}
