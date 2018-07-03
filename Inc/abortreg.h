/*
 * abortreg.h
 *
 *  Created on: 4 Jul 2018
 *      Author: Asus
 */

#ifndef ABORTREG_H_
#define ABORTREG_H_

#define	ORUNERRCLR	1<<4		// Clear STICKYORUN	bit
#define WDERRCLR	1<<3		// Clear WDATAERR bit
#define STKERRCLR	1<<2		// Clear STICKYERR bit
#define	STKCMPCLR	1<<1		// Clear STICKCMP bit
#define DAPABORT	1			// Generate AP abort

#endif /* ABORTREG_H_ */
