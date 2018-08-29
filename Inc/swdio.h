/*
 * swdio.h
 *
 *  Created on: 15 Aug 2018
 *      Author: Asus
 */

#ifndef SWDIO_H_
#define SWDIO_H_

#include "stdint.h"
#include "stdio.h"
#include "swdioHardware.h"

typedef unsigned char SwdStatus;


#define	SW_EQ_CODE				(0xe79e)
#define DP_RD_IDCODE			(0x85)
#define DP_WR_ABORT				(0xA1)
#define DP_RD_CTRL_STAT			(0xB5)
#define DP_WR_CTRL_STAT			(0x91)
#define DP_RD_RESEND			(0xAD)
#define DP_WR_SELECT			(0x89)
#define DP_RD_BUFF				(0x9D)

#define AP_WR_CSW				(0x83)
#define	AP_WR_TAR				(0xB3)
#define AP_WR_DRW				(0xAB)
#define AP_RD_DRW				(0x97)



#define DCRSR					0xe000edf4
#define DCRDR					0xe000edf8


#define SW_ACK_OK               0x1
#define SW_ACK_WAIT             0x2
#define SW_ACK_FAULT            0x4
#define SW_ACK_PARITY_ERR       0x8

#define BITS_32_WIDE			2

#define	SW_CLK_H				1
#define	SW_CLK_L				0
#define	SW_IO_H					1
#define	SW_IO_L					0
#define SWDCLK_Pin				((uint16_t)0x4000)
#define	SWDIO_Pin				((uint16_t)0x0100)
#define CLOCK_SPD				100



void swdWriteBit(uint32_t bit);
void swdWriteBits(uint32_t data,int bitsize);
void swdReadBits(int bitsize,uint32_t *dataRead);
SwdStatus SwdApDpRequest(uint8_t request,uint32_t *data);
void setSwdio(uint32_t data,int bitsize);
int computeParityBit (uint32_t data);
int computeParity(uint32_t data);
void swdWrite32BitsWithParity(uint32_t *data);
void swdReadAck(int *dataRead);
void swdRead32Bits(uint32_t *dataRead);
void lineReset();
int calculateReadParity(uint32_t data);
void swdRead32BitsWithParity(uint32_t *data);
uint32_t readMcuRegister(uint32_t regNum);
void writeMcuRegister(uint32_t regNum, uint32_t data);
void setCSW32Bits();
void writeDCRSRtoTAR();
void writeDCRDRtoTAR();
void writeRegNumtoDRW(uint32_t regNum);
void writeDatatoDRW(uint32_t data);


#endif /* SWDIO_H_ */
