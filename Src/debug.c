/*
 * debug.c
 *
 *  Created on: 13 Jun 2018
 *      Author: Lee Theng Chun
 */
#include "debug.h"
#include "mockFunction.h"
#include "main.h"
#include <stdint.h>

uint8_t ack_err;
uint32_t readData,io_word;
uint8_t	iob_0;

typedef unsigned char STATUS;

const uint8_t even_parity[] =
{
    0x00, 0x10, 0x10, 0x00,
    0x10, 0x00, 0x00, 0x10,
    0x10, 0x00, 0x00, 0x10,
    0x00, 0x10, 0x10, 0x00
};

void idleCycles(int time){
	// pin2 stands for SWCLK pin (pin 14 port B)
	int i;
	for(i=0;i<time;i++){
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
}

void swdLineReset(){
	// pin1 stands for SWDIO pin (pin 8 port A)
	// pin2 stands for SWCLK pin (pin 14 port B)
	int i;
	HAL_GPIO_WritePin(SWD_IO_PORT, SWDIO_Pin, SW_IO_H);
	for(i=0;i<64;i++)
	{
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
}


void swdWriteBits1(uint32_t data, int bitsize){
	int i;
	for(i=0;i<bitsize;i++){
		//swdWriteIO(1);
		HAL_GPIO_WritePin(SWD_IO_PORT,SWDIO_Pin,(data >> i) & 0x01);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
}

void swdWriteBitsmock(uint32_t data,int bitsize){
	int i;
	//uint32_t data1=0;
	for(i=0;i<bitsize;i++){
		//swdWriteIO(1);
		//HAL_GPIO_WritePin(SWD_IO_PORT,SWDIO_Pin,(data >> i) & 0x01);
		//data1 = data1 | (HAL_GPIO_ReadPin(GPIOA,(data>> i)&0x01)>>i);
		//swdWriteClk(1);
		//HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		//swdWriteClk(1);
		//HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
}



uint32_t swdReadBits1(int bitsize,uint32_t *data){
	int i;
	uint32_t swiftBytes=0;
	for(i=bitsize;i<=0;i--){
		//*data = SW_EQ_IDCODE;
		*data |= (HAL_GPIO_ReadPin(SWD_IO_PORT,SWDIO_Pin)>>bitsize);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
	}
	return swiftBytes;
}

void resetDebugPin(){
	_swdAsOuputOpenDrain();
}

void readTurnAround(){
	int i;
	HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
	HAL_Delay(CLOCK_SPD);
	HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
	HAL_Delay(CLOCK_SPD);

	_swdAsInput();

	for(i=0;i<1;i++)
		{
			HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
			HAL_Delay(CLOCK_SPD);
			HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
			HAL_Delay(CLOCK_SPD);
		}
}

void writeTurnAround(){

	int i;
	HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, 0);
	HAL_Delay(CLOCK_SPD);
	HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, 1);
	HAL_Delay(CLOCK_SPD);

	_swdAsOuput();

	for(i=0;i<1;i++)
		{
			HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
			HAL_Delay(CLOCK_SPD);
			HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
			HAL_Delay(CLOCK_SPD);
		}

}

uint8_t SW_ShiftPacket(uint8_t request, uint8_t retry,uint32_t writeDat)
{
	uint8_t ack, limit,i, io_b1,io_b2,io_b3,io_byte,iob_0;

    // If retry parameter is zero, use the default value instead
    if (retry == 0)
    {
        retry = 255;
    }
    limit = retry;

    // While waiting, do request phase (8-bit request, turnaround, 3-bit ack)
    do
    {
        // Turnaround or idle cycle, makes or keeps SWDIO an output
        HAL_GPIO_WritePin(SWD_IO_PORT, SWDIO_Pin, SW_IO_L);
        _swdAsOuput();
        idleCycles(1);


        // Shift out the 8-bit packet request
        swdWriteBits(request,8);

        // Turnaround cycle makes SWDIO an input
        _swdAsInput();
        idleCycles(1);

        // Shift in the 3-bit acknowledge response
        //swdReadBits(32);
        io_b1 = HAL_GPIO_ReadPin(SWD_IO_PORT, (SWDIO_Pin));
        idleCycles(1);
        io_b2 = HAL_GPIO_ReadPin(SWD_IO_PORT, (SWDIO_Pin >> 1) & 0x01);
        idleCycles(1);
        io_b3 = HAL_GPIO_ReadPin(SWD_IO_PORT, (SWDIO_Pin >> 2) & 0x01);
        idleCycles(1);
        io_byte = io_b1 | io_b2 | io_b3;
        ack = io_byte;
        //_swdAsOuput();
        //swdWriteBits(ack,3);

        // Check if we need to retry the request
        if ((ack == SW_ACK_WAIT) && --retry)
        {
            // Delay an increasing amount with each retry
            for (i=retry; i < limit; i++);
        }
        else
        {
            break;  // Request phase complete (or timeout)
        }
    }
    while (TRUE);

    // If the request was accepted, do the data transfer phase (turnaround if
    // writing, 32-bit data, and parity)
    if (ack == SW_ACK_OK)
    {
        if (request & 0x04)
        {
            // Swap endian order while shifting in 32-bits of data
        	//_swdAsOuput();
        	idleCycles(1);

        	//swdWriteBits(SW_EQ_IDCODE, 32);
        	HAL_GPIO_WritePin(SWD_IO_PORT, SWDCLK_Pin, SW_CLK_H);
        	//readData = swdReadBits(32);

            // Shift in the parity bit
            //iob_0 = swdReadBits(1);

            // Check for parity error
            //if (iob_0 ^ SW_CalcDataParity())
           // {
                //ack = SW_ACK_PARITY_ERR;
           // }
        }
        else
        {
            // Turnaround cycle makes SWDIO an output
            _swdAsOuput();
            idleCycles(1);
            // Swap endian order while shifting out 32-bits of data
            swdWriteBits(writeDat, 32);

            // Shift out the parity bit
            //SWDIO_Out = SW_CalcDataParity(); _StrobeSWCLK;
        }
    }

    // Turnaround or idle cycle, always leave SWDIO an output
    HAL_GPIO_WritePin(SWD_IO_PORT, SWDIO_Pin, SW_IO_L);
    _swdAsOuput();
    idleCycles(1);

    // Update the global error accumulator if there was an error
    if (ack != SW_ACK_OK)
    {
    	ack_err = ack;
    }
    return ack;
}

uint8_t swdReadByte(uint32_t addr){
	int i;
	uint8_t returnValue[7];
	for(i = 0; i<8; i++)
	{
		//returnValue[i]=HAL_GPIO_ReadPin(GPIOA,(addr >> i) & 0x01);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
	return returnValue;
}

uint16_t swdReadHalfWord(uint32_t addr){
	int i;
	uint8_t returnValue[16];
	for(i = 0; i<16; i++)
	{
		//returnValue[i]=HAL_GPIO_ReadPin(GPIOA,(addr >> i) & 0x01);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
	return returnValue;
}

/*uint32_t swdReadWord(debug addr){
	int i;
	uint32_t returnValue;
	for(i = 0; i<32; i++)
	{
		//returnValue[i] = (addr->data >> i) & 0x01;
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
	return returnValue;
}*/

void swdWriteByte(uint32_t addr,uint8_t data){
	int i;
	for(i=0;i<8;i++){
		//HAL_GPIO_WritePin(GPIOA,SWDIO_Pin,(data >> i) & 0x01);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
}

void swdWriteHalfWord(uint32_t addr,uint16_t data){
	int i;
	for(i=0;i<16;i++){
		//HAL_GPIO_WritePin(GPIOA,SWDIO_Pin,(data >> i) & 0x01);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
}

void swdWriteWord(uint32_t addr,uint32_t data){
	int i;
	for(i=0;i<32;i++){
		//HAL_GPIO_WritePin(GPIOA,SWDIO_Pin,(data >> i) & 0x01);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(SWD_CLOCK_PORT, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
}

uint32_t tarWriteandReadAccess(uint32_t addr,uint32_t data){
	uint32_t value;
	// To access to the TAR register
	SW_ShiftPacket(0xAB,0,0x00000000);
	// Write the address to TAR register
	SW_ShiftPacket(0xAB,0,addr);
	// To access to the DRW register
	SW_ShiftPacket(0xAB,0,0x00000000);
	// Write the data to the DRW register
	SW_ShiftPacket(0xAB,0,data);
	// Read the value from the DRW register
	//value=swdReadWord(data);
	return value;
}

uint32_t tarReadAccess(uint32_t addr){
	uint32_t value;
	// To access to the TAR register
	SW_ShiftPacket(0xAB,0,0x00000000);
	// Write the address to TAR register
	SW_ShiftPacket(0xAB,0,addr);
	// To access to the DRW register
	SW_ShiftPacket(0xAB,0,0x00000000);
	// Read the value from the DRW register
	//value=swdReadWord(addr);
	return value;
}

uint8_t SW_computeParity(uint32_t data){
	uint8_t data_req;

	//data_req = data & 0x1E;
	data_req = __builtin_parityl(data_req);			// need try first
	data_req = data_req | even_parity[data_req];
	data_req = data_req << 1;
	data_req = data_req | SW_REQ_PARK_START;

	return data_req;
}

STATUS SW_Response(uint8_t sw_ack){
	switch(sw_ack)
	{
	case SW_ACK_OK : return HOST_COMMAND_OK;
	case SW_ACK_WAIT : return HOST_AP_TIMEOUT;
	case SW_ACK_FAULT : return HOST_ACK_FAULT;
	default : return HOST_WIRE_ERROR;
	}
}


