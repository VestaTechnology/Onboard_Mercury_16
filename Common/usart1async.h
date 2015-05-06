/* USART1_ASYNC.H
 *
 * This file contains the header definitions required to intitialize
 * USART1 in asynchronous mode for transmit and receive.  They are
 * designed to make full use of the libraries provided by the XC8
 * compiler.
 * 
 * These routines are specific to the PIC16F1947 processor.
 */
#ifndef _USART1ASYNC_H_
#define _USART1ASYNC_H_

#define BAUD1 115200
#define fOSC 32000000L

//#define DIVIDER1 ((int)(fOSC/(64UL * BAUD1) -1))
#define DIVIDER1 767

/* USART1 Asynchronous Initialization */
#define init_usart1()\
	SP1BRGL = (DIVIDER1 & 0xFF);     \
	SP1BRGH = (DIVIDER1 >> 8);	    \
	TRISC6 = 1;                       \
	TRISC7 = 1;      \
	TX1STAbits.SYNC = 0;    \
	TX1STAbits.BRGH = 1;    \
	BAUD1CONbits.BRG16 = 1;    \
	RC1STAbits.SPEN = 1;    \
	RC1STAbits.CREN = 1;    \
	TX1STAbits.TXEN = 1


#endif