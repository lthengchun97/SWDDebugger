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

#define	SW_EQ			(0xe79e)
#define START_EN		(1)
#define AP_EN			(1<<1)
#define	DP_EN			(0<<1)
#define WR_EN			(0<<2)
#define	RD_EN			(1<<2)
#define AddrField(x)	(x<<3)
#define	Odd_Parity		(0<<5)
#define	Even_Parity		(1<<5)
#define	STOP_BIT		(0<<6)
#define	PARK_BIT		(1<<7)
#define	SW_CLK_H		1
#define	SW_CLK_L		0
#define	SW_IO_H			1
#define	SW_IO_L			0
#define SWDCLK_Pin		((uint16_t)0x4000)
#define	SWDIO_Pin		((uint16_t)0x0100)
#define CLOCK_SPD		100




void swdLineReset();
void swdClock(uint16_t pin2);
void swdWriteBits(uint32_t data, int bitsize);
uint32_t* swdReadBits(int bitsize);
void writeTurnAround();
void readTurnAround();


#endif /* DEBUG_H_ */
