/*
 * Rcc.c
 *
 *  Created on: 13 Jun 2018
 *      Author: Asus
 */

#include"Rcc.h"

uint32_t *rccAhb1Rst= (uint32_t *)(RCC_BASE_ADDR + RCC_AHB1RST_OFF);
uint32_t *rccAhb1En= (uint32_t *)(RCC_BASE_ADDR + RCC_AHB1EN_OFF);


void enableGpioA(void){
	//unreset GPIOG
	*rccAhb1Rst &= ~1;
	//Start clock of GPIOG
	*rccAhb1En |= 1;
}

void enableGpioB(void){
	//unreset GPIOG
	*rccAhb1Rst &= ~(1 << 1);
	//Start clock of GPIOG
	*rccAhb1En |= 1 << 1;
}

void enableGpioG(void){
	//unreset GPIOG
	*rccAhb1Rst &= ~(1 << 6);
	//Start clock of GPIOG
	*rccAhb1En |= 1 << 6;
}

void enableGpioC(void){
	//unreset GPIOG
	*rccAhb1Rst &= ~(1 << 2);
	//Start clock of GPIOG
	*rccAhb1En |= 1 << 2;
}

void enableRng(void){
	Rcc->AHB2RSTR &= ~(1<<6);
	Rcc->AHB2ENR |= (1<<6);
}

void enableTimer8(void){

	Rcc->APB2RSTR &= ~(1<<1);
	Rcc->APB2ENR |= (1 <<1) ;
}

void enableI2C1(void){

	//Unreset i2c1
	Rcc->APB1RSTR &= ~(1<21);
	Rcc->APB1ENR |= (1<<21);
}

void enableI2C2(void){
	//Unreset i2c2
	Rcc->APB1RSTR &= ~(1<22);
	Rcc->APB1ENR |= (1<<22);
}

void enableUART1(void){
	Rcc->APB2RSTR &= ~(1<<4);
	Rcc->APB2ENR |= (1<<4);
}


/*
 * Enable and clock DMA
 */
void enableDMA(int dmaNumber){
	Rcc->AHB1RSTR &= ~(1<<(21 + dmaNumber));
	Rcc->AHB1ENR |= (1<<(21+dmaNumber));
}

void enableADC1(void){
	Rcc->APB2ENR |= (1<<8);
	Rcc->APB2RSTR &= ~(1<<8);
}

void enableWWDG(void){
	Rcc->APB1RSTR &= ~(1<<11);
	Rcc->APB1ENR |= (1<<11);
}

void enableWWDGLP(void){
	Rcc->APB1LPENR |= (1<11);
}
