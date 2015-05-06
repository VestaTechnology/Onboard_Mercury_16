/* USART.C
 *
 * This file contains implementations of routines that are required in order
 * to make full use of the libraries provided with the XC8 compiler.
 *
 * These routines are specific to the PIC16F1947 processor. They use EUSART2,
 * which is connected to the USB interface to the host.
 */
#include <xc.h>
#include <stdio.h>
#include "usart.h"

extern bit usart_select; //1 for USART2, 0 for USART1


/* Output one character
 */
void putch(unsigned char byte) 
{
	if (usart_select) { //USART 1 active
		/* output one byte */
		while(!TX2IF)	/* set when register is empty */
			continue;
		TX2REG = byte;
	} else {            //USART 2 active
		/* output one byte */
		while(!TX1IF)	/* set when register is empty */
			continue;
		TX1REG = byte;
	}
}

/* Obtain one character.  If the OERR bit is set, you will be 
 * stuck in the while loop forever.
 */
unsigned char getch() {
	if (usart_select) { //USART 1 active
		/* retrieve one byte */
		while(!RC2IF)	/* set when register is not empty */
			continue;
		return RC2REG;
	} else {            //USART 2 active
		/* retrieve one byte with a ~2us timeout*/
		int time_out = 1000;
		while(!RC1IF) {	/* set when register is not empty */
			if (RC1STAbits.OERR || RC1STAbits.FERR) {
				RC1STAbits.SPEN = 0;
				RC1STAbits.SPEN = 1;
				return 0x100;
			} else if (time_out == 0) {
				return 0x200;
			}
			time_out--;
			continue;
		}
		return RC1REG;
	}
}


/* Obtain one character with echo.
 */
unsigned char getche(void)
{
	unsigned char c;
	putch(c = getch());
	return c;
}

