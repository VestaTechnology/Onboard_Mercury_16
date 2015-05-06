/* spi.c
 *
 * Routines and definitions for accessing the SPI ports on the PIC16F1947.
 */

#include <xc.h>
#include "spi.h"


/* Initialize SPI channel 1
 */
void OpenSPI(unsigned char clock, unsigned char mode, unsigned char info)
{
	TRISC = (TRISC & 0xD7) | 0x10;		/* Set SDO and SCK output, SDI input */
	SSP1STAT = (mode & SPI_MODE_TRAN_MSK) | (info & SPI_INFO_MSK);
	SSP1CON1 = (clock & 0x03) | (mode & SPI_MODE_IDLE_MSK);
	SSP1CON1 |= 0x20;			/* Set enable */
}


/* Write one byte to the channel.
 */
void WriteSPI( unsigned char value)
{
	SSP1BUF = value;
}


/* Wait for and read one byte from the channel
 */
unsigned char ReadSPI( void )
{
	while(!PIR1bits.SSP1IF); //wait until cycle complete
	PIR1bits.SSP1IF = 0;	// Clear the bit
	return ( SSP1BUF );      // return with byte read 
}


/* Initialize SPI channel 2
 */
void OpenSPI2(unsigned char clock, unsigned char mode, unsigned char info)
{
	TRISD = (TRISD & 0xAF) | 0x20;		/* Set SDO and SCK output, SDI input */
	SSP2STAT = (mode & SPI_MODE_TRAN_MSK) | (info & SPI_INFO_MSK);
	SSP2CON1 = (clock & 0x03) | (mode & SPI_MODE_IDLE_MSK);
	SSP2CON1 |= 0x20;			/* Set enable */
}


/* Write one byte to the channel
 */
void WriteSPI2( unsigned char value)
{
	SSP2BUF = value;
}


/* Wait for and read one byte from the channel
 */
unsigned char ReadSPI2( void )
{
	while(!PIR4bits.SSP2IF); //wait until cycle complete
	PIR4bits.SSP2IF = 0;	// Clear the bit
	return ( SSP2BUF );      // return with byte read 
}

