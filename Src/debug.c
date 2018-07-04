/*
 * debug.c
 *
 *  Created on: 13 Jun 2018
 *      Author: Lee Theng Chun
 */
#include "debug.h"
//#include "main.h"
#include <stdint.h>

uint8_t ack_err;
uint32_t readData;

void idleCycles(int time){
	// pin2 stands for SWCLK pin (pin 14 port B)
	int i;
	for(i=0;i<time;i++){
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
}

void swdLineReset(){
	// pin1 stands for SWDIO pin (pin 8 port A)
	// pin2 stands for SWCLK pin (pin 14 port B)
	int i;
	HAL_GPIO_WritePin(GPIOA, SWDIO_Pin, SW_IO_H);
	for(i=0;i<64;i++)
	{
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
}


void swdWriteBits(uint32_t data, int bitsize){
	int i;
	for(i=0;i<bitsize;i++){
		HAL_GPIO_WritePin(GPIOA,SWDIO_Pin,(data >> i) & 0x01);
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
}

uint32_t swdReadBits(int bitsize){
	int i;
	uint32_t swiftBytes[bitsize];
	for(i=0;i<bitsize;i++){
		swiftBytes[i] = HAL_GPIO_ReadPin(GPIOA,(SWDIO_Pin >> i) & 0x01);
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_L);
		HAL_Delay(CLOCK_SPD);
		HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_H);
		HAL_Delay(CLOCK_SPD);
	}
	return *swiftBytes;
}

void resetDebugPin(){
	_swdAsOuputOpenDrain();
}

void readTurnAround(){
	int i;
	HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 0);
	HAL_Delay(CLOCK_SPD);
	HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 1);
	HAL_Delay(CLOCK_SPD);

	_swdAsInput();

	for(i=0;i<1;i++)
		{
			HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_L);
			HAL_Delay(CLOCK_SPD);
			HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_H);
			HAL_Delay(CLOCK_SPD);
		}
}

void writeTurnAround(){

	int i;
	HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 0);
	HAL_Delay(CLOCK_SPD);
	HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, 1);
	HAL_Delay(CLOCK_SPD);

	_swdAsOuput();

	for(i=0;i<1;i++)
		{
			HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_L);
			HAL_Delay(CLOCK_SPD);
			HAL_GPIO_WritePin(GPIOB, SWDCLK_Pin, SW_CLK_H);
			HAL_Delay(CLOCK_SPD);
		}

}

uint8_t SW_ShiftPacket(uint8_t request, uint8_t retry)
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
        HAL_GPIO_WritePin(GPIOA, SWDIO_Pin, SW_IO_L);
        _swdAsOuput();
        idleCycles(1);

        // Shift out the 8-bit packet request
        swdWriteBits(request,8);

        // Turnaround cycle makes SWDIO an input
        _swdAsInput();
        idleCycles(1);

        // Shift in the 3-bit acknowledge response
        //swdReadBits(32);
        io_b1 = HAL_GPIO_ReadPin(GPIOA, (SWDIO_Pin));
        idleCycles(1);
        io_b2 = HAL_GPIO_ReadPin(GPIOA, (SWDIO_Pin >> 1) & 0x01);
        idleCycles(1);
        io_b3 = HAL_GPIO_ReadPin(GPIOA, (SWDIO_Pin >> 2) & 0x01);
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
        	_swdAsOuput();
        	idleCycles(1);
        	swdWriteBits(SW_EQ_IDCODE, 32);
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
            swdWriteBits(SW_EQ_IDCODE, 32);

            // Shift out the parity bit
            //SWDIO_Out = SW_CalcDataParity(); _StrobeSWCLK;
        }
    }
    // TODO: Add error (FAULT, line, parity) handling here?  RESEND on parity error?

    // Turnaround or idle cycle, always leave SWDIO an output
    HAL_GPIO_WritePin(GPIOA, SWDIO_Pin, SW_IO_L);
    _swdAsOuput();
    idleCycles(1);

    // Update the global error accumulator if there was an error
    if (ack != SW_ACK_OK)
    {
    	ack_err = ack;
    }
    return ack;
}


