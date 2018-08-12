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
#include "stdio.h"


#define TRUE 	1
#define FALSE 	0

#define debug_addr	((debug *)(GPIOA_BASE_ADDR))

typedef struct debug debug;
struct debug {
	volatile uint32_t data;
};



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

// ARM CoreSight SW-DP packet acknowledge values
#define SW_ACK_OK               0x1
#define SW_ACK_WAIT             0x2
#define SW_ACK_FAULT            0x4
#define SW_ACK_PARITY_ERR       0x8

// Command Status Response Codes
#define HOST_COMMAND_OK         0x55
#define HOST_INVALID_COMMAND    0x80
#define HOST_COMMAND_FAILED     0x81
#define HOST_AP_TIMEOUT         0x82
#define HOST_WIRE_ERROR         0x83
#define HOST_ACK_FAULT          0x84
#define HOST_DP_NOT_CONNECTED   0x85

// ARM CoreSight DAP command masks
#define DAP_CMD_PACKED          0x80
#define DAP_CMD_A32             0x0C
#define DAP_CMD_RnW             0x02
#define DAP_CMD_APnDP           0x01
#define DAP_CMD_MASK            0x0F

// ARM CoreSight SW-DP packet request masks
#define SW_REQ_PARK_START       0x81
#define SW_REQ_PARITY           0x20
#define SW_REQ_A32              0x18
#define SW_REQ_RnW              0x04
#define SW_REQ_APnDP            0x02


void swdLineReset();
void idleCycles(int time);
void swdWriteBits(uint32_t data, int bitsize);
uint32_t swdReadBits(int bitsize,uint32_t *data);
void writeTurnAround();
void readTurnAround();
void resetDebugPin();
uint8_t SW_ShiftPacket(uint8_t request, uint8_t retry,uint32_t writeDat);
uint32_t tarWriteandReadAccess(uint32_t addr,uint32_t data);
uint32_t tarReadAccess(uint32_t addr);
uint32_t swdReadWord(uint32_t addr);
uint8_t SW_Request(uint8_t addr);

#endif /* DEBUG_H_ */
