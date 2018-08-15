/*
 * swdio.c
 *
 *  Created on: 15 Aug 2018
 *      Author: Asus
 */

#include "swdio.h"
#include <stdint.h>

uint32_t *data;

void swdWriteBit(uint32_t bit){
	if(bit==1){
		setSwdioHigh();
		setClockHigh();
		swdDelay();
		setClockLow();
		swdDelay();
	}
	else{
		setSwdioLow();
		setClockHigh();
		swdDelay();
		setClockLow();
		swdDelay();
	}
}

int swdReadBit(){
	int bit;
	bit =getSwdio();
	setClockHigh();
	swdDelay();
	setClockLow();
	swdDelay();
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

uint32_t swdReadBits(int bitsize){
	int i;
	uint32_t bit,data;
	for(i=bitsize;i>0;i--){
		bit = swdReadBit();
		data |= (bit<<bitsize);
	}
	return data;
}

uint32_t swdReadAck(){
	return swdReadBits(3);
}

void lineReset(){
	int i;
	setSwdioHigh();
	for(i=0;i<54;i++)
	{
		idleClock();
	}
}

int computeParity(uint32_t data){
	data = (data & 0x0000FFFF) ^ (data >>16);
	data = (data & 0x000000FF) ^ (data >> 8);
	data = (data & 0x0000000F) ^ (data >> 4);
	data = (data & 0x00000003) ^ (data >> 2);
	data = (data & 0x00000001) ^ (data >> 1);

	return data&1;
}

int computeParityBit (uint32_t data){
	data ^= data >>16;
	data ^= data >> 8;
	data ^= data >> 4;
	data ^= data >> 2;
	data ^= data >> 1;
	return (~data) &1;
}

void swdWrite32BitsWithParity(uint32_t data){
	swdWriteBits(data,32);
	swdWriteBits(computeParityBit(data),1);
}

SwdStatus SwdApDpRequest(uint8_t request,uint32_t *data){
	uint8_t ack;
	swdWriteBits(request,8);
	swdReadTurnAround();
	ack = swdReadAck();
	if(ack == SW_ACK_OK){
	if (request & 0x04){
		swdWriteTurnAround();
		swdWrite32BitsWithParity(data);
		}
	else
		{
		data = swdReadBits(32);
		swdWriteTurnAround();
		}
	}
	swdWriteBits(0,3);
}
