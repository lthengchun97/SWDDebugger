/*
 * Gpio.h
 *
 *  Created on: 13 Jun 2018
 *      Author: Asus
 */

#ifndef GPIO_H_
#define GPIO_H_

#include"stdint.h"

#define GPIOA_BASE_ADDR 	0x40020000
#define GPIOB_BASE_ADDR 	0x40020400
#define GPIOC_BASE_ADDR 	0x40020800
#define GPIOD_BASE_ADDR 	0x40020c00
#define GPIOE_BASE_ADDR 	0x40021000
#define GPIOF_BASE_ADDR 	0x40021400
#define GPIOG_BASE_ADDR 	0x40021800
#define GPIOH_BASE_ADDR 	0x40021C00
#define GPIOI_BASE_ADDR 	0x40022000

#define GpioA				((GpioReg *)(GPIOA_BASE_ADDR))
#define GpioB				((GpioReg *)(GPIOB_BASE_ADDR))
#define GpioC				((GpioReg *)(GPIOC_BASE_ADDR))
#define GpioD				((GpioReg *)(GPIOD_BASE_ADDR))
#define GpioE				((GpioReg *)(GPIOE_BASE_ADDR))
#define GpioF				((GpioReg *)(GPIOF_BASE_ADDR))
#define GpioG				((GpioReg *)(GPIOG_BASE_ADDR))
#define GpioH				((GpioReg *)(GPIOH_BASE_ADDR))
#define GpioI				((GpioReg *)(GPIOI_BASE_ADDR))


#define GPIO_MODE_OFF		0X0
#define GPIO_Otype_OFF		0X4
#define GPIO_OSPEED_OFF		0X8
#define GPIO_PUPD_OFF		0Xc
#define GPIO_OD_OFF			0X14

typedef struct GpioReg GpioReg;
struct GpioReg {
	volatile uint32_t mode;				//0h
	volatile uint32_t outType;			//4h
	volatile uint32_t outSpeed;			//8h
	volatile uint32_t pullType;			//ch
	volatile uint32_t inData;			//10h
	volatile uint32_t outData;			//14h
	volatile uint32_t bsrr; 			//18h
	//volatile uint32_t bitData;		//18h
	volatile uint32_t lock;				//1ch
	volatile uint32_t altFuncLow;		//20h
	volatile uint32_t altFuncHi;		//24h
};

//Alternate function register
#define	AF0			0
#define AF1			1
#define	AF2			2
#define AF3			3
#define	AF4			4
#define AF5			5
#define	AF6			6
#define AF7			7
#define	AF8			8
#define AF9			9
#define	AF10		10
#define AF11		11
#define	AF12		12
#define AF13		13
#define	AF14		14
#define AF15		15

// pin modes
#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT 		1
#define GPIO_MODE_AF		2
#define GPIO_MODE_ANA		3

// pin output drive type
#define GPIO_PUSH_PULL		0
#define GPIO_OPEN_DRAIN		1

//pin output speed
#define GPIO_LOW_SPEED			0
#define GPIO_MEDIUM_SPEED		1
#define GPIO_HI_SPEED			2
#define GPIO_VHI_SPEED			3			// VH =  very high

//pin pull type
#define GPIO_NO_PULL		0
#define GPIO_PULL_UP		1
#define GPIO_PULL_DOWN		2

#define SET_PIN(gpio,pinNum)				(gpio->bsrr = (1 <<pinNum))
#define RESET_PIN(gpio,pinNum)				(gpio->bsrr = (1 << (16 +pinNum)))
//#define LOCK_PIN(gpio,pinNum)				(gpio->lock = (1 <<pinNum))

void gpioConfig(GpioReg *gpio,int pin, int mode, int outDriveType, int pullType, int speed);
void gpioWrite(GpioReg *gpio, int pin, int state);
void gpioConfigAltFunction(GpioReg *gpio,int pinNum,int alt_function);
void LOCK_PIN(GpioReg *gpio ,int pinNum);


#endif /* GPIO_H_ */
