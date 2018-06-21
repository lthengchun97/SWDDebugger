/*
 * Rcc.h
 *
 *  Created on: 13 Jun 2018
 *      Author: Asus
 */

#ifndef RCC_H_
#define RCC_H_

#include "stdint.h"
//#include "Common.h"

#define RCC_BASE_ADDR		0x40023800
#define RCC_AHB1RST_OFF		0x10
#define RCC_AHB1EN_OFF		0x30

#define Rcc 			((RccReg *)(RCC_BASE_ADDR))
//Export variable to other modules
extern uint32_t *rccAhb1Rst;
extern uint32_t *rccAhb1En;

typedef struct RccReg RccReg;
struct RccReg {
	volatile uint32_t CR;				//0x00
	volatile uint32_t PLLCFGR;			//0x04
	volatile uint32_t CFGR;				//0x08
	volatile uint32_t CIR;				//0x0c
	volatile uint32_t AHB1RSTR;			//0x10
	volatile uint32_t AHB2RSTR;			//0x14
	volatile uint32_t AHB3RSTR;			//0x18
	volatile uint32_t Reserved1[1];		//0x1c
	volatile uint32_t APB1RSTR;			//0x20
	volatile uint32_t APB2RSTR;			//0x24
	volatile uint32_t Reserved2[2];		//0x28
	volatile uint32_t AHB1ENR;			//0x30
	volatile uint32_t AHB2ENR;			//0x34
	volatile uint32_t AHB3ENR;			//0x38
	volatile uint32_t Reserved4[1];		//0x3c
	volatile uint32_t APB1ENR;			//0x40
	volatile uint32_t APB2ENR;			//0x44
	volatile uint32_t Reserved6[2];		//0x48
	volatile uint32_t AHB1LPENR;		//0x50
	volatile uint32_t AHB2LPENR;		//0x54
	volatile uint32_t AHB3LPENR;		//0x58
	volatile uint32_t Reserved7[1];		//0x5c
	volatile uint32_t APB1LPENR;		//0x60
	volatile uint32_t APB2LPENR;		//0x64
	volatile uint32_t Reserved8[2];		//0x68
	volatile uint32_t BDCR;				//0x70
	volatile uint32_t CSR;				//0x74
	volatile uint32_t Reserved10[2];	//0x78
	volatile uint32_t SSCGR;			//0x80
	volatile uint32_t PLLI2SCFGR;		//0x84
};

void enableGpioA(void);
void enableGpioB(void);
void enableGpioG(void);
void enableRng(void);
void enableTimer8(void);
void enableI2C2(void);
void enableI2C1(void);
void enableUART1(void);
void enableGpioC(void);
void enableDMA(int dmaNumber);
void enableADC1(void);
void enableWWDGLP(void);
void enableWWDG(void);

#define	MCO_LSE_SRC		1
#define	MCO_HSE_SRC		2
#define	MCO_PLL_SRC		3

#define	MCO_NO_DIV		0
#define	MCO_DIV_BY_2	4
#define	MCO_DIV_BY_3	5
#define	MCO_DIV_BY_4	6
#define	MCO_DIV_BY_5	7

//DMA
#define	DMA1_DEV		0
#define	DMA2_DEV		1

#define	rccSelectMcolSrc(x)				\
		do{								\
			Rcc->CFGR &= ~(3<<21);		\
			Rcc->CFGR |= (x)<<21;		\
		}while(0)

#define	rccSetMcolPrescaler(x)			\
		do{								\
			Rcc->CFGR &= ~(7<<24);		\
			Rcc->CFGR |= (x)<<24;		\
		}while (0)

// Control & Status register (CSR)
#define	RCC_LPWRRSTF 	(1<<31)
#define	RCC_WWDGRSTF	(1<<30)
#define	RCC_IWDGRSTF	(1<<29)
#define	RCC_SFTRSTF		(1<<28)
#define	RCC_PORRSTF		(1<<27)
#define	RCC_PINRSTF		(1<<26)
#define	RCC_BORRSTF		(1<<25)
#define	RCC_RMVF		(1<<24)

#define	rccClearAllResetFlag()			(Rcc->CSR |= RCC_RMVF)

#endif /* RCC_H_ */
