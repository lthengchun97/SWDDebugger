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

void swdLineReset(){
	// pin1 stands for SWDIO pin (pin 8 port A)
	// pin2 stands for SWCLK pin (pin 14 port B)
	int i;
	HAL_GPIO_WritePin(GPIOA, SWDIO_Pin, 1);
	for(i=0;i<56;i++)
	{
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 0);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 1);
		HAL_Delay(100);
	}
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


void swdWriteBits(uint32_t data, int bitsize){
	int i;
	for(i=0;i<bitsize;i++){
		HAL_GPIO_WritePin(GPIOA,SWDIO_Pin,(data >> i) & 0x01);
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 0);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 1);
		HAL_Delay(100);
	}
}

uint32_t* swdReadBits(int bitsize){
	int i;
	uint32_t swiftBytes[bitsize];
	for(i=0;i<bitsize;i++){
		swiftBytes[i] = HAL_GPIO_ReadPin(GPIOA,(SWDIO_Pin >> 3));
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 0);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 1);
		HAL_Delay(100);
	}
	return swiftBytes;
}

void readTurnAround(){
	GPIO_InitTypeDef GPIO_InitStruct;
	int i;

	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);

	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	for(i=0;i<1;i++)
		{
			HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 0);
			HAL_Delay(100);
			HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 1);
			HAL_Delay(100);
		}

}

uint32_t returnIDcode(GPIO_TypeDef *GPIOx,uint16_t pin1,uint16_t pin2){
	uint32_t bitread_MSB;
	GPIO_InitTypeDef GPIO_InitStruct;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
/*
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
*/
	GPIOA->ODR = 0x3BA0;
	GPIOA->ODR = 0x0477;

	//bitread_LSB = GPIOA->ODR << 15;
	bitread_MSB = GPIOA->ODR;
	//bitread=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);

	//swdSendBit(pin1,pin2,1);		//parity

	return bitread_MSB;
}
