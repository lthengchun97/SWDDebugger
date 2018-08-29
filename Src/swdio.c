/*
 * swdio.c
 *
 *  Created on: 15 Aug 2018
 *      Author: Asus
 */

#include "swdio.h"
#include <stdint.h>

//uint32_t *data=0;

void swdWriteBit(uint32_t bit){
	if(bit==1){
		setSwdioHigh();
	}
	else{
		setSwdioLow();
	}
	setClockHigh();
	swdDelay();
	setClockLow();
	swdDelay();
}

int swdReadBit(){
	int bit=0	;
	setClockHigh();
	swdDelay();
	setClockLow();
	swdDelay();
	bit =getSwdio();
	return bit;
}

void swdWriteBits(uint32_t data,int bitsize){
	int i;
	uint32_t bit;
	for(i=0;i<bitsize;i++){
		bit = (data >>i)&0x01;
		swdWriteBit(bit);
	}
}

void swdReadBits(int bitsize,uint32_t *dataRead){
	int i,bit;
	*dataRead = 0;
	//uint32_t bit=0,data=0;
	for(i=0;i< bitsize;i++){
		bit = swdReadBit();
		*dataRead =*dataRead| (bit<<i);
	}
}

void swdReadAck(int *dataRead){
	swdReadBits(3,(uint32_t *)dataRead);
}

void swdRead32Bits(uint32_t *dataRead){
	 swdReadBits(32,dataRead);
}

void lineReset(){
	int i;
	setSwdioHigh();
	for(i=0;i<54;i++)
	{
		idleClock();
	}
}

int computeParityBit (uint32_t data){
	data ^= data >>16;
	data ^= data >> 8;
	data ^= data >> 4;
	data ^= data >> 2;
	data ^= data >> 1;
	return (~data) &1;
}

void swdWrite32BitsWithParity(uint32_t *data){
	swdWriteBits(data,32);
	swdWriteBits(computeParityBit(data),1);
}

void swdRead32BitsWithParity(uint32_t *data){
	//int actualParity;
	swdRead32Bits(data);
	swdReadBit();
	//actualParity = calculateParity32bitData(data);
}

int calculateReadParity(uint32_t data)
{
	int i , sum = 0;

	for (i = 0 ; i < 32 ; i ++)
	{
		if (data & 0x01)
			sum ++ ;

		data = data >> 1;
	}

	if (sum & 1)
		return 1 ;
	else
		return 0 ;
}


SwdStatus SwdApDpRequest(uint8_t request,uint32_t *data){
	int ack=0;
	*data = 0;
	swdWriteBits(request,8);
	swdReadTurnAround();
	swdReadAck(&ack);
	if(ack == SW_ACK_OK){
	if (request & 0x04){
		swdWriteTurnAround();
		swdWrite32BitsWithParity(data);
		}
	else
		{
		swdRead32BitsWithParity(data);
		swdWriteTurnAround();
		}
	}
	swdWriteBits(0,3);
}

void readAPIDCode(){
	SwdApDpRequest(DP_WR_CTRL_STAT,0x5000);
}



uint32_t readMcuRegister(uint32_t regNum){
	uint32_t *data;
	//set 32-bit access in AP_CSW
	setCSW32Bits();
	//write DCRSR to AP_TAR
	writeDCRSRtoTAR();
	//write regNum to AP_DRW
	writeRegNumtoDRW(regNum);
	//write DCRDR to AP_TAR
	writeDCRDRtoTAR();

	//read AP_DRW
	SwdApDpRequest(AP_RD_DRW,&data);
	//read DP_RDBUFF
	SwdApDpRequest(DP_RD_BUFF,&data);

	//return value read
	return *data;
}

void writeMcuRegister(uint32_t regNum, uint32_t data){
	//set 32-bit access in AP_CSW
	setCSW32Bits();
	//write DCRDR to AP_TAR
	writeDCRDRtoTAR();
	//write data to AP_DRW
	writeDatatoDRW(data);
	//write DCRSR to AP_TAR
	writeDCRSRtoTAR();
	//write (regNum | regWriteBit) to AP_DRW
}

void setCSW32Bits(){
	SwdApDpRequest(AP_WR_CSW,0);		// select bank 0
	SwdApDpRequest(AP_WR_CSW,BITS_32_WIDE);
}

void writeDCRSRtoTAR(){
	SwdApDpRequest(AP_WR_TAR,0);		// select bank 0
	SwdApDpRequest(AP_WR_TAR,DCRSR);
}

void writeRegNumtoDRW(uint32_t regNum){
	SwdApDpRequest(AP_WR_DRW,0);		// select bank 0
	SwdApDpRequest(AP_WR_DRW,regNum);
}

void writeDCRDRtoTAR(){
	SwdApDpRequest(AP_WR_TAR,0);		// select bank 0
	SwdApDpRequest(AP_WR_TAR,DCRDR);
}

void writeDatatoDRW(uint32_t data){
	SwdApDpRequest(AP_WR_DRW,0);		// select bank 0
	SwdApDpRequest(AP_WR_DRW,data);
}
