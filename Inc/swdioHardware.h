/*
 * swdioHardware.h
 *
 *  Created on: 15 Aug 2018
 *      Author: Asus
 */

#ifndef SWDIOHARDWARE_H_
#define SWDIOHARDWARE_H_

#include "stm32f1xx_hal.h"

#define	SW_CLK_H				1
#define	SW_CLK_L				0
#define	SW_IO_H					1
#define	SW_IO_L					0
#define SWDCLK_Pin				((uint16_t)0x4000)
#define	SWDIO_Pin				((uint16_t)0x0100)
#define CLOCK_SPD				100

int getSwdio();
void setSwdioHigh();
void setSwdioLow();
void setClockHigh();
void setClockLow();
//void setSwdio(uint32_t data,int bitsize);
//uint32_t swdReadBitsHardware(int bitsize,uint32_t *data);
void swdReadTurnAround();
void swdWriteTurnAround();
void idleClock();
void swdDelay();


#endif /* SWDIOHARDWARE_H_ */
