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
		swdRead32Bits(data);
		swdWriteTurnAround();
		}
	}
	swdWriteBits(0,3);
}
