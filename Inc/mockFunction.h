/*
 * mockFunction.h
 *
 *  Created on: 1 Aug 2018
 *      Author: Asus
 */

#ifndef MOCKFUNCTION_H_
#define MOCKFUNCTION_H_
#include <stdint.h>

void swdWriteIO(int state);
void swdWriteClk(int state);
void swdDelay(int cycles);


#endif /* MOCKFUNCTION_H_ */
