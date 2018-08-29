/*
 * swdioHardware.c
 *
 *  Created on: 15 Aug 2018
 *      Author: Asus
 */

#include "swdioHardware.h"

#define	_swdAsOuput()					\
		do{								\
			GPIO_InitTypeDef GPIO_InitStruct;	\
			HAL_GPIO_WritePin(SWD_IO_PORT, GPIO_PIN_8, GPIO_PIN_SET);	\
			GPIO_InitStruct.Pin = GPIO_PIN_8;	\
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;	\
			GPIO_InitStruct.Pull = GPIO_PULLUP;	\
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; \
			HAL_GPIO_Init(SWD_IO_PORT, &GPIO_InitStruct);		\
		}while (0)

#define	_swdAsInput()					\
		do{								\
			GPIO_InitTypeDef GPIO_InitStruct;	\
			HAL_GPIO_WritePin(SWD_IO_PORT, GPIO_PIN_8, GPIO_PIN_SET);	\
			GPIO_InitStruct.Pin = GPIO_PIN_8;	\
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;	\
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;	\
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; \
			HAL_GPIO_Init(SWD_IO_PORT, &GPIO_InitStruct);		\
		}while (0)

#define	_swdAsOuputOpenDrain()					\
		do{								\
			GPIO_InitTypeDef GPIO_InitStruct;	\
			HAL_GPIO_WritePin(SWD_IO_PORT, GPIO_PIN_8, GPIO_PIN_SET);	\
			GPIO_InitStruct.Pin = GPIO_PIN_8;	\
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;	\
			GPIO_InitStruct.Pull = GPIO_PULLUP;	\
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; \
			HAL_GPIO_Init(SWD_IO_PORT, &GPIO_InitStruct);		\
		}while (0)


int getSwdio(){
	return ((HAL_GPIO_ReadPin(SWD_IO_PORT, SWDIO_Pin)) ? 1 : 0);
	//return HAL_GPIO_ReadPin(SWD_IO_PORT,SWDIO_Pin);
}

void setSwdioHigh(){
	HAL_GPIO_WritePin(SWD_IO_PORT,SWDIO_Pin,1);
}

void setSwdioLow(){
	HAL_GPIO_WritePin(SWD_IO_PORT,SWDIO_Pin,0);
}

void setClockHigh(){
	HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
}

void setClockLow(){
	HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
}

void swdDelay(){
	HAL_Delay(CLOCK_SPD);
}

void swdReadTurnAround(){
	_swdAsInput();
	setClockHigh();
	swdDelay();
	setClockLow();
	swdDelay();
}

void swdWriteTurnAround(){
	setClockHigh();
	swdDelay();
	setClockLow();
	swdDelay();
	setClockHigh();
	swdDelay();
	_swdAsOuput();
}

void idleClock(){
	setClockHigh();
	swdDelay();
	setClockLow();
	swdDelay();
}
