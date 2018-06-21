/*
 * Gpio.c
 *
 *  Created on: 13 Jun 2018
 *      Author: Asus
 */

#include "GPIO.h"

void gpioConfig(GpioReg *gpio,int pin , int Mode , int outdriveType , int pullType , int Speed){
	gpio->mode &= ~(3<<(pin * 2));			//Clear pin mode to 0 first
	gpio->mode |= Mode <<(pin * 2);			//Set the pin mode

	gpio->outSpeed &= ~(3<<(pin *2));			//Clear pin speed to 0 first
	gpio->outSpeed |= Speed << (pin * 2);		//Set the pin speed

	gpio->pullType &= ~(3<<(pin *2));			//Clear pin pulltype to 0 first
	gpio->pullType |= pullType << (pin * 2);	//Set the pin pulltype

	gpio->outType &= ~(1<<pin);				//Clear pin outdriveType to 0 first
	gpio->outType |= outdriveType << pin;		//Set the pin outdriveType
}

void gpioWrite(GpioReg *gpio,int pin , int state){
	if(state == 1){
	gpio->outData |= 1 << pin;
}	else{
	gpio->outData &= ~(1<<pin);
}
}

int gpioRead(GpioReg *gpio,int pin ){
	return gpio->inData & (1 << pin);

}


void LOCK_PIN(GpioReg *gpio ,int pinNum){
	void LOCKPIN(GpioReg *gpio ,int pinNum){
	   volatile  int state;
		gpio->lock = (1 << 16) | (1 << pinNum);
		gpio->lock = (0 << 16) | (1 << pinNum);
		gpio->lock = (1 << 16) | (1 << pinNum);
		state = gpio->lock;
		state = gpio->lock;

	}

}

void gpioConfigAltFunction(GpioReg *gpio,int pinNum,int alt_function){
if(pinNum<8){
	//gpio->altFuncLow &= ~(0xf<<(pinNum*4));
	gpio->altFuncLow |= alt_function << (pinNum*4);
	}
else
{
	//gpio->altFuncHi &= ~(0xf<<((pinNum-8)*4));
	gpio->altFuncHi |= alt_function << ((pinNum-8)*4);
	}
}
