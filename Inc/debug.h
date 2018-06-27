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


void swdLineReset(uint16_t pin1,uint16_t pin2);
void jtagToSWDSwSeq(GPIO_TypeDef *GPIOx,uint16_t pin1,uint16_t pin2);
void readIDCode(GPIO_TypeDef *GPIOx,uint16_t pin1,uint16_t pin2);
void swdSendBit(uint16_t pin1,uint16_t pin2,int highOrLow);
void swdClock(uint16_t pin2);
void turnAround();
uint32_t returnIDcode(GPIO_TypeDef *GPIOx,uint16_t pin1,uint16_t pin2);


#endif /* DEBUG_H_ */
