/* USART.H
 *
 * This file contains the header definitions that are required in order
 * to make full use of the libraries provided with the XC8 compiler.
 *
 * These routines are specific to the PIC16F1947 processor.
 */
#ifndef _USART_H_
#define _USART_H_

#define BAUD 38400     
#define fOSC 32000000L
#define NINE 0     /* Use 9bit communication? FALSE=8bit */

#define DIVIDER ((int)(fOSC/(64UL * BAUD) -1))

#if NINE == 1
#define NINE_BITS 0x40
#else
#define NINE_BITS 0
#endif

#define TX_PIN TRISG1
#define RX_PIN TRISG2

bit usart_select;    //1 for USART2, 0 for USART1

/* Serial initialization */
#define init_comms()\
	usart_select = 1;	\
	RX_PIN  = 1;	\
	TX_PIN  = 0;		  \
	ANSELG  = 0;		\
	SP2BRGL = (DIVIDER & 0xFF);	\
	SP2BRGH = (DIVIDER >> 8);	\
	RC2STA  = (NINE_BITS|0x90);	\
	TX2STA  = (NINE_BITS|0x20)


/* Function prototypes. These are the functions we must provide as low-level
 * primitives for the library.
 */
void putch(unsigned char);
unsigned char getch(void);
unsigned char getche(void);

#endif
