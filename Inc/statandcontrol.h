/*
 * statandcontrol.h
 *
 *  Created on: Jun 27, 2018
 *      Author: ME-D203-06
 */

#ifndef STATANDCONTROL_H_
#define STATANDCONTROL_H_


// For DP :

#define OR_UNDETECT		1			// (RoW)Overrun detection
#define STICKYORUN		1<<1		// (RoW)Check overrun status
#define	TRNMODE_EN(x)	x<<2		// (RoW)Set the transfer mode for AP operations
#define	STICKYCMP		1<<4		// (RO) Set when there is a mismatch occurs during pushed-compare operation
#define	STICKYERR		1<<5		// (RO) Set when an error is returned by AP transaction.
#define	READ_OK			1<<6		// (RoW) Response to the previous AP read or RDBUFF read
#define	WDATA_ERR		1<<7		// (RO) Set when write data error occurs
#define MASKLANE(x)		x<<8		//
#define	ERR_MODE		1<<24		// (RoW) Error mode, indicates reset behavoiur of ctrl/stat stickyerr field.

#define	CDBGRSTREQ		1<<26		// Debug reset request
#define	CDBGRSTACK		1<<27		// Debug reset acknowledge
#define	CDBGPWRUPREQ	1<<28		// Debug powerup request
#define CDBGPWRUPACK	1<<29		// Debug powerup acknowledge
#define	CSYSPWRUPREEQ	1<<30		// System powerup request
#define CSYSPWRUPACK	1<<31		// System powerup acknowledege

// For AP :

#endif /* STATANDCONTROL_H_ */
