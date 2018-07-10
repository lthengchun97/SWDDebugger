/*
 * debug.h
 *
 *  Created on: 13 Jun 2018
 *      Author: Lee Theng Chun
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include"stdint.h"
#include "stm32f1xx_hal.h"
#include "main.h"

#define TRUE 	1
#define FALSE 	0

#define SW_EQ_IDCODE			0xEE2005DC
#define	SW_EQ_CODE				(0xe79e)
#define SW_IDCODE_RD            0xA5
#define SW_STATUS_FLG			0xAD

#define START_EN				(1)
#define AP_EN					(1<<1)
#define	DP_EN					(0<<1)
#define WR_EN					(0<<2)
#define	RD_EN					(1<<2)
#define AddrField(x)			(x<<3)
#define	Odd_Parity				(0<<5)
#define	Even_Parity				(1<<5)
#define	STOP_BIT				(0<<6)
#define	PARK_BIT				(1<<7)

#define SW_ACK_OK               0x1
#define SW_ACK_WAIT             0x2
#define SW_ACK_FAULT            0x4
#define SW_ACK_PARITY_ERR       0x8

#define	SW_CLK_H				1
#define	SW_CLK_L				0
#define	SW_IO_H					1
#define	SW_IO_L					0
#define SWDCLK_Pin				((uint16_t)0x4000)
#define	SWDIO_Pin				((uint16_t)0x0100)
#define CLOCK_SPD				100

//Configure pin as output/input/open drain

#define	_swdAsOuput()					\
		do{								\
			GPIO_InitTypeDef GPIO_InitStruct;	\
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);	\
			GPIO_InitStruct.Pin = GPIO_PIN_8;	\
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;	\
			GPIO_InitStruct.Pull = GPIO_PULLUP;	\
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; \
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);		\
		}while (0)

#define	_swdAsInput()					\
		do{								\
			GPIO_InitTypeDef GPIO_InitStruct;	\
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);	\
			GPIO_InitStruct.Pin = GPIO_PIN_8;	\
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;	\
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;	\
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; \
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);		\
		}while (0)

#define	_swdAsOuputOpenDrain()					\
		do{								\
			GPIO_InitTypeDef GPIO_InitStruct;	\
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);	\
			GPIO_InitStruct.Pin = GPIO_PIN_8;	\
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;	\
			GPIO_InitStruct.Pull = GPIO_PULLUP;	\
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; \
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);		\
		}while (0)

void swdLineReset();
void idleCycles(int time);
void swdWriteBits(uint32_t data, int bitsize);
uint32_t swdReadBits(int bitsize);
void writeTurnAround();
void readTurnAround();
void resetDebugPin();
uint8_t SW_ShiftPacket(uint8_t request, uint8_t retry,uint32_t writeDat);

#endif /* DEBUG_H_ */
